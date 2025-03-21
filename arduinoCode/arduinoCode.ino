int RPWM_1 = 6;
int LPWM_1 = 5;
int RPWM_2 = 10;
int LPWM_2 = 9;


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
  if (direction == 1) {
    analogWrite(RPWM_1, 255);
    analogWrite(LPWM_1, 0);
    analogWrite(RPWM_2, 255);
    analogWrite(LPWM_2, 0);
    Serial.println('F');
  }
  // Para trás (B)
  else if (direction == 2){
    analogWrite(LPWM_2, 255);
    analogWrite(LPWM_1, 255);
    analogWrite(RPWM_1, 0);
    analogWrite(RPWM_2, 0);
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
      delay(700);  
      motorStop();
      break;
    case 'B':  // Movimento para trás
      moveMotors(2);
      delay(700);  
      motorStop();
      break;

    case 'N':
      motorStop();
      break;
  }
  delay(100);
  Serial.flush();
}
