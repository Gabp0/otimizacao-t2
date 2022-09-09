#!/bin/bash

echo > resultados.txt
for counter in {1..1000}
do
    
    # GROUPS=$(( 7 * counter ))
    # PEOPLE=$(( 10 * counter ))
    # ROLES=$(( 4 * counter ))
    
    GROUPS=9
    PEOPLE=15
    ROLES=6
    
    echo "${GROUPS} ${PEOPLE} ${ROLES}" | python3 geraInput.py > run_test_saida.txt
    echo "${GROUPS} ${PEOPLE} ${ROLES}" >> resultados.txt
    
    echo "Rodando o main com -a"
    ./elenco_main -a < run_test_saida.txt >> saida_main.txt
    
    echo "Rodando o da branch"
    ./elenco < run_test_saida.txt >> saida_branch.txt
    
    #diff saida_main.txt saida_branch.txt >> resultados.txt
    
    rm run_test_saida.txt
done