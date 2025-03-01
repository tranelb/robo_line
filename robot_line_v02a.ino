//left motor
int ENL = 9;
int IN1 = 8;
int IN2 = 7;

//right motor
int ENR = 3;
int IN3 = 5;
int IN4 = 4;


//global vars
//Dark = 1 | White = 0
int leftIR = 6;
int rightIR = 12;

int  leftIRdata;
int  rightIRdata;

//LEDS
int redLED = 11;      //global var for red LED digital output pin
int greenLED = 10;      //global var for red LED digital output pin
int yellowLED = 2;      //global var for red LED digital output pin


int i = 0;

//bools for conditions
bool stop = true;
bool turn = true;
bool forwardDir = true;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(ENL, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENR, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(redLED, OUTPUT);      //Initialize red LED pin as OUTPUT
  pinMode(yellowLED, OUTPUT);      //Initialize red LED pin as OUTPUT
  pinMode(greenLED, OUTPUT);      //Initialize red LED pin as OUTPUT

  pinMode(leftIR, INPUT);
  pinMode(rightIR, INPUT);

  //leftIRdata = digitalRead(leftIR); //read the left IR 
  //rightIRdata = digitalRead(rightIR); //read the right IR 
  
  Serial.begin(9600);
  Serial.println("Intialization Complete!");
   
}

/*
void lineFollow(){
  //leftIRdata = digitalRead(leftIR); //read the left IR 
  //rightIRdata = digitalRead(rightIR); //read the right IR 
  if(leftIRdata == 1 && rightIRdata == 1){
    forward(235,185); 
    Serial.println("going forward");
  }
  else if(leftIRdata == 0 && rightIRdata == 1){
    turnRight(235,185);
    Serial.println("turning right"); 
  }
  else if(leftIRdata == 1 && rightIRdata == 0){
    turnLeft(235,185);
    Serial.println("turning left"); 
  }
}
*/
void lineFollow(){
  leftIRdata = digitalRead(leftIR); //read the left IR 
  rightIRdata = digitalRead(rightIR); //read the right IR 
  if(leftIRdata == rightIRdata){
    forward(235,185); 
    Serial.println("going forward");
  }
  else if(leftIRdata < rightIRdata){
    turnRight(235,185);
    Serial.println("turning right"); 
  }
  else if(leftIRdata > rightIRdata){
    turnLeft(235,185);
    Serial.println("turning left"); 
  }
  Serial.print("Left IR = ");
  Serial.print(leftIRdata);
  Serial.print(" | Right IR = ");
  Serial.println(rightIRdata);
  delay(1000);
}


void blinkBuiltinLED(int duration){  //method for blinking LED
  digitalWrite(LED_BUILTIN, HIGH);                //turns on specified pin
  delay(duration);                        //holds mode(on) for specified time
  digitalWrite(LED_BUILTIN, LOW);                 //turns off specified pin
  delay(duration);                        //holds mode(off) for specified time
}

void blinkAnyLED(int pin, int duration){  //method for blinking LED
  digitalWrite(pin, HIGH);                //turns on specified pin
  delay(duration);                        //holds mode(on) for specified time
  digitalWrite(pin, LOW);                 //turns off specified pin
  delay(duration);                        //holds mode(off) for specified time
}


//Congfigure motors enable or disabled
//Provide a True or False input parameter
void enableMotors(bool isEnabled){
  if(isEnabled){  //enable motors
    digitalWrite(ENL, HIGH);
    digitalWrite(ENR, HIGH);
  }
  else{  //disable motors
    digitalWrite(ENL, LOW);
    digitalWrite(ENR, LOW);
  }
}

//Drive the robot forward
void forward(int speedL, int speedR){

  enableMotors(true);
  //forwardDir = true;
  /*
  while(forwardDir && i !=1){
      blinkAnyLED(greenLED,1000);
  }
  */
  //1 1 0 Motor is on and turning forwards
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENL, speedL); //8-bit signal 0-255: 50% speed ~127

  //1 1 0 Motor is on and turning forwards
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW); 
  analogWrite(ENR, speedR); //8-bit signal 0-255: 50% speed ~127
  //delay(duration);
  //forwardDir = false;


}

void backward(int speedL, int speedR){
  enableMotors(true);
  //1 1 0 Motor is on and turning backwards
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENL, speedL); //8-bit signal 0-255: 50% speed ~127

  //1 1 0 Motor is on and turning backwards
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); 
  analogWrite(ENR, speedR); //8-bit signal 0-255: 50% speed ~127

}

void turnRight(int speedL, int speedR){
  enableMotors(true);
  //1 1 0 Motor is on and turning backwards
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENL, speedL); //8-bit signal 0-255: 50% speed ~127

  //1 1 0 Motor is on and turning backwards
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); 
  analogWrite(ENR, speedR); //8-bit signal 0-255: 50% speed ~127

}

void turnLeft(int speedL, int speedR){
  enableMotors(true);
  //turn = true;
  //1 1 0 Motor is on and turning backwards
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENL, speedL); //8-bit signal 0-255: 50% speed ~127

  //1 1 0 Motor is on and turning backwards
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENR, speedR); //8-bit signal 0-255: 50% speed ~127
  //turn = false;
  //delay(duration);


}

void stopMotors(){
  //1 0 0 Motor is stopped (brakes)
  //stop = true;
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  //1 0 0 Motor is stopped (brakes)
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW); 

  enableMotors(false);
  //stop = false;
}


void loop() {  //Original
  // 2nd draft main code here, to run repeatedly:
/*
  blinkAnyLED(redLED,1000);
  blinkAnyLED(yellowLED,500);
  blinkAnyLED(greenLED,1000);
  blinkAnyLED(LED_BUILTIN,1000);
*/
  
  lineFollow();

  /*
  while(i!=1){


    
    forward(235,185,775);  
    //delay(2250); //forward ~24in

    stopMotors();
    delay(5000);
    
      
    turnLeft(235,185);
    delay(270); //~90 degree turn
    stopMotors();
    delay(1000); // pause for 90 degree turn

    forward(235,185,775);
    stopMotors();
    delay(5000);
      
    turnLeft(235,185);
    delay(270); //~90 degree turn
    stopMotors();
    delay(1000); // pause for 90 degree turn

    forward(235,185,775);
    stopMotors();
    delay(5000);

    turnLeft(235,185);
    delay(270); //~90 degree turn
    stopMotors();
    delay(1000); // pause for 90 degree turn

    forward(235,185,775);
    stopMotors();
    delay(5000);

    stopMotors();
    i=1;

  }
  */
/*
  if(forwardDir){
    blinkAnyLED(greenLED,1000);
  }
  else if(stop){
    digitalWrite(redLED, HIGH);
  }
  else if(turn){
    blinkAnyLED(yellowLED,500);
  }
*/

}


/*
void loop() {  //straight line test
  //blinkBuiltinLED(1000);
    
  while(i!=1){
    
    forward(235,185,775);  
      
    stopMotors();
    i=1;
  }
  
}
*/

/*
void loop() { //turn test
  // 2nd draft main code here, to run repeatedly:
  //blinkBuiltinLED(1000);
    
  while(i!=1){
   
    //turnLeft(250,225);  //initial
    turnLeft(235,185);  
    delay(270); //~90 degree turn
    stopMotors();
    delay(1000); // pause for 90 degree turn

    stopMotors();
    i=1;
  }
  
}
*/


