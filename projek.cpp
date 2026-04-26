#include <iostream>
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



int main() {

    if (!login())
    {

        return 0;
    }

    int pilihan;
    do{
        cout << "\n=== MENU PERPUSTAKAAN ===\n";
        cout << "1. Input Buku\n";
        cout << "2. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;
        switch (pilihan)
        {
        case 1:
            inputBuku();
            break;
        case 2:
            cout << "Keluar...\n";
            break;
        default:
            cout << "Pilihan tidak valid!\n";
        }

    } while (pilihan != 2);


    return 0;
}
