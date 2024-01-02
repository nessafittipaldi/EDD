/*Esse exercício faz parte do site: https://www.ime.usp.br/~pf/algoritmos/aulas/fila.html

Digamos que nosso alfabeto contém apenas as letras a, b e c. 
Considere o seguinte conjunto de strings:   c,  aca,  bcb,  abcba,  bacab,  aacaa,  bbcbb, …   
Qualquer string desse conjunto tem a forma WcM, sendo W uma sequência de letras que só contém a e b  e  M o inverso de W  (ou seja, M é W lido de trás para frente). 
Escreva um programa que decida se uma string x pertence ou não ao nosso conjunto, ou seja, decida se x é da forma WcM.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Utilizei a função rand para ele considerauma string X aleatória
char* gerarStringAleatoria(int n) {
    char* str = (char*)malloc(sizeof(char) * (n + 1));
    for (int i = 0; i < n; i++) {
        int r = rand() % 2;
        str[i] = 'a' + r; 
    }
    str[n] = '\0';
    return str;
}


int verificaString(char* x) {
    int tamanho = strlen(x);
    
    
    if (tamanho % 2 == 0) {
        return 0; 
    }
    
    int meio = tamanho / 2;
    
    
    for (int i = 0; i < meio; i++) {
        if (x[i] != 'a' && x[i] != 'b') {
            return 0; 
        }
    }
    
    
    for (int i = 0; i < meio; i++) {
        if (x[i] != x[tamanho - i - 1]) {
            return 0; 
        }
    }
    
    
    if (x[meio] != 'c') {
        return 0;
    }
    
    return 1;
}

int main() {
    int tamanho;
    printf("Digite o tamanho da string: ");
    scanf("%d", &tamanho);
    
    srand(time(NULL));
    
    char* x = gerarStringAleatoria(tamanho);
    
    if (verificaString(x)) {
        printf("A string '%s' pertence ao conjunto.\n", x);
    } else {
        printf("A string '%s' não pertence ao conjunto.\n", x);
    }
    
    free(x);
    
    return 0;
}
