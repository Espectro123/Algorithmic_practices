#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <math.h>
#include <stdlib.h>

using namespace std;

//Funcion que lle ficheros de tipo tsp;
void read_file(ifstream& ff,vector<int>& xCord, vector<int>& yCord){


    int xCurrentLine;
    int yCurrentLine;
    int cityNumber;
    int numberCities;
    string aux;
    string aux2;
    //Obtengo el numero de ciudades
    ff >> aux;
    ff >> aux;

    numberCities = stoi(aux,nullptr,0); //Obtengo el numero de ciudades

    for(int i = 0; i<numberCities; i++){
        ff >> cityNumber;
        ff >> xCurrentLine;
        ff >> yCurrentLine;
        //do whatever you wanted to do with cityNumber
        xCord.push_back(xCurrentLine);
        yCord.push_back(yCurrentLine);
    }



}


//Obtengo la distancia entre dos ciudades
/*
xi e yi => Coordenadas x e y de la primera ciudad
xj e yj => Coordenadas x e y de la segunda ciudad
Esta funcion calcula la distancia euclidia entre dos ciudades
*/
int obtener_distancia(int xi, int yi, int xj, int yj){

  int resultado = 0;

  resultado = sqrt(pow((xj - xi),2) + pow((yj - yi),2));

  return resultado;
}

//Obtiene la solucion usando la heuristica del vecino mas cercano
vector<int> vecino_mas_cercano(vector<int> xCord, vector<int> yCord){

 vector<int> vector_solucion;
 vector<int> candidatos;
 int numero_de_ciudades = xCord.size();
 int distancia = 0;
 int solucion = 0;
 int mejor_distancia = 9999;

 for(int i = 1; i <= numero_de_ciudades; i++){

   candidatos.push_back(i);

 }

 vector_solucion.push_back(candidatos[0]); //Empiezo el algoritmo desde la ciudad 0

 candidatos.erase(candidatos.begin()); //Borro la ciudad 0 de lso posibles candidatos


 while(candidatos.size()-1 != 0){


   //recorremos todas las ciudades buscando el vecino mas cercano
   for(int i = 0; i < candidatos.size(); i++){


     distancia = obtener_distancia(xCord[vector_solucion.back()],yCord[vector_solucion.back()],xCord[candidatos[i]],yCord[candidatos[i]]);

     if(distancia < mejor_distancia){

       solucion = candidatos[i];
       mejor_distancia = distancia;

     }

   }

   //Reseteo los valores
   distancia = 9999;
   mejor_distancia = 9999;
   //Guardo la mejor solucion y la elimino de la lista de posibles ciudades
   vector_solucion.push_back(solucion);
   vector<int>::iterator it = candidatos.begin();
   bool encontrado = false;
   for(int i = 0; i < candidatos.size() && !encontrado; i++){

     if(candidatos[i] == solucion){
       advance(it,i);
       encontrado = true;
     }

   }

   candidatos.erase(it);

   }
    return vector_solucion;
}

//Obtiene la solucion usando la heuristica de la mejor insercion
vector<int> mejor_insercion(vector<int> xCord, vector<int> yCord){

   vector<int> vector_solucion;
   vector<int> candidatos;
   int numero_de_ciudades = xCord.size();
   int distancia = 0;
   int solucion = 0;
   int mejor_distancia = 9999;

   for(int i = 1; i < numero_de_ciudades; i++){

     candidatos.push_back(i);

   }

   vector_solucion.push_back(candidatos[0]); //Empiezo el algoritmo desde la ciudad 0

   candidatos.erase(candidatos.begin()); //Borro la ciudad 0 de los posibles candidatos

   while(candidatos.size() > 0){

     for(int i = 0; i < candidatos.size(); i++){

       for(int j = 0; j < vector_solucion.size(); j++){

         distancia = obtener_distancia(xCord[vector_solucion[j]],yCord[vector_solucion[j]],xCord[candidatos[i]],yCord[candidatos[i]]);

       }
     }

   }


}

//Obtiene la solucion usando la heuristica implementada por el grupo
/*
Descripcion de la heuristica:
Seleccion del nodo aleatoria
*/
vector<int> tercera_heuristica(vector<int> xCord, vector<int> yCord){

  vector<int> vector_solucion;
  vector<int> candidatos;
  int numero_de_ciudades = xCord.size();
  int distancia = 0;
  int solucion = 0;
  int mejor_distancia = 9999;
  int numero_random;


  for(int i = 1; i < numero_de_ciudades; i++){

    candidatos.push_back(i);

  }

  vector_solucion.push_back(candidatos[0]); //Empiezo el algoritmo desde la ciudad 0

  candidatos.erase(candidatos.begin()); //Borro la ciudad 0 de los posibles candidatos


  while(candidatos.size() != 0){



  }

}
/*
1º Parametro: Nombre del Archivo
2º Parametro: heuristica (0 => vecino mas cercano) (1 => mejor inserccion)
*/
int main(int argc, char** argv){

  if(argc < 3){
    cout << "1º parametro: Ruta hasta el archivo" << endl;
    cout << "2º parametro: Heuristica(0 o 1 o 2)" << endl;
    exit(-1);
  }

  srand (time(NULL));
  vector<int> xCord;
  vector<int> yCord;
  vector<int> solucion;
  string archivo = argv[1];
  int heuristica = atoi(argv[2]);

  ifstream lector(archivo);

  //Leo el fichero de pruebas
  if(lector.is_open()){

    cout << "Archivo leido con exito" << endl;
    read_file(lector,xCord,yCord); //Obtengo los vectores de coordenadas x e y
    lector.close();
  }else{

    cout << "No se ha podido abrir el archivo" << endl;
    exit(-1);

  }

  if(heuristica == 0){

      solucion = vecino_mas_cercano(xCord,yCord);

  }else if(heuristica == 1){

      solucion = mejor_insercion(xCord,yCord);

  }else{
    cout << "Introduzca 0 para la heuristica del vecino mas cercano o 1 para la de mejor inserccion" << endl;
    exit(-1);
  }




  for(int i = 0; i < solucion.size()-1; i++){
    cout << solucion[i] << " ";
  }
  cout << endl;



}
