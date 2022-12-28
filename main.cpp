#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <limits>

using namespace std;

// daftar variable yang digunakan untuk menginput ke database

struct daftarKontak {
  int id;
  string nomor;
  string nama;
  string alamat;
  string email;
};

// variable yang digunakan

string konfirmasiPembuatanDatabase, konfirmasiMembukaAplikasi, konfirmasiKontakBaruKembali, namaMenu, listAllContact, outputContact, buffer1;
bool konfirmasiMembukaMenu;

// inisialisai fungsi yang telah dibuat

void writeDatabase(fstream &database, daftarKontak &inputNewContact);
void showAllContact(fstream &databaseContact);
int getDataSize(fstream &database);
void addContact(fstream &databaseContact);
int getOption();
void checkdbContact(fstream &databaseContact);
void checkdbUser(fstream &databaseUser);

// Program berjalan pada fungsi utama (int main())

int main() {

  // membuka databse yang memuat data kontak dan data user login

  fstream databaseContact;
  fstream databaseUser;

  checkdbContact(databaseContact);

  if (konfirmasiMembukaMenu == true) {

    checkdbUser(databaseUser); 

    label_startProgram:

    int pilihanProgram = getOption();
    char is_continue;

    enum option {CREATE = 1, READ = 2, UPDATE = 3, DELETE = 4, FINISH = 0};

    // while (pilihanProgram != FINISH) {

    switch (pilihanProgram) {

      case CREATE :
        databaseContact.close();
        system("cls");
        databaseContact.open("databaseContact.bin", ios::out | ios::in | ios::binary);
        addContact(databaseContact);
        goto label_startProgram;
      break;

      case READ :
        databaseContact.close();
        system("cls");
        databaseContact.open("databaseContact.bin", ios::out | ios::in | ios::binary);
        showAllContact(databaseContact);
        outputContact = '\0';
        goto label_startProgram;
      break;

      case UPDATE :

      break;

      case DELETE :

      break;

      case FINISH :

        label_continue:

        cout << " Lanjutkan program ? (y/n) : "; cin >> is_continue;

        if ((is_continue == 'y') | (is_continue == 'Y')) {
          goto label_startProgram;
        } else if ( (is_continue == 'n') | (is_continue == 'N')) {
          break;
        } else {
          goto label_continue;
        }

      break;

      default :
      
      break;

    }

    cout << " Lanjutkan program ? (y/n) : "; cin >> is_continue;
    
    if ((is_continue == 'y') | (is_continue == 'Y')) {
      goto label_startProgram;
    } else if ((is_continue == 'n') | (is_continue == 'N')) {

    }
  } 

  system("color 8");

  cout << "=========================================================" << endl;
  cout << "----------- PROGRAM APLIKASI KONTAK SELESAI ------------ " << endl;
  cout << "=========================================================" << endl << endl;

  cout << " source code by : Kelompok UAS Teknologi Rekayasa Instrumentasi dan kontrol"; cout << endl;
  cout << " Daftar anggota : Mas Ridho, Mas Ferhad, Faizahel" << endl;

  return 0;
}

// Fungsi-Fungsi yang dibuat untuk program ini

void writeDatabase(fstream &database, daftarKontak &inputNewContact) {

  // memasukkan daftar kontak ke dalam database
  
  database << "ID      : " << inputNewContact.id << endl;
  database << "Nomor   : " << inputNewContact.nomor << endl;
  database << "Nama    : " << inputNewContact.nama << endl;
  database << "Alamat  : " << inputNewContact.alamat << endl;
  database << "Email   : " << inputNewContact.email << endl << endl;
}
void showAllContact(fstream &databaseContact) {

  cout << "=========================================================" << endl;
  cout << "--------------  APLIKASI KONTAK SEDERHANA   -------------" << endl;
  cout << "=========================================================" << endl << endl;

  cout << "         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~         " << endl;
  cout << "        :       Menampilkan Daftar Kontak       :        " << endl;
  cout << "         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~         " << endl << endl;

  cout << "---------------------------------------------------------" << endl << endl;

  while (!databaseContact.eof()) {
    getline(databaseContact, listAllContact);
    outputContact.append("  " + listAllContact + "\n");
  }

  cout << outputContact;


}
int getDataSize(fstream &database) {

  // Digunkaan untuk menambahkan ID dengan urut

  int start, end;
  database.seekg(0, ios::beg);
  start = database.tellg();
  database.seekg(0, ios::end);
  end = database. tellg();

  return (end-start) / sizeof(daftarKontak);
}
void addContact(fstream &databaseContact) {

  label_MenambahKontakbaru:

  daftarKontak inputNewContact, lastContact;

  int size = getDataSize(databaseContact);
  inputNewContact.id = ((size / 2) + 1); // ID secara otomatis terbuat

  cout << "=========================================================" << endl;
  cout << "--------------  APLIKASI KONTAK SEDERHANA   -------------" << endl;
  cout << "=========================================================" << endl << endl;

  cout << "         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~         " << endl;
  cout << "        :         Menambah Kontak Baru          :        " << endl;
  cout << "         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~         " << endl << endl;

  cout << "---------------------------------------------------------" << endl << endl;


  cout << "  =>  Nomor   :  "; getline(cin, inputNewContact.nomor);
  cout << "  =>  Nama    :  "; getline(cin, inputNewContact.nama);
  cout << "  =>  Alamat  :  "; getline(cin, inputNewContact.alamat);
  cout << "  =>  Email   :  "; getline(cin, inputNewContact.email);

  cout << endl;
  cout << "=========================================================" << endl;
  cout << "  Kontak [ " << inputNewContact.nama << " ] berhasil ditambahkan " << endl;
  cout << "=========================================================" << endl << endl;

  // memasukkan data kontak baru kedalam database

  writeDatabase(databaseContact, inputNewContact);

  label_konfirmasiKontakBaru:

  cout << "  Menambahkan kontak baru kembali (y/n) ?  :  "; cin >> konfirmasiKontakBaruKembali;

  cin.ignore(numeric_limits<streamsize>::max(),'\n' );


  if ((konfirmasiKontakBaruKembali == "y") | (konfirmasiKontakBaruKembali == "Y")) {
    system("cls");
    goto label_MenambahKontakbaru;
  } else if ((konfirmasiKontakBaruKembali == "n") | (konfirmasiKontakBaruKembali == "N")) {
    cout << endl;
    cout << "---------------------------------------------------------" << endl << endl;
    cout << "  =>  Press any key to menu . . .";
    getch();
  } else {
    cout << endl;
    cout << "=========================================================" << endl;
    cout << "  !!! Pilihan konfirmasi, yang anda masukkan salah . . . " << endl;
    cout << "=========================================================" << endl << endl;
    goto label_konfirmasiKontakBaru;
  }


  cout << endl << endl;

}
int getOption() {

  int pilihanMenu;

  system("cls");

    cout << "=========================================================" << endl;
    cout << "--------------  APLIKASI KONTAK SEDERHANA   -------------" << endl;
    cout << "=========================================================" << endl << endl;

    cout << "         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~         " << endl;
    cout << "        :             Menu Kontak               :        " << endl;
    cout << "         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~         " << endl << endl;

    cout << "         [1] Tambah Kontak Baru" << endl;
    cout << "         [2] Tampilkan Semua Kontak" << endl;
    cout << "         [3] Cari Kontak" << endl;
    cout << "         [4] Edit Kontak Yang Sudah Ada" << endl;
    cout << "         [0] keluar" << endl << endl;

    cout << "=========================================================" << endl << endl;
    cout << "  Masukkan pilihan Menu  :  "; cin >> pilihanMenu; 
    cout << endl;
    cout << "=========================================================" << endl << endl;

    cin.ignore(numeric_limits<streamsize>::max(),'\n' );
    return pilihanMenu;
}
void checkdbContact(fstream &databaseContact) {

  databaseContact.open("databaseContact.bin", ios::out | ios::in | ios::binary);

  // memberikan notifikasi apakah database ditemukan
  if (!databaseContact) {
    system("color 4");

    cout << "=========================================================" << endl;
    cout << "--------------  APLIKASI KONTAK SEDERHANA   -------------" << endl;
    cout << "=========================================================" << endl << endl;

    cout << "         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~         " << endl;
    cout << "        :      [ Database tidak ditemukan ]     :        " << endl;
    cout << "         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~         " << endl << endl;

    cout << "=========================================================" << endl;
    cout << "  !!!  PERHATIAN ... [ Database tidak ditemukan ] ," << endl;
    cout << "=========================================================" << endl << endl;

    label_konfirmasi:

    cout << "   =>  Izinkan program membuat Database (y/n) ?  :  "; cin >> konfirmasiPembuatanDatabase;
    cout << endl << endl;
    cout << "---------------------------------------------------------" << endl << endl << endl;

    if ((konfirmasiPembuatanDatabase == "y") | (konfirmasiPembuatanDatabase == "Y")) {
      system("cls");
      system("color a");

      databaseContact.close(); // penutupan database terlebih dahulu
      databaseContact.open("databaseContact.bin", ios::trunc | ios::out | ios::in | ios::binary); // pembukaan databse baru

      cout << "=========================================================" << endl;
      cout << "--------------  APLIKASI KONTAK SEDERHANA   -------------" << endl;
      cout << "=========================================================" << endl << endl;

      cout << "         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~         " << endl;
      cout << "        :   [ Database : databaseContact.bin ]  :        " << endl;
      cout << "         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~         " << endl << endl;

      cout << "=========================================================" << endl;
      cout << "  OK Database telah berhasil dibuat . . . " << endl;
      cout << "=========================================================" << endl << endl;
      cout << "  =>  Press any key to menu . . .";

      konfirmasiMembukaMenu = true;

      getch();

    } else if ((konfirmasiPembuatanDatabase == "n") | (konfirmasiPembuatanDatabase == "N")) {
      cout << "=========================================================" << endl;
      cout << "  !!! Mohon maaf atas ketidaknyamananya , " << endl;
      cout << "  ->  program tidak dapat berjalan tanpa Database " << endl;
      cout << "=========================================================" << endl << endl;

      konfirmasiMembukaMenu = false;

    } else {
      cout << "=========================================================" << endl;
      cout << "  !!! Pilihan konfirmasi, yang anda masukkan salah . . . " << endl;
      cout << "=========================================================" << endl << endl;
      goto label_konfirmasi;
    }
  } else {
    konfirmasiMembukaMenu = true;
  }
}
void checkdbUser(fstream &databaseUser) {

  databaseUser.open("databaseUser.bin", ios::out | ios::in | ios::binary);

  // memberikan notifikasi apakah database ditemukan

  if (!databaseUser) {
    system("cls");
    system("color a");

    databaseUser.close(); // penutupan database terlebih dahulu
    databaseUser.open("databaseUser.bin", ios::trunc | ios::out | ios::in | ios::binary); // pembukaan databse baru

    string username, password;

    cout << "=========================================================" << endl;
    cout << "--------------  APLIKASI KONTAK SEDERHANA   -------------" << endl;
    cout << "=========================================================" << endl << endl;

    cout << "         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~         " << endl;
    cout << "        :         REGISTRASI USER BARU          :        " << endl;
    cout << "         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~         " << endl << endl;

    cout << "---------------------------------------------------------" << endl << endl;

    cout << "  =>  Username baru  :  "; cin >> username;
    cout << "  =>  Password baru  :  "; cin >> password;


    // memasukkan data user login ke dalam databse

    databaseUser << username << endl;
    databaseUser << password << endl;
    cin.ignore();

    // animasi loading 

    int i = 0; 
    char load[26]; 

    system("cls");
    system("color 9");


    while(i < 25) { 
      system("cls"); 

      load[i++] = '#'; 
      load[i] = '\0'; 
      cout <<"\n\n\n\n\t\tLOADING " << i*4 << " %";
      printf("\n\n\t\t[%-25s]", load);
      usleep(50000); 
    } 

    system("color e");

  } else {
    system("cls");

    string user, pass, dbUser, dbPass;

    cout << "=========================================================" << endl;
    cout << "--------------  APLIKASI KONTAK SEDERHANA   -------------" << endl;
    cout << "=========================================================" << endl << endl;

    cout << "         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~         " << endl;
    cout << "        :            LOGIN USER PAGE            :        " << endl;
    cout << "         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~         " << endl << endl;

    cout << "---------------------------------------------------------" << endl << endl;

    getline(databaseUser, dbUser);
    getline(databaseUser, dbPass);

    user:

    cout << "  =>  Username  :  "; cin >> user;

    if(user != dbUser) {
      cout << endl;
      cout << "------------------------------------------------------" << endl << endl;
      cout << "        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~       " << endl;
      cout << "       :   Username yang anda masukkan salah   :      " << endl;
      cout << "        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~       " << endl << endl;
      cout << "------------------------------------------------------" << endl << endl;

      goto user;
    }

    pass:

    cout << "  =>  Password	:  "; cin >> pass;

    if(pass != dbPass) {
      cout << endl;
      cout << "------------------------------------------------------" << endl << endl;
      cout << "        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~       " << endl;
      cout << "       :   Password yang anda masukkan salah   :      " << endl;
      cout << "        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~       " << endl << endl;
      cout << "------------------------------------------------------" << endl << endl;

      goto pass;

    }
    cin.ignore();
    system("cls");

    // animasi loading 

    int i = 0; 
    char load[26]; 

    system("cls");
    system("color 9");

    while(i < 25) { 
      system("cls"); 

      load[i++] = '#'; 
      load[i] = '\0'; 
      cout <<"\n\n\n\n\t\tLOADING " << i*4 << " %";
      printf("\n\n\t\t[%-25s]", load);
      usleep(50000); 
    } 

    system("color e");    
  }
}

