#include <stdio.h>
#include <stdlib.h>

int main(void){
    double s1, s2, s3;
    int registration;
    int winner_num = 0;
    double winner_score = 0.0;

    while (4 == scanf("%d%lg%lg%lg", &registration, &s1, &s2, &s3)){
        if (((s1 + s2 + s3) / 2) > winner_score){
            winner_score = ((s1 + s2 + s3) / 2);
            winner_num = registration;
        }
    }
    printf("The winner is number: %d, with an average of %.1f\n", winner_num, winner_score);

    return EXIT_SUCCESS; /* defined in stdlib.h */
}
