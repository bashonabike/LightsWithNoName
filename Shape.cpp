#include "Shape.h"
#include "ShapeType.h"
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

short Shape::countdown(char width, char rate) {
	//TODO figure out convergence point of which happens first, falls below surface or falls out of frame of view
	if (upwardsDirection)
		return (2 * width - 1) - currentFrame;  
	else
		return currentFrame;
}

void Shape::addIntercepts(char frames[], char interceptingShapeTypes[], char numIntercepts) {
	intercepts = new Intercept[numIntercepts];
	for (char c = 0; c < numIntercepts; c++) {
		intercepts[c].newIntercept(frames[c], interceptingShapeTypes[c]);
	}
}