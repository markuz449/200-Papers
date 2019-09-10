#include <stdio.h>
#include <stdlib.h>

#define OCEAN_MAX 41981

struct ocean_datum {
    int x; /* grid-reference east-west */
    int y; /* grid-reference north-south */
    double conc; /* concentration of O_2 in mL/L found at grid-ref (x,y) */
};

void print_ocean_datum(struct ocean_datum *o) {
    printf("%d %d %.4f\n", o->x, o->y, o->conc);
}

int read_ocean_datum(struct ocean_datum *o) {
    return 3 == scanf("%d %d %lg", &o->x, &o->y, &o->conc);
}

int main(void) {
    struct ocean_datum ocean_data[OCEAN_MAX];
    int num_items;
    int p, i, index;
    struct ocean_datum temp;
    int j;
    
    num_items = 0;
    
    while (num_items < OCEAN_MAX && read_ocean_datum(&ocean_data[num_items])) {
        num_items++;
    }
    
    for (p = 0; p < num_items-1; p++){
        index = p; 
        for (i = p + 1; i < num_items; i++){
            if (ocean_data[i].conc < ocean_data[index].conc){
                index = i;
            }
        }
        temp = ocean_data[index];
        ocean_data[index] = ocean_data[p];
        ocean_data[p] = temp;
    }
    
    /* print out the array of structs */
    for (j = 0; j < num_items; j++) {
        print_ocean_datum(&ocean_data[j]);
    }
    
    return EXIT_SUCCESS;
}
