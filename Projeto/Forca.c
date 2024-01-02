/*

    PROJETO INDIVUDUAL - JOGO DA FORCA COM LISTA ENCADEADA
    O Jogo da Forca é um jogo clássico onde o jogador deve adivinhar uma palavra secreta, inserindo letras uma de cada vez. 
    O jogador tem um número limitado de tentativas antes de perder o jogo. 
    O objetivo é descobrir a palavra secreta antes de cometer muitos erros.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PALAVRAS_PATH "palavras.txt"
#define MAX_LETRAS_CHUTADAS 15
#define MAX_TAMANHO_PALAVRA 15

void limpar_tela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void abertura (){
    printf("****************************************\n");
    printf("*     BEM VINDO AO JOGO DA FORCA!!     *\n");
    printf("****************************************\n\n");
    
    printf("INSTRUÇÕES:\n");
    printf("O jogo da forca consiste em descobrir uma palavra secreta.\n");
    printf("Você terá 6 tentativas para adivinhar a palavra, caso contrário, perderá o jogo.\n");
    printf("Cada vez que você errar uma letra, uma parte do corpo será adicionada à forca.\n");
    printf("Se conseguir adivinhar a palavra antes de completar a forca, você vence o jogo!\n");
    printf("Pressione ENTER para continuar.\n");
    
    getchar();
    limpar_tela();
}

typedef struct No {
    char letra;
    struct No* proximo;
} No;

No* criar_no(char letra) {
    No* novo_no = malloc(sizeof(No));
    novo_no->letra = letra;
    novo_no->proximo = NULL;
    return novo_no;
}

No* adicionar_no(No* palavra_oculta, char letra) {
    if (palavra_oculta == NULL) {
        palavra_oculta = criar_no(letra);
    } else {
        No* atual = palavra_oculta;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = criar_no(letra);
    }
    return palavra_oculta;
}

void liberar_lista_palavra_oculta(No* palavra_oculta) {
    No* atual = palavra_oculta;
    while (atual != NULL) {
        No* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
}

void exibir_palavra_oculta(No* palavra_oculta) {
    No* atual = palavra_oculta;
    while (atual != NULL) {
        printf("%c ", atual->letra);
        atual = atual->proximo;
    }
    printf("\n");
}

void desenhar_forca(int erros) {
    printf("._______     \n");
    printf("|      !     \n");
    if (erros >= 1) {
        printf("|      O     \n");
    } else {
        printf("|            \n");
    }
    if (erros >= 2) {
        if (erros >= 4) {
            printf("|     /|\\   \n");
        } else if (erros >= 3) {
            printf("|     /|    \n");
        } else {
            printf("|      |    \n");
        }
    } else {
        printf("|            \n");
    }
    if (erros >= 6) {
        printf("|     / \\   \n");
    } else if (erros >= 5) {
        printf("|     /      \n");
    } else {
        printf("|            \n");
    }
    printf("|____________\n");
}

int quantidade_palavras(FILE* arquivo) {
    int quantidade = 0;
    char palavra[MAX_TAMANHO_PALAVRA];

    rewind(arquivo);

    while (fgets(palavra, sizeof(palavra), arquivo) != NULL) {
        quantidade++;
    }

    return quantidade;
}

char* escolher_palavra(FILE* arquivo) {
    int quantidade = quantidade_palavras(arquivo);

    if (quantidade == 0) {
        return NULL;
    }

    srand(time(NULL));
    int numero_aleatorio = rand() % quantidade;

    char palavra[MAX_TAMANHO_PALAVRA];

    rewind(arquivo);

    for (int i = 0; i <= numero_aleatorio; i++) {
        fgets(palavra, sizeof(palavra), arquivo);
    }

    palavra[strcspn(palavra, "\n")] = '\0';

    char* palavra_secreta = malloc((strlen(palavra) + 1) * sizeof(char));
    strcpy(palavra_secreta, palavra);

    return palavra_secreta;
}

int contar_letras(char* palavra) {
    int quantidade = 0;
    for (int i = 0; palavra[i] != '\0'; i++) {
        if (palavra[i] != ' ') {
            quantidade++;
        }
    }
    return quantidade;
}

int letra_ja_chutada(char letra, char* letras_chutadas, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (letras_chutadas[i] == letra) {
            return 1;
        }
    }
    return 0;
}

void adicionar_palavra(FILE* arquivo) {
    char novaPalavra[MAX_TAMANHO_PALAVRA];
    printf("A palavra deve ter até 15 letras. Digite tudo em maiúsculo.\n");
    printf("Digite a nova palavra: ");
    scanf("%s", novaPalavra);

    FILE* arquivo_palavras = fopen(PALAVRAS_PATH, "a");

    if (arquivo_palavras == NULL) {
        printf("Desculpe, banco de dados de palavras não disponível.\n\n");
        exit(1);
    }

    fprintf(arquivo_palavras, "\n%s", novaPalavra);

    fclose(arquivo_palavras);

    getchar();
}

void jogar(FILE* arquivo) {
    char letras_chutadas[MAX_LETRAS_CHUTADAS];
    int tentativas = 0;
    int acertos = 0;
    int erros = 0;
    char* palavra_secreta = NULL;
    No* palavra_oculta = NULL;

    palavra_secreta = escolher_palavra(arquivo);

    if (palavra_secreta == NULL) {
        printf("Nenhuma palavra cadastrada.\n");
    } else {
        liberar_lista_palavra_oculta(palavra_oculta);
        palavra_oculta = NULL;
        tentativas = 0;
        acertos = 0;
        erros = 0;

        int tamanho_palavra = strlen(palavra_secreta);
        int quantidade_letras = contar_letras(palavra_secreta);
        printf("A palavra oculta possui %d letras.\n\n", quantidade_letras);
        for (int i = 0; i < tamanho_palavra; i++) {
            if (palavra_secreta[i] == ' ') {
                palavra_oculta = adicionar_no(palavra_oculta, ' ');
                acertos++;
            } else {
                palavra_oculta = adicionar_no(palavra_oculta, '_');
            }
        }

        char letra;
        while (acertos < tamanho_palavra && erros < 6) {
            printf("\n");
            desenhar_forca(erros);
            exibir_palavra_oculta(palavra_oculta);
            printf("Entre com uma letra: ");
            scanf(" %c", &letra);
            getchar(); // Limpar o buffer do teclado

            if (letra_ja_chutada(letra, letras_chutadas, tentativas)) {
                printf("Letra já chutada. Tente novamente.\n");
                continue;
            }

            letras_chutadas[tentativas] = letra;
            tentativas++;

            int encontrou = 0;
            No* atual = palavra_oculta;
            for (int i = 0; i < tamanho_palavra; i++) {
                if (palavra_secreta[i] == ' ' && atual->letra == ' ') {
                    atual = atual->proximo;
                    continue;
                }
                if (palavra_secreta[i] == letra && atual->letra == '_') {
                    atual->letra = letra;
                    acertos++;
                    encontrou = 1;
                }
                atual = atual->proximo;
            }

            if (!encontrou) {
                erros++;
            }
        }

        printf("\n");
        desenhar_forca(erros);
        exibir_palavra_oculta(palavra_oculta);

        if (acertos == tamanho_palavra) {
            printf("\nParabéns, você acertou a palavra!\n\n");
        } else {
            printf("\nQue pena, você perdeu. A palavra era: %s\n", palavra_secreta);
        }

        free(palavra_secreta);
    }
}

int main() {
    abertura ();

    FILE* arquivo = fopen(PALAVRAS_PATH, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de palavras.\n");
        return 1;
    }

    int opcao;
    int continuar = 1;

    do {
        printf("****************************\n");
        printf("****        MENU        ****\n");
        printf("*        Opções:           *\n");
        printf("*  [1] - Adicionar Palavra *\n");
        printf("*  [2] - Jogar             *\n");
        printf("*  [0] - Sair              *\n");
        printf("****************************\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao);
        getchar();
        limpar_tela();

        switch (opcao) {
            case 1:
                adicionar_palavra(arquivo);
                break;
            case 2:
                jogar(arquivo);
                break;
            case 0:
                continuar = 0;
                printf("Obrigado por jogar! Até a próxima.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }

        if (opcao == 2) {
            printf("Deseja continuar jogando? (1 - Sim, 0 - Não): ");
            scanf("%d", &continuar);
            getchar();
        }

        limpar_tela();

    } while (continuar && opcao != 0);

    fclose(arquivo);

    return 0;
}

