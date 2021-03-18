#pragma once


struct BallBehavior {
public:
	enum ballside { left, right, none };
protected:
	bool leftBombStatus = false;
	bool rightBombStatus = false;
	ballside player = none;
public:
	virtual ~BallBehavior() {}
	ballside getPlayerSide() {
		return player;
	}
	bool getLBombStatus() {
		return leftBombStatus;
	}
	bool getRBombStatus() {
		return rightBombStatus;
	}
	void setLBombStatus(const bool& status) {
		leftBombStatus = status;
	}
	void setRBombStatus(const bool& status) {
		rightBombStatus = status;
	}
	virtual void setIteration() = 0;
	virtual void resetIteration() = 0;
	virtual bool changeState() = 0;
};