🍎 Mesin Penyortir Apel Otomatis
Proyek ini mengimplementasikan sistem otomatis menggunakan Arduino untuk menyortir apel berdasarkan warnanya (Merah, Kuning, Hijau, Merah Jambu) menggunakan sensor warna TCS3200, motor servo untuk gerbang penyortiran, dan layar LCD untuk menampilkan jumlah.

🌟 Fitur
Penyortiran Berdasarkan Warna: Mengidentifikasi dan menyortir apel berdasarkan warna merah, kuning, hijau, dan merah jambu.

Penghitungan Real-time: Melacak jumlah apel yang disortir untuk setiap warna dan menampilkannya pada LCD I2C.

Kontrol Konveyor Otomatis: Terintegrasi dengan sistem konveyor (melalui relai) untuk berhenti sementara selama penyortiran dan melanjutkan operasi.

Desain Modular: Mudah untuk menyesuaikan ambang batas warna dan sudut servo untuk berbagai varietas apel atau pengaturan fisik.

Debugging Serial: Memberikan data sensor mentah dan status deteksi melalui Serial Monitor untuk kalibrasi dan pemecahan masalah yang mudah.

🛠️ Persyaratan Perangkat Keras
Papan Arduino: Arduino Uno atau yang kompatibel.

Modul Sensor Warna TCS3200: Untuk mendeteksi warna apel.

Motor Servo (4x): Servo SG90 standar atau yang serupa untuk menggerakkan gerbang penyortiran.

Layar LCD I2C 16x2 atau 20x4: Untuk menampilkan jumlah apel yang disortir.

Adaptor LCD I2C: Diperlukan untuk menghubungkan LCD melalui I2C.

Modul Relai (1-saluran): Untuk mengontrol motor konveyor.

Sistem Konveyor: Konveyor skala kecil (tidak termasuk dalam kode ini, tetapi tersirat oleh kontrol relai).

Catu Daya: Catu daya eksternal untuk servo dan konveyor, jika diperlukan.

Kabel Jumper: Untuk koneksi.

Breadboard (Opsional): Untuk prototyping yang lebih rapi.

🔌 Diagram Pengkabelan (Konseptual)
Bagian ini menjelaskan koneksi. Silakan merujuk pada diagram Fritzing standar atau lembar data komponen Anda untuk pinout yang tepat.

Komponen

Pin pada Arduino UNO

Catatan

Sensor Warna TCS3200





S0

Pin Digital 4

Penskalaan Frekuensi

S1

Pin Digital 5

Penskalaan Frekuensi

S2

Pin Digital 6

Pemilihan Filter Merah/Biru

S3

Pin Digital 7

Pemilihan Filter Hijau/Biru

OUT (salidaTCS)

Pin Digital 8

Frekuensi output (hubungkan ke pin interupsi jika diperlukan)

VCC

5V



GND

GND



Layar LCD I2C





SDA (Data)

A4 (Pin Analog 4)



SCL (Clock)

A5 (Pin Analog 5)



VCC

5V



GND

GND



Modul Relai





IN (Kontrol)

Pin Digital 12

Hubungkan ke pin sinyal relai

VCC

5V (atau kompatibel dengan modul relai)



GND

GND



Servo 1 (Merah)

Pin Digital 9



Servo 2 (Hijau)

Pin Digital 10



Servo 3 (Kuning)

Pin Digital 2



Servo 4 (Merah Jambu)

Pin Digital 3



Memberi Daya pada Servo: Untuk beberapa servo, sangat disarankan untuk memberi daya dari catu daya eksternal 5V daripada langsung dari pin 5V Arduino, karena mereka dapat menarik arus yang signifikan dan membuat Arduino mati mendadak. Pastikan GND dari catu daya eksternal terhubung ke GND Arduino.

💻 Persyaratan Perangkat Lunak
Arduino IDE: Versi terbaru direkomendasikan.

Pustaka (Libraries): Instal pustaka berikut melalui Manajer Pustaka Arduino IDE:

LiquidCrystal_I2C (oleh Frank de Brabander atau versi yang kompatibel)

Servo (sudah terinstal secara bawaan dengan Arduino IDE)

🚀 Instalasi dan Penyiapan
Kloning repositori ini (atau salin kode) ke mesin lokal Anda.

Buka file .ino di Arduino IDE.

Instal Pustaka:

Buka Sketch > Include Library > Manage Libraries...

Cari LiquidCrystal_I2C dan instal.

Hubungkan Perangkat Keras: Sambungkan semua komponen sesuai dengan bagian "Diagram Pengkabelan".

Pilih Papan dan Port:

Buka Tools > Board dan pilih papan Arduino Anda (misalnya, "Arduino Uno").

Buka Tools > Port dan pilih port serial yang terhubung ke Arduino Anda.

Unggah Kode: Klik tombol "Upload" (ikon panah kanan) di Arduino IDE untuk mengkompilasi dan mengunggah kode ke papan Arduino Anda.

📝 Penggunaan dan Kalibrasi
Penyalaan Awal: Setelah diunggah, LCD akan menyala dan menampilkan label jenis apel. Semua servo akan bergerak ke posisi "buka" mereka.

Mulai Konveyor: Konveyor harus awalnya MATI (RELAY_CONVEYOR diatur ke LOW di setup() dan blok if (!warnaTerdeteksi)).

Kalibrasi Sensor Warna: Ini adalah langkah yang paling penting!

Buka Serial Monitor (Tools > Serial Monitor) di Arduino IDE.

Letakkan apel merah di bawah sensor TCS3200. Catat nilai R, G, B yang dicetak di Serial Monitor. Rekam nilai-nilai tersebut.

Ulangi untuk apel kuning, hijau, dan merah jambu.

Sesuaikan Ambang Batas: Ubah kondisi if-else if dalam fungsi loop() pada kode berdasarkan nilai R, G, B yang Anda amati. Misalnya, jika apel merah Anda memberikan R: 950 | G: 1600 | B: 1750, kondisi Anda r > 800 && g > 1500 && b < 1800 mungkin cocok, atau Anda mungkin perlu mempersempitnya (misalnya, r > 900 && r < 1000 && g > 1500 && g < 1700 && b < 1800). Lakukan eksperimen untuk menemukan rentang yang kuat.

Kalibrasi Sudut Servo:

Uji secara manual nilai SERVO_BUKA dan SERVO_TUTUP untuk setiap servo hingga mereka secara efektif membelokkan atau melewatkan apel. Unggah sketsa uji kecil untuk menyesuaikan sudut ini.

Verifikasi Logika Konveyor:

Konfirmasikan apakah digitalWrite(RELAY_CONVEYOR, HIGH) dan digitalWrite(RELAY_CONVEYOR, LOW) dengan benar menghidupkan/mematikan konveyor Anda. Sesuaikan fungsi kontrolServo() dan loop() jika relai Anda aktif-LOW (yaitu, HIGH mematikannya, LOW menghidupkannya) atau sebaliknya.

Penyetelan Penundaan:

Sesuaikan nilai delay() dalam kontrolServo() (misalnya, delay(2000) untuk merah) berdasarkan kecepatan konveyor Anda dan jarak fisik yang ditempuh apel dari sensor ke gerbang servo. Tujuannya adalah agar gerbang terbuka tepat ketika apel tiba.

🤝 Berkontribusi
Jangan ragu untuk mem-fork repositori ini, membuka isu, atau mengirimkan permintaan pull dengan perbaikan!

📄 Lisensi
Proyek ini adalah open-source dan tersedia di bawah Lisensi MIT.
