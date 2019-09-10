#include <stdio.h>
#include <stdlib.h>

int main(void){
    double s1, s2, s3;
    int check;
    printf("Please enter the contestants scores: \n");

    fflush(stdout);
    check = scanf("%lg%lg%lg", &s1, &s2, &s3);
     if (check != 3) {
        printf("scanf returned code %d\n", check);
        return EXIT_FAILURE;
        }
     
     if (s1 < s2 && s1 < s3){
         printf ("Average of the top two scores: %.1f\n", (s2 + s3)/2);
     }
     else if (s2 < s1 && s2 < s3){
         printf ("Average of the top two scores: %.1f\n", (s1 + s3)/2);
     }
     else {
         printf ("Average of the top two scores: %.1f\n", (s1 + s2)/2);
     }

    return EXIT_SUCCESS; /* defined in stdlib.h */
}
