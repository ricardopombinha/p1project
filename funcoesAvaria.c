#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoesAvaria.h"

void reparacao(tipoPortatil vPortatil[MAX_PORTATIL], int quant_portatil, tipoAvaria *vAvaria, int quant_Avaria, int *quant_Avaria_Ativas)
{
    // Declaraçao para a variavel da posiçao portatil (pos_P) avaria (pos_A), e o numero de identificaçao do portatil
    int pos_P, pos_A, num_Id;

    do
    {
        //Introducao do numero do PC
        printf("Insira 0 para sair ou o numero de identificacao do portatil que quer reparar: ");
        num_Id = lerInteiro(0,9999);
        pos_P = procura_Portatil(vPortatil, quant_portatil, num_Id);
        //Verificacao para a existencia ou nao do PC, caso nao exista devolve -1, caso exista devolve a posicao
        if(num_Id != 0 && pos_P == -1)
        {
            printf("Portatil inexistente\n");
        }

    }while(num_Id != 0 && pos_P == -1); // sai do loop quando encontrar a posiçao ou o numero de identificaçao for 0

    //Entra Se encontrar posiçao
    if(pos_P != -1)
    {
        // Procura a posiçao da avaria
        pos_A = procura_Avaria(vAvaria, quant_Avaria, num_Id);
        if(pos_A != -1 )
        {
            // Poem o portatil como disponivel
            strcpy(vPortatil[pos_P].estado_Pc, S_ESTADO_PC_DISPONIVEL);
            //Le a data
            do
            {
                lerData(&(vAvaria[pos_A].data_Reparacao));
                if(!((vAvaria[pos_A].data_Reparacao.ano > vAvaria[pos_A].data_Avaria.ano) || (vAvaria[pos_A].data_Reparacao.ano == vAvaria[pos_A].data_Avaria.ano
                    && vAvaria[pos_A].data_Reparacao.mes > vAvaria[pos_A].data_Avaria.mes) || (vAvaria[pos_A].data_Reparacao.ano == vAvaria[pos_A].data_Avaria.ano
                    && vAvaria[pos_A].data_Reparacao.mes >= vAvaria[pos_A].data_Avaria.mes && vAvaria[pos_A].data_Reparacao.dia > vAvaria[pos_A].data_Avaria.dia)))
                {
                    printf("A data de reparacao tem de estar depois da data de avaria %2d-%2d-%4d\n",vAvaria[pos_A].data_Avaria.dia,
                           vAvaria[pos_A].data_Avaria.mes, vAvaria[pos_A].data_Avaria.ano);
                }
                //Verifica se a data de reparacao é superior ou igual à data de avaria
            }while(!((vAvaria[pos_A].data_Reparacao.ano > vAvaria[pos_A].data_Avaria.ano) || (vAvaria[pos_A].data_Reparacao.ano == vAvaria[pos_A].data_Avaria.ano
                    && vAvaria[pos_A].data_Reparacao.mes > vAvaria[pos_A].data_Avaria.mes) || (vAvaria[pos_A].data_Reparacao.ano == vAvaria[pos_A].data_Avaria.ano
                    && vAvaria[pos_A].data_Reparacao.mes >= vAvaria[pos_A].data_Avaria.mes && vAvaria[pos_A].data_Reparacao.dia > vAvaria[pos_A].data_Avaria.dia)));

            vAvaria[pos_A].duracao_avaria = difenreca_Datas(vAvaria[pos_A].data_Avaria, vAvaria[pos_A].data_Reparacao);

            (*quant_Avaria_Ativas)--;
        }
    }
    else
    {
        printf("Sair da opcao\n");
    }
}

int procura_Avaria(tipoAvaria *vAvaria, int quant_avaria, int id_Portatil)
{
    int pos = -1;
    int i;

    //aqui vai andar do ultimo para o zero. porque se encontramos o portatil e tiver reparadado já sabemos que as outras avarias
    //que ocorrem foram resolvidas por isso não é necessário procurar mais
    for(i = quant_avaria -1 ; i >= 0; i--)
    {
        if(vAvaria[i].num_Indentificacao_PC == id_Portatil && vAvaria[i].tipo_Avaria == 2)
        {
            i = -1;
            printf("Portatil avariado permanentemente, impossivel de reparar|\n");
        }
        else
        {
            // A duracao indica se ele foi arranjado ou nao
            // Se tiver o mesmo numero, e avaria for permanente e a duraçao tiver com -1 o numero inicializado
            // O pc nao foi arranjado e manda essa pos para fora
            if(vAvaria[i].num_Indentificacao_PC == id_Portatil && vAvaria[i].tipo_Avaria == 1
               && vAvaria[i].duracao_avaria == -1)
            {
                pos = i;
                // para sair do loop
                i = -1;
            }
            else
            {
                // Mesma condiçao que anterior ,as
                //Se a duracao da avaria for diferente a -1 entao o portatil nao se encontra avariado
                if(vAvaria[i].num_Indentificacao_PC == id_Portatil && vAvaria[i].tipo_Avaria == 1
                   && vAvaria[i].duracao_avaria != -1 )
                {
                    printf("Portatil nao se encontra danificado!\n");
                    // para sair do loop
                    i = -1;
                }
                else
                {
                    //Se o portatil nunca tiver sido avariado, nao estará no vetor e só ai é que chega a esta opcao
                    if(i == 0)
                    {
                        printf("Portatil nao se encontra danificado!\n");
                    }
                }
            }
        }
    }

    return pos;

}

tipoAvaria *acrescentaAvaria(tipoPortatil *portatil, tipoAvaria *vAvaria, int *quant_Avaria, int *quant_Avaria_Ativas, int num_Id, tipoData data, int *confirma_Avaria)
{
    tipoAvaria *ponteiro_Temp;
    //Guarda o vAvaria numa variável de "backup" caso der erro a re-alocar o vetor
    ponteiro_Temp = vAvaria;
    //Vai aumentar um espaço no vetor para guardar outra avaria
    vAvaria = realloc(vAvaria, (*quant_Avaria + 1)*sizeof(tipoAvaria));

    if(vAvaria == NULL)
    {
        printf("Impossivel de registar a avaria! Tente novamente.\n");
        //Devolve o valor inicial antes do erro
        vAvaria = ponteiro_Temp;
    }
    else
    {
        //  Por o numero de identificaçao do vetor
        vAvaria[*quant_Avaria].num_Indentificacao_PC = num_Id;

        // Por o tipo de avaria no vetor
        printf("A avaria e do tipo:\n");
        printf("(1)-Temporaria\n");
        printf("(2)-Permanente\n");
        printf("\t Opcao a selecionar: ");
        vAvaria[*quant_Avaria].tipo_Avaria = lerInteiro(1,2);

        // Ler a data
        vAvaria[*quant_Avaria].data_Avaria.ano = data.ano;
        vAvaria[*quant_Avaria].data_Avaria.mes = data.mes;
        vAvaria[*quant_Avaria].data_Avaria.dia = data.dia;

        // Inicializar a duraçao a -1
        vAvaria[*quant_Avaria].duracao_avaria = -1;

        // Aumentar o numero de vezes que o portatil foi avariado
        (portatil->quant_Avarias)++;
        // Actualizar o portatil para avariado
        strcpy(portatil->estado_Pc, S_ESTADO_PC_AVARIADO);
        //actualizar a quantidade de avarias  e quantidade de avarias ativas
        (*quant_Avaria)++;
        (*quant_Avaria_Ativas)++;
        (*confirma_Avaria)++;
    }
    return vAvaria;
}


void listagem_Avaria(tipoPortatil vPortatil[MAX_PORTATIL], int quant_portatil, tipoAvaria *vAvaria, int quant_Avaria)
{
    int i, pos_P;
    //Vai percorrer o for() de modo a listar todos os dados do pc juntamente com os dados da avaria
    for(i = 0; i < quant_Avaria; i++)
    {
        pos_P= procura_Portatil(vPortatil, quant_portatil, vAvaria[i].num_Indentificacao_PC);
        printf("\n-------------------------------Informacao da avaria do Portatil N. Identificacao : %d", vAvaria[i].num_Indentificacao_PC);
        printf("-------------------------------\n\n");
        printf("Designacao: %s \t\tProcessador: %s \t\t\tRAM: %d GB\n", vPortatil[pos_P].designacao, vPortatil[pos_P].processador, vPortatil[pos_P].ram);
        printf("Estado: %s \t\tLocalizacao: %s\t\t", vPortatil[pos_P].estado_Pc, vPortatil[pos_P].localizacao);
        printf("Data de Aquisicao: %2d-%2d-%4d\n", vPortatil[pos_P].data_Aquisicao.dia, vPortatil[pos_P].data_Aquisicao.mes, vPortatil[pos_P].data_Aquisicao.ano);
        printf("Valor do PC: %4.2f\t\tQuantidade de avarias: %d\t\tQuantidade de requisicoes:%d\n", vPortatil[pos_P].Valor_Equipamento, vPortatil[pos_P].quant_Avarias, vPortatil[pos_P].quant_Requisicoes);
        printf("Quantidade de Dias Requisitados no total: %d\n", vPortatil[pos_P].quant_Dias_Requisitados);
        printf("\n\t-----------------------Informacao Referente a avaria-----------------------\n");
        //Escreve no monitor o tipo da avaria
        if(vAvaria[i].tipo_Avaria == 1)
        {
            printf("\tTipo de avaria: Temporaria\t\t");
        }
        else
        {
            printf("\tTipo de avaria: Permanente\t\t");
        }
        //Escreve no monitor a data da avaria
        printf("Data da avaria: %2d-%2d-%4d\n", vAvaria[i].data_Avaria.dia, vAvaria[i].data_Avaria.mes, vAvaria[i].data_Avaria.ano);
        //Escreve no monitor a data de reparacao e duracao de avaria
        // Se a duraçao for -1 escreve os riscos
        if(vAvaria[i].duracao_avaria == -1)
        {
            printf("\tData da reparacao: --------\t\t");
            printf("Duracao da avaria: --------\n");
        }
        else
        {
            printf("\tData da reparacao: %2d-%2d-%4d\t\t", vAvaria[i].data_Reparacao.dia, vAvaria[i].data_Reparacao.mes, vAvaria[i].data_Reparacao.ano);
            printf("Duracao da avaria: %d\n", vAvaria[i].duracao_avaria);
        }
    }
}

tipoAvaria *avaria_Inicial(tipoPortatil vPortatil[MAX_PORTATIL], int quant_portatil, tipoRequisicao *vRequisicao, int quant_Requisicao,
                           tipoAvaria *vAvaria, int *quant_Avaria, int *quant_Avaria_Ativas, int *quant_Requisicao_Ativa)
{
    // Declara as variaveis necessárias
    int num_Id, pos_Pc, i;
    int pos_Req = -1;
    // Confirma se foi possivel registar a avaria, se foi possivel vai retornar da função avaria com o valor 1
    int confirma_Avaria = 0;
    // Utilizado como argumento de entrada para as funcoes acrescentar avaria e devolver portatil
    tipoData data_Temp;

    printf("Insira 0 para sair ou o numero de identificacao do portatil que avariou: ");
    do
    {
        num_Id = lerInteiro(0,9999);
        //Procura o numero de identificacao do portatil indicado pelo utilizador
        pos_Pc = procura_Portatil(vPortatil, quant_portatil, num_Id);
        //Devolve -1 se não encontrar o numero, se encontrar devolve a posicao onde se encontra
        //Verificar se o portátil existe
        if(num_Id != 0 && pos_Pc == -1)
        {
            printf("Portatil inexistente\n");
        }

    }
    while(num_Id != 0 && pos_Pc == -1);
    //Se o portátil existir, vai ser devolvida uma pos_Pc diferente de -1, logo vai entrar neste if()
    if(pos_Pc != -1)
    {
        //
        //Proteçao para ver se existem requisicoes
        if(quant_Requisicao != 0)
        {
            //Procura a ultima posicao em que se encontra o portatil, no vetor de Requisicoes
            //ATENCAO, este for() é percorrido da ultima posicao até à primeira, de forma a fazer com que guarde a posicao da requisicao mais recente desse portatil
            //Caso nao encontre no vetor, o numero do portatil vai devolver -1, se encontrar devolve a posicao

            for(i = quant_Requisicao-1 ; i>=0; i--)
            {
                if(vRequisicao[i].num_Indentificacao_Portatil==vPortatil[pos_Pc].num_Identificacao_PC)
                {
                    pos_Req = i;

                    i=-1;
                }

            }
        }
        //Verificacao do estado do PC
        if(strcmp(vPortatil[pos_Pc].estado_Pc, S_ESTADO_PC_DISPONIVEL) == 0)
        {
            do
            {
                //Ler data da avaria
                lerData(&data_Temp);

                if(!((data_Temp.ano > vPortatil[pos_Pc].data_Aquisicao.ano) || (data_Temp.ano == vPortatil[pos_Pc].data_Aquisicao.ano
                        && data_Temp.mes >= vPortatil[pos_Pc].data_Aquisicao.mes) || (data_Temp.ano == vPortatil[pos_Pc].data_Aquisicao.ano
                                && data_Temp.mes >= vPortatil[pos_Pc].data_Aquisicao.mes && data_Temp.dia >= vPortatil[pos_Pc].data_Aquisicao.dia)))

                {
                    printf("A data de avaria tem de ser igual ou superior à data de aquisicao do portatil: ");
                    printf("%2d-%2d-%4d\n", vPortatil[pos_Pc].data_Aquisicao.dia, vPortatil[pos_Pc].data_Aquisicao.mes,
                           vPortatil[pos_Pc].data_Aquisicao.ano);
                }
                //Proteção para impedir com que a data da avaria introduzida seja anterior à data da aquisicao do PC
            }
            while(!((data_Temp.ano > vPortatil[pos_Pc].data_Aquisicao.ano) || (data_Temp.ano == vPortatil[pos_Pc].data_Aquisicao.ano
                    && data_Temp.mes >= vPortatil[pos_Pc].data_Aquisicao.mes) || (data_Temp.ano == vPortatil[pos_Pc].data_Aquisicao.ano
                            && data_Temp.mes >= vPortatil[pos_Pc].data_Aquisicao.mes && data_Temp.dia >= vPortatil[pos_Pc].data_Aquisicao.dia)));

            //Acrescenta uma avaria
            vAvaria = acrescentaAvaria(&vPortatil[pos_Pc], vAvaria, &(*quant_Avaria), &(*quant_Avaria_Ativas), num_Id, data_Temp, &confirma_Avaria);

        }
        else
        {
            //Verificar se o portatil esta requisitado
            if(strcmp(vPortatil[pos_Pc].estado_Pc, S_ESTADO_PC_REQUISITADO) == 0)
            {
                do
                {
                    lerData(&data_Temp);

                    if(!((data_Temp.ano > vRequisicao[pos_Req].data_Requisacao.ano) || (data_Temp.ano == vRequisicao[pos_Req].data_Requisacao.ano
                            && data_Temp.mes > vRequisicao[pos_Req].data_Requisacao.mes) ||(data_Temp.ano == vRequisicao[pos_Req].data_Requisacao.ano
                                    && data_Temp.mes == vRequisicao[pos_Req].data_Requisacao.mes && data_Temp.dia > vRequisicao[pos_Req].data_Requisacao.dia)))

                    {
                        printf("A data de avaria tem de ser ou superior à data de requisicao do portatil: ");
                        printf("%2d-%2d-%4d\n", vRequisicao[pos_Req].data_Requisacao.dia, vRequisicao[pos_Req].data_Requisacao.mes,
                               vRequisicao[pos_Req].data_Requisacao.ano);
                    }
                    //Proteção para impedir com que a data da avaria introduzida seja anterior à data da aquisicao do PC
                }
                while(!((data_Temp.ano > vRequisicao[pos_Req].data_Requisacao.ano) || (data_Temp.ano == vRequisicao[pos_Req].data_Requisacao.ano
                        && data_Temp.mes > vRequisicao[pos_Req].data_Requisacao.mes) ||(data_Temp.ano == vRequisicao[pos_Req].data_Requisacao.ano
                                && data_Temp.mes == vRequisicao[pos_Req].data_Requisacao.mes && data_Temp.dia > vRequisicao[pos_Req].data_Requisacao.dia)));
                //acrescenta uma avaria
                vAvaria = acrescentaAvaria(&vPortatil[pos_Pc], vAvaria, &(*quant_Avaria), &(*quant_Avaria_Ativas), num_Id, data_Temp, &confirma_Avaria);
                //Caso o acrescentaAvaria tenha sido bem sucedido vai devolver o portatil
                if(confirma_Avaria == 1)
                {
                    printf("Portatil Encontra-se Requisitado terá de devolver\n");
                    devolverPortatil(&(vPortatil[pos_Pc]), &vRequisicao[pos_Req], data_Temp,0);
                    //Como o portatil foi devolvido teve de ser diminuida a quantidade de requisicoes ativas
                    (*quant_Requisicao_Ativa)--;
                }
            }
            else
            {
                printf("O portatil encontra-se avariado!\n");
            }

        }
    }

    return vAvaria;
}

