//Κώδικας που λειτουργεί με πολυπλέκτη και είσοδο που δίνεται μόνο στο C0. Το S0-->D7..S3-->D4
unsigned int passes = 0;
unsigned long first = 0;
unsigned long last = 0;

unsigned long Timer = 0;

byte controlPin = B00000000;
void blade_Pass(){
  passes++;
  if (passes == 1){
    first = micros();
  }
  else if (passes > 1){
    last = micros();
  }
}

void setPin()
// function to select pin on 74HC4067
{
  PORTB = controlPin;
}

void setup(){

  attachInterrupt(0,blade_Pass,FALLING);
  Serial.begin(9600);
  DDRB = B11110000;
  setPin();
}


void loop(){
  //detachInterrupt(digitalPinToInterrupt(2));
  
  if (passes > 1){
    float passesPerSecond = (float)passes / ((float)last - (float)first) * 1000.0 * 1000.0;
    float RPM = passesPerSecond * 30.0;// / numBlades;
     
    passes = 0;
//    if(millis() - Timer >= 10)
//        {
//          Timer = millis();
     
          Serial.println((int)RPM);
          
//        }
  }
  
  attachInterrupt(0,blade_Pass,FALLING);
}
