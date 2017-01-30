//This script takes 2 inputs from each multiplexer
//Κώδικας που λειτουργεί με 2 πολυπλέκτες και είσοδο που δίνεται μόνο στα 2 C0 και C1. Στο D port S0-->D7..S3-->D4 , Στο B port S0-->D13..S3-->D10
#define FANS 2

unsigned int passes = 0;
unsigned long first = 0; //variable for the calculation of dt
unsigned long last = 0;  //variable for the calculation of dt

unsigned long Timer = 0; //variable for the pseudo delay, tha holds tha value of the millis() in each iteration
int index = 0; //variable to 
byte controlPinsD[] = {B00000000, B10000000}; //D mux
byte controlPinsB[] = {B00000000, B10000000}; //B mux

float muxValues[] = {0,0,};//0};
bool flag = false; // variable to control which multiplexer is used

float RPM=0;
void blade_Pass()
{
  passes++;
  if (passes == 1){
    first = micros();
  }
  else if (passes > 1){
    last = micros();
  }
}//blade_Pass()

void setPinD(int outputPin)
// function to select pin on 74HC4067
{
  PORTD = controlPinsD[outputPin];
} //setPinD()

void setPinB(int outputPin)
// function to select pin on 74HC4067
{
  PORTB = controlPinsB[outputPin];
} //setPinD()

void setup()
{
  attachInterrupt(0,blade_Pass,FALLING); // Starting with port D (mux D)
  Serial.begin(9600);
  DDRD = B11110000; // 0 = input, 1 = output 
  DDRB = B11110000; // pins 8-13, 0 = input, 1 = output
  setPinD(index);
}// setup()

void loop(){
    //delay(1000);
    
    if (passes > 1)
    {
      float passesPerSecond = (float)passes / ((float)last - (float)first) * 1000.0 * 1000.0;
      muxValues[index] = passesPerSecond * 30.0;// numBlades;
      // RPM = passesPerSecond * 30.0;
      passes = 0;   
      if(millis()-Timer >=1000) // This is a pseudo delay. This is used because of the usage of interrupt, we do not want to disturb the process
      {
       Timer = millis();
       Serial.println((int)muxValues[index]);
       index++;
       Serial.println(index);
       if(flag)
       {
        setPinB(index);
       }
       else
       {
        setPinD(index);
       }
       if(index>1)
       {
        index = 0;
        flag = !flag; // to alternate the control of which mux is used
        if(flag) setPinB(index); // if true, use port B
        else setPinD(index);     // else use port D
       }     
      }//if
    }//if
  if(flag) //if true, use mux B
  {
    detachInterrupt(0);
    attachInterrupt(1,blade_Pass,FALLING);
  }
  else //else use mux D
  {
    detachInterrupt(1);
    attachInterrupt(0,blade_Pass,FALLING);
  }
  
} //loop
