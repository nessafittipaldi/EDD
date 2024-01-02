/*

Exercício de nivelamento da sala.
Apresentação de uma calculadora em C que fiz no semestre anterior em LG1 e inseri o por extenso no resultado.
*/

#include <stdio.h>
#include <stdlib.h>

int soma() {
    int y, x, resultado;
    printf("\nDigite o primeiro valor:");
    scanf("%d", &x);
    printf("Digite o segundo valor:");
    scanf("%d", &y);
    resultado = x + y;
    printf("Resultado: %d\n", resultado);
}

int subtracao() {
    int y, x, resultado;
    printf("\nDigite o primeiro valor:");
    scanf("%d", &x);
    printf("Digite o segundo valor:");
    scanf("%d", &y);
    resultado = x - y;
    printf("Resultado: %d\n", resultado);
}

//O resultado da calculadora é escrito por extenso.
void PorExtenso(){
    int resultado;
    int c,d,u;

  c = resultado / 100;
	d = (resultado % 100) / 10;
	u = resultado % 10;
	
	if(resultado > 999 || resultado < 0){
		printf("** INVALIDO **");
          return 1;
	} else{
	   
	if(resultado == 100)
		printf("cem");
	else {
		switch(c){
			case 1 : printf("cento ");
				break;
			case 2 : printf("duzentos ");
				break;
			case 3 : printf("trezentos ");
				break;
			case 4 : printf("quatrocentos ");
				break;
			case 5 : printf("quinhentos ");
				break;
			case 6 : printf("seiscentos ");
				break;
			case 7 : printf("setecentos ");
				break;
			case 8 : printf("oitocentos ");
				break;
			case 9 : printf("novecentos ");
				break;
		}
		
		if( c != 0 && (d != 0 || u !=0))
			printf(" e ");
		
			switch(d){
			case 1 : 
					switch(u){
						case 0 : printf("dez ");
							break;
						case 1 : printf("onze ");
							break;
						case 2 : printf("doze ");
							break;
						case 3 : printf("treze ");
							break;
						case 4 : printf("quatorze ");
							break;
						case 5 : printf("quize ");
							break;
						case 6 : printf("dezeseis ");
							break;
						case 7 : printf("dezesete ");
							break;
						case 8 : printf("dezoito ");
							break;
						case 9 : printf("dezenove ");
							break;					
					}
				break;
				
			case 2 : printf("vinte ");
				break;
			case 3 : printf("trinta ");
				break;
			case 4 : printf("quarenta ");
				break;
			case 5 : printf("cinquenta ");
				break;
			case 6 : printf("sessenta ");
				break;
			case 7 : printf("setetenta ");
				break;
			case 8 : printf("oitenta ");
				break;
			case 9 : printf("noventa ");
				break;
		}
		
		if(d > 1 && u !=0)
			printf(" e ");
		
		if(d != 1)
			switch(u){
			case 1 : printf("um ");
				break;
			case 2 : printf("dois ");
				break;
			case 3 : printf("trez ");
				break;
			case 4 : printf("quatro ");
				break;
			case 5 : printf("cinco ");
				break;
			case 6 : printf("seis ");
				break;
			case 7 : printf("sete ");
				break;
			case 8 : printf("oito ");
				break;
			case 9 : printf("nove ");
				break;
		}
	}
    }


}

int main() {
    int x, y, i;
    char continuar = 's';

    while (continuar == 's') {
        printf("Calculadora A\n\n");
        printf("Escolha a operação a ser realizada:\n 1- Soma\n 2- Subtração\n");
        scanf("%d", &i);

        switch (i) {
            case 1:
                system("cls || clear");
                soma();
                PorExtenso();
                break;
            case 2:
                system("cls || clear");
                subtracao();
                PorExtenso();
                break;
            default:
                printf("Opção inválida.\n");
        }

        printf("\nDeseja realizar outra operação? (s/n): ");
        scanf(" %c", &continuar);
    }

    return 0;
}
