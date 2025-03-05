#ifndef FUNCOESPORTATEIS_H_INCLUDED
#define FUNCOESPORTATEIS_H_INCLUDED


#include "constantes.h"
#include "funcaoLerAuxiliar.h"

int inserir_Portatil(tipoPortatil vPortatil[MAX_PORTATIL],int quant_Portatil);
void listarPortateis(tipoPortatil vPortatil[MAX_PORTATIL], int quant_Portatil, tipoRequisicao *vRequisicao, int quant_Requisicao);
//Funcao que procura o portatil pelo seu numero de identificacao e devolve a posicao em que se encontra
int procura_Portatil(tipoPortatil vPortatil[MAX_PORTATIL], int quant_Portatil, int num_ID);
void alterar_local(tipoPortatil vPortatil[MAX_PORTATIL], int quant_Portatil);

#endif // FUNCOESPORTATEIS_H_INCLUDED
