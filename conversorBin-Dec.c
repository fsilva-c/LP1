/* 
 * File:   main.c
 * Author: FILIPE-00
 *
 * Created on 7 de Maio de 2019, 20:47
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int conversorBinDec (char arrayBin[43]);

int main(int argc, char** argv) {

    char arrayBin[43];
    int valorDec;

    printf("Informe um numero na base 2 (BINARIO EX.: 101001): ");
    scanf(" %s", arrayBin);
    
    printf("\n");
    conversorBinDec(arrayBin);
    
    valorDec = conversorBinDec(arrayBin);
    printf("O numero %s convertido para decimal eh %d", arrayBin, valorDec);
    printf("\n");
    
}

int conversorBinDec (char arrayBin[43]){
    
    int valorConvertido = 0;
    int potenciaAux = 1;
    int numerosBits;
    numerosBits = strlen(arrayBin);
        
    for(int i=numerosBits-1; i>=0; i--){
       
        if(arrayBin[i] == '1'){
            
            valorConvertido += potenciaAux;
              
        }
        
        potenciaAux *= 2;
        
    }//fim for
    
    return valorConvertido;
    
}