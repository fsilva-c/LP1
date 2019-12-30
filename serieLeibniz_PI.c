#include <stdio.h>
#include <stdlib.h>

/* 
    serie de Leibniz:
    4/1 - 4/3 + 4/5 - 4/7 + 4/9... = ~ pi 
*/

//definindo o intervalo de operação do laço for
#define N 30000000

int main(){
    int sinal = -1;
    float valor = 0., somaPi = 0.;

    for(int iSoma = 1; iSoma <= N; iSoma += 2){
        valor = 4. / iSoma;

        //somando o valor da divisao de 4 pelo indiceSoma na variavel que guarda o valor de pi 
        somaPi += valor;

        //multiplicando o valor por -1 pra sequencia ficar + - + - + - + -...
        somaPi *= sinal;
    }

    printf("O valor aproximado de PI apos %d operacoes eh = %.8f\n", N/2, somaPi);

}//END main
