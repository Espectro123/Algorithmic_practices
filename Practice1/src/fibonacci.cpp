/**
   @file C�lculo de la sucesi�n de Fibonacci
*/
#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

/**
   @brief Calcula el t�rmino n-�simo de la sucesi�n de Fibonacci.

   @param n: n�mero de orden del t�rmino buscado. n >= 1.

   @return: t�rmino n-�simo de la sucesi�n de Fibonacci.
*/
int fibo(int n)
{
  if (n < 2)
    return 1;
  else
    return fibo(n-1) + fibo(n-2);
}


int main(int argc, char* argv[])
{

  int n = atoi(argv[1]);
  int f = 0;

  high_resolution_clock::time_point antes, despues;
  duration<double> transcurrido;

  antes = high_resolution_clock::now();
  f = fibo(n);
  despues = high_resolution_clock::now();

  transcurrido = duration_cast<duration<double>>(despues - antes);

  cout << n << " " << transcurrido.count() << endl;

  return 0;
}
