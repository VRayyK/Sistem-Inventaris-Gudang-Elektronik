#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Kelompok 4 : 123250034, 123250045
// Judul      : Sistem Inventaris Gudang Elektronik

struct Barang { //Implementasi Struct dan Array
    int kode;
    string nama;
    string kategori;
    int harga;
    int stok;
};

const int MAX_BARANG = 100; // Batas maksimal kapasitas penyimpanan
Barang dataBarang[MAX_BARANG];
int jumlahBarang = 0; // Menghitung jumlah data yang ada saat ini
const string NAMA_FILE = "data_barang.txt";

void simpanData() { //Impelementasi File
    ofstream file(NAMA_FILE); //Output file (menulis ke file)
    if (!file.is_open()) { //Error handling jika file tidak dapat dibuka
        cout << "  [Error] Gagal membuka file untuk menyimpan data!\n";
        return;
    }
    for (int i = 0; i < jumlahBarang; i++) {
        file << dataBarang[i].kode << "\n"
             << dataBarang[i].nama << "\n"
             << dataBarang[i].kategori << "\n"
             << dataBarang[i].harga << "\n"
             << dataBarang[i].stok << "\n";
    }
    file.close();
}

void muatData() {
    ifstream file(NAMA_FILE); //Input file (membaca file)
    if (!file.is_open()) return;

    string temp;
    jumlahBarang = 0;
    
    while (getline(file, temp) && jumlahBarang < MAX_BARANG) {
        if (temp.empty()) continue;
        dataBarang[jumlahBarang].kode = stoi(temp); // stoi = fungsi ini bertugas untuk mengubah tipe data teks (string) menjadi tipe data angka bulat (int)
        
        getline(file, dataBarang[jumlahBarang].nama);
        getline(file, dataBarang[jumlahBarang].kategori);
        
        getline(file, temp); 
        dataBarang[jumlahBarang].harga = stoi(temp); 
        
        getline(file, temp); 
        dataBarang[jumlahBarang].stok = stoi(temp);

        jumlahBarang++;
    }
    file.close();
}

void urutkanData() {
    for (int i = 1; i < jumlahBarang; i++) { // Implementasi Sorting (Insertion Sort)
        Barang key = dataBarang[i];
        int j = i - 1;

        // Pointer menunjuk ke alamat elemen array
        Barang* ptrJ = &dataBarang[j]; // Mendeklarasikan sebuah pointer yang akan menyimpan alamat memori dari sebuah variabel bertipe Barang

        // Kita gunakan pointer untuk mengakses kode
        while (j >= 0 && ptrJ->kode > key.kode) { //Operator panah (->) adalah cara mengakses anggota struct jika kita memegang sebuah pointer (singkatan dari (*ptr).kode)
            dataBarang[j + 1] = dataBarang[j];
            j = j - 1;
            ptrJ = &dataBarang[j]; // Update pointer ke elemen sebelumnya
        }
        dataBarang[j + 1] = key;
    }
}

int cariData(int targetKode) { // Implementasi Searching (Binary Search)
    int kiri = 0;
    int kanan = jumlahBarang - 1;

    while (kiri <= kanan) {
        int tengah = kiri + (kanan - kiri) / 2;

        if (dataBarang[tengah].kode == targetKode)
            return tengah; 
        if (dataBarang[tengah].kode < targetKode)
            kiri = tengah + 1;
        else
            kanan = tengah - 1;
    }
    return -1; 
}

void cetakTabel() {
    cout << "=============================================================\n";
    cout << left << setw(4) << "No" 
         << setw(10) << "KODE" 
         << setw(15) << "NAMA BARANG"
         << setw(15) << "KATEGORI"  
         << setw(10) << "HARGA" 
         << setw(8) << "STOK" << endl;
    cout << "=============================================================\n";
    
    if (jumlahBarang == 0) { // Jika tidak ada barang dalam data
        cout << "        Belum ada data barang di penyimpanan.         \n";
    } else {
        for (int i = 0; i < jumlahBarang; i++) {
            cout << left << setw(4) << i + 1
                 << setw(10) << dataBarang[i].kode
                 << setw(15) << dataBarang[i].nama
                 << setw(15) << dataBarang[i].kategori
                 << setw(10) << dataBarang[i].harga
                 << setw(8) << dataBarang[i].stok << endl;
        }
    }
    cout << "-------------------------------------------------------------\n";
}

void tampilData() {
    system("cls"); // Membersihkan layar menu sebelumnya agar rapi
    cout << "=============================================================\n";
    cout << "                         DATA BARANG                         \n";
    cout << "=============================================================\n\n";
    
    urutkanData(); 
    cetakTabel(); // Memanggil fungsi cetak tabel
    
    system("pause");
}

void updateData() {
    char kembali;
    do {
        system("cls");
        cout << "======================================\n";
        cout << "          M E N U  U P D A T E        \n";
        cout << "======================================\n";
        
        urutkanData();
        cetakTabel(); // melihat barang apa saja yang ada

        cout << "Masukkan kode barang yang ingin diupdate: ";
        int kodeCari;
        if (!(cin >> kodeCari)) { // Error handling jika data yang dimasukkan bukan bertipe int
            cout << "[Error] Input salah!\n";
            return;
        }

        int index = cariData(kodeCari);
        if (index != -1) {
            cin.ignore();
            cout << "\nData Lama -> Nama: " << dataBarang[index].nama
				 << ", Kategori: " << dataBarang[index].kategori
                 << ", Harga: " << dataBarang[index].harga 
                 << ", Stok: " << dataBarang[index].stok << "\n\n";

            cout << "Masukkan Nama Baru  : ";
            getline(cin, dataBarang[index].nama);
            cout << "Masukkan Kategori Baru : ";
            getline(cin, dataBarang[index].kategori);
            cout << "Masukkan Harga Baru : ";
            cin >> dataBarang[index].harga;
            cout << "Masukkan Stok Baru  : ";
            cin >> dataBarang[index].stok;

            simpanData();
            cout << "\n[Success] Data berhasil diperbarui!\n";
        } else {
            cout << "\n[Error] Data dengan kode " << kodeCari << " tidak ditemukan!\n";
        }

        cout << "\nIngin update data lain? (y/n) : ";
        cin >> kembali;
    } while (kembali == 'y' || kembali == 'Y');
}

void cariBerdasarkanHarga() {
    system("cls");
    string katCari;
    int hargaMax;
    
    cout << "=========================================================\n";
    cout << "                      CARI BARANG                        \n";
    cout << "=========================================================\n";
    cin.ignore();
    cout << "Masukkan Kategori yang dicari (ex: HP/Laptop): ";
    getline(cin, katCari);
    cout << "Masukkan Budget Anda: Rp ";
    cin >> hargaMax;
    
    cout << "\nMenampilkan Kategori [" << katCari << "] dengan harga <= Rp " << hargaMax << " :\n\n";
    cout << "==============================================================================\n";
    cout << left << setw(4) << "No" 
         << setw(10) << "KODE" 
         << setw(15) << "NAMA BARANG"  
         << setw(15) << "KATEGORI" 
         << setw(10) << "HARGA" 
         << setw(8) << "STOK" << endl;
    cout << "==============================================================================\n";
    
    int nomor = 1;
    for (int i = 0; i < jumlahBarang; i++) {
        // Melakukan pengecekan ganda: Kategori COCOK DAN Harga MASUK BUDGET
        if (dataBarang[i].kategori == katCari && dataBarang[i].harga <= hargaMax) {
            cout << left << setw(4) << nomor
                 << setw(10) << dataBarang[i].kode
                 << setw(15) << dataBarang[i].nama
                 << setw(15) << dataBarang[i].kategori
                 << setw(10) << dataBarang[i].harga
                 << setw(8) << dataBarang[i].stok << endl;
            nomor++;
        }
    }
    
    if (nomor == 1) {
        cout << "Tidak ada barang di kategori '" << katCari << "' yang cocok dengan budget Anda.\n";
    }
    cout << "------------------------------------------------------------------------------\n";
    system("pause");
}

void beliBarang() {
    system("cls");
    cout << "=======================================================================\n";
    cout << "                     D A F T A R   B A R A N G                         \n";
    cout << "=======================================================================\n";
    
    urutkanData();
    cetakTabel(); // melihat barang yang bisa dibeli

    if (jumlahBarang == 0) {
        system("pause");
        return;
    }

    string namaPembeli;
    int kodeCari, jumlahBeli;

    cin.ignore();
    cout << "Nama Pembeli            : ";
    getline(cin, namaPembeli);
    cout << "Masukkan kode barang    : ";
    cin >> kodeCari;

    int index = cariData(kodeCari);
    if (index != -1) {
        cout << "Barang dipilih          : " << dataBarang[index].nama << " (Harga: " << dataBarang[index].harga << ")\n";
        cout << "Jumlah yang ingin dibeli: ";
        cin >> jumlahBeli;

        if (jumlahBeli <= dataBarang[index].stok) {
            dataBarang[index].stok -= jumlahBeli; 
            simpanData(); 

            int totalHarga = dataBarang[index].harga * jumlahBeli;

            // Cetak Struk ke Layar
            cout << "\n================================================\n";
            cout << "               STRUK PEMBELIAN                  \n";
            cout << "================================================\n";
            cout << "Nama Pembeli : " << namaPembeli << "\n";
            cout << "Barang       : " << dataBarang[index].nama << " (" << dataBarang[index].kategori << ")\n";
            cout << "Jumlah       : " << jumlahBeli << "\n";
            cout << "Total Bayar  : Rp " << totalHarga << "\n";
            cout << "======================================\n";
            cout << "[Success] Pembelian berhasil!\n";

            // Tulis Struk ke File Baru
            ofstream fileStruk("struk_pembelian.txt", ios::app); // ios::app agar struk sebelumnya tidak terhapus
            if (fileStruk.is_open()) {
                fileStruk << "================================================\n";
                fileStruk << "               STRUK PEMBELIAN                  \n";
                fileStruk << "================================================\n";
                fileStruk << "Nama Pembeli : " << namaPembeli << "\n";
                fileStruk << "Barang       : " << dataBarang[index].nama << " (" << dataBarang[index].kategori << ")\n";
                fileStruk << "Jumlah       : " << jumlahBeli << "\n";
                fileStruk << "Total Bayar  : Rp " << totalHarga << "\n";
                fileStruk << "================================================\n\n";
                fileStruk.close();
                cout << "[Info] Struk cetak disimpan ke 'struk_pembelian.txt'\n";
            }

        } else {
            cout << "[Error] Stok tidak mencukupi!\n";
        }
    } else {
        cout << "[Error] Kode barang tidak ditemukan!\n";
    }
    system("pause");
}

void inputBarang() {
char kembali; 
do{
    system("cls"); // Langsung menulis perintah clear screen
    cout << "======================================\n";
    cout << "              M E N U                 \n";
    cout << "          1. Input Barang             \n";
    cout << "======================================\n";
    
    cout << "Berapa banyak data : ";
    int banyak;

    if (!(cin >> banyak)) { // Error handling jika data yang dimasukkan bukan bertipe int
        cout << "\n  [Error] Input salah! Keluar dari program...";
        return; 
    }
    
    for (int i = 0; i < banyak; i++) { // Error handling jika data yang dimasukkan bukan bertipe int
        cout << "\nData ke-" << (i + 1) << "\nKode Barang : ";
        if (!(cin >> dataBarang[jumlahBarang].kode)){ 
			cout << "[Error] Input salah!"; 
			return; 
		}
        cin.ignore();
        cout << "Nama Barang : "; 
        getline(cin, dataBarang[jumlahBarang].nama);
        cout << "Kategori    : "; 
            getline(cin, dataBarang[jumlahBarang].kategori);
        cout << "Harga       : "; 
        if (!(cin >> dataBarang[jumlahBarang].harga)){ // Error handling jika data yang dimasukkan bukan bertipe int
			cout << "[Error] Input salah!"; 
			return; 
		}
        cout << "Stok        : "; 
        if (!(cin >> dataBarang[jumlahBarang].stok)){ // Error handling jika data yang dimasukkan bukan bertipe int
			cout << "[Error] Input salah!"; 
			return; 
		}
        jumlahBarang++;
    }
    urutkanData(); 
    simpanData();
    
    cout << "\n[Info] Data berhasil ditambahkan dan disimpan!\n";
    
    cout << "\nKembali ke menu (y/n) : ";
    cin >> kembali;
}while (kembali == 'n' || kembali == 'N');
}

void hapusData() {
char kembali;
do{
    system("cls"); // Langsung menulis perintah clear screen
    cout << "======================================\n";
    cout << "              M E N U                 \n";
    cout << "          3. Hapus Data               \n";
    cout << "======================================\n";
    
    urutkanData();
    cetakTabel();
    
    cout << "Masukkan kode barang yang ingin dihapus: ";
    int kodeCari;
	if (!(cin >> kodeCari)){  // Error handling jika data yang dimasukkan bukan bertipe int
		cout << "[Error] Input salah!"; 
		return; 
	}
	
    int index = cariData(kodeCari);
    
    if (index != -1){
		// Deklarasi pointer 'target' yang menyimpan alamat memori dari elemen array dataBarang pada indeks yang ditemukan
        Barang* target = &dataBarang[index];
        // Menampilkan nama barang yang akan dihapus ke layar menggunakan operator panah (->) untuk mengakses struct lewat pointer
        cout << "\nMenghapus barang: " << target->nama << "\n";
        
        // Perulangan untuk menggeser elemen array (Array Shifting) guna menutup celah kosong akibat penghapusan data
		// Perulangan dimulai dari posisi data yang dihapus ('index') hingga satu elemen sebelum data terakhir ('jumlahBarang - 1')
        for (int i = index; i < jumlahBarang - 1; i++) {
            dataBarang[i] = dataBarang[i + 1];
        }
        jumlahBarang--;
        simpanData();
        cout << "Data Berhasil Dihapus!\n";
    } else {
        cout << "\n[Error] Data dengan kode " << kodeCari << " tidak ditemukan!\n";
    }
    
    cout << "\nKembali ke menu (y/n) : "; 
    cin >> kembali;
}while (kembali == 'n' || kembali == 'N');
}

int main() {
    muatData(); 
    
    int peran;
    do {
		system("cls");
		cout << "============================================\n";
        cout << "=   SISTEM INVENTARIS GUDANG ELEKTRONIK    =\n\n";
        cout << "  1. Masuk sebagai Penjual\n";
        cout << "  2. Masuk sebagai Pembeli\n";
        cout << "  3. Keluar\n";
        cout << "\n============================================\n";
        cout << "Pilihan peran: ";
        cin >> peran;
        
        if (peran == 1) {
            int pilihan;
            do{
				system("cls"); // Langsung menulis perintah clear screen
				cout << "======================================\n";
				cout << "        M E N U  P E N J U A L        \n";
				cout << "       1. Input Barang                \n";
				cout << "       2. Data Barang                 \n";
				cout << "       3. Hapus Data                  \n";
				cout << "       4. Update Data Barang          \n";
				cout << "       5. Exit                        \n";
				cout << "======================================\n";
				cout << "       Pilihan : ";
				if (!(cin >> pilihan)){  // Error handling jika data yang dimasukkan bukan bertipe int
				cout << "[Error] Input salah!"; 
				return 0; 
				}
		
				switch (pilihan) {
					case 1: 
						inputBarang(); 
						break;
					case 2: 
						tampilData(); 
						break;
					case 3: 
						hapusData(); 
						break;
					case 4: 
						updateData();
						break;
					case 5:
						cout << "\nKembali ke menu utama...\n";
                        system("pause");
                        break;
					default:
						cout << "[Error] Pilihan tidak valid!\n";
						break;
					}
				} while (pilihan != 5);
			} 
			else if (peran == 2) {
			int pilih;
				
			do{
				system("cls");
                cout << "======================================\n";
                cout << "        M E N U  P E M B E L I        \n";
                cout << "       1. Cari Kategori & Budget      \n";
                cout << "       2. Beli Barang                 \n";
                cout << "       3. Kembali ke Menu Utama       \n";
                cout << "======================================\n";
                cout << "       Pilihan : ";
                if (!(cin >> pilih)){  
                    cout << "[Error] Input salah!"; 
                    return 0; 
                }
				switch (pilih){
					case 1:
						cariBerdasarkanHarga();
                        break;
                    case 2:
                        beliBarang();
                        break;
                    case 3:
                        cout << "Kembali ke menu utama...\n";
                        system("pause");
                        break;
                    default:
                        cout << "[Error] Pilihan tidak valid!\n";
                        system("pause");
                        break;
				}
					
			}while(pilih != 3);
		}
	} while (peran != 3);

return 0;
}
