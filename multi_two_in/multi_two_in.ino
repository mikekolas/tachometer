//This script takes 2 inputs from multiplexer
unsigned int passes = 0;
unsigned long first = 0; //variable for the calculation of dt
unsigned long last = 0;  //variable for the calculation of dt

unsigned long Timer = 0; //variable for the pseudo delay, tha holds tha value of the millis() in each iteration
int index = 0; //variable to 
byte controlPins[] = {B00000000, B00100000}; 
float muxValues[] = {0,0};

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

void setPin(int outputPin)
// function to select pin on 74HC4067
{
  PORTD = controlPins[outputPin];
} //setPin()

void setup()
{
  attachInterrupt(0,blade_Pass,FALLING);
  Serial.begin(9600);
  DDRD = B11110000; // 0 = input, 1 = output 
  setPin(index);
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
       Serial.print(index + 1);
       Serial.print("o - ");
       Serial.println((int)muxValues[index]);
       index++;
       if(index>1) index = 0;       
       setPin(index); // choose an input pin on the 74HC4067
      }//if
    }//if
  attachInterrupt(0,blade_Pass,FALLING);
} //loop
