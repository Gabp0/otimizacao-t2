GROUPS=10
PEOPLE=30
ROLES=12

echo "${GROUPS} ${PEOPLE} ${ROLES}" | python3 geraInput.py > run_test_saida.txt

echo "Rodando o main com -a"
./elenco_main -a < run_test_saida.txt

echo "Rodando o da branch"
./elenco < run_test_saida.txt

rm run_test_saida.txt