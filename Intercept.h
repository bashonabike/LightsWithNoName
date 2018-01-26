#pragma once
#ifndef Intercept_H
#define Intercept_H

class Intercept {
public:
	char interceptFrame;
	char interceptingShape;
	bool fired;

	Intercept();
	Intercept(char newInterceptFrame,
		char newInterceptingShape);
	void newIntercept(char newInterceptFrame,
		char newInterceptingShape);
	void deleteIntercept();
};
#endif
