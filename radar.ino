#include <Servo.h>

Servo servo_1; // servo controller (multiple can exist)

int trig = 9; // trig pin for HC-SR04
int echo = 10; // echo pin for HC-SR04
int servo_pin = 8; // PWM pin for servo control
int buzzer= 7;
int pos = 0;    // servo starting position
float duration, distance;
int red_light = 11;
int green_light = 12;
int blue_light = 13;

void setup() {
  Serial.begin(8818);
  Serial.println("Radar Start");
  servo_1.attach(servo_pin); // start servo control
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(red_light,OUTPUT);
  pinMode(green_light,OUTPUT);
  pinMode(blue_light,OUTPUT);
}

void loop() {
  for (pos = 0; pos <= 70; pos += 3) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo_1.write(pos); 
    // tell servo to go to position in variable 'pos'
     // delay to allow the servo to reach the desired position
    calculateDistance(pos);
    
  }

  for (pos = 70; pos >= 0; pos -= 3) { // goes from 180 degrees to 0 degrees
    servo_1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(50);
    calculateDistance(pos);
  }
}

int calculateDistance(int pos){ 

  tone(buzzer, 200);
  delay(100);
  noTone(buzzer);     // Stop sound...
   delay(100);
  
  digitalWrite(trig, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trig, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  if(distance<150){
      tone(buzzer, 2048);
      RGB_color(255,0,0);// Send 1KHz sound signal...
      delay(80);        // ...for 1 sec
      noTone(buzzer);     // Stop sound...
      delay(80);// ...for 1sec
      }else{
        RGB_color(0,255,0);}
      
  Serial.print(pos); // position of servo motor
  Serial.print(","); // comma separate variables
  Serial.println(distance);
  return distance;
}
void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  digitalWrite(red_light, red_light_value);
  digitalWrite(green_light, green_light_value);
  digitalWrite(blue_light, blue_light_value);
}

 
