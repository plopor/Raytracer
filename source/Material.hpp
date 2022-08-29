// Termm--Fall 2020

#pragma once

#include <glm/glm.hpp>

class Material {
public:
  virtual glm::vec3 shadeDiffuse(glm::vec3& outL);
  virtual glm::vec3 shadeAmbient(const glm::vec3& ambient);
  virtual glm::vec3 shadeSpecular(glm::vec3& specOutL);
  virtual void setTexture(glm::vec3& color);
  virtual double getIndex();
  virtual double getMirror();
  virtual bool isGlossy();

  virtual ~Material();

protected:
  Material();
};
