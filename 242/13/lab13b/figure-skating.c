#include <stdlib.h>
#include <stdio.h>

int main(void){
    int registration, winreg = 0;
    float s1, s2, s3;
    float score, winscore = 0;

    while (4 == scanf("%d%f%f%f", &registration, &s1, &s2, &s3)){

        if (s1 < s2 && s1 < s3){
            /*printf ("%.1f\n", (s2 + s3) / 2);*/
            score = (s2 + s3) / 2;
        } else if (s2 < s1 && s2 < s3){
            /*printf ("%.1f\n", (s1 + s3) / 2);*/
            score = (s2 + s3) / 2;
        } else {
            /* printf ("%.1f\n", (s1 + s2) / 2);*/
            score = (s2 + s3) / 2;
        }
        
        if (score > winscore){
            winscore = score;
            winreg = registration;
        }
    }

    printf ("%d\n", winreg);
    
    return EXIT_SUCCESS;
}
