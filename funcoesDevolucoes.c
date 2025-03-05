#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoesDevolucoes.h"


tipoAvaria *devolucoes(tipoPortatil vPortatil[MAX_PORTATIL], tipoRequisicao *vRequisicao, int quant_Portatil, int quant_Requisicao,
                       tipoAvaria *vAvaria, int *quant_Avaria, int *quant_Avaria_Ativas, int *quant_Requisicao_Ativa)
{
    // Declara todas as variaveis a serem precisas
    // Verifica_Avaria verifica se durante a requisi�ao o portatil ficou avariado
    int num_ID, verifica_Avaria, i;
    int pos_PC = -1;
    int pos_Requisicao = -1;
    // Confirma se foi possivel registar a avaria, se foi possivel vai retornar da fun��o avaria com o valor 1
    int confirma_Avaria = 0;
    // Para guardar data temporaria e entrar como argumento de entrada nas fun�oes de devolver portatil e acrescentarRequisicao
    tipoData data_Temp;

    do
    {
         // Pede o numero de identifica�ao ao utilizador
        printf("Insira 0 para sair ou o numero de identificacao(1 a 9999) do Portatil: ");
        num_ID = lerInteiro(0,9999);
        //Procura o numero de identificacao do portatil indicado pelo utilizador
        pos_PC = procura_Portatil(vPortatil, quant_Portatil, num_ID);
        if(pos_PC == -1 && num_ID != 0)
        {
            printf("Portatil inexistente, impossivel devolver\n\n");
        }

    }while(num_ID != 0 && pos_PC == -1); // sai quando inserir 0 ou um portatil valido


    if(pos_PC != -1 && num_ID != 0)
    {
        //Procura a ultima posicao em que se encontra o portatil, no vetor de Requisicoes
        //ATENCAO, este for() � percorrido da ultima posicao at� � primeira, de forma a fazer com que guarde a posicao da requisicao mais recente desse portatil
        //Caso nao encontre no vetor, o numero do portatil vai devolver -1, se encontrar devolve a posicao
        for(i = quant_Requisicao-1 ; i>=0; i--)
        {
            if(vRequisicao[i].num_Indentificacao_Portatil==vPortatil[pos_PC].num_Identificacao_PC)
            {
                pos_Requisicao = i;

                i=-1;
            }

        }

        if(pos_Requisicao != -1)
        {
            //Verificar se a requisicao esta ativa
            if(strcmp (vRequisicao[pos_Requisicao].estado_Requisacao, S_ESTADO_REQ_ATIVA)==0)
            {
                //Confirmacao de uma poss�vel avaria
                printf("\nO portatil esta avariado?");
                printf("\n(1)-SIM\n(2)-NAO\n\tOpcao: ");
                verifica_Avaria=lerInteiro(1,2);

                do
                {
                    //Fun��o em que permite o utilizador inserir a data de devolu��o
                    printf("\nIndique a data em que esta a devolver o PC\n");
                    lerData(&(data_Temp));


                //Mensagem de aviso caso a data de devolu��o seja anterior � data da requisicao
                    if(vRequisicao[pos_Requisicao].data_Requisacao.ano>data_Temp.ano ||
                            (vRequisicao[pos_Requisicao].data_Requisacao.ano==data_Temp.ano && vRequisicao[pos_Requisicao].data_Requisacao.mes>data_Temp.mes) ||
                            (vRequisicao[pos_Requisicao].data_Requisacao.ano==data_Temp.ano && vRequisicao[pos_Requisicao].data_Requisacao.mes==data_Temp.mes && vRequisicao[pos_Requisicao].data_Requisacao.dia>data_Temp.dia))
                    {
                        printf("Por favor indique uma data valida!!! A data devolucao tem de ser posterior ou a mesma data de data de requisicao:"
                               "%2d-%2d-%4d", vRequisicao[pos_Requisicao].data_Requisacao.dia, vRequisicao[pos_Requisicao].data_Requisacao.mes,
                               vRequisicao[pos_Requisicao].data_Requisacao.ano);
                    }
                //Prote��o para impedir com que a data de devolu��o introduzida seja anterior � data da requisi��o
                }
                while(vRequisicao[pos_Requisicao].data_Requisacao.ano>data_Temp.ano ||
                        (vRequisicao[pos_Requisicao].data_Requisacao.ano==data_Temp.ano && vRequisicao[pos_Requisicao].data_Requisacao.mes>data_Temp.mes) ||
                        (vRequisicao[pos_Requisicao].data_Requisacao.ano==data_Temp.ano && vRequisicao[pos_Requisicao].data_Requisacao.mes==data_Temp.mes && vRequisicao[pos_Requisicao].data_Requisacao.dia>data_Temp.dia));

                //Caso o utilizador tivesse introduzido que o port�til estivesse avariado, vai entrar na fun��o acrescenta avaria
                if(verifica_Avaria == 1)
                {
                    vAvaria = acrescentaAvaria(&vPortatil[pos_PC], vAvaria, &(*quant_Avaria), &(*quant_Avaria_Ativas), num_ID, data_Temp, &confirma_Avaria);

                    //Se a avaria for confirmada == 1 permite ao utilizador devolver o portatil
                    if(confirma_Avaria == 1)
                    {
                        devolverPortatil(&(vPortatil[pos_PC]), &vRequisicao[pos_Requisicao], data_Temp, 0);
                        (*quant_Requisicao_Ativa)--;

                    }
                }
                else
                {
                    //Caso o portatil nao esteja avariado, � na mesma poss�vel o utilizador devolver o port�til
                    devolverPortatil(&(vPortatil[pos_PC]), &vRequisicao[pos_Requisicao], data_Temp, 1);
                    (*quant_Requisicao_Ativa)--;
                }
            }
            else
            {
                // Quando encontra a posi�ao e requisi�ao est� como concluida
                printf("O portatil nao se encontra requisitado\n\n");
            }
        }
        else
        {   // Este printf serve quando o portatil nunca foi requisitado ou seja o numero nao est� no vetor das requisi��es
            printf("O portatil nao se encontra requisitado\n\n");
        }
    }

    return vAvaria;
}

// Nesta fun��o nao se trabalha com os vetores inteiros de portatil e da requisi�ao mas sim
// A posi�ao em que se encontra. Ou seja passamos a estrutura por argumento de referencia
void devolverPortatil(tipoPortatil *vPortatil, tipoRequisicao *vRequisicao, tipoData data, int modo)
{
    // declara variaveis
    // local para a pergunta de qual locar quer
    int local, dia_Contados, dias_multa=0;

    // Pergunta ao user onde ele quer devolver o portatil
    printf("\nIndique onde quer devolver o portatil");
    printf("\n(1)-Residencias\n(2)-Campus1\n(3)-Campus2\n(4)-Campus5");
    printf("\n\tOpcao: ");
    local= lerInteiro(1,4);
    // Copia a op�ao escolhida para o vetor das requisi�oes e o vetor dos portateis a localiza��o que foi devolvido
    switch(local)
    {
    case 1:
        strcpy(vPortatil->localizacao, S_RESIDENCIAS);
        strcpy(vRequisicao->local_Devolucao, S_RESIDENCIAS);
        break;
    case 2:
        strcpy(vPortatil->localizacao, S_CAMPUS1);
        strcpy(vRequisicao->local_Devolucao, S_CAMPUS1);
        break;
    case 3:
        strcpy(vPortatil->localizacao, S_CAMPUS2);
        strcpy(vRequisicao->local_Devolucao, S_CAMPUS2);
        break;
    case 4:
        strcpy(vPortatil->localizacao, S_CAMPUS5);
        strcpy(vRequisicao->local_Devolucao, S_CAMPUS5);
    }
    //Mete o estado da requisi�ao como concluida
    strcpy (vRequisicao->estado_Requisacao, S_ESTADO__REQ_CONCLUIDA);

    //Mete o data de devolu��o. A data vem como argumento de entrada.
    vRequisicao->data_Devolucao.ano = data.ano;
    vRequisicao->data_Devolucao.mes = data.mes;
    vRequisicao->data_Devolucao.dia = data.dia;

    //Verificar a diferenca de dias entre as datas
    dia_Contados = difenreca_Datas(vRequisicao->data_Requisacao, vRequisicao->data_Devolucao);
    // Se a diferen�a dos dias for superior ao prazo
    if (dia_Contados > vRequisicao->prazo)
    {
        //Calcula a diferen�a de dias entre os dias contados entre as datas e o prazo da requisi�ao
        dias_multa = dia_Contados - vRequisicao->prazo;
        // A multa � calculada ao multiplicar por 10
        // Se nao pagar multa, nao faz mal pq o valor � inicializado a 0 quando inicia-se uma requisi�ao
        vRequisicao->valor_Multa = dias_multa * 10;
    }
    //Mete os dias que foi requisitado para o vetor do portatis na posi�ao passada
    vPortatil->quant_Dias_Requisitados += dia_Contados;

    printf("\nO valor a pagar de multa sera de %d euros\n\n", vRequisicao->valor_Multa);

    // Se o modo vier 1 significa que nao houve avaria e tem de meter como disponivel
    if(modo == 1)
    {
        strcpy(vPortatil->estado_Pc, S_ESTADO_PC_DISPONIVEL);
    }
    //Grava as devolu��es no log
    gravaFicheiroLog(*vRequisicao, &(*vPortatil));

}


