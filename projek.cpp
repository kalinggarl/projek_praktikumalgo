#include <iostream>
#include <fstream>
using namespace std;


struct admin{   
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
            return true;
        } else{
            coba++;
            cout << "Login anda gagal! (Sisa "<< 3 - coba << ")\n";
        }
    }
    cout << "Anda gagal login 3x. Program keluar\n";
    return false;
}
// ===== FUNCTION INPUT BUKU =====

void inputBuku() {

    cout << "\n=== INPUT DATA BUKU ===\n";
    cin.ignore();
    cout << "Nama Buku: ";
    getline(cin, daftarBuku[jumlahBuku].nama);
    cout << "ID Buku: ";
    cin >> daftarBuku[jumlahBuku].id;
    cout << "Harga Buku: ";
    cin >> daftarBuku[jumlahBuku].harga;
    cin.ignore();
    cout << "Kategori: ";
    getline(cin, daftarBuku[jumlahBuku].kategori);
    jumlahBuku++;
    cout << "Buku berhasil ditambahkan!\n";
}

// ==== OUTPUTNYA ==== //

void outputBuku(){
    if(jumlahBuku == 0) {
        cout << "Belum ada data bukunya!\n";
        return;
    }

    int pilih;
    cout << "Tampil data secara:\n";
    cout << "1. Ascending\n";
    cout << "2. Descending\n";
    cout << "Pilihlah: ";
    cin >> pilih;

    if(pilih != 1 && pilih != 2){
        cout << "Pilihan tidak tersedia!\n";
        return;
    }

    Buku temp[100];
    for(int i=0; i<jumlahBuku; i++) { //copy datanya
        temp[i] = daftarBuku[i];
    }
    for(int i=0; i<jumlahBuku - 1; i++) { //sorting
        for(int j=0; j<jumlahBuku - i - 1; j++) {
            if(pilih == 1){
                if(temp[j].nama > temp[j+1].nama) { //ascending
                    swap(temp[j], temp[j+1]);
                }
            } else {
                if(temp[j].nama < temp[j+1].nama) { //descending
                    swap(temp[j], temp[j+1]);
                }
            }
        }
    }
    cout << "\n==== DATA BUKU ====\n";
    for(int i=0; i<jumlahBuku; i++){
        cout << "Nama    : " << temp[i].nama <<endl;
        cout << "ID      : " << temp[i].id <<endl;
        cout << "Harga   : " << temp[i].harga <<endl;
        cout << "Kategori: " << temp[i].kategori <<endl;
    }
}
// === SORTFILE === //
void sortFile(){
    if(jumlahBuku == 0) {
        cout << "Data masih kosong!\n";
        return;
    }
    Buku temp[100];
    for (int i = 0; i < jumlahBuku; i++) { //copydata
        temp[i] = daftarBuku[i];
    }
    for (int i = 0; i < jumlahBuku - 1; i++) {
        for (int j = 0; j < jumlahBuku - i - 1; j++) {
            if (temp[j].nama > temp[j+1].nama) {
                swap(temp[j], temp[j+1]);
            }
        }
    }

     ofstream file("sorted_buku.txt");
     for (int i = 0; i < jumlahBuku; i++) {
        file << temp[i].nama << " | "
             << temp[i].id << " | "
             << temp[i].harga << " | "
             << temp[i].kategori << endl;
    }
     file.close();
     cout << "Data berhasil diurutkan & disimpan\n";
}

void searchingBuku(){

    if(jumlahBuku == 0){
        cout << "Data buku masih kosong!\n";
        return;
    }

    int pilih;
    bool ditemukan = false;

    cout << "\n=== SEARCHING BUKU ===\n";
    cout << "1. Search by Nama Buku\n";
    cout << "2. Search by ID Buku\n";
    cout << "Pilih: ";
    cin >> pilih;

    // ===== SEARCH BY NAMA =====
    if(pilih == 1){

        string cariNama;

        cin.ignore();

        cout << "Masukkan nama buku: ";
        getline(cin, cariNama);
        for(int i = 0; i < jumlahBuku; i++){

            if(daftarBuku[i].nama == cariNama){

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

 // ===== SEARCH BY ID =====
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

// ===== PILIHAN TIDAK VALID =====
    else{
        cout << "Pilihan tidak valid!\n";
        return;
    }

    // ===== DATA TIDAK DITEMUKAN =====
    if(!ditemukan){
        cout << "Data tidak ditemukan!\n";
    }
}

// ================= DELETE BUKU =================
void deleteBuku(){
    if(jumlahBuku == 0){
        cout << "Data buku masih kosong!\n";
        return;
    }

    string cariNama;
    bool ditemukan = false;

    cin.ignore();

    cout << "\n=== DELETE BUKU ===\n";
    cout << "Masukkan nama buku yang ingin dihapus: ";
    getline(cin, cariNama);

    for(int i = 0; i < jumlahBuku; i++){
        if(daftarBuku[i].nama == cariNama){
            // geser array
            for(int j = i; j < jumlahBuku - 1; j++){
                daftarBuku[j] = daftarBuku[j + 1];
            }
            jumlahBuku--;

            cout << "Data berhasil dihapus!\n";
            ditemukan = true;
            break;
        }
    }
    if(!ditemukan){
        cout << "Data tidak ditemukan!\n";
    }
}

// ================= EDIT BUKU =================
void editBuku(){
    if(jumlahBuku == 0){
        cout << "Data buku masih kosong!\n";
        return;
    }

    string cariNama;
    bool ditemukan = false;
    cin.ignore();

    cout << "\n=== EDIT BUKU ===\n";
    cout << "Masukkan nama buku yang ingin diedit: ";
    getline(cin, cariNama);

    for(int i = 0; i < jumlahBuku; i++){
        if(daftarBuku[i].nama == cariNama){
            cout << "\n=== INPUT DATA BARU ===\n";

            cout << "Nama Buku Baru: ";
            getline(cin, daftarBuku[i].nama);

            cout << "ID Buku Baru: ";
            cin >> daftarBuku[i].id;

            cout << "Harga Buku Baru: ";
            cin >> daftarBuku[i].harga;

            cin.ignore();

            cout << "Kategori Baru: ";
            getline(cin, daftarBuku[i].kategori);

            cout << "Data berhasil diedit!\n";

            ditemukan = true;
            break;
        }
    }
    if(!ditemukan){
        cout << "Data tidak ditemukan!\n";
    }
}

int main() {

    if (!login()){
        return 0;
    }

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
            deleteBuku();
            break;
        case 7: 
            cout << "Keluar...\n";
            break;
        default:
            cout << "Pilihan tidak valid!\n";
        }

    } while (pilihan != 7);
    return 0;
}
