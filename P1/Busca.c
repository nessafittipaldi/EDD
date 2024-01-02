/*

Exercício de busca binária que consiste em um gerador de senhas aleatórias que utiliza da busca binária para verificar se a senha gerada é nova ou se já foi utilizada.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAMANHO_SENHA 6
#define TAMANHO_MAXIMO 12


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

int main() {

  srand(time(NULL));

  char caracteres[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+{}[];:'<>,.?/|";

  char senhas[TAMANHO_MAXIMO][TAMANHO_SENHA + 1];
  int quantidade_senhas = 0;
  FILE *arquivo = fopen("senhas.txt", "r");
  if (arquivo != NULL) {
    char linha[TAMANHO_SENHA + 1];
    while (fgets(linha, TAMANHO_SENHA + 1, arquivo) != NULL) {
      linha[strcspn(linha, "\n")] = '\0';
      strcpy(senhas[quantidade_senhas], linha);
      quantidade_senhas++;
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

    if (busca_binaria(senhas, 0, quantidade_senhas - 1, senha)) {
      printf("A senha gerada já foi utilizada anteriormente. Gerando uma nova senha...\n");
    }
  } while (busca_binaria(senhas, 0, quantidade_senhas - 1, senha));

  strcpy(senhas[quantidade_senhas], senha);
  quantidade_senhas++;

			arquivo = fopen("senhas.txt", "w");
		if (arquivo != NULL) {
			for (int i = 0; i < quantidade_senhas; i++) {
				fprintf(arquivo, "%s\n", senhas[i]);
			}
				fclose(arquivo);
			} else {
			printf("Erro ao salvar as senhas no arquivo.\n");
			}
	
		printf("Senha gerada: %s\n", senha);
	
	return 0;
}
