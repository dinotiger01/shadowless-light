// #include <Servo.h>
#include <ServoTimer2.h>
// rotary endoder
#define rot_clk 2
#define rot_dt 3
#define rot_sw 4
// each color brighness
int countW = 0;
int countR = 0;
int countG = 0;
int countB = 0;
int servAng = 1500;
// rot stuff
int current;
int last;
int type = 0;

int vPin = 5;
int wPin = 6;
int rPin = 9;
int gPin = 10;
int bPin = 11;

int indB = A3;
int indG = A4;
int indR = A5;

unsigned long lastServoPulse = 0;
unsigned long buttonDebounceTimer = 0;

int servoPin = 7;

void setup(){
  pinMode(wPin, OUTPUT);
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
  pinMode(vPin, OUTPUT);
  pinMode(indB, OUTPUT);
  pinMode(indG, OUTPUT);
  pinMode(indR, OUTPUT);
  pinMode(servoPin, OUTPUT);
  

  pinMode(rot_clk, INPUT_PULLUP);
  pinMode(rot_dt, INPUT_PULLUP);
  pinMode(rot_sw, INPUT_PULLUP);

  Serial.begin(9600);

  last = digitalRead(rot_clk);

  analogWrite(indR, 255);
  analogWrite(indG, 255);
  analogWrite(indB, 255);
}

void loop(){
  if (millis() - lastServoPulse >= 20) {
    digitalWrite(servoPin, HIGH);
    delayMicroseconds(servAng); // Precise servo pulse length
    digitalWrite(servoPin, LOW);
    lastServoPulse = millis();
  }
  current = digitalRead(rot_clk);
  if(current != last && current == LOW){
    if(digitalRead(rot_dt) != current){
      if(type == 0 && countW < 255){
        countW += 5;
      }else if(type == 1 && countR < 255){
        countR += 5;
        Serial.println(countR);
      }else if(type == 2 && countG < 255){
        countG += 5;
      }else if(type == 3 && countB < 255){
        countB += 5;
      }else if(type == 4 && servAng < 2250){
        servAng += 5;
      }
      //clockwise
    }else{
      //counter clockwise
      if(type == 0 && countW > 0){
        countW -= 5;
      }else if(type == 1 && countR > 0){
        countR -= 5;
        Serial.println(countR);
      }else if(type == 2 && countG > 0){
        countG -= 5;
      }else if(type == 3 && countB > 0){
        countB -= 5;
      }else if(type == 4 && servAng > 750){
        servAng -= 5;
      }
    }
    analogWrite(wPin, countW);
    analogWrite(rPin, countR);
    analogWrite(gPin, countG);
    analogWrite(bPin, countB);

    // myServ.write(servAng);
    Serial.println(servAng);
  }
  last = current;


  if(digitalRead(rot_sw) == LOW && (millis() - buttonDebounceTimer > 300)){
    buttonDebounceTimer = millis();
    type++;
    if(type == 6){ 
      type = 0;
    }
    
    if(type == 0){
      analogWrite(vPin, 0);
      digitalWrite(indR, HIGH); digitalWrite(indG, HIGH); digitalWrite(indB, HIGH);
    }else if(type == 1){
      analogWrite(vPin, 0);
      digitalWrite(indR, HIGH); digitalWrite(indG, LOW); digitalWrite(indB, LOW);
    }else if(type == 2){
      analogWrite(vPin, 0);
      digitalWrite(indR, LOW); digitalWrite(indG, HIGH); digitalWrite(indB, LOW);
    }else if(type == 3){
      analogWrite(vPin, 0);
      digitalWrite(indR, LOW); digitalWrite(indG, LOW); digitalWrite(indB, HIGH);
    }else if(type == 4){
      analogWrite(vPin, 0);
      digitalWrite(indR, HIGH); digitalWrite(indG, HIGH); digitalWrite(indB, LOW);
    }else if(type == 5){
      analogWrite(vPin, 255);
      digitalWrite(indR, HIGH); digitalWrite(indG, LOW); digitalWrite(indB, HIGH);
    }
  }
}
