#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1024

typedef int elem_t;

typedef enum _T_error_t {
    NOERROR,
    OVERFLOW,
    SUBSCRIPT
} error_t;

typedef struct _T_linear_list {
    elem_t a[MAXSIZE];  // Sequential list storage array
    int a_len;          // Current length
} linear_list_t;

/* Create a linear list */
linear_list_t *Create(void) {
    linear_list_t *L = (linear_list_t *)malloc(sizeof(linear_list_t));
    if (L != NULL) {
        L->a_len = 0;
    }
    return L;
}

/* Destroy the linear list */
void Destroy(linear_list_t *L) {
    free(L);
}

/* Empty the table */
void Set_null(linear_list_t *L) {
    L->a_len = 0;
}

/* Get the length of the table */
int Length(linear_list_t *L) {
    return L->a_len;
}

/* Get the element at the specified position */
elem_t Get(linear_list_t *L, int i) {
    if (i < 0 || i >= L->a_len) {
        printf("Index out of range!\n");
        return -1; // The return value can be modified as needed
    }
    return L->a[i];
}

/* Insert element at position i */
error_t Insert(linear_list_t *L, elem_t x, int i) {
    if (L->a_len >= MAXSIZE) {
        return OVERFLOW;
    }
    if (i < 0 || i > L->a_len) {
        return SUBSCRIPT;
    }
    // Move elements from back to front
    for (int j = L->a_len; j > i; j--) {
        L->a[j] = L->a[j - 1];
    }
    L->a[i] = x;
    L->a_len++;
    return NOERROR;
}

/* Delete the element at position i */
error_t Remove(linear_list_t *L, int i) {
    if (i < 0 || i >= L->a_len) {
        return SUBSCRIPT;
    }
    for (int j = i; j < L->a_len - 1; j++) {
        L->a[j] = L->a[j + 1];
    }
    L->a_len--;
    return NOERROR;
}

/* Search by value and return the position index; return -1 if not found */
int Locate(linear_list_t *L, elem_t x) {
    for (int i = 0; i < L->a_len; i++) {
        if (L->a[i] == x) {
            return i;
        }
    }
    return -1;
}

/* Remove duplicate elements, keeping the first occurrence */
void RemoveDup(linear_list_t *L) {
    for (int i = 0; i < L->a_len; i++) {
        for (int j = i + 1; j < L->a_len; ) {
            if (L->a[j] == L->a[i]) {
                // Remove duplicate elements
                Remove(L, j);
            } else {
                j++;
            }
        }
    }
}

/* Print the contents of the list */
void PrintList(linear_list_t *L) {
    printf("List: ");
    for (int i = 0; i < L->a_len; i++) {
        printf("%d ", L->a[i]);
    }
    printf("\n");
}

/* Test program */
int main() {
    linear_list_t *L = Create();

    Insert(L, 12, 0);
    Insert(L, 15, 1);
    Insert(L, 98, 2);
    Insert(L, 33, 3);
    Insert(L, 76, 4);
    Insert(L, 15, 5);
    Insert(L, 98, 6);

    PrintList(L);

    printf("Locate 33: %d\n", Locate(L, 33));
    printf("Locate 100: %d\n", Locate(L, 100));

    RemoveDup(L);
    PrintList(L);

    Destroy(L);
    return 0;
}