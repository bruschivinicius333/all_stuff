#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_FILE_NAME_LENGTH 255
typedef unsigned long ulong;

char inputBuffer[1024] = "";
FILE *pFile = NULL;
char escolhaFuncao = 0;
char nomeArquivo[MAX_FILE_NAME_LENGTH] = "";
char *dataToInsert = NULL;
ulong dataToInsert_length = 0;
char *dataToRetrieve = NULL;
long fileSize = 0;
char skipIntro = 0;

void ler();
void writeFile(char *);
void inputChecker(char *);

int main() {

    while(1) {
        while(1) {
            if(skipIntro) {
                break;
            }
            printf("\nBem-vindo ao BruschiPad!\n");
            printf("Selecione uma operação:\n");
            printf("1. Criar memorando\n");
            printf("2. Ler memorando\n");
            printf("3. Atualizar (append) memorando\n");
            printf("4. Deletar memorando\n");
            printf("5. Sair\n");
            ler();
            escolhaFuncao = inputBuffer[0];
            if(escolhaFuncao >= '1' && escolhaFuncao <= '4') {
                break;
            }
            if (escolhaFuncao == '5') {
                exit(0);
            }
            printf("\nOpção inválida!\n");
        }
        if(!skipIntro) {
            printf("\nQual o nome do arquivo? (max 255)\n");
            if(fgets(nomeArquivo, sizeof(nomeArquivo), stdin) == NULL) {
                exit(1);
            }
            nomeArquivo[strlen(nomeArquivo) - 1] = '\0';
        }
        skipIntro = 0;
        pFile = fopen(nomeArquivo, "r+");
        switch(escolhaFuncao) {
            case '1': // Create
                if(pFile != NULL) {
                    fclose(pFile);
                    pFile = NULL;
                    inputChecker("Arquivo já existente. Deseja sobrescrevê-lo? (s/n)\n");
                    if(inputBuffer[0] == 'N' || inputBuffer[0] == 'n') {
                        break;
                    }
                }
                writeFile("w");
                break;
            case '2': // Read
                if(pFile == NULL) {
                    inputChecker("Arquivo não existe. Deseja criá-lo? (s/n)\n");
                    if(inputBuffer[0] == 'S' || inputBuffer[0] == 's') {
                        escolhaFuncao = '1';
                        skipIntro = 1;
                    }
                    break;
                }
                fseek(pFile, 0, SEEK_END);
                fileSize = ftell(pFile) + 1;
                if(fileSize == -1) {
                    exit(1);
                }
                rewind(pFile);
                dataToRetrieve = (char *)malloc(sizeof(char) * fileSize);
                if(fgets(dataToRetrieve, fileSize, pFile) == NULL) {
                    exit(1);
                }
                printf("%s\n", dataToRetrieve);
                fclose(pFile);
                pFile = NULL;
                break;
            case '3': // Update
                if(pFile == NULL) {
                    inputChecker("Arquivo não existente. Deseja criá-lo? (s/n)\n");
                    if(inputBuffer[0] == 'S' || inputBuffer[0] == 's') {
                        escolhaFuncao = '1';
                        skipIntro = 1;
                    }
                    break;
                }
                fclose(pFile);
                pFile = NULL;
                writeFile("a");
                break;
            case '4': // Delete
                if(pFile == NULL) {
                    printf("Arquivo não existe\n");
                } else {
                    unlink(nomeArquivo);
                    fclose(pFile);
                    pFile = NULL;
                    printf("Arquivo deletado!\n");
                }
                break;
        }
        free(dataToInsert);
        dataToInsert = NULL;
        free(dataToRetrieve);
        dataToRetrieve = NULL;
    }

    return 0;
}

void ler() {
    if(fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL) {
        exit(1);
    }
}

void writeFile(char *mode) {
    pFile = fopen(nomeArquivo, mode);
    while(1) {
        printf("Quantos caracteres ASCII serão inseridos?\n");
        ler();
        dataToInsert_length = atoi(inputBuffer);
        if(dataToInsert_length > 0) {
            break;
        }
        printf("Tamanho inválido\n");
    }
    dataToInsert_length++;
    dataToInsert = (char *)malloc(sizeof(char) * dataToInsert_length);
    if(dataToInsert == NULL) {
        exit(2);
    }
    printf("Insira o texto a ser inserido\n");
    if(fgets(dataToInsert, dataToInsert_length, stdin) == NULL) {
        exit(1);
    }
    fprintf(pFile, "%s", dataToInsert);
    fclose(pFile);
    pFile = NULL;
    printf("Sucesso! (provavelmente)\n");
}

void inputChecker(char *question) {
    while(1) {
        printf("%s", question);
        ler();
        if(inputBuffer[0] == 'S' || inputBuffer[0] == 's'
            || inputBuffer[0] == 'N' || inputBuffer[0] == 'n') {
            break;
        }
        printf("Opção inválida");
    }
}
