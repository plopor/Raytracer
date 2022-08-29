// Termm--Fall 2020

#include "Material.hpp"

Material::Material()
{}

glm::vec3 Material::shadeDiffuse(glm::vec3& outL) {
    return glm::vec3(0.0f);
}

glm::vec3 Material::shadeAmbient(const glm::vec3& ambient) {
    return glm::vec3(0.0f);
}

glm::vec3 Material::shadeSpecular(glm::vec3& specOutL) {
    return glm::vec3(0.0f);
}

void Material::setTexture(glm::vec3& color) {
    return;
}

double Material::getIndex() {
    return (double)0;
}

double Material::getMirror() {
    return (double)0;
}

bool Material::isGlossy() {
    return false;
}

Material::~Material()
{}
