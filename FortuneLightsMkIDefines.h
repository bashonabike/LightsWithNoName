#define PIN1 3
#define PIN2 6
#define PIN3 9

#define NUMSTRIPS 1
#define STRIPLEN 300
#define SIZEOFCRGB 4

#define SIZESHAPEBUFFER 50//100

//////////TEMP/////////////
#define TEMPSIZESHAPE 10
#define TEMPNUMFRAMES 29
#define A 1.4
#define B 7
#define C 160
#define formula(c, i) (A*c - (7 * (TEMPNUMFRAMES - i) - C)) 
//////////TEMP/////////////

#define PING_RATE 1000 //us
