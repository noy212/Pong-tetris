#include "BombBall.h"

bool BombBall::changeState()
{
	if (numIteration >= maxIter)
		return true;
	return false;
}
