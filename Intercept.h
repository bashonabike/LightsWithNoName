#pragma once
#ifndef Intercept_H
#define Intercept_H

class Intercept {
public:
	unsigned char interceptFrame;
	unsigned char interceptingShape;
	bool fired;

	Intercept();
	Intercept(unsigned char newInterceptFrame,
		unsigned char newInterceptingShape);
	void newIntercept(unsigned char newInterceptFrame,
		unsigned char newInterceptingShape);
	void deleteIntercept();
};
#endif
