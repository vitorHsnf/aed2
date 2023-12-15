#include <stdio.h>
#include <time.h>
#include "auxiliares.c"
#define TAMANHO 100     
#define TIPO 1              // 1 - vetor aleatório, 2 - vetor ordenado
#define METODO 2            /* 1 - bubblesort, 2 - insertsort, 3 - selectionsort
                               4 - shellsort,  5 - quicksort,  6 - mergesort
                               7 - heapsort */
#define IMPRIME 0           // 0 - Não imprime vetor, 1 - Imprime vetor

// Funções Principais de Ordenação
void bubblesort(int vetor[], int n);
void insertsort(int vetor[], int n);
void selectionsort(int vetor[], int n);
void shellsort(int vetor[], int n);
void heapsort(int vetor[], int size);
void mergesort(int vetor[], int left, int right);
void quicksort(int vetor[], int left, int right);

// Funções Auxiliares de Ordenação
void heapify(int size, int i);
void merge(int vetor[], int left, int middle, int right);

// Variáveis Principais
int *vetor;         
int comp = 0, trocas = 0;

void bubblesort(int vetor[], int n)
{
    int i, j, temp;

    for (i = 0; i < n-1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            comp++;
            if (vetor[j] > vetor[j+1])
            {
                temp = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = temp;
                trocas++;
            }
        }
    }
}

void insertsort(int vetor[], int n)
{
    int i, j;
    int temp;

    // Iteracão-base: percorre o vetor
    for (i = 1; i < n - 1; i++) 
    {
        temp = vetor[i];  // Posição Atual
        j = i - 1;        // Posição à Esquerda do Atual

        comp++;
        //  Iteração-Auxiliar: comparando os valores à esquerda do atual
        while (j >= 0 && temp < vetor[j])
        {   
            comp++;
            vetor[j+1] = vetor[j];
            j--;
            trocas++;
        }

        // Verifica se a primeira posição já está com o valor
        if (vetor[j+1] != temp)
        {
            vetor[j+1] = temp; // Inserindo o elemento na posição ordenada
            trocas++;
        }
    }
}

void selectionsort(int vetor[], int n)
{
    int indice_menor, aux;

    // Iteracão base: Percorre o vetor
    for (int i = 0; i < n-1; i++)
    {
        // Índice do menor elemento não ordenado
        indice_menor = i;

        // Iteração auxiliar: Encontra o menor elemento no vetor
        for (int j = i+1; j < n; j++)
        {
            if (vetor[j] < vetor[indice_menor]) 
                indice_menor = j;
            comp++;
        }

        // Se o menor for diferente do atual, faz a troca de posição 
        if (i != indice_menor) {
            aux = vetor[i];
            vetor[i] = vetor[indice_menor];
            vetor[indice_menor] = aux;
            trocas++;
        } 
    }
}

void shellsort(int vetor[], int size)
{
    int i, j, h;
    int temp;

    for (h = size/2; h > 0; h /= 2)
    {
        for (i = h; i < size; i++)
        {
            temp = vetor[i];
            
            for (j = i; j >= h && vetor[j-h] > temp; j-=h)
            {
                vetor[j] = vetor[j - h];
                trocas++;
            }
            vetor[j] = temp;
            comp++;
        }
    }
}

// Função que ajusta um heap máximo
void heapify(int size, int i)
{
    int temp;
    int heap = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Verifica se o nó possui nós filhos
    if (left > size && right > size)
        return;

    // Verifica se há um filho à esquerda e compara
    comp++;
    if (left < size && vetor[left] > vetor[heap])
        heap = left;

    // Verifica se há um filho à direita e compara  
    comp++;
    if (right < size && vetor[right] > vetor[heap])
        heap = right;

    // Se o maior não é o heap, faz a troca
    if (heap != i)
    {    
        temp = vetor[i];
        vetor[i] = vetor[heap];
        vetor[heap] = temp;

        trocas++;

        // Ajusta o sup-heap afetado
        heapify(size, heap);
    }
}

void heapsort(int vetor[], int size)
{   
    int temp;

    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(size, i);
    
    for (int i = size - 1; i >= 0; i--)
    {   
        if (vetor[0] != vetor[i])
        {
            temp = vetor[0];
            vetor[0] = vetor[i];
            vetor[i] = temp;

            trocas++;
        }
        heapify(i, 0);
    }
}

void mergesort(int vetor[], int left, int right)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;

        // Classifica a metada esquerda
        mergesort(vetor, left, middle);

        // Classifica a metade direita
        mergesort(vetor, middle + 1, right);

        // Faz o merge das partes do vetor ordenados
        merge(vetor, left, middle, right);
    }
}

// Função que mescla as duas partes de um vetor dividido
void merge(int vetor[], int left, int middle, int right)
{   
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Cria vetores temporários
    int vet_l[n1], vet_r[n2];

    // Copia dados para vetores temporários vet_l[] e vet_r[]
    for (i = 0; i < n1; i++)
        vet_l[i] = vetor[left + i];

    for (j = 0; j < n2; j++)
        vet_r[j] = vetor[middle + 1 + j];
    
    // Mesclar os vetores temporários de volta no vetor[left...right]
    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2)
    {   
        comp++;
        if (vet_l[i] <= vet_r[j])
        {
            if (i != k)
                trocas++;
            vetor[k] = vet_l[i];
            i++;
        }

        else
        {   
            trocas++;
            vetor[k] = vet_r[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        vetor[k] = vet_l[i];
        i++;
        k++;
        trocas++;
    }

    while (j < n2)
    {
        vetor[k] = vet_r[j];
        j++;
        k++; 
        trocas++;
    }
}

void quicksort(int vet[], int left, int right)
{

    int aux, pivot, L, R;

    L = left;
    R = right;

    pivot = vet[(left + right) / 2];

    while (L <= R)
    {   
        comp++;
        while(vet[L] < pivot && L < right)
        {   
            comp++;
            L++;
        }

        comp++;
        while(vet[R] > pivot && R > left)
        {   
            comp++;
            R--;
        }
        
        if (L <= R)
        {
            aux = vet[L];
            vet[L] = vet[R];
            vet[R] = aux;
            L++;
            R--;
            trocas++;
        }
    }

    if (R > left)
        quicksort(vet, left, R);
    if (L < right)
        quicksort(vet, L, right);

}


int main(int argc, char *argv[])
{   
    int i;
    double start, finish, elapsed;

    printf("\n --- Analise de Algoritmos de Ordenacao --- \n");
    printf(" Avisos do Sistema: \n");
    printf("-> Tamanho do Vetor Atual: %d \n", TAMANHO);
    printf("-> Tipo do Vetor Atual: %d \n", TIPO);

    vetor = aloca_vetor(vetor, TAMANHO);

    // Entrada de dados do vetor
    printf("Entre com os dados do vetor: \n");    

    // Entrada de dados para o vetor tipo ordenado
    if (TIPO == 2)
    {
        for (i = 0; i < TAMANHO; i++)
        {
            scanf("%d", &vetor[i]);
            // Validação de entrada de dados do tipo ordenado
            while (vetor[i] < vetor[i-1])
            {
                printf("Por favor entre com valores em ordem crescente ou altere o tipo de vetor \n");
                scanf("%d", &vetor[i]);
            }
        }
    }

    // Entrada de dados para o vetor desordenado
    else
    {
        for (i = 0; i < TAMANHO; i++)
            scanf("%d", &vetor[i]);
    }
    printf("Vetor lido...\n");

    // Imprime o vetor antes da ordenação
    if (IMPRIME == 1)
    {
        printf("Vetor: ");
        imprime_vetor(vetor, TAMANHO);
    }
    
    switch(METODO)
    {   
        // Bubble Sort
        case 1:
        {
            // Inicia o cronômetro
            start = (double) clock() / CLOCKS_PER_SEC;

            bubblesort(vetor, TAMANHO);

            // Finaliza o cronômetro
            finish = (double) clock() / CLOCKS_PER_SEC;

            if (IMPRIME == 1)
            {
                printf("Vetor Ordenado: ");
                imprime_vetor(vetor, TAMANHO);
            }

            libera_vetor(vetor);
            
            // Calcula o tempo gasto
            elapsed = (double) finish - start;

            break;
        }

        // Insertion Sort
        case 2:
        {
            // Inicia o cronômetro
            start = (double) clock() / CLOCKS_PER_SEC;

            insertsort(vetor, TAMANHO);

            // Finaliza o cronômetro
            finish = (double) clock() / CLOCKS_PER_SEC;

            if (IMPRIME == 1)
            {
                printf("Vetor ordenado: ");
                imprime_vetor(vetor, TAMANHO);
            }
            
            // Calcula o tempo gasto
            elapsed = (double) finish - start;
            break;
        }

        // Selection Sort
        case 3:
        {
            // Inicia o cronômetro
            start = (double) clock() / CLOCKS_PER_SEC;

            selectionsort(vetor, TAMANHO);

            // Finaliza o cronômetro
            finish = (double) clock() / CLOCKS_PER_SEC;

            if (IMPRIME == 1)
            {
                printf("Vetor ordenado: ");
                imprime_vetor(vetor, TAMANHO);
            }
            
            // Calcula o tempo gasto
            elapsed = (double) finish - start;

            break;
        }

        // Shell Sort
        case 4:
        {
            // Inicia o cronômetro
            start = (double) clock() / CLOCKS_PER_SEC;

            shellsort(vetor, TAMANHO);

            // Finaliza o cronômetro
            finish = (double) clock() / CLOCKS_PER_SEC;

            if (IMPRIME == 1)
            {
                printf("Vetor ordenado: ");
                imprime_vetor(vetor, TAMANHO);
            }
            
            // Calcula o tempo gasto
            elapsed = (double) finish - start;

            break;
        }

        // Quick Sort
        case 5:
        {
            // Inicia o cronômetro
            start = (double) clock() / CLOCKS_PER_SEC;

            quicksort(vetor, 0, TAMANHO-1);

            // Finaliza o cronômetro
            finish = (double) clock() / CLOCKS_PER_SEC;

            if (IMPRIME == 1)
            {
                printf("Vetor ordenado: ");
                imprime_vetor(vetor, TAMANHO);
            }
            
            // Calcula o tempo gasto
            elapsed = (double) finish - start;

            break;
        }

        // Merge Sort
        case 6:
        {
            // Inicia o cronômetro
            start = (double) clock() / CLOCKS_PER_SEC;

            mergesort(vetor, 0, TAMANHO-1);

            // Finaliza o cronômetro
            finish = (double) clock() / CLOCKS_PER_SEC;

            if (IMPRIME == 1)
            {
                printf("Vetor ordenado: ");
                imprime_vetor(vetor, TAMANHO);
            }
            
            // Calcula o tempo gasto
            elapsed = (double) finish - start;

            break;
        }

        // Heap Sort
        case 7:
        {
            // Inicia o cronômetro
            start = (double) clock() / CLOCKS_PER_SEC;

            heapsort(vetor, TAMANHO);

            // Finaliza o cronômetro
            finish = (double) clock() / CLOCKS_PER_SEC;

            if (IMPRIME == 1)
            {
                printf("Vetor ordenado: ");
                imprime_vetor(vetor, TAMANHO);
            }
            
            // Calcula o tempo gasto
            elapsed = (double) finish - start;

            break;
        }

         
    }
    // Imprime as estatísticas do método utilizado
    analise(METODO, TAMANHO, TIPO, elapsed, comp, trocas);

    return 0; 
}