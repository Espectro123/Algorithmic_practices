#!/bin/bash

for ((i=10000;i<=25*5000;i+=5000)); do

./rep $i >> reparaciones_multiples_heuristico.dat

done
