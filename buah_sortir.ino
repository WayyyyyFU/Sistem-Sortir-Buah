#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Inisialisasi LCD I2C dengan alamat 0x27 dan ukuran 20x4
LiquidCrystal_I2C lcd(0x27, 20, 4);

//Pin servo
#define SERVO1_PIN 9  // Servo untuk buah masak
#define SERVO2_PIN 10 // Servo untuk buah mentah
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define salidaTCS 8

// Pin tambahan untuk IR dan Relay
#define IR_SENSOR_PIN 11    // Pin sensor infrared
#define RELAY_CONVEYOR 12   // Pin relay untuk konveyor

// Counter untuk setiap kategori
int countMasak = 0;
int countMentah = 0;
int countBusuk = 0;

// Objek servo
Servo servo1; // Servo untuk buah masak
Servo servo2; // Servo untuk buah mentah

// Posisi default servo (terbuka)
const int SERVO1_BUKA = 0;    // Posisi terbuka servo1
const int SERVO1_TUTUP = 135;  // Posisi tutup servo1
const int SERVO2_BUKA = 0;    // Posisi terbuka servo2
const int SERVO2_TUTUP = 64;  // Posisi tutup servo2

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(salidaTCS, INPUT);
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(RELAY_CONVEYOR, OUTPUT);
  
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  
  // Pastikan konveyor berjalan sejak awal
  digitalWrite(RELAY_CONVEYOR, HIGH);
  
  Serial.begin(9600);
  
  // Inisialisasi servo
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  
  // Set posisi awal servo (terbuka)
  servo1.write(SERVO1_BUKA);
  servo2.write(SERVO2_BUKA);
  
  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sortir Buah APEL");
  lcd.setCursor(0, 1);
  lcd.print("APEL_MERAH : ");
  lcd.setCursor(0, 2);
  lcd.print("APEL_HIJAU : ");
  lcd.setCursor(0, 3);
  lcd.print("Busuk : ");
}

// Fungsi untuk membaca warna
void bacaWarna(int &merah, int &hijau, int &biru) {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  merah = pulseIn(salidaTCS, LOW, 100000);
  delay(100);
  
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  hijau = pulseIn(salidaTCS, LOW, 100000);
  delay(100);
  
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  biru = pulseIn(salidaTCS, LOW, 100000);
  delay(100);
}

// Fungsi untuk mengontrol servo
void kontrolServo(String kondisi) {
  if (kondisi == "MASAK") {
    servo1.write(SERVO1_TUTUP);
    delay(1000);
    servo1.write(SERVO1_BUKA);
  }
  else if (kondisi == "MENTAH") {
    servo2.write(SERVO2_TUTUP);
    delay(1000);
    servo2.write(SERVO2_BUKA);
  }
  else if (kondisi == "BUSUK") {
    delay(1000);
  }
}

void loop() {
  // Baca status sensor IR
  bool objectDetected = (digitalRead(IR_SENSOR_PIN) == LOW);
  
  if (objectDetected) {
    // Hentikan konveyor saat objek terdeteksi
    digitalWrite(RELAY_CONVEYOR, LOW);
    delay(500);
    
    // Baca warna
    int merah, hijau, biru;
    bacaWarna(merah, hijau, biru);
    
    Serial.print("R:"); Serial.print(merah);
    Serial.print("\tG:"); Serial.print(hijau);
    Serial.print("\tB:"); Serial.println(biru);
    
    // Tentukan warna dan kontrol servo
    if (merah < 200 && hijau > 185 && biru > 40) {
      Serial.println("APEL MERAH");
      countMasak++;
      kontrolServo("MASAK");
    }
    else if (merah > 187 && hijau < 174 && biru > 200) {
      Serial.println("APEL HIJAU");
      countMentah++;
      kontrolServo("MENTAH");
    }
    else if (merah > 400 && hijau > 450 && biru < 250) {
      Serial.println("BUSUK");
      countBusuk++;
      kontrolServo("BUSUK");
    }
    else {
      Serial.println("TIDAK TERDETEKSI");
    }
    
    // Update LCD
    lcd.setCursor(12, 1);
    lcd.print(countMasak);
    lcd.setCursor(12, 2);
    lcd.print(countMentah);
    lcd.setCursor(10, 3);
    lcd.print(countBusuk);
    
    delay(500); // Tunggu proses sortir selesai
    digitalWrite(RELAY_CONVEYOR, HIGH); // Jalankan konveyor kembali
  }
  else {
    // Tidak ada objek terdeteksi, konveyor tetap berjalan
    digitalWrite(RELAY_CONVEYOR, HIGH);
  }
}
