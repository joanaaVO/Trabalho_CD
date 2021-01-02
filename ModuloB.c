#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 1000

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

//cria uma lista nova com os valores das freq de cada bloco
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
    l[k] = '\0';
}

//remove as frequências iguais a 0
void removeFreq (long ord[]) {
    int i;
    int j = 0;

    for(i=0; ord[i]!='\0'; i++) {
        if (ord[i] != 0) ord[j++] = ord[i];
    }
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
        if (dif<mindif) { 
            div = div+1;
            mindif = dif;
        }
        else dif = mindif+1; 
    } while (dif == mindif); //até (dif!=mindif)
    return div-1; //calcular_melhor_divisão=div-1
} 

int calcular_codigos_SF(long ord[],char codes[],int start,int end,int divisoes[],int k) {
    int div;
    int i;
    char zero = '0';
    char one = '1';
    if (start!=end) {
        div = calcular_melhor_divisao(ord,start,end);
        printf("k antes: %i\n", k);
        divisoes[k++] = div;
        printf("k depois: %i\n", k);
        printf("div[k]: %i\n", divisoes[k-1]);
        printf("div: %i\n", div);
        for (i=0; i<=div-start; i++) strncat (codes, &zero, 1); //add_bit_to_code('0',codes,start,div);
        for (i=0; i<=end-(div+1); i++) strncat(codes, &one, 1); //add_bit_to_code('1',codes,div+1,end);
        printf("%s\n", codes);
        k = calcular_codigos_SF(ord,codes,start,div,divisoes,k);
        k = calcular_codigos_SF(ord,codes,div+1,end,divisoes,k);
    }
    return k;
}

void codigo_simbolo (char cod[], int divs[], char codsimb[MAX][MAX]) {
    int i = 0; //percorre cod
    int z; //percorre cod para contar os zeros
    int j = 0; //percorre divs
    int k = 0; //percorrer codsimb
    int zeros;
    char c;

    for (int l=0; l<MAX; l++) memset(codsimb[l], '\0', sizeof(codsimb[l])); //limpa a memória

    while (cod[i]!='\0') {
        zeros = 0;
        for (z=i; cod[z]!= '1'; z++) zeros++;
        k=divs[j]-zeros+1;
        while (cod[i]!='1') { //adicionar os 0s
            c = cod[i]; 
            strncat(codsimb[k],&c,1);
            k++;
            i++;
        }
        while (cod[i]!='0' && cod[i]!='\0') { //adicionar os 1s
            c = cod[i];
            strncat(codsimb[k],&c,1);
            k++;
            i++;
        }
        j++; //avança com o array das divs
    }
    //for(int n=0; n<8; n++) printf("%s\n",codsimb[n]);
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


int maior (long freq[]) {
    int maior = 0;
    int ind = 0;
    int i;

    for (i=0; freq[i]!='\0'; i++) {
        if (freq[i]>maior) {
            maior = freq[i];
            ind = i;
        }
    }
    return ind;
}

void atribiu_cod_simb (long freq[],char codesimb[MAX][MAX], char novo[MAX][MAX]) { //recebe o array com as freqs não ordenadas
    int i = 0; //percorre codesimb
    int j = 0; //percorre codesimb
    int indMaior;

    for(i=0; codesimb[i][0]!='\0'; i++) {
        indMaior = maior(freq);
        strcpy(novo[indMaior],codesimb[i]);

        for(int n=indMaior; freq[n]!='\0'; n++) freq[n] = freq[n+1];
    }
}

//função principal que retorna o conteúdo do ficheiro .cod
char *cod (char *freq) {
    char *final; //string que vai ser retornada
    int k; //índice que percorre a lista final
    int i = 0;
    int b = 1; //indicador do bloco
    int m;
    long bloco = 1;
    long l[257];
    long r[257];
    char *t;
    char a = '@';
    char zero = '0';
    char p = ';';
    char *codes;
    char *ptr;
    char codesimb[MAX][MAX];
    char novo [MAX][MAX];
    int divs[MAX];

    while (i <= 4) final[k++] = freq[i++];

    //ATENÇÃO AOS CASOS QUE SÃO IGUAIS (;;) ??
    while (bloco <= strtol(freq+3, &ptr, 10)) { //repete o processo para todos os blocos
        tamanhoB (freq,bloco,t);
        strcat (final, t); //copiar o tam do bloco diretamente do ficheiro de entrada
        strncat (final,&a,1); //coloca um @ a seguir do tamanho do bloco
        freqsbloco (freq,bloco,l);
        for (m=0; l[m]!='\0'; m++) r[m] = l[m];
        r[m] = '\0';
        ordena(l,256); //número de símbolos é sempre 256
        removeFreq (l); //remove as frequências iguais a 0
        calcular_codigos_SF(l,codes,0,255,divs,0);
        codigo_simbolo(codes,divs,codesimb);
        atribiu_cod_simb(r,codesimb,novo);
        for (int n=0; novo[n][0]!='\0'; n++) {
            if (r[n] != 0) { //se não for um símbolo com freq = 0
                strcat(final,novo[n]);
                strncat(final,&p,1);       
            }
            else strncat(final,&p,1);
        }
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
    char *simb;
    char *s = "@R@2@57444@1322;;335;;456@1620@19;21;6@0";
    int div;
    int cont;
    int divs [MAX];
    //char codsimb[MAX][MAX];

    //removeFreq(ex);
    //printf("%ld",ex[8]);
    calcular_codigos_SF(ex,t,0,7,divs,0);
    //codigo_simbolo(t,divs,codsimb);
    //strcpy(codsimb[0], "hello");
    //printf("%s",codsimb[0]);
    //printf("%i\n", cont);
    //divs[cont] = '\0';
    //agrupar(codigos,divs,codsimb,8);
    //printf("%i\n", divs[4]);
    //agrupar(t,ex,simb,0,7);

    //tamanhoB(s,2,t);
    //printf("%s\n",t);

    //div = calcular_melhor_divisao(l,0,3);
    //printf("Div: %i\n", div); 
  
    // print string 
    //printf("Appended String: %s\n", str); 

    //freqsbloco(s,1,l);
    //int loop;   
    //for(loop = 0; ex[loop] != '\0'; loop++) printf("%ld ", ex[loop]);

    return 0;
}