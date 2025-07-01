// Librerías necesarias
#include <Wire.h>
#include <DS1302.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <EEPROM.h>

// Configuración de hardware
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servoAuger;
DS1302 rtc(10, 11, 12); // CE, IO, SCLK

// Pines
const int PIN_CLK    = 2;
const int PIN_DT     = 3;
const int PIN_SW     = 4;
const int PIN_MANUAL = A3;
const int PIN_SERVO  = 9;

// Modos de operación
enum Mode { MODE_NORMAL, MODE_SET_CLOCK, MODE_CONFIG_FEED };
Mode mode = MODE_NORMAL;

// Sub-estados para ajuste de reloj
enum ClockParam { C_HOUR, C_MIN, C_SEC, C_DONE };
ClockParam clkParam = C_HOUR;

// Sub-estados para ajuste de alimentación
enum FeedParam { F_H1_H, F_H1_M, F_H2_H, F_H2_M, F_R, F_DONE };
FeedParam feedParam = F_H1_H;

// Configuración guardada
typedef struct { uint8_t h1, m1, h2, m2, r; } Config;
Config cfg;
const uint8_t ADDR[] = {0,1,2,3,4};

// Variables encoder
unsigned long lastPress = 0;
int lastCLK = HIGH;
int valueTemp = 0;

// Variables de horario
bool dispensed = false;
unsigned long lastCheck = 0;

String twoDigits(uint8_t v) { return v < 10 ? "0" + String(v) : String(v); }

// Prototiposoid loadConfig();
void saveConfig();
void displayNormal();
void displayClockSet();
void displayFeedSet();
void checkSchedule();
void dispense();

void setup() {
  Serial.begin(9600);
  lcd.init(); lcd.backlight();

  pinMode(PIN_CLK, INPUT_PULLUP);
  pinMode(PIN_DT, INPUT_PULLUP);
  pinMode(PIN_SW, INPUT_PULLUP);
  pinMode(PIN_MANUAL, INPUT_PULLUP);

  rtc.writeProtect(false);
  rtc.halt(false);

  
  // rtc.time(Time(2025, 6, 30, 14, 55, 0, Time::kMonday));

  loadConfig();

  servoAuger.attach(PIN_SERVO);
  servoAuger.write(90);
  delay(200);
  servoAuger.detach();

  lcd.clear(); lcd.print("Bienvenido!");
  delay(1500);
}

void loop() {
  // Leer encoder
  int clk = digitalRead(PIN_CLK);
  bool turning = (clk != lastCLK && clk == LOW);
  bool cw = digitalRead(PIN_DT) == HIGH;
  lastCLK = clk;

  // Lectura botón encoder
  if (digitalRead(PIN_SW) == LOW) {
    lastPress = millis();
    while (digitalRead(PIN_SW) == LOW);
    unsigned long dt = millis() - lastPress;

    if (dt > 1000) {
      // Larga: ajustar reloj
      mode = MODE_SET_CLOCK;
      clkParam = C_HOUR;
      Time t = rtc.time(); valueTemp = t.hr;
      displayClockSet();
    } else if (mode == MODE_NORMAL) {
      // Corta en normal: configurar alimentación
      mode = MODE_CONFIG_FEED;
      feedParam = F_H1_H;
      valueTemp = cfg.h1;
      displayFeedSet();
    } else if (mode == MODE_SET_CLOCK) {
      // Confirmar ajuste de reloj
      Time cur = rtc.time();
      if (clkParam == C_HOUR) cur.hr = valueTemp;
      else if (clkParam == C_MIN) cur.min = valueTemp;
      else if (clkParam == C_SEC) cur.sec = valueTemp;
      rtc.time(cur);

      clkParam = (ClockParam)(clkParam + 1);
      if (clkParam == C_DONE) {
        mode = MODE_NORMAL;
        lcd.clear(); lcd.print("Reloj ajustado"); delay(800);
      } else {
        Time nxt = rtc.time();
        valueTemp = (clkParam == C_MIN ? nxt.min : nxt.sec);
        displayClockSet();
      }
    } else if (mode == MODE_CONFIG_FEED) {
      // Confirmar ajuste alimentación
      switch (feedParam) {
        case F_H1_H: cfg.h1 = valueTemp; break;
        case F_H1_M: cfg.m1 = valueTemp; break;
        case F_H2_H: cfg.h2 = valueTemp; break;
        case F_H2_M: cfg.m2 = valueTemp; break;
        case F_R:    cfg.r  = valueTemp; break;
        default: break;
      }
      feedParam = (FeedParam)(feedParam + 1);
      if (feedParam == F_DONE) {
        saveConfig(); mode = MODE_NORMAL;
        lcd.clear(); lcd.print("Config guardada"); delay(800);
      } else {
        // Preparar siguiente valorTemp
        switch (feedParam) {
          case F_H1_M: valueTemp = cfg.m1; break;
          case F_H2_H: valueTemp = cfg.h2; break;
          case F_H2_M: valueTemp = cfg.m2; break;
          case F_R:    valueTemp = cfg.r;  break;
          default: break;
        }
        displayFeedSet();
      }
    }
  }

  // Girar encoder en modos de ajuste
  if (turning) {
    if (mode == MODE_SET_CLOCK) {
      if (clkParam == C_HOUR) valueTemp = (valueTemp + (cw?1:-1) + 24) % 24;
      else if (clkParam == C_MIN) valueTemp = (valueTemp + (cw?1:-1) + 60) % 60;
      else if (clkParam == C_SEC) valueTemp = (valueTemp + (cw?1:-1) + 60) % 60;
      displayClockSet();
    } else if (mode == MODE_CONFIG_FEED) {
      if (feedParam == F_H1_H)  valueTemp = (valueTemp + (cw?1:-1) + 24) % 24;
      else if (feedParam == F_H1_M) valueTemp = (valueTemp + (cw?1:-1) + 60) % 60;
      else if (feedParam == F_H2_H)  valueTemp = (valueTemp + (cw?1:-1) + 24) % 24;
      else if (feedParam == F_H2_M) valueTemp = (valueTemp + (cw?1:-1) + 60) % 60;
      else if (feedParam == F_R)    valueTemp = constrain(valueTemp + (cw?1:-1), 1, 10);
      displayFeedSet();
    }
  }

  // Modo normal: mostrar hora y feed
  if (mode == MODE_NORMAL) {
    displayNormal();
    if (millis() - lastCheck > 1000) { lastCheck = millis(); checkSchedule(); }
  }

  // Botón manual de dispensado
  if (digitalRead(PIN_MANUAL) == LOW) { delay(200); dispense(); }
}

void displayNormal() {
  Time t = rtc.time();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(twoDigits(t.hr) + ":" + twoDigits(t.min) + ":" + twoDigits(t.sec));
  lcd.setCursor(0,1);
  lcd.print("1-" + twoDigits(cfg.h1) + ":" + twoDigits(cfg.m1) + " 2-" + twoDigits(cfg.h2) + ":" + twoDigits(cfg.m2));
}

void displayClockSet() {
  lcd.clear();
  if (clkParam == C_HOUR)    lcd.print("Set Hora: " + twoDigits(valueTemp));
  else if (clkParam == C_MIN) lcd.print("Set Minutos: " + twoDigits(valueTemp));
  else if (clkParam == C_SEC) lcd.print("Set Segundos: " + twoDigits(valueTemp));
}

void displayFeedSet() {
  lcd.clear();
  if (feedParam == F_H1_H)   lcd.print("T1 Hora: " + twoDigits(valueTemp));
  else if (feedParam == F_H1_M) lcd.print("T1 Minutos: " + twoDigits(valueTemp));
  else if (feedParam == F_H2_H)  lcd.print("T2 Hora: " + twoDigits(valueTemp));
  else if (feedParam == F_H2_M) lcd.print("T2 Minutos: " + twoDigits(valueTemp));
  else if (feedParam == F_R)    lcd.print("Raciones: " + String(valueTemp));
}

void checkSchedule() {
  Time t = rtc.time();
  bool win = (t.hr == cfg.h1 && t.min == cfg.m1) || (t.hr == cfg.h2 && t.min == cfg.m2);
  if (win && !dispensed) { dispense(); dispensed = true; }
  if (!win) dispensed = false;
}

void dispense() {
  servoAuger.attach(PIN_SERVO);
  lcd.clear(); lcd.print("Dispensando...");
  for (int i = 0; i < cfg.r; i++) {
    servoAuger.write(180); delay(800);
    servoAuger.write(90);  delay(200);
  }
  servoAuger.detach();
  lcd.clear(); lcd.print("Listo!"); delay(800);
}

void loadConfig() {
  cfg.h1 = EEPROM.read(ADDR[0]); if (cfg.h1 > 23) cfg.h1 = 7;
  cfg.m1 = EEPROM.read(ADDR[1]); if (cfg.m1 > 59) cfg.m1 = 0;
  cfg.h2 = EEPROM.read(ADDR[2]); if (cfg.h2 > 23) cfg.h2 = 17;
  cfg.m2 = EEPROM.read(ADDR[3]); if (cfg.m2 > 59) cfg.m2 = 30;
  cfg.r  = EEPROM.read(ADDR[4]); if (cfg.r  < 1 || cfg.r > 10) cfg.r  = 4;
}

void saveConfig() {
  EEPROM.update(ADDR[0], cfg.h1);
  EEPROM.update(ADDR[1], cfg.m1);
  EEPROM.update(ADDR[2], cfg.h2);
  EEPROM.update(ADDR[3], cfg.m2);
  EEPROM.update(ADDR[4], cfg.r);
}
