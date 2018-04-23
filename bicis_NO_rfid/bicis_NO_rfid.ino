int stationNumber;
int nuevaBici = 0;

int unoAbierto = 53;
int unoCerrado = 52;
int unoChecker = A10;

int dosAbierto = 51;
int dosCerrado = 50;
int dosChecker = A11;

int tresAbierto = 49;
int tresCerrado = 48;
int tresChecker = A12;

int cuatroAbierto = 47;
int cuatroCerrado = 46;
int cuatroChecker = A13;

int cincoAbierto = 45;
int cincoCerrado = 44;
int cincoChecker = A14;

int seisAbierto = 43;
int seisCerrado = 42;
int touchSensor = 21; //Este es un sensor de toque

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
  pinMode(seisAbierto, OUTPUT);
  pinMode(seisCerrado, OUTPUT);
  pinMode(touchSensor, INPUT);
  pinMode(unoChecker, INPUT);
  pinMode(dosChecker, INPUT);
  pinMode(tresChecker, INPUT);
  pinMode(cuatroChecker, INPUT);
  pinMode(cincoChecker, INPUT);
  start();
}

void loop() {

  while (Serial.available() > 0) {
    char recieved = Serial.read();
    if (recieved == 'a') {
      isJustUpdate = true;
    }
    cache += recieved;
    if (recieved == '\n' && !isJustUpdate)    {
      stationNumber = cache.toInt();
      cache = "";
      cualAbrir(stationNumber);
      mandarDatos(stationNumber);
    }
    else if (recieved == '\n' && isJustUpdate) {
      stationNumber = cache.substring(1).toInt();
      cualAbrir(stationNumber);
      isJustUpdate = false;
      cache = "";
    }

  }
  if (digitalRead(touchSensor) == HIGH) {
    Serial.println("b6");
    delay(1000);
  }
  if (analogRead(unoChecker) <= 150) {
    Serial.println("b1");
    delay(1500);
  }
  if (analogRead(dosChecker) <= 150) {
    Serial.println("b2");
    delay(1500);
  }
  if (analogRead(tresChecker) <= 150) {
    Serial.println("b3");
    delay(1500);
  }
  if (analogRead(cuatroChecker) <= 150) {
    Serial.println("b4");
    delay(1500);
  }
  if (analogRead(cincoChecker) <= 350) {
    Serial.println("b5");
    delay(1500);
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
    case 6:
      digitalWrite(seisAbierto, LOW);
      digitalWrite(seisCerrado, HIGH);
      break;
    case -6:
      digitalWrite(seisAbierto, HIGH);
      digitalWrite(seisCerrado, LOW);
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
  digitalWrite(seisAbierto, LOW);
  digitalWrite(unoCerrado, HIGH);
  digitalWrite(dosCerrado, HIGH);
  digitalWrite(tresCerrado, HIGH);
  digitalWrite(cuatroCerrado, HIGH);
  digitalWrite(cincoCerrado, HIGH);
  digitalWrite(seisCerrado, HIGH);
}

void open() {
  digitalWrite(unoAbierto, HIGH);
  digitalWrite(dosAbierto, HIGH);
  digitalWrite(tresAbierto, HIGH);
  digitalWrite(cuatroAbierto, HIGH);
  digitalWrite(cincoAbierto, HIGH);
  digitalWrite(seisAbierto, HIGH);
  digitalWrite(unoCerrado, LOW);
  digitalWrite(dosCerrado, LOW);
  digitalWrite(tresCerrado, LOW);
  digitalWrite(cuatroCerrado, LOW);
  digitalWrite(cincoCerrado, LOW);
  digitalWrite(seisCerrado, LOW);
}
