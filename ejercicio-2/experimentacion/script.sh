#!/bin/bash
comando_denso="./gen_tiempos < exp2_grafo_denso.txt"
comando_esparzo="./gen_tiempos < exp2_grafo_esparzo.txt"
comando_bipartito="./gen_tiempos < exp2_grafo_bipartito.txt"
comando_estrella="./gen_tiempos < exp2_grafo_estrella.txt"

comando_compilar_denso= "./gen_exp2_denso"
comando_compilar_esparzo= "./gen_exp2_esparzo"
comando_compilar_estrella= "./gen_exp2_estrella"
comando_compilar_bipartito= "./gen_exp2_bipartito"

echo "Empiezo a compilar todos los experimentos"

eval $comando_compilar_denso
eval $comando_compilar_esparzo
eval $comando_compilar_estrella
eval $comando_compilar_bipartito

date

echo "Empiezo a correr todos los experimentos"
eval $comando_denso
mv cambiar_nombre_exp.csv datos_exp_2_denso.csv
echo "denso listo"
eval $comando_estrella
mv cambiar_nombre_exp.csv datos_exp_2_estrella.csv
echo "estrella listo"
eval $comando_esparzo
mv cambiar_nombre_exp.csv datos_exp_2_esparzo.csv
echo "esparzo listo"
eval $comando_bipartito
mv cambiar_nombre_exp.csv datos_exp_2_bipartito.csv
echo "bipartito listo"
echo "Terminé de correr todos los experimentos!!!"
date



# usar chmod u+x script1.sh
