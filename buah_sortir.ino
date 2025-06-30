#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Inisialisasi LCD I2C
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Pin sensor warna TCS3200
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define salidaTCS 8

// Relay
#define RELAY_CONVEYOR 12

// Pin servo untuk tiap warna
#define SERVO1_PIN 9   // Merah
#define SERVO2_PIN 10  // Hijau
#define SERVO3_PIN 2   // Kuning
#define SERVO4_PIN 3   // Pink

// Objek servo
Servo servo1, servo2, servo3, servo4;

// Posisi servo
const int SERVO1_BUKA = 0, SERVO1_TUTUP = 63;
const int SERVO2_BUKA = 55,  SERVO2_TUTUP = 0;
const int SERVO3_BUKA = 0,  SERVO3_TUTUP = 76;
const int SERVO4_BUKA = 55,  SERVO4_TUTUP = 5;

// Counter
int countMerah = 0, countKuning = 0, countHijau = 0, countPink = 0;

void setup() {
  // Inisialisasi pin sensor warna
  pinMode(S0, OUTPUT); pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT); pinMode(S3, OUTPUT);
  pinMode(salidaTCS, INPUT);
  pinMode(RELAY_CONVEYOR, OUTPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  digitalWrite(RELAY_CONVEYOR, LOW); // Konveyor OFF saat awal

  // Serial
  Serial.begin(9600);

  // Servo
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  servo3.attach(SERVO3_PIN);
  servo4.attach(SERVO4_PIN);

  servo1.write(SERVO1_BUKA);
  servo2.write(SERVO2_BUKA);
  servo3.write(SERVO3_BUKA);
  servo4.write(SERVO4_BUKA);

  // LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("APEL_MERAH :");
  lcd.setCursor(0, 1); lcd.print("APEL_KUNING:");
  lcd.setCursor(0, 2); lcd.print("APEL_HIJAU :");
  lcd.setCursor(0, 3); lcd.print("APEL_PINK  :");
}

void bacaWarna(int &r, int &g, int &b) {
  digitalWrite(S2, LOW); digitalWrite(S3, LOW);
  r = pulseIn(salidaTCS, LOW);
  delay(100);

  digitalWrite(S2, HIGH); digitalWrite(S3, HIGH);
  g = pulseIn(salidaTCS, LOW);
  delay(100);

  digitalWrite(S2, LOW); digitalWrite(S3, HIGH);
  b = pulseIn(salidaTCS, LOW);
  delay(100);
}

void kontrolServo(String warna) {
  digitalWrite(RELAY_CONVEYOR, HIGH); // Matikan konveyor sebelum buka tutup

  if (warna == "MERAH") {
    servo1.write(SERVO1_TUTUP);
    delay(2000);
    servo1.write(SERVO1_BUKA);
  } else if (warna == "HIJAU") {
    servo2.write(SERVO2_TUTUP);
    delay(3000);
    servo2.write(SERVO2_BUKA);
  } else if (warna == "KUNING") {
    servo3.write(SERVO3_TUTUP);
    delay(3300);
    servo3.write(SERVO3_BUKA);
  } else if (warna == "PINK") {
    servo4.write(SERVO4_TUTUP);
    delay(2500);
    servo4.write(SERVO4_BUKA);
  }

  digitalWrite(RELAY_CONVEYOR, HIGH); // Konveyor nyala kembali setelah servo selesai
}

void loop() {
  int r, g, b;
  bacaWarna(r, g, b);

  Serial.print("R: "); Serial.print(r);
  Serial.print(" | G: "); Serial.print(g);
  Serial.print(" | B: "); Serial.println(b);

  bool warnaTerdeteksi = false;

  if (r > 800 && g > 1500 && b < 1800) {
    Serial.println("APEL MERAH");
    countMerah++;
    kontrolServo("MERAH");
    warnaTerdeteksi = true;
  }
  else if (r > 200 && g < 500 && b < 600) {
    Serial.println("APEL KUNING");
    countKuning++;
    kontrolServo("KUNING");
    warnaTerdeteksi = true;
  }
  else if (r > 500 && g < 850 && b < 1000) {
    Serial.println("APEL HIJAU");
    countHijau++;
    kontrolServo("HIJAU");
    warnaTerdeteksi = true;
  }
  else if (r > 250 && g > 700 && b < 700) {
    Serial.println("APEL PINK");
    countPink++;
    kontrolServo("PINK");
    warnaTerdeteksi = true;
  }

  if (!warnaTerdeteksi) {
    Serial.println("TIDAK DIKENALI");
    digitalWrite(RELAY_CONVEYOR, LOW); // Konveyor tetap OFF sampai warna dikenali
  }

  // Update LCD
  lcd.setCursor(13, 0); lcd.print(countMerah);
  lcd.setCursor(13, 1); lcd.print(countKuning);
  lcd.setCursor(13, 2); lcd.print(countHijau);
  lcd.setCursor(13, 3); lcd.print(countPink);

  delay(1000);
}
