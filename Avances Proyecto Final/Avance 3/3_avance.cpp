#include<iostream>
#include<ctime>
#include <locale.h>
#include <stdlib.h> 
#include <time.h> 

using namespace std;

const int f = 13;
const int c = 9;
char tablero[f][c];

int main(){
//setlocale(LC_CTYPE, "Spanish");//Usar carácteres españoles.
//Funciones.
    void imprimirMapa(char tablero[f][c]);
    void rellenarMapa(char tablero[f][c]);
    void mostrarDado(int a);
	void mov_jugador( int mov_dado, char j, int *mov_j);
	void tirarDado(char j, int *mov_dado );
//Variables.
    bool gameOver=false;
    char dado, j1='1', j2='2', j3='3', j4='4';
    int mov_dado, mov_j1=0, mov_j2=0, mov_j3=0, mov_j4=0, turnos=1;
//Crear Mapa.
    rellenarMapa(tablero);
//Imprimir mapa.
    imprimirMapa(tablero);
//Bucle principal.
    while(gameOver==false){
		
	    tirarDado(j1, &mov_dado);
	    mostrarDado(mov_dado);
		mov_jugador( mov_dado, j1, &mov_j1);
		imprimirMapa(tablero);
	
	    tirarDado(j2, &mov_dado);
	    mostrarDado(mov_dado);
		mov_jugador( mov_dado, j2, &mov_j2);
		imprimirMapa(tablero);
	
	    tirarDado(j3, &mov_dado);
	    mostrarDado(mov_dado);
		mov_jugador( mov_dado, j3, &mov_j3);
		imprimirMapa(tablero);
		
	    tirarDado(j4, &mov_dado);
	    mostrarDado(mov_dado);
		mov_jugador( mov_dado, j4, &mov_j4);
	    imprimirMapa(tablero);
	//verifica ganador
		if(tablero[10][5]!='X'){
			if (tablero[10][5]==j1){cout<<"Ganó el jugador"<<j1<<endl;}
			if(tablero[10][5]==j2){cout<<"Ganó el jugador"<<j2<<endl;}
			if (tablero[10][5]==j3){cout<<"Ganó el jugador"<<j3<<endl;}
			if (tablero[10][5]==j4){cout<<"Ganó el jugador"<<j4<<endl;}
			gameOver=true;
		}
    }
}


void tirarDado(char j, int *mov_dado ){
	char dado;
	cout<<"Jugador "<<j<<" ingrese 'd' para tirar el dado: "; cin>>dado;
	if (dado=='d'){
		srand((unsigned int)time(NULL));
	    *mov_dado=1+ rand()%6;
        cout << *mov_dado << endl;
	}
}

void mov_jugador( int mov_dado, char j, int *mov_j){
    int reF[55]={10,11,12,12,12,12,11,10,9 ,8 ,7 ,7 ,7 ,6 ,5 ,5 ,5 ,4, 3, 2, 1, 0, 0, 0, 0, 1, 2, 2, 2, 1, 0, 0, 0, 0, 1, 2, 3, 4, 5, 5, 5, 6, 7, 7, 7, 8, 9, 10,11,12,12,12,12,11,10};
    int reC[55]={3 ,3 ,3 ,2 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,2 ,2 ,2 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,2 ,3 ,3 ,3 ,4 ,5 ,5 ,5 ,6 ,7 ,8 ,8 ,8 ,8, 8, 8, 7, 6, 6, 6, 7, 8, 8, 8, 8, 8, 8, 7, 6, 5, 5, 5};
	tablero[reF[*mov_j]][reC[*mov_j]]='X';
	*mov_j += mov_dado;
	//Verifica limites
	if(*mov_j>54){
	   *mov_j=54;
       tablero[reF[*mov_j]][reC[*mov_j]]=j;
    }
	tablero[reF[*mov_j]][reC[*mov_j]] = j;
}

void imprimirMapa(char tablero[f][c]){
    for(int x=0; x<f; x++){
        for(int y=0; y<c ; y++){
            cout << tablero[x][y] << " ";
        }
        cout << endl;
    }
}

void rellenarMapa(char tablero[f][c]){
    for(int x=0; x<f; x++){
        for(int y=0; y<c ;y++){
            tablero[x][y] = ' ';
        }
    }
	for(int x=0; x<6; x++){
        tablero[x][0] = 'X';
        tablero[x][8] = 'X';
	}
	for(int x=7; x<13; x++){
        tablero[x][0] = 'X';
        tablero[x][8] = 'X';
	}
	for(int x=0; x<4; x++){
        tablero[0][x] = 'X';
        tablero[12][x] = 'X';
	}
	for(int x=0; x<4; x++){
        tablero[0][x] = 'X';
        tablero[12][x] = 'X';
    }
	for(int x=5; x<9; x++){
        tablero[0][x] = 'X';
        tablero[12][x] = 'X';
	}
	for(int x=3; x<6; x++){
        tablero[2][x] = 'X';
	}
	for(int x=5; x<8; x++){
        tablero[x][2] = 'X';
	}
	for(int x=5; x<8; x++){
        tablero[x][6] = 'X';
	}
	for(int x=10; x<12; x++){
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

void mostrarDado(int a){
    char va = '*';
    char num = 'O' ;

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


