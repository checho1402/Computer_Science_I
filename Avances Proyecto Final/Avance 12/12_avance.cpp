//12 avance.cpp
#include<iostream>
#include<ctime>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include<fstream>
#include "Cartas.h"
#include "minijuegos.h"
#include "funciones.cpp"
#include <climits>

using namespace std;

//Dayevska Caceres
//Roberto Cayro
//Sergio Ramos
//Gabriel Valdivia

//variables generales
int m_1_F[55]={10,11,12,12,12,12,11,10,9 ,8 ,7 ,7 ,7 ,6 ,5 ,5 ,5 ,4, 3, 2, 1, 0, 0, 0, 0, 1, 2, 2, 2, 1, 0, 0, 0, 0, 1, 2, 3, 4, 5, 5, 5, 6, 7, 7, 7, 8, 9,10,11,12,12,12,12,11,10};
int m_1_C[55]={3 ,3 ,3 ,2 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,2 ,2 ,2 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,2 ,3 ,3 ,3 ,4 ,5 ,5 ,5 ,6 ,7 ,8 ,8 ,8 ,8, 8, 8, 7, 6, 6, 6, 7, 8, 8, 8, 8, 8, 8, 7, 6, 5, 5, 5};
int m_2_F[55]={9,8,7,6,5,4,3,2,2,2,2,2,2,2,2,2,2, 2, 3, 4, 5, 6, 7, 8, 9,10,11,11,11,11,11,11,11,11,10,9,8,7,6,5,4,4,4,4,4,4,5,6,7,8,9,9,9,9,8  };
int m_2_C[55]={1,1,1,1,1,1,1,1,1,2,3,4,5,6,7,8,9,10,10,10,10,10,10,10,10,10,10, 9, 8, 7, 6, 5, 4, 3, 3,3,3,3,3,3,3,4,5,6,7,8,8,8,8,8,8,7,6,5,5    };
int m_3_F[55]={0,0,0,0,0,0,0,1,2,2,2,2,3,3,3,3,4,5,5,5,5,6,6,6,6,7,7,7,8, 9,9,9,10,10,10,10,11,11,11,11,11,12,13,13,13,13,13,13,13,13,13,13,13,13,13 };
int m_3_C[55]={10,9,8,7,6,5,4,3,4,5,6,7,8,9,10,11,12,11,10,9,8,7,6,5,4,3,2,1,0,1,2,3,4,5,6,7,8,9,10,11,12,12,12,11,10,9,8,7,6,5,4,3,2,1,0 }, carta;
bool ocupado_1=false, ocupado_2=false, ocupado_3=false, ocupado_4=false, ocupado_5=false, ocupado_6=false, ocupado_7=false, ocupado_8=false, ocupado_9=false, ocupado_10=false;
string pregunta, opciona, opcionb, opcionc, opciond, opcione;
bool rpt=true;

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
		char Tablero[14][13];
	mapa(int f[55], int c[55],int recorrido){
		for(int x=0;x<recorrido;x++){
			corF[x]=f[x];
			corC[x]=c[x];
		}
		this->recorrido=recorrido;
	}
    mapa(mapa *map){//contructor copia
    	this->recorrido=map->recorrido;
		for(int x=0;x<recorrido;x++){
			corF[x]=map->corF[x];
			corC[x]=map->corC[x];
		}
	    for(int x=0; x<14; x++){ //lena la matriz de espacios, matriz vacia
            for(int y=0; y<13 ;y++){ Tablero[x][y] = ' '; }
        }
        for (int a=0 ; a< recorrido ; a++ ) Tablero[corF[a]][corC[a]] = 'X'; //casilla vacia
        for (int a=5 ; a< recorrido ; a+=6) Tablero[corF[a]][corC[a]] = 'P';//casilla con carta de pregunta
        for (int a=1 ; a< recorrido ; a+=6) Tablero[corF[a]][corC[a]] = 'B'; //casilla bomba
        for (int a=3 ; a< recorrido ; a+=6) Tablero[corF[a]][corC[a]] = 'C'; //casilla con carta de bonificación o castigo
        for (int a=2 ; a< recorrido ; a+=7) Tablero[corF[a]][corC[a]] = 'M';//casilla que te envia a un juego aleatorio
    }
    void imprimirMapa(){
        for(int x=0; x<14; x++){
    	    cout<<"\t";
            for(int y=0; y<13; y++){
                cout << Tablero[x][y] << " ";
            }
            cout << endl;
        }
    }
    void refrescarMapa(jugador j){ //Permite que no se borren los jugadore y las casillas "C" "M" "P" "B" con sus funcionalidades
	if ( j.bomba==false){
        if(Tablero[corF[j.movi]][corC[j.movi]]==j.id) { Tablero[corF[j.movi]][corC[j.movi]]='X'; } //reset, borra la pos anterior deljugador

        for (int a=0 ; a<recorrido ; a++){//verifica que no haya un jugador y recien pone la casilla
        	if ( Tablero[corF[a]][corC[a]]!='1'&& Tablero[corF[a]][corC[a]]!='2'&& Tablero[corF[a]][corC[a]]!='3'&& Tablero[corF[a]][corC[a]]!='4')
    	    Tablero[corF[a]][corC[a]] = 'X'; //casilla vacia
        }
        for (int a=5 ; a<recorrido ; a+=6){
        	if ( Tablero[corF[a]][corC[a]]!='1'&& Tablero[corF[a]][corC[a]]!='2'&& Tablero[corF[a]][corC[a]]!='3'&& Tablero[corF[a]][corC[a]]!='4')
    	    Tablero[corF[a]][corC[a]] = 'P';//casilla con carta de pregunta
        }
        for (int a=1 ; a<recorrido ; a+=6){
        	if ( Tablero[corF[a]][corC[a]]!='1'&& Tablero[corF[a]][corC[a]]!='2'&& Tablero[corF[a]][corC[a]]!='3'&& Tablero[corF[a]][corC[a]]!='4')
    	    Tablero[corF[a]][corC[a]] = 'B'; //casilla bomba
        }
        for (int a=3 ; a<recorrido ; a+=6){
        	if ( Tablero[corF[a]][corC[a]]!='1'&& Tablero[corF[a]][corC[a]]!='2'&& Tablero[corF[a]][corC[a]]!='3'&& Tablero[corF[a]][corC[a]]!='4')
    	    Tablero[corF[a]][corC[a]] = 'C'; //casilla con carta de bonificación o castigo
        }
        for (int a=2 ; a<recorrido ; a+=7){ //casilla que te envia a un juego aleatorio
        	if ( Tablero[corF[a]][corC[a]]!='1'&& Tablero[corF[a]][corC[a]]!='2'&& Tablero[corF[a]][corC[a]]!='3'&& Tablero[corF[a]][corC[a]]!='4')
    	    Tablero[corF[a]][corC[a]] = 'M';//casilla que te envia a un juego aleatorio
            }
        }
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

    void recompensa(int  puntaje, jugador *j, mapa *map);
    void comprobarCasilla(jugador j,mapa *map,char temp);
    void mostrarDado(int a);
	void tirarDado(int *mov_dado ,jugador j);
    void moverJugador(jugador *j, int mov_dado, mapa *map);
	void recogerBonificacion(jugador *j,mapa *map);
    void recogerCastigo(jugador *j,mapa *map);
    void otherPlayer_RA(int llave, jugador *j,int movR,mapa *map );
    void imprimirBomba();
    void imprimirEscudo();
    void imprimirCartaB();
    void imprimirCartaC();
    void imprimirCarta();

	bool verRegistros(ifstream &lec);
    bool verificarGanador(mapa *map,int j1,int j2,int j3,int j4);
    bool preguntas(bool &ocupado, char rpta);

int main(){
    //mn_1.juego_laberinto();

	cout<<
  " #     #                                                                            \n"<<
  " ##   ##    ##     ####   #   ####           #####    ####     ##    #####   #####  \n"<<
  " # # # #   #  #   #    #  #  #    #          #    #  #    #   #  #   #    #  #    # \n"<<
  " #  #  #  #    #  #       #  #               #####   #    #  #    #  #    #  #    # \n"<<
  " #     #  ######  #  ###  #  #               #    #  #    #  ######  #####   #    # \n"<<
  " #     #  #    #  #    #  #  #    #          #    #  #    #  #    #  #   #   #    # \n"<<
  " #     #  #    #   ####   #   ####           #####    ####   #    #  #    #  #####  \n";

	setlocale(LC_CTYPE, "Spanish");//Usar carácteres españoles.

//Variables y objetos internos.
    bool gameOver=false;
    char dado,elec_mapa;
    int mov_dado;
	mapa mapa_e(mapa1);
//Elegir y crear el Mapa general
	cout<<"Elija uno de los mapas disponibles(1,2,3)\n"; cin>>elec_mapa;
	if(elec_mapa=='1'||elec_mapa=='2'||elec_mapa=='3'){
	switch(elec_mapa){
		case '1':mapa_e=&mapa1;break;
		case '2':mapa_e=&mapa2;break;
		case '3':mapa_e=&mapa3;break;
	}
	}else if(elec_mapa!='1'&&elec_mapa!='2'&&elec_mapa!='3'){
		mapa_e=&mapa1;
		cout<<"Elección incorrecta, usando mapa1 por defecto\n";
	}
	mapa_e.imprimirMapa();
//Bucle principal.
    while(gameOver==false){

	    //jugador 1
	    tirarDado(&mov_dado, j1);
		moverJugador(&j1,mov_dado,&mapa_e);
		if (verificarGanador(&mapa_e,j1.id,j2.id,j3.id,j4.id)==true) { gameOver=true; }
        //jugador 2
		if(gameOver==false){
	        tirarDado(&mov_dado,j2);
		    moverJugador(&j2,mov_dado,&mapa_e);
		    if (verificarGanador(&mapa_e,j1.id,j2.id,j3.id,j4.id)==true) { gameOver=true; }
		}
        //jugador 3
		if(gameOver==false){
	        tirarDado( &mov_dado, j3);
		    moverJugador(&j3,mov_dado,&mapa_e);
		    if (verificarGanador(&mapa_e,j1.id,j2.id,j3.id,j4.id)==true) { gameOver=true; }
		}
        //jugador 4
		if(gameOver==false){
	        tirarDado(&mov_dado, j4);
		    moverJugador(&j4,mov_dado,&mapa_e);
	        if (verificarGanador(&mapa_e,j1.id,j2.id,j3.id,j4.id)==true) { gameOver=true; }
		}
	}


}
//////////////////////////////////////////////////////////// FUNCIONES //////////////////////////////////////////////////
void comprobarCasilla(jugador *j,mapa *map, char temp){
    int g;
	if(temp=='P'){ //te toca una pregunta, puedes tener una bonificacion o un castigo
		cout<<"El jugador: "<<j->id<<" debe responder UNA pregunta "<<endl;
		verRegistros(Lec);
		if(rpt == 0){ recogerBonificacion(j,map);} //"ver registros" mostrata la pregunta si respondemos correctamente nos da un abonificacion
		else if(rpt==1){ recogerCastigo(j,map);} //si respondemos incorrectamente un castigo
		map->imprimirMapa();
	}

	else if(temp=='C'){ //te toca una carta aleatoria
		srand((unsigned int)time(NULL));
	    carta=rand()%17;
	    cout<<"CARTA ALEATORIA para jugador "<<j->id<<"\n";
	    imprimirCarta();
	    cout<<"-"<<cartas[carta]<<endl; // se elige aleatoriamente una carta de "Cartas.h"
	    switch(carta){
	    	case 0:moverJugador(j,3,map);break; //avanaza 3 casillas
	    	case 1:moverJugador(j,4,map);break; //avanaza 4 casillas
	    	case 2:moverJugador(j,5,map);break; //avanaza 5 casillas
	    	case 9:moverJugador(j,3,map);break; //avanaza 3 casillas
	    	case 10:moverJugador(j,(-3),map);break; //retrocede 3 casillas
	    	case 11:moverJugador(j,(-3),map);break; //retrocede 3 casillas
	    	case 12:moverJugador(j,(-4),map);break; //retrocede 4 casillas
	    	case 13:moverJugador(j,(-5),map);break; //retrocede 5 casillas
	    	case 7: j->escudo=true;imprimirEscudo();break; //Ganar un escudo.
			case 14: j->bomba=true;imprimirBomba();break;//Carta bomba.
			case 15: j->bomba=true;imprimirBomba();break;//Carta bomba.
	    	case 3:otherPlayer_RA(0, j,0,map);map->imprimirMapa();break;//Tirar una bomba a alguien.
			case 4:otherPlayer_RA(1, j,-3,map);break;//Hacer que alguien retroceda 3 casillas.
			case 5:otherPlayer_RA(1, j,-4,map);break;//Hacer que alguien retroceda 4 casillas.
			case 6:otherPlayer_RA(1, j,-5,map);break;//Hacer que alguien retroceda 5 casillas.
			case 8: otherPlayer_RA(2, j,0,map);break;//hacer que otro jugador reciba una carta castigo
			case 16:otherPlayer_RA(3, j,0,map);break; //hacer que otro jugador reciba una carta bonificación
			case 17:otherPlayer_RA(3, j,0,map);break; //hacer que otro jugador reciba una carta bonificación
	    }
	    
	}
	else if(temp=='B'){ //te toco una bomba
	    cout << "El jugador "<<j->id<<" cayó en una casilla bomba "<<endl;
	    imprimirBomba();
		j->bomba=true;
		map->imprimirMapa();
	}
	else if(temp == 'M'){ //te toco un juego aleatorio, si ganas tendras un abonificación si no un castigo
		cout<<"El jugador "<<j->id<<"tiene que jugar un juego aleatorio\n";
	    srand((unsigned int)time(NULL));
        int puntaje=0, s_mn; 
		s_mn=1+rand()%5;

    	if(s_mn == 1){ puntaje = mn_1.juego_laberinto(); recompensa(puntaje,j,map);}        //te toco el juego de laberinto
    	if(s_mn == 2){ puntaje = mn_2.mini_gato(); recompensa(puntaje,j,map);}             //te toco el juego del gato
    	if(s_mn == 3){ puntaje = minijuego_3_raya(); recompensa(puntaje,j,map);} //te toco jugar de 3 en raya
    	if(s_mn == 4){ puntaje = busca_minas(); recompensa(puntaje,j,map);}      //te toco jugar busca minas
    	if(s_mn == 5){ puntaje = tron_M_juego(); recompensa(puntaje,j,map);}	      //te toco jugar tron
    	if(s_mn == 6){ puntaje = minijuego_hanoi(); recompensa(puntaje,j,map);}  //te toco jugar hanoi

	}
}
void otherPlayer_RA(int llave, jugador *j,int movR,mapa *map ){
	if (llave == 0 ){//Tirar una bomba a alguien.
		int jBombardeado;
	    cout<<"Jugador "<<j->id<<", escribe el número del jugador al que quieras tirarle una bomba: "; cin>>jBombardeado; 
	    
	    while (cin.fail()){
        cin.clear(); 
        cin.ignore(INT_MAX, '\n'); // Ignorar valor incorreecto
        cout << "Solo puedes ingresar números\n";
        cout<<"Jugador "<<j->id<<", escribe el número del jugador al que quieras tirarle una bomba: ";
        cin>>jBombardeado;cout<<endl;
    	}
    	
	    switch(jBombardeado){
			case 1:cout<<"El jugador "<<j1.id<<" recibe una bomba"<<endl;j1.bomba=true;break;
			case 2:cout<<"El jugador "<<j2.id<<" recibe una bomba"<<endl;j2.bomba=true;break;
			case 3:cout<<"El jugador "<<j3.id<<" recibe una bomba"<<endl;j3.bomba=true;break;
			case 4:cout<<"El jugador "<<j4.id<<" recibe una bomba"<<endl;j4.bomba=true;break;
		}
		imprimirBomba();
	}
	if (llave ==1){//Hacer que alguien retroceda x casillas.
		int mostrarmov, jRetrocede;
		if (movR == -3) mostrarmov=3;
		if (movR == -4) mostrarmov=4;
		if (movR == -5) mostrarmov=5;
		cout<<"Jugador "<<j->id<<", escribe el número del jugador que quieres que retroceda "<<mostrarmov<<" casillas: "; cin>>jRetrocede;
		
		while (cin.fail()){
        cin.clear(); 
        cin.ignore(INT_MAX, '\n'); // Ignorar valor incorreecto
        cout << "Solo puedes ingresar números\n";
        cout<<"Jugador "<<j->id<<", escribe el número del jugador que quieres que retroceda "<<mostrarmov<<" casillas: ";
        cin>>jRetrocede;cout<<endl;
    	}
    	
		switch(jRetrocede){
			case 1:cout<<"El jugador "<<j1.id<<" retrocede "<< mostrarmov <<" casillas"<<endl;moverJugador(&j1,(movR),map);break;
			case 2:cout<<"El jugador "<<j2.id<<" retrocede "<< mostrarmov <<" casillas"<<endl;moverJugador(&j2,(movR),map);break;
			case 3:cout<<"El jugador "<<j3.id<<" retrocede "<< mostrarmov <<" casillas"<<endl;moverJugador(&j3,(movR),map);break;
			case 4:cout<<"El jugador "<<j4.id<<" retrocede "<< mostrarmov <<" casillas"<<endl;moverJugador(&j4,(movR),map);break;
		}
	}
	if (llave == 2){ //hacer que otro jugador reciba una carta castigo
		int otroJugador;
		cout<<"Jugador "<<j->id<<" escribe el número del jugador que quieres que recoja una carta de castigo: "; cin>>otroJugador; 
		
		while (cin.fail()){
        cin.clear(); 
        cin.ignore(INT_MAX, '\n'); // Ignorar valor incorreecto
        cout << "Solo puedes ingresar números\n";
        cout<<"Jugador "<<j->id<<" escribe el número del jugador que quieres que recoja una carta de castigo: ";
        cin>>otroJugador; cout<<endl;
    	}
    	
		switch(otroJugador){
			case 1:cout<<"EL jugador "<<j1.id<<" tiene que recoger una carta de castigo\n"; recogerCastigo(&j1,map);break;
			case 2:cout<<"EL jugador "<<j2.id<<" tiene que recoger una carta de castigo\n"; recogerCastigo(&j2,map);break;
			case 3:cout<<"EL jugador "<<j3.id<<" tiene que recoger una carta de castigo\n"; recogerCastigo(&j3,map);break;
			case 4:cout<<"EL jugador "<<j4.id<<" tiene que recoger una carta de castigo\n"; recogerCastigo(&j4,map);break;
		}
	}
	if (llave == 3){ //hacer que otro jugador reciba una carta bonificación
	    int otroJugador;
		cout<<"Jugador "<<j->id<<" escribe el número del jugador que quieres que recoja una carta de bonificación: "; cin>>otroJugador;
		
		while (cin.fail()){
        cin.clear(); 
        cin.ignore(INT_MAX, '\n'); // Ignorar valor incorreecto
        cout << "Solo puedes ingresar números\n";
        cout<<"Jugador "<<j->id<<" escribe el número del jugador que quieres que recoja una carta de bonificación: ";
        cin>>otroJugador; cout<<endl;
    	}
    	
		switch(otroJugador){
			case 1:cout<<"EL jugador "<<j1.id<<" tiene que recoger una carta de bonificación\n"; recogerBonificacion(&j1,map);break;
			case 2:cout<<"EL jugador "<<j2.id<<" tiene que recoger una carta de bonificación\n"; recogerBonificacion(&j2,map);break;
			case 3:cout<<"EL jugador "<<j3.id<<" tiene que recoger una carta de bonificación\n"; recogerBonificacion(&j3,map);break;
			case 4:cout<<"EL jugador "<<j4.id<<" tiene que recoger una carta de bonificación\n"; recogerBonificacion(&j4,map);break;
		}
	}
}
void recompensa(int  puntaje, jugador *j, mapa *map){ //Efectos del jugador despues de estar en una casilla "M"
    if (puntaje == 3){ recogerBonificacion(j,map); }
    if (puntaje == 1){ recogerCastigo(j,map); }
    if (puntaje == 2){ cout << "Ni bonificación ni castigo"; }
}
void recogerBonificacion(jugador *j,mapa *map){
	cout<<"CARTA BONIFICACIÓN para el jugador "<<j->id<<"\n";
	imprimirCartaB();
	srand((unsigned int)time(NULL));
	int c_B = rand()%9; // se lige una bonificacion aleatoriamente
	cout<<"-"<<bonificaciones[c_B]<<endl;
	switch(c_B){
		case 0: moverJugador(j,3,map);break; //Avanzar 3.
		case 1: moverJugador(j,4,map);break; //Avanzar 4.
		case 2: moverJugador(j,5,map);break; //Avanzar 5.
		case 7: j->escudo=true;imprimirEscudo();break; //La bomba no te afectara
		case 3:otherPlayer_RA(0, j,0,map);break;//Tirar una bomba a alguien.
		case 4:otherPlayer_RA(1, j,-3,map);break;//Hacer que alguien retroceda 3 casillas.
		case 5:otherPlayer_RA(1, j,-4,map);break;//Hacer que alguien retroceda 4 casillas.
		case 6:otherPlayer_RA(1, j,-5,map);break;//Hacer que alguien retroceda 5 casillas.
		case 8: otherPlayer_RA(2, j,0,map);break;//hacer que otro jugador reciba una carta castigo
	}
}
void recogerCastigo(jugador *j,mapa *map){
	cout<<"CARTA CASTIGO para el jugador "<<j->id<<"\n";
	imprimirCartaC();
	srand((unsigned int)time(NULL));
	int c_C = rand()%5; // se escoje un castigo aleatorio
	cout<<"-"<<castigos[c_C]<<endl;
	switch(c_C){
		case 0:moverJugador(j,(-3),map);break; //Retrocede 3
		case 1:moverJugador(j,(-4),map);break; //Retrocede 4
		case 2:moverJugador(j,(-5),map);break; //Retrocede 5
		case 3:j->bomba=true;imprimirBomba();break; //Pierdes un turno
		case 4:otherPlayer_RA(3, j,0,map);break; //hacer que otro jugador reciba una carta bonificación
	}
}
void moverJugador(jugador *j, int mov_dado, mapa *map){
	map->refrescarMapa(*j);

	if ( (j->bomba==false && j->escudo==false)||(j->bomba==false && j->escudo == true)){//avanzas segun el dado
		j->movi += mov_dado;
	    //Verifica limites
        if(j->movi>54) { j->movi=54; }
        if(j->movi<0) { j->movi=0; }
        char temp =map->Tablero[map->corF[j->movi]][map->corC[j->movi]];
        map->Tablero[map->corF[j->movi]][map->corC[j->movi]] = j->id;//se coloca al jugador en su nueva pos
        map->imprimirMapa();
        comprobarCasilla(j,map,temp); //ver si estas en una casilla "C"carta, "M"juego, "P"pregunta, "B"bomba.
	}
	else if(j->bomba==true && j->escudo ==true){ //se activa el escudo y avanzas apesar de tener una bomba
		cout<<"Jugador "<<j->id<<" su escudo evitó el efecto de la bomba\n";
		j->escudo=false;
		j->movi += mov_dado;
	    //Verifica limites
        if(j->movi>54) { j->movi=54; }
        if(j->movi<0) { j->movi=0; }
        char temp =map->Tablero[map->corF[j->movi]][map->corC[j->movi]];
        map->Tablero[map->corF[j->movi]][map->corC[j->movi]] = j->id;//se coloca al jugador en su nueva pos
        map->imprimirMapa();
        comprobarCasilla(j,map,temp); //ver si estas en una casilla "C"carta, "M"juego, "P"pregunta, "B"bomba.
	}
	else if (j->bomba==true && j->escudo==false) {// se activa la bomca y pierdes el turno por lo que no avanzas
		cout << "El jugador "<< j->id << " está inmovilizado por la bomba, ¡no puede moverse!" << endl;
		j->bomba = false ;
	}
}
void tirarDado(int *mov_dado ,jugador j){
	if ( j.bomba==false){
		char dado;
		bool turnoValido;
		turnoValido=false;
		while(turnoValido==false){
		cout<<"Jugador "<<j.id<<" ingrese 'd' para tirar el dado: "; cin>>dado;
		if (dado=='d'){
			turnoValido=true;
			srand((unsigned int)time(NULL));
	    	*mov_dado=1+ rand()%6; //un numero aleatorio del [1-6] ya que es un dado
        	cout << *mov_dado << endl; //se imprime en numero
		}
		}
	    mostrarDado(*mov_dado); //se muestra el dado segun el número aleatorio
    }
}
bool verificarGanador(mapa *map,int j1,int j2,int j3,int j4){
	if(map->Tablero[10][5]!='X'){ //si la ultima casilla de los mapas es diferente a "X" existe un ganador
		if (map->Tablero[10][5]==j1){cout<<"Ganó el jugador"<<j1<<endl;return true;}
		if (map->Tablero[10][5]==j2){cout<<"Ganó el jugador"<<j2<<endl;return true;}
		if (map->Tablero[10][5]==j3){cout<<"Ganó el jugador"<<j3<<endl;return true;}
		if (map->Tablero[10][5]==j4){cout<<"Ganó el jugador"<<j4<<endl;return true;}
	} return false;
}
bool  preguntas(bool &ocupado, char rpta){ //muestra en pantalla su pregunta y sus alternativas dependiendo de eso se activara la bonificacion o castigo
    cout<<pregunta<<endl;
    cout<<opciona<<endl;
    cout<<opcionb<<endl;
    cout<<opcionc<<endl;
    cout<<opciond<<endl;
    cout<<opcione<<endl;
    ocupado=true; // para que no se repita la pregunta
    char respuesta;
    cout<<"Ingrese la respuesta(letra): ";cin>>respuesta;
    if(respuesta == rpta){ //respuesta correcta, se retorna true para activar la bonificación
		cout<<"La respuesta es correcta, ganaste una bonificación "<<endl;
		rpt= 0;
	}
    else {  //respuesta incorrecta, se retorna false
		cout<<"La respuesta es incorrecta"<<endl;
		rpt= 1;
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
    if(pregunta[0]=='1' && ocupado_1==false)
     {preguntas(ocupado_1, 'd'); break;}
    else if(pregunta[0]=='2' && ocupado_2==false)
    {preguntas(ocupado_2, 'a');break;}
    else if(pregunta[0]=='3' && ocupado_3==false)
    {preguntas(ocupado_3, 'a');break;}
    else if(pregunta[0]=='4' && ocupado_4==false)
    {preguntas(ocupado_4, 'b');break;}
    else if(pregunta[0]=='5' && ocupado_5==false)
    {preguntas(ocupado_5, 'c');break;}
    else if(pregunta[0]=='6' && ocupado_6==false)
    {preguntas(ocupado_6, 'c');break;}
    else if(pregunta[0]=='7' && ocupado_7==false)
    {preguntas(ocupado_7, 'b');break;}
    else if(pregunta[0]=='8' && ocupado_8==false)
    {preguntas(ocupado_8, 'c');break;}
    else if(pregunta[0]=='9' && ocupado_9==false)
    {preguntas(ocupado_9, 'd');break;}
    else if(pregunta[0]=='1' && pregunta[1]=='0' && ocupado_10==false)
    {preguntas(ocupado_10, 'd');break;}
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
	cout<<endl;
}
void imprimirBomba(){
	
	cout<<"\t      ,--.!,  \n";
	cout<<"\t   __/   -*-  \n";
	cout<<"\t ,####.  '|`  \n";
	cout<<"\t ######       \n";
	cout<<"\t `####´       \n";
}
void imprimirEscudo(){
	cout<<"\t       _._      \n";     
	cout<<"\t   _.-` : `-._  \n"; 
	cout<<"\t |`     :    `| \n";
	cout<<"\t |      :     | \n";
	cout<<"\t |::::::::::::| \n"; 
	cout<<"\t |      :     | \n";
	cout<<"\t        :    /  \n";
	cout<<"\t   `-.  : .-'   \n";
}
void imprimirCartaB(){
	cout<<"\t|- ~ -|\n";
	cout<<"\t|     |\n";
	cout<<"\t| :)  |\n"; 
	cout<<"\t|     |\n"; 
	cout<<"\t|__~__|\n";
}
void imprimirCartaC(){
	cout<<"\t|- ~ -|\n";
	cout<<"\t|     |\n";
	cout<<"\t| :(  |\n"; 
	cout<<"\t|     |\n"; 
	cout<<"\t|__~__|\n";	
}
void imprimirCarta(){
	cout<<"\t|- ~ -|\n";
	cout<<"\t|     |\n";
	cout<<"\t|  ?  |\n"; 
	cout<<"\t|     |\n"; 
	cout<<"\t|__~__|\n";
}
