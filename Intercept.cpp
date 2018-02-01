#include "Intercept.h"
#include "FortuneLightsMkIDefines.h"

Intercept::Intercept() {
} //initial constructor

Intercept::Intercept(unsigned char newInterceptFrame,
	unsigned char newInterceptingShape) {
	newIntercept(newInterceptFrame, newInterceptingShape);
} //actual constructor

void Intercept::newIntercept(unsigned char newInterceptFrame,
	unsigned char newInterceptingShape) { // constructor code
	interceptFrame = newInterceptFrame;
	interceptingShape = newInterceptingShape;
	fired = false;
}

void Intercept::deleteIntercept() {
}