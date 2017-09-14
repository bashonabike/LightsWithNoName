#define PIN1 3
#define PIN2 6
#define PIN3 9

#define NUMSTRIPS 1
#define STRIPLEN 300
#define SIZEOFCRGB 3

#define SIZESHAPEBUFFER 20
//100

//////////TEMP/////////////
#define TEMPSIZESHAPE 14
#define TEMPNUMFRAMES 30
#define A 1.8
#define B 0.35
#define C 8 
#define D 15
#define formula(p, f) (int)((-1)*A*(p - B*TEMPSIZESHAPE)*(p - B*TEMPSIZESHAPE) + C*f + D)
//f is the frame, p is the position

#define FADEIMPEDEMENT 6
#define SPEEDIMPEDEMENT 2

#define MAXFAKEOUTRATE .3
//////////TEMP/////////////

#define PING_RATE 500000
//1000 //us
