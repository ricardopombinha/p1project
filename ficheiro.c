#include <stdio.h>
#include <stdlib.h>

#include "ficheiro.h"

void gravaFicheiroBinario(tipoPortatil vetorPortatil[MAX_PORTATIL], tipoRequisicao
                          *vetorRequisicao, int quant_Portatil, int quant_Requisicao, int quant_Requisicao_Ativas)
{
    FILE *ficheiro;
    // Abre ficheiro
    ficheiro = fopen("InfoPortatil.dat","wb");
    // Verifica se temos espaço para o ficheiro
    if (ficheiro == NULL)
    {
        printf("Erro ao abrir ao ficheiro");
    }
    else
    {

        // Grava primeiro o numero de portateis
        fwrite(&quant_Portatil, sizeof(int), 1, ficheiro);
        // Grava depois o vetor dos portateis
        fwrite(vetorPortatil, sizeof(tipoPortatil), quant_Portatil, ficheiro);
        // Grava o numero de requisições
        fwrite(&quant_Requisicao, sizeof(int), 1, ficheiro);
        // E por ultimo grava o o vetor de requisições
        fwrite(vetorRequisicao, sizeof(tipoRequisicao), quant_Requisicao, ficheiro);
        // Grava as quantidades de requisicoes ativas
        fwrite(&quant_Requisicao_Ativas, sizeof(int), 1, ficheiro);
        fclose(ficheiro);
    }
}

tipoRequisicao* leFicheiroBinario(tipoPortatil vetorPortatil[MAX_PORTATIL], tipoRequisicao
                                  *vetorRequisicao, int *quant_Portatil, int *quant_requisicao, int *quant_Requisicao_Ativas, int *confirma)
{
    FILE *ficheiro;

    //inicializar valores a 0
    // Tou a pensar se é necessário inicializar as variaveis a 0
    *quant_Portatil = 0;
    *quant_requisicao = 0;

    // Abre ficheiro
    ficheiro = fopen("InfoPortatil.dat","rb");
    // Verifica se temos espaço para o ficheiro
    if (ficheiro == NULL)
    {
        printf("Erro ao abrir ao ficheiro");
    }
    else
    {
        // Vai ler pela mesma ordem que foi gravada na função de gravar os ficheiros
        fread(quant_Portatil, sizeof(int), 1, ficheiro);
        fread(vetorPortatil, sizeof(tipoPortatil), *quant_Portatil, ficheiro);
        fread(quant_requisicao, sizeof(int), 1, ficheiro);

        // fazer o vetor dinamico
        vetorRequisicao = realloc(vetorRequisicao, (*quant_requisicao)* sizeof(tipoRequisicao));
        // verificar se foi possivel criar
        if (vetorRequisicao == NULL && *quant_requisicao != 0)
        {
            printf("Nao foi possivel ler das requisiçoes, tente novamente!");
            *quant_requisicao = 0;
        }
        else
        {
            fread(vetorRequisicao, sizeof(tipoRequisicao), *quant_requisicao, ficheiro);
            fread(quant_Requisicao_Ativas, sizeof(int), 1, ficheiro);
            (*confirma) = 1;
        }
        fclose(ficheiro);
    }

    return vetorRequisicao;
}

void gravaFicheiroLog(tipoRequisicao requisicao, tipoPortatil *vPortatil)
{
    // Declara a variavel
    FILE *ficheiro;
    //Abre o ficheiro
    ficheiro = fopen("Logs.txt", "a");
    // SE ocorrer erro mostra mensagem de erro
    if(ficheiro==NULL)
    {
        printf("ERRO! Foi impossivel de escrever no ficheiro de texto mas a devolucao foi registada");
    }
    else // Caso contrario escreve no log
    {
        fprintf(ficheiro, "\t\tDEVOLUCAO CONCLUIDA\n");
        fprintf(ficheiro, "Codigo da requisicao: %s \nNumero ID Portatil: %d\n", requisicao.codigo, requisicao.num_Indentificacao_Portatil);
        fprintf(ficheiro,"Nome do utente: %s \nTipo de utente: %s\n", requisicao.nome_Utente, requisicao.tipo_Utente);
        fprintf(ficheiro,"Data Requisicao: %d-%d-%d \n", requisicao.data_Requisacao.dia, requisicao.data_Requisacao.mes, requisicao.data_Requisacao.ano);
        fprintf(ficheiro, "Prazo requisitado:%d\n", requisicao.prazo);
        fprintf(ficheiro, "Estado Requisicao: %s \nLocal de devolucao: %s \n", requisicao.estado_Requisacao, requisicao.local_Devolucao);
        fprintf(ficheiro, "Data devolucao: %d-%d-%d \n", requisicao.data_Devolucao.dia, requisicao.data_Devolucao.mes, requisicao.data_Devolucao.ano);
        fprintf(ficheiro, "Multa: %d \n", requisicao.valor_Multa);
        fprintf(ficheiro, "Processador: %s \nRAM: %d GB\n\n", vPortatil->processador, vPortatil->ram);
        fclose(ficheiro);
    }


}

void gravaFicheiroBinarioAvarias(tipoAvaria *vAvaria, int quant_Avarias, int quant_Avarias_Ativas)
{
    FILE *ficheiro;
    // Abre ficheiro
    ficheiro = fopen("InfoAvaria.dat", "wb");
    // Verifica se temos espaço para o ficheiro
    if(ficheiro == NULL)
    {
        printf("Erro ao abrir ao ficheiro");
    }
    else
    {

        // Grava primeiro o numero de avarias
        fwrite(&quant_Avarias, sizeof(int), 1, ficheiro);
        // Grava depois o vetor dos avarias
        fwrite(vAvaria, sizeof(tipoAvaria), quant_Avarias, ficheiro);
        // Grava o numero de avarias ativas
        fwrite(&quant_Avarias_Ativas, sizeof(int), 1, ficheiro);
        printf("Ficheiro gravado com sucesso!\n\n");
        fclose(ficheiro);
    }
}

tipoAvaria *leFicheiroBinarioAvarias(tipoAvaria *vAvaria, int *quant_Avarias, int *quant_Avarias_Ativas)
{
    FILE *ficheiro;

    //inicializar valores a 0
    *quant_Avarias = 0;
    *quant_Avarias_Ativas = 0;

    // Abre ficheiro
    ficheiro = fopen("InfoAvaria.dat","rb");
    // Verifica se temos espaço para o ficheiro
    if (ficheiro == NULL)
    {
        printf("Erro ao abrir ao ficheiro");
    }
    else
    {

        // le primeiro o numero de avarias
        fread(quant_Avarias, sizeof(int), 1, ficheiro);
         // fazer o vetor dinamico
        vAvaria = realloc(vAvaria, (*quant_Avarias)* sizeof(tipoRequisicao));
        // verificar se foi possivel criar
        if (vAvaria == NULL && *quant_Avarias != 0)
        {
            printf("Nao foi possivel ler das requisiçoes, tente novamente!");
            *quant_Avarias = 0;
        }
        else
        {
            // le a informaçao do vetor de vetor
            fread(vAvaria, sizeof(tipoAvaria), *quant_Avarias, ficheiro);
            // le a quantidade de avarias ativas
            fread(quant_Avarias_Ativas, sizeof(int), 1, ficheiro);

            printf("Ficheiros lidos com sucesso!\n\n");

        }
        fclose(ficheiro);


    }

    return vAvaria;
}

