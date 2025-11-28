#ifndef SRC_LISTA_PERSONAGENS_H_
#define SRC_LISTA_PERSONAGENS_H_

#include "personagem.h"

typedef struct elemento {
    Personagem* personagem;
    struct elemento* prox;
    struct elemento* prev;
} Elemento;

typedef struct listapersonagens {
    Elemento* primeiro;
    Elemento* ultimo;
    int quant_elementos;
} ListaPersonagens;

typedef struct duas_listas {
    ListaPersonagens* lista1;
    ListaPersonagens* lista2;
} DuasListas;

ListaPersonagens* criarLista();
void destruirLista(ListaPersonagens* l);
void destruirListaMantendoPersonagens(ListaPersonagens* l);
void destruirListaComPersonagens(ListaPersonagens* l);
void transferirConteudo(ListaPersonagens* origem, ListaPersonagens* destino);

Personagem* adicionarPersonagem(Personagem* p, ListaPersonagens* l);
Personagem* removerPersonagem(Personagem* p, ListaPersonagens* l);

DuasListas divideLista(ListaPersonagens* l);
ListaPersonagens* merge(ListaPersonagens* a, ListaPersonagens* b);

ListaPersonagens* ordenarIniciativasMergeSort(ListaPersonagens* l);
ListaPersonagens* ordenarIniciativasBubbleSort(ListaPersonagens* l);

void printOrdemCombate(ListaPersonagens* l);

#endif
