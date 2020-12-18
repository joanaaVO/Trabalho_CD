#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//ordenar por ordem decrescente os índices de cada bloco 
//dois ciclos : para cada bloco e dentro de cada bloco
//numero de blocos = freq[3];
//frequencia do 1ºsimbolo do 1º bloco aparece após 4 @
//1ºbloco só acaba quando encontrar o próximo @
//nesse caso avanca para o proximo bloco
//1ºciclo(para o 1ºbloco) é diferente dos restantes devido ao inicio do array

char *ordena (char freq[]) {
    int a = 4; //número de @
    int i = 0; //percorrer os blocos
    int j; //percorrer as frequências dos símbolos de cada bloco

    while (a>0) { //serve para avançar com o array até ao sítio onde começam as frequências (após o 4 @) 
        if (freq[i]=='@') {
            a--;
            i++;
        }
        else i++;
    }

    for ( ; freq[i]!='0'; i++) { //percorre o array todo
        for (j=i; freq[j]!='@'; j++) { //percorre cada bloco
            if (valor(freq,j) < valor )
        }
    }

    
}

//retira o valor da frequência e transforma-o num inteiro
int valor (char freq[], int ind) {
    int n = 0; //nº de carateres
    int i;
    char *str;

    for (i=ind; freq[i]!=';'; i++) n++;
    strncpy (str, &freq[i-n],n);
    int x = atoi(str);

    return x;    
} 

int main () {
    int k;
    char s[] = "@R@2@57444@1322;335;";
    k = valor(s,11);
    printf ("Resultado: %i\n", k);

    return 0;
}