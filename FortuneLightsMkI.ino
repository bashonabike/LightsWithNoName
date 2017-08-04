#include <FastLED.h>
#include <TimerOne.h>

#include "Shape.h"
#include "FortuneLightsMkIDefines.h"

CRGB strip[NUMSTRIPS][STRIPLEN];

//TEMP
char shapetail[3][TEMPNUMFRAMES];
char shapehead[3][TEMPNUMFRAMES];
CRGB trialshape[3][TEMPNUMFRAMES][TEMPSIZESHAPE];
char trialShapeFrameRate[3];
unsigned short shapefadedelay = 0;

//TEMP

Shape shapeBuffer[SIZESHAPEBUFFER];
char shapeBufferTop = 0;

unsigned short frameRateCounter = 0;

String buffer = "";
char shapeType = 0;
char inByte = 0;

short effShapeSize;
short endPixel;

char currentShape, shapesRenderedCount;

short rng;

void grabSerial();

//Loop-specific variables
short localShapeBufferTop = 0;
char localShapeType = 0;


void setup() {
  Serial.begin(115200);
  Timer1.initialize(PING_RATE);
  Timer1.attachInterrupt(grabSerial, PING_RATE);

  FastLED.addLeds<NEOPIXEL, PIN1>(strip[0], STRIPLEN);
  FastLED.addLeds<NEOPIXEL, PIN2>(strip[0], STRIPLEN);
  FastLED.addLeds<NEOPIXEL, PIN3>(strip[0], STRIPLEN);
  FastLED.clear();
  FastLED.show();

  randomSeed((analogRead(0) + analogRead(2) + analogRead(7)) / 3);


  //TEMP
  char c, i;
  for (i = 0; i < TEMPNUMFRAMES; i++) {
    for (c = 0; c < TEMPSIZESHAPE; c++) {
	/*	trialshape[0][TEMPNUMFRAMES - 1 - i][c] = CHSV(10, 255, 255);
		trialshape[1][TEMPNUMFRAMES - 1 - i][c] = CHSV(80, 255, 255);
		trialshape[2][TEMPNUMFRAMES - 1 - i][c] = CHSV(190, 255,255);*/
      if (((255 * 2) / TEMPNUMFRAMES)*(TEMPNUMFRAMES / 2 - abs(TEMPNUMFRAMES / 2 - c)) - 15 * i > 0){
		  trialshape[0][TEMPNUMFRAMES - 1 - i][c] = CHSV(10, 255, ((255 * 2) / TEMPNUMFRAMES)*(TEMPNUMFRAMES / 2 - abs(TEMPNUMFRAMES / 2 - c)) - 15 * i);// formula(c, i) * 70);
        trialshape[1][TEMPNUMFRAMES - 1 - i][c] = CHSV(80, 255, ((255 * 2) / TEMPNUMFRAMES)*(TEMPNUMFRAMES / 2 - abs(TEMPNUMFRAMES / 2 - c)) - 15 * i);//formula(c, i) * 70);
        trialshape[2][TEMPNUMFRAMES - 1 - i][c] = CHSV(190, 255, ((255 * 2) / TEMPNUMFRAMES)*(TEMPNUMFRAMES / 2 - abs(TEMPNUMFRAMES / 2 - c)) - 15 * i);//formula(c, i) * 70);
      }
      else {
        trialshape[0][TEMPNUMFRAMES - 1 - i][c] = CHSV(0, 0, 0);
        trialshape[1][TEMPNUMFRAMES - 1 - i][c] = CHSV(0, 0, 0);
        trialshape[2][TEMPNUMFRAMES - 1 - i][c] = CHSV(0, 0, 0);
      }
      //      printstring = "Frame " + String((int)i) + " Px " + String((int)c) + " Val " + String((int)trialshape[0][i][c].red);
      //      Serial.println(printstring);

    }
    shapetail[0][i] = TEMPSIZESHAPE-1;
    shapetail[1][i] = TEMPSIZESHAPE-1;
    shapetail[2][i] = TEMPSIZESHAPE-1;
  }
  trialShapeFrameRate[0] = 1;
  trialShapeFrameRate[1] = 2;
  trialShapeFrameRate[2] = 3;
  //TEMP
}

void loop() {
	localShapeBufferTop = shapeBufferTop;
	localShapeType = shapeType;

  FastLED.clear();
  for (shapesRenderedCount = 0;
       shapesRenderedCount < SIZESHAPEBUFFER;
       shapesRenderedCount++) {
    currentShape = (localShapeBufferTop + shapesRenderedCount) % SIZESHAPEBUFFER;

    if (shapeBuffer[currentShape].shapeEnabled) {
		
      //TODO: Retrieve shape frame from SD card

      //TEMP
      effShapeSize = TEMPSIZESHAPE;
      endPixel = shapeBuffer[currentShape].topPointLocation - shapetail[shapeBuffer[currentShape].baseShape][shapeBuffer[currentShape].currentFrame];
      if (STRIPLEN - endPixel < TEMPSIZESHAPE) 
        effShapeSize = STRIPLEN - endPixel;
      memcpy(&strip[shapeBuffer[currentShape].stripNum][endPixel],
             trialshape[shapeBuffer[currentShape].baseShape][shapeBuffer[currentShape].currentFrame],
		  effShapeSize * SIZEOFCRGB);

      if (!(shapefadedelay % FADEIMPEDEMENT)) {
		  Serial.println((int)shapeBuffer[currentShape].currentFrame);
        if (shapeBuffer[currentShape].upwardsDirection) {
          shapeBuffer[currentShape].currentFrame++;
		  //TODO: wtf why is the final frame glitching out???
		  if (shapeBuffer[currentShape].currentFrame >= TEMPNUMFRAMES - 2) {
			  shapeBuffer[currentShape].upwardsDirection = false;
			 // if (shapeBuffer[currentShape].baseShape == 2) 
		  }
        }
        else if (!shapeBuffer[currentShape].upwardsDirection && shapeBuffer[currentShape].currentFrame > 0) shapeBuffer[currentShape].currentFrame--;
		else {
			shapeBuffer[currentShape].shapeEnabled = false;
		//	Serial.println("Burninated");
		}
      }
		  if (shapeBuffer[currentShape].forwardDirection) {
			  if (!(frameRateCounter%trialShapeFrameRate[shapeBuffer[currentShape].baseShape]))  shapeBuffer[currentShape].topPointLocation++;
			  if (shapeBuffer[currentShape].topPointLocation - shapetail[shapeBuffer[currentShape].baseShape][shapeBuffer[currentShape].currentFrame] >= STRIPLEN - 1) {
			  shapeBuffer[currentShape].shapeEnabled = false;
		//	  Serial.println("Burninated");
			}
		  }
	  }
    //TEMP
  }

FastLED.show();
  shapefadedelay = (shapefadedelay + 1) % FADEIMPEDEMENT;
  frameRateCounter++;
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

	rng = random(0, 5000);
	if (rng < (5000 * MAXFAKEOUTRATE) / (1000000 / PING_RATE) ){//&& temptimeout == 0) { //rngmax times rate/s divided by revs/s
		shapeType = 2;// random(0, 3);

    shapeBufferTop = (shapeBufferTop + 1) % SIZESHAPEBUFFER;
    shapeBuffer[shapeBufferTop].newShape(shapeType,
                                         0, //TEMP shape variant, compute it somehow
                                         0, //TEMP starter depth, compute it somehow
                                         0, //random(0, STRIPLEN - 1), //TEMP top of peak location, compute it somehow
                                         1); //TEMPforward direction, compute it somehow
	}
  //}
}
