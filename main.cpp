#include <iostream>
#include <chrono>
#include <windows.h>
#include <thread>
using namespace std;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

char mapa[10][10] = {
	'O','O','O','O','O','O','O','O','O','O',
	'O','O','O','O','O','O','O','O','O','O',
	'O','O','O','O','O','O','O','O','O','O',
	'O','O','O','O','Z','O','O','O','O','O',
	'O','O','O','Z','O','O','O','O','O','O',
	'O','Z','Z','O','O','O','O','O','O','O',
	'O','O','O','O','O','O','O','O','O','O',
	'O','O','O','O','O','O','Z','Z','Z','Z',
	'Z','Z','Z','Z','Z','Z','Z','Z','Z','Z',
	'Z','Z','Z','Z','Z','Z','Z','Z','Z','Z'
};

int main()
{
	//kierunki: GORA - 1, PRAWO - 2, DOL - 3, LEWO - 4
	using namespace std::this_thread;
	using namespace std::chrono;
	int x = 0,Xkierunku=1, Ykierunku=7, y = 7, i = 0, j = 0, liczbaodswiezen = 0, ileskoku = 0, kierunek = 2;
	bool czydalej = true, czysiezmienia = true, czyzablokowanyskok = false, czyskacze = false;
	while (czydalej) {
		if (czyzablokowanyskok == false) {
			if (GetAsyncKeyState(VK_UP)) {
				kierunek = 1;
				czysiezmienia = true;
				if (y > 0) {
					if (mapa[y - 1][x] == 'O') {
						czyskacze = true;
						ileskoku = 0;
						czyzablokowanyskok = true;
					}
				}
			}
			else if (GetAsyncKeyState(VK_DOWN)) {
				cout << "eee";
				kierunek = 3;
				czysiezmienia = true;
				if (y < 9) {
					if (mapa[y + 1][x] == 'O') {
						y++;
						czyzablokowanyskok = true;
					}
				}
			}
		}
		else {
			czysiezmienia = true;
			if (czyskacze == true && ileskoku < 3 && mapa[y - 1][x] == 'O') {
					y--;
					ileskoku++;
			}
			else{
				czyskacze = false;
			}
		}
		if (GetAsyncKeyState(VK_RIGHT)) {
			kierunek = 2;
			czysiezmienia = true;
			if (x < 9) {
				if (mapa[y][x + 1] == 'O') {
					x++;
				}
			}
		}
		else if (GetAsyncKeyState(VK_LEFT)) {
			kierunek = 4;
			czysiezmienia = true;
			if (x > 0) {
				if (mapa[y][x - 1] == 'O') {
					x--;
				}
			}
		}
		if (czyskacze == false) {
			if (mapa[y + 1][x] == 'O') {
				y++;
				czysiezmienia = true;
			}
			else {
				czyzablokowanyskok = false;
			}
		}
		if (kierunek==1) {
			Xkierunku = x;
			Ykierunku = y - 1;
		}
		else if (kierunek==2) {
			Xkierunku = x + 1;
			Ykierunku = y;
		}
		else if (kierunek==3) {
			Xkierunku = x;
			Ykierunku = y + 1;
		}
		else if (kierunek==4) {
			Xkierunku = x - 1;
			Ykierunku = y;
		}
		if (GetAsyncKeyState(VK_SPACE)) {
			if (mapa[Ykierunku][Xkierunku] == 'Z')
			{
				mapa[Ykierunku][Xkierunku] = 'O';
			}
			else if (mapa[Ykierunku][Xkierunku] == 'O') {
				mapa[Ykierunku][Xkierunku] = 'Z';
			}
			sleep_for(nanoseconds(100000000));
			czysiezmienia = true;
		}
		if (czysiezmienia) {
			system("cls");
			czysiezmienia = false;
			//cout << "Y: " << y << endl << "X: " << x << endl;
			j = 0;
			i = 0;
			while (i < 10) {
				while (j < 10) {
					if (j == x && y == i)
					{
						SetConsoleTextAttribute(h, 8);
					}
					else if (j == Xkierunku && i == Ykierunku) {
						SetConsoleTextAttribute(h, 4);
					}
					else if(mapa[i][j]=='Z') {
						SetConsoleTextAttribute(h, 7);
					}
					else {
						SetConsoleTextAttribute(h, 3);
					}
					cout << (char)(219) << (char)(219);
					j++;
				}
				cout << endl;
				j = 0;
				i++;
			}
		}
		sleep_for(nanoseconds(10000000));
	}
}
