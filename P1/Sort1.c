/*

Dada a sequência de números 3,4,9,2,5,1,8
Ordene em ordem crescente utilizando os três algoritmos aprendidos em sala (BubbleSort, SelectionSort e
InsertionSort)

*/

#include <stdio.h>

// BubbleSort
void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// SelectionSort
void selectionSort(int arr[], int n) {
    int i, j, minIndex, temp;
    for (i = 0; i < n-1; i++) {
        minIndex = i;
        for (j = i+1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

// InsertionSort
void insertionSort(int arr[], int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j = j - 1;
        }
        arr[j+1] = key;
    }
}

int main() {
    int arr[] = {3, 4, 9, 2, 5, 1, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i;

    // BubbleSort
    printf("BubbleSort:\n");
    bubbleSort(arr, n);
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // SelectionSort
    printf("SelectionSort:\n");
    selectionSort(arr, n);
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // InsertionSort
    printf("InsertionSort:\n");
    insertionSort(arr, n);
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
