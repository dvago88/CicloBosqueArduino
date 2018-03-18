int touchSensor = 7;

int stationNumber;
int nuevaBici = 0;

int unoAbierto = 3;
int unoCerrado = 4;

int dosAbierto = 5;
int dosCerrado = 6;

int tresAbierto = 8;
int tresCerrado = 9;

int cuatroAbierto = 10;
int cuatroCerrado = 11;

int cincoAbierto = 12;
int cincoCerrado = 13;

int n = 0;

String cache;

int c = 0;
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
  open();
  delay(200);
  close();
  delay(200);
  open();
  delay(200);
  close();
  delay(200);
  open();
  delay(200);
  close();
  delay(200);
  open();
}

void loop() {
  stationNumber = 0;
  stationNumber = confirmacion();
  if (stationNumber == 0) {
    c++;
    if (c == 10) {
      Serial.println("8888888");
      c = 0;
    }
    return;
  }

  if (stationNumber < 100) {
    for (int i = 0; i <= 1000; i++) {
      if (digitalRead(touchSensor) == HIGH) {
        mandarDatos(stationNumber);
        esperarRespuestaServidor(stationNumber);
        break;
      }
      delay(100);
    }
  } else {
    esperarRespuestaServidor(stationNumber);
  }
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
  for (int i = 0; i <= 10; i++) {
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



void mandarDatos(int estacion) {
  Serial.println("b");
  //  Serial.println(strID);
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

