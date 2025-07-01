# 🍎 Mesin Penyortir Apel Otomatis dengan Arduino

Proyek ini mengimplementasikan sistem otomatis menggunakan Arduino untuk menyortir apel berdasarkan warnanya (Merah, Kuning, Hijau, Merah Jambu) menggunakan sensor warna **TCS3200**, motor **servo** untuk gerbang penyortiran, **relay** untuk konveyor, dan **LCD I2C** untuk menampilkan jumlah apel tersortir secara *real-time*.

![Gambar Proyek Anda Disini](https://github.com/WayyyyyFU/Sistem-Sortir-Buah/blob/fcce0d071ed4d47d17c1a1530e60f165817d2a0a/3d.png)  



## ✨ Fitur Utama

- **Penyortiran Otomatis Berdasarkan Warna**: Mendeteksi dan memisahkan apel merah, kuning, hijau, dan pink.
- **LCD Real-time Counter**: Menampilkan jumlah apel tersortir pada masing-masing warna.
- **Kontrol Konveyor Otomatis**: Menggunakan **relay** untuk menghidupkan atau mematikan konveyor.
- **Debug Serial**: Untuk kalibrasi dan pengujian warna secara langsung.
- **Modular & Mudah Dikembangkan**: Nilai warna dan sudut servo dapat diubah dengan mudah.

---

## 🛠️ Komponen yang Dibutuhkan

- Arduino Uno
- Sensor Warna **TCS3200**
- Motor **Servo SG90** (4x)
- Layar **LCD I2C** 16x2 atau 20x4
- **Relay 1 Channel**
- Sistem konveyor (eksternal)
- Breadboard, kabel jumper, dan power supply

---

## 🔌 Skema Koneksi (Wiring)

| Komponen              | Pin Arduino   |
|----------------------|---------------|
| TCS3200 S0           | `D4`          |
| TCS3200 S1           | `D5`          |
| TCS3200 S2           | `D6`          |
| TCS3200 S3           | `D7`          |
| TCS3200 OUT          | `D8`          |
| Servo Merah          | `D9`          |
| Servo Hijau          | `D10`         |
| Servo Kuning         | `D2`          |
| Servo Pink           | `D3`          |
| Relay Konveyor       | `D12`         |
| LCD I2C SDA          | `A4`          |
| LCD I2C SCL          | `A5`          |

![](https://github.com/WayyyyyFU/Sistem-Sortir-Buah/blob/16a76e1b9c74fe2413e9568cfb062217bca2b703/Skema.png) 

---

## 🚀 Instalasi dan Cara Penggunaan

1. **Siapkan Arduino IDE**
   - Instal versi terbaru Arduino IDE.
   - Tambahkan library berikut:
     - `LiquidCrystal_I2C`
     - `Servo`
   - Gunakan `Sketch > Include Library > Manage Libraries...` untuk menambahkan jika belum tersedia.

2. **Unggah Kode**
   - Buka file `.ino` proyek ini di Arduino IDE.
   - Pilih board: **Arduino Uno**
   - Pilih port COM yang sesuai.
   - Klik tombol **Upload** (✔️) untuk mengunggah program.

3. **Rakit & Hubungkan Perangkat Keras**
   - Hubungkan semua komponen seperti di skema di atas.
   - Pastikan catu daya cukup dan stabil.

4. **Kalibrasi Warna**
   - Buka **Serial Monitor** (`Ctrl + Shift + M`) di Arduino IDE.
   - Letakkan apel di bawah sensor.
   - Catat nilai `R`, `G`, dan `B` yang muncul.
   - Sesuaikan ambang batas di bagian kode berikut:
     ```cpp
     if (r > 800 && g > 1500 && b < 1800) { ... } // Merah
     ```

---

## 🧪 Contoh Nilai Kalibrasi

| Warna Apel     | R      | G      | B      |
|----------------|--------|--------|--------|
| Merah          | >800   | >1500  | <1800  |
| Kuning         | >200   | <500   | <600   |
| Hijau          | >500   | <850   | <1000  |
| Merah Jambu    | >250   | >700   | <700   |

*Silakan sesuaikan dengan kondisi pencahayaan dan jenis apel.*

---

## ⚙️ Cara Kerja Kode

- **`setup()`**:
  - Menginisialisasi sensor, LCD, servo, dan relay.
  - Menampilkan counter pada LCD.
- **`loop()`**:
  1. Membaca warna dengan `pulseIn()` dari TCS3200.
  2. Menentukan warna dan menambah counter.
  3. Memanggil fungsi `kontrolServo(warna)` untuk membuka gerbang servo dan mematikan konveyor sementara.
  4. Menyalakan konveyor kembali setelah penyortiran.
  5. Menampilkan jumlah apel di LCD.

---

## 🤝 Kontribusi

Kontribusi sangat dipersilakan!  
Silakan buka *issue* atau kirim *pull request* jika Anda menemukan bug atau ingin menambahkan fitur baru.

1. Fork repositori ini
2. Buat *branch* baru (`git checkout -b fitur/fitur-baru`)
3. Commit perubahan (`git commit -am 'Tambah fitur baru'`)
4. Push ke *branch* Anda (`git push origin fitur/fitur-baru`)
5. Buat *Pull Request* di GitHub

---

## 📜 Lisensi

Lisensi: **MIT License**  
Bebas digunakan untuk tujuan edukasi maupun komersial.  
Lihat file `LICENSE` untuk detail lebih lanjut.
