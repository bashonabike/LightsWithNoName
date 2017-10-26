#ifndef Shape_H
#define Bolt_H
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

bool shapeEnabled;

Shape ();
void newShape (char newBaseShape,
              char newShapeVariant,
              char newCurrentDepth,
              short newTopPointLocation,
              bool newForwardDirection);
void deleteShape ();
};
#endif
