#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoesEstatisticas.h"


void custo_Medio(tipoRequisicao *vRequisicao, int quant_Requisicao)
{
    //inicializa a variavel i a ser usada no for(), e o contador onde vai incrementar cada vez que encontrar uma requisicao concluida
    int i, contador = 0;
    float media = 0;

    // Percorre o vetor de requisiçoes
    for(i = 0; i <quant_Requisicao; i++)
    {
        // Se o estado de requisição tiver como concluido
        if(strcmp(vRequisicao[i].estado_Requisacao, S_ESTADO__REQ_CONCLUIDA) == 0)
        {
            //incrementa o contador
            contador++;
            //adiciona o valor da multa a variavel media
            media += vRequisicao[i].valor_Multa;
        }
    }
    //Verifica se encontrou requisicoes concluidas
    if(contador != 0)
    {
        //Faz a conta da média
        media = media/contador;

        printf("O custo medio de cada multa paga e %.2f euros.\n\n", media);
    }
    else
    {
        printf("Nenhuma requisicao finalizou! Impossivel prosseguir para o calculo da media das multas.\n\n");
    }
}

void estatisticasPORTATIL(tipoPortatil vPortatil[MAX_PORTATIL], int quant_Portatil)
{
    // Declaraçao das variaveis necessarias
    int i;
    // Guardar o numero dos computadores com cada tipo de processador
    float pc_I3=0, pc_I5=0, pc_I7=0;

    // Percorre o vetor dos portateis
    for(i=0; i<quant_Portatil; i++)
    {
        // Adiciona se o processador I3 incrementa o contador pc_I3
        if(strcmp(vPortatil[i].processador, S_I3) ==0)
        {
            pc_I3++;
        }
        else
        {
            // Adiciona se o processador I5 incrementa o contador pc_I7
            if(strcmp(vPortatil[i].processador, S_I5) ==0)
            {
                pc_I5++;
            }
            else // O ultimo processador possivel incrementa o contador pc_I7
            {
                pc_I7++;
            }
        }

    }
    // Faz as contas das percentagens
    pc_I3 = (pc_I3/quant_Portatil)*100;
    pc_I5 = (pc_I5/quant_Portatil)*100;
    pc_I7 = (pc_I7/quant_Portatil)*100;
    // Mostra as percentagens
    printf("Percentagem de portateis com:\n");
    printf("\tI3: %.2f %%\n", pc_I3);
    printf("\tI5: %.2f %%\n", pc_I5);
    printf("\tI7: %.2f %%\n\n", pc_I7);


}

void estatisticasTipoRequisicao(tipoRequisicao *vRequisicao, int quant_Requisicao)
{
    // Declara as variaveis necessarias
    // Guarda as quantidades de todos os tipos de utente e a quantidade menor dos 3
    int i, quant_E=0, quant_D=0, quant_TA=0, quant_menor;

    //Percorre o vetor das requisiçoes
    for(i=0; i<quant_Requisicao; i++)
    {
        // Adiciona se for estudadente incrementa o contador quant_E
        if(strcmp(vRequisicao[i].tipo_Utente, S_UTENTE_ESTUDANTE)==0)
        {
            quant_E++;
        }
        else
        {
            // Adiciona se for Docente incrementa o contador quant_D
            if(strcmp(vRequisicao[i].tipo_Utente, S_UTENTE_DOCENTE)==0)
            {
                quant_D++;
            }
            else // Adiciona se for TEcnico incrementa o contador quant_TA
            {
                quant_TA++;
            }
        }
    }
    // Poem como menor valor a quantidade E
    quant_menor = quant_E;
    // Se a quantidade menor for maior que quantidade D quer dizer que a quantidade D é menor que quantidade guardada na variavel Quant_menor
    // E depois copia o valor Quant_D para a variavel quantidade menor
    if(quant_menor>quant_D)
    {
        quant_menor = quant_D;

    }
    // Se a quantidade menor for maior que quantidade TA quer dizer que a quantidade TA é menor que quantidade guardada na variavel Quant_menor
    // E depois copia o valor Quant_TA para a variavel quantidade menor
    if(quant_menor>quant_TA)
    {
        quant_menor= quant_TA;

    }
    // indica quais os tipos de utentes com menor quantidades
    printf("\nTipo de utente com menor quantidade de requisicoes:\n");
    // Se um destes valores for igual à variavel quant_menor quer dizer que pode mostrar ao user
    // Pode calhar que os tres tipos sejam a mesma quantidade e quer dizer que mostra os 3 printfs.
    if(quant_menor==quant_E)
    {
        printf("\tEstudante: %d\n", quant_E);
    }
    if(quant_menor==quant_D)
    {
        printf("\tDocente: %d\n", quant_D);
    }
    if(quant_menor==quant_TA)
    {
        printf("\tTecnico Administrativo: %d\n", quant_TA);
    }
    printf("\n");

}

void devolucoes_Recentes(tipoRequisicao *vRequisicao, int quant_Requisicao)
{
    //inicia a variavel a utilizar no ciclo for
    int i;
    tipoData data_Recente;
    // variavel para guardar a diferença de dias
    int duracao = -1;
    //inicia a variavel a utilizar para ajudar no calculo da duracao
    data_Recente.ano = 2012;
    data_Recente.mes = 1;
    data_Recente.dia = 1;

    // Percorre o vetor das requisiçoes
    for(i = 0; i < quant_Requisicao; i++)
    {
        // Se a requisiçaot tiver concluida procede para verificar qual é data mais recente
        if(strcmp(vRequisicao[i].estado_Requisacao, S_ESTADO__REQ_CONCLUIDA) == 0)
        {
            // Como a funçao diferença datas precisa que o primeiro argumento seja uma data mais antiga ou igual é necesario fazer a verificaçao que
            // a data da devoluçao seja igual ou depois da data recente
            // Se nao houvesse esta verificaçao a funçao entra num loop infinito
            if(data_Recente.ano < vRequisicao[i].data_Devolucao.ano || (data_Recente.ano == vRequisicao[i].data_Devolucao.ano
                    && data_Recente.mes < vRequisicao[i].data_Devolucao.mes) || (data_Recente.ano == vRequisicao[i].data_Devolucao.ano
                    && data_Recente.mes == vRequisicao[i].data_Devolucao.mes && data_Recente.mes < vRequisicao[i].data_Devolucao.mes))
            {
                // calcula a diferença de datas
                duracao = difenreca_Datas(data_Recente, vRequisicao[i].data_Devolucao);
                // Como pode dar 0, só copia se a duraçao for maior que 0
                if(duracao > 0)
                {
                    //Atualiza valor da data_Recente
                    data_Recente = vRequisicao[i].data_Devolucao;
                }
            }

        }
    }
    //Verifica se a duracao é diferente de -1, se for diferente que -1 quer dizer que há requisiçoes concluidas
    // Se for igual -1, quer dizer que nenhuma das requisiçoes foram concluidas
    if(duracao != -1)
    {
        printf("A(s) devolucoe(s) mais recente e(sao):\n");
        // Percorre pelo o vetor das requisiçoes
        for(i = 0; i <quant_Requisicao; i++)
        {
            // Se a data da devoluçao for igual à data_recente mostra os dados da requisiçao
            if(data_Recente.ano == vRequisicao[i].data_Devolucao.ano && data_Recente.mes == vRequisicao[i].data_Devolucao.mes
               && data_Recente.dia == vRequisicao[i].data_Devolucao.dia)
            {
                printf("\n-------------------------------Informacao da Requisicao codigo : %s", vRequisicao[i].codigo);
                printf("-------------------------------\n\n");
                printf("Estado: %s\t\tNumero do portatil: %4d\t\t", vRequisicao[i].estado_Requisacao, vRequisicao[i].num_Indentificacao_Portatil);
                printf("Nome do utente: %s\nTipo de utente: %s\t\t", vRequisicao[i].nome_Utente, vRequisicao[i].tipo_Utente);
                printf("Data de requisicao: %2d-%2d-%4d\t\t", vRequisicao[i].data_Requisacao.dia, vRequisicao[i].data_Requisacao.mes, vRequisicao[i].data_Requisacao.ano);
                printf("Prazo da requisicao: %d\n",vRequisicao[i].prazo);
                printf("Data da devolucao: %2d-%2d-%4d\t\t", vRequisicao[i].data_Devolucao.dia, vRequisicao[i].data_Devolucao.mes, vRequisicao[i].data_Devolucao.ano);
                printf("Local de devolucao: %s\t\t", vRequisicao[i].local_Devolucao);
                printf("Valor da multa: %d\n", vRequisicao[i].valor_Multa);

            }
        }
    }
    else
    {
        printf("Nenhuma requisicao finalizou para mostrar a(s) devolucoe(s) mais recente(s).\n");
    }
    printf("\n");
}
