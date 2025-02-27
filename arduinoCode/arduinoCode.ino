int RPWM_1 = 6;
int LPWM_1 = 5;
int RPWM_2 = 9;
int LPWM_2 = 10;

int state_RPWM_1 = 0;
int state_LPWM_1 = 0;
int state_RPWM_2 = 0;
int state_LPWM_2 = 0;

void setup() {
  Serial.begin(9600);
  Serial.flush();
  Serial.println("Serial connection stabilished");
  
  pinMode(RPWM_1, OUTPUT);
  pinMode(LPWM_1, OUTPUT);
  
  pinMode(RPWM_2, OUTPUT);
  pinMode(LPWM_2, OUTPUT);

}

void motorStop(){
  analogWrite(RPWM_1, 0);
  analogWrite(LPWM_1, 0);
  analogWrite(RPWM_2, 0);
  analogWrite(LPWM_2, 0);
}


void loop() {
  uint8_t byteFromSerial = Serial.read();
  uint8_t buff[100] = {byteFromSerial};
  String state = (char*)buff;

    switch (state.charAt(0)){
      case 'F':
      if(state_RPWM_1 != 1 && state_RPWM_2 != 1){
        analogWrite(RPWM_2, 90);
        analogWrite(RPWM_1, 90);
        analogWrite(LPWM_1, 0);
        analogWrite(LPWM_2, 0);
        state_RPWM_1 = 1;
        state_RPWM_2 = 1;
        state_LPWM_1 = 0;
        state_LPWM_2 = 0;
        Serial.println('F');
      }else if (state_RPWM_1 != 1 && state_RPWM_2 == 1){
        analogWrite(RPWM_1, 90);
        analogWrite(LPWM_1, 0);
        analogWrite(LPWM_2, 0);
        state_RPWM_1 = 1;
        state_RPWM_2 = 1;
        state_LPWM_1 = 0;
        state_LPWM_2 = 0;
        Serial.println('F');
      }else if (state_RPWM_1 == 1 && state_RPWM_2 != 1){
        analogWrite(RPWM_2, 90);
        analogWrite(LPWM_1, 0);
        analogWrite(LPWM_2, 0);
        state_RPWM_1 = 1;
        state_RPWM_2 = 1;
        state_LPWM_1 = 0;
        state_LPWM_2 = 0;
        Serial.println('F');
      }
      delay(1000);
    break;

    case 'B':
      if(state_LPWM_1 != 1 && state_LPWM_2 != 1){
        analogWrite(LPWM_2, 90);
        analogWrite(LPWM_1, 90);
        analogWrite(RPWM_1, 0);
        analogWrite(RPWM_2, 0);
        state_RPWM_1 = 0;
        state_RPWM_2 = 0;
        state_LPWM_1 = 1;
        state_LPWM_2 = 1;
        Serial.println('B');
      }else if (state_LPWM_1 != 1 && state_LPWM_2 == 1){
        analogWrite(LPWM_1, 90);
        analogWrite(RPWM_1, 0);
        analogWrite(RPWM_2, 0);
        state_RPWM_1 = 0;
        state_RPWM_2 = 0;
        state_LPWM_1 = 1;
        state_LPWM_2 = 1;
        Serial.println('B');
      }else if (state_LPWM_1 == 1 && state_LPWM_2 != 1){
        analogWrite(LPWM_2, 90);
        analogWrite(RPWM_1, 0);
        analogWrite(RPWM_2, 0);
        state_RPWM_1 = 0;
        state_RPWM_2 = 0;
        state_LPWM_1 = 1;
        state_LPWM_2 = 1;
        Serial.println('B');
      }
      delay(1000);

    break;
  }
  
  motorStop();
  delay(1000);
  Serial.flush();
}
