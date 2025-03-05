#include <stdio.h>
#include <stdlib.h>
#include <string.h>




#include "constantes.h"
#include "funcoesportateis.h"
#include "funcoesrequisicao.h"
#include "funcaoLerAuxiliar.h"
#include "funcoesAvaria.h"
#include "funcoesEstatisticas.h"
#include "funcoesDevolucoes.h"


int menu_Principal(int num_Portateis, int num_Disponiveis, int num_Requisicoes, int num_Requisicoes_Ativa, int quant_Avarias_Ativas); //Função do menu principal
int menu_Portateis(int quant_Pc_Disponiveis, int quant_Portatil);
int menu_Requisicao(int quant_Pc_Disponiveis, int quant_Requisicao, int quant_Requisicao_Ativas);
int menu_Avaria(int quant_Avarias_Ativas);

int main()
{
    // Declaraçao e inicialização de variaveis existentes no main
    tipoPortatil vPortatil[MAX_PORTATIL];
    // Declaraçao de duas variaveis para os vetores de avaria e requisiçao
    tipoRequisicao *vRequisicao;
    tipoAvaria *vAvaria;
    int quant_Portatil = 0;
    int quant_Requisicao = 0;
    int quant_Avarias = 0;
    int quant_Avarias_Ativas = 0;
    int quant_Pc_Disponiveis = 0;
    int quant_Requisicao_Ativas = 0;
    // Variaveis para as opçoes dos menus
    int opcaoPrincipal, opcao_submenu;
    // Variavel para a pergunta se quer gravar ou nao
    int escolha_Gravar = 0;

    //vetor dinamico por a NULL
    vRequisicao = NULL;
    vAvaria = NULL;

    do
    {
        opcaoPrincipal = menu_Principal(quant_Portatil, quant_Pc_Disponiveis, quant_Requisicao, quant_Requisicao_Ativas, quant_Avarias_Ativas);
        //Cada case é uma opcão escolhida no menu principal
        switch(opcaoPrincipal)
        {
        case 1:
            do
            {
                //Cada case é uma opcão escolhida no menu portatil
                opcao_submenu = menu_Portateis(quant_Pc_Disponiveis, quant_Portatil);
                switch(opcao_submenu)
                {
                case 1:
                    quant_Portatil = inserir_Portatil(vPortatil, quant_Portatil);
                    quant_Pc_Disponiveis = quant_Portatil - quant_Avarias_Ativas - quant_Requisicao_Ativas;
                    break;
                case 2:
                    if(quant_Portatil==0)
                    {
                        printf("\n AVISO! Nao existem portateis!\n");
                    }
                    else
                    {
                        listarPortateis(vPortatil, quant_Portatil, vRequisicao, quant_Requisicao);
                    }
                    break;
                case 3:
                    if(quant_Portatil != 0)
                    {
                        alterar_local(vPortatil, quant_Portatil);
                    }
                    else
                    {
                        printf("\n AVISO! Nao existem portateis!\n");
                    }
                    break;
                }

            }
            while(opcao_submenu!=0);
            break;
        case 2:
            do
            {
                opcao_submenu = menu_Requisicao(quant_Pc_Disponiveis,quant_Requisicao,quant_Requisicao_Ativas);
                //Cada case é uma opcão escolhida no menu Requisições
                switch(opcao_submenu)
                {
                case 1:
                    // Verifica se existe portáteis para requisitar
                    // E verifica se existe portáteis disponiveis para requisitar
                    if(quant_Portatil == 0 || quant_Pc_Disponiveis == 0)
                    {
                        printf("\nImpossivel requisitar portateis\n");
                    }
                    else
                    {
                        vRequisicao = acrescentaRequisicao(vPortatil, vRequisicao, quant_Portatil,
                                                        &quant_Requisicao, &quant_Requisicao_Ativas);
                        quant_Pc_Disponiveis = quant_Portatil - quant_Avarias_Ativas - quant_Requisicao_Ativas;
                    }
                    break;
                case 2:
                    if(quant_Requisicao == 0 || quant_Requisicao_Ativas == 0)
                    {
                        printf("\nNenhum portatil esta atualmente requisitado\n");
                    }
                    else
                    {
                        renovarRequisicao(vRequisicao, quant_Requisicao);
                    }
                    break;
                case 3:
                    if(quant_Requisicao != 0)
                    {
                        listaRequisicao(vRequisicao, quant_Requisicao);
                    }
                    else
                    {
                        printf("\nNao existe requisicoes! Impossivel de listar\n");
                    }

                    break;
                case 4:
                    if(quant_Requisicao != 0)
                    {
                        mostraRequisicao(vRequisicao, quant_Requisicao, vPortatil, quant_Portatil);
                    }
                    else
                    {
                        printf("\nNao existe requisicoes! Impossivel de listar\n");
                    }
                    break;
                }
            }
            while(opcao_submenu != 0);
            break;
        case 3:
            if(quant_Requisicao_Ativas > 0)
            {
                vAvaria = devolucoes(vPortatil, vRequisicao, quant_Portatil, quant_Requisicao, vAvaria, &quant_Avarias, &quant_Avarias_Ativas, &quant_Requisicao_Ativas);
                quant_Pc_Disponiveis = quant_Portatil - quant_Avarias_Ativas - quant_Requisicao_Ativas;
            }
            else
            {
                printf("Nao existem requisicoes ativas para poder devolver um portatil\n");
            }
            break;
        case 4:
            if(quant_Portatil != 0)
            {
               do
                {
                    opcao_submenu = menu_Avaria(quant_Avarias_Ativas);
                    //Cada case é uma opcão escolhida no menu Avarias
                    switch(opcao_submenu)
                    {
                    case 1:
                        if(quant_Avarias_Ativas == quant_Portatil)
                        {
                            printf("Todos os portateis encontram-se avariados\n");

                        }
                        else
                        {
                             vAvaria = avaria_Inicial(vPortatil, quant_Portatil, vRequisicao, quant_Requisicao, vAvaria, &quant_Avarias, &quant_Avarias_Ativas, &quant_Requisicao_Ativas);
                             quant_Pc_Disponiveis = quant_Portatil - quant_Avarias_Ativas - quant_Requisicao_Ativas;
                        }
                        break;
                    case 2:
                        if(quant_Avarias_Ativas != 0)
                        {
                            // Aumentar a quantidade de pc disponiveis
                            reparacao(vPortatil, quant_Portatil, vAvaria, quant_Avarias, &quant_Avarias_Ativas);
                            quant_Pc_Disponiveis = quant_Portatil - quant_Avarias_Ativas - quant_Requisicao_Ativas;
                        }
                        else
                        {
                            printf("Impossivel de reparar! Nao ha avarias.\n");
                        }
                        break;
                    case 3:
                        if(quant_Avarias != 0)
                        {
                            listagem_Avaria(vPortatil, quant_Portatil, vAvaria, quant_Avarias);
                        }
                        else
                        {
                            printf("Impossivel de listar! Nao ha avarias.\n");
                        }
                        break;
                    }
                }while(opcao_submenu != 0);
            }else
            {
                printf("Nao ha portateis!\n");
            }
            break;
        case 5:
            // Se nao existe portateis nao pode fazer contas estatisticas
            if(quant_Portatil != 0)
            {
                // Se nao existe Requisicões nao pode fazer estas estatisticas
                // Mas existem mais proteçao dentro de cada função
                if(quant_Requisicao != 0)
                {
                    custo_Medio(vRequisicao, quant_Requisicao);
                    devolucoes_Recentes(vRequisicao, quant_Requisicao);
                    estatisticasTipoRequisicao(vRequisicao, quant_Requisicao);
                }
                else
                {
                    printf("Impossivel apresentar dados estatisticos sobre o custo medio da multa, devolucoes mais recentes\n"
                           "e os tipos de utentes com menor requisicoes\n\n");
                }

                estatisticasPORTATIL(vPortatil, quant_Portatil);
            }
            else
            {
                printf("Impossivel apresentar dados estatisticos! Nao existem portateis\n");
            }
            break;
        case 6:
            // Gravar os vetores e mais varaiveis importantes
            //Se nao houver dados no programa pergunta se quer mesmo gravar para nao gravar por cima do ficheiro existente
            if(quant_Portatil == 0)
            {
                printf("Nao ha dados para gravar! Tem a certeza que quer gravar e ficar sem dados?\n");
                printf("(1)-SIM\n");
                printf("(0)-Nao\n");
                printf("\t\tOpcao a realizar: ");
                escolha_Gravar = lerInteiro(0,1);
                if(escolha_Gravar == 1)
                {
                    gravaFicheiroBinario(vPortatil, vRequisicao, quant_Portatil, quant_Requisicao, quant_Requisicao_Ativas);
                    gravaFicheiroBinarioAvarias(vAvaria, quant_Avarias, quant_Avarias_Ativas);
                    quant_Pc_Disponiveis = quant_Portatil - quant_Avarias_Ativas - quant_Requisicao_Ativas;
                }

            }
            else
            {
                gravaFicheiroBinario(vPortatil, vRequisicao, quant_Portatil, quant_Requisicao, quant_Requisicao_Ativas);
                gravaFicheiroBinarioAvarias(vAvaria, quant_Avarias, quant_Avarias_Ativas);
                quant_Pc_Disponiveis = quant_Portatil - quant_Avarias_Ativas - quant_Requisicao_Ativas;
            }
            break;
        case 7:
            // Ler os ficheiros
            vRequisicao = leFicheiroBinario(vPortatil, vRequisicao, &quant_Portatil, &quant_Requisicao, &quant_Requisicao_Ativas, &escolha_Gravar);
            // Se confirmaçao vier 1 a função anterior foi bem sucecida e pode continuar a ler o ficheiro das avarias.
            if(escolha_Gravar == 1)
            {
                // Le o ficheiro de avarias
                vAvaria = leFicheiroBinarioAvarias(vAvaria, &quant_Avarias, &quant_Avarias_Ativas);
            }
            quant_Pc_Disponiveis = quant_Portatil - quant_Avarias_Ativas - quant_Requisicao_Ativas;
            break;
        }
    }
    while(opcaoPrincipal != 0);

    // Liberta os vetores
    free(vRequisicao);
    free(vAvaria);

    printf("Sair do programa!\n");
    return 0;
}

int menu_Principal(int num_Portateis, int num_Disponiveis, int num_Requisicoes, int num_Requisicoes_Ativa, int quant_Avarias_Ativas)
{

    int opcao;
    //Exibe texto do menu principal e pede opcao
    printf("*********************************** MENU PRINCIPAL ***********************************\n\n");
    printf("Quantidade de portateis existentes: %d\t\t", num_Portateis);
    printf("Quantidade de portateis disponiveis: %d\n", num_Disponiveis);
    printf("Total de requisicoes efetuadas: %d\t\t", num_Requisicoes);
    printf("Quantidade de requisicoes ativas: %d\n", num_Requisicoes_Ativa);
    printf("Quantidade de Avarias ativas: %d\n\n", quant_Avarias_Ativas);
    printf("Escolha uma das seguintes opcoes:\n");
    printf("(1)-Inserir/Alterar portatil\n");
    printf("(2)-Requisicoes\n");
    printf("(3)-Devolucoes\n");
    printf("(4)-Avaria/Reparacoes\n");
    printf("(5)-Dados Estatisticos\n");
    printf("(6)-Gravar ficheiro\n");
    printf("(7)-Ler ficheiro\n");
    printf("(0)-Sair\n");
    printf("\t\tOpcao a realizar: ");

    opcao = lerInteiro(0,7);
    printf("\n");

    //devolve opcao escolhida
    return opcao;
}

int menu_Portateis(int quant_Pc_Disponiveis, int quant_Portatil)
{
    //Submenu dos portateis

    int opcao_submenu; //Variavel das opcoes dos submenus

    printf("\n***********************************MENU PORTATEIS***********************************\n\n");
    printf("Quantidade de portateis existentes: %d", quant_Portatil);
    printf("\t\t\tQuantidade de portateis disponiveis: %d", quant_Pc_Disponiveis);
    printf("\n\nOpcoes:\n\n");
    printf("(1)-Inserir portatil\n");
    printf("(2)-Listar portateis\n");
    printf("(3)-Alterar localizacao de portateis\n");
    printf("(0)-Sair\n");
    printf("\tOpcao a selecionar: ");
    opcao_submenu = lerInteiro(0,4);
    printf("\n");
    return opcao_submenu;
}

int menu_Requisicao(int quant_Pc_Disponiveis, int quant_Requisicao, int quant_Requisicao_Ativas)
{
    int opcao;
    //Exibe texto do menu principal e pede opcao
    printf("\n*********************************** MENU DE REQUESICOES ***********************************\n\n");
    printf("Quantidade de portateis disponiveis: %d", quant_Pc_Disponiveis);
    printf("\t\t\tQuantidade de requisicoes efetuadas: %d", quant_Requisicao);;
    printf("\n\nQuantidade de requisicoes ativas: %d", quant_Requisicao_Ativas);
    printf("\n\nEscolha uma das seguintes opcoes:\n\n");
    printf("(1) Registar requisicao de um portatil\n");
    printf("(2) Renovar Requisiçao de um portatil\n");
    printf("(3) Listar todas as requisicoes\n");
    printf("(4) Apresentar informacao de uma requisicao\n");
    printf("(0) Sair\n");
    printf("\t\tOpcao a realizar: ");
    // Escolhe a opcao que pretende
    opcao = lerInteiro(0,4);
    printf("\n");

    return opcao;
}

int menu_Avaria(int quant_Avarias_Ativas)
{
    int opcao;
    //Exibe texto do menu principal e pede opcao
    printf("\n************************************ MENU DE AVARIA ************************************\n\n");
    printf("Quantidade de Avarias ativas: %d\n\n", quant_Avarias_Ativas);
    printf("Escolha uma das seguintes opcoes:\n\n");
    printf("(1)-Registar uma avaria\n");
    printf("(2)-Reparar um portatil\n");
    printf("(3)-Listagem das avarias\n");
    printf("(0)-Sair\n");
    printf("\t\tOpcao a realizar: ");
    opcao = lerInteiro(0,3);
    printf("\n");

    return opcao;
}
