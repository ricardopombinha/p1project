#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "funcaoLerAuxiliar.h"

// README/README
// README/README
// README/README
//Estas sao as versões simplificadas de ler inteiros/floats/strings
//depois quando sobermos utilizarmos as outras funções temos de alterar
int lerInteiro(int minimo, int maximo)
{
    int numero, controlo;
    do
    {
        controlo = scanf ("%d", &numero);  // scanf devolve quantidade de valores vàlidos obtidos
        limpaBufferStdin();     //limpa todos os caracteres do buffer stdin (nomeadamente o \n)

        if (controlo == 0)
        {
            printf("Devera inserir um numero inteiro: ");
        }
        else
        {

            if(numero<minimo || numero>maximo)
            {
                printf("Numero invalido. Insira novamente: ");
            }

        }
    }
    while(numero<minimo || numero>maximo || controlo ==0);

    return numero;
}

float lerFloat(float minimo, float maximo)
{
    float numero;
    int controlo;
    do
    {
        controlo = scanf ("%f", &numero);  // scanf devolve quantidade de valores vàlidos obtidos
        limpaBufferStdin();

        if (controlo == 0)
        {
            printf("Devera inserir um numero decimal (float) \n");
        }
        else
        {

            if(numero<minimo || numero>maximo)
            {
                printf("Numero invalido. Insira novamente:\n");
            }

        }
    }
    while(numero<minimo || numero>maximo || controlo ==0);

    return numero;
}

void lerString(char vetorCaracteres[], int maximoCaracteres)
{
    int tamanhoString;

    do 			// Repete leitura caso sejam obtidas strings vazias
    {

        fgets(vetorCaracteres, maximoCaracteres, stdin);

        tamanhoString = strlen(vetorCaracteres);

        if (tamanhoString == 1)
        {
            printf("Nao foram introduzidos caracteres!!! . apenas carregou no ENTER \n\n");  // apenas faz sentido limpar buffer se a ficarem caracteres
        }

    }
    while (tamanhoString == 1);

    if(vetorCaracteres[tamanhoString-1] != '\n')  // ficaram caracteres no buffer....
    {
        limpaBufferStdin();  // apenas faz sentido limpar buffer se a ficarem caracteres
    }
    else
    {
        vetorCaracteres[tamanhoString-1] = '\0'; 	//Elimina o \n da string armazenada em vetor
    }

}

void limpaBufferStdin(void)
{
    char chr;
    do
    {
        chr = getchar();
    }
    while (chr != '\n' && chr != EOF);
}

//READ ME
//READ ME
//READ ME
//READ ME
void lerData(tipoData *data)
{
    //o ano é bissexto quanto o ano%==0 ou (o ano%4 == 0 e o ano%100 != 0)
    //feveiro é com 29 dias se for bissexto
    //mes com 30 dias é abril junho setembro e novembro)
    //o resto é com 31 dias
    int max_dias;
    // indica ano
    printf("Insira a data:");
    printf("\tAno: ");
    data->ano = lerInteiro(MENOR_ANO,MAIOR_ANO);
    // indica mes
    printf("\tMes: ");
    data->mes = lerInteiro(1,12);

    //ve o maximo de dias que pode ter em cada mes
    switch(data->mes)
    {
    case 2:
        if (data->ano % 400 == 0 || (data->ano % 4 == 0 && data->ano % 100 != 0))
        {
            max_dias = 29;
        }
        else
        {
            max_dias = 28;
        }

        break;
    case 4:
    case 6:
    case 9:
    case 11:
        max_dias = 30;
        break;
    default:
        max_dias = 31;
    }

    //le o dia
    printf("\tDia: ");
    data->dia = lerInteiro(1,max_dias);
}

int difenreca_Datas(tipoData data_I, tipoData data_F)
{
    // Variavel para guardar a duraçao
    int duracao = 0;
    //So se sai do while quando a data_I for igual a data_F
    while(!(data_F.dia == data_I.dia && data_F.mes == data_I.mes && data_F.ano == data_I.ano))
    {
        //Se a data_I é dia 31 dos meses 1, 3 , 5, 7, 8, 10, 12
        if(data_I.dia == 31 && (data_I.mes == 1 || data_I.mes == 3 || data_I.mes == 5 || data_I.mes == 7 || data_I.mes == 8 || data_I.mes == 10 || data_I.mes == 12))
        {
            //Passa dia da data_I a 1
            data_I.dia = 1;
            //Se o mes da data_I é 12, desta forma irá colocá-lo a mes=1 e incrementar um ano
            if (data_I.mes == 12)
            {
                data_I.mes = 1;
                data_I.ano++;
            }
            else
            {
                //Caso contrário apenas incrementa um mês
                data_I.mes++;
            }
        }
        else
        {
            //Se a data_I é dia 30 dos meses 4, 6 , 9, 11
            if (data_I.dia == 30 &&(data_I.mes == 4 || data_I.mes == 6 || data_I.mes == 9 || data_I.mes == 11))
            {
                //Passa dia da data_I a 1 e incrementa um mes
                data_I.dia = 1;
                data_I.mes++;
            }
            else
            {
                //Se o ano é  bissexto  e se está no dia 29 do mes 2
                if ((data_I.ano % 400 == 0 || (data_I.ano % 4 == 0 && data_I.ano % 100 != 0)) && data_I.dia == 29 && data_I.mes == 2)
                {
                    //Passa dia da data_I a 1 e incrementa um mes
                    data_I.dia = 1;
                    data_I.mes++;
                }
                else
                {
                    //Se o ano nao é bissexto  e se está no dia 28 do mes 2
                    if(!((data_I.ano % 400 == 0 || (data_I.ano % 4 == 0 && data_I.ano % 100 != 0))) && data_I.dia == 28 && data_I.mes == 2)
                    {
                        //Passa dia da data_I a 1 e incrementa um mes
                        data_I.dia = 1;
                        data_I.mes++;
                    }
                    else
                    {
                        //caso nada disto antes aconteça, apenas incrementa um dia
                        data_I.dia++;
                    }
                }
            }
        }
        //incrementa duracao
        duracao++;
    }
    return duracao;
}


