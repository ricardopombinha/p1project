#ifndef FUNCOESAVARIA_H_INCLUDED
#define FUNCOESAVARIA_H_INCLUDED


#include "constantes.h"
#include "funcoesrequisicao.h"
#include "funcoesDevolucoes.h"


void reparacao(tipoPortatil vPortatil[MAX_PORTATIL], int quant_portatil, tipoAvaria *vAvaria, int quant_avaria, int *quant_Avaria_Ativas);
int procura_Avaria(tipoAvaria *vAvaria, int quant_avaria, int id_Portatil);
tipoAvaria *acrescentaAvaria(tipoPortatil *portatil, tipoAvaria *vAvaria, int *quant_Avaria, int *quant_Avaria_Ativas, int num_Id, tipoData data, int *confirma_Avaria);
void listagem_Avaria(tipoPortatil vPortatil[MAX_PORTATIL], int quant_portatil, tipoAvaria *vAvaria, int quant_Avaria);
tipoAvaria *avaria_Inicial(tipoPortatil vPortatil[MAX_PORTATIL], int quant_portatil, tipoRequisicao *vRequisicao, int quant_Requisicao, tipoAvaria *vAvaria,
                           int *quant_Avaria, int *quant_Avaria_Ativas, int *quant_Requisicao_Ativa);


#endif // FUNCOESAVARIA_H_INCLUDED
