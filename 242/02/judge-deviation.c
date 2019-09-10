#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void){
    double av1 = 0, av2 = 0, av3 = 0;
    int registration;
    double judge1[10], judge2[10], judge3[10];
    double judge1_dev = 0, judge2_dev = 0, judge3_dev = 0;
    int lines = 0;
    int i;

    /* Add values to arrays and find the mean */
    while (4 == scanf("%d%lg%lg%lg", &registration, &judge1[lines], &judge2[lines], &judge3[lines])){
        av1 = av1 + judge1[lines];
        av2 = av2 + judge2[lines];
        av3 = av3 + judge3[lines];
        lines ++;
    }
    av1 = av1 / lines;
    av2 = av2 / lines;
    av3 = av3 / lines;

    /* Find the standard deviation for each judge */
    for (i = 0;  i < lines; i++){
        judge1_dev = judge1_dev + pow((judge1[i] - av1), 2);
        judge2_dev = judge2_dev + pow((judge2[i] - av2), 2);
        judge3_dev = judge3_dev + pow((judge3[i] - av3), 2);
    }
    judge1_dev = sqrt(judge1_dev / (lines-1));
    judge2_dev = sqrt(judge2_dev / (lines-2));
    judge3_dev = sqrt(judge3_dev / (lines-3));
    
    /* Print statements */
    printf("          Average SD\n");
    printf("Judge 1 : %.1f     %.1f\n", av1, judge1_dev);
    printf("Judge 2 : %.1f     %.1f\n", av2, judge2_dev);
    printf("Judge 3 : %.1f     %.1f\n", av3, judge3_dev);

    return EXIT_SUCCESS;
}
