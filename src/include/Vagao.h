#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

#ifndef VAGAO_H
#define VAGAO_H

typedef struct Vagao Vagao;
typedef struct VagaoCarga VagaoCarga;
typedef struct VagaoPassageiro VagaoPassageiro;
typedef struct Vagoes Vagoes;

struct VagaoCarga{
    int id;
    char carga[50];
    float peso_maximo;
    float peso_atual;
};

struct VagaoPassageiro{
    int id;
    int assentos;
    int peso_maximo;
    int peso_atual;    
};

struct Vagao{
    int tipo;
    union{
        VagaoCarga carga;
        VagaoPassageiro passageiro;
    }dados;
    Vagao* proximo;
    Vagao* anterior;
};

struct Vagoes{
    Vagao* primeiro;
    Vagao* ultimo;
    int quantidade;
};

Vagao createVagao(int tipo);
void inicializaVagoes(Vagoes* vagoes);
int addVagao(Vagoes* vagoes, Vagao vagao, int posicao);
int removeVagao(Vagoes* vagoes, int id);
void imprimeVagoes(Vagoes* vagoes);
void liberaVagoes(Vagoes* vagoes);
Vagao* buscaVagao(Vagoes* vagoes, int id);

#endif // VAGAO_H