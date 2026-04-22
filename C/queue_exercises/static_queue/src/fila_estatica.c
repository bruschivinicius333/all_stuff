#include <stdio.h>
#include <stdlib.h>
#include "../include/fila_estatica.h"

// Cria a fila e inicializa os campos (pág. 76)
Fila Criar(int length) {
    Fila f = (Fila)malloc(sizeof(struct estrutura_Fila));
    if (f != NULL) {
        f->ini = 0; // Inicializamos em 0 para facilitar a lógica circular
        f->fim = -1; // Conforme pág. 76, indica fila inicialmente vazia
        f->quant_elementos = 0;
        f->length = length;
        f->elementos = (tipo_base **)calloc(length, sizeof(tipo_base *));
    } else {
        printf("Não existe memória suficiente.\n");
    }
    return f;
}

int Delete(Fila *f) {
    if(!f)
        return 1;
    while(!Remover(*f));
    free((*f)->elementos);
    free((*f));
    *f = NULL;
    return 0;
}

// Implementação do incremento circular (pág. 77)
int incrementar(const Fila f, int pos) {
    if(pos == f->length) 
        return 0; // Se atingir o fim físico, volta para o início (0)
    else 
        return pos + 1;
}

// Verifica se a fila está cheia (pág. 74, 76)
int Cheia(Fila f) {
    return (f->quant_elementos == f->length);
}

// Verifica se a fila está vazia (pág. 74, 77)
int Vazia(Fila f) {
    return (f->quant_elementos == 0);
}

// Insere um elemento no fim da fila (pág. 77)
int Inserir(Fila f, tipo_base v) {
    if(Cheia(f)) {
        printf("Fila cheia!\n");
        return 1;
    }
    f->fim = incrementar(f, f->fim); // Move o índice de fim circularmente
    f->elementos[f->fim] = malloc(sizeof(tipo_base));
    if(!(f->elementos[f->fim])) {
        fprintf(stderr, "Memória insuficiente para inserir elemento na fila\n");
        exit(EXIT_FAILURE);
    }
    *(f->elementos[f->fim]) = v;
    f->quant_elementos++;
    return 0;
}

// Remove o elemento do início (pág. 77, 78)
int Remover(Fila f) {
    if(Vazia(f)) {
        printf("Fila vazia.\n");
        return 1; // Valor de erro
    }
    free(f->elementos[f->ini]);
    f->elementos[f->ini] = NULL;
    f->ini = incrementar(f, f->ini); // Move o índice de início circularmente
    f->quant_elementos--;
    
    // Se a fila ficar vazia, opcionalmente resetamos os índices (pág. 77)
    if (f->quant_elementos == 0) {
        f->ini = 0;
        f->fim = -1;
    }
    return 0;
}

const tipo_base *Peek(Fila f) { // it can be NULL
    if(Vazia(f)) {
        return NULL;
    }
    return f->elementos[f->ini]; // Returns the FRONT element (head)
}