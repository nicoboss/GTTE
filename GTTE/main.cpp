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
#define BLINK 12


//#include <P:\winmm.h>


using namespace std;


//vector<string> Spielfeld;using namespace std;


string Spielfeld[3][10] {
    {
        {"XXXXXXXXXXXXXXXXXXXXXXXX\n"},
        {"X  X   X$X         X\n"},
        {"X XX X X XX    XX XX\n"},
        {"X      X       X        X\n"},
        {"XXXXXX X XX    XX XX\n"},
        {"X    X   X         X\n"},
        {"X?XX   XXXXXXXXXXXXXXXX\n"},
        {"X    XXXXXXXXXXXXXXXXX\n"},
        {"XXXXXXXXXXXXXXXXXXXXX\n"}
    },

    {
        {"XXXXXXAXXX\n"},
        {"X  X   X X\n"},
        {"X XX X X X\n"},
        {"X      X  \n"},
        {"XXXXX  X X\n"},
        {"XXXX     X\n"},
        {"XXXXXXXXXX\n"},
        {"XXXXXXXXXX\n"},
        {"XXXXXXXXXX\n"}
    }
};


//vector<int> Feind{1, 2, 2};



vector<vector<vector<vector<unsigned int>>>> Feind{
{
    {{6, 3}, {5, 3}, {4, 3},{3, 3},{2, 3},{1, 3}},
    {{6, 1}, {6, 2}, {6, 3},{6, 4}, {6, 5}, {6, 6}},
    {{1, 5},{2, 5}, {3, 5},{4, 5}, {4, 6}, {4, 7}, {3, 7},{2, 7},{1, 7}},
    {{8, 3}, {9, 3}, {10, 3},{11, 3},{12, 3},{13, 3},{14, 3}},
    {{12, 1}, {12, 2}, {12, 3},{12, 4},{12, 5}},
    {{10, 1}, {11, 1}, {12, 1},{13, 1},{14, 1},{15, 1},{16, 1},{17, 1},{18, 1}},
    {{10, 5}, {11, 5}, {12, 5},{13, 5},{14, 5},{15, 5},{16, 5},{17, 5},{18, 5}},
    //{{0, 0}, {0, 0}, {0, 0},{0, 0}},
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
unsigned char Schwirigkeitsgrad=15; //Achtung: klein ist hoch und gross schwierig!
unsigned short Geschwindigkeit=50;  //Achtung: klein ist schnell und gross langsahm!

unsigned char Spielfigur_x = 2;
unsigned char Spielfigur_y = 1 ;

unsigned char Spielfigur_x_alt = 2;
unsigned char Spielfigur_y_alt = 1;

int i;



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

    Spielfeld[Level][FeindYPosAlt[Level][i]].at(FeindXPosAlt[Level][i])=32;

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

    for(size_t i=0; i < 10; i++)
    {
        cout << Spielfeld[Level][i];
    }

    cout << endl;
    cout << "Leben: ";
    // Herze Rot ferben
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
    FOREGROUND_INTENSITY | FOREGROUND_RED | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
    for(size_t i=0; i < Leben; i++)
    {
        cout << char(3);
    }
    // Farbe wieder zurücksetzen
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
    //FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    FOREGROUND_INTENSITY | FOREGROUND_GREEN | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
    cout << endl << "Geld: " << Geld;

}




int main(int argc, char *argv[])
{
unsigned int Feind_Neuberechnung=0;

//Herzchensymbole
Spielfeld[0][6].at(1)=char(3);


//mciSendString("play P:\\8.mp3 repeat",0,0,0);

mciSendString("open 8.mp3 alias MY_SND",0,0,0);
mciSendString("play MY_SND repeat",0,0,0);

// etc

//mciSendString("pause MY_SND",0,0,0);

// etc

//mciSendString("resume MY_SND",0,0,0);

// etc

//mciSendString("stop MY_SND",0,0,0);

// etc



// FOREGROUND_YELLOW + FOREGROUND_INTENSITY
//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
//FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);



system("color F0");

// FOREGROUND_YELLOW + FOREGROUND_INTENSITY + BACKGROUND_RED + BACKGROUND_INTENSITY
//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
//FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | BACKGROUND_INTENSITY | BACKGROUND_RED);

//WinExec(HHH.c_str(),0);
//ShellExecute(NULL, "open", "P:\\Programme\\mpg123\\mpg123.exe", "P:\\Programme\\mpg123\\mpg123\\8-bit.mp3", NULL, SW_SHOWNORMAL);
//system("vlc P:\\Programme\\mpg123\\mpg123.exe --no-gapless P:\\Programme\\mpg123\\8-bit.mp3");
//system("pause");

int Map_Zeilen;
int Map_Buchstaben;

while(true)
{
    Sleep(Geschwindigkeit);
    //system("cls"); //Wenn Aktiv: Erste Zeile blinkt, da Befehl zu langsahm!
     gotoXY(0,0);


    //for(size_t i=0; i < 10; i++)
    //{
    //    cout << Spielfeld[Level][i];
    //}

    for(Map_Zeilen=0; Map_Zeilen < sizeof(Spielfeld)/sizeof(char); Map_Zeilen++)
        for(Map_Buchstaben=0; Map_Buchstaben < 10; Map_Buchstaben++)
        {
            //cout << Spielfeld[Level][Map_Zeilen].at(Map_Buchstaben);
            cout << Spielfeld[Level][Map_Zeilen];
        }
        cout << endl;



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



}
