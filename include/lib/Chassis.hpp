#pragma once

#include "pros/motors.hpp"
#include <vector>

using namespace pros;
using namespace std;

class Chassis{
public:
  double ForwardCoefficient = 1, TurningCoefficient = 1;
  int MaxSpeed = 127;
  bool IsReversed = false;
  int CurrentSpeed, CurrentYaw;
  vector<Motor> LeftMotors, RightMotors;

  Chassis(const vector<Motor> left, const vector<Motor> right, const int &maxSpeed);
  void Drive(const int &forward, const int &yaw);
  void Stop();
  void SetMotorLeft(const int &speed);
  void SetMotorRight(const int &speed);

private:
  double _maxSpeed;
};
