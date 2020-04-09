#include "main.h"

// 18:1 -> Green cartridge
// 36:1 -> Red cartridge
// 6:1 -> Blue

//Define inertial
pros::Imu inertial(8);

//Define motors
pros::Motor leftFront (1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftBack (2, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightFront(9, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightBack (10, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

//Variable and Constants
int TICS_PER_REVOLUTION = 360;
double WHEEL_DIAMETER = 4;
double pi = 3.14159;

double CORRECTION_FACTOR = 0.8;
int THRESHHOLD = 5;

PIDController movePID(0.5, 30);
PIDController turnPID(2.5, 30);

void right(int speed) {
  rightFront.move(speed);
  rightBack.move(speed);
}

void left(int speed) {
  leftFront.move(speed);
  leftBack.move(speed);
}

void wait(int time) {
  //milliseconds
  pros::delay(time);
}

void timedDrive(int time, int speed) {
  right(speed);
  left(speed);
  wait(time);
  right(0);
  left(0);
}

void brake() {
  rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void coast() {
  rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

//Drive bAse autonomous functions
void moveForward(int inches) {

  rightFront.tare_position();
  leftFront.tare_position();

  int time = 0;

  double target = TICS_PER_REVOLUTION * (inches / (WHEEL_DIAMETER * pi));

  while(time < 50) {

    int rightFrontPosition = rightFront.get_position();
    int leftFrontPosition = leftFront.get_position();

    int PIDSpeed = movePID.getSpeedToMotor(target, rightFront.get_position());

    if (rightFrontPosition - leftFrontPosition <= -THRESHHOLD) {
      right(PIDSpeed);
      left(PIDSpeed * CORRECTION_FACTOR);
    }
    else if (leftFrontPosition - rightFrontPosition <= -THRESHHOLD) {
      right(PIDSpeed * CORRECTION_FACTOR);
      left(PIDSpeed);
    }
    else {
      right(PIDSpeed);
      left(PIDSpeed);
    }

    if(fabs(movePID.getError()) < 1) {
      time++; //Increment by one
      wait(2);
    }

  }
  left(0);
  right(0);

}

void moveBackward(int inches) {

  rightFront.tare_position();

  int time = 0;

  double target = TICS_PER_REVOLUTION * (inches / (WHEEL_DIAMETER * pi));

  while(time < 50) {

    int rightFrontPosition = rightFront.get_position();
    int leftFrontPosition = leftFront.get_position();

    int PIDSpeed = movePID.getSpeedToMotor(target, rightFront.get_position());

    if (rightFrontPosition - leftFrontPosition <= -THRESHHOLD) {
      right(-PIDSpeed);
      left(-PIDSpeed * CORRECTION_FACTOR);
    }
    else if (leftFrontPosition - rightFrontPosition <= -THRESHHOLD) {
      right(-PIDSpeed * CORRECTION_FACTOR);
      left(-PIDSpeed);
    }
    else {
      right(-PIDSpeed);
      left(-PIDSpeed);
    }

    if(fabs(movePID.getError()) < 1) {
      time++; //Increment by one
      wait(2);
    }

  }
  left(0);
  right(0);

}

//turn for degrees
void turn(int degrees) {

  int time = 0;

  while(time < 50) {

    left(turnPID.getSpeedToMotor(degrees, inertial.get_rotation()));
    right(-turnPID.getSpeedToMotor(degrees, inertial.get_rotation()));

    if(fabs(turnPID.getError()) < 1) {
      time++; //Increment by one
      wait(2);
    }
  }
  right(0);
  left(0);
}


//Drive OP control
void driveOP() {

    rightFront.move(master.get_analog(ANALOG_RIGHT_Y));
    rightBack.move(master.get_analog(ANALOG_RIGHT_Y));
    leftFront.move(master.get_analog(ANALOG_LEFT_Y));
    leftBack.move(master.get_analog(ANALOG_LEFT_Y));
}
