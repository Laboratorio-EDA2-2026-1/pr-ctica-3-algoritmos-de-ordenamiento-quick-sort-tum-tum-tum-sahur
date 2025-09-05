#include <stdio.h>
#include <stdlib.h>

/*
  Ejercicio: QuickSort con pivote = promedio de los valores en el subarreglo.

  Requisitos:
    - El pivote es el promedio (double) de los valores del segmento actual.
    - El pivote puede NO pertenecer al arreglo.
    - En el arreglo de salida solo pueden aparecer valores del arreglo original
      (NO se inserta el pivote como elemento).

  Sugerencia de diseño (no obligatorio):
    - calcular_promedio_segmento(arr, bajo, alto) -> double
    - particion_por_promedio(arr, bajo, alto, pivote) -> índice final (int)
      (reorganizar comparando cada arr[i] con el pivote)
    - quicksort_promedio(arr, bajo, alto) -> recursivo
*/

void intercambiar(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

/* Devuelve el promedio (double) de arr[bajo..alto] */
double calcular_promedio_segmento(int arr[], int bajo, int alto) {
    // Escribe aquí tu función
    // Pista:
    //   - Acumula en (long long) o (double) para evitar overflow
    //   - Devuelve suma / cantidad como double
    double suma = 0;
    for (int i = bajo; i <= alto; i++)
        {
            suma += arr[i];
        }
    return suma / (alto - bajo + 1); // placeholder
}

/*
  Partición usando pivote = promedio.
  Objetivo:
    - Reordenar in-place arr[bajo..alto] comparando cada elemento con "pivote".
    - Colocar a la izquierda los elementos < pivote
      y a la derecha los elementos >= pivote (o la convención que elijas).
    - NO insertar el pivote en el arreglo (solo se usa para decidir posiciones).
    
  Nota:
    - Define y documenta tu convención de partición para manejar duplicados:
      por ejemplo, (< pivote) a la izquierda y (>= pivote) a la derecha.
    - Asegura progreso (evitar ciclos infinitos cuando todos son iguales).
*/
int particion_por_promedio(int arr[], int bajo, int alto){ //double pivote) {
    // Escribe aquí tu función
    // Puedes implementar un esquema tipo Hoare o Lomuto pero guiado por pivot double.
    // Recuerda: NO escribas 'pivote' dentro del arreglo; solo compáralo contra arr[i].
    double pivote = calcular_promedio_segmento(arr,bajo, alto);
    int i = bajo - 1;
    int j = alto + 1;
    
    while (1)
    {
        do {
            i++;
        }while (arr[i] < pivote);
        do {
            j--;
        }while (arr[j] > pivote);
    
        if (i >= j) return j;
    
        intercambiar(&arr[i], &arr[j]);
    }
    //indice final del grupo < pivote
    //return i; // placeholder
}

/*
  QuickSort con pivote = promedio:
    - Caso base: si bajo >= alto, terminar.
    - Paso:
        1) pivote = promedio de arr[bajo..alto]
        2) k = particion_por_promedio(arr, bajo, alto, pivote)
        3) Llamar recursivamente a los segmentos definidos por k
*/
void quicksort_promedio(int arr[], int bajo, int alto) {
    // Escribe aquí tu función
    if (bajo < alto){
        int pi = particion_por_promedio(arr, bajo, alto);
        quicksort_promedio(arr, bajo, pi);
        quicksort_promedio(arr,pi+1,alto);
    }
    //quicksort_promedio(arr, bajo, k);
    //quicksort_promedio(arr, k + 1, alto);
}

/* Utilidad para imprimir un arreglo */
void imprimir_arreglo(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (i) printf(" ");
        printf("%d", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Error: n inválido.\n");
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (!arr) {
        fprintf(stderr, "Error: memoria insuficiente.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Error: entrada inválida en la posición %d.\n", i + 1);
            free(arr);
            return 1;
        }
    }

    // Antes
    // printf("Antes:  "); imprimir_arreglo(arr, n);

    quicksort_promedio(arr, 0, n - 1);

    // Después
    imprimir_arreglo(arr, n);

    free(arr);
    return 0;
}
