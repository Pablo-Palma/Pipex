#!/bin/bash

run_test() {
    description=$1
    pipex_cmd=$2
    shell_cmd=$3
    echo "Running test: $description"

    # Ejecutar comandos y capturar códigos de salida
    eval $pipex_cmd 2> pipex_error.txt
    pipex_exit_code=$?
    eval $shell_cmd 2> shell_error.txt
    shell_exit_code=$?

    # Comparar archivos de salida si ambos comandos se ejecutaron correctamente
    if [ $pipex_exit_code -eq 0 ] && [ $shell_exit_code -eq 0 ]; then
        if diff -u pipex_output.txt shell_output.txt > /dev/null; then
            echo -e "\033[32mTest PASSED\033[0m"
        else
            echo -e "\033[31mTest FAILED (Output Mismatch)\033[0m"
        fi
    else
        # Extraer la última parte de los mensajes de error
        pipex_error=$(tail -n 1 pipex_error.txt | awk -F ': ' '{print $NF}')
        shell_error=$(tail -n 1 shell_error.txt | awk -F ': ' '{print $NF}')

        # Comprobar si las partes extraídas son iguales
        if [ "$pipex_error" = "$shell_error" ]; then
            echo -e "\033[32mTest PASSED (Error Messages Match)\033[0m"
        else
            echo -e "\033[31mTest FAILED (Error Messages Do Not Match)\033[0m"
        fi
    fi

    rm -f pipex_output.txt shell_output.txt pipex_error.txt shell_error.txt
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

run_test "Múltiples Comandos" \
"./pipex input_file.txt 'grep test' 'wc -l' pipex_output.txt" \
"< input_file.txt grep test | wc -l > shell_output.txt"

run_test "Comando awk y Comillas Simples" \
"./pipex input_file.txt \"awk '/test/'\" 'cat' pipex_output.txt" \
"< input_file.txt awk '/test/' | cat > shell_output.txt"

run_test "Comandos con Ruta Completa" \
"./pipex input_file.txt '/bin/cat' '/usr/bin/wc -l' pipex_output.txt" \
"< input_file.txt /bin/cat | /usr/bin/wc -l > shell_output.txt"

run_test "Archivo de Entrada Inexistente" \
"./pipex non_existing_file 'cat' 'wc -l' pipex_output.txt" \
"< non_existing_file cat | wc -l > shell_output.txt"

run_test "Pipelines Largos" \
"./pipex input_file.txt 'grep test' 'sort' 'uniq' 'wc -l' pipex_output.txt" \
"< input_file.txt grep test | sort | uniq | wc -l > shell_output.txt"

run_test "Redirección de Here Document" "./pipex here_doc END 'grep hola munod' 'wc -l' pipex_output.txt" "grep hola mundo << END | wc -l > shell_output.txt"

