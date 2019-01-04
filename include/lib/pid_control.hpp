#pragma once

class PidControl {
public:
	float Kp, Ki, Kd;
	float maxOutput = 127;

	void Pidinit(float kP, float kI, float kD);

	/*
	* return the output of a pid
	*
	* @param posTarget: target value
	* @param posCurrent: current value
	*/
	double PidProcess(int posTarget, int posCurrent);

	private:
		float nPowerOut;
		int nErr, nErr_last;
		int nSetPos, nActPos;
		float nIntegral;
		float nDiffer;
};
