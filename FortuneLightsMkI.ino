#include <FastLED.h>
#include <TimerOne.h>

#include "Shape.h"
#include "ShapeType.h"
#include "FortuneLightsMkIDefines.h"

CRGB strip[NUMSTRIPS][STRIPLEN];

//TEMP
//TODO: get it going so only memcpys over the non-0 bits
//unsigned char shapetail[3][TEMPNUMFRAMES];
//unsigned char shapehead[3][TEMPNUMFRAMES];
//CRGB blueice[25][18];
//CRGB purplerain[24][9];
//CRGB antibluemeetspurple[16][8];
//CRGB antipurplemeetsblue[16][8];

ShapeType blueice; //= new ShapeType(0);

unsigned short shapefadedelay = 0;
unsigned char currfrm = 0;
bool tempTurnoff = false;

//TEMP

Shape shapeBuffer[SIZESHAPEBUFFER];
unsigned char shapeBufferTop = 0;

unsigned short frameRateCounter = 0;

String buffer = "";
unsigned char shapeType = 0;
unsigned char inByte = 0;

short effShapeSize;
short endPixel;

unsigned char currentShape, shapesRenderedCount;

short rng;

void grabSerial();
//void findIntercepts(Shape newShape);
//Loop-specific variables
short localShapeBufferTop = 0;
unsigned char localShapeType = 0;


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
	//shapeTypes[0].instanciate(0);
	//shapeTypes[1].instanciate(0);
	//for (unsigned char c = 0; c < NUMSHAPETYPES; c++)
	//	shapeTypes[c].instanciate(c);
	blueice.instanciate(0);



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
			//effShapeSize = shapeTypes[shapeBuffer[currentShape].baseShape].length;
			effShapeSize = blueice.length;
			endPixel = shapeBuffer[currentShape].topPointLocation - (blueice.length - 1);// -shapetail[shapeBuffer[currentShape].baseShape][shapeBuffer[currentShape].currentFrame];
			if (STRIPLEN - endPixel < blueice.length)
				effShapeSize = STRIPLEN - endPixel;
			if (shapeBuffer[currentShape].baseShape == 0) {
				currfrm = shapeBuffer[currentShape].currentFrame;
				memcpy(&strip[shapeBuffer[currentShape].stripNum][endPixel],
					//&shapeTypes[0].data[0][[shapeBuffer[currentShape].currentFrame],
					&blueice.data[0][currfrm],
					effShapeSize * SIZEOFCRGB);
				strip[0][0] = CRGB(255, 255, 255);
				strip[0][1] = CRGB(255, 255, 255);
				strip[0][2] = CRGB(255, 255, 255);
				strip[0][3] = CRGB(255, 255, 255);
				strip[0][4] = CRGB(255, 255, 255);
				strip[0][5] = CRGB(255, 255, 255);
			}
			else {
				currfrm = shapeBuffer[currentShape].currentFrame;
				memcpy(&strip[shapeBuffer[currentShape].stripNum][endPixel],
					//&shapeTypes[1].data[0][[shapeBuffer[currentShape].currentFrame],
					&blueice.data[0][currfrm],
					effShapeSize * SIZEOFCRGB);
				strip[0][0] = CRGB(255, 255, 255);
				strip[0][1] = CRGB(255, 255, 255);
				strip[0][2] = CRGB(255, 255, 255);
				strip[0][3] = CRGB(255, 255, 255);
				strip[0][4] = CRGB(255, 255, 255);
				strip[0][5] = CRGB(255, 255, 255);
			}

			if (!(shapefadedelay % FADEIMPEDEMENT)) {
				/*if (shapeBuffer[currentShape].currentFrame = 29) {
				for (int d = 0; d < TEMPSIZESHAPE; d++) {
					Serial.print((int)shapeBuffer[currentShape].baseShape);
					Serial.print("..");
					Serial.print((int)shapeBuffer[currentShape].currentFrame);
					Serial.print(", ");
					Serial.print(d);
					Serial.print(" - ");
					Serial.print(trialshape[shapeBuffer[currentShape].baseShape][shapeBuffer[currentShape].currentFrame][d].r);
					Serial.print(",");
					Serial.print(trialshape[shapeBuffer[currentShape].baseShape][shapeBuffer[currentShape].currentFrame][d].g);
					Serial.print(",");
					Serial.println(trialshape[shapeBuffer[currentShape].baseShape][shapeBuffer[currentShape].currentFrame][d].b);
				}
			}*/

			//if (currentShape % 4 == 0) {
		/*		Serial.print((int)currentShape);
				Serial.print(" - ");
				Serial.println((int)shapeBuffer[currentShape].currentFrame);*/
				//	}
					//  Serial.println((int)shapeBuffer[currentShape].currentFrame);
					  //TODO: wtf why is the final frame glitching out???
				if (shapeBuffer[currentShape].upwardsDirection && shapeBuffer[currentShape].currentFrame >= blueice.numframes - 2) {
					//Serial.println(trialshape[2][shapeBuffer[currentShape].currentFrame][5].b);
					shapeBuffer[currentShape].upwardsDirection = false;
					// if (shapeBuffer[currentShape].baseShape == 2) 
				}
				if (shapeBuffer[currentShape].upwardsDirection) {
					shapeBuffer[currentShape].currentFrame++;
				}
				else if (!shapeBuffer[currentShape].upwardsDirection && shapeBuffer[currentShape].currentFrame > 0) {
					shapeBuffer[currentShape].currentFrame--;
				}
				else {
					shapeBuffer[currentShape].shapeEnabled = false;
					//	Serial.println("Burninated");
				}
			}
			if (shapeBuffer[currentShape].forwardDirection) {
				if (!(frameRateCounter % blueice.framerate))
					shapeBuffer[currentShape].topPointLocation++;
				if (shapeBuffer[currentShape].topPointLocation - (blueice.length - 1) >= STRIPLEN - 1) {
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

	rng = random(0, 4000);
	if (rng < (5000 * MAXFAKEOUTRATE) / (1000000 / PING_RATE)) {//&& temptimeout == 0) { //rngmax times rate/s divided by revs/s
		shapeType = 0;// random(0, 2);
		shapeBufferTop = (shapeBufferTop + 1) % SIZESHAPEBUFFER;
		shapeBuffer[shapeBufferTop].newShape(shapeType,
			0, //TEMP shape variant, compute it somehow
			0, //TEMP starter depth, compute it somehow
			0, //random(0, STRIPLEN - 1), //TEMP top of peak location, compute it somehow
			1); //TEMPforward direction, compute it somehow




		//findIntercepts(shapeBuffer[shapeBufferTop]);


	}
	//}
}

//void findIntercepts(Shape newShape) {
//	//Search for bolts that it will will run into at some point
//	//TODO: get it working for bolts starting midway thru the strand
//	//TODO sorting algorithm?? store a seperate indexed list ordered by proximity?
//	unsigned char interceptFrames[SIZESHAPEBUFFER];
//	unsigned char interceptShapes[SIZESHAPEBUFFER];
//	unsigned char interceptIndex = 0;
//	short calcFrames = 0;
//	for (unsigned char c = 0; c < SIZESHAPEBUFFER; c++) {
//		//If old shape is slower than the new one (remember high rate means slow)
//		if (shapeTypes[shapeBuffer[c].baseShape].framerate > shapeTypes[newShape.baseShape].framerate) {
//			//NOTE that this only identifies when the intercept will occur ish.  Once it happens, check every cycle where the intercepting shape is at and evauluate what to do in the moment
//			//if (top-len)*delta rate < end - (top-len)*rate2 then covers all bases for it catching up
//			calcFrames = (shapeBuffer[c].topPointLocation - shapeTypes[shapeBuffer[c].baseShape].length)*
//				(shapeTypes[shapeBuffer[c].baseShape].framerate - shapeTypes[newShape.baseShape].framerate);
//			if (calcFrames < (STRIPLEN - (shapeBuffer[c].topPointLocation - shapeTypes[shapeBuffer[c].baseShape].length))*shapeTypes[shapeBuffer[c].baseShape].framerate &&
//				calcFrames <= shapeTypes[newShape.baseShape].numframes && calcFrames <= shapeTypes[shapeBuffer[c].baseShape].numframes - shapeBuffer[c].currentFrame) {
//					interceptFrames[interceptIndex] = calcFrames;
//					interceptShapes[interceptIndex] = c;
//					interceptIndex++;
//				}
//			}
//		}
//		//else if (shapeTypes[shapeBuffer[c].baseShape].framerate > shapeTypes[shapeBufferTop].framerate) {
//
//		//}
//	newShape.addIntercepts(interceptFrames, interceptShapes, interceptIndex);
//	}