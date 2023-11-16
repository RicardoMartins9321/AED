#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

int main() {
    char str1[MAX_SIZE], str2[MAX_SIZE], str2_copy[MAX_SIZE];
    int i, count_alpha = 0, count_upper = 0;

    printf("Digite a primeira string: ");
    gets(str1);
    printf("Digite a segunda string: ");
    gets(str2);

    // Conta os caracteres da primeira string que são letras do alfabeto
    for (i = 0; str1[i] != '\0'; i++) {
        if (isalpha(str1[i])) {
            count_alpha++;
        }
    }
    printf("A primeira string tem %d caracteres que são letras do alfabeto.\n", count_alpha);

    // Conta os caracteres da segunda string que são letras maiúsculas
    for (i = 0; str2[i] != '\0'; i++) {
        if (isupper(str2[i])) {
            count_upper++;
        }
    }
    printf("A segunda string tem %d caracteres maiúsculos.\n", count_upper);

    // Converte todas as letras maiúsculas, das duas strings, para minúsculas
    for (i = 0; str1[i] != '\0'; i++) {
        str1[i] = tolower(str1[i]);
    }
    for (i = 0; str2[i] != '\0'; i++) {
        str2[i] = tolower(str2[i]);
    }

    // Compara as duas strings resultantes
    int cmp = strcmp(str1, str2);
    if (cmp == 0) {
        printf("As duas strings são iguais.\n");
    } else if (cmp < 0) {
        printf("A primeira string vem antes da segunda na ordem lexicográfica.\n");
    } else {
        printf("A segunda string vem antes da primeira na ordem lexicográfica.\n");
    }

    // Cria uma cópia da segunda string
    strcpy(str2_copy, str2);

    // Concatena a segunda string com a sua cópia
    strcat(str2, str2_copy);

    printf("A string resultante da concatenação da segunda string com a sua cópia é: %s\n", str2);

    return 0;
}
