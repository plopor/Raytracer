// Termm--Fall 2020

#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "SceneNode.hpp"
#include "Light.hpp"
#include "Image.hpp"
#include "Ray.hpp"

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
);

void loadImage(std::vector<unsigned char>& texture, const std::string& filename, int& x, int& y, int tupleSize);

glm::vec3 raytrace(Ray& ray, int bounces, std::vector<unsigned char>& texture, int width, int height, std::vector<unsigned char>& bump, int widthB, int heightB, const glm::vec3& eye, const glm::vec3& ambient, const std::list<Light*>& lights, SceneNode* root, bool isInside);
