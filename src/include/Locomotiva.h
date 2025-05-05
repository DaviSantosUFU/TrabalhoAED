#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Vagao.h"

#ifndef LOCOMOTIVA_H
#define LOCOMOTIVA_H

typedef struct Locomotivas Locomotivas;
typedef struct Locomotiva Locomotiva;
typedef struct ListaLocomotivas ListaLocomotivas;

struct Locomotiva{
    int id;
    float peso_maximo;
    float peso;
    float peso_atual;
    Vagoes* vagoes;
};

struct Locomotivas{
    Locomotiva locomotiva;
    Locomotivas* proximo;
};

struct ListaLocomotivas{
    Locomotivas* primeiro;
    Locomotivas* ultimo;
};

Locomotiva createLocomotiva(int id, float peso_maximo, float peso);
Locomotivas* buscaLocomotiva(ListaLocomotivas* locomotivas, int id);
void inicializaListaLocomotivas(ListaLocomotivas* locomotivas);
int addLocomotiva(ListaLocomotivas* locomotivas, Locomotiva locomotiva);
int addVagaoLocomotiva(ListaLocomotivas* locomotivas, int idLocomotiva, Vagao vagao, int posicao);
int removeLocomotiva(ListaLocomotivas* locomotivas, int id);
void imprimeLocomotivas(ListaLocomotivas* locomotivas);
void liberaLocomotivas(ListaLocomotivas* locomotivas);
int removeVagaoLocomotiva(ListaLocomotivas* locomotivas, int idLocomotiva, int idVagao);
int trocarVagoesLocomotiva(ListaLocomotivas* locomotivas, int idLocomotiva, int idVagao1, int idVagao2);

#endif // LOCOMOTIVA_H