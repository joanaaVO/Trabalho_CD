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
        n = 0;
        if (k != 0 && (freq[i+1] == ';' || freq[i+1] == '@')) { //caso a frequência do valor em que nos encontramos seja igual à anterior (CASO ;;)
            l[k++] = l[k-1]; 
            n = 1; //anda 1 para a frente  
        }
        else {
            if (k != 0) i++; //se já não estiver na 1ºfrequência
            for (j=i; freq[j]!=';' && freq[j]!='@'; j++) n++; //percorre cada frequência
            l[k++] = strtol (freq+i,&ptr,10);
        }
    }
}

//remove as frequências iguais a 0
void removeFreq (long ord[]) {
    int i;
    int j = 0;

    for(i=0; ord[i]!='\0'; i++) {
        if (ord[i] != 0) ord[j++] = ord[i];
    }
    ord[j] = '\0';
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
        divisoes[k++] = div;
        for (i=0; i<=div-start; i++) strncat (codes, &zero, 1); //add_bit_to_code('0',codes,start,div);
        for (i=0; i<=end-(div+1); i++) strncat(codes, &one, 1); //add_bit_to_code('1',codes,div+1,end);
        k = calcular_codigos_SF(ord,codes,start,div,divisoes,k);
        k = calcular_codigos_SF(ord,codes,div+1,end,divisoes,k);
    }
    return k;
}

//calcula os códigos de cada símbolo
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
}

//coloca numa string 'tam' o tamanho de um dado bloco
void *tamanhoB (char *freq, int ind, char tam[]) {
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

//calcula a maior frequência
int maior (long freq[]) {
    long maior = 0;
    int ind = 0;
    int i;
    int j;

    for (i=0; i<256; i++) {
        if (freq[i]>maior) { 
            maior = freq[i];
            ind = i; 
        } 
    }
    return ind;
}

//atribui cada código ao respetivo símbolo
void atribiu_cod_simb (long freq[],char codesimb[MAX][MAX], char novo[MAX][MAX]) { //recebe o array com as freqs não ordenadas
    long temp[257];
    int k;
    for(k=0; k<256; k++) temp[k] = freq[k]; //guarda temporariamente o conteúdo de freq
    temp[k] = '\0';
    int i = 0; //percorre codesimb
    int indMaior = 0;

    for (int l=0; l<MAX; l++) memset(novo[l], '\0', sizeof(novo[l])); //limpa a memória

    for(i=0; codesimb[i][0]!='\0'; i++) {
        indMaior = maior(freq);
        if (freq[indMaior] > 0) {
            strcpy(novo[indMaior],codesimb[i]);
            freq[indMaior] = -1;
        }
    }
    for(k=0; k<256;k++) freq[k] = temp[k]; //devolve o conteúdo original a freq
    freq[k] = '\0';
}

//função principal que retorna o conteúdo do ficheiro .cod
void cod (char freq[], char final[]) {
    int k; //índice que percorre a lista final
    int i = 0;
    int b = 1; //indicador do bloco
    int m;
    int tam;
    int arrobas = 3;
    int bloco = 1;
    long l[257];
    long r[257];
    char t[30];
    char a = '@';
    char zero = '0';
    char p = ';';
    char codes[10000];
    char *ptr;
    int divs[MAX];
    char codesimb[MAX][MAX];
    char novo [MAX][MAX];

    memset(final, '\0', strlen(final)); //limpa a memória

    while (arrobas > 0) {
        if (freq[i] == '@') arrobas--;
        char c;
        c = freq[i];
        strncat(final,&c,1);
        i++;
    }

    //i=0; ??
    //ATENÇÃO AOS CASOS QUE SÃO IGUAIS (;;) ??
    while (bloco <= strtol(freq+3, &ptr, 10)) { //repete o processo para todos os blocos
        memset(codes,'\0',sizeof(codes));
        memset(l,'\0',sizeof(l));
        tamanhoB (freq,bloco,t);
        strcat (final, t); //copiar o tam do bloco diretamente do ficheiro de entrada
        strncat (final,&a,1); //coloca um @ a seguir do tamanho do bloco
        freqsbloco (freq,bloco,l);
        for (m=0; m<256; m++) r[m] = l[m];
        r[m] = '\0';
        ordena(l,256); //número de símbolos é sempre 256
        removeFreq (l); //remove as frequências iguais a 0
        for (tam=0; l[tam]!='\0'; tam++);
        calcular_codigos_SF(l,codes,0,tam-1,divs,0);
        codigo_simbolo(codes,divs,codesimb);
        atribiu_cod_simb(r,codesimb,novo);
        for (int n=0; n<256; n++) {
            if (n == 255) { //s estiver no último elemento
                if (r[n] != 0) strcat(final,novo[n]);
            }
            else {
                if (r[n] != 0) { //se não for um símbolo com freq = 0
                    strcat(final,novo[n]);
                    strncat(final,&p,1); 
                }
                else strncat(final,&p,1);
            }
        }
        strncat (final,&a,1);
        bloco++;  
    }
    strncat(final,&zero,1); //adiciona o caracter "0" no fim
}

int main (int argc, char **argv) {
    FILE *fp;
    FILE *novo;
    int bloco = 1;
    int p = 0; 
    int j = 0;
    char c = '/';
    char filename[MAX];
    char newfile[MAX];
    char tam[MAX];
    char tam_total[MAX];
    char saida[10000];
    char conteudo[10000];
    char *ptr;
    clock_t start, end, total;

    memset(tam, '\0', strlen(tam));
    memset(tam_total, '\0', strlen(tam_total));

    time_t tempo = time(NULL);
    char * data = ctime(&tempo);
    data[strlen(data)-1] = '\0';

    strcpy(filename,argv[1]);

    start = clock();

    fp = fopen (filename, "r"); //abre o ficheiro .freq em modo de leitura
    fread(conteudo,sizeof(char), sizeof(filename),fp);

    cod(conteudo,saida); //executa o módulo

    long n_blocks = strtol(conteudo+3, &ptr, 10);
    while (bloco <= n_blocks) {
        if (bloco < n_blocks) {
            tamanhoB(conteudo, bloco, tam);
            strcat(tam_total,tam);
            strncat(tam_total,&c,1);
        }
        else {
            tamanhoB(conteudo, bloco, tam);
            strcat(tam_total,tam);
        }
        bloco++;
    }

    for (int n=0; filename[n]!='\0'; n++) {
        if (filename[n] == '.') p++;
    }

    for (int i=0; filename[i]!='\0' && p>0; i++) {
        if (filename[i] == '.') p--;
        newfile[j++] = filename[i];
        }
        newfile[j] = '\0';

    novo = fopen(strcat(newfile,"cod"), "w"); //cria um novo ficheiro (.cod)
    fputs(saida,novo); //coloca no novo ficheiro a string resultante da execução do módulo

    end = clock();
    total = 1000*(double)(end - start) / (double)CLOCKS_PER_SEC;

    printf("Filipa Rebelo, a90234, Joana Oliveira, a87956, MIEI-CD, %s\n", data);
    printf("Modulo: t (calculo dos codigos dos simbolos)\n");
    printf("Numero de blocos: %ld\n", strtol(conteudo+3,&ptr,10));
    printf("Tamanho dos blocos analisados no ficheiro de simbolos: %s bytes\n", tam_total);
    printf("Tempo de execucao do modulo (milissegundos): %lu\n", total);
    printf("Ficheiro gerado: %s", newfile); 

    fclose(fp);
    fclose(novo);

    return 0;
}