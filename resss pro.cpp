#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>  // untuk system("cls")
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

// Fungsi membaca data dari file
void bacaFile() {
    ifstream file("data.txt");
    if (!file) {
        cout << "Gagal membaca file atau file belum dibuat.\n";
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

// Fungsi menyimpan data ke file
void simpanFile() {
    ofstream file("data.txt");
    for (int i = 0; i < jumlahUser; i++) {
        file << users[i].username << " " << users[i].nama << " " << users[i].nilai << endl;
    }
    file.close();
    cout << "? Data telah disimpan ke file.\n";
}

// Fungsi bubble sort berdasarkan nilai
void bubbleSort() {
    for (int i = 0; i < jumlahUser - 1; i++) {
        for (int j = 0; j < jumlahUser - i - 1; j++) {
            if (users[j].nilai > users[j + 1].nilai) {
                swap(users[j], users[j + 1]);
            }
        }
    }
    cout << "? Data berhasil diurutkan berdasarkan nilai.\n";
}

// Fungsi searching berdasarkan nama
void cariNama(string namaCari) {
    bool ketemu = false;
    for (int i = 0; i < jumlahUser; i++) {
        if (users[i].nama == namaCari) {
            cout << "?? Ditemukan: " << users[i].username << " - " << users[i].nama << " - " << users[i].nilai << endl;
            ketemu = true;
        }
    }
    if (!ketemu) {
        cout << "? Data tidak ditemukan.\n";
    }
}

// Menampilkan semua data
void tampilkanData() {
    if (jumlahUser == 0) {
        cout << "?? Belum ada data.\n";
        return;
    }

    cout << "?? Data Pengguna:\n";
    for (int i = 0; i < jumlahUser; i++) {
        cout << i + 1 << ". " << users[i].username << " - " << users[i].nama << " - " << users[i].nilai << endl;
    }
}

// Tambah data baru
void tambahData() {
    if (jumlahUser >= MAX) {
        cout << "?? Data sudah penuh.\n";
        return;
    }

    string u, n;
    int v;
    cout << "Masukkan username: ";
    cin >> u;
    cin.ignore(); // Untuk menangkap newline setelah username
    cout << "Masukkan nama lengkap: ";
    getline(cin, n);
    cout << "Masukkan nilai: ";
    while (!(cin >> v)) {
        cout << "? Input nilai harus angka! Masukkan ulang: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    users[jumlahUser++] = User(u, n, v);
    cout << "? Data berhasil ditambahkan.\n";
}

int main() {
    bacaFile();

    int pilihan;
    do {
        cout << "\nTekan Enter untuk melanjutkan...";
        cin.ignore();
        cin.get();
        system("cls");

        cout << "=== APLIKASI DATA MAHASISWA ===\n";
        cout << "1. Tampilkan Data\n";
        cout << "2. Tambah Data\n";
        cout << "3. Urutkan Nilai (Bubble Sort)\n";
        cout << "4. Cari Berdasarkan Nama\n";
        cout << "5. Simpan dan Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;

        cin.ignore(); // untuk membersihkan newline

        switch (pilihan) {
        case 1:
            tampilkanData();
            break;
        case 2:
            tambahData();
            break;
        case 3:
            bubbleSort();
            break;
        case 4: {
            string cari;
            cout << "Masukkan nama yang dicari: ";
            getline(cin, cari);
            cariNama(cari);
            break;
        }
        case 5:
            simpanFile();
            cout << "?? Terima kasih, keluar dari program.\n";
            break;
        default:
            cout << "? Pilihan tidak valid.\n";
        }

    } while (pilihan != 5);

    return 0;
}

