#pragma once
#include "BallBehavior.h"


using namespace std;

class BombBall : public BallBehavior {
	int numIteration;
	enum {maxIter = 4};
public:
	void setIteration() {
		numIteration += 1;
	}
	void resetIteration() {
		numIteration = 0;
	}
	bool changeState();

};