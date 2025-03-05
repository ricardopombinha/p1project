#ifndef FUNCOESDEVOLUCOES_H_INCLUDED
#define FUNCOESDEVOLUCOES_H_INCLUDED

#include "constantes.h"
#include "funcoesportateis.h"
#include "funcoesrequisicao.h"
#include "funcoesAvaria.h"
#include "ficheiro.h"


tipoAvaria *devolucoes(tipoPortatil vPortatil[MAX_PORTATIL], tipoRequisicao *vRequisicao, int quant_Portatil, int quant_Requisicao,
                        tipoAvaria *vAvaria, int *quant_Avaria, int *quant_Avaria_Ativas, int *quant_Requisicao_Ativa);
// Se o modo for 1 é muda o estado do portatil para disponivel
// Se o modo for 0 deixa o estado do portatil como chega
void devolverPortatil(tipoPortatil *vPortatil, tipoRequisicao *vRequisicao, tipoData data, int modo);

#endif // FUNCOESDEVOLUCOES_H_INCLUDED
