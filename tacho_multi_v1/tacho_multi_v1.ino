unsigned long Timer = 0;

byte controlPins[] = {B00000000, B10000000};
byte muxValues[] = {0,0,};

void setPin(int outputPin)
// function to select pin on 74HC4067
{
  PORTD = controlPins[outputPin];
}

void setup()
{
  Serial.begin(9600);
  DDRD = B11110000; // 0 = input, 1 = output 
}

void loop(){
  for (int i = 0; i < 2; i++)
  {
    setPin(i); // choose an input pin on the 74HC4067
   
    muxValues[i] = digitalRead(2);
    Serial.println(muxValues[i]);
    
    delay(1000); 
  }
   Serial.println("=================================");
}
