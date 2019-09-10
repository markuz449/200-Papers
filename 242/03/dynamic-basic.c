#include <stdio.h>
#include <stdlib.h>

int main(void) {
    
    int a[] = { 5, 4, 3, 2, 1 };
    printf(" a: %p\n", a); /* the array itself */
    printf("&a[0]: %p\n", &a[0]); /* the address of the first element of a */
    printf(" a[0]: %d\n", a[0]); /* the value of the first element of a */
    return EXIT_SUCCESS;
}
