#include <Servo.h>

Servo servo_base;
Servo servo_1;
Servo servo_2;
Servo servo_3;

int pos = 0;

void move_servo(int a0,int a1 ,int a2,int a3){
  servo_base.write(a0);
  delay(100);
  servo_1.write(a1);
  delay(100);
  servo_2.write(60);
  delay(100);
  servo_3.write(a3);
  delay(100);
}
void setup() {
  servo_base.attach(2);
  servo_1.attach(3);
  servo_2.attach(4);
  servo_3.attach(5);
}

void loop() {
  move_servo(90,90,90,90);
}
