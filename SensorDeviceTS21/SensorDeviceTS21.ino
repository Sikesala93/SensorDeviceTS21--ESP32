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

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
#define SERVICE_UUID        "877a5e9a-74ae-4403-bfef-dc4c3fe2179f"
#define CHARACTERISTIC_UUID "040983c3-bbcd-4311-b270-4e530359ad27"
// Lenght for morse space
int morsePause = 90;
bool deviceConnected = false;

// Di ja dah morsetukseen
void di(){
  tone(SummeriPin, NOTE_G6, 30, BUZZ_CHAN);
  noTone(SummeriPin, BUZZ_CHAN);
}
void dah(){
  tone(SummeriPin, NOTE_G6, 90, BUZZ_CHAN);
  noTone(SummeriPin, BUZZ_CHAN);
}
// connect ja disconnect morsetukset
void onConnectMorse() {
  // B
  dah();
  di();
  di();
  di();
  delay(morsePause);
  // T
  dah();
  delay(morsePause*2);
  // O
  dah();
  dah();
  dah();
  delay(morsePause);
  // K
  dah();
  di();
  dah();
  delay(morsePause*2);
  
}
void onDisconnectMorse(){
  // D
  dah();
  di();
  di();
  delay(morsePause);
  // I
  di();
  di();
  delay(morsePause);
  // S 
  di();
  di();
  di();
  delay(morsePause);
  // C
  dah();
  di();
  dah();
  di();
  delay(morsePause);
  // O 
  dah();
  dah();
  dah();
  delay(morsePause);
  // N
  dah();
  di();
  delay(morsePause);
  // N
  dah();
  di();
  delay(morsePause);
  // E
  di();
  delay(morsePause);
  // C
  dah();
  di();
  dah();
  di();
  delay(morsePause);
  // T
  dah();
  delay(morsePause);
  // E
  di();
  delay(morsePause);
  // D
  dah();
  di();
  di();
  delay(morsePause*2);
  
}

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      Serial.println("onConnect");
      onConnectMorse();
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {   
      Serial.println("onDisconnect");
      onDisconnectMorse();
      deviceConnected = false;
    }
};

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();

      if (value.length() > 0) {
        Serial.println("*********");
        Serial.print("New value: ");
        for (int i = 0; i < value.length(); i++)
          Serial.print(value[i]);

        Serial.println();
        Serial.println("*********");
      }
    }
};



BLECharacteristic *pCharacteristic ;

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
