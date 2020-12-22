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

//função que guarda o valor,bloco, o código SF e a frequência
//criar uma struct para tal

typedef struct inf {
    int valor;
    int bloco;
    char *sf; //código SF
    int freq;
    struct inf *prox;
} *Inf;

//cria uma lista nova com os valores das freq de cada bloco
int *freqsbloco (char freq[], int ind) { //indíce do bloco (número de @-1 a percorrer após os 4 primeiros)
    int a = 4 + ind - 1; //número de @ a percorrer (4 iniciais + ind - 1)
    int i = 0; //percorrer os blocos
    int j; //percorrer as frequências dos símbolos de cada bloco
    int *l; 
    int n; //nº de caracteres da frequência

    while (a>0) { //serve para avançar com o array até ao sítio onde começa o bloco 
        if (freq[i]=='@') {
            a--;
            i++;
        }
        else i++;
    }

    for ( ; freq[i]!= '@'; i+=n) { //percorre o bloco
        n = 0;
        for (j=i; freq[j]!=';'; j++) n++; //percorre cada frequência
        strcat(l, valor(freq,j,n));
        }
        return l; 
}

//retira o valor da frequência e transforma-o num inteiro
int valor (char freq[], int i, int n) {
    char *str;

    strncpy (str, &freq[i],n);
    int x = atoi(str);

    return x;    
} 

char *calcular_codigos_SF (char freq[]) {
    char *codes;
    int i = 0;
    int j;
    int end = strlen(freq)-1;
    int div;
    int divAnt;

    for (i=0; ... ; i++) {
        div = calcular_melhor_divisao(freq,i,end);
        for (j=i; j<=div; j++) strcat(codes,'0');
        for (j=div+1; j<=end; j++) strcat(codes,'1');
        j=i; //(?)
        divAnt = div;

        while (j!=divAnt) { //ou div?
            if (divAnt > div) { //>= (?)
                divAnt = div; //guarda a divisão anterior
                div = calcular_melhor_divisao(freq,j,div);
            }
            else divAnt = end;
            int k;
            for (k=j; k<=div; k++) strcat(codes,'0');
            for (k=div+1; k<=divAnt; k++) strcat(codes,'1');
            // assim j vai ser sempre !=div ?? v
            div = calcular_melhor_divisao(freq,divAnt+1,end); //(?)
            j = divAnt+1;
            //colocar isto no início fora do ciclo ? e fazer as devidas alterações (??)
        }
        div = calcular_melhor_divisao(freq,divAnt+1,end);
        for(j= divAnt+1; j<=div; j++) strcat(codes,'0');
        for (j=div+1; j<=end; j++) strcat(codes,'1');





    }

//função para ordenar as probabilidades (decrescente)
 ordenaP(int a[],int N){
     int i,j;
     for(i=0;i<N-1;i++){
         for(j=i;j<N-1;j++){
             if(a[i]<a[j])
                 swap(a,i,j);
         }
     }
    
// função para dividir as probabilidades 
   void divideP(int a [],int N){
       int pt=sum a[i];
       int i,meio ,arr b,tmp;
       meio=length N/2;
       for(i=0;i<N-1;i++){
           if(a[i]>=0,5 && pt=1){ 
               tmp=a[i];
               removeelem(a,i,N);
           b[0]=tmp;
           }
       else {
           //fazer uma função para calcular a melhor divisão das frequencias 
}

// calcular a melhor divisao das frequencias 
    void melhorDiv(int a[],int N){
        int i;
        int arr b;
        int meio=length N/2;
        for(i=0;i<N-1;i++){
            if(sum a[i..meio]==sum a[meio+1..N]){
                while(i<=meio){
                    b=insert(a,i); //acho que ha uma função c este nome caso n haja faço a 
                } //falta acabar 
                
            
           
int main () {
    int k;
    char s[] = "@R@2@57444@1322;335;";
    k = valor(s,11,4);
    printf ("Resultado: %i\n", k);

    return 0;
}
