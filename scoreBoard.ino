#include "SevSeg.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int maisEq1 = 8;
int menosEq1 = 7;
int maisEq2 = 10;
int menosEq2 = 9;
int reset = 4;
int ledEq1 = 6;
int ledEq2 = 5;

bool i;
bool band;
bool troca;
bool quadra;
bool areia;
int tiebreake;

int set1;
int eq1;
int estadoAnteriorReset;
int estadoAnteriorMaisEq1;
int estadoAnteriorMenosEq1;

int set2;
int eq2;
int estadoAnteriorMaisEq2;
int estadoAnteriorMenosEq2;

SevSeg sevseg;
SevSeg sevseg2;
SevSeg sevseg3;
SevSeg sevseg4;

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int horario = 11; // PINO DIGITAL (CLK)
const int antiHorario = 12; // PINO DIGITAL (DT)

int contadorPos = 0;  // CONTADOR DE POSIÇÕES DO ENCODER
int ultPosicao; // REGISTRA A ÚLTIMA POSIÇÃO DO ENCODER

void setup() {
  display();
  display2();
  display3();
  display4();


  Serial.begin (9600); //INICIALIZA A SERIAL
  pinMode(ledEq1, OUTPUT);
  pinMode(ledEq2, OUTPUT);
  pinMode(maisEq1, INPUT);
  pinMode(menosEq1, INPUT);
  pinMode(maisEq2, INPUT);
  pinMode(menosEq2, INPUT);
  pinMode(reset, INPUT);
  pinMode (horario, INPUT); //DEFINE O PINO COMO ENTRADA
  pinMode (antiHorario, INPUT); //DEFINE O PINO COMO ENTRADA
  //encoder
  ultPosicao = digitalRead(horario); // VARIÁVEL RECEBE A LEITURA DO PINO CLK
  //LCD
  lcd.init();
  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Selecione:");
  lcd.setCursor(0, 1);
  lcd.print("Quadra ou Areia");
  delay(1000);
  lcd.setBacklight(LOW);
  delay(1000);
}

void loop() {
  //botao
  int estadoReset = digitalRead(reset);
  int estadoMaisEq1 = digitalRead(maisEq1);
  int estadoMenosEq1 = digitalRead(menosEq1);
  int estadoMaisEq2 = digitalRead(maisEq2);
  int estadoMenosEq2 = digitalRead(menosEq2);

 
  
  if ((estadoReset == LOW) && (estadoAnteriorReset == HIGH)) {
    eq1 = 0;
    eq2 = 0;
    set1 = 0;
    set2 = 0;
    i = false;
    troca = false;
    quadra = false;
    areia = false;
    tiebreake = false;
    digitalWrite(ledEq2, LOW);
    digitalWrite(ledEq1, LOW);
    delay(200);
  }
  
  if ((estadoMaisEq1 == LOW) && (estadoAnteriorMaisEq1 == HIGH)) {
    eq1++;
    band = true;
    digitalWrite(ledEq2, LOW);
    digitalWrite(ledEq1, HIGH);
    delay(200);
  }
  if ((estadoMenosEq1 == LOW) && (estadoAnteriorMenosEq1 == HIGH)) {
    eq1--;
    band = true;
    delay(200);
  }
  if ((estadoMaisEq2 == LOW) && (estadoAnteriorMaisEq2 == HIGH)) {
    eq2++;
    band = true;
    digitalWrite(ledEq1, LOW);
    digitalWrite(ledEq2, HIGH);
    delay(200);
  }
  if ((estadoMenosEq2 == LOW) && (estadoAnteriorMenosEq2 == HIGH)) {
    eq2--;
    band = true;
    delay(200);
  }

  estadoAnteriorReset = estadoReset;

  estadoAnteriorMaisEq1 = estadoMaisEq1;
  estadoAnteriorMenosEq1 = estadoMenosEq1;

  estadoAnteriorMaisEq2 = estadoMaisEq2;
  estadoAnteriorMenosEq2 = estadoMenosEq2;

  lcd.setBacklight(HIGH);

  //encoder
  int leituraHorario = digitalRead(horario); // LEITURA DO PinoCLK

  if (leituraHorario != ultPosicao) { // SE O VALOR DA VARIÁVEL FOR DIFERENTE DO VALOR DE "ultPosicao", FAZ
    if (digitalRead(antiHorario) != leituraHorario) { // SE LEITURA DO PinoDT FOR DIFERENTE DA LEITURA DE "leituraCLK", FAZ
      contadorPos++; // INCREMENTA CONTAGEM DA VARIÁVEL EM +1
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("2.Areia");
      lcd.setCursor(0, 0);
      lcd.print(" ");
      areia = true;
      quadra = false;
    } else { // SENÃO, FAZ
      contadorPos--; // DECREMENTA CONTAGEM DA VARIÁVEL EM -1
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("1.Quadra");
      lcd.setCursor(0, 1);
      lcd.print(" ");
      quadra = true;
      areia = false;
    }

    ultPosicao = leituraHorario; // VARIÁVEL RECEBE O VALOR DE "leituraCLK"
  }

  sevseg4.setNumber(eq1);
  sevseg3.setNumber(eq2);
  sevseg2.setNumber(set1);
  sevseg.setNumber(set2);
  sevseg.refreshDisplay();
  sevseg2.refreshDisplay();
  sevseg3.refreshDisplay();
  sevseg4.refreshDisplay();
  //regras do jogo quadra
  if (quadra == true) {
    if ((eq1 >= 25 || eq2 >= 25) && abs(eq1 - eq2) >= 2 && tiebreake == false) {
      if (eq1 > eq2) {
        eq1 = 0;
        eq2 = 0;
        set1++;

      } else {
        eq1 = 0;
        eq2 = 0;
        set2++;
      }
    }
    if ((set1 == 2 && set2 == 2) && (i == false)) {
      i = true;
      tiebreake = true;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Tiebreake");
      delay(5000);
    }
    if (tiebreake == true && troca == false) {
      if (eq1 == 8 || eq2 == 8 && tiebreake == true ) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Tiebreake");
        lcd.setCursor(0, 1);
        lcd.print("troca de lado");
        delay(30000);
        lcd.clear();
        troca = true;
      }

    }
    if ((eq1 >= 15 || eq2 >= 15) && abs(eq1 - eq2) >= 2 && tiebreake == true) {
      if (eq1 > eq2) {
        eq1 = 0;
        eq2 = 0;
        set1++;

      } else {
        eq1 = 0;
        eq2 = 0;
        set2++;
      }
    }
    if (set1 == 3 || set2 == 3) {
      if (set1 > set2) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("time 1 ganhou");
        delay(3000);
        lcd.clear();
        set1 = 0;
        set2 = 0;
        i = false;
        troca = false;
        quadra = false;
        areia = false;
        tiebreake = false;
      } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("time 2 ganhou");
        delay(3000);
        lcd.clear();
        set1 = 0;
        set2 = 0;
        i = false;
        troca = false;
        quadra = false;
        areia = false;
        tiebreake = false;
      }
    }
  }
  // regras da areia
  if (areia == true) {
    if ((eq1 >= 21 || eq2 >= 21) && abs(eq1 - eq2) >= 2 && tiebreake == false) {
      if (eq1 > eq2) {
        eq1 = 0;
        eq2 = 0;
        set1++;

      } else {
        eq1 = 0;
        eq2 = 0;
        set2++;
      }
    }
    if ((set1 == 1 && set2 == 1) && (i == false)) {
      i = true;
      tiebreake = true;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Tiebreake");
      delay(5000);
    }
    if (tiebreake == true) {
      if (((eq1 + eq2 ) % 7 == 0 ) && (eq1 >= 1 || eq2 >= 1 )  && (band == true)) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Tiebreake");
        lcd.setCursor(0, 1);
        lcd.print("troca de lado");
        delay(30000);
        lcd.clear();
        band = false;
      }
    }
    if (set1 == 2 || set2 == 2) {
      if (set1 > set2) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("time 1 ganhou");
        delay(5000);
        lcd.clear();
        set1 = 0;
        set2 = 0;
        i = false;
        troca = false;
        quadra = false;
        areia = false;
        tiebreake = false;
      } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("time 2 ganhou");
        delay(5000);
        lcd.clear();
        set1 = 0;
        set2 = 0;
        i = false;
        troca = false;
        quadra = false;
        areia = false;
        tiebreake = false;
      }
    }
  }
}

void display() {
  byte numDigits = 1;
  byte digitPins[] = {39};
  byte segmentPins[] = {42, 43, 40, 38, 41, 45, 44};
  bool resistorsOnSegments = false;
  byte hardwareConfig = COMMON_ANODE;
  bool updateWithDelays = false;
  bool leadingZeros = false;
  bool disableDecPoint = false;

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
               updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);
}

void display2() {
  byte numDigits1 = 1;
  byte digitPins1[] = {31};
  byte segmentPins1[] = {49, 46, 48, 51, 50, 53, 52};
  bool resistorsOnSegments1 = false;
  byte hardwareConfig1 = COMMON_ANODE;
  bool updateWithDelays1 = false;
  bool leadingZeros1 = false;
  bool disableDecPoint1 = false;

  sevseg2.begin(hardwareConfig1, numDigits1, digitPins1, segmentPins1, resistorsOnSegments1,
                updateWithDelays1, leadingZeros1, disableDecPoint1);
  sevseg2.setBrightness(90);
}

void display3() {
  byte numDigits2 = 2;
  byte digitPins2[] = {16, 24};
  byte segmentPins2[] = {26, 27, 29, 22, 15, 25, 14, 28};
  bool resistorsOnSegments2 = false;
  byte hardwareConfig2 = COMMON_ANODE;
  bool updateWithDelays2 = false;
  bool leadingZeros2 = false;
  bool disableDecPoint2 = false;

  sevseg3.begin(hardwareConfig2, numDigits2, digitPins2, segmentPins2, resistorsOnSegments2,
                updateWithDelays2, leadingZeros2, disableDecPoint2);
  sevseg3.setBrightness(90);
}

void display4() {
  byte numDigits = 2;
  byte digitPins[] = {18, 36};
  byte segmentPins[] = {35, 34, 32, 30, 19, 37, 17, 33};
  bool resistorsOnSegments = false;
  byte hardwareConfig = COMMON_ANODE;
  bool updateWithDelays = false;
  bool leadingZeros = false;
  bool disableDecPoint = false;

  sevseg4.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
                updateWithDelays, leadingZeros, disableDecPoint);
  sevseg4.setBrightness(90);
  
}

