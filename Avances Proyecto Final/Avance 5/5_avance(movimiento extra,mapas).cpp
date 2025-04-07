
#include<iostream>
#include<ctime>
#include <locale.h>
#include <stdlib.h> 
#include <time.h> 
#include<fstream>
#include "Cartas.h"

using namespace std;

const int f = 14;//t1=13,9 t2=12,13 t3=14,13.
const int c = 13;


char tablero[f][c];
int m_1_F[55]={10,11,12,12,12,12,11,10,9 ,8 ,7 ,7 ,7 ,6 ,5 ,5 ,5 ,4, 3, 2, 1, 0, 0, 0, 0, 1, 2, 2, 2, 1, 0, 0, 0, 0, 1, 2, 3, 4, 5, 5, 5, 6, 7, 7, 7, 8, 9,10,11,12,12,12,12,11,10};
int m_1_C[55]={3 ,3 ,3 ,2 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,2 ,2 ,2 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,2 ,3 ,3 ,3 ,4 ,5 ,5 ,5 ,6 ,7 ,8 ,8 ,8 ,8, 8, 8, 7, 6, 6, 6, 7, 8, 8, 8, 8, 8, 8, 7, 6, 5, 5, 5};
int m_2_F[55]={9,8,7,6,5,4,3,2,2,2,2,2,2,2,2,2,2, 2, 3, 4, 5, 6, 7, 8, 9,10,11,11,11,11,11,11,11,11,10,9,8,7,6,5,4,4,4,4,4,4,5,6,7,8,9,9,9,9,8  }; // 55
int m_2_C[55]={1,1,1,1,1,1,1,1,1,2,3,4,5,6,7,8,9,10,10,10,10,10,10,10,10,10,10, 9, 8, 7, 6, 5, 4, 3, 3,3,3,3,3,3,3,4,5,6,7,8,8,8,8,8,8,7,6,5,5    }; // 55
int m_3_F[55]={0,0,0,0,0,0,0,1,2,2,2,2,3,3,3,3,4,5,5,5,5,6,6,6,6,7,7,7,8, 9,9,9,10,10,10,10,11,11,11,11,11,12,13,13,13,13,13,13,13,13,13,13,13,13,13 }; // 38 +13
int m_3_C[55]={10,9,8,7,6,5,4,3,4,5,6,7,8,9,10,11,12,11,10,9,8,7,6,5,4,3,2,1,0,1,2,3,4,5,6,7,8,9,10,11,12,12,12,11,10,9,8,7,6,5,4,3,2,1,0 }; //51-3 = 48 +7
int carta;
bool ocupado_1=false,
	 ocupado_2=false,
	 ocupado_3=false,
	 ocupado_4=false,
	 ocupado_5=false,
	 ocupado_6=false,
	 ocupado_7=false,
	 ocupado_8=false,
	 ocupado_9=false,
	 ocupado_10=false;
string pregunta;
     string opciona;
     string opcionb;
     string opcionc;
     string opciond;
     string opcione;
ifstream Lec;
//Clases.
	class jugador{
		public:
			char id;
			int movi;
			char pos;
			
			jugador(char j,int mov){
				id=j;
				movi=mov;
			}	
	}; 
	
	class mapa{
		public:
			int recorrido;
			int corF[60];
			int corC[60];
			
			mapa(int f[55], int c[55],int lar){
				for(int x=0;x<lar;x++){
					corF[x]=f[x];
					corC[x]=c[x];
				}
				recorrido=lar;
			}
	};
//Objetos.
	jugador j1('1',0);
	jugador j2('2',0);
	jugador j3('3',0);
	jugador j4('4',0);
	
	mapa mapa1(m_1_F,m_1_C,55);
	mapa mapa2(m_2_F,m_2_C,55);
    mapa mapa3(m_3_F,m_3_C,55);
	
	
	void imprimirMapa(char tablero[f][c]);
    void mostrarDado(int a);
	void tirarDado(char j, int *mov_dado );
	bool verificarGanador(char tablero[f][c],int j1,int j2,int j3,int j4);
	void preguntas(char num, bool ocupado, char rpta);
	void verRegistros(ifstream &lec);
	void moverJugador(jugador *j, int mov_dado,mapa *map);
	
int main(){
	setlocale(LC_CTYPE, "Spanish");//Usar carácteres españoles.
//Funciones. 
   
   void rellenarMapa(char tablero[f][c],mapa *map);
   void refrescarMapa(jugador j, mapa *map);
   void comprobarCasilla(jugador j,mapa *map);

//Variables y objetos internos.
    bool gameOver=false;
    char dado; 
    int mov_dado,elec_mapa;
	mapa *mapa_e=&mapa3;
 
//Elegir Mapa.
	cout<<"Elija uno de los mapas disponibles(1,2,3)\n";
	cin>>elec_mapa;
	switch(elec_mapa){
		case 1:mapa_e=&mapa1;break;
		case 2:mapa_e=&mapa2;break;
		case 3:mapa_e=&mapa3;break;
		default:cout<<"Elección incorrecta, usando mapa1 por defecto\n";mapa_e=&mapa1;
	}
//Crear Mapa.
    rellenarMapa(tablero,mapa_e);
//Imprimir mapa.
    imprimirMapa(tablero);
//Bucle principal.
    while(gameOver==false){
		
	    tirarDado(j1.id, &mov_dado);
	    mostrarDado(mov_dado);
		refrescarMapa(j1,mapa_e);
		moverJugador(&j1,mov_dado,mapa_e);
		imprimirMapa(tablero);
		if (verificarGanador(tablero,j1.id,j2.id,j3.id,j4.id)==true){
			gameOver=true;
		}
		
		if(gameOver==false){
	    tirarDado(j2.id, &mov_dado);
	    mostrarDado(mov_dado);
		refrescarMapa(j2,mapa_e);
		moverJugador(&j2,mov_dado,mapa_e);
		imprimirMapa(tablero);
		if (verificarGanador(tablero,j1.id,j2.id,j3.id,j4.id)==true){
			gameOver=true;
		}
		}
		
		if(gameOver==false){
	    tirarDado(j3.id, &mov_dado);
	    mostrarDado(mov_dado);
		refrescarMapa(j3,mapa_e);
		moverJugador(&j3,mov_dado,mapa_e);
		imprimirMapa(tablero);
		if (verificarGanador(tablero,j1.id,j2.id,j3.id,j4.id)==true){
			gameOver=true;
		}
		}
		
		if(gameOver==false){
	    tirarDado(j4.id, &mov_dado);
	    mostrarDado(mov_dado);
		refrescarMapa(j4,mapa_e);
		moverJugador(&j4,mov_dado,mapa_e);
	    imprimirMapa(tablero);
	    if (verificarGanador(tablero,j1.id,j2.id,j3.id,j4.id)==true){
			gameOver=true;
		}
		}
		cout<<j1.movi<<endl<<j2.movi<<endl<<j3.movi<<endl<<j4.movi<<endl;	
    }
}

bool verificarGanador(char tablero[f][c],int j1,int j2,int j3,int j4){
	if(tablero[10][5]!='X'){
			if (tablero[10][5]==j1){cout<<"Ganó el jugador"<<j1<<endl;return true;}
			if(tablero[10][5]==j2){cout<<"Ganó el jugador"<<j2<<endl;return true;}
			if (tablero[10][5]==j3){cout<<"Ganó el jugador"<<j3<<endl;return true;}
			if (tablero[10][5]==j4){cout<<"Ganó el jugador"<<j4<<endl;return true;}
		}
	return false;
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
        	if (tablero[x][y]!='1'&& tablero[x][y]!='2'&& tablero[x][y]!='3'&& tablero[x][y]!='4')
            tablero[x][y] = ' ';
            
        }
    }
    for (int a=0;a<map->recorrido;a++){
    	if (tablero[map->corF[a]][map->corC[a]]!='1'&& tablero[map->corF[a]][map->corC[a]]!='2'&& tablero[map->corF[a]][map->corC[a]]!='3'&& tablero[map->corF[a]][map->corC[a]]!='4')
    	tablero[map->corF[a]][map->corC[a]]='X';
    }
    for (int a=5;a<map->recorrido;a+=6){
    	if (tablero[map->corF[a]][map->corC[a]]!='1'&& tablero[map->corF[a]][map->corC[a]]!='2'&& tablero[map->corF[a]][map->corC[a]]!='3'&& tablero[map->corF[a]][map->corC[a]]!='4')
    	tablero[map->corF[a]][map->corC[a]]='P';
    }
    for (int a=1;a<map->recorrido;a+=6){
    	if (tablero[map->corF[a]][map->corC[a]]!='1'&& tablero[map->corF[a]][map->corC[a]]!='2'&& tablero[map->corF[a]][map->corC[a]]!='3'&& tablero[map->corF[a]][map->corC[a]]!='4')
    	tablero[map->corF[a]][map->corC[a]]='B';
    }
    for (int a=3;a<map->recorrido;a+=6){
    	if (tablero[map->corF[a]][map->corC[a]]!='1'&& tablero[map->corF[a]][map->corC[a]]!='2'&& tablero[map->corF[a]][map->corC[a]]!='3'&& tablero[map->corF[a]][map->corC[a]]!='4')
    	tablero[map->corF[a]][map->corC[a]]='C';
    }
    
}

void  preguntas(char num, bool ocupado, char rpta){
     if(pregunta[0]==num && ocupado==false)
     {
      cout<<pregunta<<endl;
      cout<<opciona<<endl;
      cout<<opcionb<<endl;
      cout<<opcionc<<endl;
      cout<<opciond<<endl;
      cout<<opcione<<endl;
      ocupado=true;
      char respuesta;
      cout<<"Ingrese la respuesta: ";
      cin>>respuesta;
      if(respuesta == rpta){
        cout<<"La respuesta es correcta, ganaste una bonificación "<<endl;
      }
      else
      {
        cout<<"La respuesta es inccorrecta"<<endl;
      }
     
     }
}
void verRegistros(ifstream &lec){

     lec.open("Base de datos - Preguntas.txt",ios::in);
     lec >> pregunta;
     while(!lec.eof()){
     lec>>opciona;
     lec>>opcionb;
     lec>>opcionc;
     lec>>opciond;
     lec>>opcione;
    if(ocupado_1==false)
    {preguntas('1', ocupado_1, 'd'); break;}
    else if(ocupado_2==false)
    {preguntas('2', ocupado_2, 'a');break;}
    else if(ocupado_3==false)
    {preguntas('3', ocupado_3, 'a');break;}
    else if(ocupado_4==false)
    {preguntas('4', ocupado_4, 'b');break;}
    else if(ocupado_5==false)
    {preguntas('5', ocupado_5, 'c');break;}
    else if(ocupado_6==false)
    {preguntas('6', ocupado_6, 'c');break;}
    else if(ocupado_7==false)
    {preguntas('7', ocupado_7, 'b');break;}
    else if(ocupado_8==false)
    {preguntas('8', ocupado_8, 'c');break;}
    else if(ocupado_9==false)
    {preguntas('9', ocupado_9, 'd');break;}
	 lec>>pregunta; 	
	 }
	 lec.close();
}

void refrescarMapa(jugador j, mapa *map){
	if(tablero[map->corF[j.movi]][map->corC[j.movi]]==j.id){
		tablero[map->corF[j.movi]][map->corC[j.movi]]='X';
	}
	rellenarMapa(tablero,map);
}
void comprobarCasilla(jugador *j,mapa *map){
	char temp =tablero[map->corF[j->movi]][map->corC[j->movi]];
	if(temp=='P'){
		cout<<"El jugador: "<<j->id<<" debe responder UNA pregunta "<<endl;
		
		verRegistros(Lec);
	}
	else if(temp=='C'){
		srand((unsigned int)time(NULL));
	    carta=13;//rand()%18;
	    cout<<cartas[carta]<<endl;
	    switch(carta){
	    	case 0:moverJugador(j,3,map);break;
	    	case 1:moverJugador(j,4,map);break;
	    	case 2:moverJugador(j,5,map);break;
	    	case 9:moverJugador(j,3,map);break;
	    	case 10:moverJugador(j,(-3),map);break;
	    	case 11:moverJugador(j,(-3),map);break;
	    	case 12:moverJugador(j,(-4),map);break;
	    	case 13:moverJugador(j,(-5),map);break;
	    }
	}
	tablero[map->corF[j->movi]][map->corC[j->movi]] = j->id;
	
}
void moverJugador(jugador *j, int mov_dado, mapa *map){
	j->movi += mov_dado;
	//Verifica limites
	if(j->movi>54){
	   j->movi=54;
    }
    if(j->movi<0){
    	j->movi=0;
    }
    comprobarCasilla(j,map);
}

void mostrarDado(int a){
    char va = '|';
    char num = 'O' ;
	
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
