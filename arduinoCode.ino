const int motorA1 = 4;
const int motorA2 = 5;
const int motorB1 = 6;
const int motorB2 = 7;

char state;

void stopMovement(){
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorA1, LOW);
  digitalWrite(motorB2, LOW);
}

void motorControler(int motor1, int motor2, int motor3, int motor4, String state){
  digitalWrite(motorA2, motor2);
  digitalWrite(motorB1, motor3);
  digitalWrite(motorA1, motor1);
  digitalWrite(motorB2, motor4);
  Serial.println(state);
};


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

  if (state.equalsIgnoreCase("L")){
    motorControler(HIGH, LOW, LOW, HIGH, state);
    delay(100);
    stopMovement(); 
    
  }else if (state.equalsIgnoreCase("R")){
    motorControler(LOW, HIGH, HIGH, LOW, state);
    delay(100);
    stopMovement(); 
    
  }else if (state.equalsIgnoreCase("F")){
    motorControler(HIGH, LOW, HIGH, LOW, state);
    delay(150);
    stopMovement(); 

  }else if (state.equalsIgnoreCase("B")){
    motorControler(LOW, HIGH, LOW, HIGH, state);
    delay(150);
    stopMovement(); 

  }
  else if (state.equalsIgnoreCase("S")){
    stopMovement();    
  };
  Serial.flush();
}


