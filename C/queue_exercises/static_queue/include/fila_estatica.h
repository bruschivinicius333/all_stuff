#ifndef FILA_ESTATICA_H
#define FILA_ESTATICA_H
#define CLIENTE_NOME_LENGTH 50
#define CLIENTE_CPF_LENGTH 12

typedef struct {
    char cpf[CLIENTE_CPF_LENGTH];
    char nome[CLIENTE_NOME_LENGTH];
} Cliente;

typedef Cliente tipo_base;

// Estrutura da Fila conforme página 75
struct estrutura_Fila {
    int ini;
    int fim;
    int quant_elementos;
    tipo_base **elementos;
    int length;
};

typedef struct estrutura_Fila *Fila;

// Interface do TAD Fila (pág. 73, 74)
Fila Criar(int);
int Inserir(Fila f, tipo_base v);
int Remover(Fila f);
int Vazia(Fila f);
int Cheia(Fila f);
int incrementar(const Fila, int); // Função auxiliar para o vetor circular
//int MostrarFila(Fila f);
int Delete(Fila *);
const tipo_base *Peek(Fila);

#endif