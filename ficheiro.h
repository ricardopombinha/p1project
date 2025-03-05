#ifndef FICHEIRO_H_INCLUDED
#define FICHEIRO_H_INCLUDED

#include "constantes.h"
#include "funcoesportateis.h"
#include "funcoesrequisicao.h"


// README/README
// README/README
// README/README
// Temos de discutir se vamos querer gravar tambem o vetor de avaria ou onde a informaçao da avaria
// Atualmente nao tenho na função mas se for preciso a mudança é facil;
void gravaFicheiroBinario(tipoPortatil vetorPortatil[MAX_PORTATIL], tipoRequisicao *vetorRequisicao, int quant_Portatil, int quant_Requisicao, int quant_Requisicao_Ativas);
tipoRequisicao *leFicheiroBinario(tipoPortatil vetorPortatil[MAX_PORTATIL], tipoRequisicao *vetorRequisicao, int *quant_Portatil, int *quant_requisicao, int *quant_Requisicao_Ativas, int *confirma);
void gravaFicheiroLog(tipoRequisicao vRequisicao, tipoPortatil *vPortatil);
void gravaFicheiroBinarioAvarias(tipoAvaria *vAvaria, int quant_Avarias, int quant_Avarias_Ativas);
tipoAvaria *leFicheiroBinarioAvarias(tipoAvaria *vAvaria, int *quant_Avarias, int *quant_Avarias_Ativas);

#endif // FICHEIRO_H_INCLUDED
