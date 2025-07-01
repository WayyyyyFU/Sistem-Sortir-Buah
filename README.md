  🍎 Mesin Penyortir Apel Otomatis
  --------------------------------
  Proyek ini mengimplementasikan sistem otomatis menggunakan Arduino 
  untuk menyortir apel berdasarkan warnanya (Merah, Kuning, Hijau, Merah Jambu) 
  menggunakan sensor warna TCS3200, motor servo untuk gerbang penyortiran, 
  dan layar LCD untuk menampilkan jumlah.
 
  🌟 Fitur:
  - Penyortiran Berdasarkan Warna (Merah, Kuning, Hijau, Merah Jambu)
  - Penghitungan Real-time di LCD I2C
  - Kontrol Konveyor Otomatis via Relay
  - Desain Modular untuk kalibrasi warna dan servo
  - Debugging Serial
 
  🛠️ Perangkat Keras:
  - Arduino Uno
  - Sensor TCS3200
  - 4x Servo SG90
  - LCD I2C 16x2 / 20x4
  - Relay 1 channel
  - Sistem Konveyor (eksternal)
  - Breadboard, kabel jumper, dan catu daya eksternal
 
  🔌 Wiring (Arduino UNO):
  - TCS3200: S0(4), S1(5), S2(6), S3(7), OUT(8)
  - Servo Merah (9), Hijau (10), Kuning (2), Pink (3)
  - Relay Konveyor: IN (12)
  - LCD I2C: SDA (A4), SCL (A5)
 
  💻 Software:
  - Arduino IDE terbaru
  - Library: LiquidCrystal_I2C, Servo
 
  🚀 Langkah Penggunaan:
  1. Upload kode ke Arduino
  2. Hubungkan seluruh perangkat keras
  3. Nyalakan sistem
  4. Gunakan Serial Monitor untuk kalibrasi warna apel
  5. Atur ambang batas R, G, B untuk tiap warna
  6. Atur sudut servo dan delay penyortiran
 
  🧪 Contoh Kalibrasi:
  - Apel Merah: R > 900, G > 1500, B < 1800
  - Apel Hijau: R < 900, G > 2000, B < 2000
  - Apel Kuning: R > 1000, G > 1700, B < 1600
  - Apel Merah Jambu: R > 1000, G < 1500, B > 1700
 
 📜 Cara Penggunaan Kode
  Untuk menjalankan sistem penyortir apel otomatis dengan benar, ikuti panduan berikut:

  1️⃣ Persiapan Software
  Pastikan Arduino IDE versi terbaru telah terinstal.
  Buka Arduino IDE.
  Tambahkan library berikut jika belum ada:
  LiquidCrystal_I2C (untuk LCD I2C)
  Servo (untuk mengontrol motor servo)
  Tambahkan library melalui Sketch > Include Library > Manage Libraries...
  
  2️⃣ Buka dan Unggah Kode
  Buka file .ino kode proyek ini di Arduino IDE.
  Pilih board: Arduino Uno
  Pilih port COM yang sesuai: Tools > Port
  Klik Upload (✔) untuk mengunggah program ke Arduino.

  3️⃣ Hubungkan Perangkat Keras
  Rakit dan hubungkan seluruh komponen sesuai dengan bagian 🔌 Wiring (Arduino UNO).
  Pastikan semua koneksi kabel aman dan tegangan sesuai.

  4️⃣ Gunakan Serial Monitor untuk Kalibrasi
  Buka Serial Monitor di Arduino IDE (Ctrl + Shift + M
  Letakkan apel di bawah sensor warna TCS3200 satu per satu.
  Catat nilai RGB yang muncul di Serial Monitor.
  Sesuaikan batas RGB di bagian kode ini:
  
  if (R > 900 && G > 1500 && B < 1800) {
  // apel merah
  }

  🤝 Kontribusi:
  Fork, issue, dan pull request dipersilakan!
 
  📄 Lisensi:
  MIT License - bebas digunakan untuk tujuan edukasi dan komersial.
 */
