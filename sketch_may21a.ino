#include <MFRC522.h>
#include <Servo.h>
#define doorPin 7
Servo door;
#define SS_PIN 10
#define RST_PIN 9
#define buz 3
MFRC522 mfrc522(SS_PIN, RST_PIN);
String allowed1 = "8b62983b";
String allowed2 = "83e08397";
String allowed3 = "7377e31";
void setup() {
  Serial.begin(9600);
  pinMode(buz, OUTPUT);
  door.attach(doorPin);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Place your card");
  door.write(180);
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    String cardID = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      cardID += String(mfrc522.uid.uidByte[i], HEX);
    }
    mfrc522.PICC_HaltA();
    if (cardID == allowed1 || cardID == allowed2 || cardID == allowed3) {
      Serial.println("Open the door");
      door.write(0);
      delay(2000);
      door.write(180);
    }
    else {
      decline();
    }
    Serial.print("Card ID: ");
    Serial.println(cardID);
    delay(500);
    Serial.println("Place your card");
  }
}
void decline() {
  tone(buz, 500);
  delay(200);
  noTone(buz);
  delay(200);
}
