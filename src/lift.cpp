#include "main.h"

//Define Lift Motor
pros::Motor liftMotor(11, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);

pros::ADIPotentiometer pot('H');

PIDController liftPID(0.46, 5);

void liftBrake() {
  liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void lift(int speed) {
  liftMotor.move(speed);
}

//Auton
void moveLift(int target) {
  int time = 0;

  while(time < 50) {
    int PIDSpeed = -liftPID.getSpeedToMotor(target, pot.get_value());

    if(fabs(liftPID.getError()) < 10) {
      time++; //Increment by one
      wait(2);
    }

    lift(PIDSpeed);
  }
  lift(0);
  liftBrake();
}

//OP CONTROL
void liftOP() {

  liftBrake();

  if(master.get_digital(DIGITAL_L1)) {
    liftMotor.move_velocity(100);
  }
  else if(master.get_digital(DIGITAL_L2)) {
    liftMotor.move_velocity(-100);
  }
  else {
    liftMotor.move_velocity(0);
  }
}
