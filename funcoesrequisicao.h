#ifndef FUNCOESREQUISICAO_H_INCLUDED
#define FUNCOESREQUISICAO_H_INCLUDED

#include "constantes.h"
#include "funcoesportateis.h"


int procuraRequisicao(tipoRequisicao *vRequisicao, int num_Requisicao, char code_string[MAX_CODIGO]);
int leCodigo_e_Retorna_Pos(tipoRequisicao *vRequisicao, int num_Requisicao, char code[MAX_CODIGO]);
tipoRequisicao leRequisicao(tipoData data_I);
tipoRequisicao *acrescentaRequisicao(tipoPortatil vPortatil[MAX_PORTATIL], tipoRequisicao *vRequisacao,
                                     int num_Portatil, int *num_Requisicao, int *num_Requisicao_Ativa);
void listaRequisicao(tipoRequisicao *vRequisicao, int num_requisicao);
void renovarRequisicao(tipoRequisicao *vRequisicao, int num_requisicao);
void mostraRequisicao(tipoRequisicao *vRequisicao, int num_Requisicao, tipoPortatil vPortatil[MAX_PORTATIL], int num_Portatil);

#endif // FUNCOESREQUISICAO_H_INCLUDED
