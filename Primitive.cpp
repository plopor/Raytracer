// Termm--Fall 2020

#include "Primitive.hpp"

Primitive::~Primitive()
{
}

bool Primitive::intersects(const Ray& ray, glm::vec3& point, glm::vec3& norm) {
    return false;
}

glm::vec2 Primitive::textureMap(glm::vec3 pointInter) {
    return glm::vec2(0.0f);
}

bool Primitive::hasTexture() {
    return false;
}

bool Primitive::hasBump() {
    return false;
}

Sphere::~Sphere()
{
}

Cube::~Cube()
{
}

NonhierSphere::~NonhierSphere()
{
}

bool NonhierSphere::intersects(const Ray& ray, glm::vec3& point, glm::vec3& norm) {
    double A = glm::dot(ray.dir, ray.dir);
    double B = 2 * glm::dot(ray.dir, ray.origin - m_pos);
    double C = glm::dot(ray.origin - m_pos, ray.origin - m_pos) - m_radius * m_radius;

    double roots[2];
    size_t numRoots = quadraticRoots(A, B, C, roots);

    float t;      
    if (numRoots == 2) {
        if (roots[0] < 0 && roots[1] < 0) {
            return false;
        }
        else if (roots[0] >= 0 && roots[1] >= 0) {
            t = glm::min(roots[0], roots[1]);
        } 
        else {
            t = glm::max(roots[0], roots[1]);
        }

        if (t < 0.01) {
            return false;
        }

        point = ray.origin + t * ray.dir;
        norm = glm::normalize(point - m_pos);
        return true;
    }
    return false;
}

glm::vec2 NonhierSphere::textureMap(glm::vec3 pointInter) {
    glm::vec3 sphereCoords = pointInter - m_pos;

    double theta = atan2(sphereCoords.x, sphereCoords.z);
    double phi = acos(sphereCoords.y / m_radius);
    double raw_u = theta / (2 * 3.142857);
    double u = 1 - (raw_u + 0.5);
    double v = 1 - phi / 3.142857;

    return glm::vec2(u, v);
}

bool NonhierSphere::hasTexture() {
    return hasTex;
}

bool NonhierSphere::hasBump() {
    return hasBum;
}

NonhierBox::~NonhierBox()
{
}
