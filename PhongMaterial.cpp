// Termm--Fall 2020

#include <glm/gtc/constants.hpp>
#include "PhongMaterial.hpp"

PhongMaterial::PhongMaterial(
	const glm::vec3& kd, const glm::vec3& ks, double shininess, double index, double mirror, bool glossy)
	: m_kd(kd)
	, m_ks(ks)
	, m_shininess(shininess)
	, m_index(index)
	, m_mirror(mirror)
	, is_glossy(glossy)
{}

glm::vec3 PhongMaterial::shadeAmbient(const glm::vec3& ambient) {
	float ka = 1.0f;
	return ka * glm::vec3(m_kd[0] * ambient[0], m_kd[1] * ambient[1], m_kd[2] * ambient[2]);
}

glm::vec3 PhongMaterial::shadeDiffuse(glm::vec3& outL) {
	return glm::vec3(m_kd[0] * outL[0], m_kd[1] * outL[1], m_kd[2] * outL[2]);
}

glm::vec3 PhongMaterial::shadeSpecular(glm::vec3& specOutL) {
	return glm::vec3(m_ks[0] * specOutL[0], m_ks[1] * specOutL[1], m_ks[2] * specOutL[2]);
}

void PhongMaterial::setTexture(glm::vec3& color) {
	m_kd[0] = color[0];
	m_kd[1] = color[1];
	m_kd[2] = color[2];
}

double PhongMaterial::getIndex() {
	return m_index;
}

double PhongMaterial::getMirror() {
	return m_mirror;
}

bool PhongMaterial::isGlossy() {
	return is_glossy;
}

PhongMaterial::~PhongMaterial()
{}
