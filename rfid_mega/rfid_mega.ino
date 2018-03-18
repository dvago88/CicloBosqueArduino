#include "SPI.h"
#include "MFRC522.h"

#define SS_PIN 53
#define RST_PIN 5
//#define SP_PIN 8

MFRC522 rfid(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

int touchSensor = 46;

int stationNumber;
int nuevaBici = 0;

int unoAbierto = 17;
int unoCerrado = 16;

int dosAbierto = 15;
int dosCerrado = 14;

int tresAbierto = 8;
int tresCerrado = 9;

int cuatroAbierto = 10;
int cuatroCerrado = 11;

int cincoAbierto = 12;
int cincoCerrado = 13;

int n = 0;

String cache;

void setup() {
  Serial.begin(9600);
  pinMode(unoAbierto, OUTPUT);
  pinMode(unoCerrado, OUTPUT);
  pinMode(dosAbierto, OUTPUT);
  pinMode(dosCerrado, OUTPUT);
  pinMode(tresAbierto, OUTPUT);
  pinMode(tresCerrado, OUTPUT);
  pinMode(cuatroAbierto, OUTPUT);
  pinMode(cuatroCerrado, OUTPUT);
  pinMode(cincoAbierto, OUTPUT);
  pinMode(cincoCerrado, OUTPUT);
  pinMode(touchSensor, INPUT);
  SPI.begin();
  rfid.PCD_Init();
  open();
}

void loop() {
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

  Serial.print("a");
  Serial.println(strID);
  stationNumber = 0;
  stationNumber = confirmacion();
  if (stationNumber == 0) {
    return;
  }

  //  strID.toUpperCase();
  if (stationNumber < 100) {
    for (int i = 0; i <= 1000; i++) {
      if (digitalRead(touchSensor) == HIGH) {
        mandarDatos(stationNumber, strID);
        esperarRespuestaServidor(stationNumber);
        break;
      }
      delay(100);
    }
  } else {
//        shit();
    esperarRespuestaServidor(stationNumber);
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

void esperarRespuestaServidor(int estacion) {
  delay(500);
  for (int i = 0; i <= 100; i++) {
    if (Serial.available()) {
      cache = "";
      cache += Serial.read();
      cache += Serial.read();
      n = cache.toInt();
      break;
    }
    delay(500);
  }
  if (n != 0) {
    cualAbrir(estacion);
  }
}


int confirmacion() {
  int station;
  delay(100);
  for (int i = 0; i <= 1000; i++) {
    if (Serial.available()) {
      cache = "";
      cache += Serial.read();
      cache += Serial.read();
      station = cache.toInt();
      return station;
    }
    delay(100);
  }
  return 0;
}



void mandarDatos(int estacion, String strID ) {
  Serial.print("b");
  Serial.println(strID);
  Serial.print(abs(estacion));
  Serial.print("/");
  Serial.print("1111");
  Serial.print("/");
  Serial.print("1111");
  Serial.print("/");
  Serial.println("1111");

}

void cualAbrir(int estacion) {
  switch (estacion) {
    case 10:
      digitalWrite(unoAbierto, LOW);
      digitalWrite(unoCerrado, HIGH);
      break;
    case 100:
      digitalWrite(unoAbierto, HIGH);
      digitalWrite(unoCerrado, LOW);
      break;
    case 12:
      digitalWrite(dosAbierto, LOW);
      digitalWrite(dosCerrado, HIGH);
      break;
    case 120:
      digitalWrite(dosAbierto, HIGH);
      digitalWrite(dosCerrado, LOW);
      break;
    case 13:
      digitalWrite(tresAbierto, LOW);
      digitalWrite(tresCerrado, HIGH);
      break;
    case 130:
      digitalWrite(tresAbierto, HIGH);
      digitalWrite(tresCerrado, LOW);
      break;
    case 14:
      digitalWrite(cuatroAbierto, LOW);
      digitalWrite(cuatroCerrado, HIGH);
      break;
    case 140:
      digitalWrite(cuatroAbierto, HIGH);
      digitalWrite(cuatroCerrado, LOW);
      break;
    case 15:
      digitalWrite(cincoAbierto, LOW);
      digitalWrite(cincoCerrado, HIGH);
      break;
    case 150:
      digitalWrite(cincoAbierto, HIGH);
      digitalWrite(cincoCerrado, LOW);
      break;
    case 0:
      break;
  }
}

void close() {
  digitalWrite(unoAbierto, LOW);
  digitalWrite(dosAbierto, LOW);
  digitalWrite(tresAbierto, LOW);
  digitalWrite(cuatroAbierto, LOW);
  digitalWrite(cincoAbierto, LOW);
  digitalWrite(unoCerrado, HIGH);
  digitalWrite(dosCerrado, HIGH);
  digitalWrite(tresCerrado, HIGH);
  digitalWrite(cuatroCerrado, HIGH);
  digitalWrite(cincoCerrado, HIGH);
}

void open() {
  digitalWrite(unoAbierto, HIGH);
  digitalWrite(dosAbierto, HIGH);
  digitalWrite(tresAbierto, HIGH);
  digitalWrite(cuatroAbierto, HIGH);
  digitalWrite(cincoAbierto, HIGH);
  digitalWrite(unoCerrado, LOW);
  digitalWrite(dosCerrado, LOW);
  digitalWrite(tresCerrado, LOW);
  digitalWrite(cuatroCerrado, LOW);
  digitalWrite(cincoCerrado, LOW);
}

void shit() {
  digitalWrite(unoAbierto, LOW);
  digitalWrite(unoCerrado, LOW);
  digitalWrite(dosAbierto, LOW);
  digitalWrite(dosCerrado, LOW);
  digitalWrite(tresAbierto, LOW);
  digitalWrite(tresCerrado, LOW);
  digitalWrite(cuatroAbierto, LOW);
  digitalWrite(cuatroCerrado, LOW);
  delay(100);
  digitalWrite(unoAbierto, HIGH);
  digitalWrite(unoCerrado, HIGH );
  digitalWrite(dosAbierto, HIGH);
  digitalWrite(dosCerrado, HIGH);
  digitalWrite(tresAbierto, HIGH);
  digitalWrite(tresCerrado, HIGH);
  digitalWrite(cuatroAbierto, HIGH);
  digitalWrite(cuatroCerrado, HIGH);
  delay(100);
  digitalWrite(unoAbierto, LOW);
  digitalWrite(unoCerrado, LOW);
  digitalWrite(dosAbierto, LOW);
  digitalWrite(dosCerrado, LOW);
  digitalWrite(tresAbierto, LOW);
  digitalWrite(tresCerrado, LOW);
  digitalWrite(cuatroAbierto, LOW);
  digitalWrite(cuatroCerrado, LOW);
  delay(100);
  digitalWrite(unoAbierto, HIGH);
  digitalWrite(unoCerrado, HIGH );
  digitalWrite(dosAbierto, HIGH);
  digitalWrite(dosCerrado, HIGH);
  digitalWrite(tresAbierto, HIGH);
  digitalWrite(tresCerrado, HIGH);
  digitalWrite(cuatroAbierto, HIGH);
  digitalWrite(cuatroCerrado, HIGH);
  delay(100);
  open();


}

