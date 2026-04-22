#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "include/fila_dinamica.h"

typedef unsigned int uint;

char inputBuffer[512] = {0};

const char *read() { // read user input from stdin
    if(!fgets(inputBuffer, sizeof(inputBuffer), stdin))
        exit(EXIT_FAILURE);
    return inputBuffer;
}
const char *readPut(const char *toPrint) { // like read(), but with a loop for printing toPrint until a valid response is entered
    do {
        printf("%s", toPrint);
        read();
    } while(inputBuffer[0] == '\0' || inputBuffer[0] == '\n');
    return inputBuffer;
}

char *strnput(char *s1, char *s2, size_t n) { // no truncation warnings :)
    size_t size = strnlen (s2, n);
    if (size != n)
        memset (s1 + size, '\0', n - size);
    return memcpy (s1, s2, size);
}

int bubbleSort(const void *a, const void *b) { // use it in qsort()
    return (*(int *)a - *(int *)b);
}

int main() {
    Fila mainFila = Criar();

    while(1) {
        int menuChoice = 0;

        do {   
            printf("\nMenu:\n");
            printf("1. Entrada no Ponto (Inserir).\n");
            printf("2. Chamada de Passageiro (Remover).\n");
            printf("3. Listagem da Fila (Percorrer).\n");
            printf("4. Pesquisar Motorista.\n");
            printf("5. Encerramento.\n");

            menuChoice = atoi(read());
        } while(!menuChoice);

        printf("\n");

        switch(menuChoice) {
            case 1: {
                    tipo_base toInsert;
                    readPut("Digite a placa do taxi a ser inserido: ");
                    strnput(toInsert.placa, inputBuffer, TAXI_LENGTH_PLACA);
                    readPut("Agora o modelo do taxi: ");
                    strnput(toInsert.modelo, inputBuffer, TAXI_LENGTH_MODELO);
                    readPut("Agora, o nome do motorista: ");
                    strnput(toInsert.nomeMotorista, inputBuffer, TAXI_LENGTH_NOMEMOTORISTA);
                    Inserir(mainFila, toInsert);
                    
                    const tipo_base *toCmp = Peek(mainFila);
                    if(!toCmp) {
                        printf("Falha na inserção\n");
                        break;
                    }
                    if(cmp_tipo_base(toInsert, *toCmp)) {
                        printf("Inserido com sucesso!\n");
                        break;
                    }
                    printf("Falha na inserção\n");
                    break;
            }
            case 2: {
                const tipo_base *toPrint = Peek(mainFila);
                if(!toPrint) {
                    printf("Não há veículos a exibir\n");
                    break;
                }
                printf("Veículo em serviço:\nplaca: %smodelo: %snome do motorista: %s", toPrint->placa, toPrint->modelo, toPrint->nomeMotorista);
                Remover(mainFila);
                break;
            }
            case 3: {
                if(MostrarFila(mainFila)) {
                    printf("Não há veículos a exibir\n");
                }
                break;
            }
            case 4: {
                readPut("Digite o nome do motorista para pesquisar: ");
                node *current = mainFila->inicio;
                int posFila = 0;
                while(current) {
                    if(!strcmp(current->elemento->nomeMotorista, inputBuffer)) {
                        break;
                    }
                    current = current->prox;
                    ++posFila;
                }
                if(current) {
                    printf("O motorista %s está na posição %d da fila\n", current->elemento->nomeMotorista, posFila);
                    break;
                }
                printf("Não há um motorista com esse nome na fila\n");
                break;
            }
            case 5: {
                printf("Mensagem de despedida!\n");
                Delete(&mainFila);
                return 0;
                break;
            }
        }
    }

    return 0;
}