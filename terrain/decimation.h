#ifndef DECIMATION_H
#define DECIMATION_H

#include <Fade_2D.h>
#include <vector>

using namespace GEOM_FADE25D;

int random(int low, int high);

void decimate(std::vector<Point2> *points, float percentage);

#endif
