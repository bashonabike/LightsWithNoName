#include "Intercept.h"
#include "FortuneLightsMkIDefines.h"

Intercept::Intercept() {
} //initial constructor

Intercept::Intercept(char newInterceptFrame,
	char newInterceptingShape) {
	newIntercept(newInterceptFrame, newInterceptingShape);
} //actual constructor

void Intercept::newIntercept(char newInterceptFrame,
	char newInterceptingShape) { // constructor code
	interceptFrame = newInterceptFrame;
	interceptingShape = newInterceptingShape;
	fired = false;
}

void Intercept::deleteIntercept() {
}