#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

const int MAX = 100;

class User {
public:
    string username;
    string nama;
    int nilai;

    User() : username(""), nama(""), nilai(0) {}
    User(string u, string n, int v) : username(u), nama(n), nilai(v) {}
};

User users[MAX];
int jumlahUser = 0;

bool login(string uname) {
    for (int i = 0; i < jumlahUser; i++) {
        if (users[i].username == uname) {
            cout << "Halo, " << users[i].nama << "!" << endl;
            return true;
        }
    }
    cout << "Username tidak ditemukan.\n";
    return false;
}

void bacaFile() {
    ifstream file("data.txt");
    if (!file) {
        cout << "Gagal membaca file!\n";
        return;
    }

    jumlahUser = 0;
    string uname, nama;
    int nilai;
    while (file >> uname >> nama >> nilai && jumlahUser < MAX) {
        users[jumlahUser++] = User(uname, nama, nilai);
    }
    file.close();
}

void simpanFile() {
    ofstream file("data.txt");
    for (int i = 0; i < jumlahUser; i++) {
        file << users[i].username << " " << users[i].nama << " " << users[i].nilai << endl;
    }
    file.close();
}

void bubbleSort() {
    for (int i = 0; i < jumlahUser - 1; i++) {
        for (int j = 0; j < jumlahUser - i - 1; j++) {
            if (users[j].nilai > users[j + 1].nilai) {
                swap(users[j], users[j + 1]);
            }
        }
    }
}

void cariNama(string namaCari) {
    bool ketemu = false;
    for (int i = 0; i < jumlahUser; i++) {
        if (users[i].nama == namaCari) {
            cout << "Ditemukan: " << users[i].username << " - " << users[i].nama << " - " << users[i].nilai << endl;
            ketemu = true;
        }
    }
    if (!ketemu) {
        cout << "Data tidak ditemukan.\n";
    }
}

void tampilkanSemua() {
    for (int i = 0; i < jumlahUser; i++) {
        cout << users[i].username << " - " << users[i].nama << " - " << users[i].nilai << endl;
    }
}

int main() {
    bacaFile(); 

    cout << "LOGIN\nMasukkan username: ";
    string uname;
    cin >> uname;

    if (!login(uname)) return 0;

    int pilihan;
    do {
        cout << "\n=== MENU ===\n";
        cout << "1. Tampilkan semua\n";
        cout << "2. Urutkan nilai \n";
        cout << "3. Cari nama\n";
        cout << "4. Tambah data\n";
        cout << "5. Simpan & Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            tampilkanSemua();
        } else if (pilihan == 2) {
            bubbleSort();
            cout << "Data telah diurutkan.\n";
        } else if (pilihan == 3) {
            string cari;
            cout << "Nama yang dicari: ";
            cin >> cari;
            cariNama(cari);
        } else if (pilihan == 4) {
            string u, n;
            int v;
            cout << "Username: "; cin >> u;
            cout << "Nama: "; cin >> n;
            cout << "Nilai: "; cin >> v;
            users[jumlahUser++] = User(u, n, v);
            cout << "Data ditambahkan.\n";
        }

    } while (pilihan != 5);

    simpanFile();
    cout << "Data disimpan. Keluar.\n";

    return 0;
}

