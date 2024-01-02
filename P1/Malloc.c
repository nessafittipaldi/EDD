/* 

Exercício para treinar malloc.

Suponha dado um arquivo de texto que contém uma sequência de números inteiros. O comprimento da sequência é desconhecido. 
Escreva uma função que imprima esses números em ordem inversa (o último, depois o penúltimo, etc.).  
É claro que você terá que ler todos os números e armazená-los na memória.  
A dificuldade está em alocar espaço para uma quantidade de números que só será conhecida quando chegarmos ao fim do arquivo.

*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *arquivo = fopen("numeros.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!");
        return 1;
    }

    int tamanho = 1;
    int *numeros = (int*) malloc(sizeof(int)); 
    int numero;

    while (fscanf(arquivo, "%d", &numero) == 1) {
        numeros[tamanho-1] = numero;
        tamanho++;
        numeros = (int*) realloc(numeros, sizeof(int) * tamanho);
    }

    fclose(arquivo);
   
    for (int i = tamanho-2; i >= 0; i--) {
        printf("%d\n", numeros[i]);
    }

    free(numeros);

    return 0;
}
