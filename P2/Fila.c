/*

Nesse código eu refatorei o código que fiz para busca binária e 
implementei os conceitos de fila para organizar as senhas*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAMANHO_SENHA 6
#define TAMANHO_MAXIMO 12

typedef struct fila {
  char senhas[TAMANHO_MAXIMO][TAMANHO_SENHA + 1];
  int inicio;
  int fim;
  int tamanho;
} Fila;


int busca_binaria(char senhas[][TAMANHO_SENHA + 1], int inicio, int fim, char senha[]) {
  if (inicio <= fim) {
    int meio = (inicio + fim) / 2;
    int comparacao = strcmp(senhas[meio], senha);
    if (comparacao == 0) {
     
      return 1;
    } else if (comparacao < 0) {

      return busca_binaria(senhas, meio + 1, fim, senha);
    } else {
      
      return busca_binaria(senhas, inicio, meio - 1, senha);
    }
  }
  
  return 0;
}


void enfileirar(Fila *fila, char senha[]) {
  if (fila->tamanho < TAMANHO_MAXIMO) {
    strcpy(fila->senhas[fila->fim], senha);
    fila->fim = (fila->fim + 1) % TAMANHO_MAXIMO;
    fila->tamanho++;
  } else {
    printf("A fila de senhas já atingiu o tamanho máximo. Removendo a senha mais antiga...\n");
    fila->inicio = (fila->inicio + 1) % TAMANHO_MAXIMO;
		strcpy(fila->senhas[fila->fim], senha);
		fila->fim = (fila->fim + 1) % TAMANHO_MAXIMO;

	}
}

int main() {
	srand(time(NULL));	
	char caracteres[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+{}[];:'<>,.?/|";
    int senha_repetida = 0;
	
	Fila fila;
	fila.inicio = 0;
	fila.fim = 0;
	fila.tamanho = 0;


	FILE *arquivo = fopen("senhas.txt", "r");
		if (arquivo != NULL) {
			char linha[TAMANHO_SENHA + 1];
		while (fgets(linha, TAMANHO_SENHA + 1, arquivo) != NULL) {
			linha[strcspn(linha, "\n")] = '\0';
			enfileirar(&fila, linha);
		}
	fclose(arquivo);
	}

	
	char senha[TAMANHO_SENHA + 1];
	do {
		for (int i = 0; i < TAMANHO_SENHA; i++) {
			int indice = rand() % (sizeof(caracteres) - 1);
			senha[i] = caracteres[indice];
		}
	    senha[TAMANHO_SENHA] = '\0';

        int senha_repetida = 0;
        for (int i = 0; i < fila.tamanho; i++) {
            if (strcmp(fila.senhas[(fila.inicio + i) % TAMANHO_MAXIMO], senha) == 0) {
                senha_repetida = 1;
                break;
            }
        }

        if (senha_repetida) {
            printf("A senha gerada já foi utilizada anteriormente. Gerando uma nova senha...\n");
        } 

    } while (senha_repetida);

	    enfileirar(&fila, senha);
	    arquivo = fopen("senhas.txt", "w");
	    if (arquivo != NULL) {
		    for (int i = 0; i < fila.tamanho; i++) {
		        fprintf(arquivo, "%s\n", fila.senhas[(fila.inicio + i) % TAMANHO_MAXIMO]);
		        }
	        fclose(arquivo);
	        } else {
		        printf("Erro ao salvar as senhas no arquivo.\n");
	        }
            
        printf("Senha gerada: %s\n", senha);
        return 0;
}
