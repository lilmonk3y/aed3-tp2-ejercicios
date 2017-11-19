#!/bin/bash
comando_denso="./gen_tiempos < exp2_grafo_denso.txt"
comando_esparzo="./gen_tiempos < exp2_grafo_esparzo.txt"
comando_bipartito="./gen_tiempos < exp2_grafo_bipartito.txt"
comando_estrella="./gen_tiempos < exp2_grafo_estrella.txt"


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
