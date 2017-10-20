int PWM1 = 6;// this is the PWM pin for the motor for how much we move it to correct for its error
int InA1 = 7;//these pins are to control the direction of the motor (clockwise/counter-clockwise)
int InB1 = 3;

double setpoint = 100;//I am setting it to move through 100 degrees
double Kp = 0.32;// you can set these constants however you like depending on trial & error
double Ki = 0.1;
double Kd = 0.3;
double count = 0; //set the counts of the encoder
double currentangle = 0;//set the angles
boolean A,B;
byte state, statep;
float last_error = 0;
float error = 0;
float changeError = 0;
float totalError = 0;
float pidTerm = 0;
float pidTerm_scaled = 0;// if the total gain we get is not in the PWM range we scale it down so that it's not bigger than |255|


void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);//encoder pins
  pinMode(3, INPUT);
  attachInterrupt(digitalPinToInterrupt(encodPinA1),getFeedback,CHANGE);//interrupt pins for encoder 
  pinMode(PWM1, OUTPUT);
  pinMode(InA1, OUTPUT);
  pinMode(InB1, OUTPUT);

}

void loop(){
  
  PIDcalculation();// find PID value
  
  if (currentangle < setpoint) {
    digitalWrite(InA1, LOW);// Forward motion
    digitalWrite(InB1, HIGH);
  } else {
    digitalWrite(InA1, HIGH);//Reverse motion
    digitalWrite(InB1, LOW);
  }

  analogWrite(PWM1, pidTerm_scaled);
  delay(100);
}

void PIDcalculation(){
  currentangle = count;//count to angle conversion 
  error = setpoint - currentangle;  
  changeError = error - last_error; // derivative term
  totalError += error; //accumalate errors to find integral term
  pidTerm = (Kp * error) + (Ki * totalError) + (Kd * changeError);//total gain
  pidTerm = constrain(pidTerm, -255, 255);//constraining to appropriate value
  pidTerm_scaled = abs(pidTerm);//make sure it's a positive value
  last_error = error;
}
  
void getFeedback() //these functions are for finding the encoder counts
{
  A = digitalRead(encodPinA1);
  B = digitalRead(encodPinB1);

  if (((A==HIGH)&&(B==HIGH)) || ((A==LOW)&&(B==LOW))) state = 1;
  else state = 0;
  
  if (state){
    count++;
  }
  else count--;
}
