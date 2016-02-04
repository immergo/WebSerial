#include <SerialCommand.h>

SerialCommand sCmd;   // The SerialCommand object

#define NUMBER_OF_OUTPUTS 4

const byte OUT_PIN[NUMBER_OF_OUTPUTS]={2,3,4,5}; // OUTPUT ARRAY

boolean OUT_FLAG[NUMBER_OF_OUTPUTS]={false,false,false,false};
unsigned long ON_INTERVAL[NUMBER_OF_OUTPUTS];
unsigned long OFF_timestamp[NUMBER_OF_OUTPUTS];

void setup(){
  Serial.begin(115200);
  set_up_output();
  //Callback serial setup
  sCmd.addCommand("H", LED_H);

  Serial.println("Setup done.");
}
void set_up_output(){
  for(int i=0; i<NUMBER_OF_OUTPUTS;i++) {
    pinMode (OUT_PIN[i], OUTPUT);
    //TEST PUROPSE, REMOVE
    digitalWrite(OUT_PIN[i], HIGH);
    delay(200);
    digitalWrite(OUT_PIN[i], LOW);
    //TEST PUROPSE, REMOVE
  }

}
void loop(){
  sCmd.readSerial();     // We don't do much, just process serial commands
  unsigned long currentMillis=millis();
    for(int i=0; i<NUMBER_OF_OUTPUTS;i++){

      if(OUT_FLAG[i]==true&&ON_INTERVAL[i]>0 ) {
        //jesli nie wlaczona
        if(digitalRead(OUT_PIN[i])==LOW) {
          digitalWrite(OUT_PIN[i],HIGH);
          OFF_timestamp[i]=millis();
        }
        //jesli wlaczona, sprawdz czas
        else{
          if((millis()-OFF_timestamp[i])>=ON_INTERVAL[i]){
            //jezeli czas minal, wylacz pin, zmien flage, wywal czas
            digitalWrite(OUT_PIN[i],LOW);
            OUT_FLAG[i]=false;
            ON_INTERVAL[i]=0;
          }

        }
      }

    }
  print_data();//

}
void toggle_led(const byte which){

}

void LED_H(){
  int num;
  unsigned long timeout;
  char *arg;
  arg = sCmd.next();    // Get the next argument from the SerialCommand object buffer
  if (arg!=NULL) {
    num=atoi(arg);
    Serial.println(num);
  }
  else {
    Serial.println("No arguments");
  }
  arg = sCmd.next();
  if (arg != NULL) {
    timeout = atol(arg);
    Serial.println(timeout);
    OUT_FLAG[num]=true;
    ON_INTERVAL[num]=timeout;
  }

else {
  Serial.println("No second argument");
}
}

void print_data(){
  for(int i=0; i<NUMBER_OF_OUTPUTS;i++){
    Serial.print(OUT_FLAG[i]? "1" : "0");
    Serial.print(",");
    Serial.print(ON_INTERVAL[i]);
    Serial.print(",");
  }
  Serial.println(".");
}

