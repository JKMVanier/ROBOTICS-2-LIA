#ifndef MOTOR_H
#define MOTOR_H

class Motor {
public:
  void RIGHT();
  void FRR();
  void FFR();
  void FWD();
  void FFL();
  void FLL();
  void LEFT();
  void stop();
  void back();
  void init();

private:
  void move(bool a, int b, bool c, int d);
};

#endif // MOTOR_H
