
#include <Fade_2D.h>
#include <vector>

using namespace GEOM_FADE25D;


int random(int low, int high){
    return low + (std::rand() % (high - low + 1));
}

void decimate(std::vector<Point2> *points, float percentage){
    int amountToRemove = points->size() - int(percentage * points->size());
    if(amountToRemove < 0) return;
    for(int i = 0; i < amountToRemove; i++){
        points->erase(points->begin() + random(0, points->size()));
    }
}


