#include "include/Vagao.h"
#include "include/Locomotiva.h"
#include "include/config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void imprimeMenu(){
    /*
    Imprime o menu de opções para o usuário.
    Retorna a opção escolhida pelo usuário.
    */
    printf("\nEscolha uma opcao:\n");
    printf("1. Adicionar Locomotiva\n");
    printf("2. Adicionar Vagao\n");
    printf("3. Remover Locomotiva\n");
    printf("4. Remover Vagao\n");
    printf("5. Imprimir Locomotivas\n");
    printf("6. Imprimir Vagoes\n");
    printf("7. Trocar Vagões\n");
    printf("0. Sair\n");
}

void menu(){
    /*
    Função que exibe o menu principal do programa e processa as opções escolhidas pelo usuário.
    Inicializa a lista de locomotivas e chama as funções correspondentes às opções escolhidas.
    */
    int opcao;
    ListaLocomotivas locomotivas;
    inicializaListaLocomotivas(&locomotivas);
    int id, idLocomotiva, tipo, posicao, idVagao, idvagao1, idvagao2;
    float peso_maximo, peso;
    do{
        system("cls");
        imprimeMenu();
        scanf("%d", &opcao);
        switch(opcao){
            case 1:         
                printf("\nDigite o ID da locomotiva: ");
                scanf("%d", &id);
                printf("\nDigite o peso maximo da locomotiva: ");
                scanf("%f", &peso_maximo);
                printf("\nDigite o peso da locomotiva: ");
                scanf("%f", &peso);
                Locomotiva locomotiva = createLocomotiva(id, peso_maximo, peso);
                if(addLocomotiva(&locomotivas, locomotiva)){
                    printf("\nLocomotiva adicionada com sucesso!\n");
                }
                system("pause");
                break;
            case 2:
                printf("\nDigite o ID da locomotiva: ");
                scanf("%d", &idLocomotiva);
                Locomotivas* locomotivaEncontrada = buscaLocomotiva(&locomotivas, idLocomotiva);
                if(locomotivaEncontrada == NULL) {
                    printf("Locomotiva com ID %d nao encontrada!\n", idLocomotiva);
                    system("pause");
                    break;
                }
                printf("\nDigite o tipo do vagao (1 - CARGA, 2 - PASSAGEIRO): ");
                scanf("%d", &tipo);
                Vagao vagao = createVagao(tipo);
                printf("\nDigite a posicao para adicionar o vagao (-1 - INICIO, 0 - FIM, ? - POSIÇÃO DESEJADA): ");
                scanf("%d", &posicao);
                if(addVagaoLocomotiva(&locomotivas, idLocomotiva, vagao, posicao)){
                    printf("\nVagao adicionado com sucesso!\n");
                }
                system("pause");
                break;
            case 3:
                printf("\nDigite o ID da locomotiva a ser removida: ");
                scanf("%d", &id);
                if(removeLocomotiva(&locomotivas, id)){
                    printf("\nLocomotiva removida com sucesso!\n");
                }
                system("pause");
                break;
            case 4:
                printf("\nDigite o ID da locomotiva: ");
                scanf("%d", &id);
                printf("\nDigite o ID do vagao a ser removido: ");
                scanf("%d", &idVagao);
                if(removeVagaoLocomotiva(&locomotivas, id, idVagao)){
                    printf("\nVagao removido com sucesso!\n");
                }
                system("pause");
                break;
            case 5:
                printf("\nLocomotivas:\n");
                imprimeLocomotivas(&locomotivas);
                system("pause");
                break;
            case 6:
                printf("Digite o ID da locomotiva: ");
                scanf("%d", &idLocomotiva);
                locomotivaEncontrada = buscaLocomotiva(&locomotivas, idLocomotiva);
                if(locomotivaEncontrada == NULL) {
                    printf("Locomotiva com ID %d nao encontrada!\n", idLocomotiva);
                    system("pause");
                    break;
                }
                imprimeVagoes(locomotivaEncontrada->locomotiva.vagoes);
                system("pause");
                break;
            case 7:
                printf("\nDigite o ID da locomotiva: ");
                scanf("%d", &idLocomotiva);
                locomotivaEncontrada = buscaLocomotiva(&locomotivas, idLocomotiva);
                if(locomotivaEncontrada == NULL) {
                    printf("Locomotiva com ID %d nao encontrada!\n", idLocomotiva);
                    system("pause");
                    break;
                }
                printf("\nDigite o ID do primeiro vagao: ");
                scanf("%d", &idvagao1);
                printf("\nDigite o ID do segundo vagao: ");
                scanf("%d", &idvagao2);
                if(trocarVagoesLocomotiva(&locomotivas, idLocomotiva, idvagao1, idvagao2)){
                    printf("\nVagoes trocados com sucesso!\n");
                }
                system("pause");
                break;
            case 0:
                printf("\nSaindo...\n");
                liberaLocomotivas(&locomotivas);
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                system("pause");
                break;
        }
    }while (opcao != 0);
}

int main(){
    menu();
    return 0;
}