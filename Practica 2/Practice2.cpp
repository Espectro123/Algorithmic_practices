#include <iostream>
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;
using namespace std::chrono;


/*
Generador de ejemplos para el problema del elemento en su posici�n.
Para rellenar el vector de tamaño n, genera todos los enteros entre -(n-1) y (n-1) en un vector auxiliar;
despu�s obtiene una permutacion aleatoria de ese vector,
se queda con los n primeros elementos, y los ordena de forma creciente
*/

//Genera un numero uniformemente distribuido en el
//intervalo [0,1) a partir de uno de los generadores
//disponibles en C
double uniforme(){

 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;

}

//ALGORITMO DE FUERZA BRUTA
//Devuelve -1 si no se ha encontrado el elemento
//Si encuentra el elemento devuelve la posicion del vector en la que se ha encontrado
//1º parametro: Vector en el que buscar el elemento
//2º parametro: Elemento a buscar
int brute_force(vector<int> myvector, int elemento){

  int posicion = -1;

  for(int i = 0; i < myvector.size() && posicion == -1; ++i){

    if(myvector[i] == elemento){
      posicion = i;
    }

  }

 return posicion;
}

//ALGORITMO BASADO EN LA TECNICA DIVIDE Y VENCERAS
//Devuelve -1 si no se ha encontrado el elemento
//Si encuentra el elemento devuelve la posicion del vector en la que se ha encontrado
//1º parametro: Vector en el que buscar el elemento
//2º parametro: Elemento a buscar
//3º parametro: iterador que apunta al principio del vector
//4º paramentor: Iterador que apunta al final del vector
vector<int>::iterator divide_y_venceras(vector<int> myvector,int elemento,vector<int>::iterator inicio, vector<int>::iterator fin){

  int posicion_i = -1;
  int posicion_f = -1;
  vector<int>::iterator medio;

  //Obtengo el punto medio del vector
  if(inicio <= fin){

    posicion_i = inicio - myvector.begin();
    posicion_f = fin - myvector.begin();
    medio = myvector.begin() + (posicion_i + posicion_f)/2;

    //Compruebo si el elemento se encuentra en el punto medio
    //Este sera el caso base
    if(elemento == *medio){

      return medio;

    }else if(elemento < *medio){

      return divide_y_venceras(myvector,elemento,inicio,medio-1);

    }else if(elemento > *medio){

      return divide_y_venceras(myvector,elemento,medio+1,fin);

    }


  }else{

    return myvector.end();

  }





}

/*
1º Argumento: N -> Tamaño del Vector
2º Argumento: Algoritmo -> Para seleccionar el algoritmo a buscar
3º Argumento: Obtiene el elemento a buscar. Debe ser de 0 a N
*/
int main(int argc, char * argv[]){

  if (argc != 4)
    {
      cerr << "Formato " << argv[0] << " <num_elem>  <Algoritmo(0-> Fuerza bruta 1-> D&C)>" << endl;
      return -1;
    }

  int n = atoi(argv[1]);
  int algoritmo = atoi(argv[2]);
  int indice_del_vector = atoi(argv[3]);
  int m=2*n-1;
  int posicion = -1;

  int * T = new int[n];
  assert(T);
  int * aux = new int[m];
  assert(aux);

  srand(time(0));
  //genero todos los enteros entre -(n-1) y n-1
  for (int j=0; j<m; j++) aux[j]=j-(n-1);

  //algoritmo de random shuffling the Knuth (permutacion aleatoria)
  for (int j=m-1; j>0; j--) {
     double u=uniforme();
     int k=(int)(j*u);
     int tmp=aux[j];
     aux[j]=aux[k];
     aux[k]=tmp;
  }

  //me quedo con los n primeros del vector
  for (int j=0; j<n; j++) T[j]=aux[j];

  //Y ahora ordeno el vector T
  vector<int> myvector (T, T+n);
  vector<int>::iterator it;

  sort(myvector.begin(),myvector.end());

  /*
   for (it=myvector.begin(); it!=myvector.end(); ++it)
      cout << " " << *it;
 */

  delete [] aux;

  //Elemento que se buscara en el vector
  int elemento = myvector[indice_del_vector];

  vector<int>::iterator inicio = myvector.begin();
  vector<int>::iterator fin = myvector.begin() + myvector.size();
  vector<int>::iterator iterador_posicion;

  high_resolution_clock::time_point antes, despues;
  duration<double> transcurrido;

  if(algoritmo == 0){

    antes = high_resolution_clock::now();
    posicion = brute_force(myvector,elemento);
    despues = high_resolution_clock::now();
    transcurrido = duration_cast<duration<double>>(despues - antes);

  }else{

    antes = high_resolution_clock::now();
    iterador_posicion = divide_y_venceras(myvector,elemento,inicio,fin);

    if(*iterador_posicion != 0){
       posicion = iterador_posicion - myvector.begin();
    }else{
      posicion = -1;
    }

    despues = high_resolution_clock::now();
    transcurrido = duration_cast<duration<double>>(despues - antes);

  }

  cout << n << " " << transcurrido.count() << endl;

}
