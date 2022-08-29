// Termm--Fall 2020

#pragma once

#include <iosfwd>

#include <glm/glm.hpp>

// Represents a simple point light.
struct Light {
  Light();
  
  glm::vec3 colour;
  glm::vec3 position;
  double falloff[3];

  glm::vec3 findOutL(const glm::vec3& point, const glm::vec3& norm);
  glm::vec3 findSpecOutL(const glm::vec3& point, const glm::vec3& norm, const glm::vec3& eye);
};

std::ostream& operator<<(std::ostream& out, const Light& l);
