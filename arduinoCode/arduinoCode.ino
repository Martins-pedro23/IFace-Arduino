 #include "Ultrasonic.h" 

const int motorA1 = 4;
const int motorA2 = 5;
const int motorB1 = 6;
const int motorB2 = 7;

 Ultrasonic frontSensor(10,11); 

char state;

void stopMovement(){
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorA1, LOW);
  digitalWrite(motorB2, LOW);
}

void motorController(int motor1, int motor2, int motor3, int motor4) {
  digitalWrite(motorA2, motor2);
  digitalWrite(motorB1, motor3);
  digitalWrite(motorA1, motor1);
  digitalWrite(motorB2, motor4);
}


float readFrontSensor() {
  long microsec = frontSensor.timing();
  return frontSensor.convert(microsec, Ultrasonic::CM);
}



void setup() {
  Serial.begin(9600);
  Serial.flush();
  Serial.println("Serial connection stablished");
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
}

void loop() {
  uint8_t byteFromSerial = Serial.read();
  uint8_t buff[100] = {byteFromSerial};
  String state = (char*)buff;

  switch (state.charAt(0)) {
    case 'L':
      motorController(HIGH, LOW, LOW, HIGH);
      delay(100);
      stopMovement();
      break;
    case 'R':
      motorController(LOW, HIGH, HIGH, LOW);
      delay(100);
      stopMovement();
      break;
    case 'F':
      if(readFrontSensor() > 10){
        Serial.println(readFrontSensor());
        motorController(HIGH, LOW, HIGH, LOW);
        delay(150);
        stopMovement();
      };
      break;
    case 'B':
      motorController(LOW, HIGH, LOW, HIGH);
      delay(150);
      stopMovement();
      break;
    case 'S':
      stopMovement();
      break;
  }

  Serial.flush();
};


