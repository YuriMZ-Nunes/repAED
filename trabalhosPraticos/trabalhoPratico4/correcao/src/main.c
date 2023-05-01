#include <stdio.h>
#include <stdlib.h>

int* maxSubsequence(int* nums, int numsSize, int k, int* returnSize);
void selectionSort(int* nums, int numsSize);
int verifyIndex(int* max, int k, int index);

int main(){
    
    int k = 8;
    int nums[86] = {-16,-13,8,16,35,-17,30,-8,34,-2,-29,-35,15,13,-30,-34,6,15,28,-23,34,28,-24,15,-17,10,31,32,-3,-36,19,31,-5,-21,-33,-18,-23,-37,-15,12,-28,-40,1,38,38,-38,33,-35,-28,-40,4,-15,-29,-33,-18,-9,-29,20,1,36,-8,23,-34,16,-7,13,39,38,7,-7,-10,30,9,26,27,-37,-18,-25,14,-36,23,28,-15,35,-9,1};


    /*int k = 9;
    int nums[10] = {63,-74,61,-17,-55,-59,-10,2,-60,-65};*/
    maxSubsequence(nums, 86, k, &k);

    return 0;
}

int* maxSubsequence(int* nums, int numsSize, int k, int* returnSize){
    int *max = malloc(sizeof(int) * k);
    int *sorted = malloc(sizeof(int) * numsSize);
    *returnSize = k;
    
    int dup = 0;
    int index = 0;

    int diff;
    diff = numsSize - k;

    if(k == numsSize){
        max = nums;
        return max;
    }

    for(int h = 0; h < numsSize; h++)
        sorted[h] = nums[h];
    
    selectionSort(sorted, numsSize);

    int beginMax = sorted[diff];

    for(int i = diff; i < numsSize; i++){
        if(sorted[i] == beginMax)
            dup++;
        else break;
    }

    for(int i = 0; i < numsSize; i++){
        if(nums[i] > beginMax)
            max[index++] = nums[i];
        else if(nums[i] == beginMax){
            if(dup > 0){
                max[index++] = nums[i];
                dup--;
            }
        }
    }
    
    for(int i = 0; i < k; i++)
        printf("[%d] ", max[i]);

    return max;
}

void selectionSort(int* nums, int numsSize){
    int minInx, aux;

    for(int i = 0; i < numsSize - 1; i++){
        minInx = i;
        for(int j = i + 1; j < numsSize; j++){
            if(nums[j] < nums[minInx]){
                minInx = j;
            }
        }
        aux = nums[minInx];
        nums[minInx] = nums[i];
        nums[i] = aux;
    }
}