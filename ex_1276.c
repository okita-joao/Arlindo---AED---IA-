#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN 1000

int cmpfunc(const void *a, const void *b) {
    return (*(char*)a - *(char*)b);
}

int main() {
    char str[MAX_LEN];
    while (fgets(str, sizeof(str), stdin)) {
        size_t len = strlen(str);
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';  // Remover a nova linha
            len--;
        }
        
        if (len == 0) {
            printf("\n");
        } else {
            char unique_chars[MAX_LEN];
            int count = 0;
            
            for (size_t i = 0; i < len; i++) {
                if (str[i] != ' ') {
                    int found = 0;
                    for (int j = 0; j < count; j++) {
                        if (unique_chars[j] == str[i]) {
                            found = 1;
                            break;
                        }
                    }
                    if (!found) {
                        unique_chars[count++] = str[i];
                    }
                }
            }
            
            qsort(unique_chars, count, sizeof(char), cmpfunc);
            
            char first = unique_chars[0], last = unique_chars[0], temp = first;
            bool x = false;
            
            for (int i = 1; i < count; i++) {
                temp++;
                if (temp == unique_chars[i]) {
                    last = unique_chars[i];
                } else {
                    if (x) {
                        printf(" ");
                    }
                    printf("%c:%c,", first, last);
                    first = unique_chars[i];
                    last = unique_chars[i];
                    temp = unique_chars[i];
                    x = true;
                }
            }
            if (x) {
                printf(" ");
            }
            printf("%c:%c\n", first, last);
        }
    }
    return 0;
}
