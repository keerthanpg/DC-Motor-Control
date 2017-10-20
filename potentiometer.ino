int potpin = A0;   // select the input pin for the potentiometer
int inpin0 = 2;
int reading1=0;
int state_val=0;   // the current reading from the input pin
int previous1 = LOW;    // the previous reading from the input pin
long time = 0;         // the last time output pin was toggled
long debounce = 200; 
int pwmpin=6;
int val=0;
int bri;
void setup() {
  //state1 set up
  analogReference(DEFAULT);
  pinMode(pwmpin,OUTPUT);    
  Serial.begin(9600);
}

void loop() 
{
  
  reading1 = digitalRead(inpin0);
  //Serial.println(reading1);
  if(reading1 != previous1)
  {
    if (reading1 == HIGH)
    {
      if(state_val==1)
        state_val=0;      
      else
        state_val=1;
    }      
    delay(50);  
  }
  previous1=reading1;  
  if (state_val==1)
  {
  potentiometer();
  }
  else
  {
      
  }
}

void potentiometer()
{
  //Serial.println("blah");
  val=analogRead(potpin);
  //Serial.println(val);
  bri=map(val , 0 , 1023 , 0, 255 );
  analogWrite(pwmpin,bri); 
  Serial.println(bri); 
}
