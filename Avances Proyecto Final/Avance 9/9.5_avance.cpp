#include<iostream>
#include<ctime>
#include <locale.h>//Caracteres especiales
#include <stdlib.h>
#include<fstream>
#include "Cartas.h"
#include "minijuegos.h"
#include "funciones.cpp"

using namespace std;

//Dayevska Caceres
//Roberto Cayro
//Sergio Ramos
//Gabriel Valdivia



//variables generales
char tablero[f][c];
int m_1_F[55]={10,11,12,12,12,12,11,10,9 ,8 ,7 ,7 ,7 ,6 ,5 ,5 ,5 ,4, 3, 2, 1, 0, 0, 0, 0, 1, 2, 2, 2, 1, 0, 0, 0, 0, 1, 2, 3, 4, 5, 5, 5, 6, 7, 7, 7, 8, 9,10,11,12,12,12,12,11,10};
int m_1_C[55]={3 ,3 ,3 ,2 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,2 ,2 ,2 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,2 ,3 ,3 ,3 ,4 ,5 ,5 ,5 ,6 ,7 ,8 ,8 ,8 ,8, 8, 8, 7, 6, 6, 6, 7, 8, 8, 8, 8, 8, 8, 7, 6, 5, 5, 5};
int m_2_F[55]={9,8,7,6,5,4,3,2,2,2,2,2,2,2,2,2,2, 2, 3, 4, 5, 6, 7, 8, 9,10,11,11,11,11,11,11,11,11,10,9,8,7,6,5,4,4,4,4,4,4,5,6,7,8,9,9,9,9,8  }; // 55
int m_2_C[55]={1,1,1,1,1,1,1,1,1,2,3,4,5,6,7,8,9,10,10,10,10,10,10,10,10,10,10, 9, 8, 7, 6, 5, 4, 3, 3,3,3,3,3,3,3,4,5,6,7,8,8,8,8,8,8,7,6,5,5    }; // 55
int m_3_F[55]={0,0,0,0,0,0,0,1,2,2,2,2,3,3,3,3,4,5,5,5,5,6,6,6,6,7,7,7,8, 9,9,9,10,10,10,10,11,11,11,11,11,12,13,13,13,13,13,13,13,13,13,13,13,13,13 }; // 38 +13
int m_3_C[55]={10,9,8,7,6,5,4,3,4,5,6,7,8,9,10,11,12,11,10,9,8,7,6,5,4,3,2,1,0,1,2,3,4,5,6,7,8,9,10,11,12,12,12,11,10,9,8,7,6,5,4,3,2,1,0 }; //51-3 = 48 +7
int carta;
bool ocupado_1=false, ocupado_2=false, ocupado_3=false, ocupado_4=false, ocupado_5=false, ocupado_6=false, ocupado_7=false, ocupado_8=false, ocupado_9=false, ocupado_10=false;
string pregunta, opciona, opcionb, opcionc, opciond, opcione;
ifstream Lec;

//Clases.
class jugador{
	public:
		char id, pos;
		int movi;
		bool bomba, escudo;
	jugador(char j,int mov, bool bomb, bool escud=false){
		id=j;
		movi=mov;
		bomba = bomb;
		escudo=escud;
	}
};
class mapa{
	public:
		int recorrido, corF[60], corC[60];
	mapa(int f[55], int c[55],int lar){
		for(int x=0;x<lar;x++){
			corF[x]=f[x];
			corC[x]=c[x];
		}
		recorrido=lar;
	}
};

//Objetos.
	jugador j1('1',0,false);
	jugador j2('2',0,false);
	jugador j3('3',0,false);
	jugador j4('4',0,false);
	mapa mapa1(m_1_F,m_1_C,55);
	mapa mapa2(m_2_F,m_2_C,55);
    mapa mapa3(m_3_F,m_3_C,55);

//Funciones.
    void recompensa(int  puntaje, jugador *j, mapa *map, int random);
    void rellenarMapa(char tablero[f][c],mapa *map);
    void refrescarMapa(jugador j, mapa *map);
	void imprimirMapa(char tablero[f][c]);
    void comprobarCasilla(jugador j,mapa *map, int random);
    void mostrarDado(int a);
	void tirarDado(int *mov_dado ,jugador j);
    void moverJugador(jugador *j, int mov_dado, mapa *map,int random);
	void recogerBonificacion(jugador *j,mapa *map, int random);
    void recogerCastigo(jugador *j,mapa *map, int random);
    void otherPlayer_RA(int llave, jugador *j,int movR,mapa *map, int random );

	bool verRegistros(ifstream &lec);
    bool verificarGanador(char tablero[f][c],int j1,int j2,int j3,int j4);
    bool preguntas(char num, bool ocupado, char rpta);

int main(){

	


	setlocale(LC_CTYPE, "Spanish");//Usar carácteres españoles.
//Variables y objetos internos.
    bool gameOver=false;
    char dado;
    int mov_dado,elec_mapa;
	mapa *mapa_e=&mapa3;

//Elegir Mapa.
	cout<<"Elija uno de los mapas disponibles(1,2,3)\n"; cin>>elec_mapa;
	switch(elec_mapa){
		case 1:mapa_e=&mapa1;break;
		case 2:mapa_e=&mapa2;break;
		case 3:mapa_e=&mapa3;break;
		default:cout<<"Elección incorrecta, usando mapa1 por defecto\n";mapa_e=&mapa1;
	}
//Crear Mapa.
    rellenarMapa(tablero,mapa_e);
    imprimirMapa(tablero);
//Bucle principal.
    while(gameOver==false){

        srand((unsigned int)time(NULL));
	    int a= 1+rand()%5;
	    //jugador 1
	    tirarDado(&mov_dado, j1);
		refrescarMapa(j1,mapa_e);
		moverJugador(&j1,mov_dado,mapa_e,a);
		imprimirMapa(tablero);
		if (verificarGanador(tablero,j1.id,j2.id,j3.id,j4.id)==true) { gameOver=true; }
        //jugador 2
		if(gameOver==false){
	        tirarDado(&mov_dado,j2);
		    refrescarMapa(j2,mapa_e);
		    moverJugador(&j2,mov_dado,mapa_e,a);
		    imprimirMapa(tablero);
		    if (verificarGanador(tablero,j1.id,j2.id,j3.id,j4.id)==true) { gameOver=true; }
		}
        //jugador 3
		if(gameOver==false){
	        tirarDado( &mov_dado, j3);
		    refrescarMapa(j3,mapa_e);
		    moverJugador(&j3,mov_dado,mapa_e,a);
		    imprimirMapa(tablero);
		    if (verificarGanador(tablero,j1.id,j2.id,j3.id,j4.id)==true) { gameOver=true; }
		}
        //jugador 4
		if(gameOver==false){
	        tirarDado(&mov_dado, j4);
		    refrescarMapa(j4,mapa_e);
		    moverJugador(&j4,mov_dado,mapa_e,a);
	        imprimirMapa(tablero);
	        if (verificarGanador(tablero,j1.id,j2.id,j3.id,j4.id)==true) { gameOver=true; }
		}
	}
}
//////////////////////////////////////////////////////////// FUNCIONES //////////////////////////////////////////////////
void imprimirMapa(char tablero[f][c]){
    for(int x=0; x<f; x++){
    	cout<<"\t";
        for(int y=0; y<c ; y++){
            cout << tablero[x][y] << " ";
        }
        cout << endl;
    }
}
void rellenarMapa(char tablero[f][c], mapa *map){
    for(int x=0; x<f; x++){
        for(int y=0; y<c ;y++){
        	if (tablero[x][y]!='1'&& tablero[x][y]!='2'&& tablero[x][y]!='3'&& tablero[x][y]!='4') tablero[x][y] = ' ';
        }
    }
    for (int a=0 ; a<map->recorrido ; a++){
    	if (tablero[map->corF[a]][map->corC[a]]!='1'&& tablero[map->corF[a]][map->corC[a]]!='2'&& tablero[map->corF[a]][map->corC[a]]!='3'&& tablero[map->corF[a]][map->corC[a]]!='4')
    	tablero[map->corF[a]][map->corC[a]] = 'X'; //casilla vacia
    }
    for (int a=5 ; a<map->recorrido ; a+=6){
    	if (tablero[map->corF[a]][map->corC[a]]!='1'&& tablero[map->corF[a]][map->corC[a]]!='2'&& tablero[map->corF[a]][map->corC[a]]!='3'&& tablero[map->corF[a]][map->corC[a]]!='4')
    	tablero[map->corF[a]][map->corC[a]] = 'P'; //casilla con carta de pregunta
    }
    for (int a=1 ; a<map->recorrido ; a+=6){
    	if (tablero[map->corF[a]][map->corC[a]]!='1'&& tablero[map->corF[a]][map->corC[a]]!='2'&& tablero[map->corF[a]][map->corC[a]]!='3'&& tablero[map->corF[a]][map->corC[a]]!='4')
    	tablero[map->corF[a]][map->corC[a]] = 'B'; //casilla bomba
    }
    for (int a=3 ; a<map->recorrido ; a+=6){ //casilla con carta de bonificación o castigo
    	if (tablero[map->corF[a]][map->corC[a]]!='1'&& tablero[map->corF[a]][map->corC[a]]!='2'&& tablero[map->corF[a]][map->corC[a]]!='3'&& tablero[map->corF[a]][map->corC[a]]!='4')
    	tablero[map->corF[a]][map->corC[a]] = 'C';
    }
    for (int a=2 ; a<map->recorrido ; a=a+7){ //casilla que te envia a un juego aleatorio
    	if (tablero[map->corF[a]][map->corC[a]]!='1'&& tablero[map->corF[a]][map->corC[a]]!='2'&& tablero[map->corF[a]][map->corC[a]]!='3'&& tablero[map->corF[a]][map->corC[a]]!='4')
    	tablero[map->corF[a]][map->corC[a]] = 'M';
    }
}
void comprobarCasilla(jugador *j,mapa *map, int random){
    int g;
	char temp =tablero[map->corF[j->movi]][map->corC[j->movi]];
	if(temp=='P'){ //te toca una pregunta, puedes tener una bonificacion o un castigo
		cout<<"El jugador: "<<j->id<<" debe responder UNA pregunta "<<endl;
		if(verRegistros(Lec)==true) recogerBonificacion(j,map,random); //"ver registros" mostrata la pregunta si respondemos correctamente nos da un abonificacion
		else recogerCastigo(j,map,random); //si respondemos incorrectamente un castigo
	}
	else if(temp=='C'){ //te toca una carta aleatoria
		srand((unsigned int)time(NULL));
	    carta=rand()%17;//rand()%17;
	    cout<<cartas[carta]<<endl; // se elige aleatoriamente una carta de "Cartas.h"
	    switch(carta){
	    	case 0:moverJugador(j,3,map,random);break; //avanaza 3 casillas
	    	case 1:moverJugador(j,4,map,random);break; //avanaza 4 casillas
	    	case 2:moverJugador(j,5,map,random);break; //avanaza 5 casillas
	    	case 9:moverJugador(j,3,map,random);break; //avanaza 3 casillas
	    	case 10:moverJugador(j,(-3),map,random);break; //retrocede 3 casillas
	    	case 11:moverJugador(j,(-3),map,random);break; //retrocede 3 casillas
	    	case 12:moverJugador(j,(-4),map,random);break; //retrocede 4 casillas
	    	case 13:moverJugador(j,(-5),map,random);break; //retrocede 5 casillas
	    	case 7: j->escudo=true;break; //Ganar un escudo.
			case 14: j->bomba=true;break;//Carta bomba.
			case 15: j->bomba=true;break;//Carta bomba.
	    	case 3:otherPlayer_RA(0, j,0,map,random);break;//Tirar una bomba a alguien.
			case 4:otherPlayer_RA(1, j,-3,map,random);break;//Hacer que alguien retroceda 3 casillas.
			case 5:otherPlayer_RA(1, j,-4,map,random);break;//Hacer que alguien retroceda 4 casillas.
			case 6:otherPlayer_RA(1, j,-5,map,random);break;//Hacer que alguien retroceda 5 casillas.
			case 8: otherPlayer_RA(2, j,0,map,random);break;//hacer que otro jugador reciba una carta castigo
			case 16:otherPlayer_RA(3, j,0,map,random);break; //hacer que otro jugador reciba una carta bonificación
			case 17:otherPlayer_RA(3, j,0,map,random);break; //hacer que otro jugador reciba una carta bonificación
	    }
	}
	else if(temp=='B'){ //te toco una bomba
	    cout << "Pierdes un turno"<<endl;
		j->bomba=true;
	}
	else if(temp == 'M'){ //te toco un juego aleatorio, si ganas tendras un abonificación si no un castigo
        int s_mn = random, puntaje=0;
    	if(s_mn == 1){ puntaje = laberinto(); recompensa(puntaje,j,map,random);}        //te toco el juego de laberinto
    	if(s_mn == 2){ puntaje = gato(); recompensa(puntaje,j,map,random);}             //te toco el juego del gato
    	if(s_mn == 3){ puntaje = minijuego_3_raya(); recompensa(puntaje,j,map,random);} //te toco jugar de 3 en raya
    	if(s_mn == 4){ puntaje = busca_minas(); recompensa(puntaje,j,map,random);}      //te toco jugar busca minas
    	if(s_mn == 5){ puntaje = tron_M_juego(); recompensa(puntaje,j,map,random);}

	}
	tablero[map->corF[j->movi]][map->corC[j->movi]] = j->id;
}
void otherPlayer_RA(int llave, jugador *j,int movR,mapa *map, int random ){
	if (llave == 0 ){//Tirar una bomba a alguien.
		int jBombardeado;
	    cout<<"Jugador "<<j->id<<", escribe el número del jugador al que quieras tirarle una bomba: "; cin>>jBombardeado; cout<<endl;
	    switch(jBombardeado){
			case 1:cout<<"El jugador "<<j1.id<<" recibe una bomba"<<endl;j1.bomba=true;break;
			case 2:cout<<"El jugador "<<j2.id<<" recibe una bomba"<<endl;j2.bomba=true;break;
			case 3:cout<<"El jugador "<<j3.id<<" recibe una bomba"<<endl;j3.bomba=true;break;
			case 4:cout<<"El jugador "<<j4.id<<" recibe una bomba"<<endl;j4.bomba=true;break;
		}
	}
	if (llave ==1){//Hacer que alguien retroceda x casillas.
		int mostrarmov, jRetrocede;
		if (movR == -3) mostrarmov=3;
		if (movR == -4) mostrarmov=4;
		if (movR == -5) mostrarmov=5;
		cout<<"Jugador "<<j->id<<", escribe el número del jugador que quieres que retroceda "<<mostrarmov<<" casillas: "; cin>>jRetrocede; cout<<endl;
		switch(jRetrocede){
			case 1:cout<<"El jugador "<<j1.id<<" retrocede "<< mostrarmov <<" casillas"<<endl;refrescarMapa(j1,map);moverJugador(&j1,(movR),map,random);break;
			case 2:cout<<"El jugador "<<j2.id<<" retrocede "<< mostrarmov <<" casillas"<<endl;refrescarMapa(j2,map);moverJugador(&j2,(movR),map,random);break;
			case 3:cout<<"El jugador "<<j3.id<<" retrocede "<< mostrarmov <<" casillas"<<endl;refrescarMapa(j3,map);moverJugador(&j3,(movR),map,random);break;
			case 4:cout<<"El jugador "<<j4.id<<" retrocede "<< mostrarmov <<" casillas"<<endl;refrescarMapa(j4,map);moverJugador(&j4,(movR),map,random);break;
		}
	}
	if (llave == 2){ //hacer que otro jugador reciba una carta castigo
		int otroJugador;
		cout<<"Jugador "<<j->id<<" escribe el número del jugador que quieres que recoja una carta de castigo: "; cin>>otroJugador; cout << endl;
		switch(otroJugador){
			case 1:cout<<"EL jugador "<<j1.id<<" tiene que recoger una carta de castigo\n"; recogerCastigo(&j1,map,random);break;
			case 2:cout<<"EL jugador "<<j2.id<<" tiene que recoger una carta de castigo\n"; recogerCastigo(&j2,map,random);break;
			case 3:cout<<"EL jugador "<<j3.id<<" tiene que recoger una carta de castigo\n"; recogerCastigo(&j3,map,random);break;
			case 4:cout<<"EL jugador "<<j4.id<<" tiene que recoger una carta de castigo\n"; recogerCastigo(&j4,map,random);break;
		}
	}
	if (llave == 3){ //hacer que otro jugador reciba una carta bonificación
	    int otroJugador;
		cout<<"Jugador "<<j->id<<" escribe el número del jugador que quieres que recoja una carta de bonificación: "; cin>>otroJugador; cout << endl;
		switch(otroJugador){
			case 1:cout<<"EL jugador "<<j1.id<<" tiene que recoger una carta de bonificación\n"; recogerBonificacion(&j1,map,random);break;
			case 2:cout<<"EL jugador "<<j2.id<<" tiene que recoger una carta de bonificación\n"; recogerBonificacion(&j2,map,random);break;
			case 3:cout<<"EL jugador "<<j3.id<<" tiene que recoger una carta de bonificación\n"; recogerBonificacion(&j3,map,random);break;
			case 4:cout<<"EL jugador "<<j4.id<<" tiene que recoger una carta de bonificación\n"; recogerBonificacion(&j4,map,random);break;
		}
	}
}

void recompensa(int  puntaje, jugador *j, mapa *map,int random){ //Efectos del jugador despues de estar en una casilla "M"
    if (puntaje >= 2){ moverJugador(j,(-3),map,random); }
    if (puntaje == 1){ moverJugador(j,(+5),map,random); }
    if (puntaje == 5){ cout << "No hay recompensa, es un empate"; }
	if (puntaje == 7){ moverJugador(j,(-3),map,random); }
    if (puntaje == 8){ moverJugador(j,(+5),map,random); }
}
void recogerBonificacion(jugador *j,mapa *map, int random){
	cout<<"CARTA BONIFICACIÓN:\n";
	srand((unsigned int)time(NULL));
	int c_B = rand()%9; // se lige una bonificacion aleatoriamente
	cout<<bonificaciones[c_B]<<endl;
	switch(c_B){
		case 0: moverJugador(j,3,map,random);break; //Avanzar 3.
		case 1: moverJugador(j,4,map,random);break; //Avanzar 4.
		case 2: moverJugador(j,5,map,random);break; //Avanzar 5.
		case 7: j->escudo=true;break; //La bomba no te afectara
		case 3:otherPlayer_RA(0, j,0,map,random);break;//Tirar una bomba a alguien.
		case 4:otherPlayer_RA(1, j,-3,map,random);break;//Hacer que alguien retroceda 3 casillas.
		case 5:otherPlayer_RA(1, j,-4,map,random);break;//Hacer que alguien retroceda 4 casillas.
		case 6:otherPlayer_RA(1, j,-5,map,random);break;//Hacer que alguien retroceda 5 casillas.
		case 8: otherPlayer_RA(2, j,0,map,random);break;//hacer que otro jugador reciba una carta castigo
	}
}
void recogerCastigo(jugador *j,mapa *map, int random){
	cout<<"CARTA CASTIGO:\n";
	srand((unsigned int)time(NULL));
	int c_C = rand()%5; // se escoje un castigo aleatorio
	cout<<castigos[c_C]<<endl;
	switch(c_C){
		case 0:moverJugador(j,(-3),map,random);break; //Retrocede 3
		case 1:moverJugador(j,(-4),map,random);break; //Retrocede 4
		case 2:moverJugador(j,(-5),map,random);break; //Retrocede 5
		case 3:j->bomba=true;break; //Pierdes un turno
		case 4:otherPlayer_RA(3, j,0,map,random);break; //hacer que otro jugador reciba una carta bonificación
	}
}
void moverJugador(jugador *j, int mov_dado, mapa *map, int random){ // true = bomba activada
	if ( (j->bomba==false && j->escudo==false)||(j->bomba==false && j->escudo == true)){//avanzas segun el dado
		j->movi += mov_dado;
	    //Verifica limites
        if(j->movi>54) { j->movi=54; }
        if(j->movi<0) { j->movi=0; }
        comprobarCasilla(j,map,random); //ver si estas en una casilla "C"carta, "M"juego, "P"pregunta, "B"bomba.
	}
	else if(j->bomba==true && j->escudo ==true){ //se activa el escudo y avanzas apesar de tener una bomba
		cout<<"Jugador "<<j->id<<" su escudo evitó el efecto de la bomba\n";
		j->escudo=false;
		j->movi += mov_dado;
	    //Verifica limites
        if(j->movi>54) { j->movi=54; }
        if(j->movi<0) { j->movi=0; }
        comprobarCasilla(j,map,random); //ver si estas en una casilla "C"carta, "M"juego, "P"pregunta, "B"bomba.
	}
	else if (j->bomba==true && j->escudo==false) {// se activa la bomca y pierdes el turno por lo que no avanzas
		cout << "El jugador "<< j->id << " está inmovilizado por la bomba, ¡no puede moverse!" << endl;
		j->bomba = false ;
	}
}
void refrescarMapa(jugador j, mapa *map){ //Permite que no se borren las casillas "C" "M" "P" "B" y sus funcionalidades
	if ( j.bomba==false){
        if(tablero[map->corF[j.movi]][map->corC[j.movi]]==j.id) { tablero[map->corF[j.movi]][map->corC[j.movi]]='X'; }
	    rellenarMapa(tablero,map);
    }
}
void tirarDado(int *mov_dado ,jugador j){
	if ( j.bomba==false){
		char dado;
		cout<<"Jugador "<<j.id<<" ingrese 'd' para tirar el dado: "; cin>>dado;
		if (dado=='d'){
			srand((unsigned int)time(NULL));
	    	*mov_dado=1+ rand()%6; //un numero aleatorio del [1-6] ya que es un dado
        	cout << *mov_dado << endl; //se imprime en numero
		}
	    mostrarDado(*mov_dado); //se muestra el dado segun el número aleatorio
    }
}
bool verificarGanador(char tablero[f][c],int j1,int j2,int j3,int j4){
	if(tablero[10][5]!='X'){ //si la ultima casilla de los mapas es diferente a "X" existe un ganador
		if (tablero[10][5]==j1){cout<<"Ganó el jugador"<<j1<<endl;return true;}
		if (tablero[10][5]==j2){cout<<"Ganó el jugador"<<j2<<endl;return true;}
		if (tablero[10][5]==j3){cout<<"Ganó el jugador"<<j3<<endl;return true;}
		if (tablero[10][5]==j4){cout<<"Ganó el jugador"<<j4<<endl;return true;}
	}
	return false;
}
bool  preguntas(char num, bool ocupado, char rpta){ //muestra en pantalla su pregunta y sus alternativas dependiendo de eso se activara la bonificacion o castigo
    if(pregunta[0]==num && ocupado==false){
        cout<<pregunta<<endl;
        cout<<opciona<<endl;
        cout<<opcionb<<endl;
        cout<<opcionc<<endl;
        cout<<opciond<<endl;
        cout<<opcione<<endl;
        ocupado=true; // para que no se repita la pregunta
        char respuesta;
        cout<<"Ingrese la respuesta: ";cin>>respuesta;
        if(respuesta == rpta){ //respuesta correcta, se retorna true para activar la bonificación
			cout<<"La respuesta es correcta, ganaste una bonificación "<<endl;
			return true;
		}
        else {  //respuesta incorrecta, se retorna false
			cout<<"La respuesta es incorrecta"<<endl;
			return false;
		}
    }
}
bool verRegistros(ifstream &lec){
    lec.open("Base de datos - Preguntas.txt",ios::in);
    lec >> pregunta;
    while(!lec.eof()){
        lec>>opciona;
        lec>>opcionb;
        lec>>opcionc;
        lec>>opciond;
        lec>>opcione;
        if(ocupado_1==false) { return preguntas('1', ocupado_1, 'd'); break;}
        else if(ocupado_2==false) { return preguntas('2', ocupado_2, 'a');break; }
        else if(ocupado_3==false) { return preguntas('3', ocupado_3, 'a');break; }
        else if(ocupado_4==false) { return preguntas('4', ocupado_4, 'b');break; }
        else if(ocupado_5==false) { return preguntas('5', ocupado_5, 'c');break; }
        else if(ocupado_6==false) { return preguntas('6', ocupado_6, 'c');break; }
        else if(ocupado_7==false) { return preguntas('7', ocupado_7, 'b');break; }
        else if(ocupado_8==false) { return preguntas('8', ocupado_8, 'c');break; }
        else if(ocupado_9==false) { return preguntas('9', ocupado_9, 'd');break; }
	    lec>>pregunta;
	}
	lec.close();
}

void mostrarDado(int a){ //se muestra el numero del dado un poco mas visual
    char va = '|', num = 'O' ;
	switch(a){
		case 1:
			cout <<"\t\t"<< va<<' '<< va<<' ' << va<<' ' << va<<' ' << va<<' ' << endl;
            cout <<"\t\t"<< va<<' ' << va<<' ' << va<<' ' << va<<' ' << va<<' ' << endl;
            cout <<"\t\t"<< va<<' ' << va<<' ' << num<<' ' << va<<' ' << va<<' '<< endl;
            cout <<"\t\t"<< va<<' ' << va<<' ' << va<<' ' << va<<' ' << va<<' '<< endl;
            cout <<"\t\t"<< va<<' ' << va<<' ' << va<<' ' << va<<' ' << va<<' ' << endl;break;
		case 2:
			cout <<"\t\t"<< va<<' ' << va<<' ' << va<<' ' << va<<' ' << va<<' ' << endl;
            cout <<"\t\t"<< va<<' ' << va<<' ' << va<<' ' << num<<' ' << va<<' '<< endl;
            cout <<"\t\t"<< va<<' ' << va<<' ' << va<<' ' << va<<' ' << va<<' '<< endl;
            cout <<"\t\t"<< va<<' ' << num<<' ' << va<<' ' << va<<' ' << va<<' '<< endl;
            cout <<"\t\t"<< va<<' ' << va<<' ' << va<<' ' << va<<' ' << va<<' '<< endl;break;
		case 3:
			cout <<"\t\t"<< va<<' ' << va<<' ' << va<<' ' << va<<' ' << va<<' ' << endl;
            cout <<"\t\t"<< va<<' ' << va<<' ' << va<<' ' << num<<' '<< va<<' ' << endl;
            cout <<"\t\t"<< va<<' ' << va<<' ' << num<<' ' << va<<' ' << va<<' '<< endl;
            cout <<"\t\t"<< va<<' ' << num<<' ' << va<<' ' << va<<' ' << va<<' '<< endl;
            cout <<"\t\t"<< va<<' ' << va<<' ' << va<<' ' << va<<' ' << va<<' ' << endl;break;
		case 4:
			cout <<"\t\t"<< va<<' ' << va<<' ' << va<<' ' << va<<' ' << va<<' ' << endl;
            cout <<"\t\t"<< va<<' ' << num<<' ' << va<<' ' << num<<' ' << va<<' ' << endl;
            cout <<"\t\t"<< va<<' ' << va<<' ' << va<<' ' << va<<' ' << va<<' '<< endl;
            cout <<"\t\t"<< va<<' ' << num<<' ' << va<<' ' << num<<' ' << va<<' '<< endl;
            cout <<"\t\t"<< va<<' ' << va<<' ' << va<<' ' << va<<' ' << va<<' ' << endl;break;
		case 5:
			cout <<"\t\t"<< va<<' ' << va<<' ' << va<<' ' << va<<' ' << va<<' ' << endl;
            cout <<"\t\t"<< va<<' ' << num<<' ' << va<<' ' << num<<' ' << va<<' ' << endl;
            cout <<"\t\t"<< va<<' ' << va<<' ' << num<<' ' << va<<' ' << va<<' '<< endl;
            cout <<"\t\t"<< va<<' '<< num<<' ' << va<<' ' << num<<' ' << va<<' '<< endl;
            cout <<"\t\t"<< va<<' ' << va<<' ' << va<<' ' << va<<' ' << va<<' ' << endl;break;
		case 6:
			cout <<"\t\t"<< va<<' ' << va<<' ' << va<<' ' << va<<' ' << va<<' ' << endl;
            cout <<"\t\t"<< num<<' ' << va <<' '<< num<<' ' << va<<' ' << num<<' ' << endl;
            cout <<"\t\t"<< va<<' ' << va<<' ' << va<<' ' << va<<' ' << va<<' '<< endl;
            cout <<"\t\t"<< num<<' ' << va<<' ' << num<<' ' << va<<' ' << num<<' ' << endl;
            cout <<"\t\t"<< va <<' '<< va<<' ' << va<<' ' << va<<' ' << va<<' ' << endl;break;
	}
}
