/*


Criar um programa em C que:

1. Gera um array de tamanho n com números aleatórios;
2. Cria funções para cada algoritmo de ordenação (mergesort, quicksort e heapsort);
3. Mede o tempo de execução de cada algoritmo para ordenar o array gerado;
4. Imprime o tempo de execução de cada algoritmo para cada tamanho de array.

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10000


void mergeSort(int arr[], int left, int right);
void quickSort(int arr[], int left, int right);
void heapSort(int arr[], int n, int k);


double measureTime(int arr[], int n, void (*sortFunction)(int[], int, int)) {
    clock_t start = clock();
    sortFunction(arr, 0, n - 1);
    clock_t end = clock();
    double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
    return timeSpent;
}

int main() {
    int n;
    int arr[MAX_SIZE];

    printf("Informe o tamanho do array: ");
    scanf("%d", &n);

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % MAX_SIZE;
    }

    double mergeSortTime = measureTime(arr, n, mergeSort);
    double quickSortTime = measureTime(arr, n, quickSort);
    double heapSortTime = measureTime(arr, n, heapSort);

    printf("Tamanho do array: %d\n", n);
    printf("Tempo de execução do Merge Sort: %lf segundos\n", mergeSortTime);
    printf("Tempo de execução do Quick Sort: %lf segundos\n", quickSortTime);
    printf("Tempo de execução do Heap Sort: %lf segundos\n", heapSortTime);

    return 0;
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }

    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int partition(int arr[], int left, int right) {
    int pivot = arr[right];
    int i = left - 1;

    for (int j = left; j <= right - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
        return (i + 1);
    }
}

void quickSort(int arr[], int left, int right) {
    if (left < right) {
        int partitionIndex = partition(arr, left, right);
        quickSort(arr, left, partitionIndex - 1);
        quickSort(arr, partitionIndex + 1, right);
    }
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    
    if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n, int k) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i >= 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}




