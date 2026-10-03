#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

const int MAX_MHS = 50;
const float BOBOT_TUGAS = 0.30f;
const float BOBOT_UTS   = 0.30f;
const float BOBOT_UAS   = 0.40f;
const float BATAS_LULUS = 60.0f;

struct Mahasiswa {
    string nama;
    string nim;
    float tugas;
    float uts;
    float uas;
    float nilaiAkhir;
    char grade;
};

float bacaNilai(const string& label);
float hitungNilaiAkhir(float tugas, float uts, float uas);
char konversiGrade(float nilai);
void tambahMahasiswa(Mahasiswa data[], int& jumlah);
void tampilkanData(const Mahasiswa data[], int jumlah);
void cariMahasiswa(const Mahasiswa data[], int jumlah);
void tampilkanRataRata(const Mahasiswa data[], int jumlah);
void tampilkanTertinggiTerendah(const Mahasiswa data[], int jumlah);

int cariIndexRekursif(const Mahasiswa data[], int jumlah, const string& nim, int i = 0);
float jumlahNilaiRekursif(const Mahasiswa data[], int n);
int indexTertinggiRekursif(const Mahasiswa data[], int n);
int indexTerendahRekursif(const Mahasiswa data[], int n);


float bacaNilai(const string& label) {
    float nilai;
    while (true) {
        cout << label;
        if (!(cin >> nilai)) {            
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Input harus angka!\n";
            continue;
        }
        if (nilai < 0 || nilai > 100) {   
            cout << "  Nilai harus antara 0 sampai 100!\n";
            continue;
        }
        return nilai;
    }
}

float hitungNilaiAkhir(float tugas, float uts, float uas) {
    return tugas * BOBOT_TUGAS + uts * BOBOT_UTS + uas * BOBOT_UAS;
}


char konversiGrade(float nilai) {
    int kategori = (int)(nilai / 10);   
    switch (kategori) {
        case 10:
        case 9:
        case 8:  return 'A';
        case 7:  return 'B';
        case 6:  return 'C';
        case 5:  return 'D';
        default: return 'E';
    }
}

void tambahMahasiswa(Mahasiswa data[], int& jumlah) {
    if (jumlah >= MAX_MHS) {
        cout << "Data penuh! Maksimal " << MAX_MHS << " mahasiswa.\n";
        return;
    }

    Mahasiswa m;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Nama  : ";
    getline(cin, m.nama);
    cout << "NIM   : ";
    getline(cin, m.nim);

    if (cariIndexRekursif(data, jumlah, m.nim) != -1) {
        cout << "NIM sudah terdaftar!\n";
        return;
    }

    m.tugas = bacaNilai("Nilai Tugas : ");
    m.uts   = bacaNilai("Nilai UTS   : ");
    m.uas   = bacaNilai("Nilai UAS   : ");

    m.nilaiAkhir = hitungNilaiAkhir(m.tugas, m.uts, m.uas);
    m.grade      = konversiGrade(m.nilaiAkhir);

    data[jumlah] = m;
    jumlah++;

    cout << "\nData tersimpan. Nilai akhir: " << fixed << setprecision(2)
         << m.nilaiAkhir << " (" << m.grade << ") - ";
    if (m.nilaiAkhir >= BATAS_LULUS) {
        cout << "LULUS\n";
    } else {
        cout << "TIDAK LULUS\n";
    }
}

void tampilkanData(const Mahasiswa data[], int jumlah) {
    if (jumlah == 0) {
        cout << "Belum ada data mahasiswa.\n";
        return;
    }

    cout << "\n" << left
         << setw(4)  << "No"
         << setw(20) << "Nama"
         << setw(12) << "NIM"
         << setw(8)  << "Tugas"
         << setw(8)  << "UTS"
         << setw(8)  << "UAS"
         << setw(10) << "Akhir"
         << setw(7)  << "Grade"
         << "Status\n";
    cout << string(87, '-') << "\n";

    cout << fixed << setprecision(2);
    for (int i = 0; i < jumlah; i++) {
        cout << left
             << setw(4)  << i + 1
             << setw(20) << data[i].nama
             << setw(12) << data[i].nim
             << setw(8)  << data[i].tugas
             << setw(8)  << data[i].uts
             << setw(8)  << data[i].uas
             << setw(10) << data[i].nilaiAkhir
             << setw(7)  << data[i].grade
             << (data[i].nilaiAkhir >= BATAS_LULUS ? "Lulus" : "Tidak Lulus")
             << "\n";
    }
}

void cariMahasiswa(const Mahasiswa data[], int jumlah) {
    string nim;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Masukkan NIM yang dicari: ";
    getline(cin, nim);

    int ditemukan = -1;
    for (int i = 0; i < jumlah; i++) {
        if (data[i].nim == nim) {
            ditemukan = i;
            break;
        }
    }

    if (ditemukan == -1) {
        cout << "[Iteratif] Mahasiswa tidak ditemukan.\n";
    } else {
        cout << "[Iteratif] Ditemukan: " << data[ditemukan].nama
             << " | Nilai akhir " << fixed << setprecision(2)
             << data[ditemukan].nilaiAkhir << " (" << data[ditemukan].grade << ")\n";
    }

    int idx = cariIndexRekursif(data, jumlah, nim);
    if (idx == -1) {
        cout << "[Rekursif] Mahasiswa tidak ditemukan.\n";
    } else {
        cout << "[Rekursif] Ditemukan di indeks ke-" << idx << ": " << data[idx].nama << "\n";
    }
}

void tampilkanRataRata(const Mahasiswa data[], int jumlah) {
    if (jumlah == 0) {
        cout << "Belum ada data mahasiswa.\n";
        return;
    }
    float total = jumlahNilaiRekursif(data, jumlah);
    float rata  = total / (float)jumlah;

    cout << fixed << setprecision(2);
    cout << "Jumlah nilai akhir : " << total << "\n";
    cout << "Jumlah mahasiswa   : " << jumlah << "\n";
    cout << "Rata-rata kelas    : " << rata << "\n";
}

void tampilkanTertinggiTerendah(const Mahasiswa data[], int jumlah) {
    if (jumlah == 0) {
        cout << "Belum ada data mahasiswa.\n";
        return;
    }
    int tinggi = indexTertinggiRekursif(data, jumlah);
    int rendah = indexTerendahRekursif(data, jumlah);

    cout << fixed << setprecision(2);
    cout << "Nilai tertinggi : " << data[tinggi].nama << " (" << data[tinggi].nilaiAkhir << ")\n";
    cout << "Nilai terendah  : " << data[rendah].nama << " (" << data[rendah].nilaiAkhir << ")\n";
}


int cariIndexRekursif(const Mahasiswa data[], int jumlah, const string& nim, int i) {
    if (i >= jumlah) return -1;              
    if (data[i].nim == nim) return i;        
    return cariIndexRekursif(data, jumlah, nim, i + 1);
}

float jumlahNilaiRekursif(const Mahasiswa data[], int n) {
    if (n == 0) return 0;                    // basis
    return data[n - 1].nilaiAkhir + jumlahNilaiRekursif(data, n - 1);
}

int indexTertinggiRekursif(const Mahasiswa data[], int n) {
    if (n == 1) return 0;                    // basis
    int idx = indexTertinggiRekursif(data, n - 1);
    return (data[n - 1].nilaiAkhir > data[idx].nilaiAkhir) ? n - 1 : idx;
}

int indexTerendahRekursif(const Mahasiswa data[], int n) {
    if (n == 1) return 0;                    // basis
    int idx = indexTerendahRekursif(data, n - 1);
    return (data[n - 1].nilaiAkhir < data[idx].nilaiAkhir) ? n - 1 : idx;
}

int main() {
    Mahasiswa data[MAX_MHS];   
    int jumlah = 0;
    int pilihan;

    do {
        cout << "\n===== PENGELOLAAN NILAI MAHASISWA =====\n";
        cout << "1. Tambah mahasiswa\n";
        cout << "2. Tampilkan tabel nilai\n";
        cout << "3. Cari mahasiswa berdasarkan NIM\n";
        cout << "4. Rata-rata kelas\n";
        cout << "5. Nilai tertinggi dan terendah\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";

        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input harus angka!\n";
            pilihan = -1;
            continue;   
        }

        switch (pilihan) {
            case 1: tambahMahasiswa(data, jumlah);          break;
            case 2: tampilkanData(data, jumlah);            break;
            case 3: cariMahasiswa(data, jumlah);            break;
            case 4: tampilkanRataRata(data, jumlah);        break;
            case 5: tampilkanTertinggiTerendah(data, jumlah); break;
            case 0: cout << "Terima kasih!\n";              break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 0);

    return 0;
}