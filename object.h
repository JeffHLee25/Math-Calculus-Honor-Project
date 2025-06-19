#ifndef OBJECT_H
#define OBJECT_H

#include "Vector2D.h"

struct Object {
  Vector2D position;
  Vector2D velocity;

  Object(Vector2D pos = Vector2D(0, 0), Vector2D vel = Vector2D(0, 0))
      : position(pos), velocity(vel) {}
};

#endif
