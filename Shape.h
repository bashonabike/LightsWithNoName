#pragma once
#ifndef Shape_H
#define Shape_H
#include "Intercept.h"

class Shape {
public:
char baseShape;
char shapeVariant;
char currentDepth;
short topPointLocation;

bool forwardDirection;
bool upwardsDirection;

char stripNum;
char currentFrame;

Intercept* intercepts;

bool shapeEnabled;


Shape ();
void newShape (char newBaseShape,
              char newShapeVariant,
              char newCurrentDepth,
              short newTopPointLocation,
              bool newForwardDirection);
void deleteShape ();
short countdown(char width, char rate);
void addIntercepts(char frames[], char interceptingShapeTypes[], char numIntercepts);
};
#endif
