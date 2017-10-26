#include <FastLED.h>
#include <TimerOne.h>

#include "Shape.h"
#include "FortuneLightsMkIDefines.h"

CRGB strip[NUMSTRIPS][STRIPLEN];

//TEMP
//TODO: get it going so only memcpys over the non-0 bits
//char shapetail[3][TEMPNUMFRAMES];
//char shapehead[3][TEMPNUMFRAMES];
CRGB blueice[25][18];
CRGB purplerain[24][9];
CRGB antibluemeetspurple[8][4];
CRGB antipurplemeetsblue[8][4];

char length[4];
char numframes[4];
char rate[2];

unsigned short shapefadedelay = 0;

bool tempTurnoff = false;

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

#pragma region PURPLE_RAIN
	//TEMP
	purplerain[0][0] = CRGB(0, 0, 2);
	purplerain[0][1] = CRGB(1, 0, 4);
	purplerain[0][2] = CRGB(2, 0, 5);
	purplerain[0][3] = CRGB(2, 0, 5);
	purplerain[0][4] = CRGB(3, 0, 5);
	purplerain[0][5] = CRGB(3, 0, 5);
	purplerain[0][6] = CRGB(3, 0, 4);
	purplerain[0][7] = CRGB(3, 0, 3);
	purplerain[0][8] = CRGB(2, 0, 2);
	purplerain[1][0] = CRGB(1, 0, 5);
	purplerain[1][1] = CRGB(2, 0, 7);
	purplerain[1][2] = CRGB(3, 0, 9);
	purplerain[1][3] = CRGB(5, 0, 10);
	purplerain[1][4] = CRGB(6, 0, 11);
	purplerain[1][5] = CRGB(7, 0, 10);
	purplerain[1][6] = CRGB(7, 0, 9);
	purplerain[1][7] = CRGB(6, 0, 6);
	purplerain[1][8] = CRGB(4, 0, 4);
	purplerain[2][0] = CRGB(1, 0, 7);
	purplerain[2][1] = CRGB(3, 0, 11);
	purplerain[2][2] = CRGB(5, 0, 14);
	purplerain[2][3] = CRGB(7, 0, 16);
	purplerain[2][4] = CRGB(9, 0, 16);
	purplerain[2][5] = CRGB(10, 0, 15);
	purplerain[2][6] = CRGB(10, 0, 13);
	purplerain[2][7] = CRGB(9, 0, 10);
	purplerain[2][8] = CRGB(7, 0, 6);
	purplerain[3][0] = CRGB(1, 0, 10);
	purplerain[3][1] = CRGB(4, 0, 15);
	purplerain[3][2] = CRGB(6, 0, 19);
	purplerain[3][3] = CRGB(9, 0, 21);
	purplerain[3][4] = CRGB(12, 0, 21);
	purplerain[3][5] = CRGB(14, 0, 21);
	purplerain[3][6] = CRGB(14, 0, 17);
	purplerain[3][7] = CRGB(12, 0, 13);
	purplerain[3][8] = CRGB(9, 0, 9);
	purplerain[4][0] = CRGB(1, 0, 12);
	purplerain[4][1] = CRGB(4, 0, 19);
	purplerain[4][2] = CRGB(8, 0, 24);
	purplerain[4][3] = CRGB(11, 0, 26);
	purplerain[4][4] = CRGB(15, 0, 26);
	purplerain[4][5] = CRGB(17, 0, 26);
	purplerain[4][6] = CRGB(17, 0, 22);
	purplerain[4][7] = CRGB(15, 0, 16);
	purplerain[4][8] = CRGB(11, 0, 11);
	purplerain[5][0] = CRGB(2, 0, 14);
	purplerain[5][1] = CRGB(5, 1, 22);
	purplerain[5][2] = CRGB(10, 0, 28);
	purplerain[5][3] = CRGB(14, 1, 31);
	purplerain[5][4] = CRGB(18, 1, 32);
	purplerain[5][5] = CRGB(21, 0, 31);
	purplerain[5][6] = CRGB(21, 0, 26);
	purplerain[5][7] = CRGB(18, 0, 19);
	purplerain[5][8] = CRGB(13, 0, 13);
	purplerain[6][0] = CRGB(2, 0, 17);
	purplerain[6][1] = CRGB(6, 1, 26);
	purplerain[6][2] = CRGB(11, 0, 33);
	purplerain[6][3] = CRGB(16, 1, 36);
	purplerain[6][4] = CRGB(21, 1, 37);
	purplerain[6][5] = CRGB(24, 0, 36);
	purplerain[6][6] = CRGB(24, 0, 30);
	purplerain[6][7] = CRGB(21, 0, 22);
	purplerain[6][8] = CRGB(15, 0, 15);
	purplerain[7][0] = CRGB(2, 0, 19);
	purplerain[7][1] = CRGB(7, 1, 30);
	purplerain[7][2] = CRGB(13, 0, 38);
	purplerain[7][3] = CRGB(18, 1, 41);
	purplerain[7][4] = CRGB(24, 1, 42);
	purplerain[7][5] = CRGB(28, 0, 41);
	purplerain[7][6] = CRGB(28, 0, 35);
	purplerain[7][7] = CRGB(24, 0, 26);
	purplerain[7][8] = CRGB(18, 0, 17);
	purplerain[8][0] = CRGB(3, 0, 21);
	purplerain[8][1] = CRGB(8, 1, 33);
	purplerain[8][2] = CRGB(14, 0, 42);
	purplerain[8][3] = CRGB(21, 1, 47);
	purplerain[8][4] = CRGB(27, 1, 48);
	purplerain[8][5] = CRGB(31, 0, 46);
	purplerain[8][6] = CRGB(31, 0, 39);
	purplerain[8][7] = CRGB(27, 0, 29);
	purplerain[8][8] = CRGB(20, 0, 19);
	purplerain[9][0] = CRGB(3, 0, 24);
	purplerain[9][1] = CRGB(9, 1, 37);
	purplerain[9][2] = CRGB(16, 0, 47);
	purplerain[9][3] = CRGB(23, 1, 52);
	purplerain[9][4] = CRGB(30, 1, 53);
	purplerain[9][5] = CRGB(35, 0, 51);
	purplerain[9][6] = CRGB(35, 0, 43);
	purplerain[9][7] = CRGB(30, 0, 32);
	purplerain[9][8] = CRGB(22, 0, 21);
	purplerain[10][0] = CRGB(3, 0, 26);
	purplerain[10][1] = CRGB(10, 1, 41);
	purplerain[10][2] = CRGB(17, 0, 52);
	purplerain[10][3] = CRGB(25, 1, 57);
	purplerain[10][4] = CRGB(33, 1, 58);
	purplerain[10][5] = CRGB(38, 0, 56);
	purplerain[10][6] = CRGB(38, 0, 48);
	purplerain[10][7] = CRGB(33, 0, 35);
	purplerain[10][8] = CRGB(24, 0, 23);
	purplerain[11][0] = CRGB(4, 1, 29);
	purplerain[11][1] = CRGB(11, 1, 45);
	purplerain[11][2] = CRGB(19, 1, 57);
	purplerain[11][3] = CRGB(28, 1, 62);
	purplerain[11][4] = CRGB(36, 1, 64);
	purplerain[11][5] = CRGB(42, 1, 62);
	purplerain[11][6] = CRGB(42, 0, 52);
	purplerain[11][7] = CRGB(36, 0, 39);
	purplerain[11][8] = CRGB(27, 0, 26);
	purplerain[12][0] = CRGB(4, 1, 31);
	purplerain[12][1] = CRGB(11, 1, 48);
	purplerain[12][2] = CRGB(21, 1, 61);
	purplerain[12][3] = CRGB(30, 1, 67);
	purplerain[12][4] = CRGB(38, 1, 69);
	purplerain[12][5] = CRGB(45, 1, 67);
	purplerain[12][6] = CRGB(45, 0, 56);
	purplerain[12][7] = CRGB(38, 0, 42);
	purplerain[12][8] = CRGB(29, 0, 28);
	purplerain[13][0] = CRGB(4, 1, 33);
	purplerain[13][1] = CRGB(12, 1, 52);
	purplerain[13][2] = CRGB(22, 1, 66);
	purplerain[13][3] = CRGB(32, 1, 72);
	purplerain[13][4] = CRGB(41, 1, 74);
	purplerain[13][5] = CRGB(48, 1, 72);
	purplerain[13][6] = CRGB(48, 0, 61);
	purplerain[13][7] = CRGB(41, 0, 45);
	purplerain[13][8] = CRGB(31, 0, 30);
	purplerain[14][0] = CRGB(4, 1, 36);
	purplerain[14][1] = CRGB(13, 1, 56);
	purplerain[14][2] = CRGB(24, 1, 71);
	purplerain[14][3] = CRGB(34, 1, 78);
	purplerain[14][4] = CRGB(44, 1, 79);
	purplerain[14][5] = CRGB(52, 1, 77);
	purplerain[14][6] = CRGB(52, 0, 65);
	purplerain[14][7] = CRGB(44, 0, 48);
	purplerain[14][8] = CRGB(33, 0, 32);
	purplerain[15][0] = CRGB(5, 1, 38);
	purplerain[15][1] = CRGB(14, 1, 59);
	purplerain[15][2] = CRGB(25, 1, 75);
	purplerain[15][3] = CRGB(37, 1, 83);
	purplerain[15][4] = CRGB(47, 1, 85);
	purplerain[15][5] = CRGB(55, 1, 82);
	purplerain[15][6] = CRGB(55, 0, 69);
	purplerain[15][7] = CRGB(47, 0, 51);
	purplerain[15][8] = CRGB(35, 0, 34);
	purplerain[16][0] = CRGB(5, 1, 40);
	purplerain[16][1] = CRGB(15, 1, 63);
	purplerain[16][2] = CRGB(27, 1, 80);
	purplerain[16][3] = CRGB(39, 1, 88);
	purplerain[16][4] = CRGB(50, 1, 90);
	purplerain[16][5] = CRGB(59, 1, 87);
	purplerain[16][6] = CRGB(59, 0, 74);
	purplerain[16][7] = CRGB(50, 0, 55);
	purplerain[16][8] = CRGB(38, 0, 36);
	purplerain[17][0] = CRGB(5, 1, 43);
	purplerain[17][1] = CRGB(16, 2, 67);
	purplerain[17][2] = CRGB(29, 1, 85);
	purplerain[17][3] = CRGB(41, 2, 93);
	purplerain[17][4] = CRGB(53, 2, 95);
	purplerain[17][5] = CRGB(62, 1, 92);
	purplerain[17][6] = CRGB(62, 0, 78);
	purplerain[17][7] = CRGB(53, 0, 58);
	purplerain[17][8] = CRGB(40, 0, 38);
	purplerain[18][0] = CRGB(6, 1, 45);
	purplerain[18][1] = CRGB(17, 2, 70);
	purplerain[18][2] = CRGB(30, 1, 89);
	purplerain[18][3] = CRGB(44, 2, 98);
	purplerain[18][4] = CRGB(56, 2, 101);
	purplerain[18][5] = CRGB(66, 1, 97);
	purplerain[18][6] = CRGB(66, 0, 82);
	purplerain[18][7] = CRGB(56, 0, 61);
	purplerain[18][8] = CRGB(42, 0, 40);
	purplerain[19][0] = CRGB(6, 1, 48);
	purplerain[19][1] = CRGB(18, 2, 74);
	purplerain[19][2] = CRGB(32, 1, 94);
	purplerain[19][3] = CRGB(46, 2, 103);
	purplerain[19][4] = CRGB(59, 2, 106);
	purplerain[19][5] = CRGB(69, 1, 103);
	purplerain[19][6] = CRGB(69, 0, 87);
	purplerain[19][7] = CRGB(59, 0, 64);
	purplerain[19][8] = CRGB(44, 0, 43);
	purplerain[20][0] = CRGB(6, 1, 50);
	purplerain[20][1] = CRGB(18, 2, 78);
	purplerain[20][2] = CRGB(33, 1, 99);
	purplerain[20][3] = CRGB(48, 2, 109);
	purplerain[20][4] = CRGB(62, 2, 111);
	purplerain[20][5] = CRGB(73, 1, 108);
	purplerain[20][6] = CRGB(73, 0, 91);
	purplerain[20][7] = CRGB(62, 0, 67);
	purplerain[20][8] = CRGB(46, 0, 45);
	purplerain[21][0] = CRGB(6, 1, 52);
	purplerain[21][1] = CRGB(19, 2, 82);
	purplerain[21][2] = CRGB(35, 1, 104);
	purplerain[21][3] = CRGB(50, 2, 114);
	purplerain[21][4] = CRGB(65, 2, 116);
	purplerain[21][5] = CRGB(76, 1, 113);
	purplerain[21][6] = CRGB(76, 0, 95);
	purplerain[21][7] = CRGB(65, 0, 71);
	purplerain[21][8] = CRGB(49, 0, 47);
	purplerain[22][0] = CRGB(7, 1, 55);
	purplerain[22][1] = CRGB(20, 2, 85);
	purplerain[22][2] = CRGB(36, 1, 108);
	purplerain[22][3] = CRGB(53, 2, 119);
	purplerain[22][4] = CRGB(68, 2, 122);
	purplerain[22][5] = CRGB(80, 1, 118);
	purplerain[22][6] = CRGB(80, 0, 100);
	purplerain[22][7] = CRGB(68, 0, 74);
	purplerain[22][8] = CRGB(51, 0, 49);
	purplerain[23][0] = CRGB(7, 1, 57);
	purplerain[23][1] = CRGB(21, 2, 89);
	purplerain[23][2] = CRGB(38, 1, 113);
	purplerain[23][3] = CRGB(55, 2, 124);
	purplerain[23][4] = CRGB(71, 2, 127);
	purplerain[23][5] = CRGB(83, 1, 123);
	purplerain[23][6] = CRGB(83, 0, 104);
	purplerain[23][7] = CRGB(71, 0, 77);
	purplerain[23][8] = CRGB(53, 0, 51);
	length[0] = 9;
	numframes[0] = 24;
	length[2] = 4;
	numframes[2] = 8;
	rate[0] = 2;
	//TEMP
#pragma endregion PURPLE_RAIN
#pragma region BLUE_ICE
	blueice[0][0] = CRGB(0, 9, 10);
	blueice[0][1] = CRGB(1, 9, 10);
	blueice[0][2] = CRGB(1, 9, 10);
	blueice[0][3] = CRGB(1, 8, 10);
	blueice[0][4] = CRGB(1, 8, 10);
	blueice[0][5] = CRGB(1, 8, 10);
	blueice[0][6] = CRGB(1, 8, 10);
	blueice[0][7] = CRGB(1, 7, 10);
	blueice[0][8] = CRGB(1, 7, 10);
	blueice[0][9] = CRGB(1, 7, 10);
	blueice[0][10] = CRGB(2, 7, 10);
	blueice[0][11] = CRGB(2, 7, 10);
	blueice[0][12] = CRGB(2, 6, 10);
	blueice[0][13] = CRGB(2, 6, 10);
	blueice[0][14] = CRGB(2, 6, 10);
	blueice[0][15] = CRGB(2, 6, 10);
	blueice[0][16] = CRGB(2, 5, 10);
	blueice[0][17] = CRGB(2, 5, 10);
	blueice[1][0] = CRGB(1, 18, 20);
	blueice[1][1] = CRGB(1, 18, 20);
	blueice[1][2] = CRGB(1, 17, 20);
	blueice[1][3] = CRGB(2, 17, 20);
	blueice[1][4] = CRGB(2, 16, 20);
	blueice[1][5] = CRGB(2, 16, 20);
	blueice[1][6] = CRGB(2, 15, 20);
	blueice[1][7] = CRGB(2, 15, 20);
	blueice[1][8] = CRGB(3, 14, 20);
	blueice[1][9] = CRGB(3, 14, 20);
	blueice[1][10] = CRGB(3, 13, 20);
	blueice[1][11] = CRGB(3, 13, 20);
	blueice[1][12] = CRGB(3, 13, 20);
	blueice[1][13] = CRGB(4, 12, 20);
	blueice[1][14] = CRGB(4, 12, 20);
	blueice[1][15] = CRGB(4, 11, 20);
	blueice[1][16] = CRGB(4, 11, 20);
	blueice[1][17] = CRGB(4, 11, 20);
	blueice[2][0] = CRGB(1, 27, 31);
	blueice[2][1] = CRGB(2, 26, 31);
	blueice[2][2] = CRGB(2, 26, 31);
	blueice[2][3] = CRGB(2, 25, 31);
	blueice[2][4] = CRGB(3, 24, 31);
	blueice[2][5] = CRGB(3, 24, 31);
	blueice[2][6] = CRGB(3, 23, 31);
	blueice[2][7] = CRGB(4, 22, 31);
	blueice[2][8] = CRGB(4, 22, 31);
	blueice[2][9] = CRGB(4, 21, 31);
	blueice[2][10] = CRGB(5, 20, 31);
	blueice[2][11] = CRGB(5, 20, 31);
	blueice[2][12] = CRGB(5, 19, 31);
	blueice[2][13] = CRGB(6, 18, 31);
	blueice[2][14] = CRGB(6, 18, 31);
	blueice[2][15] = CRGB(6, 17, 31);
	blueice[2][16] = CRGB(7, 16, 31);
	blueice[2][17] = CRGB(7, 16, 31);
	blueice[3][0] = CRGB(2, 36, 41);
	blueice[3][1] = CRGB(2, 35, 41);
	blueice[3][2] = CRGB(3, 34, 41);
	blueice[3][3] = CRGB(3, 33, 41);
	blueice[3][4] = CRGB(3, 32, 41);
	blueice[3][5] = CRGB(4, 32, 41);
	blueice[3][6] = CRGB(4, 31, 41);
	blueice[3][7] = CRGB(5, 30, 41);
	blueice[3][8] = CRGB(5, 29, 41);
	blueice[3][9] = CRGB(6, 28, 41);
	blueice[3][10] = CRGB(6, 27, 41);
	blueice[3][11] = CRGB(7, 26, 41);
	blueice[3][12] = CRGB(7, 25, 41);
	blueice[3][13] = CRGB(8, 24, 41);
	blueice[3][14] = CRGB(8, 24, 41);
	blueice[3][15] = CRGB(8, 23, 41);
	blueice[3][16] = CRGB(9, 22, 41);
	blueice[3][17] = CRGB(9, 21, 41);
	blueice[4][0] = CRGB(2, 45, 51);
	blueice[4][1] = CRGB(3, 44, 51);
	blueice[4][2] = CRGB(3, 43, 51);
	blueice[4][3] = CRGB(4, 42, 51);
	blueice[4][4] = CRGB(4, 41, 51);
	blueice[4][5] = CRGB(5, 39, 51);
	blueice[4][6] = CRGB(5, 38, 51);
	blueice[4][7] = CRGB(6, 37, 51);
	blueice[4][8] = CRGB(6, 36, 51);
	blueice[4][9] = CRGB(7, 35, 51);
	blueice[4][10] = CRGB(8, 34, 51);
	blueice[4][11] = CRGB(8, 33, 51);
	blueice[4][12] = CRGB(9, 32, 51);
	blueice[4][13] = CRGB(9, 30, 51);
	blueice[4][14] = CRGB(10, 29, 51);
	blueice[4][15] = CRGB(10, 28, 51);
	blueice[4][16] = CRGB(11, 27, 51);
	blueice[4][17] = CRGB(11, 26, 51);
	blueice[5][0] = CRGB(2, 54, 61);
	blueice[5][1] = CRGB(3, 53, 61);
	blueice[5][2] = CRGB(4, 51, 61);
	blueice[5][3] = CRGB(5, 50, 61);
	blueice[5][4] = CRGB(5, 49, 61);
	blueice[5][5] = CRGB(6, 47, 61);
	blueice[5][6] = CRGB(6, 46, 61);
	blueice[5][7] = CRGB(7, 44, 61);
	blueice[5][8] = CRGB(8, 43, 61);
	blueice[5][9] = CRGB(8, 42, 61);
	blueice[5][10] = CRGB(9, 40, 61);
	blueice[5][11] = CRGB(10, 39, 61);
	blueice[5][12] = CRGB(10, 38, 61);
	blueice[5][13] = CRGB(11, 36, 61);
	blueice[5][14] = CRGB(12, 35, 61);
	blueice[5][15] = CRGB(12, 34, 61);
	blueice[5][16] = CRGB(13, 33, 61);
	blueice[5][17] = CRGB(13, 32, 61);
	blueice[6][0] = CRGB(3, 63, 71);
	blueice[6][1] = CRGB(4, 61, 71);
	blueice[6][2] = CRGB(4, 60, 71);
	blueice[6][3] = CRGB(5, 58, 71);
	blueice[6][4] = CRGB(6, 57, 71);
	blueice[6][5] = CRGB(7, 55, 71);
	blueice[6][6] = CRGB(7, 54, 71);
	blueice[6][7] = CRGB(8, 52, 71);
	blueice[6][8] = CRGB(9, 50, 71);
	blueice[6][9] = CRGB(10, 49, 71);
	blueice[6][10] = CRGB(11, 47, 71);
	blueice[6][11] = CRGB(11, 46, 71);
	blueice[6][12] = CRGB(12, 44, 71);
	blueice[6][13] = CRGB(13, 43, 71);
	blueice[6][14] = CRGB(13, 41, 71);
	blueice[6][15] = CRGB(14, 39, 71);
	blueice[6][16] = CRGB(15, 38, 71);
	blueice[6][17] = CRGB(16, 37, 71);
	blueice[7][0] = CRGB(3, 72, 82);
	blueice[7][1] = CRGB(4, 70, 82);
	blueice[7][2] = CRGB(5, 68, 82);
	blueice[7][3] = CRGB(6, 67, 82);
	blueice[7][4] = CRGB(7, 65, 82);
	blueice[7][5] = CRGB(8, 63, 82);
	blueice[7][6] = CRGB(8, 61, 82);
	blueice[7][7] = CRGB(10, 59, 82);
	blueice[7][8] = CRGB(10, 58, 82);
	blueice[7][9] = CRGB(11, 56, 82);
	blueice[7][10] = CRGB(12, 54, 82);
	blueice[7][11] = CRGB(13, 52, 82);
	blueice[7][12] = CRGB(14, 51, 82);
	blueice[7][13] = CRGB(15, 49, 82);
	blueice[7][14] = CRGB(15, 47, 82);
	blueice[7][15] = CRGB(16, 45, 82);
	blueice[7][16] = CRGB(18, 44, 82);
	blueice[7][17] = CRGB(18, 42, 82);
	blueice[8][0] = CRGB(4, 81, 92);
	blueice[8][1] = CRGB(5, 79, 92);
	blueice[8][2] = CRGB(6, 77, 92);
	blueice[8][3] = CRGB(7, 75, 92);
	blueice[8][4] = CRGB(8, 73, 92);
	blueice[8][5] = CRGB(9, 71, 92);
	blueice[8][6] = CRGB(9, 69, 92);
	blueice[8][7] = CRGB(11, 67, 92);
	blueice[8][8] = CRGB(12, 65, 92);
	blueice[8][9] = CRGB(13, 63, 92);
	blueice[8][10] = CRGB(14, 60, 92);
	blueice[8][11] = CRGB(15, 59, 92);
	blueice[8][12] = CRGB(15, 57, 92);
	blueice[8][13] = CRGB(17, 55, 92);
	blueice[8][14] = CRGB(17, 53, 92);
	blueice[8][15] = CRGB(18, 51, 92);
	blueice[8][16] = CRGB(20, 49, 92);
	blueice[8][17] = CRGB(20, 48, 92);
	blueice[9][0] = CRGB(4, 90, 102);
	blueice[9][1] = CRGB(5, 88, 102);
	blueice[9][2] = CRGB(6, 85, 102);
	blueice[9][3] = CRGB(8, 83, 102);
	blueice[9][4] = CRGB(8, 81, 102);
	blueice[9][5] = CRGB(10, 79, 102);
	blueice[9][6] = CRGB(10, 77, 102);
	blueice[9][7] = CRGB(12, 74, 102);
	blueice[9][8] = CRGB(13, 72, 102);
	blueice[9][9] = CRGB(14, 70, 102);
	blueice[9][10] = CRGB(15, 67, 102);
	blueice[9][11] = CRGB(16, 65, 102);
	blueice[9][12] = CRGB(17, 63, 102);
	blueice[9][13] = CRGB(19, 61, 102);
	blueice[9][14] = CRGB(19, 59, 102);
	blueice[9][15] = CRGB(20, 56, 102);
	blueice[9][16] = CRGB(22, 54, 102);
	blueice[9][17] = CRGB(22, 53, 102);
	blueice[10][0] = CRGB(4, 99, 112);
	blueice[10][1] = CRGB(6, 96, 112);
	blueice[10][2] = CRGB(7, 94, 112);
	blueice[10][3] = CRGB(8, 92, 112);
	blueice[10][4] = CRGB(9, 89, 112);
	blueice[10][5] = CRGB(11, 87, 112);
	blueice[10][6] = CRGB(11, 84, 112);
	blueice[10][7] = CRGB(13, 81, 112);
	blueice[10][8] = CRGB(14, 79, 112);
	blueice[10][9] = CRGB(15, 77, 112);
	blueice[10][10] = CRGB(17, 74, 112);
	blueice[10][11] = CRGB(18, 72, 112);
	blueice[10][12] = CRGB(19, 70, 112);
	blueice[10][13] = CRGB(21, 67, 112);
	blueice[10][14] = CRGB(21, 65, 112);
	blueice[10][15] = CRGB(22, 62, 112);
	blueice[10][16] = CRGB(24, 60, 112);
	blueice[10][17] = CRGB(25, 58, 112);
	blueice[11][0] = CRGB(5, 108, 122);
	blueice[11][1] = CRGB(6, 105, 122);
	blueice[11][2] = CRGB(8, 102, 122);
	blueice[11][3] = CRGB(9, 100, 122);
	blueice[11][4] = CRGB(10, 97, 122);
	blueice[11][5] = CRGB(12, 95, 122);
	blueice[11][6] = CRGB(12, 92, 122);
	blueice[11][7] = CRGB(14, 89, 122);
	blueice[11][8] = CRGB(15, 86, 122);
	blueice[11][9] = CRGB(17, 84, 122);
	blueice[11][10] = CRGB(18, 81, 122);
	blueice[11][11] = CRGB(20, 78, 122);
	blueice[11][12] = CRGB(21, 76, 122);
	blueice[11][13] = CRGB(23, 73, 122);
	blueice[11][14] = CRGB(23, 71, 122);
	blueice[11][15] = CRGB(24, 68, 122);
	blueice[11][16] = CRGB(26, 65, 122);
	blueice[11][17] = CRGB(27, 63, 122);
	blueice[12][0] = CRGB(5, 116, 133);
	blueice[12][1] = CRGB(7, 114, 133);
	blueice[12][2] = CRGB(8, 111, 133);
	blueice[12][3] = CRGB(10, 108, 133);
	blueice[12][4] = CRGB(11, 106, 133);
	blueice[12][5] = CRGB(12, 102, 133);
	blueice[12][6] = CRGB(14, 100, 133);
	blueice[12][7] = CRGB(16, 96, 133);
	blueice[12][8] = CRGB(17, 94, 133);
	blueice[12][9] = CRGB(18, 91, 133);
	blueice[12][10] = CRGB(20, 87, 133);
	blueice[12][11] = CRGB(21, 85, 133);
	blueice[12][12] = CRGB(22, 82, 133);
	blueice[12][13] = CRGB(24, 79, 133);
	blueice[12][14] = CRGB(25, 76, 133);
	blueice[12][15] = CRGB(27, 73, 133);
	blueice[12][16] = CRGB(29, 71, 133);
	blueice[12][17] = CRGB(29, 69, 133);
	blueice[13][0] = CRGB(6, 125, 143);
	blueice[13][1] = CRGB(7, 123, 143);
	blueice[13][2] = CRGB(9, 119, 143);
	blueice[13][3] = CRGB(11, 116, 143);
	blueice[13][4] = CRGB(12, 114, 143);
	blueice[13][5] = CRGB(13, 110, 143);
	blueice[13][6] = CRGB(15, 108, 143);
	blueice[13][7] = CRGB(17, 104, 143);
	blueice[13][8] = CRGB(18, 101, 143);
	blueice[13][9] = CRGB(20, 98, 143);
	blueice[13][10] = CRGB(21, 94, 143);
	blueice[13][11] = CRGB(23, 91, 143);
	blueice[13][12] = CRGB(24, 88, 143);
	blueice[13][13] = CRGB(26, 85, 143);
	blueice[13][14] = CRGB(27, 82, 143);
	blueice[13][15] = CRGB(29, 79, 143);
	blueice[13][16] = CRGB(31, 76, 143);
	blueice[13][17] = CRGB(31, 74, 143);
	blueice[14][0] = CRGB(6, 134, 153);
	blueice[14][1] = CRGB(8, 131, 153);
	blueice[14][2] = CRGB(10, 128, 153);
	blueice[14][3] = CRGB(11, 125, 153);
	blueice[14][4] = CRGB(13, 122, 153);
	blueice[14][5] = CRGB(14, 118, 153);
	blueice[14][6] = CRGB(16, 115, 153);
	blueice[14][7] = CRGB(18, 111, 153);
	blueice[14][8] = CRGB(19, 108, 153);
	blueice[14][9] = CRGB(21, 105, 153);
	blueice[14][10] = CRGB(23, 101, 153);
	blueice[14][11] = CRGB(25, 98, 153);
	blueice[14][12] = CRGB(26, 95, 153);
	blueice[14][13] = CRGB(28, 91, 153);
	blueice[14][14] = CRGB(29, 88, 153);
	blueice[14][15] = CRGB(31, 85, 153);
	blueice[14][16] = CRGB(33, 82, 153);
	blueice[14][17] = CRGB(34, 79, 153);
	blueice[15][0] = CRGB(6, 143, 163);
	blueice[15][1] = CRGB(8, 140, 163);
	blueice[15][2] = CRGB(10, 136, 163);
	blueice[15][3] = CRGB(12, 133, 163);
	blueice[15][4] = CRGB(13, 130, 163);
	blueice[15][5] = CRGB(15, 126, 163);
	blueice[15][6] = CRGB(17, 123, 163);
	blueice[15][7] = CRGB(19, 118, 163);
	blueice[15][8] = CRGB(20, 115, 163);
	blueice[15][9] = CRGB(22, 112, 163);
	blueice[15][10] = CRGB(24, 108, 163);
	blueice[15][11] = CRGB(26, 104, 163);
	blueice[15][12] = CRGB(28, 101, 163);
	blueice[15][13] = CRGB(30, 97, 163);
	blueice[15][14] = CRGB(31, 94, 163);
	blueice[15][15] = CRGB(33, 90, 163);
	blueice[15][16] = CRGB(35, 87, 163);
	blueice[15][17] = CRGB(36, 84, 163);
	blueice[16][0] = CRGB(7, 152, 173);
	blueice[16][1] = CRGB(9, 149, 173);
	blueice[16][2] = CRGB(11, 145, 173);
	blueice[16][3] = CRGB(13, 141, 173);
	blueice[16][4] = CRGB(14, 138, 173);
	blueice[16][5] = CRGB(16, 134, 173);
	blueice[16][6] = CRGB(18, 131, 173);
	blueice[16][7] = CRGB(20, 126, 173);
	blueice[16][8] = CRGB(22, 122, 173);
	blueice[16][9] = CRGB(24, 119, 173);
	blueice[16][10] = CRGB(26, 114, 173);
	blueice[16][11] = CRGB(28, 111, 173);
	blueice[16][12] = CRGB(29, 107, 173);
	blueice[16][13] = CRGB(32, 103, 173);
	blueice[16][14] = CRGB(33, 100, 173);
	blueice[16][15] = CRGB(35, 96, 173);
	blueice[16][16] = CRGB(37, 92, 173);
	blueice[16][17] = CRGB(38, 90, 173);
	blueice[17][0] = CRGB(7, 161, 184);
	blueice[17][1] = CRGB(9, 158, 184);
	blueice[17][2] = CRGB(12, 153, 184);
	blueice[17][3] = CRGB(14, 150, 184);
	blueice[17][4] = CRGB(15, 146, 184);
	blueice[17][5] = CRGB(17, 142, 184);
	blueice[17][6] = CRGB(19, 138, 184);
	blueice[17][7] = CRGB(22, 133, 184);
	blueice[17][8] = CRGB(23, 130, 184);
	blueice[17][9] = CRGB(25, 126, 184);
	blueice[17][10] = CRGB(27, 121, 184);
	blueice[17][11] = CRGB(30, 117, 184);
	blueice[17][12] = CRGB(31, 114, 184);
	blueice[17][13] = CRGB(34, 109, 184);
	blueice[17][14] = CRGB(35, 106, 184);
	blueice[17][15] = CRGB(37, 102, 184);
	blueice[17][16] = CRGB(40, 98, 184);
	blueice[17][17] = CRGB(40, 95, 184);
	blueice[18][0] = CRGB(8, 170, 194);
	blueice[18][1] = CRGB(10, 166, 194);
	blueice[18][2] = CRGB(12, 162, 194);
	blueice[18][3] = CRGB(14, 158, 194);
	blueice[18][4] = CRGB(16, 154, 194);
	blueice[18][5] = CRGB(18, 150, 194);
	blueice[18][6] = CRGB(20, 146, 194);
	blueice[18][7] = CRGB(23, 141, 194);
	blueice[18][8] = CRGB(24, 137, 194);
	blueice[18][9] = CRGB(27, 133, 194);
	blueice[18][10] = CRGB(29, 128, 194);
	blueice[18][11] = CRGB(31, 124, 194);
	blueice[18][12] = CRGB(33, 120, 194);
	blueice[18][13] = CRGB(36, 116, 194);
	blueice[18][14] = CRGB(36, 112, 194);
	blueice[18][15] = CRGB(39, 107, 194);
	blueice[18][16] = CRGB(42, 103, 194);
	blueice[18][17] = CRGB(43, 100, 194);
	blueice[19][0] = CRGB(8, 179, 204);
	blueice[19][1] = CRGB(10, 175, 204);
	blueice[19][2] = CRGB(13, 170, 204);
	blueice[19][3] = CRGB(15, 166, 204);
	blueice[19][4] = CRGB(17, 162, 204);
	blueice[19][5] = CRGB(19, 158, 204);
	blueice[19][6] = CRGB(21, 154, 204);
	blueice[19][7] = CRGB(24, 148, 204);
	blueice[19][8] = CRGB(26, 144, 204);
	blueice[19][9] = CRGB(28, 140, 204);
	blueice[19][10] = CRGB(30, 134, 204);
	blueice[19][11] = CRGB(33, 130, 204);
	blueice[19][12] = CRGB(34, 126, 204);
	blueice[19][13] = CRGB(38, 122, 204);
	blueice[19][14] = CRGB(38, 118, 204);
	blueice[19][15] = CRGB(41, 113, 204);
	blueice[19][16] = CRGB(44, 109, 204);
	blueice[19][17] = CRGB(45, 106, 204);
	blueice[20][0] = CRGB(8, 188, 214);
	blueice[20][1] = CRGB(11, 184, 214);
	blueice[20][2] = CRGB(13, 179, 214);
	blueice[20][3] = CRGB(16, 175, 214);
	blueice[20][4] = CRGB(18, 171, 214);
	blueice[20][5] = CRGB(20, 165, 214);
	blueice[20][6] = CRGB(22, 161, 214);
	blueice[20][7] = CRGB(25, 155, 214);
	blueice[20][8] = CRGB(27, 151, 214);
	blueice[20][9] = CRGB(29, 147, 214);
	blueice[20][10] = CRGB(32, 141, 214);
	blueice[20][11] = CRGB(34, 137, 214);
	blueice[20][12] = CRGB(36, 133, 214);
	blueice[20][13] = CRGB(39, 128, 214);
	blueice[20][14] = CRGB(40, 123, 214);
	blueice[20][15] = CRGB(43, 118, 214);
	blueice[20][16] = CRGB(46, 114, 214);
	blueice[20][17] = CRGB(47, 111, 214);
	blueice[21][0] = CRGB(9, 197, 224);
	blueice[21][1] = CRGB(11, 193, 224);
	blueice[21][2] = CRGB(14, 187, 224);
	blueice[21][3] = CRGB(17, 183, 224);
	blueice[21][4] = CRGB(18, 179, 224);
	blueice[21][5] = CRGB(21, 173, 224);
	blueice[21][6] = CRGB(23, 169, 224);
	blueice[21][7] = CRGB(26, 163, 224);
	blueice[21][8] = CRGB(28, 158, 224);
	blueice[21][9] = CRGB(31, 154, 224);
	blueice[21][10] = CRGB(33, 148, 224);
	blueice[21][11] = CRGB(36, 143, 224);
	blueice[21][12] = CRGB(38, 139, 224);
	blueice[21][13] = CRGB(41, 134, 224);
	blueice[21][14] = CRGB(42, 129, 224);
	blueice[21][15] = CRGB(45, 124, 224);
	blueice[21][16] = CRGB(48, 120, 224);
	blueice[21][17] = CRGB(49, 116, 224);
	blueice[22][0] = CRGB(9, 206, 235);
	blueice[22][1] = CRGB(12, 201, 235);
	blueice[22][2] = CRGB(15, 196, 235);
	blueice[22][3] = CRGB(17, 191, 235);
	blueice[22][4] = CRGB(19, 187, 235);
	blueice[22][5] = CRGB(22, 181, 235);
	blueice[22][6] = CRGB(24, 177, 235);
	blueice[22][7] = CRGB(28, 170, 235);
	blueice[22][8] = CRGB(29, 166, 235);
	blueice[22][9] = CRGB(32, 161, 235);
	blueice[22][10] = CRGB(35, 155, 235);
	blueice[22][11] = CRGB(38, 150, 235);
	blueice[22][12] = CRGB(40, 145, 235);
	blueice[22][13] = CRGB(43, 140, 235);
	blueice[22][14] = CRGB(44, 135, 235);
	blueice[22][15] = CRGB(47, 130, 235);
	blueice[22][16] = CRGB(51, 125, 235);
	blueice[22][17] = CRGB(52, 121, 235);
	blueice[23][0] = CRGB(10, 215, 245);
	blueice[23][1] = CRGB(12, 210, 245);
	blueice[23][2] = CRGB(15, 204, 245);
	blueice[23][3] = CRGB(18, 200, 245);
	blueice[23][4] = CRGB(20, 195, 245);
	blueice[23][5] = CRGB(23, 189, 245);
	blueice[23][6] = CRGB(25, 184, 245);
	blueice[23][7] = CRGB(29, 178, 245);
	blueice[23][8] = CRGB(31, 173, 245);
	blueice[23][9] = CRGB(34, 168, 245);
	blueice[23][10] = CRGB(36, 161, 245);
	blueice[23][11] = CRGB(39, 156, 245);
	blueice[23][12] = CRGB(41, 152, 245);
	blueice[23][13] = CRGB(45, 146, 245);
	blueice[23][14] = CRGB(46, 141, 245);
	blueice[23][15] = CRGB(49, 135, 245);
	blueice[23][16] = CRGB(53, 131, 245);
	blueice[23][17] = CRGB(54, 127, 245);
	blueice[24][0] = CRGB(10, 224, 255);
	blueice[24][1] = CRGB(13, 219, 255);
	blueice[24][2] = CRGB(16, 213, 255);
	blueice[24][3] = CRGB(19, 208, 255);
	blueice[24][4] = CRGB(21, 203, 255);
	blueice[24][5] = CRGB(24, 197, 255);
	blueice[24][6] = CRGB(26, 192, 255);
	blueice[24][7] = CRGB(30, 185, 255);
	blueice[24][8] = CRGB(32, 180, 255);
	blueice[24][9] = CRGB(35, 175, 255);
	blueice[24][10] = CRGB(38, 168, 255);
	blueice[24][11] = CRGB(41, 163, 255);
	blueice[24][12] = CRGB(43, 158, 255);
	blueice[24][13] = CRGB(47, 152, 255);
	blueice[24][14] = CRGB(48, 147, 255);
	blueice[24][15] = CRGB(51, 141, 255);
	blueice[24][16] = CRGB(55, 136, 255);
	blueice[24][17] = CRGB(56, 132, 255);
	length[1] = 18;
	numframes[1] = 25;
	length[3] = 4;
	numframes[3] = 8;
	rate[1] = 1;
#pragma endregion BLUE_ICE



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
			effShapeSize = length[shapeBuffer[currentShape].baseShape];
			endPixel = shapeBuffer[currentShape].topPointLocation - (length[shapeBuffer[currentShape].baseShape] - 1);// -shapetail[shapeBuffer[currentShape].baseShape][shapeBuffer[currentShape].currentFrame];
			if (STRIPLEN - endPixel < length[shapeBuffer[currentShape].baseShape])
				effShapeSize = STRIPLEN - endPixel;
			if (shapeBuffer[currentShape].baseShape == 0) {
				memcpy(&strip[shapeBuffer[currentShape].stripNum][endPixel],
					purplerain[shapeBuffer[currentShape].currentFrame],
					effShapeSize * SIZEOFCRGB);
			}
			else {
				memcpy(&strip[shapeBuffer[currentShape].stripNum][endPixel],
					blueice[shapeBuffer[currentShape].currentFrame],
					effShapeSize * SIZEOFCRGB);
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
				if (shapeBuffer[currentShape].upwardsDirection && shapeBuffer[currentShape].currentFrame >= numframes[shapeBuffer[currentShape].baseShape] - 2) {
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
				if (!(frameRateCounter % rate[shapeBuffer[currentShape].baseShape]))
					shapeBuffer[currentShape].topPointLocation++;
				if (shapeBuffer[currentShape].topPointLocation - (length[shapeBuffer[currentShape].baseShape] - 1) >= STRIPLEN - 1) {
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
		shapeType = random(0, 2);
		shapeBufferTop = (shapeBufferTop + 1) % SIZESHAPEBUFFER;
		shapeBuffer[shapeBufferTop].newShape(shapeType,
			0, //TEMP shape variant, compute it somehow
			0, //TEMP starter depth, compute it somehow
			0, //random(0, STRIPLEN - 1), //TEMP top of peak location, compute it somehow
			1); //TEMPforward direction, compute it somehow
	}
	//}
}
