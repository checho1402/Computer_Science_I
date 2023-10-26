#include <iostream>
#include <stdlib.h>    
#include "matriz3D.h"
using namespace std;


int main() {

  matriz_3D Matriz_1(2,2,2);//El tamaño de la matriz definido antes por el usuario
  //Matriz_1.imprimir();
  Matriz_1.llenar_datos();
  Matriz_1.imprimir();
          cout<<"\n --------------------- \n";
  //Matriz_1.punto_especifico();
  //Matriz_1.imprimir();
  matriz_3D Matriz_2(2,2,2);
  Matriz_2.llenar_datos();
  Matriz_2.imprimir();
          cout<<"\n --------------------- \n";

  Matriz_2.menor_mayor();
  Matriz_2.indices(2);
  Matriz_2.repeticiones(5);
  cout<<"\n --------------------- \n";
  Matriz_1.suma(Matriz_1, Matriz_2,2,2,2);
  Matriz_1.resta(Matriz_1, Matriz_2,2,2,2);
  matriz_3D Matriz_3 = Matriz_2;//Permite copiar un objeto matriz hacia otro.
  Matriz_3.imprimir();
}

