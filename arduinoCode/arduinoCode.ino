int RPWM_1 = 6;
int LPWM_1 = 5;
int RPWM_2 = 10;
int LPWM_2 = 9;

int state_RPWM_1 = 0;
int state_LPWM_1 = 0;
int state_RPWM_2 = 0;
int state_LPWM_2 = 0;
int lastMovment = 0;

void setup() {
  Serial.begin(9600);
  Serial.flush();
  Serial.println("Serial connection stabilished");
  
  pinMode(RPWM_1, OUTPUT);
  pinMode(LPWM_1, OUTPUT);
  
  pinMode(RPWM_2, OUTPUT);
  pinMode(LPWM_2, OUTPUT);

}

void motorStop() {
  analogWrite(RPWM_1, 0);
  analogWrite(LPWM_1, 0);
  analogWrite(RPWM_2, 0);
  analogWrite(LPWM_2, 0);
}

void moveMotors(int direction) {
  // Para frente (F)
  if (direction == 1 && state_RPWM_1 != 1 && state_RPWM_2 != 1) {
    analogWrite(RPWM_1, 255);
    analogWrite(LPWM_1, 0);
    analogWrite(RPWM_2, 255);
    analogWrite(LPWM_2, 0);
    state_RPWM_1 = 1;
    state_RPWM_2 = 1;
    state_LPWM_1 = 0;
    state_LPWM_2 = 0;
    Serial.println('F');
  } else if (direction == 1 && state_RPWM_1 != 1 && state_RPWM_2 == 1){
    analogWrite(RPWM_1, 255);
    analogWrite(LPWM_1, 0);
    analogWrite(LPWM_2, 0);
    state_RPWM_1 = 1;
    state_RPWM_2 = 1;
    state_LPWM_1 = 0;
    state_LPWM_2 = 0;
    Serial.println('F');
  } else if (direction == 1 && state_RPWM_1 == 1 && state_RPWM_2 != 1){
    analogWrite(RPWM_2, 255);
    analogWrite(LPWM_1, 0);
    analogWrite(LPWM_2, 0);
    state_RPWM_1 = 1;
    state_RPWM_2 = 1;
    state_LPWM_1 = 0;
    state_LPWM_2 = 0;
    Serial.println('F');
  }
  // Para trás (B)
  else if (direction == 2 && state_LPWM_1 != 1 && state_LPWM_2 != 1){
    analogWrite(LPWM_2, 255);
    analogWrite(LPWM_1, 255);
    analogWrite(RPWM_1, 0);
    analogWrite(RPWM_2, 0);
    state_RPWM_1 = 0;
    state_RPWM_2 = 0;
    state_LPWM_1 = 1;
    state_LPWM_2 = 1;
    Serial.println('B');
  } else if (direction == 2 && state_LPWM_1 != 1 && state_LPWM_2 == 1){
    analogWrite(LPWM_1, 255);
    analogWrite(RPWM_1, 0);
    analogWrite(RPWM_2, 0);
    state_RPWM_1 = 0;
    state_RPWM_2 = 0;
    state_LPWM_1 = 1;
    state_LPWM_2 = 1;
    Serial.println('B');
  } else if (direction == 2 && state_LPWM_1 == 1 && state_LPWM_2 != 1){
    analogWrite(LPWM_2, 255);
    analogWrite(RPWM_1, 0);
    analogWrite(RPWM_2, 0);
    state_RPWM_1 = 0;
    state_RPWM_2 = 0;
    state_LPWM_1 = 1;
    state_LPWM_2 = 1;
    Serial.println('B');
  }
}


void loop() {
  uint8_t byteFromSerial = Serial.read();
  uint8_t buff[100] = {byteFromSerial};
  String state = (char*)buff;

  switch (state.charAt(0)){
    case 'F':  // Movimento para frente
      moveMotors(1);
      delay(1000);  // Move para frente
      motorStop();
      lastMovment = 1;
      break;
    case 'B':  // Movimento para trás
      moveMotors(2);
      delay(1000);  // Move para frente
      motorStop();
      lastMovment = 2;
      break;

    default:
      if(lastMovment == 1){
        moveMotors(2);
      } else if(lastMovment == 2) {
        moveMotors(1);
      }
      delay(1000);  // Move para frente
      motorStop();
      lastMovment = 0;
      state_RPWM_1 = 0;
      state_RPWM_2 = 0;
      state_LPWM_1 = 0;
      state_LPWM_2 = 0;
      break;
  }
  delay(1000);
  Serial.flush();
}
