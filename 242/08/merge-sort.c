#include <stdio.h>
#include <stdlib.h>

#define ARRAY_LEN 100000

void merge (int *a, int *workspace, int len){
    int i = 0;
    int j = len / 2;
    int w = 0;

    while (i < len/2 && j < len){
        if (a[i] < a[j]){
            workspace[w++] = a[i++];
        } else {
            workspace[w++] = a[j++];
        }
    }
    while (i != (len / 2)){
        workspace[w++] = a[i++];
    }
    while (j != len){
        workspace[w++] = a[j++];
    }
    
}

void mergeSort (int *nums, int *w, int n){
    int count;
    if (n < 2){
        return;
    }
    mergeSort(nums, w, (n / 2));
    mergeSort((nums + (n / 2)), w, (n-(n / 2)));
    merge(nums, w, n);

    for (count = 0; count < n; count++){
       nums[count] = w[count];
    }
}


int main(void) {
    int nums[ARRAY_LEN];
    int workspace[ARRAY_LEN];
    int count = 0, i;

    while (count < ARRAY_LEN && 1 == scanf("%d", &nums[count])) {
        count++;
    }

    mergeSort(nums, workspace, count);

    for(i = 0; i < count; i++){
        printf("%d ", workspace[i]);
    }
    printf("\n");
    
    return EXIT_SUCCESS;
}
        
