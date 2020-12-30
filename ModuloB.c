#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//troca o conteúdo de dois elementos do array
void swap (long v[], int i, int j) {
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

//cria uma lista nova com os valores das freq de cada bloco e ordena-os por ordem decrescente
void freqsbloco (char *freq, int ind, long l[]) { //indíce do bloco (número de @-1 a percorrer após os 4 primeiros)
    int a = (ind + 1)*2; //número de @ a percorrer 
    int i = 0; //percorrer os blocos
    int j; //percorrer as frequências dos símbolos de cada bloco
    int k = 0; //índice para percorrer a lista a retornar
    int n; //nº de caracteres da frequência
    char *ptr;

    while (a>0) { //serve para avançar com o array até ao sítio onde começam os blocos 
        if (freq[i]=='@') {
            a--;
            i++;
        }
        else i++;
    }
 
    for ( ; freq[i]!= '@'; i+=n) { //percorre o bloco
        if (k != 0 && freq[i+1] != ';') i++; //se já não estiver na 1ºfrequência e se não for um caso ;; avança +1 para ficar no sítio onde começa a frequência
        n = 0;
        if (freq[i+1] == ';') {
            l[k++] = l[k-1]; //caso a frequência do valor em que nos encontramos seja igual à anterior (CASO ;;)
            n = 1; //anda 1 para a frente  
        }
        else {
            for (j=i; freq[j]!=';' && freq[j]!='@'; j++) n++; //percorre cada frequência
            l[k++] = strtol (freq+i,&ptr,10);
        }
    }
    ordena(l,256); //número de símbolos é sempre 256
}

//calcula a soma das frequências entre dois índices
long sum (long v[], int inicio, int fim) {
    int i;
    int soma=0;

    for (i=inicio; i<=fim; i++) soma+=v[i];

    return soma;
}

int calcular_melhor_divisao (long ord[],int i,int j) {
    int div = i;
    long total,mindif,dif;
    total = mindif = dif = sum(ord,i,j);
    //printf("mindif:%ld ",mindif);
    long g1 = 0;
    do {
        g1 = g1 + ord[div]; //soma acumulada dos sucessivos elementos
        dif = abs(2*g1-total);
        //printf("dif:%ld ",dif);
        if (dif<mindif) { 
            div = div+1;
            mindif = dif;
        }
        else dif = mindif+1; 
        //printf("dif2:%ld ",dif);
        //printf("mindif2:%ld ",mindif);
        //printf("div:%i\n",div);
    } while (dif == mindif); //até (dif!=mindif)
    return div-1; //calcular_melhor_divisão=div-1
} 

void calcular_codigos_SF(long ord[],char codes[],int start,int end) {
    int div;
    int i;
    char zero = '0';
    char one = '1';
    if (start!=end) {
        div = calcular_melhor_divisao(ord,start,end);
        printf("div: %i\n", div);
        for (i=0; i<=div-start; i++) strncat (codes, &zero, 1); //add_bit_to_code('0',codes,start,div);
        for (i=0; i<=end-(div+1); i++) strncat(codes, &one, 1); //add_bit_to_code('1',codes,div+1,end);
        printf("%s\n", codes);
        calcular_codigos_SF(ord,codes,start,div);
        calcular_codigos_SF(ord,codes,div+1,end);
    }
}

//coloca numa string 'tam' o tamanho de um dado bloco
void *tamanhoB (char *freq, int ind, char *tam) {
    int a = 2 * ind + 1; //num de @ que terá de passar
    int i = 0;
    int k = 0;
    
    while (a>0) { //percorre o array até ao sítio onde se encontra o tamanho do bloco
        if (freq[i]=='@') {
            a--;
            i++;
        }
        else i++;
    }

    while (freq[i]!='@') tam[k++] = freq[i++];

    tam[k] = '\0';
}

//função principal que retorna o conteúdo do ficheiro .cod
char *cod (char *freq) {
    char *final; //string que vai ser retornada
    int k; //índice que percorre a lista final
    int i = 0;
    int b = 1; //indicador do bloco
    long bloco = 1;
    long l[257];
    char *t;
    char a = '@';
    char zero = '0';
    char *codes;
    char *ptr;

    while (i <= 4) final[k++] = freq[i++];

    //ALGURES AQUI COLOCAR UMA FUNÇÃO PARA ADICONAR ; ENTRE OS CÓDIGOS E TER ATENÇÃO AOS CASOS QUE SÃO IGUAIS (;;) ??
    //CASO A FREQUÊNCIA DOS SIMBOLOS SEJA 0 APARECE ;; NO FICHEIRO DE SAÍDA
    while (bloco <= strtol(freq+3, &ptr, 10)) { //repete o processo para todos os blocos
        tamanhoB(freq,bloco,t);
        strcat (final, t); //copiar o tam do bloco diretamente do ficheiro de entrada
        strncat (final,&a,1); //coloca um @ a seguir do tamanho do bloco
        freqsbloco (freq,bloco,l);
        calcular_codigos_SF(l,codes,0,255); //255?
        strcat (final, codes); //não vai ser bem a codes
        strncat (final,&a,1); //coloca um @ no fim do bloco
        bloco++;  
    }
    strncat(final,&zero,1); //adiciona o caracter "0" no fim
    //último caracter '\0' ?
}

/*int main () {
    FILE *fp;
    FILE *novo;
    char *command;
    char *filename;
    int i;
    int j = 0;
    char *saida;
    char *conteudo;
    char *ptr;
    clock_t start, end, total;

    start = clock();

    scanf ("%s", command); 

    for (i=0; command[i]!=' '; i++); //percorre a palavra 'shafa'
    i++; //avança mais 1 para ficar no sítio onde começa o nome do ficheiro
    for( ; command[i]!=' '; i++) filename[j++] = command[i]; //retira o nome do ficheiro
    filename[j] = '\0';
    
    fp = fopen (filename, "r"); //abre o ficheiro .freq em modo de leitura (rb?)
    fgets(conteudo, strlen(conteudo), filename); //retira a string que lá se encontra

    saida = cod(conteudo); //executa o módulo
    novo = fopen(strcat(filename,".cod"), "w"); //cria um novo ficheiro (.cod) (wb?)
    fprintf(novo, saida); //coloca no novo ficheiro a string resultante da execução do módulo

    end = clock();
    total = (long int) ((end-start) / CLOCKS_PER_SEC) * 1000);

    printf("Filipa Rebelo, a90234, Joana Oliveira, a87956, MIEI-CD, DATA\n");
    printf("Módulo: t (cálculo dos códigos dos símbolos)\n");
    printf("Número de blocos: \n", strtol(conteudo+3,&ptr,10));
    printf("Tamanho dos blocos analisados no ficheiro de símbolos: %s bytes\n");
    printf("Tempo de execução do módulo (milissegundos): %lu\n", total);
    printf("Ficheiro gerado: %s", novo); //novo?

    fclose(fp);
    fclose(novo);

    return 0;
}
*/
                      
int main () {
    long k;
    //long l[8] = {1/2,1/12,1/12,1/12,1/16,1/16,1/16,1/16};
    long l[4] = {5,3,1,1};
    long ex[8] = {24,4,4,4,3,3,3,3};
    char *t;
    char *s = "@R@2@57444@1322;;335;;456@1620@19;21;6@0";
    int div;

    calcular_codigos_SF(ex,t,0,7);

    //tamanhoB(s,2,t);
    printf("%s\n",t);

    //div = calcular_melhor_divisao(l,0,3);
    //printf("Div: %i\n", div); 
  
    // print string 
    //printf("Appended String: %s\n", str); 

    /*freqsbloco(s,1,l);
    int loop;   
    for(loop = 0; loop < 5; loop++) printf("%ld ", l[loop]);
    */

    return 0;
}