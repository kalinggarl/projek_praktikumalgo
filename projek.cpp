#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>

using namespace std;

struct admin {   
    string username;
    string password; 
};

struct Buku {
    string nama;
    int id;
    int harga;
    string kategori;
};

admin admins[] = {
    {"user", "2570"},
    {"lingga", "2580"},
    {"naura", "2590"}
};
int jmlhadmins = 3;
Buku daftarBuku[100];
int jumlahBuku = 0;
bool adaArsipNegara = false; // Penanda global untuk membatasi kategori 'arsip negara'

// Fungsi untuk mengubah string menjadi huruf kecil semua (case-insensitive)
string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// Fungsi konfirmasi setelah melakukan aksi untuk kembali ke menu utama
void konfirmasiKembali() {
    char pilihan;
    cout << "\nKembali ke menu? (Y/n): ";
    cin >> pilihan;
    cin.ignore(); // Membersihkan sisa buffer setelah input karakter
}

// ==================== BARU: FUNGSI FILE HANDLING ====================

// Fungsi untuk menyimpan seluruh data dari array ke dalam file txt
void simpanKeFile() {
    ofstream file("database_buku.txt");
    if (file.is_open()) {
        file << adaArsipNegara << endl;
        file << jumlahBuku << endl;
        for (int i = 0; i < jumlahBuku; i++) {
            file << daftarBuku[i].nama << endl;
            file << daftarBuku[i].id << endl;
            file << daftarBuku[i].harga << endl;
            file << daftarBuku[i].kategori << endl;
        }
        file.close();
    }
}

// Fungsi untuk membaca data dari file txt ke dalam array saat program dinyalakan
void bacaDariFile() {
    ifstream file("database_buku.txt");
    if (file.is_open()) {
        file >> adaArsipNegara;
        file >> jumlahBuku;
        file.ignore(); // Bersihkan sisa enter setelah membaca jumlahBuku
        
        for (int i = 0; i < jumlahBuku; i++) {
            getline(file, daftarBuku[i].nama);
            file >> daftarBuku[i].id;
            file >> daftarBuku[i].harga;
            file.ignore(); // Bersihkan enter sebelum getline kategori
            getline(file, daftarBuku[i].kategori);
        }
        file.close();
    }
}

// ====================================================================

bool cekLogin(string user, string pass){
    for(int i=0; i<jmlhadmins; i++){
        if(admins[i].username == user && admins[i].password == pass){
            return true;
        }
    }
    return false;
}

bool login(){
    string username, password;
    int coba = 0;
    while (coba < 3){
        cout << "LOGIN ADMIN PERPUSTAKAAN\n";
        cout << "==========================\n";
        cout << "Input username: ";
        cin >> username;
        cout << "Input password: ";
        cin >> password;

        if(cekLogin(username, password)){
            cout << "Yayy, login berhasil!\n";
            cin.ignore(); // Bersihkan sisa enter login agar menu utama aman
            return true;
        } else{
            coba++;
            cout << "Login anda gagal! (Sisa "<< 3 - coba << ")\n";
        }
    }
    cout << "Anda gagal login 3x. Program keluar\n";
    return false;
}

// ===== REVISI 1: INPUT BUKU BANYAK DATA, VALIDASI KETAT & SKIP HARGA ARSIP NEGARA =====
void inputBuku() {
    int jumlahInput;
    cout << "\n=== INPUT DATA BUKU ===\n";
    cout << "Mau input berapa data buku? : ";
    cin >> jumlahInput;
    cin.ignore(); // Bersihkan buffer enter dari jumlahInput agar perulangan lancar

    for (int k = 0; k < jumlahInput; k++) {
        if (jumlahBuku >= 100) {
            cout << "Gagal: Memori penyimpanan buku sudah penuh!\n";
            break;
        }
        
        cout << "\nData Buku ke-" << k + 1 << ":\n";
        cout << "Nama Buku : ";
        getline(cin, daftarBuku[jumlahBuku].nama);

        // Validasi ID agar tidak duplikat dengan yang sudah ada
        int tempID;
        while (true) {
            bool idDuplikat = false;
            cout << "ID Buku   : ";
            cin >> tempID;
            
            for (int i = 0; i < jumlahBuku; i++) {
                if (daftarBuku[i].id == tempID) {
                    idDuplikat = true;
                    break;
                }
            }
            if (idDuplikat) {
                cout << "-> ID sudah digunakan! Silakan masukkan ID lain.\n";
            } else {
                daftarBuku[jumlahBuku].id = tempID;
                cin.ignore(); // Bersihkan buffer enter setelah input ID
                break;
            }
        }

        // Validasi Kategori Khusus
        string inputKat;
        string katLower;
        while (true) {
            cout << "Kategori (novel, self improvement, bisnis, biografi, arsip negara): ";
            getline(cin, inputKat);
            katLower = toLowerCase(inputKat);

            if (katLower == "novel" || katLower == "self improvement" || katLower == "bisnis" || katLower == "biografi") {
                daftarBuku[jumlahBuku].kategori = inputKat; // Format asli ketikan user tetap disimpan utuh
                break;
            } else if (katLower == "arsip negara") {
                if (adaArsipNegara) {
                    cout << "-> Kategori 'arsip negara' hanya bisa diinput 1x! Silakan masukkan kategori lain.\n";
                } else {
                    daftarBuku[jumlahBuku].kategori = inputKat;
                    adaArsipNegara = true;
                    break;
                }
            } else {
                cout << "-> Kategori tidak valid/tidak tersedia! Silakan coba lagi.\n";
            }
        }

        // Logika Pengisian Harga Buku
        if (katLower == "arsip negara") {
            daftarBuku[jumlahBuku].harga = 0; // Otomatis gratis/0 untuk arsip negara
            cout << "Harga Buku: 0 (Otomatis digratiskan karena merupakan Arsip Negara)\n";
        } else {
            cout << "Harga Buku: ";
            cin >> daftarBuku[jumlahBuku].harga;
            cin.ignore(); // Bersihkan buffer setelah cin >> harga
        }

        jumlahBuku++;
        cout << "Buku berhasil ditambahkan!\n";
    }
    simpanKeFile(); // <-- UPDATE: Simpan otomatis setelah selesai input semua buku
    konfirmasiKembali();
}

// ===== REVISI 2: OUTPUT BERDASARKAN HARGA BUKU =====
void outputBuku(){
    if(jumlahBuku == 0) {
        cout << "Belum ada data bukunya!\n";
        konfirmasiKembali();
        return;
    }

    int pilih;
    cout << "Tampil data berdasarkan HARGA secara:\n";
    cout << "1. Ascending (Termurah -> Termahal)\n";
    cout << "2. Descending (Termahal -> Termurah)\n";
    cout << "Pilihlah: ";
    cin >> pilih;

    if(pilih != 1 && pilih != 2){
        cout << "Pilihan tidak tersedia!\n";
        konfirmasiKembali();
        return;
    }

    Buku temp[100];
    for(int i=0; i<jumlahBuku; i++) {
        temp[i] = daftarBuku[i];
    }

    // Proses Bubble Sort berdasarkan Harga Buku
    for(int i=0; i<jumlahBuku - 1; i++) {
        for(int j=0; j<jumlahBuku - i - 1; j++) {
            if(pilih == 1){
                if(temp[j].harga > temp[j+1].harga) {
                    swap(temp[j], temp[j+1]);
                }
            } else {
                if(temp[j].harga < temp[j+1].harga) {
                    swap(temp[j], temp[j+1]);
                }
            }
        }
    }

    cout << "\n==== DATA BUKU KESELURUHAN (BERDASARKAN HARGA) ====\n";
    for(int i=0; i<jumlahBuku; i++){
        cout << "Nama    : " << temp[i].nama << endl;
        cout << "ID      : " << temp[i].id << endl;
        cout << "Harga   : " << temp[i].harga << endl;
        cout << "Kategori: " << temp[i].kategori << endl;
        cout << "-------------------------\n";
    }
    konfirmasiKembali();
}

// ===== REVISI 3: SORTING BY NAMA / ID, CETAK KE LAYAR & KE FILE =====
void sortFile(){
    if(jumlahBuku == 0) {
        cout << "Data masih kosong!\n";
        konfirmasiKembali();
        return;
    }

    int opsiSort;
    cout << "Urutkan data secara Ascending berdasarkan:\n";
    cout << "1. Nama Buku\n";
    cout << "2. ID Buku\n";
    cout << "Pilihan: ";
    cin >> opsiSort;

    if(opsiSort != 1 && opsiSort != 2) {
        cout << "Pilihan tidak valid!\n";
        konfirmasiKembali();
        return;
    }

    Buku temp[100];
    for (int i = 0; i < jumlahBuku; i++) {
        temp[i] = daftarBuku[i];
    }

    // Proses Algoritma Sorting
    for (int i = 0; i < jumlahBuku - 1; i++) {
        for (int j = 0; j < jumlahBuku - i - 1; j++) {
            if (opsiSort == 1) { // Berdasarkan Nama
                if (toLowerCase(temp[j].nama) > toLowerCase(temp[j+1].nama)) {
                    swap(temp[j], temp[j+1]);
                }
            } else { // Berdasarkan ID
                if (temp[j].id > temp[j+1].id) {
                    swap(temp[j], temp[j+1]);
                }
            }
        }
    }

    // Tampilkan data hasil urutan ke layar hitam (console)
    cout << "\n==== HASIL SORTING DATA ====\n";
    for (int i = 0; i < jumlahBuku; i++) {
        cout << "Nama    : " << temp[i].nama << endl;
        cout << "ID      : " << temp[i].id << endl;
        cout << "Harga   : " << temp[i].harga << endl;
        cout << "Kategori: " << temp[i].kategori << endl;
        cout << "-------------------------\n";
    }

    // Tulis dan ekspor otomatis hasil urutan ke dalam berkas text eksternal
    ofstream file("sorted_buku.txt");
    file << "=== DATA BUKU TERURUT ===\n";
    for (int i = 0; i < jumlahBuku; i++) {
        file << temp[i].nama << " | "
             << temp[i].id << " | "
             << temp[i].harga << " | "
             << temp[i].kategori << endl;
    }
    file.close();
    cout << "Data berhasil diurutkan & disimpan ke dalam file 'sorted_buku.txt'\n";
    konfirmasiKembali();
}

// ===== REVISI 4: SEARCH BY NAMA / ID (CASE-INSENSITIVE) =====
void searchingBuku(){
    if(jumlahBuku == 0){
        cout << "Data buku masih kosong!\n";
        konfirmasiKembali();
        return;
    }

    int pilih;
    bool ditemukan = false;

    cout << "\n=== SEARCHING BUKU ===\n";
    cout << "1. Search by Nama Buku\n";
    cout << "2. Search by ID Buku\n";
    cout << "Pilih: ";
    cin >> pilih;

    if(pilih == 1){
        string cariNama;
        cin.ignore();
        cout << "Masukkan nama buku: ";
        getline(cin, cariNama);
        
        for(int i = 0; i < jumlahBuku; i++){
            if(toLowerCase(daftarBuku[i].nama) == toLowerCase(cariNama)){
                cout << "\n=== DATA DITEMUKAN ===\n";
                cout << "Nama     : " << daftarBuku[i].nama << endl;
                cout << "ID       : " << daftarBuku[i].id << endl;
                cout << "Harga    : " << daftarBuku[i].harga << endl;
                cout << "Kategori : " << daftarBuku[i].kategori << endl;
                ditemukan = true;
                break;
            }
        }
    }
    else if(pilih == 2){
        int cariID;
        cout << "Masukkan ID buku: ";
        cin >> cariID;

        for(int i = 0; i < jumlahBuku; i++){
            if(daftarBuku[i].id == cariID){
                cout << "\n=== DATA DITEMUKAN ===\n";
                cout << "Nama     : " << daftarBuku[i].nama << endl;
                cout << "ID       : " << daftarBuku[i].id << endl;
                cout << "Harga    : " << daftarBuku[i].harga << endl;
                cout << "Kategori : " << daftarBuku[i].kategori << endl;
                ditemukan = true;
                break;
            }
        }
    }
    else{
        cout << "Pilihan tidak valid!\n";
        konfirmasiKembali();
        return;
    }

    if(!ditemukan){
        cout << "Data tidak ditemukan!\n";
    }
    konfirmasiKembali();
}

// ===== REVISI 5: DELETE BY NAMA ONLY =====
void deleteBuku(){
    if(jumlahBuku == 0){
        cout << "Data buku masih kosong!\n";
        konfirmasiKembali();
        return;
    }

    string cariNama;
    bool ditemukan = false;
    cin.ignore();

    cout << "\n=== DELETE BUKU ===\n";
    cout << "Masukkan nama buku yang ingin dihapus: ";
    getline(cin, cariNama);

    for(int i = 0; i < jumlahBuku; i++){
        if(toLowerCase(daftarBuku[i].nama) == toLowerCase(cariNama)){
            if(toLowerCase(daftarBuku[i].kategori) == "arsip negara") {
                adaArsipNegara = false;
            }

            for(int j = i; j < jumlahBuku - 1; j++){
                daftarBuku[j] = daftarBuku[j + 1];
            }
            jumlahBuku--;

            cout << "Data berhasil dihapus!\n";
            ditemukan = true;
            simpanKeFile(); // <-- UPDATE: Simpan perubahan setelah data dihapus
            break;
        }
    }
    if(!ditemukan){
        cout << "Data tidak ditemukan!\n";
    }
    konfirmasiKembali();
}

// ===== REVISI 6: EDIT BY NAMA ONLY WITH RE-VALIDATION =====
void editBuku(){
    if(jumlahBuku == 0){
        cout << "Data buku masih kosong!\n";
        konfirmasiKembali();
        return;
    }

    string cariNama;
    bool ditemukan = false;
    cin.ignore();

    cout << "\n=== EDIT BUKU ===\n";
    cout << "Masukkan nama buku yang ingin diedit: ";
    getline(cin, cariNama);

    for(int i = 0; i < jumlahBuku; i++){
        if(toLowerCase(daftarBuku[i].nama) == toLowerCase(cariNama)){
            if(toLowerCase(daftarBuku[i].kategori) == "arsip negara") {
                adaArsipNegara = false;
            }

            cout << "\n=== INPUT DATA BARU ===\n";
            cout << "Nama Buku Baru: ";
            getline(cin, daftarBuku[i].nama);

            // Validasi ID Baru
            int tempID;
            while (true) {
                bool idDuplikat = false;
                cout << "ID Buku Baru  : ";
                cin >> tempID;
                
                for (int j = 0; j < jumlahBuku; j++) {
                    if (j != i && daftarBuku[j].id == tempID) { 
                        idDuplikat = true;
                        break;
                    }
                }
                if (idDuplikat) {
                    cout << "-> ID sudah digunakan! Silakan masukkan ID lain.\n";
                } else {
                    daftarBuku[i].id = tempID;
                    cin.ignore();
                    break;
                }
            }

            // Validasi Kategori Baru
            string inputKat;
            string katLower;
            while (true) {
                cout << "Kategori Baru (novel, self improvement, bisnis, biografi, arsip negara): ";
                getline(cin, inputKat);
                katLower = toLowerCase(inputKat);

                if (katLower == "novel" || katLower == "self improvement" || katLower == "bisnis" || katLower == "biografi") {
                    daftarBuku[i].kategori = inputKat;
                    break;
                } else if (katLower == "arsip negara") {
                    if (adaArsipNegara) {
                        cout << "-> Kategori 'arsip negara' hanya bisa digunakan oleh 1 buku! Gunakan kategori lain.\n";
                    } else {
                        daftarBuku[i].kategori = inputKat;
                        adaArsipNegara = true;
                        break;
                    }
                } else {
                    cout << "-> Kategori tidak valid! Silakan masukkan kategori yang sesuai ketentuan.\n";
                }
            }

            // Atur Harga Baru berdasarkan Kategori Baru
            if (katLower == "arsip negara") {
                daftarBuku[i].harga = 0;
                cout << "Harga Buku Baru: 0 (Otomatis digratiskan karena merupakan Arsip Negara)\n";
            } else {
                cout << "Harga Buku Baru: ";
                cin >> daftarBuku[i].harga;
                cin.ignore();
            }

            cout << "Data berhasil diedit!\n";
            ditemukan = true;
            simpanKeFile(); // <-- UPDATE: Simpan perubahan setelah data berhasil diedit
            break;
        }
    }
    if(!ditemukan){
        cout << "Data tidak ditemukan!\n";
    }
    konfirmasiKembali();
}

int main() {
    if (!login()){
        return 0;
    }

    bacaDariFile(); // <-- UPDATE: Otomatis membaca database lama sesaat setelah login berhasil

    int pilihan;
    do{
        cout << "\n=== MENU PERPUSTAKAAN ===\n";
        cout << "1. Input Buku\n";
        cout << "2. Output Buku\n";
        cout << "3. Sorting Buku\n";
        cout << "4. Searching Buku\n";
        cout << "5. Delete Buku\n";
        cout << "6. Edit Buku\n";
        cout << "7. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;
        
        switch (pilihan)
        {
        case 1:
            inputBuku();
            break;
        case 2:
            outputBuku();
            break;
        case 3:
            sortFile();
            break;
        case 4:
            searchingBuku();
            break;
        case 5:
            deleteBuku();
            break;
        case 6:
            editBuku();
            break;
        case 7: 
            cout << "Keluar...\n";
            break;
        default:
            cout << "Pilihan tidak valid!\n";
            konfirmasiKembali();
        }

    } while (pilihan != 7);
    return 0;
}