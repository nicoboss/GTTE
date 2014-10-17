#include <iostream>
#include <windows.h>
#include <vector>
#include <string>

using namespace std;

//vector<string> Spielfeld;

string Spielfeld[3][10] {
    {
        {"XXXXXXXXXXXXXXXXXXXXXXXX\n"},
        {"X  X   X X\n"},
        {"X XX X X X\n"},
        {"X      X  \n"},
        {"XXXX   X X\n"},
        {"XXXX     X\n"},
        {"XXXXXXXXXXXXXXXXXXXXXXXX\n"},
        {"XXXXXXXXXXXXXXXXXXXXX\n"},
        {"XXXXXXXXXXXXXXXXXXXXX\n"}
    },

    {
        {"XXXXXXAXXX\n"},
        {"X  X   X X\n"},
        {"X XX X X X\n"},
        {"X      X  \n"},
        {"XXXX   X X\n"},
        {"XXXX     X\n"},
        {"XXXXXXXXXX\n"},
        {"XXXXXXXXXX\n"},
        {"XXXXXXXXXX\n"}
    }
};


//vector<int> Feind{1, 2, 2};



vector<vector<vector<vector<unsigned int>>>> Feind{
{
    {{6, 1}, {6, 3}, {6, 2},{6, 4}, {6, 5}, {5, 5}, {6, 5}},
    {{1, 3}, {2, 3}, {3, 3},{4, 3}},
    {{0, 0}, {0, 0}, {0, 0},{0, 0}},
    {{0, 0}, {0, 0}, {0, 0},{0, 0}},
    {{0, 0}, {0, 0}, {0, 0},{0, 0}},
    {{0, 0}, {0, 0}, {0, 0},{0, 0}},
    {{0, 0}, {0, 0}, {0, 0},{0, 0}},
    {{0, 0}, {0, 0}, {0, 0},{0, 0}},
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


void SpielfigurSetPos(unsigned char x, unsigned char y)
{
    if(Spielfeld[Level][y].at(x)==32)
    {
        Spielfeld[Level][Spielfigur_y_alt].at(Spielfigur_x_alt)=32;
        Spielfigur_x_alt = x;
        Spielfigur_y_alt = y;

        Spielfeld[Level][y].at(x)=2;
    }
    else
    {
        Spielfigur_x=Spielfigur_x_alt;
        Spielfigur_y=Spielfigur_y_alt;
    }
}


void Feindberechnung()
{
    //for(i=0; i < 10; i++)
    //{
        //Feind[Level][i][FeindPos[i]]
    //}
        //if(Spielfeld[Level][3].at(3)==32)
        //{
            //Spielfeld[Level][Spielfigur_y_alt].at(Spielfigur_x_alt)=32;
            //Spielfigur_x_alt = x;
            //Spielfigur_y_alt = y;

            //Spielfeld[Level][y].at(x)=40;
        //}
        //else
        //{
            //Spielfigur_x=Spielfigur_x_alt;
            //Spielfigur_y=Spielfigur_y_alt;
        //}
    //}


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

cout << "\a";


//FeindVectorPos;
//FeindPorM;

//cout << Feind[Level].size();
//cout << endl << endl;


    //cout << Feind[Level][i][1][0];
    //cout << Feind[Level][i][1][1];

}


int main()
{
unsigned int Feind_Neuberechnung=0;

CursorVerschlucker();

//char SSS=2;
//cout << SSS;
//system("pause");

while(true)
{
    Sleep(Geschwindigkeit);
    //system("cls"); //Wenn Aktiv: Erste Zeile blinkt, da Befehl zu langsahm!
     gotoXY(0,0);

    for(size_t i=0; i < 10; i++)
    {
        cout << Spielfeld[Level][i];
    }

    SpielfigurSetPos(Spielfigur_x, Spielfigur_y);

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
        //cout << "Rechts\n\a";
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
