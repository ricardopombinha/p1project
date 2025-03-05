#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoesportateis.h"

//Função para inserir portateis
int inserir_Portatil(tipoPortatil vPortatil[MAX_PORTATIL], int quant_Portatil)
{
    int processador; //i3,i5,i7
    int pos;
    int opcao_localizacao;
    int num_ID;

    if(quant_Portatil==MAX_PORTATIL)
    {
        printf("Nao e possivel inserir mais portateis, limite maximo atingido!\n");
    }
    else
    {
        do
        {
            // Inserir e ler o numero do portatil para acrescentar
            printf("Insira 0 para sair ou o numero de identificacao(1 a 9999) do Portatil: ");;
            num_ID = lerInteiro(0,9999);
            // Procura pelo numero do portatil se retornar uma posição o portatil já existe
            pos = procura_Portatil(vPortatil, quant_Portatil, num_ID);
            if(pos != -1 && num_ID != 0)
            {
                printf("Portatil existente! Escolha outro numero\n\n");
            }

        }while(num_ID != 0 && pos != -1); // sai quando inserir 0 ou um portatil com numero inexisten
        // Se nao exisitr
        if(pos==-1 && num_ID)
        {
            //Copia o numero do portatil para dentro do vetor
            vPortatil[quant_Portatil].num_Identificacao_PC = num_ID;
            //Le a designação que o user introduz
            printf("Indique a designacao (maximo 79 caracteres) do portatil: ");
            lerString(vPortatil[quant_Portatil].designacao, MAX_CHARS_STRING);

            //Le a opçao do processador que o user quer
            printf("Indique o processador do portatil(i3, i5, i7)\n");
            printf("(1)-i3\n(2)-i5\n(3)-i7\n");
            printf("\tOpcao:");
            processador = lerInteiro(1,3);

            //Copia opçao para o vetor
            switch(processador)
            {
            case 1:
                strcpy(vPortatil[quant_Portatil].processador, S_I3);
                break;
            case 2:
                strcpy(vPortatil[quant_Portatil].processador, S_I5);
                break;
            case 3:
                strcpy(vPortatil[quant_Portatil].processador, S_I7);
                break;
            }

            //Le a memoria ram que o user introduz
            printf("Indique a memoria RAM do portatil(4, 8, 16 ou 32)GB: ");
            do
            {
                vPortatil[quant_Portatil].ram = lerInteiro(4,32);
                if(vPortatil[quant_Portatil].ram != 4 && vPortatil[quant_Portatil].ram != 8 && vPortatil[quant_Portatil].ram != 16 && vPortatil[quant_Portatil].ram !=32)
                {
                    printf("\nValor invalido. Insira novamente: \n");
                }
            }
            while(vPortatil[quant_Portatil].ram != 4 && vPortatil[quant_Portatil].ram != 8 && vPortatil[quant_Portatil].ram != 16 && vPortatil[quant_Portatil].ram !=32);

            //define automaticamente o estado do pc como disponivel
            strcpy(vPortatil[quant_Portatil].estado_Pc, S_ESTADO_PC_DISPONIVEL);

            //Le a opçao da Localizaçao que o user quer
            printf("Indique a localizacao do Portatil(Residencias, Campus1, Campus2, Campus5)\n");
            printf("(1)- Residencias\n");
            printf("(2)- Campus1\n");
            printf("(3)- Campus2\n");
            printf("(4)- Campus5\n");
            printf("\tOpcao: ");
            opcao_localizacao = lerInteiro(1,4);

            //Copia opçao para o vetor
            switch(opcao_localizacao)
            {
            case 1:
                strcpy(vPortatil[quant_Portatil].localizacao, S_RESIDENCIAS);
                break;
            case 2:
                strcpy(vPortatil[quant_Portatil].localizacao, S_CAMPUS1);
                break;
            case 3:
                strcpy(vPortatil[quant_Portatil].localizacao, S_CAMPUS2);
                break;
            case 4:
                strcpy(vPortatil[quant_Portatil].localizacao, S_CAMPUS5);
            }

            //Inserir data de aquisicao
            lerData(&vPortatil[quant_Portatil].data_Aquisicao);

            printf("\nIndique o valor do portatil (400 a 3500): ");
            vPortatil[quant_Portatil].Valor_Equipamento=lerFloat(400.0,3500.0);

            //inicializar quantidades de avarias e requisicoes a zero
            vPortatil[quant_Portatil].quant_Avarias = 0;
            vPortatil[quant_Portatil].quant_Requisicoes = 0;
            vPortatil[quant_Portatil].quant_Dias_Requisitados = 0;

            //incrementar a quantidade do vetor do portatil
            quant_Portatil++;
        }
        else
        {
            printf("O portatil ja existe\n");
        }
    }



    return quant_Portatil;
}

//Função para listar portateis
void listarPortateis(tipoPortatil vPortatil[MAX_PORTATIL], int quant_Portatil, tipoRequisicao *vRequisicao, int quant_Requisicao)
{
    //Declarava variaveis necessarias
    int i, j, duracao;

    //Loop for para percorrer o vetor
    for(i=0; i<quant_Portatil; i++)
    {
        // Informação do Portatil
        printf("\n-------------------------------Informacao do Portatil N. Identificacao : %d", vPortatil[i].num_Identificacao_PC);
        printf("-------------------------------\n\n");
        printf("Designacao: %s \t\tProcessador: %s \t\t\tRAM: %d GB\n", vPortatil[i].designacao, vPortatil[i].processador, vPortatil[i].ram);
        printf("Estado: %s \t\tLocalizacao: %s\t\t", vPortatil[i].estado_Pc, vPortatil[i].localizacao);
        printf("Data de Aquisicao: %2d-%2d-%4d\n", vPortatil[i].data_Aquisicao.dia, vPortatil[i].data_Aquisicao.mes, vPortatil[i].data_Aquisicao.ano);
        printf("Valor do PC: %4.2f\t\tQuantidade de avarias: %d\t\tQuantidade de requisicoes:%d\n", vPortatil[i].Valor_Equipamento, vPortatil[i].quant_Avarias, vPortatil[i].quant_Requisicoes);
        printf("Quantidade de Dias Requisitados no total: %d\n", vPortatil[i].quant_Dias_Requisitados);

        // Se o portatil tiver quantidade de requisiçoes a 0 nao mostra esta parte
        if(vPortatil[i].quant_Requisicoes != 0)
        {
            // Informaçao de cada requisiçao do portatil
            printf("\n\t\t-----------------------Informacao das Requisicoes do Portatil-----------------------\n");
            printf("\tCodigo da requisicao\t\tTipo de utente\t\tPrazo da Requisicao\n");
            // Percorre o vetor da requisição e mostra a informação se tiverem o mesmo numero do portatil
            for(j = 0; j < quant_Requisicao; j++)
            {
                if(vRequisicao[j].num_Indentificacao_Portatil == vPortatil[i].num_Identificacao_PC)
                {
                    // Destingue se a requisiçao já acabou ou ainda esta ativa
                    if(strcmp(vRequisicao[j].estado_Requisacao, S_ESTADO_REQ_ATIVA) == 0)
                    {
                        printf("\t%s\t\t\t%s\t\t\tRequisicao ainda ativa\n", vRequisicao[j].codigo, vRequisicao[j].tipo_Utente);
                    }
                    else
                    {
                        //
                        duracao = difenreca_Datas(vRequisicao[j].data_Requisacao, vRequisicao[j].data_Devolucao);
                        printf("\t%s\t\t\t%s\t\t\t%d\n", vRequisicao[j].codigo, vRequisicao[j].tipo_Utente, duracao);
                    }
                }
            }

        }

    }
}
//funcao que devolve a posicao em que se encontra o portatil
int procura_Portatil(tipoPortatil vPortatil[MAX_PORTATIL], int quant_Portatil, int num_ID)
{
    // variavel do indice e da posiçao do portatil, inicializa a varaivel da posiçao
    int i;
    int pos = -1;

    // Percorre pelo vetor do portatil
    for(i=0; i<quant_Portatil; i++)
    {
        // Se na posiçao do vetor tiver o mesmo numero identificaçao que o argumento de entrada num_ID
        // Retorna a posiçao da posiçao que encontra
        if(vPortatil[i].num_Identificacao_PC==num_ID)
        {
            // Atribui o valor do i ao pos para saber qual foi a posiçao que encontrou
            pos=i;
            // poem o i como quant_portatil para sair do for
            i = quant_Portatil;
        }
    }
    // Retorna a pos com numero diferente de -1 se encontrar uma posicao
    return pos;
}

void alterar_local(tipoPortatil vPortatil[MAX_PORTATIL], int quant_Portatil)
{
    int confirm; //Variavel para confirmar se deseja mesmo alterar a posicao
    int opcao; //opcao escolhida para alterar
    int num_ID; // Para guardar o numero de identificaçao do portatil
    int pos; // para guardar a posiçao que se encontra o portatil

    //Perguntar ao user o numero do portatil
    do
    {
        printf("Insira 0 para sair ou o numero de identificacao(1 a 9999) do Portatil: ");
        num_ID = lerInteiro(0,9999);
        pos = procura_Portatil(vPortatil, quant_Portatil, num_ID);
        if(pos == -1 && num_ID != 0)
        {
            printf("Portatil inexistente, impossivel alterar local\n\n");
        }

    }while(num_ID != 0 && pos == -1); // sai quando inserir 0 ou um portatil valido

    if(pos!=-1 && num_ID != 0)
    {
        // Verifica se o portatil está disponivel
        // É só possivel alterar portateis disponiveis
        if(strcmp(vPortatil[pos].estado_Pc, S_ESTADO_PC_DISPONIVEL)== 0)
        {
            // Confirma se o user quer alterar mesmo a localizaçao do portatil
            printf("Deseja mesmo alterar o portatil %s que se encontra no local %s?", vPortatil[pos].designacao, vPortatil[pos].localizacao);
            printf("\n(1)-SIM\n(0)-NAO\n\tOpcao:");
            confirm = lerInteiro(0,1);

            // Se Sim
            if(confirm==1)
            {
                printf("Escolhe uma das seguintes opcoes para alterar a localizacao do portatil\n");
                //Verificar qual é o local atual do portatil para exibir só os restantes
                if(strcmp(vPortatil[pos].localizacao, S_RESIDENCIAS)==0)
                {
                    //Exibir opcoes disponiveis para poder alterar
                    printf("(1)-Campus1\n(2)-Campus2\n(3)-Campus5\n\tOpcao:");
                    opcao=lerInteiro(1,3);
                    switch(opcao)
                    {
                    case 1:
                        strcpy(vPortatil[pos].localizacao, S_CAMPUS1);
                        break;
                    case 2:
                        strcpy(vPortatil[pos].localizacao, S_CAMPUS2);
                        break;
                    case 3:
                        strcpy(vPortatil[pos].localizacao, S_CAMPUS5);
                        break;
                    }

                }
                else
                {
                    //Verificar qual é o local atual do portatil para exibir só os restantes
                    if(strcmp(vPortatil[pos].localizacao, S_CAMPUS1)==0)
                    {
                        //Exibir opcoes disponiveis para poder alterar
                        printf("(1)-Residencias\n(2)-Campus2\n(3)-Campus5\n\tOpcao:");
                        opcao=lerInteiro(1,3);
                        switch(opcao)
                        {
                        case 1:
                            strcpy(vPortatil[pos].localizacao, S_RESIDENCIAS);
                            break;
                        case 2:
                            strcpy(vPortatil[pos].localizacao, S_CAMPUS2);
                            break;
                        case 3:
                            strcpy(vPortatil[pos].localizacao, S_CAMPUS5);
                            break;

                        }
                    }
                    else
                    {
                        //Verificar qual é o local atual do portatil para exibir só os restantes
                        if(strcmp(vPortatil[pos].localizacao, S_CAMPUS2)==0)
                        {
                            //Exibir opcoes disponiveis para poder alterar
                            printf("(1)-Residencias\n(2)-Campus1\n(3)-Campus5\n\tOpcao:");
                            opcao=lerInteiro(1,3);
                            switch(opcao)
                            {
                            case 1:
                                strcpy(vPortatil[pos].localizacao, S_RESIDENCIAS);
                                break;
                            case 2:
                                strcpy(vPortatil[pos].localizacao, S_CAMPUS1);
                                break;
                            case 3:
                                strcpy(vPortatil[pos].localizacao, S_CAMPUS5);
                                break;
                            }
                        }
                        else
                        {
                            //Verificar qual é o local atual do portatil para exibir só os restantes
                            if(strcmp(vPortatil[pos].localizacao, S_CAMPUS5)==0)
                            {
                                //Exibir opcoes disponiveis para poder alterar
                                printf("(1)-Residencias\n(2)-Campus1\n(3)-Campus2\n\tOpcao:");
                                opcao=lerInteiro(1,3);
                                switch(opcao)
                                {
                                case 1:
                                    strcpy(vPortatil[pos].localizacao, S_RESIDENCIAS);
                                    break;
                                case 2:
                                    strcpy(vPortatil[pos].localizacao, S_CAMPUS1);
                                    break;
                                case 3:
                                    strcpy(vPortatil[pos].localizacao, S_CAMPUS2);
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                printf("Opcao escolhida: NAO");
            }
        }
        else // Se o portatil tiver requisitado ou avariado
        {
            printf("Impossivel! Portatil requisitado ou avariado\n");
        }

    }
}
