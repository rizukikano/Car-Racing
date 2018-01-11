//How To Play :
//Kita menggerakkan mobil dengan menhindari musuh yang datang dengan memencet tombol "A" untuk berpindah posisi ke kiri dan "D" untuk berpindah posisi ke kanan
//Diberikan Kesempatan 5x Tabrakan dengan musuh , kalau sudah 5x maka akan kalah dan dihitung scorenya , high score akan ditampilkan 
// Setiap score kelipatan 50 maka kecepatan musuh akan meningkat



#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>

#define KOTAK char(178) //Kotak = char 178
#define BATAS_KIRI 16	// Buat BATAS KIRI senilai = 16
#define BATAS_KANAN 59	// Buat BATAS KANAN senilai = 59
#define BATANG char(219) // Batang = char 219

using namespace std;

int iJarak = 0;

//Buat fungsi kordinat pointer
void gotoxy(int x, int y)
{
        COORD koord = {x, y};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), koord);
}
// Untuk Menyimpan High Score
int getScore()
{
	ifstream myfile ("score.dat");
	string line;
	int high;

	if (myfile.is_open())
	{
  		getline(myfile, line);
  		stringstream num(line);
  		num >> high;
  		return high;
	}
	
	return 0;
}

//Print Control
void Credit()
{
    gotoxy(BATAS_KIRI - 15, 15); cout << "CONTROL";
    gotoxy(BATAS_KIRI - 15, 18); cout << "D : KANAN";
    gotoxy(BATAS_KIRI - 15, 19); cout << "A : KIRI";
    gotoxy(BATAS_KANAN +5 , 15); cout << "HIGH SCORE :";
    gotoxy(BATAS_KANAN +8 , 17); cout <<  getScore();
}

//print Sirkuit
void gambarLatar()
{
    for(int i = 0; i <= 24; i++)
    {
        gotoxy(BATAS_KIRI + 3, i); cout << BATANG;
        gotoxy(BATAS_KANAN - 2, i); cout << BATANG;
        gotoxy(BATAS_KIRI, i); cout << KOTAK << KOTAK;
        gotoxy(BATAS_KANAN, i); cout << KOTAK << KOTAK;
    }
}

//Membuat efek berjalan di sirkuit
void gambarJalan(int spasi, int awal)
{
      for(int i = awal + 1; i <= 24; i += spasi)
      {
              gotoxy(BATAS_KIRI, i - 1); cout << KOTAK << KOTAK;
              gotoxy(BATAS_KANAN, i - 1); cout << KOTAK << KOTAK;
              gotoxy(BATAS_KIRI, i); cout << "  ";
              gotoxy(BATAS_KANAN, i); cout << "  ";
      }
}
//Nilai absolut
int abs(int a)
{
    if(a < 0) return -a;
}

//Fungsi Health mobil
void batangDarah(int a)
{
    gotoxy(1, 4);
    cout << "HEALTH : ";
    gotoxy(1, 5);
    for(int i = 1; i <= a / 10; i++)
    {
        cout << BATANG;
    }
    for(int i = 1; i <= 5 - (a / 10); i++)
    {
        cout << KOTAK;
    }
}

//fungsi print jarak 
void jarak(int iJarak)
{
    gotoxy(1, 7);
    cout << "JARAK :";
    gotoxy(1, 8);
    cout << iJarak;
}
//fungsi kecepatan mobil
void Speed(int speed)
{
    gotoxy(1, 10);
    cout << "KECEPATAN :";
    gotoxy(1, 11);
    cout << "    ";
    gotoxy(1, 11);
    cout << speed;
}
// Objek Mobil
struct car {
    int x,y,darah, kebal;
    bool exis;
    string gambar[5];
    car()
    {
        x = 25;
        y = 20;
        exis = false;
        darah = 50;
        kebal = 0;
        gambar[0] = " - ";
        gambar[1] = "0+1";
        gambar[2] = " + ";
        gambar[3] = "0+1";
    }
    void setPos(int a, int b)
    {
        x = a;
        y = b;
    }
    //Fungsi Menggerakkan mobil ke kiri
	void keKiri()
    {
      if(x > 20)
       {
         hapus();
         x -= 1;
       }
    }
    //Fungsi Menggerakkan mobil ke kanan
    void keKanan()
    {
       if(x + 2 < 56)
       {
         hapus();
         x += 1;
       }
    }
    //Fungsi Menggerakkan mobil ke bawah
    void keBawah()
    {
       if(y + 3 <= 23)
       {
            hapus();
            y += 1;
       }
    }
    //Fungsi Update Posisi Mobil
	void hapus()
    {
        gotoxy(x+1, y);   cout << " ";
        gotoxy(x, y+1);   cout << "   ";
        gotoxy(x+1, y+2); cout << " ";
        gotoxy(x, y+3);   cout << "   ";
    }
	// Fungsi Mengecek tabrakan antar mobil dengan enemy
    bool cekTabrakan(car a)
    {
        if((a.y >= y && a.y <= y+3) && (abs(a.x - x) < 3))
        {
            return true;
        } else
        {
            return false;
        }
    }
    //void print mobil jika bertabrakan
    void gores()
    {
        for(int i = y; i <= (y + 3); i++)
        {
            gotoxy(x, i);
            for(int j = 0; j < gambar[i - y].length(); j++)
            {
             if(gambar[i - y][j] == '0') cout << char(221); else
             if(gambar[i - y][j] == '1') cout << char(222); else
             if(gambar[i - y][j] == '+') cout << BATANG; else
             if(gambar[i - y][j] == '-') cout << char(220); else
             cout << " ";
            }
        }
    }
    // Fungsi Membuat gambar kembali
	void buatGambar()
    {
                 if(kebal == 0)
                 {
                   gores();
                 } else
                 {
                   if(kebal % 2 == 0)
                   {
                    gores();
                   }
                   else {
                    hapus();
                   }
                 }
    }
};

//fungsi print di tengah cmd
void tulisTengah(string s, int y)
{
    gotoxy(40 - (s.length() / 2), y);
    cout << s;
}

//fungsi counter waktu
void tidur(int a)
{
    time_t now = clock();
    while((clock() - now) < a) {};
}

//fungsi hitung mundur
void opening()
{
    tulisTengah("Bersedia", 10);
    tidur(1000);
    tulisTengah("        ", 10);
    tulisTengah("3", 10);
    tidur(1000);
    tulisTengah("2", 10);
    tidur(1000);
    tulisTengah("1", 10);
    tidur(1000);
    tulisTengah(" ", 10);
}
// Menyimpan Score tertinggi
void saveScore()
{
  ofstream out;
  ifstream myfile ("score.dat");
  string line;
  int high;

  if (myfile.is_open())
  {
  	getline(myfile, line);
  	stringstream num(line);
  	num >> high;
  	
  	if (iJarak > high)
  	{
  		out.open("score.dat", ofstream::out);
		out << iJarak << endl;
		out.close();
	}
  }
}
int main()
{//Kecepatan Mobil
 int spk = 0;
 float fSpk = 100;
  while(spk <= 0)
  {
    tulisTengah("=====WELCOME TO CAR RACING=====", 9);
	tulisTengah("Play your old retro car racing game", 10);
	tulisTengah("Press any key to play", 15);
	getch();
    spk = (int) fSpk;
  }
  system("cls");

    srand(clock());
    car pemainUtama; //mobil untuk player 
    car enemy[4]; // jumah musuh ada 4
    char control = ' ';
    enemy[0].setPos(20 + rand()%34, 0);// merandom musuh yang muncul
    enemy[1].setPos(20 + rand()%34, 0);// merandom musuh yang muncul
    enemy[2].setPos(20 + rand()%34, 0);// merandom musuh yang muncul
    enemy[0].exis = true;
    bool mulai = false;
    int spasi = 8, awal = 0, nMusuh = 0;
    batangDarah(pemainUtama.darah);
    float before = clock();
    gambarLatar();
    Credit();
    while(pemainUtama.darah > 0 && (spk - iJarak / 50) > 0)
    {
        Speed(spk - iJarak / 50);
        iJarak++;
        if(awal > 8) awal = 0;
        gambarJalan(spasi, awal);
        awal++;
        if(kbhit())//mengecek tombol keyboard
            {
                control = getch();
                control = toupper(control);
            }
        switch (control)// kontrol mobil
            {
                case 'D' : pemainUtama.keKanan(); break;
                case 'A' : pemainUtama.keKiri(); break;
            }
        pemainUtama.buatGambar();

        //generate musuh
        for(int i = 0; i <= 2; i++)
        {
           if(enemy[i].exis == true)
           {
            enemy[i].keBawah();
            enemy[i].buatGambar();
            if(enemy[i].y > 20)
            {
                enemy[i].hapus();
                enemy[i].y = 0;
                enemy[i].x = 20 + rand()%34;
                enemy[i].exis = false;
                nMusuh++;
            }
            // Mengecek tabrakan antara mobil dengan lawan
            if(enemy[i].cekTabrakan(pemainUtama))
            {
                if(pemainUtama.kebal == 0)
                {

                    pemainUtama.darah -= 10;
                    pemainUtama.kebal = 45;
                    batangDarah(pemainUtama.darah);
                }
            }
           } else
           {
               nMusuh = i - 1;
               if(nMusuh < 0) nMusuh = 3;
               if(enemy[nMusuh].y >= 7)
               {
                   enemy[i].exis = true;
               }

           }
           if(pemainUtama.kebal > 0)
           {
               pemainUtama.kebal--;
           }
           jarak(iJarak);
        }
        if(mulai == false)
        {
            opening();
            mulai = true;
        }
        control = ' ';
        tidur(spk - iJarak / 50);
    }
    spk -= (iJarak / 50);
    system("cls");
    saveScore();
    gotoxy(20, 12); cout << "Game Berakhir Score Anda : " << iJarak;
    gotoxy(20, 13); cout << "Total Waktu Bermain      : " << (clock() - before) / 1000 << " Detik";
    tidur(5000);
    getch();
}
