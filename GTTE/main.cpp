#include <iostream>     //Standartbibliothek
#include <windows.h>    //Standartbibliothek
#include <vector>       //neue Arreys
#include <string>       //neue Strings
#include "mmsystem.h"   //Soundencoder
#include <locale.h>     //Deeeutsches Sprachpacket für Umlaute
#include <locale> //Sprachbibliothek


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


string Spielfeld[3][11] {
    {
        {"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX \n"},
        {"X  XXXX         XXXX            XXX$XXXXXX \n"},
        {"X XX               X$XXXXX XXX XX     XXXX \n"},
        {"X    XX         XX XXX$     X?X XXX XX XXXX\n"},
        {"XXXXXXXXXXXXXXXXX       XXXXX        XX    \n"},
        {"XXX$           $XX XXX$     X?X XXX XX XXXX\n"},
        {"X?   x   x   X     X$XXXXX XXX XX     XXXX \n"},
        {"XXX$           $XXXX            XXX$XXXXXX \n"},
        {"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX \n"}
    },

    {
        {"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX \n"},
        {"X  X   X$X         XXX            XX     X \n"},
        {"X XX X X XX    XX XXXX XXX       XXX XXX X \n"},
        {"X      X       X        XXX     XX     X XX\n"},
        {"XXXXXX X XX    XX XXXXXXX$XX   XXX  X  X   \n"},
        {"X    X   X         X       X   XXX    XX XX\n"},
        {"X?XX   XXXXXXXXXXXXX XXXXX XX XXXXXX XX? X \n"},
        {"X    XXX$$                            XX X \n"},
        {"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX \n"}
    },
    {
        {"****************************************** \n"},
        {"*  *   *$*         **             **     * \n"},
        {"* ** * * **    ** **** ***  * *  *** *** * \n"},
        {"*      *       *        ***     **     * **\n"},
        {"****** * **    ** *******$*** ****  ** *   \n"},
        {"*    *   *         *       *$ $***    ** **\n"},
        {"*?**   ************* ***** ** ****** **? * \n"},
        {"*    **$?*                            ** * \n"},
        {"****************************************** \n"}
    }
};


//vector<int> Feind{1, 2, 2};



vector<vector<vector<vector<unsigned int>>>> Feind{
{
    {{7, 1},{7, 2},{7, 3}},
    {{8, 3},{8, 2},{8, 1}},
    {{9, 1},{9, 2},{9, 3}},
    {{10, 3},{10, 2},{10, 1}},
    {{11, 1},{11, 2},{11, 3}},
    {{12, 3},{12, 2},{12, 1}},
    {{13, 1},{13, 2},{13, 3}},
    {{14, 3},{14, 2},{14, 1}},
    {{15, 1},{15, 2},{15, 3}},
    {{5, 5}, {6, 5},{6, 6},{6, 7},{5, 7},{4, 7},{4, 6},{4, 5},{5, 5}},
    {{9, 7},{8, 7},{8, 6},{8, 5},{9, 5}, {10, 5},{10, 6},{10, 7},{9, 7}},
    {{13, 5}, {14, 5},{14, 6},{14, 7},{13, 7},{12, 7},{12, 6},{12, 5},{13, 5}},
    {{17, 4},{18, 4},{19, 4},{20, 4},{21, 4},{22, 4},{23, 4}},
    {{27, 3},{26, 3},{25, 3},{24, 3},{23, 3}},
    {{23, 5},{24, 5},{25, 5},{26, 5},{27, 5}},
    {{19, 1},{20, 1},{21, 1},{22, 1},{23, 1},{24, 1},{25, 1},{26, 1},{27, 1},{28, 1},{29, 1},{30, 1},{31, 1}},
    {{31, 7},{30, 7},{29, 7},{28, 7},{27, 7},{26, 7},{25, 7},{24, 7},{23, 7},{22, 7},{21, 7},{20, 7},{19, 7}},
    {{36, 4},{35, 4},{34, 4},{33, 4},{32, 4},{31, 4},{30, 4},{29, 4}},
    {{33, 2},{34, 2},{35, 2},{36, 2},{37, 2},{38, 2},{39, 2}},
    {{39, 6},{38, 6},{37, 6},{36, 6},{35, 6},{34, 6},{32, 6}},


},
{
    {{6, 3},{5, 3},{4, 3},{3, 3},{2, 3},{1, 3}},
    {{6, 3},{5, 3},{4, 3},{3, 3},{2, 3},{1, 3}},
    {{6, 1},{6, 2},{6, 3},{6, 4},{6, 5},{6, 6}},
    {{1, 5},{2, 5},{3, 5},{4, 5},{4, 6},{4, 7},{3, 7},{2, 7},{1, 7}},
    {{8, 3},{9, 3},{10, 3},{11, 3},{12, 3},{13, 3},{14, 3}},
    {{12, 1},{12, 2},{12, 3},{12, 4},{12, 5}},
    {{10, 1},{11, 1},{12, 1},{13, 1},{14, 1},{15, 1},{16, 1},{17, 1},{18, 1}},
    {{10, 5},{11, 5},{12, 5},{13, 5},{14, 5},{15, 5},{16, 5},{17, 5},{18, 5}},
    {{16, 3},{17, 3},{18, 3},{19, 3},{20, 3},{21, 3},{22, 3},{23, 3}},
    {{37, 7},{36, 7},{35, 7},{34, 7},{33, 7},{32, 7},{31, 7},{30, 7},{29, 7},{28, 7},{27, 7},{26, 7},{25, 7},
    {24, 7},{23, 7},{22, 7},{21, 7},{20, 7},{19, 7},{18, 7},{17, 7},{16, 7},{15, 7},{14, 7},{13, 7},{12, 7},{11, 7},{10, 7}},
    {{20, 5},{21, 5},{22, 5},{23, 5},{24, 5},{25, 5},{26, 5}},
    {{29, 7},{29, 6},{29, 5},{29, 4},{29, 3},{29, 2},{29, 1}},
    {{37, 5},{36, 5},{35, 5},{34, 5},{34, 4},{34, 3},{35, 3},{36, 3},{37, 3},{38, 3},{38, 4}},
    {{40, 5},{40, 6},{40, 7}},
},
{
    {{6, 3},{5, 3},{4, 3},{3, 3},{2, 3},{1, 3}},
    {{6, 3},{5, 3},{4, 3},{3, 3},{2, 3},{1, 3}},
    {{6, 1},{6, 2},{6, 3},{6, 4},{6, 5},{6, 6}},
    {{1, 5},{2, 5},{3, 5},{4, 5},{4, 6},{4, 7},{3, 7},{2, 7},{1, 7}},
    {{8, 3},{9, 3},{10, 3},{11, 3},{12, 3},{13, 3},{14, 3}},
    {{12, 1},{12, 2},{12, 3},{12, 4},{12, 5}},
    {{10, 1},{11, 1},{12, 1},{13, 1},{14, 1},{15, 1},{16, 1},{17, 1},{18, 1}},
    {{10, 5},{11, 5},{12, 5},{13, 5},{14, 5},{15, 5},{16, 5},{17, 5},{18, 5}},
    {{16, 3},{17, 3},{18, 3},{19, 3},{20, 3},{21, 3},{22, 3},{23, 3}},
    {{37, 7},{36, 7},{35, 7},{34, 7},{33, 7},{32, 7},{31, 7},{30, 7},{29, 7},{28, 7},{27, 7},{26, 7},{25, 7},
    {24, 7},{23, 7},{22, 7},{21, 7},{20, 7},{19, 7},{18, 7},{17, 7},{16, 7},{15, 7},{14, 7},{13, 7},{12, 7},{11, 7},{10, 7}},
    {{20, 5},{21, 5},{22, 5},{23, 5},{24, 5},{25, 5},{26, 5}},
    {{29, 7},{29, 6},{29, 5},{29, 4},{29, 3},{29, 2},{29, 1}},
    {{37, 5},{36, 5},{35, 5},{34, 5},{34, 4},{34, 3},{35, 3},{36, 3},{37, 3},{38, 3},{38, 4}},

    //Anders als in Level 2:
    {{40, 1},{40, 2},{40, 3},{40, 4},{40, 5},{40, 6},{40, 7}},
    {{21, 1},{22, 1},{23, 1},{24, 1},{25, 1},{26, 1},{27, 1},{28, 1},{29, 1},{30, 1},{31, 1},{32, 1},{33, 1}},
    {{8, 1},{8, 2},{8, 3},{8, 4},{8, 5}},
}
};



//vector< vector< unsigned char> >FeindVectorPos(2,vector<unsigned char>(2,0));

//25 bedeutet, dass 26 die Maximale Anzakl Feinde ist!!!
vector<vector<unsigned char>>FeindVectorPos(25,vector<unsigned char>(25,0));
vector<vector<char>>FeindPorM(25,vector<char>(25,0));
vector<vector<char>>FeindXPos(25,vector<char>(25,0));
vector<vector<char>>FeindYPos(25,vector<char>(25,0));
vector<vector<char>>FeindXPosAlt(25,vector<char>(25,0));
vector<vector<char>>FeindYPosAlt(25,vector<char>(25,0));

int Leben=5;
int Geld=100;

unsigned short Level = 0;
unsigned short Schwierigkeitsgrad; //Achtung: klein ist hoch und gross einfach!
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
    info.dwSize   = 1;

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

            Geld=Geld/2;

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
    else if(Spielfeld[Level][y].at(x)==63)
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
//Feind[Level].size()
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



int main()
{
unsigned int Feind_Neuberechnung=0;

setlocale ( LC_ALL, "German" );


//mciSendString("play P:\\8.mp3 repeat",0,0,0);
mciSendString("open 8.mp3 alias MY_SND",0,0,0);
mciSendString("play MY_SND repeat",0,0,0);
//mciSendString("pause MY_SND",0,0,0);
//mciSendString("resume MY_SND",0,0,0);
//mciSendString("stop MY_SND",0,0,0);

while(GetAsyncKeyState(VK_ESCAPE)==false) {

system("color 1F");

cout << " Herzlich Willkommen zum Spiel GTTE 2013\n\n";
cout << " Das Ziel des Spiels ist es, durch Steuern\n deiner Spielfigur ins Freie zu gelangen.\n\n";
cout << " Auf deinem Weg müssen Sie jedoch allen\n Wächtern ausweichen, die Sie sonst\n wieder an deine Startposition bringen.\n\n";
cout << " Sie können ihre Spielfigur mit ASDW, mit\n den Pfeiltasten sowie mit dem Num-Block\n (auch diagonal möglich) steuern.\n\n";
cout << " Noch viel Spass beim Spielen wünscht ihnen\n Nico Bosshard\n\n\n";
cout << " ";
system("Pause");
system("Cls");

int Level_Eingabe;
int Schwierigkeitsgrad_Eingabe;


while(true){

cout << endl;
cout << " Wählen Sie einen Level sowie eine\n beliebige Geschwindigkeit der Wächter\n aus um mit dem Spiel zu beginnen.\n\n";

cout << " Level 1 (leicht) bis 3 (schwer): ";
cin >> Level_Eingabe;
cout << endl << endl;
cout << " Tempo 1 (langsam) bis 20 (schnell): ";
cin >> Schwierigkeitsgrad_Eingabe;

system("Cls");
if(Level_Eingabe>0 && Level_Eingabe<4 && Schwierigkeitsgrad_Eingabe>0 && Schwierigkeitsgrad_Eingabe<21)
{
    break;
}
}

system("color F0");
system("Cls");


int Map_Zeilen;
int Map_Buchstaben;

Level=Level_Eingabe-1;
Schwierigkeitsgrad_Eingabe=21-Schwierigkeitsgrad_Eingabe;

Schwierigkeitsgrad=Schwierigkeitsgrad_Eingabe;

Feind_Neuberechnung=Schwierigkeitsgrad-1;


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

    if(Spielfigur_x==42 && Spielfigur_y==4)
        {
            Spielfeld[Level][Spielfigur_y].at(Spielfigur_x)=32;

            system("color E0");
            system("Cls");

            cout << endl;
            cout << endl;
            cout << "           @@@@@   @@    @  @@@@  \n";
            cout << "           @       @ @   @  @   @ \n";
            cout << "           @@@@@   @  @  @  @   @ \n";
            cout << "           @       @   @ @  @   @ \n";
            cout << "           @@@@@   @    @@  @@@@  \n";
            cout << endl;
            cout << endl;
            cout << " Herzliche Gratulation: Sie habe Level " << Level+1 << "\n erfolgreich mit der Schwierigkeitsstufe\n "
                 << Schwierigkeitsgrad_Eingabe <<" und " << Geld << "$ abgeschlossen.";
            cout << endl;
            cout << endl;
            cout << endl;
            cout << endl;
            cout << " ";
            system("Pause");

            Leben=5;
            Geld=100;
            Spielfigur_x=2;
            Spielfigur_y=1;

            break;
        }

    if(SpielfigurSetPos(Spielfigur_x, Spielfigur_y)==true)
    {

        if(Leben==0)
        {
            Spielfigur_x=2;
            Spielfigur_y=1;
            Leben=5;
            Geld=100;
            system("color C0");
            system("Cls");

            cout << endl;
            cout << endl;
            cout << "        @@@@    @@@@@     @     @@@@  \n";
            cout << "        @   @   @       @  @    @   @ \n";
            cout << "        @   @   @@@@@  @@@@@@   @   @ \n";
            cout << "        @   @   @      @    @   @   @ \n";
            cout << "        @@@@    @@@@@  @    @   @@@@  \n";
            cout << endl;
            cout << endl;
            cout << " Sie haben das Level leider nicht gesschafft. Versuchen Sie es später nochmals.\n "
                 << "Tipp: Versuchen Sie immer Orte zu finden, wo nie nie ein Wächter hindurchläuft.";
            cout << endl;
            cout << endl;
            cout << endl;
            cout << endl;
            cout << " ";

            system("Pause");
            break;
        }

        Statusanzeige();
        gotoXY(0,0);
    }


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
                case 63 :
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



    Feind_Neuberechnung++;
    if(Feind_Neuberechnung==Schwierigkeitsgrad)
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


};


}
