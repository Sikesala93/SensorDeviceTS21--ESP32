#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

#include <pitches.h>
#include <Tone32.h> //pitches.h ja Tone32.h -->  https://github.com/lbernstone/Tone32
 
#define PIRPin 32
#define SummeriPin 12
#define LedPin 15
#define BUZZ_CHAN 0

#define SERVICE_UUID        "877a5e9a-74ae-4403-bfef-dc4c3fe2179f"
#define CHARACTERISTIC_UUID "040983c3-bbcd-4311-b270-4e530359ad27"

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
