unsigned int passes = 0;
unsigned long first = 0;
unsigned long last = 0;

unsigned long Timer = 0;
int times = 0;
byte controlPins[] = {B00000000, B10000000,B01000000,
                  B11000000,
                  B00100000,
                  B10100000,
                  B01100000,
                  B11100000,
                  B00010000,
                  B10010000,
                  B01010000,
                  B11010000,
                  B00110000,
                  B10110000,
                  B01110000,
                  B11110000 }; 
                  
float muxValues[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

float RPM=0;
void blade_Pass(){
  passes++;
  if (passes == 1){
    first = micros();
  }
  else if (passes > 1){
    last = micros();
  }
}

void setPin(int outputPin)
// function to select pin on 74HC4067
{
  PORTD = controlPins[outputPin];
}

void setup(){
  for(int i=4; i<8;i++)
  {
    digitalWrite(i,0);
  }
  attachInterrupt(0,blade_Pass,FALLING);
  Serial.begin(9600);
  DDRD = B11110000; // 0 = input, 1 = output 
}

void loop(){
    //delay(1000);
    setPin(times); // choose an input pin on the 74HC4067
    if (passes > 1)
    {
      float passesPerSecond = (float)passes / ((float)last - (float)first) * 1000.0 * 1000.0;
      muxValues[times] = passesPerSecond * 30.0;// numBlades;
      // RPM = passesPerSecond * 30.0;
      passes = 0;

       //Serial.println((int)RPM);
      //Serial.println((int)muxValues[times]);
      //Serial.println(times);   
      //Serial.println(passes);   
      if(millis()-Timer >=1000)
      {
       Timer = millis();
       Serial.println((int)muxValues[times]);
      }
    }
    times++;
    if(times>1)
    {
      times = 0;
    } 
    
  //delay(2000); 

  attachInterrupt(0,blade_Pass,FALLING);
}
