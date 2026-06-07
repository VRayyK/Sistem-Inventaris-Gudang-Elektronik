# Sistem Inventaris Gudang Elektronik 🛒⚡
Sistem Inventaris Gudang Elektronik adalah aplikasi berbasis CLI (Command Line Interface) yang dirancang untuk mengelola sirkulasi data barang di gudang elektronik secara efisien. Proyek ini dibuat sebagai pemenuhan Tugas Akhir praktikum mata kuliah **Algoritma dan Pemrograman Lanjut (Semester Genap T.A. 2025/2026)**.

Program ini mengimplementasikan konsep interaksi multi-peran, memisahkan fitur hak akses antara **Penjual (Administrator)** untuk manajemen stok, dan **Pembeli (Customer)** untuk melakukan simulasi transaksi pembelian.

---

## 👥 Anggota Kelompok 4 (IF-A)
1. **123250034** - Feyzar
2. **123250045** - Vipassa

---

## 🚀 Fitur Utama

### 👨‍💼 Menu Penjual (Admin Mode)
* **Input Barang:** Menambahkan data barang baru ke dalam sistem inventaris secara massal.
* **Data Barang (Viewing):** Menampilkan seluruh daftar barang yang terdaftar di gudang dalam bentuk tabel yang rapi.
* **Hapus Data:** Menghapus data barang tertentu berdasarkan kode unik barang menggunakan metode pergeseran memori.
* **Update Data:** Mengubah informasi barang lama (Nama, Kategori, Harga, Stok) berdasarkan kode barang secara dinamis.

### 👤 Menu Pembeli (Customer Mode)
* **Cari Kategori & Budget (Filtering):** Mencari dan menyaring barang secara spesifik berdasarkan kombinasi filter nama kategori dan batas maksimal harga (*budget*).
* **Beli Barang (Transaction):** Melakukan simulasi pembelian barang yang otomatis mengurangi jumlah stok gudang di RAM dan berkas penyimpanan.
* **Cetak Struk:** Menggenerasi struk bukti pembelian langsung ke layar kaca pengguna sekaligus mengekspornya ke dalam berkas fisik eksternal.

---

## 🛠️ Konsep & Struktur Data yang Diimplementasikan

Aplikasi ini dibangun dengan menerapkan berbagai konsep fundamental pemrograman terstruktur dan algoritma lanjutan:

1. **Struct & Array of Struct:** Menyatukan komponen atribut heterogen dari entitas barang (Kode, Nama, Kategori, Harga, Stok) menjadi satu kesatuan objek logis di dalam larik statis berkapasitas maksimal 100 data.
2. **File Handling (`<fstream>`):** Memberikan fitur ketahanan penyimpanan (*data persistence*). 
   * `ifstream` digunakan untuk memuat (*load*) data dari `data_barang.txt` saat aplikasi pertama kali dijalankan.
   * `ofstream` digunakan untuk memperbarui (*save*) berkas setiap kali terjadi penambahan, pengubahan, atau penghapusan data barang.
   * Mode `ios::app` digunakan untuk mencetak riwayat struk belanja baru tanpa menghapus data struk lama di `struk_pembelian.txt`.
3. **Insertion Sort Algorithm:** Mengurutkan seluruh data inventaris secara otomatis berdasarkan *Kode Barang* secara *ascending* (dari kecil ke besar) demi memastikan aspek kerapian visual tabel.
4. **Binary Search Algorithm:** Mengoptimasi efisiensi pencarian kode barang dari skala linear $O(n)$ menjadi skala logaritmik $O(\log n)$ dengan memanfaatkan kondisi data array yang sudah terurut pra-pencarian.
5. **Pointer Memory Address:** Menggunakan penunjuk alamat memori (*pointer*) dan operator panah (`->`) untuk mengakses dan memanipulasi anggota data *struct* secara efisien pada modul sorting dan penghapusan data.
6. **Array Shifting:** Mekanisme penghapusan data pada array statis dengan cara menimpa (*overwriting*) posisi indeks data yang dihapus menggunakan data di samping kanannya secara beruntun.
7. **Input Trap Validation:** Validasi ganda menggunakan ekspresi logika `if (!(cin >> variabel))` guna memfilter proteksi *error handling* agar sistem tidak mengalami kemacetan (*infinite loop*) akibat kesalahan input tipe data karakter.

---

## 📁 Struktur Berkas Output
Setelah program dijalankan dan berinteraksi, sistem akan otomatis menghasilkan berkas berikut di dalam direktori proyek:
* `data_barang.txt` : Berkas database utama penyimpanan stok inventaris gudang.
* `struk_pembelian.txt` : Berkas log berisi kumpulan seluruh riwayat struk belanja konsumen.

---
