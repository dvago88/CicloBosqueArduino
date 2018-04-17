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
boolean isJustUpdate = false;

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
  start();
}

void loop() {

  while (Serial.available() > 0) {
    char recieved = Serial.read();
    //    if (recieved == 'a') {
    //      isJustUpdate = true;
    //    }
    cache += recieved;
    if (recieved == '\n' && !isJustUpdate)    {
      stationNumber = cache.toInt();
      cache = "";
      cualAbrir(stationNumber);
      mandarDatos(stationNumber);
    }
    //    else if (recieved == '\n' && isJustUpdate) {
    //      stationNumber = cache.substring(1).toInt();
    //      cualAbrir(stationNumber);
    //      isJustUpdate = false;
    //      cache = "";
    //    }

  }
  //  Por ahora es un solo sensor para todas las ciclas
  //  la idea es que sea 1 por estación
  if (digitalRead(touchSensor) == HIGH) {
    Serial.println("b");
    delay(1000);
  }
}


void cualAbrir(int estacion) {
  switch (estacion) {
    case 1:
      digitalWrite(unoAbierto, LOW);
      digitalWrite(unoCerrado, HIGH);
      break;
    case -1:
      digitalWrite(unoAbierto, HIGH);
      digitalWrite(unoCerrado, LOW);
      break;
    case 2:
      digitalWrite(dosAbierto, LOW);
      digitalWrite(dosCerrado, HIGH);
      break;
    case -2:
      digitalWrite(dosAbierto, HIGH);
      digitalWrite(dosCerrado, LOW);
      break;
    case 3:
      digitalWrite(tresAbierto, LOW);
      digitalWrite(tresCerrado, HIGH);
      break;
    case -3:
      digitalWrite(tresAbierto, HIGH);
      digitalWrite(tresCerrado, LOW);
      break;
    case 4:
      digitalWrite(cuatroAbierto, LOW);
      digitalWrite(cuatroCerrado, HIGH);
      break;
    case -4:
      digitalWrite(cuatroAbierto, HIGH);
      digitalWrite(cuatroCerrado, LOW);
      break;
    case 5:
      digitalWrite(cincoAbierto, LOW);
      digitalWrite(cincoCerrado, HIGH);
      break;
    case -5:
      digitalWrite(cincoAbierto, HIGH);
      digitalWrite(cincoCerrado, LOW);
      break;
    case 0:
      break;
  }
}

void mandarDatos(int estacion) {
  Serial.print("a");
  //  Serial.println(strID);
  //  String myS = String(abs(estacion));
  Serial.print(abs(estacion));
  //  Serial.print(myS);
  Serial.print("/");
  Serial.print("1111");
  Serial.print("/");
  Serial.print("1111");
  Serial.print("/");
  Serial.println("1111");
}



void start() {
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
