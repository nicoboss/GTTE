#include <iostream>
#include <windows.h>
#include <vector>
#include <string>

using namespace std;

vector<string> Spielfeld;

    int Spielfigur_x = 1;
    int Spielfigur_y = 1 ;

    int Spielfigur_x_alt = 1;
    int Spielfigur_y_alt = 1;

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

void SpielfigurSetPos(int x, int y)
{


Spielfeld[Spielfigur_y_alt].at(Spielfigur_x_alt)=32;
Spielfigur_x_alt = x;
Spielfigur_y_alt= y;

Spielfeld[y].at(x)=1;

}


int main()
{

int i;

string Hallo;


Spielfeld.push_back("XXXXXXXXXX\n");
Spielfeld.push_back("X XX   X X\n");
Spielfeld.push_back("X XX X X X\n");
Spielfeld.push_back("X      X  \n");
Spielfeld.push_back("XXXX   X X\n");
Spielfeld.push_back("XXXX     X\n");
Spielfeld.push_back("XXXXXXXXXX\n");
Spielfeld.push_back("XXXXXXXXXX\n");
Spielfeld.push_back("XXXXXXXXXX\n");




//cout << Spielfeld[0].at(1);

CursorVerschlucker();


while(true)
{
    Sleep(50);
    //system("cls");
     gotoXY(0,0);

    //cout << "\n";

    for(size_t i=0; i < Spielfeld.size(); i++)
    {
    cout << Spielfeld[i];
    }

    SpielfigurSetPos(Spielfigur_x, Spielfigur_y);
    //SpielfigurSetPos(1, 1);

    if(GetAsyncKeyState(VK_LEFT)&1||GetAsyncKeyState(VK_NUMPAD4)&1||GetAsyncKeyState(0x41)&1 == true)
    {
        cout << "Links\n\a";
        Spielfigur_x--;
    }
    else if(GetAsyncKeyState(VK_RIGHT)&1||GetAsyncKeyState(VK_NUMPAD6)&1||GetAsyncKeyState(0x44)&1 == true)
    {
        cout << "Rechts\n\a";
        Spielfigur_x++;
    }
    else if(GetAsyncKeyState(VK_UP)&1||GetAsyncKeyState(VK_NUMPAD8)&1||GetAsyncKeyState(0x57)&1 == true)
    {
        cout << "Oben\n\a";
        Spielfigur_y--;
    }
    else if(GetAsyncKeyState(VK_DOWN)&1||GetAsyncKeyState(VK_NUMPAD2)&1||GetAsyncKeyState(0x53)&1 == true)
    {
        cout << "Unten\n\a";
        Spielfigur_y++;
    }

    //Diagonal
    else if(GetAsyncKeyState(VK_NUMPAD1)&1 == true)
    {
        cout << "Unten-Links\n\a";
        Spielfigur_x--;
        Spielfigur_y++;
    }
        else if(GetAsyncKeyState(VK_NUMPAD3)&1 == true)
    {
        cout << "Unten-Rechts\n\a";
        Spielfigur_x++;
        Spielfigur_y++;
    }
        else if(GetAsyncKeyState(VK_NUMPAD9)&1 == true)
    {
        cout << "Oben-Rechts\n\a";
        Spielfigur_x++;
        Spielfigur_y--;
    }
        else if(GetAsyncKeyState(VK_NUMPAD7)&1 == true)
    {
        cout << "Unten-Links\n\a";
        Spielfigur_x--;
        Spielfigur_y--;
    }




}

    while (GetAsyncKeyState(0x41) == false) {   //http://msdn.microsoft.com/en-us/library/windows/desktop/dd375731%28v=vs.85%29.aspx

        for(i=1; i < 100; i++)
        {
            cout << "Hallo\n";
            cout << "Nico\n";

        system("cls");
        //Sleep(20);
    }


}


}



