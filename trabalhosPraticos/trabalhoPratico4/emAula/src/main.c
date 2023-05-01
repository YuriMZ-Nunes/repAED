#include <stdio.h>
#include <stdlib.h>

int* maxSubsequence(int* nums, int numsSize, int k, int* returnSize);
int verifyIndex(int* max, int k, int index);

int main(){
    
    int k = 3;
    int nums[4] = {-1, -2, 3, 4};

    maxSubsequence(nums, 4, k, &k);

    return 0;
}

int* maxSubsequence(int* nums, int numsSize, int k, int* returnSize){
    int *max = malloc(sizeof(int) * k);
    int bigger = nums[0];
    
    if(k == numsSize)
        return nums;

    for(int i = k - 1; i >= 0; i--){
        bigger = nums[0];
        for(int j = 0; j < numsSize; j++){
            if(nums[j] >= bigger){
                bigger = nums[j];
                if(verifyIndex(max, k, j) == 0)
                    max[i] = j;
            }
        }
    }

    for(int i = 0; i < k; i++){
        max[i] = nums[max[i]];
    }
        
    return max;
}

int verifyIndex(int* max, int k, int index){
    int haveIndex = 0;
    for(int i = 0; i < k; i++){
        if(max[i] == index)
            haveIndex = 1;
    }

    return haveIndex;
}


