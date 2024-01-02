/* Esse exercício faz parte do site: https://www.ime.usp.br/~pf/algoritmos/aulas/fila.html

1.Imagine uma implementação circular de fila em um vetor fila[0..9] que contém:
16 17 18 19 20 11 12 13 14 15
Suponha que o primeiro elemento da fila está na posição de índice 5 e o último está na posição de índice 4.
Essa fila está cheia?

*/

#include <stdio.h>

#define TAMANHO_MAX 10

int filaCheia(int inicio, int fim) {
    return (fim + 1) % TAMANHO_MAX == inicio;
}

int main() {
    int fila[TAMANHO_MAX] = {16, 17, 18, 19, 20, 11, 12, 13, 14, 15};
    int inicio = 5;
    int fim = 4;

    if (filaCheia(inicio, fim)) {
        printf("A fila está cheia.\n");
    } else {
        printf("A fila não está cheia.\n");
    }

    return 0;
}
