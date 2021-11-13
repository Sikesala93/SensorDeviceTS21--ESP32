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

// Morsekoodit----------------------------------------------------------------

// Morsen pauseväli
int morsePause = 90;

// Di ja dah
void di(){
  tone(SummeriPin, NOTE_G6, 30, BUZZ_CHAN);
  noTone(SummeriPin, BUZZ_CHAN);
}
void dah(){
  tone(SummeriPin, NOTE_G6, 90, BUZZ_CHAN);
  noTone(SummeriPin, BUZZ_CHAN);
}

// connect, disconnect ja hello morsetukset
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
void helloMorse(){
  //H
  di();
  di();
  di();
  di();
  delay(morsePause);
  // E
  di();
  delay(morsePause);
  //L
  di();
  dah();
  di();
  di();
  delay(morsePause);
  //L
  di();
  dah();
  di();
  di();
  delay(morsePause);
  // O 
  dah();
  dah();
  dah();
  delay(morsePause*2);
}
// Morsetukset loppuu ------------------------------------------------------------------

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
#define SERVICE_UUID        "877a5e9a-74ae-4403-bfef-dc4c3fe2179f"
#define CHARACTERISTIC_UUID "040983c3-bbcd-4311-b270-4e530359ad27"
bool deviceConnected = false;

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      Serial.println("onConnect");
      onConnectMorse();
      digitalWrite(LedPin, HIGH);
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {   
      Serial.println("onDisconnect");
      onDisconnectMorse();
      digitalWrite(LedPin, LOW);
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

  Serial.println("R5ESP");
  
  BLEDevice::init("R5ESP");
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  BLEService *pService = pServer->createService(SERVICE_UUID);
  
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );

  pCharacteristic->setCallbacks(new MyCallbacks());
  //pCharacteristic->addDescriptor(new BLE2902());
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
  
  
  helloMorse();
  delay(1000);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(PIRPin) == HIGH ){
    int movement = 1;
    pCharacteristic->setValue(movement);
    pCharacteristic->notify();
    Serial.println("Movement Detetected!");   
  }
  delay(100);
}
