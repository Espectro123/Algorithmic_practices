#!/bin/bash

#Creo los archivos .dat

touch datos/burbuja.dat
touch datos/fibonacci.dat
touch datos/floyd.dat
touch datos/hanoi.dat
touch datos/heapsort.dat
touch datos/insercion.dat
touch datos/mergesort.dat
touch datos/quicksort.dat
touch datos/seleccion.dat



#Algorimos n2
#100, 1000, 5000, 10000, 50.000, 100.000
for ((i=1000;i <= 25*1000;i+=1000)); do
#./burbuja $i >> datos/burbuja.dat
./insercion $i >> datos/insercion.dat
#./seleccion $i >> datos/seleccion.dat
done

#Algoritmos nlogn
for ((i=20000;i <= 25*20000;i+=20000)); do
#./mergesort $i >> datos/mergesort.dat
#./quicksort $i >> datos/quicksort.dat
./heapsort $i >> datos/heapsort.dat
done
#Algoritmos n3
for ((i=60;i <= 720;i+=30)); do
./floyd $i >> datos/floyd.dat
done

#Algoritmos 2^n
for ((i=3;i<=27;i+=1)); do
./hanoi $i >> datos/hanoi.dat
done
