#ifndef FILA_DINAMICA_H
#define FILA_DINAMICA_H

#define TAXI_LENGTH_PLACA 8
#define TAXI_LENGTH_MODELO 32
#define TAXI_LENGTH_NOMEMOTORISTA 64

typedef struct {
    char placa[TAXI_LENGTH_PLACA];
    char modelo[TAXI_LENGTH_MODELO];
    char nomeMotorista[TAXI_LENGTH_NOMEMOTORISTA];
} Taxi;

typedef Taxi tipo_base;

// Estrutura do Nó (pág. 79)
typedef struct node *no_ptr;
struct node {
    tipo_base *elemento;
    no_ptr prox;
};
typedef struct node node;

// Estrutura descritora da Fila (pág. 79)
struct estrutura_fila {
    no_ptr inicio;
    no_ptr fim;
};

typedef struct estrutura_fila *Fila;

// Protótipos (pág. 78-82)
Fila Criar();
int Vazia(Fila f);
void Inserir(Fila f, tipo_base x);
int Remover(Fila f);
int MostrarFila(Fila f);
int Delete(Fila *);
node *Find(const Fila, tipo_base);
node *FindPrevious(const Fila, node *);
int cmp_tipo_base(const tipo_base a, const tipo_base b);
const tipo_base *Peek(const Fila f);
/* tipo_base FindMax(const Fila);
tipo_base FindMin(const Fila);
int Acum(const Fila); */

#endif