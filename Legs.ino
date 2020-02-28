#include <Servo.h>
#include <math.h>

// Left Front Pins
#define LFBodyServoPin 22
#define LFLegServoPin 24
#define LFKneeServoPin 26

// Right Front Pins
#define RFBodyServoPin 5
#define RFLegServoPin 4
#define RFKneeServoPin 3

// Left Back Pins
#define LBBodyServoPin 8
#define LBLegServoPin 7
#define LBKneeServoPin 6

// Right Back Pins
#define RBBodyServoPin 11
#define RBLegServoPin 10
#define RBKneeServoPin 9

#define LegsNum 4
#define ServosPerLeg 3

Servo LFBodyServo;
Servo LFLegServo;
Servo LFKneeServo;

Servo RFBodyServo;
Servo RFLegServo;
Servo RFKneeServo;

Servo LBBodyServo;
Servo LBLegServo;
Servo LBKneeServo;

Servo RBBodyServo;
Servo RBLegServo;
Servo RBKneeServo;

Servo servos[LegsNum][ServosPerLeg] = {
  {LFBodyServo,LFLegServo,LFKneeServo},
  {RFBodyServo,RFLegServo,RFKneeServo},
  {LBBodyServo,LBLegServo,LBKneeServo},
  {RBBodyServo,RBLegServo,RBKneeServo}};


const float flengthBodyLeg; // todo: measure length of body-leg
const float flengthLegKnee; // todo: measure length of leg-knee
const float fnormalAngleBody;
const float fnormalAngleLeg; // angle between leg and normal to body for each leg
const float fnormalAngleKnee; // angle between leg and knee for each leg
const float fnormalHeight; // = flengthBodyLeg*cos(fnormalAngleBody) + flengthLegKnee*cos(fnormalAngleKnee - fnormalAngleLeg); measure height from body to ground in normal position

/*
 * k - coefficient to normal height (how far from normal value)
*/
void standingMODE(int k) {
  double dnum = pow(flengthBodyLeg, 2) - pow(flengthLegKnee, 2) + pow(k*(fnormalHeight), 2);
  double ddenom = 2*k*fnormalHeight*flengthBodyLeg;
  double tmp = dnum/ddenom;
  double dbetaLeg = acos(tmp);
  double dbetaKnee = acos((k*fnormalHeight - flengthBodyLeg*tmp)/flengthLegKnee) + dbetaLeg;

  // body servos leave untouched
  for (int i = 0; i < LegsNum; i++) {
    servos[i][1].write(dbetaLeg);
    servos[i][2].write(dbetaKnee);
  }
}

void setup() {
  
  // Left Front
  LFBodyServo.attach(LFBodyServoPin);
  LFLegServo.attach(LFLegServoPin);
  LFKneeServo.attach(LFKneeServoPin);

  // Right Front
  RFBodyServo.attach(RFBodyServoPin);
  RFLegServo.attach(RFLegServoPin);
  RFKneeServo.attach(RFKneeServoPin);
  
  // Left Back
  LBBodyServo.attach(LBBodyServoPin);
  LBLegServo.attach(LBLegServoPin);
  LBKneeServo.attach(LBKneeServoPin);

  // Right Back
  RBBodyServo.attach(RBBodyServoPin);
  RBLegServo.attach(RBLegServoPin);
  RBKneeServo.attach(RBKneeServoPin);

  // Left Front
  LFBodyServo.write(78);
  LFLegServo.write(90-20); 
  LFKneeServo.write(30-15);

  // Right Front
  RFBodyServo.write(123);
  RFLegServo.write(65); // 40 - паралелльно (больше задевет провод)
  RFKneeServo.write(145);

  // Left Back
  LBBodyServo.write(40);
  LBLegServo.write(105-30);
  LBKneeServo.write(35);

  // Right Back
  RBBodyServo.write(132);
  RBLegServo.write(95+22);
  RBKneeServo.write(120);

  
}

void loop() {
  
}
