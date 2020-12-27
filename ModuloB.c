#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//ATENÇÃO AOS CASOS EM QUE O VALOR É REPETIDO (;;)

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

//retira o valor da frequência e transforma-o num long (inteiro)
long valor (char *freq, int i, int n) {
    char *str;
    char *ptr;
    long x;

    strncpy (str, freq+i,n);
    x = strtol(str, &ptr, 10);

    return x;    
} 

//cria uma lista nova com os valores das freq de cada bloco
long *freqsbloco (char *freq, int ind) { //indíce do bloco (número de @-1 a percorrer após os 4 primeiros)
    int a = (ind + 1)*2; //número de @ a percorrer 
    int i = 0; //percorrer os blocos
    int j; //percorrer as frequências dos símbolos de cada bloco
    long *l; 
    int k=0; //índice para percorrer a lista a retornar
    int n; //nº de caracteres da frequência

    while (a>0) { //serve para avançar com o array até ao sítio onde começam os blocos 
        if (freq[i]=='@') {
            a--;
            i++;
        }
        else i++;
    }
 
    for ( ; freq[i]!= '@'; i+=n) { //percorre o bloco
        n = 0;
        if (freq[i+1] == ';') l[k++] = l[k-1]; //caso a frequência do valor em que nos encontramos seja igual à anterior (CASO ;;)
        else {
            for (j=i; freq[j]!=';'; j++) n++; //percorre cada frequência
            l[k++] = valor(freq,i,n);  
        }
    }
    return l;
}

/*char *calcular_codigos_SF (char freq[]) {
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
*/

//troca o conteúdo de dois elementos do array
void swap (long v[], int i, int j){
	int temp = v[i];
	v[i] = v[j];
    v[j] = temp;
}

//ordena as probabilidades por ordem decrescente
void ordena (long a[], int N) {
     int i,j;

     for(i=0; i<N-1; i++) {
         for(j=i+1; j<N; j++) {
             if(a[i] < a[j]) swap(a,i,j);
         }
     }
}
    
// função para dividir as probabilidades 
void divideP(int a [], int N){
       int pt = sum (a[i]);
       int i,meio ,arr b,tmp;
       meio = length (N/2);
       for(i=0; i<N-1; i++){
           if(a[i] >= 0.5 && pt == 1){ 
               tmp = a[i];
               removeelem(a,i,N);
           b[0]=tmp;
           }
       else {
           //fazer uma função para calcular a melhor divisão das frequencias 
}


// calcular a melhor divisao das frequencias 
    void melhorDiv(int a[],int N){
        int i;
        int b;
        int dif,melhordif;
        int soma1,soma2;
        int meio= length (N/2);
        for(i=0;i<N-1;i++){
            if(sum (a[i..meio]) ==sum (a[meio+1..N])){
                while(i<=meio){
                    b=insert(a,i); //acho que ha uma função c este nome caso n haja faço a 
                }
            }
            else {
            	dif=sum(a[i..N]);
              if(a[i]<sum(a[i+1..N])){
              	soma1=a[i];
              	soma2=sum(a[i+1..N]);
              	melhordif=abs(soma1-soma2);
              if(dif<melhordif){
                 melhordif=dif;
                 soma1=a[i]+a[i+1];
                 soma2= sum(a[i+2]);
              }
              }
                
            }
        }
}


//retorna uma string que contém o tamanho de um dado bloco
char *tamanhoB (char *freq, int ind) {
    int a = 2 * ind + 1; //num de @ que terá de passar
    int i = 0;
    int k = 0;
    char *tam;
    
    while (a>0) { //percorre o array até ao sítio onde se encontra o tamanho do bloco
        if (freq[i]=='@') {
            a--;
            i++;
        }
        else i++;
    }

    while (freq[i]!='@') tam[k++] = freq[i];

    return tam;
}

//função principal que retorna o conteúdo do ficheiro .cod
char *cod (char *freq) {
    char *final; //string que vai ser retornada
    int i = 0;
    int b = 1; //indicador do bloco
    int blocos = freq[3];

    while (blocos > 0) {
        strcat (final)    
    }



}

/*int main () {
    FILE *fp;
    char *command;
    char *filename;
    char *c = "shafa ";

    printf ("Nome do ficheiro: ");
    scanf ("%s", str); 

    fp = fopen (filename, "r");

    c = c + filename + " -m t";

    strcpy(command, "shafa" + "-m t");
    system(command);

    return 0;
}
*/
            
           
int main () {
    long k;
    char *l;
    char *s = "@R@2@57444@1322;335;456@1620@19;21;6@0";

    //char *ptr;
    //strncpy (l, s+11, 4);
    //k = strtol(l, &ptr, 10); 

    //strncpy(l,s+11,4);
    //printf ("%s\n", l);
    k = valor(s,11,4);
    //l = freqsbloco(s,1);
    //printf ("%i\n", l[0]);
    //int loop;
    
    //for(loop = 0; loop < sizeof(l); loop++) printf("%i\n", l[loop]);

    printf ("Resultado:%ld\n", k);

    return 0;
}
