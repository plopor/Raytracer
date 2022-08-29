// Termm--Fall 2020

#pragma once

#include <glm/glm.hpp>

#include "Material.hpp"

class PhongMaterial : public Material {
public:
  PhongMaterial(const glm::vec3& kd, const glm::vec3& ks, double shininess, double index, double mirror, bool glossy);

  glm::vec3 shadeDiffuse(glm::vec3& outL) override;

  glm::vec3 shadeAmbient(const glm::vec3& ambient) override;

  glm::vec3 shadeSpecular(glm::vec3& specOutL) override;

  void setTexture(glm::vec3& color) override;

  double getIndex() override;

  double getMirror() override;

  bool isGlossy() override;

  virtual ~PhongMaterial();

private:
  glm::vec3 m_kd;
  glm::vec3 m_ks;

  double m_shininess;
  double m_index;
  double m_mirror;

  bool is_glossy;
};
