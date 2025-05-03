#include "include/Locomotiva.h"
#include "include/config.h"
#include "include/Vagao.h"

Locomotiva createLocomotiva(int id, float peso_maximo, float peso) {
    /*
    Cria uma locomotiva com os dados fornecidos.
    id: ID da locomotiva.
    peso_maximo: Peso máximo que a locomotiva pode suportar.
    peso_atual: Peso atual da locomotiva.
    peso: Peso da locomotiva.
    Retorna uma estrutura Locomotiva preenchida com os dados fornecidos.
    */
    Locomotiva locomotiva;
    locomotiva.id = id;
    locomotiva.peso_maximo = peso_maximo;
    locomotiva.peso = peso;
    locomotiva.peso_atual = peso;
    locomotiva.vagoes = (Vagoes*)malloc(sizeof(Vagoes));
    inicializaVagoes(locomotiva.vagoes);
    return locomotiva;
}

void inicializaListaLocomotivas(ListaLocomotivas* locomotivas){
    /*
    Inicializa a lista de locomotivas, definindo o primeiro e o último elemento como NULL.
    locomotivas: ponteiro para a estrutura ListaLocomotivas a ser inicializada.
    */
    locomotivas->primeiro = NULL;
    locomotivas->ultimo = NULL;
}

Locomotivas* buscaLocomotiva(ListaLocomotivas* locomotivas, int id){
    /*
    Busca uma locomotiva na lista de locomotivas pelo ID.
    locomotivas: ponteiro para a estrutura ListaLocomotivas onde a locomotiva será buscada.
    id: ID da locomotiva a ser buscada.
    Se a locomotiva for encontrada, retorna um ponteiro para a locomotiva encontrada.
    */
    Locomotivas* temp = locomotivas->primeiro;
    while(temp != NULL) {
        if(temp->locomotiva.id == id) {
            return temp;
        }
        temp = temp->proximo;
    }
    return NULL;
}

Locomotivas* buscaAnteriorLocomotiva(ListaLocomotivas* locomotivas, int id){
    /*
    Busca o elemento anterior a uma locomotiva na lista de locomotivas pelo ID.
    locomotivas: ponteiro para a estrutura ListaLocomotivas onde a locomotiva será buscada.
    id: ID da locomotiva a ser buscada.
    Se a locomotiva for encontrada, retorna um ponteiro para o elemento anterior.
    */
    Locomotivas* temp = locomotivas->primeiro;
    if(temp == NULL) {
        return NULL;
    }
    while(temp->proximo != NULL) {
        if(temp->proximo->locomotiva.id == id) {
            return temp;
        }
        temp = temp->proximo;
    }
    return NULL;
}

int addLocomotiva(ListaLocomotivas* locomotivas, Locomotiva locomotiva){
    /*
    Adiciona uma locomotiva à lista de locomotivas.
    Se a locomotiva já existir na lista, uma mensagem de erro é exibida.
    locomotivas: ponteiro para a estrutura ListaLocomotivas onde a locomotiva será adicionada.
    locomotiva: estrutura Locomotiva a ser adicionada.
    */
    if(locomotiva.peso_atual > locomotiva.peso_maximo) {
        printf("Peso atual maior que o peso maximo!!!\n");
        return 0;
    }
    if(buscaLocomotiva(locomotivas, locomotiva.id) != NULL) {
        printf("Locomotiva com ID %d ja existe!\n", locomotiva.id);
        return 0;
    }
    Locomotivas* novaLocomotiva = (Locomotivas*)malloc(sizeof(Locomotivas));
    novaLocomotiva->locomotiva = locomotiva;
    novaLocomotiva->proximo = NULL;

    if (locomotivas->primeiro == NULL) {
        locomotivas->primeiro = novaLocomotiva;
        locomotivas->ultimo = novaLocomotiva;
    } else {
        locomotivas->ultimo->proximo = novaLocomotiva;
        locomotivas->ultimo = novaLocomotiva;
    }
    return 1;
}

int addVagaoLocomotiva(ListaLocomotivas* locomotivas, int idLocomotiva, Vagao vagao, int posicao){
    /*
    Adiciona um vagão a uma locomotiva na lista de locomotivas.
    Se a locomotiva não for encontrada, uma mensagem de erro é exibida.
    Se o vagão já existir na lista, uma mensagem de erro é exibida.
    locomotivas: ponteiro para a estrutura ListaLocomotivas onde a locomotiva será encontrada.
    idLocomotiva: ID da locomotiva onde o vagão será adicionado.
    vagao: estrutura Vagao a ser adicionada.
    posicao: posição onde o vagão será adicionado (INICIO, FIM ou uma posição específica).
    */
    Locomotivas* locomotiva = buscaLocomotiva(locomotivas, idLocomotiva);
    if(locomotiva == NULL) {
        printf("Locomotiva nao encontrada!\n");
        return 0;
    }

    if((vagao.dados.carga.peso_atual + locomotiva->locomotiva.peso_atual) > locomotiva->locomotiva.peso_maximo || (vagao.dados.passageiro.peso_atual + locomotiva->locomotiva.peso_atual) > locomotiva->locomotiva.peso_maximo){
        printf("Peso maximo da locomotiva excedido!\n");
        printf("Peso até o máximo: %.2f\n", locomotiva->locomotiva.peso_maximo - locomotiva->locomotiva.peso_atual);
        return 0;
    }
    if(addVagao(locomotiva->locomotiva.vagoes, vagao, posicao)){
        locomotiva->locomotiva.peso_atual += vagao.tipo == CARGA ? vagao.dados.carga.peso_atual : vagao.dados.passageiro.peso_atual;
        return 1;
    }
    return 0;
}

int removeLocomotiva(ListaLocomotivas* locomotivas, int id){
    /*
    Remove uma locomotiva da lista de locomotivas pelo ID.
    Se a locomotiva não for encontrada, uma mensagem de erro é exibida.
    */
    Locomotivas* temp = locomotivas->primeiro;
    if(temp->locomotiva.id == id) {
        locomotivas->primeiro = temp->proximo;
        liberaVagoes(temp->locomotiva.vagoes);
        free(temp);
        return 1;
    }
    temp = buscaAnteriorLocomotiva(locomotivas, id);
    if(temp == NULL) {
        printf("Locomotiva com ID %d nao encontrada!\n", id);
        return 0;
    }
    Locomotivas* temp2 = temp->proximo;
    temp->proximo = temp2->proximo;
    if(temp2 == locomotivas->ultimo) {
        locomotivas->ultimo = temp;
    }
    liberaVagoes(temp2->locomotiva.vagoes);
    free(temp2);
    return 1;
}

void imprimeVagoesComLocomotiva(Vagoes* vagoes){
    /*
    Imprime os detalhes de todos os vagões na lista de vagões.
    Se o vagão for do tipo CARGA, imprime os detalhes da carga. Se for do tipo PASSAGEIRO, imprime os detalhes do passageiro.
    vagoes: ponteiro para a estrutura Vagoes a ser impressa.
    */
    Vagao* temp = vagoes->primeiro;
    while (temp != NULL) {
        if(temp->tipo == CARGA) {
            printf("\tVagao de Carga ID: %d, Carga: %s, Peso Maximo: %.2f, Peso Atual: %.2f\n",
                   temp->dados.carga.id, temp->dados.carga.carga,
                   temp->dados.carga.peso_maximo, temp->dados.carga.peso_atual);
        }else if(temp->tipo == PASSAGEIRO) {
            printf("\tVagao de Passageiros ID: %d, Assentos: %d, Peso Maximo: %d, Peso Atual: %d\n",
                   temp->dados.passageiro.id, temp->dados.passageiro.assentos,
                   temp->dados.passageiro.peso_maximo, temp->dados.passageiro.peso_atual);
        }
        temp = temp->proximo;
    }
}

void imprimeLocomotivas(ListaLocomotivas* locomotivas){
    /*
    Imprime os detalhes de todas as locomotivas na lista de locomotivas.
    Se a locomotiva não for encontrada, uma mensagem de erro é exibida.
    */
    Locomotivas* temp = locomotivas->primeiro;
    while (temp != NULL) {
        printf("Locomotiva ID: %d, Peso Maximo: %.2f, Peso Atual: %.2f, Peso: %.2f\n",
               temp->locomotiva.id, temp->locomotiva.peso_maximo,
               temp->locomotiva.peso_atual, temp->locomotiva.peso);
        imprimeVagoesComLocomotiva(temp->locomotiva.vagoes);
        temp = temp->proximo;
    }
}

void liberaLocomotivas(ListaLocomotivas* locomotivas){
    /*
    Libera a memória alocada para a lista de locomotivas.
    */
    Locomotivas* temp = locomotivas->primeiro;
    while (temp != NULL) {
        Locomotivas* proximo = temp->proximo;
        liberaVagoes(temp->locomotiva.vagoes);
        free(temp);
        temp = proximo;
    }
    locomotivas->primeiro = NULL;
    locomotivas->ultimo = NULL;
}

int removeVagaoLocomotiva(ListaLocomotivas* locomotivas, int idLocomotiva, int idVagao){
    /*
    Remove um vagão de uma locomotiva na lista de locomotivas pelo ID.
    Se a locomotiva não for encontrada, uma mensagem de erro é exibida.
    Se o vagão não for encontrado, uma mensagem de erro é exibida.
    */
    Locomotivas* locomotiva = buscaLocomotiva(locomotivas, idLocomotiva);
    if(locomotiva == NULL) {
        printf("Locomotiva nao encontrada!\n");
        return 0;
    }
    if(removeVagao(locomotiva->locomotiva.vagoes, idVagao)){
        return 1;
    }
    printf("Vagao com ID %d nao encontrado!\n", idVagao);
    return 0;
}

int trocarVagoes(Locomotivas* locomotiva, Vagao* vagao1, Vagao* vagao2){
    /*
    Troca dois vagões de uma locomotiva.
    Se os vagões forem iguais, uma mensagem de erro é exibida.
    */
    if(vagao1 == vagao2) return 0;
    
    Vagao* temp = vagao1;
    while(temp!=vagao2 && temp) temp = temp->proximo;
    int vagao1Antes = (temp == vagao2);
    if (!vagao1Antes){
        temp = vagao1;
        vagao1 = vagao2;
        vagao2 = temp;
    }
    
    if(vagao1->proximo = vagao2){
        if(vagao1->anterior) vagao1->anterior = vagao2;
        else locomotiva->locomotiva.vagoes->primeiro = vagao2;
        
        if(vagao1->proximo) vagao1->proximo->anterior = vagao2;
        else locomotiva->locomotiva.vagoes->ultimo = vagao2;

        vagao1->proximo = vagao2->proximo;
        vagao2->anterior = vagao1->anterior;

        vagao1->anterior = vagao2;
        vagao2->proximo = vagao1;
    }else{
        Vagao* anterior1 = vagao1->anterior;
        Vagao* proximo1 = vagao1->proximo;
        Vagao* anterior2 = vagao2->anterior;
        Vagao* proximo2 = vagao2->proximo;

        if(anterior1) anterior1->proximo = vagao2;
        else locomotiva->locomotiva.vagoes->primeiro = vagao2;
        if(proximo1) proximo1->anterior = vagao2;
        else locomotiva->locomotiva.vagoes->ultimo = vagao2;

        if(anterior2) anterior2->proximo = vagao1;
        else locomotiva->locomotiva.vagoes->primeiro = vagao1;
        if(proximo2) proximo2->anterior = vagao1;
        else locomotiva->locomotiva.vagoes->ultimo = vagao1; 
        
        vagao1->proximo = proximo2;
        vagao1->anterior = anterior2;
        vagao2->proximo = proximo1;
        vagao2->anterior = anterior1;
        
    }
}

int trocarVagoesLocomotiva(ListaLocomotivas* locomotivas, int idLocomotiva, int idVagao1, int idVagao2){
    /*
    Troca dois vagões de uma locomotiva na lista de locomotivas pelo ID.
    Se a locomotiva não for encontrada, uma mensagem de erro é exibida.
    Se os vagões não forem encontrados, uma mensagem de erro é exibida.
    */
    Locomotivas* locomotiva = buscaLocomotiva(locomotivas, idLocomotiva);
    if(locomotiva == NULL) {
        printf("Locomotiva nao encontrada!\n");
        return 0;
    }
    Vagao* vagao1 = buscaVagao(locomotiva->locomotiva.vagoes, idVagao1);
    Vagao* vagao2 = buscaVagao(locomotiva->locomotiva.vagoes, idVagao2);
    if(vagao1 == NULL || vagao2 == NULL) {
        printf("Um ou ambos os vagoes nao encontrados!\n");
        return 0;
    }
    // Troca os dados dos vagões
    return trocarVagoes(locomotiva, vagao1, vagao2);
}
