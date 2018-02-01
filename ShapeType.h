#pragma once
#include <FastLED.h>
#ifndef ShapeType_H
#define ShapeType_H

class ShapeType {
public:
	unsigned char shapetype;
	unsigned char length;
	unsigned char numframes;
	unsigned char framerate; //is frames per increment of movement
	CRGB **data;

	ShapeType();
	ShapeType(unsigned char newShapeType);
	void instanciate(unsigned char newShapeType);
};
#endif