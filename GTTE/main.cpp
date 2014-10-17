#include <iostream>
#include <windows.h>
#include <vector>
#include <string>

using namespace std;

const size_t N = 73;

//vector<string> Spielfeld;

string Spielfeld[3][10] {
    {
        {"XXXXXXXXXX\n"},
        {"X  X   X X\n"},
        {"X XX X X X\n"},
        {"X      X  \n"},
        {"XXXX   X X\n"},
        {"XXXX     X\n"},
        {"XXXXXXXXXX\n"},
        {"XXXXXXXXXX\n"},
        {"XXXXXXXXXX\n"}
    },

    {
        {"XXXXXXXXXX\n"},
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


unsigned char Feind[3][8][4][2] = {
{
    {{1, 1}, {1, 1}, {1, 1},{1, 1}},
    {{1, 1}, {1, 1}, {1, 1},{1, 1}},
    {{1, 1}, {1, 1}, {1, 1},{1, 1}},
    {{1, 1}, {1, 1}, {1, 1},{1, 1}},
    {{1, 1}, {1, 1}, {1, 1},{1, 1}},
    {{1, 1}, {1, 1}, {1, 1},{1, 1}},
    {{1, 1}, {1, 1}, {1, 1},{1, 1}},
    {{1, 1}, {1, 1}, {1, 1},{1, 1}},
},
{
    {{1, 1}, {1, 1}, {1, 1},{1, 1}},
    {{1, 1}, {1, 1}, {1, 1},{1, 1}},
    {{1, 1}, {1, 1}, {1, 1},{1, 1}},
    {{1, 1}, {1, 1}, {1, 1},{1, 1}},
    {{1, 1}, {1, 1}, {1, 1},{1, 1}},
    {{1, 1}, {1, 1}, {1, 1},{1, 1}},
    {{1, 1}, {1, 1}, {1, 1},{1, 1}},
    {{1, 1}, {1, 1}, {1, 1},{1, 1}},
}
};


unsigned char Level = 0;

unsigned char Schwirigkeitsgrad=5   //Achtung: klein ist hoch und gross schwierig!


unsigned char Spielfigur_x = 2;
unsigned char Spielfigur_y = 1 ;

unsigned char Spielfigur_x_alt = 2;
unsigned char Spielfigur_y_alt = 1;

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
    Spielfigur_y_alt= y;

    Spielfeld[Level][y].at(x)=2;
}
else
{
    Spielfigur_x=Spielfigur_x_alt;
    Spielfigur_y=Spielfigur_y_alt;
}
//

}//


int main()
{
//
int i;

CursorVerschlucker();


while(true)
{
    Sleep(50);
    //system("cls");
     gotoXY(0,0);

    //cout << "\n";

    for(size_t i=0; i < 10; i++)
    {
    cout << Spielfeld[Level][i];
    }

    SpielfigurSetPos(Spielfigur_x, Spielfigur_y);
    //SpielfigurSetPos(1, 1);

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
        //cout << "Unten-Rechts\n\a";
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



