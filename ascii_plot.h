#ifndef ASCII_PLOT_H
#define ASCII_PLOT_H

#include <iostream>

#include "Object.h"
#include "Vector2D.h"

void simple2DPlot(const Object& obj, const Vector2D& vehiclePos);

void animateMotionSmoothWithCrash(const Object& objInit,
                                  const Vector2D& vehicleInit,
                                  const Vector2D& vehicleVel, double duration,
                                  double& crashTime, double frameRate = 10.0);

#endif
