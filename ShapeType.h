#pragma once
#include <FastLED.h>
#ifndef ShapeType_H
#define ShapeType_H

class ShapeType {
public:
	char shapetype;
	char length;
	char numframes;
	char rate;
	CRGB **data;

	ShapeType();
	ShapeType(char newShapeType);
	void instanciate(char newShapeType);
};
#endif