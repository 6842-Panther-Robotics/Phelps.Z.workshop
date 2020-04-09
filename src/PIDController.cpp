#include "main.h"


PIDController::PIDController(double inKP, int inMinSpeed) {
  kP = inKP;
  minSpeed = inMinSpeed;
}

int PIDController::getSpeedToMotor(int target, int current) {

  error = target - current;

  int speed = error * kP;

  if(speed <= minSpeed && speed >= 0) {
    speed = minSpeed;
  }
  else if(speed <= minSpeed && speed <= 0) {
    speed = -minSpeed;
  }

  return speed;

}

double PIDController::getError() {
  return error;
}
