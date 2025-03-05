#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "funcoesrequisicao.h"

int procuraRequisicao(tipoRequisicao *vRequisicao, int num_Requisicao, char code_string[MAX_CODIGO])
{
    //inicializar posiçao a menos 1
    int pos = -1,i;

    for (i = 0; i < num_Requisicao; i++)
    {
        if(strcmp(vRequisicao[i].codigo, code_string) == 0)
        {
            pos = i;
            i = num_Requisicao;
        }
    }
    //Caso encontre um codigo igual devolve o valor da posicao, caso nao encontre devolve -1
    return pos;
}

int leCodigo_e_Retorna_Pos(tipoRequisicao *vRequisicao, int num_Requisicao, char code[MAX_CODIGO])
{
    //declarar posicao
    int posicao;
    // Le codigo e retorna a posiçao
    printf("Insira o codigo (10 Caracteres) da requisicao pretendido\n");
    printf("Se pretender sair insira o 0\n");
    printf("Codigo da Requisicao: ");

    do
    {
        //le o codigo da requisicao
        lerString(code, MAX_CODIGO);
        posicao = procuraRequisicao(vRequisicao, num_Requisicao, code);
        //Caso encontre um codigo igual devolve o valor da posicao, caso nao encontre devolve -1
        if(posicao == -1)
        {
            printf("Codigo Inexistente! Insira 0 para sair ou insira um codigo valido para continuar: \n");
        }
    }
    while((strcmp(code, "0") != 0) && posicao == -1);  //Sai quando o code for 0 ou o codigo exisitr

    return posicao;
}

tipoRequisicao leRequisicao(tipoData data_I)
{
    //declarar variavel de requisicao
    tipoRequisicao dados;
    int opcao;

    //le nome de utente
    printf("Indique o seu nome: ");
    lerString(dados.nome_Utente, MAX_CHARS_STRING);

    //le o tipo de utente
    printf("Indique que tipo de utente e?\n");
    printf("(1)-Estudante\n");
    printf("(2)-Docente\n");
    printf("(3)-Tecnico Administrativo\n");
    printf("\t\tOpcao a realizar:");
    opcao = lerInteiro(1,3);
    switch(opcao)
    {
    case 1:
        strcpy(dados.tipo_Utente, S_UTENTE_ESTUDANTE);
        break;
    case 2:
        strcpy(dados.tipo_Utente, S_UTENTE_DOCENTE);
        break;
    case 3:
        strcpy(dados.tipo_Utente, S_UTENTE_TECNICO);
        break;
    }

    // Le data requisicao
    do
    {
        lerData(&dados.data_Requisacao);
        if(!((dados.data_Requisacao.ano > data_I.ano) || (dados.data_Requisacao.ano == data_I.ano
                && dados.data_Requisacao.mes >= data_I.mes && dados.data_Requisacao.dia >= data_I.dia)))
        {
            printf("A data de requisicao tem de ser igual ou superior à data de aquisicao do portatil que e: ");
            printf("%2d-%2d-%4d\n", data_I.dia, data_I.mes, data_I.ano);
        }
        //Verifica se a data da requisicao é superior à data de aquisicao do portatil
    }while(!((dados.data_Requisacao.ano > data_I.ano) || (dados.data_Requisacao.ano == data_I.ano
                && dados.data_Requisacao.mes > data_I.mes) || (dados.data_Requisacao.ano == data_I.ano
                && dados.data_Requisacao.mes == data_I.mes && dados.data_Requisacao.dia >= data_I.dia )));

    // Le prazo da requisicao
    printf("Indique o prazo(minimo 1 dia, maximo 30 dias) que quer requisitar o portatil: ");
    dados.prazo = lerInteiro(1,30);

    // Por requisicao como ativa
    strcpy(dados.estado_Requisacao, S_ESTADO_REQ_ATIVA);

    //valor de multa , data de devolução inicializar os valores a 0
    dados.valor_Multa = 0;
    dados.data_Devolucao.ano = 0;
    dados.data_Devolucao.mes = 0;
    dados.data_Devolucao.dia = 0;

    return dados;

}

tipoRequisicao *acrescentaRequisicao(tipoPortatil vPortatil[MAX_PORTATIL], tipoRequisicao *vRequisicao,
                                     int num_Portatil, int *num_Requisicao, int *num_Requisicao_Ativa)
{
    // Variavel para guarda o endereço do vetor dinamico
    tipoRequisicao *ponteiro_Temporario;
    // Variaveeis de posiçao a PC é para portateis a R é para requisiçoes para guardar a posicao que retorna sendo que vai ser utilizada para ambos os vetores
    // Temp_id - Numero temporário para guardar ID portatil
    int pos_Pc, pos_R, temp_id;
    // Variavel temporária para guardar codigo de requisiçao
    char temp_code[MAX_CODIGO];

    do
    {
        //le num de indentificacao e verifica se o portatil existe
        printf("Insira o numero de indentificacao(1 a 9999) do portatil que quer requisitar\n");
        printf("Se quiser sair apenas insira o 0\n");
        printf("Numero do portatil: ");
        //Le o numero do portatil a requisitar
        temp_id = lerInteiro(0,9999);
        pos_Pc = procura_Portatil(vPortatil, num_Portatil, temp_id);
        //Devolve -1 caso nao encontre o portatil
        if(pos_Pc == -1)
        {
            printf("Portatil inexistente! Insira 0 para sair ou para continuar insira um numero de indentificacao do portatil: \n\n");
        }
    }
    while(temp_id !=0 && pos_Pc == -1);  // Sai quando o temp_id for 0 ou a encontrar um portatil

    if(temp_id != 0)
    {
        // Verifica se o portatil está disponivel
        if(strcmp(vPortatil[pos_Pc].estado_Pc, S_ESTADO_PC_DISPONIVEL) == 0)
        {
            //ler codigo de requisiçao e verifica se o codigo existe
            printf("Insira um codigo de maximo 10 caracteres(letras e numeros) para a requisicao\n");
            printf("Se pretender sair insira o 0\n");
            printf("codigo da Requisicao: ");
            do
            {
                lerString(temp_code, MAX_CODIGO);
                pos_R = procuraRequisicao(vRequisicao, *num_Requisicao, temp_code);
                //Devolve -1 caso o codigo nao exista
                if(pos_R != -1)
                {
                    printf("Codigo ja existe! Insira 0 para sair ou insira um codigo valido para continuar: \n");
                }
            }while(strcmp(temp_code, "0") != 0 && pos_R != -1); //Sai quando o temp_code for 0 ou o codigo nao exisitr

            if(strcmp(temp_code, "0") != 0)
            {
                //Guarda o endereço antigo, no caso de erro
                ponteiro_Temporario = vRequisicao;

                //Reserva espaço
                vRequisicao = realloc(vRequisicao, (*num_Requisicao + 1) * sizeof(tipoRequisicao));

                // Verifica se foi possivel arranjar espaço
                if(vRequisicao == NULL)
                {
                    printf("Erro!! Impossivel de reservar espaço\n");
                    // Restaurar posiçao do ponteiro
                    vRequisicao = ponteiro_Temporario;
                }
                else
                {
                    // Le os resta dos campos
                    vRequisicao[*num_Requisicao] = leRequisicao(vPortatil[pos_Pc].data_Aquisicao);
                    // Copia para dentro da estrutura o campos lidos no inicio
                    vRequisicao[*num_Requisicao].num_Indentificacao_Portatil = temp_id;
                    strcpy(vRequisicao[*num_Requisicao].codigo, temp_code);
                    //Muda o estado do pc para requsitado
                    strcpy(vPortatil[pos_Pc].estado_Pc, S_ESTADO_PC_REQUISITADO);

                    // incrementar quantidades de requisiçoes
                    vPortatil[pos_Pc].quant_Requisicoes++;

                    (*num_Requisicao)++;
                    (*num_Requisicao_Ativa)++;
                }
            }
        }
        else
        {
            printf("Portatil encontra-se atualmente requisatado ou avariado\n");
        }

    }
    return vRequisicao;
}

void listaRequisicao(tipoRequisicao *vRequisicao, int num_requisicao)
{
    // variavel para percorrer loop
    int i;
    //variavel para guardar duracao da requisicao
    int duracao_Requisicao = 0;
    //Percorre o loop e lista cada informacao do PC
    for(i = 0; i < num_requisicao; i++)
    {
        printf("\n-------------------------------Informacao da Requisicao codigo : %s", vRequisicao[i].codigo);
        printf("-------------------------------\n\n");
        if ((strcmp(vRequisicao[i].estado_Requisacao, S_ESTADO_REQ_ATIVA) == 0))
        {
            printf("Estado: %s\t\tNumero do portatil: %4d\t\t", vRequisicao[i].estado_Requisacao, vRequisicao[i].num_Indentificacao_Portatil);
            printf("Nome do utente: %s\nTipo de utente: %s\t\t", vRequisicao[i].nome_Utente, vRequisicao[i].tipo_Utente);
            printf("Data de requisicao: %2d-%2d-%4d\t\t", vRequisicao[i].data_Requisacao.dia, vRequisicao[i].data_Requisacao.mes, vRequisicao[i].data_Requisacao.ano);
            printf("Prazo da requisicao: %d\n",vRequisicao[i].prazo);
            printf("Data da devolucao: --------\t\tDuracao da requisicao: --------\t\tLocal de devolucao: --------\n");
            printf("Valor da multa: --------\n");

        }
        else
        {
            duracao_Requisicao = difenreca_Datas(vRequisicao[i].data_Requisacao, vRequisicao[i].data_Devolucao);

            printf("Estado: %s\t\tNumero do portatil: %4d\t\t", vRequisicao[i].estado_Requisacao, vRequisicao[i].num_Indentificacao_Portatil);
            printf("Nome do utente: %s\nTipo de utente: %s\t\t", vRequisicao[i].nome_Utente, vRequisicao[i].tipo_Utente);
            printf("Data de requisicao: %2d-%2d-%4d\t\t", vRequisicao[i].data_Requisacao.dia, vRequisicao[i].data_Requisacao.mes, vRequisicao[i].data_Requisacao.ano);
            printf("Prazo da requisicao: %d\n",vRequisicao[i].prazo);
            printf("Data da devolucao: %2d-%2d-%4d\t", vRequisicao[i].data_Devolucao.dia, vRequisicao[i].data_Devolucao.mes, vRequisicao[i].data_Devolucao.ano);
            printf("Duracao da requisicao: %d\t\tLocal de devolucao: %s\n", duracao_Requisicao, vRequisicao[i].local_Devolucao);
            printf("Valor da multa: %d\n", vRequisicao[i].valor_Multa);
        }
    }

}

void renovarRequisicao(tipoRequisicao *vRequisicao, int num_Requisicao)
{
    // Declara um sitio para guardar a variavel
    char temp_code[MAX_CODIGO];
    // Declara sitio para guardar a posiçao
    int pos; //temp_prazo;

    // Le a requisiçao que quer renovar
    pos = leCodigo_e_Retorna_Pos(vRequisicao, num_Requisicao, temp_code);
    // Verifica se o utilizador quer sair
    if((strcmp(temp_code, "0") != 0))
    {
        // Verificar se a requisiçao está ativa
        if(strcmp(vRequisicao[pos].estado_Requisacao, S_ESTADO_REQ_ATIVA) == 0)
        {
            printf("Insira o numero de dias(maximo 7 dias) que deseja extender a sua requisicao?\n");
            vRequisicao[pos].prazo += lerInteiro(1,7);
            //temp_prazo = lerInteiro(1,7);
            //vRequisicao[pos].prazo += temp_prazo;
        }
        else
        {
            printf("Requisicao concluida! Impossivel de renovar requisicao\n");
        }
    }
}

void mostraRequisicao(tipoRequisicao *vRequisicao, int num_Requisicao, tipoPortatil vPortatil[MAX_PORTATIL], int num_Portatil)
{
    // Declara posicao do portatil e posicao da requisicao e duraçao da requisicao
    int pos_Pc, pos_Requisicao, duracao;

    // codigo
    char code[MAX_CODIGO];

    // Le a requisiçao que quer mostrar
    pos_Requisicao = leCodigo_e_Retorna_Pos(vRequisicao, num_Requisicao, code);
    // Verifica se quer sair
    if(strcmp(code, "0") != 0)
    {
        // Procura o portatil
        pos_Pc = procura_Portatil(vPortatil, num_Portatil, vRequisicao[pos_Requisicao].num_Indentificacao_Portatil);
        printf("\n-------------------------------Informacao da Requisicao codigo : %s", vRequisicao[pos_Requisicao].codigo);
        printf("-------------------------------\n\n");
        //Se a requisiçao tiver ativa mostra sem os dados da devoluçao
        if ((strcmp(vRequisicao[pos_Requisicao].estado_Requisacao, S_ESTADO_REQ_ATIVA) == 0))
        {
            printf("Estado: %s\t\tNome do utente: %s\t\t", vRequisicao[pos_Requisicao].estado_Requisacao, vRequisicao[pos_Requisicao].nome_Utente);
            printf("Tipo de utente: %s\n", vRequisicao[pos_Requisicao].tipo_Utente);
            printf("Data de requisicao: %2d-%2d-%4d\t\t", vRequisicao[pos_Requisicao].data_Requisacao.dia, vRequisicao[pos_Requisicao].data_Requisacao.mes, vRequisicao[pos_Requisicao].data_Requisacao.ano);
            printf("Prazo da requisicao: %d\t\t",vRequisicao[pos_Requisicao].prazo);
            printf("Data da devolucao: --------\nDuracao da requisicao: --------\t\tLocal de devolucao: --------\t\t");
            printf("Valor da multa: --------\n");
            printf("\n\t\t-----------------------Informacao do Portatil N. Identificacao : %4d -----------------------\n", vPortatil[pos_Pc].num_Identificacao_PC);
            printf("\tDesignacao do portatil: %s\t\tEstado do Portatil: %s\t\t", vPortatil[pos_Pc].designacao, vPortatil[pos_Pc].estado_Pc);
            printf("Quantidade de dias Requisitados: %d", vPortatil[pos_Pc].quant_Dias_Requisitados);
        }
        else
        {
            //Calcula a duracao
            duracao = difenreca_Datas(vRequisicao[pos_Requisicao].data_Requisacao, vRequisicao[pos_Requisicao].data_Devolucao);
            //Lista os dados
            printf("Estado: %s\t\tNome do utente: %s\t\t", vRequisicao[pos_Requisicao].estado_Requisacao, vRequisicao[pos_Requisicao].nome_Utente);
            printf("Tipo de utente: %s\n", vRequisicao[pos_Requisicao].tipo_Utente);
            printf("Data de requisicao: %2d-%2d-%4d\t\t", vRequisicao[pos_Requisicao].data_Requisacao.dia, vRequisicao[pos_Requisicao].data_Requisacao.mes, vRequisicao[pos_Requisicao].data_Requisacao.ano);
            printf("Prazo da requisicao: %d\t\t",vRequisicao[pos_Requisicao].prazo);
            printf("Data da devolucao: %2d-%2d-%4d\n", vRequisicao[pos_Requisicao].data_Devolucao.dia, vRequisicao[pos_Requisicao].data_Devolucao.mes, vRequisicao[pos_Requisicao].data_Devolucao.ano);
            printf("Duracao da requisicao: %d\t\tLocal de devolucao: %s\t\t", duracao, vRequisicao[pos_Requisicao].local_Devolucao);
            printf("Valor da multa: %d\n", vRequisicao[pos_Requisicao].valor_Multa);
            printf("\n\t\t-----------------------Informacao do Portatil N. Identificacao : %4d -----------------------\n", vPortatil[pos_Pc].num_Identificacao_PC);
            printf("\tDesignacao do portatil: %s\t\tEstado do Portatil: %s\t\t", vPortatil[pos_Pc].designacao, vPortatil[pos_Pc].estado_Pc);
            printf("Quantidade de dias Requisitados: %d", vPortatil[pos_Pc].quant_Dias_Requisitados);
        }
    }
}
