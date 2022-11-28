// Define pin connections & motor's steps per revolution
const int dirPin = 2;
const int stepPin = 3;
const int dirPin1 = 4;
const int stepPin1 = 5;
const int dirPin2 = 7;
const int stepPin2 = 6;
const int dirPin3 = 8;
const int stepPin3 = 9;
const int stepsPerRevolution = 200;
String inputString= ""; 
bool stringComplete = false; 
int state_command = 0;
void setup()
{
  // Declare pins as Outputs
  
  Serial.begin(115200);
  inputString.reserve(200);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(stepPin3, OUTPUT);
  pinMode(dirPin3, OUTPUT);

  // digitalWrite(MS1, HIGH);
  // digitalWrite(MS2, HIGH);
  // digitalWrite(MS3, HIGH);
  
  // digitalWrite(SLP, HIGH);
  // digitalWrite(RST, HIGH);
  // digitalWrite(en, LOW);

}
bool signal_send(int step,int dir, int dir_need,int step_check)
{
  digitalWrite(dir,dir_need);
   
    for(int x = 0; x < step_check; x++)
      {
        digitalWrite(step, HIGH);
        delayMicroseconds(1000);
        digitalWrite(step, LOW);
        delayMicroseconds(1000);//150
      }
    delay(1000);
}
void serialEvent1() {
  while (Serial.available())
  {
    char inChar = (char)Serial.read();
    if (inChar != '\n'  && inChar != '\r') {
      inputString += inChar;
    }
    if (inChar == '\n') {
      Serial.println(inputString);
      stringComplete = true;
    }
  }
}

void loop()
{
 if (stringComplete)
  {
    if(inputString.equals("1"))
      {
         state_command = 1;
   
      }
      stringComplete = false;
    inputString = "";
  }
  switch(state_command)
   {
      case 0:  break;//idie

      case 1:     bool status_1 = false;
                  bool status_2 = false;
                  bool status_3 = false;
                  bool status_4 = false;
                  int count_time1;
                  
                  for(int x = 0; x < 200; x++)
                  {
                  if (!status_1){
                        status_1 = signal_send(3, 2,1,1);
                        if(status_1)
                        {Serial.println("found 1");}
                  // Serial1.print(",");
                  }
                      if (!status_2){
                        status_2 = signal_send(5, 4,1,1);
                        if(status_2)
                        {Serial.println("found 2");}
                  // Serial1.print(",");
                  }
                      if (!status_3){
                        status_3 = signal_send(6, 7,1,1);
                        if(status_3)
                        {Serial.println("found 3");}
                  // Serial1.print(",");
                  }
                      if (!status_4){
                        status_4 = signal_send(9, 8,1,1);
                        if(status_4)
                        Serial.println("found 4");}
                        
                  }
                    state_command = 0;
                    break;
               
      default: break;
                }
               
  
   
  }
