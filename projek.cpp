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
        cout << "4. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;
        switch (pilihan)
        {
        case 1:
            inputBuku();
            break;
        case 2:
            ouputBuku();
            break;
        case 3:
            sortFile();
            break;
        case 4:
            cout << "Keluar...\n";
            break;
        default:
            cout << "Pilihan tidak valid!\n";
        }

    } while (pilihan != 4);
    return 0;
}
