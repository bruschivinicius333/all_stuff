#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/fila_dinamica.h"

int cmp_tipo_base(const tipo_base a, const tipo_base b) {
    return (!strcmp(a.modelo, b.modelo) && !strcmp(a.nomeMotorista, b.nomeMotorista) && !strcmp(a.placa, b.placa));
}

// Cria a estrutura descritora da fila (pág. 80)
Fila Criar() {
    Fila f = (Fila) malloc(sizeof(struct estrutura_fila));
    if (f != NULL) {
        f->inicio = NULL;
        f->fim = NULL;
    }
    return f;
}

int Delete(Fila *f) {
    if(!f)
        return 1;
    while(!Remover(*f));
    free(*f);
    *f = NULL;
    return 0;
}

// Verifica se a fila está vazia (pág. 80)
int Vazia(Fila f) {
    return (f->inicio == NULL);
}

// Insere um elemento no fim da fila (pág. 81)
void Inserir(Fila f, tipo_base x) {
    if(!f) {
        fprintf(stderr, "ERROR: Parameter Fila equals NULL\n");
        exit(EXIT_FAILURE);
    }
    
    no_ptr novo = (no_ptr) malloc(sizeof(struct node));
    if (!novo) {
        fprintf(stderr, "Erro: Memória insuficiente!\n");
        exit(EXIT_FAILURE);
    }
    
    novo->elemento = malloc(sizeof(tipo_base));
    if(!(novo->elemento)) {
        fprintf(stderr, "Error: Insuficient memory\n");
        exit(EXIT_FAILURE);
    }

    *(novo->elemento) = x;
    novo->prox = NULL; // Novo nó será o último, então aponta para NULL

    if(Vazia(f)) {
        f->inicio = novo; // Se era vazia, início e fim apontam para o novo
    } else {
        f->fim->prox = novo; // O antigo último aponta para o novo
    }
    f->fim = novo; // Atualiza o ponteiro de fim da fila
}

// Remove o elemento do início (pág. 81, 82)
int Remover(Fila f) {
    if(!f) {
        return 1;
    }
    if(Vazia(f)) {
        return 1;
    }

    no_ptr aux = f->inicio;    // Aponta para o nó que será removido
    
    f->inicio = f->inicio->prox; // O início avança para o próximo nó

    // Se a fila ficou vazia após a remoção, o fim também deve ser NULL
    if (f->inicio == NULL) {
        f->fim = NULL;
    }
    free(aux->elemento);
    free(aux); // Libera a memória do nó removido
    return 0;
}

int MostrarFila(Fila f){
    if(!f) {
        fprintf(stderr, "Queue equals NULL\n");
        exit(EXIT_FAILURE);
    }
    if(Vazia(f)) {
        return 1;
    }

    // 2. Criamos um ponteiro auxiliar para não perder o início da fila
    // Ele começa apontando para o mesmo lugar que o f->inicio
    no_ptr atual = f->inicio;

    printf("Elementos da fila (do inicio ao fim): \n");

    // 3. Enquanto o ponteiro "atual" não chegar ao fim (NULL)
    while (atual != NULL) {
        // Exibe o elemento do nó corrente
        printf("placa: %s", atual->elemento->placa);
        printf("modelo: %s", atual->elemento->modelo);
        printf("nome do motorista: %s\n", atual->elemento->nomeMotorista);

        // 4. O "pulo do gato": o ponteiro atual recebe o endereço do próximo nó
        atual = atual->prox;
    }
    return 0;
}

const tipo_base *Peek(const Fila f) {
    if(!f) {
        fprintf(stderr, "Fila argument is NULL\n");
        exit(EXIT_FAILURE);
    }
    if(Vazia(f)) {
        return NULL;
    }
    return f->inicio->elemento;
}

node *Find(const Fila f, tipo_base key) {
    if(!f) {
        fprintf(stderr, "Fila é NULL\n");
        exit(EXIT_FAILURE);
    }
    if(Vazia(f)) {
        return NULL;
    }
    node *current = f->inicio;
    while(current) {
        if(cmp_tipo_base(*(current->elemento), key)) {
            return current;
        }
        current = current->prox;
    }
    return NULL;
}

node *FindPrevious(const Fila f, node *iterator) {
    if(!f || !iterator) {
        exit(EXIT_FAILURE);
    }
    if(Vazia(f)) {
        return NULL;
    }
    node *current = f->inicio;
    while(current) {
        if(current->prox == iterator) {
            return current;
        }
        current = current->prox;
    }
    return NULL;
}

