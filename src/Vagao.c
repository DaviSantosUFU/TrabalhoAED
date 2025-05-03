#include "include/Vagao.h"
#include "include/config.h"

Vagao createVagao(int tipo) {
    /*
    Cria um vagão com base no tipo especificado (CARGA ou PASSAGEIRO).
    Se o tipo for inválido, uma mensagem de erro é exibida e nada é retornado.
    tipo: tipo do vagão a ser criado (CARGA ou PASSAGEIRO).
    Retorna uma estrutura Vagao preenchida com os dados do vagão.
    */
    Vagao vagao;
    if (tipo == CARGA) {
        vagao.tipo = CARGA;
        printf("\nDigite o ID do vagão de carga: ");
        scanf("%d", &vagao.dados.carga.id);
        printf("\nDigite o tipo de carga: ");
        scanf("%s", vagao.dados.carga.carga);
        printf("\nDigite o peso máximo da carga: ");
        scanf("%f", &vagao.dados.carga.peso_maximo);
        printf("\nDigite o peso atual da carga: ");
        scanf("%f", &vagao.dados.carga.peso_atual);
    } else if (tipo == PASSAGEIRO) {
        vagao.tipo = PASSAGEIRO;
        printf("\nDigite o ID do vagão de passageiros: ");
        scanf("%d", &vagao.dados.passageiro.id);
        printf("\nDigite o número de assentos: ");
        scanf("%d", &vagao.dados.passageiro.assentos);
        printf("\nDigite o peso máximo do vagão: ");
        scanf("%d", &vagao.dados.passageiro.peso_maximo);
        printf("\nDigite o peso atual do vagão: ");
        scanf("%d", &vagao.dados.passageiro.peso_atual);
    } else {
        printf("Tipo de vagao invalido!\n");
    }
    return vagao;
}

int vagaoExiste(Vagoes* vagoes, int id){
    /*
    Verifica se um vagão existe na lista de vagões pelo ID.
    Retorna 1 se existir, 0 caso contrário.
    vagoes: ponteiro para a estrutura Vagoes onde o vagão será verificado.
    id: ID do vagão a ser verificado.
    */
    Vagao* temp = vagoes->primeiro;
    while (temp != NULL) {
        if(temp->dados.carga.id == id || temp->dados.passageiro.id == id) {
            return 1; // Vagão existe
        }
        temp = temp->proximo;
    }
    return 0; // Vagão não existe
}

Vagao* buscaVagao(Vagoes* vagoes, int id) {
    /*
    Busca um vagão na lista de vagões pelo ID.
    Retorna um ponteiro para o vagão encontrado ou NULL se não encontrado.
    */
    Vagao* temp = vagoes->primeiro;
    while (temp != NULL) {
        if(temp->dados.carga.id == id || temp->dados.passageiro.id == id) {
            return temp;
        }
        temp = temp->proximo;
    }
    return NULL;
}

void inicializaVagoes(Vagoes* vagoes) {
    /*
    Inicializa a lista de vagões, definindo o primeiro e o último vagão como NULL e a quantidade como 0.
    vagoes: ponteiro para a estrutura Vagoes a ser inicializada.
    */
    vagoes->primeiro = NULL;
    vagoes->ultimo = NULL;
    vagoes->quantidade = 0;
}

int addVagao(Vagoes* vagoes, Vagao vagao, int posicao){
    /*
    Adiciona um vagão à lista de vagões na posição especificada.
    Se a posição for INICIO, o vagão é adicionado no início da lista. Se a posição for FIM, o vagão é adicionado no final da lista.
    Caso contrário, o vagão é adicionado na posição especificada.
    Se a posição for inválida, uma mensagem de erro é exibida.
    Se o vagão já existir na lista, uma mensagem de erro é exibida.
    vagoes: ponteiro para a estrutura Vagoes onde o vagão será adicionado.
    vagao: estrutura Vagao a ser adicionada.
    posicao: posição onde o vagão será adicionado (INICIO, FIM ou uma posição específica).
    */
    if(vagao.dados.carga.peso_atual > vagao.dados.carga.peso_maximo || vagao.dados.passageiro.peso_atual > vagao.dados.passageiro.peso_maximo) {
        printf("Peso atual maior que o peso maximo!!!\n");
    return 0;
    }
    if(posicao < INICIO || posicao > vagoes->quantidade) {
        printf("Posicao invalida!\n");
        return 0;
    }
    int id = vagao.tipo == CARGA ? vagao.dados.carga.id : vagao.dados.passageiro.id;
    if(vagaoExiste(vagoes, vagao.dados.carga.id) || vagaoExiste(vagoes, vagao.dados.passageiro.id)) {
        printf("Vagao com ID %d ja existe!\n", id);
        return 0;
    }
    Vagao* novoVagao = (Vagao*)malloc(sizeof(Vagao));
    *novoVagao = vagao;
    novoVagao->proximo = NULL;
    novoVagao->anterior = NULL;
    if (vagoes->primeiro == NULL) {
        vagoes->primeiro = novoVagao;
        vagoes->ultimo = novoVagao;
    } else{
        if(posicao == INICIO){
            novoVagao->proximo = vagoes->primeiro;
            vagoes->primeiro->anterior = novoVagao;
            vagoes->primeiro = novoVagao;
            vagoes->quantidade++;
            return 1;
        }

        if(posicao == FIM){
            vagoes->ultimo->proximo = novoVagao;
            novoVagao->anterior = vagoes->ultimo;
            vagoes->ultimo = novoVagao;
            vagoes->quantidade++;
            return 1;
        }

        Vagao* temp = vagoes->primeiro;
        for(int i = 0; i < posicao - 1; i++) {
            temp = temp->proximo;
        }
        novoVagao->proximo = temp;
        novoVagao->anterior = temp->anterior;
        temp->anterior->proximo = novoVagao;
        temp->anterior = novoVagao;
        if(novoVagao->anterior == NULL) {
            vagoes->primeiro = novoVagao;
        }
        if(novoVagao->proximo == NULL) {
            vagoes->ultimo = novoVagao;
        }

    }
    vagoes->quantidade++;
    return 1;
}

int removeVagao(Vagoes* vagoes, int id){
    /*
    Remove um vagão da lista de vagões pelo ID.
    Se o vagão não for encontrado, uma mensagem de erro é exibida.
    */
    Vagao* temp = buscaVagao(vagoes, id);
    if (temp == NULL) {
        printf("Vagao com ID %d nao encontrado!\n", id);
        return 0;
    }
    if (temp->anterior != NULL) {
        temp->anterior->proximo = temp->proximo;
    } else {
        vagoes->primeiro = temp->proximo;
    }
    if (temp->proximo != NULL) {
        temp->proximo->anterior = temp->anterior;
    } else {
        vagoes->ultimo = temp->anterior;
    }
    free(temp);
    vagoes->quantidade--;
    return 1;
}

void imprimeVagoes(Vagoes* vagoes){
    /*
    Imprime os detalhes de todos os vagões na lista de vagões.
    Se o vagão for do tipo CARGA, imprime os detalhes da carga. Se for do tipo PASSAGEIRO, imprime os detalhes do passageiro.
    vagoes: ponteiro para a estrutura Vagoes a ser impressa.
    */
    Vagao* temp = vagoes->primeiro;
    while (temp != NULL) {
        if(temp->tipo == CARGA) {
            printf("Vagao de Carga ID: %d, Carga: %s, Peso Maximo: %.2f, Peso Atual: %.2f\n",
                   temp->dados.carga.id, temp->dados.carga.carga,
                   temp->dados.carga.peso_maximo, temp->dados.carga.peso_atual);
        }else if(temp->tipo == PASSAGEIRO) {
            printf("Vagao de Passageiros ID: %d, Assentos: %d, Peso Maximo: %d, Peso Atual: %d\n",
                   temp->dados.passageiro.id, temp->dados.passageiro.assentos,
                   temp->dados.passageiro.peso_maximo, temp->dados.passageiro.peso_atual);
        }
        temp = temp->proximo;
    }
}


void liberaVagoes(Vagoes* vagoes){
    /*
    Libera a memória alocada para a lista de vagões.
    vagoes: ponteiro para a estrutura Vagoes a ser liberada.
    */
    Vagao* temp = vagoes->primeiro;
    while (temp != NULL) {
        Vagao* proximo = temp->proximo;
        free(temp);
        temp = proximo;
    }
    vagoes->primeiro = NULL;
    vagoes->ultimo = NULL;
    vagoes->quantidade = 0;
}