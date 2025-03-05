#ifndef FUNCOESESTATISTICAS_H_INCLUDED
#define FUNCOESESTATISTICAS_H_INCLUDED

#include "constantes.h"
#include "funcoesrequisicao.h"


void custo_Medio(tipoRequisicao *vRequisicao, int quant_Requisicao);
void estatisticasPORTATIL(tipoPortatil vPortatil[MAX_PORTATIL], int quant_Portatil);
void estatisticasTipoRequisicao(tipoRequisicao *vRequisicao, int quant_Requisicao);
void devolucoes_Recentes(tipoRequisicao *vRequisicao, int quant_Requisicao);

#endif // FUNCOESESTATISTICAS_H_INCLUDED
