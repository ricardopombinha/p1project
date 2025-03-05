#ifndef FUNCAOLERAUXILIAR_H_INCLUDED
#define FUNCAOLERAUXILIAR_H_INCLUDED

#include "constantes.h"


int lerInteiro(int minimo, int maximo);
float lerFloat(float minimo, float maximo);
void lerString(char vetorCaracteres[], int maximoCaracteres);
void limpaBufferStdin(void);
void lerData(tipoData *data);
int difenreca_Datas(tipoData data_I, tipoData data_F);


#endif // FUNCAOLERAUXILIAR_H_INCLUDED
