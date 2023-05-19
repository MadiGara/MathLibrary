#include "Armstrong.h"

int checkArmstrong(int numToCheck, int * success) {
    int numDigits, digit, sum, originalNum;
    numDigits = 0;
    sum = 0;

    if(numToCheck < 0) {
        //error - armstrong numbers can't be negative
        return numToCheck;
    }

    //save a copy 
    originalNum = numToCheck;

    //find number of digits
    while(numToCheck != 0) {
        numToCheck = numToCheck/10;
        ++numDigits;
    }

    //set numToCheck back to original
    numToCheck = originalNum;

    //check: is the number the sum of its own digits raised to the power of numDigits?
    while(numToCheck > 0) {
        digit = numToCheck % 10;
        //power function from math.h
        sum = sum + pow(digit, numDigits);
        numToCheck = numToCheck/10; 
    }

    if(sum == originalNum) {
        printf("%d is an Armstrong number\n", originalNum);
    } else {
        printf("%d is not an Armstrong number\n", originalNum);
    }

    return 0;
}

