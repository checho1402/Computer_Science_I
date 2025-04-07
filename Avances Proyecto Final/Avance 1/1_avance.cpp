#include<iostream>
#include<ctime>


using namespace std;

const int f = 13;
const int c = 9;

void dado(int a){
    char va = '▲';
    char num = '°' ;

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


void imprimir(char tablero[f][c]){
for(int x=0; x<13; x=x+1){
    for(int y=0; y<9 ;y = y+1){
        cout << tablero[x][y] << " ";
}
cout << endl;
}

}

void rellenar(char tablero[f][c]){
for(int x=0; x<13; x=x+1){
for(int y=0; y<9 ;y = y+1){
        tablero[x][y] = '▲';
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



int main(){
char tablero[f][c];
int movimiento ;


//srand()

rellenar(tablero);
imprimir(tablero);



srand((unsigned int)time(NULL));

movimiento= rand()%7;
    cout << movimiento << endl;

    dado(movimiento);


}

