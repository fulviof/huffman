/*
 * File:   main.cpp
 * Author: fulvio
 *
 * Created on 2 de Dezembro de 2017 18:56 until 3 de Dezembro de 2017 02:03
 */

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<Math.h>
#define TF 100

using namespace std;

struct no
{
    char info;
    no *esq;
    no *dir;
    int cod;
};
typedef struct no No;

struct tabela
{
    char info;
    double freq;
    int cod;
};
typedef struct tabela tabelaFreq;

void inicializaArvore(No **arvore)
{
    *arvore = (No*)malloc(sizeof(No));
    *arvore = NULL;
}

void inicializaTabela(tabelaFreq tabela[])
{
    int i;
    
    for(i = 0; i<TF; i++)
        tabela[i].freq = 0;
}

int buscaTabela(char letra, tabelaFreq tabela[], int TLT)
{
    int i=0;


    while(i<TLT)
    {
        if(tabela[i].info == letra)
            return i;
        else
            i++;
    }

    return -1;
}


void ordenaTab(tabelaFreq tabela[], int TL)//bulbassaurosort
{
    int a, qtde = TL;
    tabelaFreq aux;
    while (qtde>0)
    {
        for (a=0; a<qtde-1; a++)
          if (tabela[a].freq < tabela[a+1].freq)
            {   
                aux = tabela[a];
                tabela[a] = tabela[a+1];
                tabela[a+1] = aux;
            }
        qtde--;    
   }
}


int criaTabela(tabelaFreq tabela[], char frase[], int TL)
{
    int i, j, aux;
    int TLT = 0;

    for(i = 0; i<TL; i++)
    {
        for(j = 0; j<TL; j++)
        {
            if(frase[i] == frase[j])
            {
                aux = buscaTabela(frase[i], tabela, TLT);
                if(aux == -1)
                {
                    tabela[TLT].info = frase[i];
                    tabela[TLT].freq++;
                    //printf("letra: %c, freq: %d\n", tabela[TLT].info, tabela[TLT].freq);
                    TLT++;
                    
                }
                else
                {
                    tabela[aux].freq++;
                }
            }
        }
    }
    return  TLT;
    
}

void percorreOrdem(No *A)
{
    if (A == NULL)
        return;
    printf("%c", A->info);
    percorreOrdem(A->esq);
    percorreOrdem(A->dir);
}

No *criaNo(char info)
{
    No *novoNo = (No*) malloc(sizeof(No));
    novoNo->info = info;
    novoNo->dir = NULL;
    novoNo->esq = NULL;
    novoNo->cod = 0;
    
    return novoNo;
}

void geraArvore(No **arvore, tabelaFreq tabela[], int TL)
{
    int i, flag;
    No *aux = NULL;
    
    flag = 0;
    (*arvore) = criaNo('x');
    aux = *arvore;
    for(i = 0; i<TL; i++)
    {
    	
        if(i != TL-1)
        {          
            aux->esq = criaNo(tabela[i].info);
    		if( i!= TL-2)
				aux->dir = criaNo('x');
			aux = aux->dir;
			
        }
		else
		{
			aux = criaNo(tabela[i].info);
		}    
        //aux->esq = criaNo(tabela[i].info);
        
        //flag = !flag;
    }
}

void criaCod(No *arvore, char cod[], char frase[], int TL)
{
    No *aux = NULL;
    No *ant = NULL;
    int i;
    
    for(i = 0; i < TL; i++)
    {
        aux = arvore;
        ant = arvore;
        
        while(aux != NULL)
        {
            if(aux->esq->info == frase[i])
            {
                strcat(cod, "1");
                aux = NULL; 
            }                           
            else
            {
               strcat(cod, "0");
               aux = aux -> dir;
            }                    
        }
    }
}

int main(int argc, char** argv)
{
    No *Arvore;
    int i;
    int TLT = 0;
    tabelaFreq tabela[TF];
    char frase[TF], cod[TF];

    inicializaArvore(&Arvore);
    inicializaTabela(tabela);
    
    scanf("%[^\n]s", &frase);
    setbuf(stdin, NULL);//gets
    
    int TL = strlen(frase);
    printf("%d\n", TL);
    
    TLT = criaTabela(tabela, frase, TL);
    ordenaTab(tabela, TLT);
    
    for(i=0; i<TLT; i++)
        printf("letra: %c, freq: %df\n", tabela[i].info, sqrt(tabela[i].freq));
    
    geraArvore(&Arvore, tabela, TLT);
    criaCod(Arvore, cod, frase, TL);
    
    printf("\n\nCodificacao: %s\n", cod);
}
