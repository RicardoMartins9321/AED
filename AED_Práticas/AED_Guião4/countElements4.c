#include <stdio.h>


void removeElements(int* sequence, int* n) {
  int i, j;

  for (i = 1; i < *n; i++) {
    for (j = 0; j < i; j++) {
      if (sequence[i] == sequence[j] || sequence[i] % sequence[j] == 0 || sequence[j] % sequence[i] == 0) {
        // Shift elements to the left to remove the current element
        for (int k = i; k < *n - 1; k++) {
          sequence[k] = sequence[k + 1];
        }
        (*n)--;
        i--; // Decrement i to recheck the current position in the next iteration
        break; // Break the inner loop to continue with the next element
      }
    }
  }
}


int main() {
    int sequence[] = { 2, 2, 2, 3, 3, 4, 5, 8, 8, 9 };
    int n = sizeof(sequence) / sizeof(sequence[0]);

    removeElements(sequence, &n);

    printf("Modified sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", sequence[i]);
    }
    printf("\n");

    return 0;
}



