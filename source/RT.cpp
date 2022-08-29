// Termm--Fall 2020

#include <glm/ext.hpp>
#include <cstdlib>

#include "RT.hpp"
#include "GeometryNode.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.hpp"

void RT_Render(
		// What to render  
		SceneNode * root,

		// Image to write to, set to a given width and height  
		Image & image,

		// Viewing parameters  
		const glm::vec3 & eye,
		const glm::vec3 & view,
		const glm::vec3 & up,
		double fovy,

		// Lighting parameters  
		const glm::vec3 & ambient,
		const std::list<Light *> & lights
) {

  // Fill in raytracing code here...  
  std::string filename = "world.png";
  int width, height;
  std::vector<unsigned char> texture;
  loadImage(texture, filename, width, height, 3);

  std::string bumpFilename = "golfball.png";
  int widthB, heightB;
  std::vector<unsigned char> bump;
  loadImage(bump, bumpFilename, widthB, heightB, 1);

  std::cout << "F20: Calling RT_Render(\n" <<
		  "\t" << *root <<
          "\t" << "Image(width:" << image.width() << ", height:" << image.height() << ")\n"
          "\t" << "eye:  " << glm::to_string(eye) << std::endl <<
		  "\t" << "view: " << glm::to_string(view) << std::endl <<
		  "\t" << "up:   " << glm::to_string(up) << std::endl <<
		  "\t" << "fovy: " << fovy << std::endl <<
          "\t" << "ambient: " << glm::to_string(ambient) << std::endl <<
		  "\t" << "lights{" << std::endl;
	
	srand((unsigned)time(0));

	for(const Light * light : lights) {
		std::cout << "\t\t" <<  *light << std::endl;
	}
	std::cout << "\t}" << std::endl;
	std:: cout <<")" << std::endl;

	size_t h = image.height();
	size_t w = image.width();

	for (uint y = 0; y < h; ++y) {
		for (uint x = 0; x < w; ++x) {
			int pixel_x = w / 2 - x;
			int pixel_y = h / 2 - y;

			glm::vec3 zAxis = glm::normalize(view);
			glm::vec3 xAxis = glm::normalize(glm::cross(-zAxis, up));

			glm::vec3 colorSum = glm::vec3(0.0f);
			for (int i = 1; i <= 3; i++){
				for (int j = 1; j <= 3; j++){
					double xCoord = pixel_x - 0.25 * (double)i;
					double yCoord = pixel_y - 0.25 * (double)j;
					double zCoord = h / glm::tan(glm::radians(fovy));

					glm::vec3 pixel = eye + xCoord * xAxis + yCoord * up + zCoord * zAxis;

					Ray ray = Ray(eye, glm::normalize(pixel - eye));

					colorSum += raytrace(ray, 2, texture, width, height, bump, widthB, heightB, eye, ambient, lights, root, false);
				}
			}
			// Red: 
			image(x, y, 0) = (double)colorSum[0] / (double)9;
			// Green: 
			image(x, y, 1) = (double)colorSum[1] / (double)9;
			// Blue: 
			image(x, y, 2) = (double)colorSum[2] / (double)9;
		}
	}
}

void loadImage(std::vector<unsigned char>& texture, const std::string& filename, int& x, int& y, int tupleSize) {
	int n;
    unsigned char* data = stbi_load(filename.c_str(), &x, &y, &n, tupleSize);
    if (data != nullptr)
    {
        texture = std::vector<unsigned char>(data, data + x * y * tupleSize);
    }
    stbi_image_free(data);
}

glm::vec3 raytrace(Ray& ray, int bounces, std::vector<unsigned char>& texture, int width, int height, std::vector<unsigned char>& bump, int widthB, int heightB, const glm::vec3& eye, const glm::vec3& ambient, const std::list<Light*>& lights, SceneNode *root, bool isInside){
	glm::vec3 toReturn = glm::vec3(0.0f);

	GeometryNode* objInter = nullptr;
	glm::vec3 pointInter = glm::vec3(0.0f);
	glm::vec3 normInter = glm::vec3(0.0f);

	for (SceneNode* child : root->children) {
		if (child->m_nodeType == NodeType::GeometryNode) {
			GeometryNode *geometryNode = static_cast<GeometryNode *>(child);

			glm::vec3 tempPointInter;
			glm::vec3 tempNormInter;
			bool intersect = geometryNode->m_primitive->intersects(ray, tempPointInter, tempNormInter);

			if (intersect && (objInter == nullptr || glm::length(tempPointInter) < glm::length(pointInter))) {
				objInter = geometryNode;
				pointInter = tempPointInter;
				normInter = tempNormInter;
			}
		}
	}

	if (objInter != nullptr) {
		glm::vec3 surfColor = glm::vec3(0.0f);
		surfColor += objInter->m_material->shadeAmbient(ambient);

		if (bounces > 0){
			double index = objInter->m_material->getIndex();
			bool isGlossy = objInter->m_material->isGlossy();
			double mirror = objInter->m_material->getMirror();
			if (index != 0){
				float ratio = 1.0f / index;
				glm::vec3 t = glm::refract(ray.dir, normInter, ratio);
				if (isInside){
					t = glm::refract(ray.dir, -normInter, 1 / ratio);
				}
				glm::vec3 newOrig = pointInter + 0.1f * t;
				Ray transmitted = Ray(newOrig, t);
				if (!isGlossy) {
					return raytrace(transmitted, bounces - 1, texture, width, height, bump, widthB, heightB, eye, ambient, lights, root, !isInside);
				}
				else {
					glm::vec3 tempSum = glm::vec3(0.0f);
					tempSum += raytrace(transmitted, bounces - 1, texture, width, height, bump, widthB, heightB, eye, ambient, lights, root, !isInside);

					glm::vec3 a = glm::normalize(glm::cross(ray.dir, t));
					glm::vec3 b = glm::normalize(glm::cross(t, a));
					glm::vec3 p = pointInter + glm::normalize(t);
					int l = 1;
					int sNum = 5;

					for (int s = 0; s < sNum; s++) {
						float ep1 = (float)rand() / (float) (RAND_MAX / 0.99);
						float ep2 = (float)rand() / (float) (RAND_MAX / 0.99);
						glm::vec3 ps = p + l * (ep1 - 0.5f) * a + l * (ep2 - 0.5f) * b;

						glm::vec3 tS = ps - pointInter;
						glm::vec3 newOrigS = pointInter + 0.1f * tS;
						Ray transmittedS = Ray(newOrigS, tS);

						tempSum += raytrace(transmittedS, bounces - 1, texture, width, height, bump, widthB, heightB, eye, ambient, lights, root, !isInside);
					}
					return (tempSum / (sNum + 1));
				}
			}
			if (mirror != 0) {
				glm::vec3 reflDir = glm::reflect(ray.dir, normInter);
				glm::vec3 newOrig = pointInter + 0.1f * reflDir;
				Ray reflected = Ray(newOrig, reflDir);
				if (!isGlossy) {
					surfColor += mirror * raytrace(reflected, bounces - 1, texture, width, height, bump, widthB, heightB, eye, ambient, lights, root, false);
				}
				else {
					glm::vec3 tempSum = glm::vec3(0.0f);
					tempSum += mirror * raytrace(reflected, bounces - 1, texture, width, height, bump, widthB, heightB, eye, ambient, lights, root, false);

					glm::vec3 a = glm::normalize(glm::cross(ray.dir, reflDir));
					glm::vec3 b = glm::normalize(glm::cross(reflDir, a));
					glm::vec3 p = pointInter + glm::normalize(reflDir);
					int l = 1;
					int sNum = 35;

					for (int s = 0; s < sNum; s++) {
						float ep1 = (float)rand() / (float) (RAND_MAX / 0.99);
						float ep2 = (float)rand() / (float) (RAND_MAX / 0.99);
						glm::vec3 ps = p + l * (ep1 - 0.5f) * a + l * (ep2 - 0.5f) * b;

						glm::vec3 reflDirS = ps - pointInter;
						glm::vec3 newOrigS = pointInter + 0.1f * reflDirS;
						Ray reflectedS = Ray(newOrigS, reflDirS);

						tempSum += mirror * raytrace(reflectedS, bounces - 1, texture, width, height, bump, widthB, heightB, eye, ambient, lights, root, false);
					}

					surfColor += (tempSum / (sNum + 1));
				}
			}
		}

		for (Light * light : lights) {
			glm::vec3 lightDir = glm::normalize(light->position - pointInter);
			Ray shadow = Ray(pointInter, lightDir);
			glm::vec3 a = glm::normalize(glm::cross(normInter, lightDir));
			glm::vec3 b = glm::normalize(glm::cross(lightDir, a));
			int l = 200;
			int iNum = 0;
			int sNum = 20;

			for (int s = 0; s < sNum; s++) {
				bool intersect = false;

				if (s != 0) {
					float ep1 = (float)rand() / (float) (RAND_MAX / 0.99);
					float ep2 = (float)rand() / (float) (RAND_MAX / 0.99);
					glm::vec3 ls = light->position + l * (ep1 - 0.5f) * a + l * (ep2 - 0.5f) * b;
					glm::vec3 lightDirS = ls - pointInter;
					shadow = Ray(pointInter, lightDirS);
				}

				for (SceneNode* child : root->children) {
					if (child->m_nodeType == NodeType::GeometryNode) {
						GeometryNode *geometryNode = static_cast<GeometryNode *>(child);

						glm::vec3 tempPointInter;
						glm::vec3 tempNormInter;
						intersect = geometryNode->m_primitive->intersects(shadow, tempPointInter, tempNormInter);

						if (intersect){
							iNum++;
							break;
						}
					}
				}
			}

			if (objInter->m_primitive->hasTexture() && objInter->m_material->getIndex() == 0){
				glm::vec2 mappedCoords = objInter->m_primitive->textureMap(pointInter);
				int xIndex = floor(mappedCoords.x * (width - 1));
				int yIndex = height - 1 - floor(mappedCoords.y * (height - 1));

				size_t textureI = glm::clamp(3 * (yIndex * width + xIndex), 0, 3 * (width * height - 1));
				//std::cout << (int)texture[textureI] / 255.0f << ", " << (int)texture[textureI + 1] / 255.0f << ", " << (int)texture[textureI + 2] / 255.0f << std::endl;
				glm::vec3 mappedColor = glm::vec3((int)texture[textureI] / 255.0f, (int)texture[textureI + 1] / 255.0f, (int)texture[textureI + 2] / 255.0f);
				objInter->m_material->setTexture(mappedColor);
			}

			if (objInter->m_primitive->hasBump() && objInter->m_material->getIndex() == 0){
				glm::vec2 mappedCoords = objInter->m_primitive->textureMap(pointInter);
				int xIndex = floor(mappedCoords.x * (widthB - 1));
				int yIndex = heightB - 1 - floor(mappedCoords.y * (heightB - 1));

				size_t bumpI = yIndex * widthB + xIndex;
				size_t bumpRightI = yIndex * widthB + xIndex + 1;
				if (xIndex == widthB - 1){
					bumpRightI = yIndex * widthB;
				}
				size_t bumpRightD = (yIndex + 1) * widthB + xIndex;
				if (yIndex == heightB - 1){
					bumpRightD = xIndex;
				}
				float mappedBump = (int)bump[glm::clamp((int)bumpI, 0, widthB * heightB - 1)] / 255.0f;
				//std::cout << mappedBump << std::endl;
				float bu = 10 * ((int)bump[glm::clamp((int)bumpRightI, 0, widthB * heightB - 1)] / 255.0f - mappedBump);
				float bv = 10 * ((int)bump[glm::clamp((int)bumpRightD, 0, widthB * heightB - 1)] / 255.0f - mappedBump);
				glm::vec3 u = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), normInter));
				glm::vec3 v = glm::normalize(glm::cross(u, normInter));
				normInter = normInter + bu * u + bv * v;
			}

			glm::vec3 outL = light->findOutL(pointInter, normInter);
			surfColor += ((sNum - iNum) / sNum * objInter->m_material->shadeDiffuse(outL));
			glm::vec3 specOutL = light->findSpecOutL(pointInter, normInter, eye);
			surfColor += ((sNum - iNum) / sNum * objInter->m_material->shadeSpecular(specOutL));
		}
		// Red: 
		toReturn[0] = surfColor[0];
		// Green: 
		toReturn[1] = surfColor[1];
		// Blue: 
		toReturn[2] = surfColor[2];
	}
	else {
		// Red: 
		toReturn[0] = 0.33f;
		// Green: 
		toReturn[1] = 0.33f;
		// Blue: 
		toReturn[2] = 0.33f;
	}

	return toReturn;
}
