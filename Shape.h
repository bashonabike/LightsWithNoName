#pragma once
#ifndef Shape_H
#define Shape_H
#include "Intercept.h"

class Shape {
public:
unsigned char baseShape;
unsigned char shapeVariant;
unsigned char currentDepth;
short topPointLocation;

bool forwardDirection;
bool upwardsDirection;

unsigned char stripNum;
unsigned char currentFrame;

//Intercept* intercepts;

bool shapeEnabled;


Shape ();
void newShape (unsigned char newBaseShape,
              unsigned char newShapeVariant,
              unsigned char newCurrentDepth,
              short newTopPointLocation,
              bool newForwardDirection);
void deleteShape ();
short countdown(unsigned char width, unsigned char rate);
//void addIntercepts(unsigned char frames[], unsigned char interceptingShapeTypes[], unsigned char numIntercepts);
};
#endif
