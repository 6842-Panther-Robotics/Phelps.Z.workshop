
class PIDController {

  private:
    double kP; 
    int minSpeed;
    double error;

  public:
    PIDController(double inKP, int inMinSpeed);
    int getSpeedToMotor(int target, int current);
    double getError();

};
