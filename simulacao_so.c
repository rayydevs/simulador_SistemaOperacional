#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Estrutura para definir um Processo
typedef struct {
    int id;            // Identificador do processo
    char nome[20];     // Nome do processo
    int em_execucao;   // 1 para em execução, 0 para suspenso
} Processo;

Processo processos[10];
int processo_contador = 0; // Quantidade de processos criados

// Função para criar um processo
void criar_processo(int id, const char* nome) {
    processos[processo_contador].id = id;                  // Define o ID do processo
    strcpy(processos[processo_contador].nome, nome);       // Define o nome do processo
    processos[processo_contador].em_execucao = 0;          // Define que o processo está suspenso inicialmente
    processo_contador++;                                   // Incrementa o contador de processos
    printf("Processo %s criado.\n", nome);                 // Exibe uma mensagem informando que o processo foi criado
}

// Função para iniciar a execução de um processo
void executar_processo(int id) {
    for (int i = 0; i < processo_contador; i++) {           // Percorre todos os processos
        if (processos[i].id == id) {                        // Verifica se o ID corresponde
            processos[i].em_execucao = 1;                   // Marca o processo como em execução
            printf("Processo %s em execução.\n", processos[i].nome);  // Exibe uma mensagem informando
            break;                                          // Sai do loop, pois já encontrou o processo
        }
    }
}

// Função para suspender um processo
void suspender_processo(int id) {
    for (int i = 0; i < processo_contador; i++) {           // Percorre todos os processos
        if (processos[i].id == id && processos[i].em_execucao) {  // Verifica se o ID corresponde e se está em execução
            processos[i].em_execucao = 0;                   // Marca o processo como suspenso
            printf("Processo %s suspenso.\n", processos[i].nome);  // Exibe uma mensagem informando
            break;                                          // Sai do loop
        }
    }
}

// Função para finalizar um processo
void finalizar_processo(int id) {
    for (int i = 0; i < processo_contador; i++) {          // Percorre todos os processos
        if (processos[i].id == id) {                       // Verifica se o ID corresponde
            printf("Processo %s finalizado.\n", processos[i].nome);  // Exibe uma mensagem
            processos[i] = processos[processo_contador - 1];  // Substitui o processo finalizado pelo último
            processo_contador--;                            // Reduz o contador de processos
            break;                                         // Sai do loop
        }
    }
}

// Definindo a Memória Total e disponível
#define MEMORIA_TOTAL 1024
int memoria_disponivel = MEMORIA_TOTAL;

// Função para alocar memória para um processo
int alocar_memoria(int id, int tamanho) {
    if (memoria_disponivel >= tamanho) {               // Verifica se há memória suficiente
        memoria_disponivel -= tamanho;                 // Subtrai o tamanho da memória disponível
        printf("Memória alocada para o processo %d. Memória disponível: %d\n", id, memoria_disponivel);
        return 1;                                      // Retorna sucesso
    } else {
        printf("Memória insuficiente para o processo %d.\n", id);
        return 0;                                      // Retorna falha
    }
}

// Função para liberar memória alocada
void liberar_memoria(int id, int tamanho) {
    memoria_disponivel += tamanho;                    // Adiciona o tamanho à memória disponível
    printf("Memória liberada pelo processo %d. Memória disponível: %d\n", id, memoria_disponivel);
}

// Estrutura para Arquivo
typedef struct {
    char nome[20];
    char conteudo[100];
} Arquivo;

Arquivo arquivos[10];
int arquivo_contador = 0;

// Função para criar um arquivo
void criar_arquivo(const char* nome) {
    strcpy(arquivos[arquivo_contador].nome, nome);
    strcpy(arquivos[arquivo_contador].conteudo, "");
    arquivo_contador++;
    printf("Arquivo %s criado.\n", nome);
}

// Função para ler o conteúdo de um arquivo
void ler_arquivo(const char* nome) {
    for (int i = 0; i < arquivo_contador; i++) {
        if (strcmp(arquivos[i].nome, nome) == 0) {
            printf("Conteúdo do arquivo %s: %s\n", nome, arquivos[i].conteudo);
            return;
        }
    }
    printf("Arquivo %s não encontrado.\n", nome);
}

// Função para escrever no arquivo
void escrever_arquivo(const char* nome, const char* conteudo) {
    for (int i = 0; i < arquivo_contador; i++) {
        if (strcmp(arquivos[i].nome, nome) == 0) {
            strcpy(arquivos[i].conteudo, conteudo);
            printf("Conteúdo escrito no arquivo %s.\n", nome);
            return;
        }
    }
    printf("Arquivo %s não encontrado.\n", nome);
}

// Função para deletar o arquivo
void deletar_arquivo(const char* nome) {
    for (int i = 0; i < arquivo_contador; i++) {
        if (strcmp(arquivos[i].nome, nome) == 0) {
            arquivos[i] = arquivos[arquivo_contador - 1];
            arquivo_contador--;
            printf("Arquivo %s deletado.\n", nome);
            return;
        }
    }
    printf("Arquivo %s não encontrado.\n", nome);
}

// Função para iniciar o sistema
void iniciar_sistema() {
    printf("Sistema operacional iniciado.\n");
}

// Função para exibir o status atual do sistema
void exibir_status() {
    printf("Status do sistema:\n");
    printf("Memória disponível: %d\n", memoria_disponivel);
    printf("Processos ativos:\n");
    for (int i = 0; i < processo_contador; i++) {
        printf("ID: %d, Nome: %s, Em execução: %d\n", processos[i].id, processos[i].nome, processos[i].em_execucao);
    }
    printf("Arquivos:\n");
    for (int i = 0; i < arquivo_contador; i++) {
        printf("Nome: %s, Conteúdo: %s\n", arquivos[i].nome, arquivos[i].conteudo);
    }
}

// Função principal
int main() {
	setlocale(LC_ALL,"portuguese");
	
    iniciar_sistema();

    // Criando e executando um processo
    criar_processo(1, "Processo1");
    alocar_memoria(1, 100); // Alocando 100 unidades de memória para o Processo1
    executar_processo(1); // Executando o processo

    // Criando um arquivo e escrevendo no arquivo
    criar_arquivo("arquivo1");
    escrever_arquivo("arquivo1", "Conteúdo do arquivo");

    // Ler o conteúdo do arquivo
    ler_arquivo("arquivo1");

    // Suspendendo o processo
    suspender_processo(1);

    // Liberando a memória e finalizando o processo
    liberar_memoria(1, 100); // Liberando a memória alocada para o processo
    finalizar_processo(1);

    // Exibindo o status atual do sistema
    exibir_status();

    // Criando outro processo e um segundo arquivo para teste adicional
    criar_processo(2, "Processo2");
    alocar_memoria(2, 200);
    executar_processo(2);
    criar_arquivo("arquivo2");
    escrever_arquivo("arquivo2", "Outro conteúdo");

    // Exibindo o status do sistema novamente após alterações
    exibir_status();

    // Finalizando o segundo processo e liberando os recursos
    liberar_memoria(2, 200);
    finalizar_processo(2);
    deletar_arquivo("arquivo1");
    deletar_arquivo("arquivo2");

    // Exibindo o status final do sistema
    exibir_status();

    return 0;
}

