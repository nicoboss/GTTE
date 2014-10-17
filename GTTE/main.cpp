#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <vfw.h>
#include "mmsystem.h"

#pragma comment( lib, "vfw32.lib" )                 // Search For VFW32.lib While Linking



#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGREY 7
#define DARKGREY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15
#define BLINK 128


//#include <P:\winmm.h>
#pragma comment(lib, "user32")

using namespace std;


//vector<string> Spielfeld;using namespace std;


string Spielfeld[3][10] {
    {
        {"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX \n"},
        {"X  X   X$X         XXX            XX     X \n"},
        {"X XX X X XX    XX XXXX XXX   X   XXX XXX X \n"},
        {"X      X       X        XXX     XX     X XX\n"},
        {"XXXXXX X XX    XX XXXXXXX$XX   XXX  X  X   \n"},
        {"X    X   X         X       X   XXX     X XX\n"},
        {"X?XX   XXXXXXXXXXXXX XXXXX XX XXXXXX XXX ? \n"},
        {"X    XXX$$                            XX X \n"},
        {"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX \n"}
    },

    {
        {"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX \n"},
        {"X  X   X$X         XXX     r      XX     X \n"},
        {"X XX X X XX    XX XXXX XXX       XXX XXX X \n"},
        {"X      X       X        XXX     XX     X XX\n"},
        {"XXXXXX X XX    XX XXXXXXX$XX   XXX  X  X   \n"},
        {"X    X   X         X       X   XXX     X XX\n"},
        {"X?XX   XXXXXXXXXXXXX XXXXX XX XXXXXX XXX ? \n"},
        {"X    XXX$$                            XX X \n"},
        {"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX \n"}
    }
};


//vector<int> Feind{1, 2, 2};



vector<vector<vector<vector<unsigned int>>>> Feind{
{
    {{6, 3},{5, 3},{4, 3},{3, 3},{2, 3},{1, 3}},
    {{6, 1},{6, 2},{6, 3},{6, 4},{6, 5},{6, 6}},
    {{1, 5},{2, 5},{3, 5},{4, 5},{4, 6},{4, 7},{3, 7},{2, 7},{1, 7}},
    {{8, 3},{9, 3},{10, 3},{11, 3},{12, 3},{13, 3},{14, 3}},
    {{12, 1},{12, 2},{12, 3},{12, 4},{12, 5}},
    {{10, 1},{11, 1},{12, 1},{13, 1},{14, 1},{15, 1},{16, 1},{17, 1},{18, 1}},
    {{10, 5},{11, 5},{12, 5},{13, 5},{14, 5},{15, 5},{16, 5},{17, 5},{18, 5}},
    {{16, 3},{17, 3},{18, 3},{19, 3},{20, 3},{21, 3},{22, 3},{23, 3}},
    {{10, 7},{11, 7},{12, 7},{13, 7},{14, 7},{15, 7},{16, 7},{17, 7},{18, 7},{19, 7},{20, 7},{21, 7},{22, 7},
    {23, 7},{24, 7},{25, 7},{26, 7},{27, 7},{28, 7},{29, 7},{30, 7},{31, 7},{32, 7},{33, 7},{34, 7},{35, 7},{36, 7},{37, 7},{38, 7}},
    {{29, 2},{29, 3},{29, 4},{29, 5},{29, 6},{29, 7}},
},
{
    {{0, 0}, {0, 0}, {0, 0},{0, 0}},
    {{0, 0}, {0, 0}, {0, 0},{0, 0}},
    {{0, 0}, {0, 0}, {0, 0},{0, 0}},
    {{0, 0}, {0, 0}, {0, 0},{0, 0}},
    {{0, 0}, {0, 0}, {0, 0},{0, 0}},
    {{0, 0}, {0, 0}, {0, 0},{0, 0}},
    {{0, 0}, {0, 0}, {0, 0},{0, 0}},
    {{0, 0}, {0, 0}, {0, 0},{0, 0}},

}
};



//vector< vector< unsigned char> >FeindVectorPos(2,vector<unsigned char>(2,0));

vector<vector<unsigned char>>FeindVectorPos(10,vector<unsigned char>(10,0));
vector<vector<char>>FeindPorM(10,vector<char>(10,0));

vector<vector<char>>FeindXPos(10,vector<char>(10,0));
vector<vector<char>>FeindYPos(10,vector<char>(10,0));
vector<vector<char>>FeindXPosAlt(10,vector<char>(10,0));
vector<vector<char>>FeindYPosAlt(10,vector<char>(10,0));

int Leben=4;
int Geld=100;

unsigned char Level = 0;
unsigned char Schwirigkeitsgrad; //Achtung: klein ist hoch und gross einfach!
unsigned short Geschwindigkeit=50;  //Achtung: klein ist schnell und gross langsahm!

unsigned char Spielfigur_x = 2;
unsigned char Spielfigur_y = 1 ;

unsigned char Spielfigur_x_alt = 2;
unsigned char Spielfigur_y_alt = 1;

int i;



void coutc(int fcolor, int bcolor, char output)
{
   HANDLE handle= GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute( handle, (fcolor + (bcolor * 16)) );
   cout<< output;
   //SetConsoleTextAttribute( handle, color| 15);
}

void gotoXY(int x, int y) {
	HANDLE hStdout;
	COORD coordScreen = { 0, 0 };
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	coordScreen.X = x;
	coordScreen.Y = y;
	SetConsoleCursorPosition( hStdout, coordScreen );
}

void CursorVerschlucker()
{
    CONSOLE_CURSOR_INFO info;
    HANDLE  out;

    info.bVisible = 0;
    info.dwSize   =   1;

    out = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo( out,  &info );
}


bool SpielfigurSetPos(unsigned char x, unsigned char y)
{
    for(size_t i=0; i < FeindXPos[Level].size(); i++)
    {
        if(x==FeindXPos[Level][i]&&y==FeindYPos[Level][i])
        {
            Leben--;

            x=2;
            y=1;
            Spielfigur_x=x;
            Spielfigur_y=y;

            Spielfeld[Level][Spielfigur_y_alt].at(Spielfigur_x_alt)=32;
            Spielfigur_x_alt = x;
            Spielfigur_y_alt = y;
            Spielfeld[Level][y].at(x)=2;
            cout << "\a";

            return true;

        }
    }
    if(Spielfeld[Level][y].at(x)==32)
    {
        Spielfeld[Level][Spielfigur_y_alt].at(Spielfigur_x_alt)=32;
        Spielfigur_x_alt = x;
        Spielfigur_y_alt = y;

        Spielfeld[Level][y].at(x)=2;
    }
    else if(Spielfeld[Level][y].at(x)==36)
    {
        Spielfeld[Level][Spielfigur_y_alt].at(Spielfigur_x_alt)=32;
        Spielfigur_x_alt = x;
        Spielfigur_y_alt = y;

        Spielfeld[Level][y].at(x)=2;

        Geld=Geld+50;
        return true;
    }
    else if(Spielfeld[Level][y].at(x)==3)
    {
        Spielfeld[Level][Spielfigur_y_alt].at(Spielfigur_x_alt)=32;
        Spielfigur_x_alt = x;
        Spielfigur_y_alt = y;

        Spielfeld[Level][y].at(x)=2;

        Leben++;
        return true;
    }
    else
    {
        Spielfigur_x=Spielfigur_x_alt;
        Spielfigur_y=Spielfigur_y_alt;
    }

    return false;
}



void Feindberechnung()
{

for(size_t i=0; i < Feind[Level].size(); i++)
{
    if(FeindVectorPos[Level][i]==0)
    {
        FeindPorM[Level][i]=1;
    }
    else if(FeindVectorPos[Level][i]==Feind[Level][i].size()-1)
    {
        FeindPorM[Level][i]=-1;
    }

    if(FeindYPosAlt[Level][i]!=0||FeindXPosAlt[Level][i]!=0)
    {
        Spielfeld[Level][FeindYPosAlt[Level][i]].at(FeindXPosAlt[Level][i])=32;
    }

    FeindXPos[Level][i]=Feind[Level][i][FeindVectorPos[Level][i]][0];
    FeindYPos[Level][i]=Feind[Level][i][FeindVectorPos[Level][i]][1];

    FeindXPosAlt[Level][i]=FeindXPos[Level][i];
    FeindYPosAlt[Level][i]=FeindYPos[Level][i];

    Spielfeld[Level][FeindYPos[Level][i]].at(FeindXPos[Level][i])=1; //Herzzeile der Feindbewegung!!!
    FeindVectorPos[Level][i]=FeindVectorPos[Level][i]+FeindPorM[Level][i];
}

}

void Statusanzeige()
{
    system("cls");

   HANDLE handle= GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute( handle, (BLACK + (WHITE * 16)) );

    gotoXY(0,10);

    cout << "Leben: ";
    // Herze Rot ferben
    //HANDLE handle= GetStdHandle(STD_OUTPUT_HANDLE);
   //SetConsoleTextAttribute( handle, (fcolor + (bcolor * 16)) );

    SetConsoleTextAttribute( handle, (LIGHTRED + (WHITE * 16)) );

    for(size_t i=0; i < Leben; i++)
    {
        cout << char(3);
    }

    cout << endl;

    SetConsoleTextAttribute( handle, (BLACK + (WHITE * 16)));
    cout << ("Geld: ");

    SetConsoleTextAttribute( handle, (LIGHTCYAN + (WHITE * 16)));
    cout << (Geld);

}



int main(int argc, char *argv[])
{
unsigned int Feind_Neuberechnung=0;

//Herzchensymbole
Spielfeld[0][6].at(1)=char(3);


//mciSendString("play P:\\8.mp3 repeat",0,0,0);

mciSendString("open 8.mp3 alias MY_SND",0,0,0);
mciSendString("play MY_SND repeat",0,0,0);
//mciSendString("pause MY_SND",0,0,0);
//mciSendString("resume MY_SND",0,0,0);
//mciSendString("stop MY_SND",0,0,0);

//while(GetAsyncKeyState(VK_ESCAPE)==true)
//{

system("color 1F");

cout << " Herzlich Willkommen zum Spiel GTTE 2013\n\n";
cout << " Das Ziel des Spiels ist es durch steuern\n deiner Spielfigur ins Freie zu gelangen.\n\n";
cout << " Auf deinem Weg musst du jedoch allen\n Wächter ausweichen, die dich sonst\n wieder an deine Startposition bringen.\n\n";
cout << " Du kannst deine Spielfigur mit ASDW, mit\n den Pfeiltasten sowie mit dem Num-Block\n (auch diagonal möglich) steuern.\n\n";
cout << " Noch viel Spass beim Spielen wünscht dir\n Nico Bosshard\n\n\n";
cout << " ";
system("Pause");
system("Cls");

int Level_Eingabe;
int Schwirigkeitsgrad_Eingabe;

cout << "Wähle eine beliebiges Level sowie eine dir Angemessene Geschwindigkeit der Wächter aus um mit dem Spiel zu beginnen.\n\n";

while(true){
cout << "Level (1-3): ";
cin >> Level_Eingabe;
cout << endl << endl;
cout << "Geschwindigkeit (1-20): ";
cin >> Schwirigkeitsgrad_Eingabe;

system("Cls");
if(Level_Eingabe>0 && Level_Eingabe<4 && Schwirigkeitsgrad_Eingabe>0 && Schwirigkeitsgrad_Eingabe<21)
{
    break;
}
}

system("color F0");
system("Cls");


int Map_Zeilen;
int Map_Buchstaben;

Level=Level_Eingabe-1;
Schwirigkeitsgrad_Eingabe=21-Schwirigkeitsgrad_Eingabe;

Schwirigkeitsgrad=Schwirigkeitsgrad_Eingabe;
//Schwirigkeitsgrad=100-Schwirigkeitsgrad;

Feind_Neuberechnung=Schwirigkeitsgrad-1;

Statusanzeige();

while(true)
{
    Sleep(Geschwindigkeit);
    //system("cls"); //Wenn Aktiv: Erste Zeile blinkt, da Befehl zu langsahm!
     gotoXY(0,0);


    //for(size_t i=0; i < 10; i++)
    //{
    //    cout << Spielfeld[Level][i];
    //}

    for(Map_Zeilen=0; Map_Zeilen < 9; Map_Zeilen++)
    {
        for(Map_Buchstaben=0; Map_Buchstaben < 43; Map_Buchstaben++)
        {
            switch(Spielfeld[Level][Map_Zeilen].at(Map_Buchstaben))
            {
                case 1 :
                    coutc(MAGENTA, WHITE, char(1));
                    break;
                case 2 :
                    coutc(BLUE, WHITE, char(2));
                    break;
                case 3 :
                    coutc(LIGHTRED,WHITE, char(3));
                    break;
                case 36 :
                    coutc(LIGHTCYAN,WHITE, char(36));
                    break;
                default : coutc(BLACK,WHITE,Spielfeld[Level][Map_Zeilen].at(Map_Buchstaben));
            }

            //cout << Spielfeld[Level][Map_Zeilen];


        }

        cout << endl;
    }




    if(SpielfigurSetPos(Spielfigur_x, Spielfigur_y)==true)
    {
        Statusanzeige();
    }

    Feind_Neuberechnung++;
    if(Feind_Neuberechnung==Schwirigkeitsgrad)
    {
        Feindberechnung();
        Feind_Neuberechnung=0;
    }



    if(GetAsyncKeyState(VK_LEFT)&1||GetAsyncKeyState(VK_NUMPAD4)&1||GetAsyncKeyState(0x41)&1 == true)
    {
        //cout << "Links\n\a";
        Spielfigur_x--;
    }
    else if(GetAsyncKeyState(VK_RIGHT)&1||GetAsyncKeyState(VK_NUMPAD6)&1||GetAsyncKeyState(0x44)&1 == true)
    {
        //cout << "Rechts\strncpyn\a";        return false;
        Spielfigur_x++;
    }
    else if(GetAsyncKeyState(VK_UP)&1||GetAsyncKeyState(VK_NUMPAD8)&1||GetAsyncKeyState(0x57)&1 == true)
    {
        //cout << "Oben\n\a";
        Spielfigur_y--;
    }
    else if(GetAsyncKeyState(VK_DOWN)&1||GetAsyncKeyState(VK_NUMPAD2)&1||GetAsyncKeyState(0x53)&1 == true)
    {
        //cout << "Unten\n\a";
        Spielfigur_y++;
    }

    //Diagonal
    else if(GetAsyncKeyState(VK_NUMPAD1)&1 == true)
    {
        //cout << "Unten-Links\n\a";
        Spielfigur_x--;
        Spielfigur_y++;
    }
        else if(GetAsyncKeyState(VK_NUMPAD3)&1 == true)
    {
        //cout << "Unten-Rechts\n\a";FeindVectorPos[Level][i]
        Spielfigur_x++;
        Spielfigur_y++;
    }
        else if(GetAsyncKeyState(VK_NUMPAD9)&1 == true)
    {
        //cout << "Oben-Rechts\n\a";
        Spielfigur_x++;
        Spielfigur_y--;
    }
        else if(GetAsyncKeyState(VK_NUMPAD7)&1 == true)
    {
        //cout << "Unten-Links\n\a";
        Spielfigur_x--;
        Spielfigur_y--;
    }


}

system("color 0F");
system("Cls");


//};


}
