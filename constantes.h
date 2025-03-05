#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

#define MAX_CHARS_STRING 80
#define MAX_CODIGO 11
#define MAX_PORTATIL 30
#define MAX_PROCESSADOR 3
#define MAX_LOCAL_AVARIA_ESTADOS_PC 12
#define MAX_UTENTE 23
#define MAX_ESTADO_REQUESICAO 10
#define MENOR_ANO 2012
#define MAIOR_ANO 2023
#define S_RESIDENCIAS "Residencias"
#define S_CAMPUS1 "Campus1"
#define S_CAMPUS2 "Campus2"
#define S_CAMPUS5 "Campus5"
#define S_ESTADO_PC_DISPONIVEL "Disponivel"
#define S_ESTADO_PC_REQUISITADO "Requisitado"
#define S_ESTADO_PC_AVARIADO "Avariado"
#define S_ESTADO_REQ_ATIVA "Ativa"
#define S_ESTADO__REQ_CONCLUIDA "Concluida"
#define S_UTENTE_ESTUDANTE "Estudante"
#define S_UTENTE_DOCENTE "Docente"
#define S_UTENTE_TECNICO "Tecnico administrativo"
#define S_I3 "i3"
#define S_I5 "i5"
#define S_I7 "i7"

typedef struct
{
    int dia;
    int mes;
    int ano;
} tipoData;

typedef struct
{
    int num_Identificacao_PC;
    char designacao[MAX_CHARS_STRING];
    char processador[MAX_PROCESSADOR];
    int ram;
    // Estados dos pcs (disponivel, requisitado, avariado)
    char estado_Pc[MAX_LOCAL_AVARIA_ESTADOS_PC];
    // Localização dos pcs (residencias, Campus1, Campus2, Campus5)
    char localizacao[MAX_LOCAL_AVARIA_ESTADOS_PC];
    tipoData data_Aquisicao;
    float Valor_Equipamento;
    int quant_Avarias;
    int quant_Requisicoes;
    int quant_Dias_Requisitados;

} tipoPortatil;

typedef struct
{
    char codigo[MAX_CODIGO];
    int num_Indentificacao_Portatil;
    char nome_Utente[MAX_CHARS_STRING];
    // Tipos do utente (estudante, docente, técnico administrativo)
    char tipo_Utente[MAX_UTENTE];
    tipoData data_Requisacao;
    int prazo;
    // Estado de requisição (ativa,concluida)
    char estado_Requisacao[MAX_ESTADO_REQUESICAO];
    // Localização dos pcs (residencias, Campus1, Campus2, Campus5)
    char local_Devolucao[MAX_LOCAL_AVARIA_ESTADOS_PC];
    tipoData data_Devolucao;
    int valor_Multa;

} tipoRequisicao;

typedef struct
{
    int num_Indentificacao_PC;
    // Tipos de avaria (1--> temporária ou 2--> permantente)
    int tipo_Avaria;
    tipoData data_Avaria;
    tipoData data_Reparacao;
    int duracao_avaria;
} tipoAvaria;

#endif // CONSTANTES_H_INCLUDED
