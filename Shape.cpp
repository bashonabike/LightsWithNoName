#include "Shape.h"
#include "FortuneLightsMkIDefines.h"

Shape::Shape () {
  shapeEnabled = false;
} //initial constructor

void Shape::newShape (char newBaseShape,
                      char newShapeVariant,
                      char newCurrentDepth,
                      short newTopPointLocation,
                      bool newForwardDirection) { //actual constructor
  baseShape = newBaseShape;
  shapeVariant = newShapeVariant;
  currentDepth = newCurrentDepth;
  topPointLocation = newTopPointLocation;

  forwardDirection = newForwardDirection;
  upwardsDirection = true;
  stripNum = 0;//random(0,NUMSTRIPS-1);

  shapeEnabled = true;
  currentFrame = 0;
}

void Shape::deleteShape () {
  shapeEnabled = false;
}

