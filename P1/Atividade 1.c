/*

Exercício de multiplicação por soma.
Aproveitei e utilizei a função aleatório e a função para medir o tempo de execução do programa.

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int multiplicar(int x, int y){
    int resultado = 0;
    while (y > 0){
        resultado += x;
        y--;
    }

    return resultado;

}

int main (){

    clock_t inicio, fim;
    double tempo;
    int y, x, resultado;

    inicio = clock();

    srand(time(NULL));
    x = rand() % 100 + 1;
    y = rand() % 100 + 1;

    resultado = multiplicar(x, y);

    printf("%d x %d = %d\n", x, y, resultado);
    
    fim = clock();
    tempo = ((double) (fim - inicio))/CLOCKS_PER_SEC;

    printf("Tempo de execução: %f segundos\n", tempo);

    return 0;
}
