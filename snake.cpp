#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef int mapa[120][30];
//FUNCIONES

void gotoxy(int x, int y);
void dibujar(mapa textura);
int mover(int &x, int &y,mapa cuerpo,mapa cabeza,int direccion);
void inicializa(mapa cabeza, mapa cuerpo, mapa bordes, mapa manzana);
bool comprobacion(int x, int y, mapa manzana);
void desplazar(int memoria[3600]);
void mover2(int &x, int &y, int memoria[3600]);
void random_manzana(mapa manzana, mapa cuerpo, mapa cabeza);
void test_lost(int x, int y, mapa cuerpo,mapa bordes);


int main() {
	//VARIABLES
	system("color 74");
	mapa cabeza, cuerpo, bordes, manzana;
	int memoria[3600];
	int contador = 0; 
	int x = 60;
	int y = 15;
	int x1 = 60;
	int y1 = 16;
	
	inicializa(cabeza, cuerpo, bordes, manzana);
	dibujar(cabeza);
	dibujar(cuerpo);
	dibujar(bordes);
	dibujar(manzana);
	memoria[0] = 119;
	int direccion = 119;
	
	//LOOP
	while (true) {
		
		gotoxy(15, 10);
		Sleep(30);
		direccion=mover(x, y,cuerpo,cabeza,direccion);
		
			
			if (comprobacion(x, y, manzana)) 
			{
				contador++;
				memoria[contador] = direccion;
				
				random_manzana(manzana, cuerpo, cabeza);
				manzana[x][y] = 4;
				
			}
			else {
				cuerpo[x1][y1] = 4;
				mover2(x1, y1, memoria);
				desplazar(memoria);
				memoria[contador] = direccion;
			}
			system("cls");
			test_lost(x, y, cuerpo,bordes);
			dibujar(cabeza);
			dibujar(cuerpo);
			dibujar(bordes);
			dibujar(manzana);
			gotoxy(0, 29);
			cout << ".";
		
		
	}
}

void dibujar(mapa textura) {
	int x = 0;
	int y = 0;
	while (x < 120) {
		while (y < 30) {
			if (textura[x][y] == 0) {
				gotoxy(x, y);
				cout << "-";
			}
			if (textura[x][y] == 1) {
				gotoxy(x, y);
				cout << "X";
			}
			if (textura[x][y] == 2) {
				gotoxy(x, y);
				cout << "O";
			}
			if (textura[x][y] == 3) {
				gotoxy(x, y);
				cout << "M";
			}
			y++;
		}
		y = 0;
		x++;
	}
}
void gotoxy(int x, int y) {
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}
int mover(int &x, int &y,mapa cuerpo, mapa cabeza,int direccion) {
	
	
		cabeza[x][y] = 4;
		cuerpo[x][y] = 1;
		
		if (GetAsyncKeyState(87) == -32767) {
			y--;
			direccion = 119;
			cabeza[x][y] = 2;
			return direccion;
			
		}
		else if (GetAsyncKeyState(65) == -32767) {
			x--;
			direccion = 97;
			cabeza[x][y] = 2;
			return direccion;
			
		}
		else if (GetAsyncKeyState(83) == -32767) {
			y++;
			direccion = 115;
			cabeza[x][y] = 2;
			return direccion;
		}
		else if(GetAsyncKeyState(68) == -32767){
			x++;
			direccion = 100;
			cabeza[x][y] = 2;
			return direccion;
		}
			 else {
		
		switch (direccion) {
		case 119:
			y--;
			break;
		case 97:
			x--;
			break;
		case 115:
			y++;
			break;
		case 100:
			x++;
			break;
		}
		cabeza[x][y] = 2;
		return direccion;
	}
}
void mover2(int &x, int &y, int memoria[3600]) {
	int direccion;
	direccion = memoria[0];
	switch (direccion) {
		case 119:
			y--;
			break;
		case 97:
			x--;
			break;
	case 115:
			y++;
			break;
	case 100:
			x++;
			break;
	}
}
void desplazar(int memoria[3600]) {
	int x = 1;
	while (x < 3600) {
		memoria[x - 1] = memoria[x];
		x++;
	}
}
void inicializa(mapa cabeza,mapa cuerpo,mapa bordes,mapa manzana) {
	cabeza[60][15] = 2;
	manzana[30][7] = 3;
	cuerpo[60][16] = 1;
	int x = 0;
	int y = 0;
	while (y< 30) {
		while (x < 120) {
			bordes[x][y] = 0;
			x++;
		}
		x = 0;
		y = y + 29;
	}
	y = 0;
	x = 0;
	while (x < 120) {
		while (y<30) {
			bordes[x][y] = 0;
			y++;
		}
		y = 0;
		x = x + 119;
	}

}
bool comprobacion(int x, int y, mapa manzana) {
	if (manzana[x][y] == 3) {
		return true;
	}
	else {
		return false;
	}
}
void random_manzana(mapa manzana, mapa cuerpo, mapa cabeza) {
	srand(time(NULL));
	int x = -3;
	int y = -3;
	int c = 0;
	while (manzana[x][y] == 3 || cuerpo[x][y] == 1 || cabeza[x][y] == 2||c==0) {
		x = rand() % 119 + 1;
		y = rand() % 29 + 1;
		c++;
	}
	manzana[x][y] = 3;
	
	
}
void test_lost(int x, int y, mapa cuerpo,mapa bordes) {
	if (cuerpo[x][y] == 1||bordes[x][y]== 0) {
		system("cls");
		cout << "HAS PERDIDO"<<endl<<endl;
	
		system("pause");
		exit(1);
	}
	
}