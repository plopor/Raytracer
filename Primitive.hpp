// Termm--Fall 2020

#pragma once

#include <glm/glm.hpp>
#include "Ray.hpp"
#include "polyroots.hpp"

class Primitive {
public:
  virtual ~Primitive();
  virtual bool intersects(const Ray& ray, glm::vec3& point, glm::vec3& norm);
  virtual glm::vec2 textureMap(glm::vec3 pointInter);
  virtual bool hasTexture();
  virtual bool hasBump();
};

class Sphere : public Primitive {
public:
  virtual ~Sphere();
};

class Cube : public Primitive {
public:
  virtual ~Cube();
};

class NonhierSphere : public Primitive {
public:
  NonhierSphere(const glm::vec3& pos, double radius, bool tex, bool bum)
    : m_pos(pos), m_radius(radius), hasTex(tex), hasBum(bum)
  {
  }
  virtual ~NonhierSphere();
  bool intersects(const Ray& ray, glm::vec3& point, glm::vec3& norm);
  glm::vec2 textureMap(glm::vec3 pointInter);
  bool hasTexture();
  bool hasBump();

private:
  glm::vec3 m_pos;
  double m_radius;
  bool hasTex;
  bool hasBum;
};

class NonhierBox : public Primitive {
public:
  NonhierBox(const glm::vec3& pos, double size)
    : m_pos(pos), m_size(size)
  {
  }
  
  virtual ~NonhierBox();

private:
  glm::vec3 m_pos;
  double m_size;
};
