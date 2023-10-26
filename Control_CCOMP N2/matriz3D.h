#include <iostream>

class matriz_3D{
  public:
    int ***myBuffer;
    int num_1,num_2,num_3;
    //La matriz definida de forma dinamica con un puntero int *** 
    //La matriz definida de forma dinamica con un puntero int *** 
    matriz_3D(int num_1 = 3,int num_2 = 4,int num_3 =2){//las dimensiones del objeto matriz 3D que debe crearse para validar su implementación deben ser: [ 3 ] [ 4 ] [ 2 ] 
      myBuffer = new int**[num_1];
      this->num_1 = num_1;
      for(int i=0;i<num_1;i++){
        myBuffer[i]=new int*[num_2];
        this->num_2 = num_2;
          for(int j=0;j<num_2;j++){
            myBuffer[i][j]=new int[num_3];
            this->num_3 = num_3;
              for(int z=0;z<num_3;z++){
                myBuffer[i][j][z]=0;//Los valores definidos por default con valor de 0
              }
          }
      }

    }
    matriz_3D(matriz_3D &o){
      //Permite copiar un objeto matriz hacia otro.
      myBuffer = new int**[o.num_1];
      this->num_1 = o.num_1;
      for(int i=0;i<num_1;i++){
        myBuffer[i]=new int*[o.num_2];
        this->num_2 = o.num_2;
          for(int j=0;j<num_2;j++){
            myBuffer[i][j]=new int[o.num_3];
            this->num_3 = o.num_3;
              for(int z=0;z<num_3;z++){
                myBuffer[i][j][z]=o.myBuffer[i][j][z];//Los valores definidos por default con valor de 0
              }
          }
      }
    }
    void imprimir();
    void llenar_datos();
    void punto_especifico();
    void suma(matriz_3D A,matriz_3D B,int x,int y,int w);
    void resta(matriz_3D A,matriz_3D B,int x,int y,int w);
    void menor_mayor();
    void indices(int valor);
    void repeticiones(int valor);
    ~matriz_3D() {
      for(int i = 0; i < num_1; i++)
        {
        for(int j = 0; j < num_2; j++)
          {
            delete[] myBuffer[i][j];
          }
        delete[] myBuffer[i];
        }
    delete[] myBuffer;
    }
};
