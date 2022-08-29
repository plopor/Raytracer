// Termm--Fall 2020

#include <iostream>

#include <glm/ext.hpp>

#include "Light.hpp"

Light::Light()
  : colour(0.0, 0.0, 0.0),
    position(0.0, 0.0, 0.0)
{
  falloff[0] = 1.0;
  falloff[1] = 0.0;
  falloff[2] = 0.0;
}

glm::vec3 Light::findOutL(const glm::vec3& point, const glm::vec3& norm) {
  float r = glm::length(position - point);
  float c1 = 0.01f;
  float c2 = 0.01f;
  float c3 = 0.01f;
  float i = 1500.0f;
  return glm::max(i * colour * glm::dot(glm::normalize(position - point), norm) / (c1 + c2 * r + c3 * r * r), 0.0f);
}

glm::vec3 Light::findSpecOutL(const glm::vec3& point, const glm::vec3& norm, const glm::vec3& eye) {
  glm::vec3 l = glm::normalize(position - point);
  glm::vec3 v = glm::normalize(eye - point);
  float r = glm::length(position - point);
  glm::vec3 rSpec = -l + 2 * glm::dot(l, norm) * norm;
  float c1 = 0.01f;
  float c2 = 0.01f;
  float c3 = 0.01f;
  float i = 1500.0f;
  return glm::max(i * colour * glm::dot(rSpec, v) / (c1 + c2 * r + c3 * r * r), 0.0f);
}

std::ostream& operator<<(std::ostream& out, const Light& l)
{
  out << "L[" << glm::to_string(l.colour) 
  	  << ", " << glm::to_string(l.position) << ", ";
  for (int i = 0; i < 3; i++) {
    if (i > 0) out << ", ";
    out << l.falloff[i];
  }
  out << "]";
  return out;
}
