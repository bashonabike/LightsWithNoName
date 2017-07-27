#define PIN1 3
#define PIN2 6
#define PIN3 9

#define NUMSTRIPS 1
#define STRIPLEN 300
#define SIZEOFCRGB 3

#define SIZESHAPEBUFFER 20//100

//////////TEMP/////////////
#define TEMPSIZESHAPE 6
#define TEMPNUMFRAMES 14 //29
#define A 3// 1.4
#define B 3.2 //7
#define C 4 //160
#define formula(c, i) (A*c - (7 * (TEMPNUMFRAMES - i) - C)) 

#define FADEIMPEDEMENT 6
#define SPEEDIMPEDEMENT 3

#define MAXFAKEOUTRATE 2
//////////TEMP/////////////

#define PING_RATE 10000 //1000 //us
