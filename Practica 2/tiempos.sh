#!/bin/bash


for ((i=10000;i<=25*10000;i+=10000)); do

./practica2 $i $1 500 >> tiempo_binary.dat

done
