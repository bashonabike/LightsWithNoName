#include <FastLED.h>
#include <TimerOne.h>

#include "Shape.h"
#include "FortuneLightsMkIDefines.h"

CRGB strip[NUMSTRIPS][STRIPLEN];

//TEMP
char shapetail[3][TEMPNUMFRAMES];
char shapehead[3][TEMPNUMFRAMES];
CRGB trialshape[3][TEMPNUMFRAMES][TEMPSIZESHAPE];
char shapefadedelay = 0;
char shapespeeddelay = 0;
//TEMP

Shape shapeBuffer[SIZESHAPEBUFFER];
char shapeBufferTop = 0;

String buffer = "";
char shapeType = 0;
char inByte = 0;

short effShapeSize;
short endPixel;

char currentShape, shapesRenderedCount;

char rng;

void grabSerial();
String printstring;

void setup() {
  Serial.begin(115200);
  Timer1.initialize(PING_RATE);
  Timer1.attachInterrupt(grabSerial, PING_RATE);

  FastLED.addLeds<NEOPIXEL, PIN1>(strip[0], STRIPLEN);
  FastLED.clear();
  FastLED.show();

  randomSeed((analogRead(0) + analogRead(2) + analogRead(7)) / 3);

  //TEMP
  char c, i;
  for (i = 0; i < TEMPNUMFRAMES; i++) {
    for (c = 0; c < TEMPSIZESHAPE; c++) {
      if (formula(c, i) > 0) {
        trialshape[0][i][c] = CHSV(10, 255, formula(c, i) * 70);
        trialshape[1][i][c] = CHSV(80, 255, formula(c, i) * 70);
        trialshape[2][i][c] = CHSV(190, 255, formula(c, i) * 70);
      }
      else {
        trialshape[0][i][c] = CHSV(0, 0, 0);
        trialshape[1][i][c] = CHSV(0, 0, 0);
        trialshape[2][i][c] = CHSV(0, 0, 0);
      }
      //      printstring = "Frame " + String((int)i) + " Px " + String((int)c) + " Val " + String((int)trialshape[0][i][c].red);
      //      Serial.println(printstring);

    }
    shapetail[0][i] = TEMPSIZESHAPE-1;
    shapetail[1][i] = TEMPSIZESHAPE-1;
    shapetail[2][i] = TEMPSIZESHAPE-1;
  }
  //TEMP
}

void loop() {
    char c, i;
    for (i = 0; i < TEMPNUMFRAMES; i++) {
      for (c = 0; c < TEMPSIZESHAPE; c++) {
              printstring = "Frame " + String((int)i) + " Px " + String((int)c) + " Val " + String((int)trialshape[0][i][c].red);
              Serial.println(printstring);
  
      }
    }


  FastLED.clear();
  for (currentShape = (shapeBufferTop + 1) % SIZESHAPEBUFFER, shapesRenderedCount = 0;
       shapesRenderedCount < SIZESHAPEBUFFER;
       shapesRenderedCount++) {
    currentShape = (shapeBufferTop + shapesRenderedCount) % SIZESHAPEBUFFER;

    if (shapeBuffer[currentShape].shapeEnabled) {
      //TODO: Retrieve shape frame from SD card

      //TEMP
      effShapeSize = TEMPSIZESHAPE;
      endPixel = shapeBuffer[currentShape].topPointLocation - shapetail[shapeBuffer[currentShape].baseShape][shapeBuffer[currentShape].currentFrame];
      if (STRIPLEN - endPixel < TEMPSIZESHAPE)
        effShapeSize = STRIPLEN - endPixel;
      memcpy(&strip[shapeBuffer[currentShape].stripNum][endPixel],
             &trialshape[shapeBuffer[currentShape].baseShape][shapeBuffer[currentShape].currentFrame][0],
             effShapeSize * SIZEOFCRGB);
      if (!(shapefadedelay % 5)) {
        if (shapeBuffer[currentShape].upwardsDirection) {
          shapeBuffer[currentShape].currentFrame++;
          if (shapeBuffer[currentShape].currentFrame == TEMPNUMFRAMES - 1) shapeBuffer[currentShape].upwardsDirection = false;
        }
        else if (!shapeBuffer[currentShape].upwardsDirection && shapeBuffer[currentShape].currentFrame > 0) shapeBuffer[currentShape].currentFrame--;
        else shapeBuffer[currentShape].shapeEnabled = false;
      }
      shapefadedelay = (shapefadedelay + 1) % 5;
      if (!(shapespeeddelay % 3)) {
        if (shapeBuffer[currentShape].forwardDirection) {
          shapeBuffer[currentShape].topPointLocation++;
          if (shapeBuffer[currentShape].topPointLocation - shapetail[shapeBuffer[currentShape].baseShape][shapeBuffer[currentShape].currentFrame] >= STRIPLEN)
            shapeBuffer[currentShape].shapeEnabled = false;
        }
      }
    }
    shapespeeddelay = (shapespeeddelay + 1) % 3;
    //TEMP
  }

  FastLED.show();
}

void grabSerial() {
  //if (Serial.available() > 0) {
  //  buffer = "";
  //  shapeType = 0;
  //  inByte = Serial.read(); // Read the incoming byte.
  //  while (inByte != ' ') {
  //    buffer += inByte;
  //    inByte = Serial.read(); // Read the incoming byte.
  //  }

  //  shapeType = buffer.toInt();
  //  buffer = "";
  //  inByte = Serial.read(); // Read the incoming byte.

  //  while (inByte != '\n') {
  //    buffer += inByte;
  //    inByte = Serial.read(); // Read the incoming byte.
  //  }
	rng = random(0, 256);
	if (rng > 254) {
		shapeType = random(0, 2);

    shapeBufferTop = (shapeBufferTop + 1) % SIZESHAPEBUFFER;
    shapeBuffer[shapeBufferTop].newShape(shapeType,
                                         0, //TEMP shape variant, compute it somehow
                                         0, //TEMP starter depth, compute it somehow
                                         random(0, STRIPLEN - 1), //TEMP top of peak location, compute it somehow
                                         1, //TEMP peak velocity, compute it somehow
                                         1, //TEMP peak elevation gain, compute it somehow
                                         1); //TEMPforward direction, compute it somehow
	}
  //}
}
