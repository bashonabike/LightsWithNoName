#ifndef Shape_H
#define Bolt_H
class Shape {
public:
char baseShape;
char shapeVariant;
char currentDepth;
short topPointLocation;

char peakVelocity; //Runtime velocity is computed using this and the frame-by-frame velocity modulator
char peakElevationGain; //Runtime elevation gain is computed using this and the frame-by-frame elevation gain modulator

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
              char newPeakVelocity,
              char newPeakElevationGain,
              bool newForwardDirection);
void deleteShape ();
};
#endif
