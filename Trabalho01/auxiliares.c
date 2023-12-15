/*
    Funções Auxiliares do Programa
*/
#include <stdio.h>
#include <stdlib.h>

// Lista de Ordenação Disponíveis
char *metodos_ordenacao[] = 
        {
            "Bubble Sort", 
            "Insertion Sort", 
            "Selection Sort", 
            "Shell Sort",
            "Quick Sort", 
            "Merge Sort", 
            "Heap Sort"
        };

// Tipos de Vetor
char *tipo_vetor[] = {"", "aleatorio", "ordenado"};

// Função que aloca espaço na memória para um vetor de tamanho n
int* aloca_vetor(int*vet, int n)
{   
    vet = (int*)malloc (sizeof(int) * n);
    return vet;
}

// Função que libera espaço da memória de um vetor
void libera_vetor(int *vet)
{
    free(vet);
}
// Função que imprime um vetor de tamanho n
void imprime_vetor(int* vetor, int n)
{   
    printf("\n\t");
    for (int i = 0; i < n; i++)
    {   
        if (i != 0 && i % 10 == 0)
            printf("\n\t");
        printf("%4d ", vetor[i]);
    }
    printf("\n");
}

/*
    Função que imprime as estatísticas da execução de um algoritmo, incluíndo o método usado, tamanho do vetor,
    tempo de execução, qtd. de comparações e trocas do vetor
*/
void analise(int sort, int tamanho, int tipo, float tempo_execucao, int comp, int trocas)
{   

    printf("\nEstatisticas da Ordenacao: \n");
    printf("Metodo Utilizado : %s \n", metodos_ordenacao[sort-1]);
    printf("- Tipo e Tamanho do Vetor: %s, %d elementos \n", tipo_vetor[tipo], tamanho);
    printf("- Tempo de execucao: %f s \n", tempo_execucao);
    printf("- Comparacoes: %d \n", comp);
    printf("- Trocas: %d", trocas);
}