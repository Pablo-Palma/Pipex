#!/bin/bash

# Definición de la función run_test
run_test() {
    description=$1
    pipex_cmd=$2
    shell_cmd=$3
    echo "Running test: $description"
    eval $pipex_cmd
    eval $shell_cmd

    # Comparamos los archivos con diff
    if diff -u pipex_output.txt shell_output.txt; then
        echo "Test PASSED"
    else
        echo "Test FAILED. Error code: $?"
    fi

    rm -f pipex_output.txt shell_output.txt
    echo "--------------------------------"
}

# Llamadas a la función run_test para realizar pruebas

run_test "Contar palabras" "./pipex input_file.txt 'cat' 'wc -w' pipex_output.txt" "< input_file.txt cat | wc -w > shell_output.txt"

run_test "Convertir a mayúsculas" "./pipex input_file.txt 'cat' 'tr a-z A-Z' pipex_output.txt" "< input_file.txt cat | tr a-z A-Z > shell_output.txt"

run_test "Ordenar líneas" "./pipex input_file.txt 'cat' 'sort' pipex_output.txt" "< input_file.txt cat | sort > shell_output.txt"

run_test "Buscar palabra y mostrar líneas" "./pipex input_file.txt 'grep palabra' 'cat' pipex_output.txt" "< input_file.txt grep palabra | cat > shell_output.txt"

run_test "Contar caracteres" "./pipex input_file.txt 'cat' 'wc -c' pipex_output.txt" "< input_file.txt cat | wc -c > shell_output.txt"

run_test "Contar líneas" "./pipex input_file.txt 'cat' 'wc -l' pipex_output.txt" "< input_file.txt cat | wc -l > shell_output.txt"

run_test "Mostrar primeras líneas" "./pipex input_file.txt 'cat' 'head -n 5' pipex_output.txt" "< input_file.txt cat | head -n 5 > shell_output.txt"

run_test "Mostrar últimas líneas" "./pipex input_file.txt 'cat' 'tail -n 5' pipex_output.txt" "< input_file.txt cat | tail -n 5 > shell_output.txt"

run_test "Invertir líneas" "./pipex input_file.txt 'cat' 'tail -r' pipex_output.txt" "< input_file.txt cat | tail -r > shell_output.txt"

run_test "Eliminar duplicados" "./pipex input_file.txt 'cat' 'uniq' pipex_output.txt" "< input_file.txt cat | uniq > shell_output.txt"

