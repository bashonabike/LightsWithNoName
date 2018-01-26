#pragma once
#include <FastLED.h>
#ifndef ShapeType_H
#define ShapeType_H

class ShapeType {
public:
	char shapetype;
	char length;
	char numframes;
	char framerate; //is frames per increment of movement
	CRGB **data;

	ShapeType();
	ShapeType(char newShapeType);
	void instanciate(char newShapeType);
};
#endif