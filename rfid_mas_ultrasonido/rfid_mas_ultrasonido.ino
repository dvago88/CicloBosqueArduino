#include "SPI.h"
#include "MFRC522.h"

#define SS_PIN 10
#define RST_PIN 9
#define SP_PIN 8

MFRC522 rfid(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

int nuevaBici = 0;
int stationNumber = 1;
int greenLed = 8;
int redLed = 7;
int n = 0;

//Distance sensor:
int trigPin = 5;
int echoPin = 6;
int contador = 1000;
float dis = 0;

void setup() {
  Serial.begin(9600);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  dis = measureDistance();
  SPI.begin();
  rfid.PCD_Init();
  open();
}

void loop() {

  if (contador == 1000) {
    float newDis = measureDistance();
    if (abs(newDis - dis) > 5) {
      Serial.print("z");
      Serial.println(newDis);
    }
    contador = 0;
  }
  contador++;

  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  // Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  // Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
      (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
      String(rfid.uid.uidByte[i], HEX) +
      (i != 3 ? ":" : "");
  }

  //  strID.toUpperCase();
  if (nuevaBici == 0) {
    dis = measureDistance();
    Serial.print("a");
    Serial.println(strID);
    Serial.print(stationNumber);
    Serial.print("/");
    Serial.print(dis);
    Serial.print("/");
    Serial.print("1111");
    Serial.print("/");
    Serial.println("1111");
  } else {
    Serial.print("b");
    Serial.println(strID);
    Serial.print(stationNumber);
    Serial.print("/");
    Serial.print("1111");
    Serial.print("/");
    Serial.print("1111");
    Serial.print("/");
    Serial.println("1111");
  }
  esperarRespuestaServidor();
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}


void esperarRespuestaServidor() {
  delay(500);
  for (int i = 0; i <= 100; i++) {
    if (Serial.available()) {
      n = Serial.read();
      break;
    }
    delay(500);
  }
  if (n != 0) {
    close();
    nuevaBici = 1;
  } else {
    open();
    nuevaBici = 0;
  }
}


void close() {
  digitalWrite(redLed, HIGH);
  digitalWrite(greenLed, LOW);
}

void open() {
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, HIGH);
}

float measureDistance() {
  float duration, distance;
  digitalWrite(trigPin, HIGH);
  delay(100);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  //  distance2 = duration * 0.034 / 2;
  return distance;
}

