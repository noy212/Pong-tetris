#pragma once
#include "BallBehavior.h"

using namespace std;

class BecomingBomb: public BallBehavior {
	int numIteration = 0;
	enum { maxIter = 8 };

public:
	void resetIteration() {
		numIteration = 0;
	}
	void setIteration() {
		numIteration += 1;
	}
	bool changeState() {
		if (numIteration >= maxIter)
				return true;
		return false;
	}
	const int& getIteration() {
		return numIteration;
	}

};