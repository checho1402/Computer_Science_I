#include<iostream>
#include<ctime>
#include <stdlib.h>
#include <time.h>
#include <locale.h>


using namespace std;

const int f = 13;
const int c = 9;


int main(){
//setlocale(LC_CTYPE, "Spanish");//Usar carácteres españoles.
//Funciones.
void imprimirMapa(char tablero[f][c]);
void rellenarMapa(char tablero[f][c]);
void tirarDado(int a);
//Variables.
char tablero[f][c];
int movimiento;
char jugador01='1';
int mov_jugador01=0;
int recorridoFila[55]=   {10,11,12,12,12,12,11,10,9 ,8 ,7 ,7 ,7 ,6 ,5 ,5 ,5 ,4, 3, 2, 1, 0, 0, 0, 0, 1, 2, 2, 2, 1, 0, 0, 0, 0, 1, 2, 3, 4, 5, 5, 5, 6, 7, 7, 7, 8, 9, 10,11,12,12,12,12,11,10};
int recorridoColumna[55]={3 ,3 ,3 ,2 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,2 ,2 ,2 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,2 ,3 ,3 ,3 ,4 ,5 ,5 ,5 ,6 ,7 ,8 ,8 ,8 ,8, 8, 8, 7, 6, 6, 6, 7, 8, 8, 8, 8, 8, 8, 7, 6, 5, 5, 5};
char dado;
bool gameOver=false;
//Crear Mapa.
rellenarMapa(tablero);
//Crear primer jugador.
cout<<endl;
tablero[recorridoFila[mov_jugador01]][recorridoColumna[mov_jugador01]]=jugador01;
//Imprimir mapa.
imprimirMapa(tablero);
//Bucle principal.
while(gameOver==false){

	//Tirar dado.
	cout<<"Ingrese 'd' para tirar el dado: ";
	cin>>dado;
	cout<<endl;
	if (dado=='d'){
		srand((unsigned int)time(NULL));
		movimiento=1+ rand()%6;
	    cout << movimiento << endl;
	    tirarDado(movimiento);
		}
	//Actualizar jugador 1.
	tablero[recorridoFila[mov_jugador01]][recorridoColumna[mov_jugador01]]='X';
	mov_jugador01+=movimiento;
	if(mov_jugador01>54)
	mov_jugador01=54;
	tablero[recorridoFila[mov_jugador01]][recorridoColumna[mov_jugador01]]=jugador01;
	//Actualizar mapa.
	imprimirMapa(tablero);
	//VerificarVictoria.
	if(tablero[10][5]=='1'){
		cout<<"Ganó el jugador 1\n";
		gameOver=true;
	}
}



}

void imprimirMapa(char tablero[f][c]){
for(int x=0; x<13; x=x+1){
    for(int y=0; y<9 ;y = y+1){
        cout << tablero[x][y] << " ";
}
cout << endl;
}

}

void rellenarMapa(char tablero[f][c]){
for(int x=0; x<13; x=x+1){
for(int y=0; y<9 ;y = y+1){
        tablero[x][y] = 'â–²';
}

}

for(int x=0; x<6; x=x+1){
        tablero[x][0] = 'X';
        tablero[x][8] = 'X';
}


for(int x=7; x<13; x=x+1){
        tablero[x][0] = 'X';
        tablero[x][8] = 'X';
}

for(int x=0; x<4; x=x+1){
        tablero[0][x] = 'X';
        tablero[12][x] = 'X';
}


for(int x=0; x<4; x=x+1){
        tablero[0][x] = 'X';
        tablero[12][x] = 'X';
}

for(int x=5; x<9; x=x+1){
        tablero[0][x] = 'X';
        tablero[12][x] = 'X';
}

for(int x=3; x<6; x=x+1){
        tablero[2][x] = 'X';
}

for(int x=5; x<8; x=x+1){
        tablero[x][2] = 'X';
}

for(int x=5; x<8; x=x+1){
        tablero[x][6] = 'X';
}

for(int x=10; x<12; x=x+1){
        tablero[x][3] = 'X';
        tablero[x][5] = 'X';
}


for(int x=5; x<8; x=x+2){
        tablero[x][1] = 'X';
        tablero[x][7] = 'X';
}

for(int x=3; x<6; x=x+2){
        tablero[1][x] = 'X';

}

}




void tirarDado(int a){
    char va = 'â–²';
    char num = 'Â°' ;

    if (a == 1){
            cout << va << va << va << va << va << endl;
            cout << va << va << va << va << va << endl;
            cout << va << va << num << va << va<< endl;
            cout << va << va << va << va << va<< endl;
            cout << va << va << va << va << va << endl;

    }


    if (a == 2){
            cout << va << va << va << va << va << endl;
            cout << va << va << va << num << va << endl;
            cout << va << va << va << va << va<< endl;
            cout << va << num << va << va << va<< endl;
            cout << va << va << va << va << va << endl;

    }

    if (a == 3){
            cout << va << va << va << va << va << endl;
            cout << va << va << va << num << va << endl;
            cout << va << va << num << va << va<< endl;
            cout << va << num << va << va << va<< endl;
            cout << va << va << va << va << va << endl;

    }

    if (a == 4){
            cout << va << va << va << va << va << endl;
            cout << va << num << va << num << va << endl;
            cout << va << va << va << va << va<< endl;
            cout << va << num << va << num << va<< endl;
            cout << va << va << va << va << va << endl;

    }

    if (a == 5){
            cout << va << va << va << va << va << endl;
            cout << va << num << va << num << va << endl;
            cout << va << va << num << va << va<< endl;
            cout << va << num << va << num << va<< endl;
            cout << va << va << va << va << va << endl;

    }

    if (a == 6){
            cout << va << va << va << va << va << endl;
            cout << num << va << num << va << num << endl;
            cout << va << va << va << va << va<< endl;
            cout << num << va << num << va << num << endl;
            cout << va << va << va << va << va << endl;

    }



}

