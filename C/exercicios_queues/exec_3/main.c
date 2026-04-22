#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "include/fila_estatica.h"

typedef unsigned int uint;

char inputBuffer[256] = {0};

const char *read() { // read user input from stdin
    if(!fgets(inputBuffer, sizeof(inputBuffer), stdin))
        exit(EXIT_FAILURE);
    return inputBuffer;
}
void readPut(const char *toPrint) { // like read(), but with a loop for printing toPrint until a valid response is entered
    do {
        printf("%s", toPrint);
    } while(!read()[0]);
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

    readPut("Quantos clientes você deseja atender no dia?: ");
    Fila mainFila = Criar(atoi(inputBuffer));

    while(1) {
        int optionMenu = 0;
        do {
            printf("\nMenu:\n");
            printf("1. Inserir cliente\n");
            printf("2. Chamar cliente\n");
            printf("3. Fechamento do dia\n");
        } while(!atoi(read()));
        optionMenu = atoi(inputBuffer);
        printf("\n");

        switch(optionMenu) {
            case 1: {
                if(Cheia(mainFila)) {
                    printf("Limite de atendimentos atingido. Favor retornar outro dia.\n");
                    break;
                }
                Cliente toInsert;
                readPut("Insira o CPF do cliente: ");
                strnput(toInsert.cpf, inputBuffer, CLIENTE_CPF_LENGTH);
                readPut("Insira o nome do cliente: ");
                strnput(toInsert.nome, inputBuffer, CLIENTE_NOME_LENGTH);

                Inserir(mainFila, toInsert);

                const Cliente *toVerify = Peek(mainFila);
                if(!toVerify) {
                    printf("Erro na inserção\n");
                    break;
                }
                if(!strcmp(toInsert.cpf, toVerify->cpf) && !strcmp(toInsert.nome, toVerify->nome)) {
                    printf("Cliente inserido com sucesso!\n");
                } else {
                    printf("Erro na inserção\n");
                }
                break;
            }
            case 2: {
                const Cliente *chamado = Peek(mainFila);
                if(!chamado) {
                    printf("Não há clientes para chamar\n");
                    break;
                }
                // head - nome - CPF.
                printf("Chamando o cliente número: %d - %s - %s", mainFila->ini, chamado->nome, chamado->cpf);
                Remover(mainFila);
                break;
            }
            case 3: {
                printf("Clientes atendidos hoje: %d\n", mainFila->quant_elementos);
                printf("Esperados: %d\n", mainFila->length);
                printf("Ocupação: %.2f%%\n", (float) (mainFila->quant_elementos * 100) / mainFila->length);
                Delete(&mainFila);
                return 0;
                break;
            }
        }
    }

    return 0;
}
