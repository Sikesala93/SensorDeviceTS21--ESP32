#include <pitches.h>
#include <Tone32.h>
 
#define PIRPin 32
#define SummeriPin 12
#define LedPin 15
#define BUZZ_CHAN 0

void setup() {
  Serial.begin(115200);
  pinMode(LedPin, OUTPUT);
  pinMode(PIRPin, INPUT);
  pinMode(SummeriPin, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(PIRPin) == HIGH){
    digitalWrite(LedPin, HIGH);
    tone(SummeriPin, NOTE_C6, 100, BUZZ_CHAN);
  }else{
    digitalWrite(LedPin, LOW);
    noTone(SummeriPin, BUZZ_CHAN);
  }
  delay(100);
}
