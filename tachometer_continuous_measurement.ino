unsigned int passes = 0;
unsigned long first = 0;
unsigned long last = 0;

unsigned long Timer = 0;
void blade_Pass(){
  passes++;
  if (passes == 1){
    first = micros();
  }
  else if (passes > 1){
    last = micros();
  }
}

void setup(){

  attachInterrupt(0,blade_Pass,FALLING);
  Serial.begin(9600);
}


void loop(){
  //detachInterrupt(digitalPinToInterrupt(2));
  if (passes > 1){
    float passesPerSecond = (float)passes / ((float)last - (float)first) * 1000.0 * 1000.0;
    float RPM = passesPerSecond * 30.0;// / numBlades;
//    Serial.print("Passes: ");
//    Serial.print(passes);
//    Serial.print(" Time: ");
//    Serial.print(last-first);
//    Serial.print(" PPS: ");
//    Serial.print(passesPerSecond);
   
       
    passes = 0;
    if(millis() - Timer >= 1000)
        {
          Timer = millis();
          Serial.print("RPM: ");
          Serial.println(RPM);
          
        }
  }
  
  attachInterrupt(0,blade_Pass,FALLING);
}
