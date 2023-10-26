#include <iostream>
#include "matriz3D.h"
using namespace std;

    void matriz_3D::imprimir(){
     for(int i=0;i<num_1;i++){
        for(int j=0;j<num_2;j++){
          for(int z=0;z<num_3;z++){
          cout<<"El número ["<<i<<"],["<<j<<"],["<<z<<"]: "<<myBuffer[i][j][z]<<"\n";
          }
        }
      }
    }
    void matriz_3D::llenar_datos(){
      for(int i=0;i<num_1;i++){
        for(int j=0;j<num_2;j++){
          for(int z=0;z<num_3;z++){
            *(*(*(myBuffer+i)+j)+z) = rand() % 9 + 1;//valores creados de manera aleatoria
          }
        }
      }

      cout<<endl;
    }
    void matriz_3D::punto_especifico(){
      //Permita ingresar un valor específico en una posición específica de la matriz ( i,j,k -> M[ i ][ j ][ k ] = x ).
      int i,j,k,x;
      cout<<" Ingreso de un valor especifico dentro de la matriz\n";
      cout<<" Ingresa una posición [i]: ";
      cin>>i;
      cout<<" \nIngresa una posición [j]: ";
      cin>>j;
      cout<<" \nIngresa una posición [z]: ";
      cin>>k;
      cout<<"\nIngrese el valor de ["<<i<<"],["<<j<<"],["<<k<<"]: \n";
      cin>>x; 
      myBuffer[i][j][k] = x;
        cout<<"\n --------------------- \n";
    }
    void matriz_3D::suma(matriz_3D A,matriz_3D B,int x,int y,int w){
      //Suma de dos matrices, C ijk = A ijk + B ijk.
      matriz_3D suma(A.num_1,A.num_2,A.num_3);
        for(int i=0;i<x;i++){
          for(int j=0;j<y;j++){
            for(int z=0;z<w;z++){
              suma.myBuffer[i][j][z] = A.myBuffer[i][j][z] + B.myBuffer[i][j][z];
            }
          }
        }
      suma.imprimir();
        cout<<endl;
    }
    void matriz_3D::resta(matriz_3D A,matriz_3D B,int x,int y,int w){
      //Resta  de dos matrices, C ijk = A ijk - B ijk.
      matriz_3D suma(A.num_1,A.num_2,A.num_3);
        for(int i=0;i<x;i++){
          for(int j=0;j<y;j++){
            for(int z=0;z<w;z++){
              suma.myBuffer[i][j][z] = A.myBuffer[i][j][z] - B.myBuffer[i][j][z];
            }
          }
        }
      suma.imprimir();
        cout<<endl;
    }
    void matriz_3D::menor_mayor(){
      //Obtener el menor y el mayor elemento de la matriz.
      int mayor = myBuffer[0][0][0];
      int menor = myBuffer[0][0][0];
      for(int i=0;i<num_1;i++){
          for(int j=0;j<num_2;j++){
            for(int z=0;z<num_3;z++){
              if (*(*(*(myBuffer+i)+j)+z) > mayor)
              {
                mayor=*(*(*(myBuffer+i)+j)+z);
              }
              if (*(*(*(myBuffer+i)+j)+z) < menor)
              {
                menor=*(*(*(myBuffer+i)+j)+z);
              }
            }
          }
        }
      cout<<"\n El mayor elemento de la matriz es: "<<mayor<<"\n";
      cout<<"\n El menor elemento de la matriz es: "<<menor<<"\n";
        cout<<endl;
    }
  void matriz_3D::indices(int valor){
      //Obtener los indices (i,j,k) de un elemento específico en la matriz.
      for(int i=0;i<num_1;i++){
          for(int j=0;j<num_2;j++){
            for(int z=0;z<num_3;z++){
              if (*(*(*(myBuffer+i)+j)+z) == valor)
              {
                cout<<"\nEl valor: "<<valor<<" se encuentra en las posiciones ["<<i<<"],["<<j<<"],["<<z<<"]: \n";
              }
            }
          }
        }
    }
    void matriz_3D:: repeticiones(int valor){
      //Obtener las veces que un valor específico aparece en la matriz.
      int veces=0;
      for(int i=0;i<num_1;i++){
          for(int j=0;j<num_2;j++){
            for(int z=0;z<num_3;z++){
              if (*(*(*(myBuffer+i)+j)+z) == valor)
              {
                veces+=1;
              }
            }
          }
        }
      cout<<"\n El valor: "<<valor<<" aparece "<<veces<<" veces dentro de la matriz 3D\n";
    }
    



