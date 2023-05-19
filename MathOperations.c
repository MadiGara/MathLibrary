/*
    24/11/22 - Test harnesses for each type of testing were done by:
	* Wali and Diya - Data flow testing
	* Madi and Kabir - Structured basis testing
	* Anna and Daniella - Boundary anaylsis testing

	All test harnesses are implemented at the bottom of this file, and called in
	switch option 8 in main. The code being tested is file Factorial.c.

	Refactored by Madison Gara (0973333) 22/09/22
*/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

#include "MathOperations.h"
#include "PrimalityTest.h"
#include "PrimeFactorization.h"
#include "Fibonacci.h"
#include "BaseConversion.h"
#include "GreatestCommonDivisor.h"
#include "Armstrong.h"
#include "Factorial.h"

//function declaration
int boundaryAnalysis(int * success);
int structuredBasisTesting(int * success);
void dataFlow(int * success);

int main(int argc, char * argv[]) {

    //declare variables
	long int i = '\0';
	long int i2 = '\0';
	int baseFrom = '\0';
	int baseTo = '\0';
	char * a = NULL;

	int boolResult = '\0';
	long int longResult = '\0';
	unsigned long int unsignedLResult = '\0';
	char * strResult = NULL;

	int * success = (int *)malloc(sizeof(int));
	*success = '\0';

	int lastDigit = '\0';
	char * ordinalIndicator = NULL;

	//offer menu options for math operations to user
	while(1) {
		do {
			printf("*** FUN WITH MATH OPERATIONS ***\n");
			printf("Select one of the following options to continue (1 - 8):\n");
			printf("1.) Primality Test\n");
			printf("2.) Prime Factorization\n");
			printf("3.) Nth Term in Fibonacci Sequence\n");
			printf("4.) Convert a Number from any Base to any Base\n");
			printf("5.) Greatest Common Divisor\n");
			printf("6.) Determine if number is an Armstrong number\n");
			printf("7.) Factorial function\n");
            printf("8.) Test Cases\n");
			printf("9.) Exit\n");
			printf("Your Selection: ");

			i = retrieveNumericInput(success);
			if(*success != 1 || i > 9 || i < 1) {
				printf("\nError parsing response, please try again.\n");
			}
		} while(*success != 1 || i > 9 || i < 1);

		//execute the math function chosen by the user from the menu with user-input number
		switch(i) {
			//conducts primality test
			case 1:
				do {
					printf("\n~~~~~~~~~~~~~~~~~~~~\n\n");
					printf("Primality Test:\n");
					printf("Enter a Number to Test the Primality Of: ");

					i = retrieveNumericInput(success);
					if(*success != 1) {
						printf("\nError parsing response, please try again.");
					}
				} while(*success != 1);

				if((boolResult = isPrime(i)) == 0) {
					printf("The Number IS NOT Prime.\n");
				} else if(boolResult == 1) {
					printf("The Number IS Prime.\n");
				}

				//reset variables and pointers so ready for the next operation - same across cases	
				*success = '\0';
				boolResult = '\0';
				i = '\0';
				break;

			//calculates prime factorization
			case 2:
				do {
					printf("\n~~~~~~~~~~~~~~~~~~~~\n\n");
					printf("Prime Factorization:\n");
					printf("Enter a Number to take the Prime Factorization Of: ");

					i = retrieveNumericInput(success);
					if(*success != 1) {
						printf("\nError parsing response, please try again.\n");
					} else {
						strResult = primeFactorization(i, success);
						if (strResult == NULL && *success == -1) {
							printf("\nError: Please Enter a Number Greater Than 1.\n");
						}
					}
				} while(*success != 1);

				printf("The Prime Factorization of %ld is:\n%s\n", i, strResult);

				free(strResult);
				strResult = NULL;

				*success ='\0';
				i = '\0';
				break;

			//calculate nth term of the fibonacci sequence
			case 3:
				do {
					printf("\n~~~~~~~~~~~~~~~~~~~~\n\n");
					printf("Nth Term in Fibonacci Sequence:\n");
					printf("Enter the Term of the Fibonacci Sequence You Want: ");

					i = retrieveNumericInput(success);
					if(*success != 1) {
						printf("\nError parsing response, please try again.\n");
					} else {

						unsignedLResult = nthFibonacciTerm(i, success);
						if(*success == -1) {
							printf("\nError: Please Enter a Non-Negative Number.\n");
						} else if(*success == 0 && unsignedLResult == ULONG_MAX) {
							printf("\nError: Number Too Big. Please Enter a Smaller Term.\n");
						}
					}
				} while(*success != 1);

				//assign appropriate suffixes for each number
				lastDigit = i % 10;
				if(lastDigit == 1) {
					ordinalIndicator = "st";
				} else if(lastDigit == 2) {
					ordinalIndicator = "nd";
				} else if(lastDigit == 3) {
					ordinalIndicator = "rd";
				} else {
					ordinalIndicator = "th";
				}

				printf("The %ld%s Term of the Fibonacci Sequence is:\n%lu\n", 
				i, ordinalIndicator, unsignedLResult);

				*success = '\0';
				i = '\0';
				unsignedLResult = '\0';
				lastDigit = '\0';
				ordinalIndicator = NULL;
				break;

			//change the base of a number
			case 4:
				do {
					printf("\n~~~~~~~~~~~~~~~~~~~~\n\n");
					printf("Convert a Number From Any Base to Any Base:\n");
					printf("Enter the Base to Convert From: ");

					baseFrom = retrieveNumericInput(success);

					if(*success != 1) {
						printf("\nError parsing input. Please try again.\n");
						continue;
					} else if(baseFrom < 2 || baseFrom > 36) {
						printf("\nError: Please Enter a Base Between 2 and 36 (Inclusive)\n");
						*success = 0;
						continue;
					}

					printf("Now Enter the Number to Convert: ");
					a = retrieveAlphanumericInput(success, baseFrom);

					if(*success != 1) {
						printf("\nError parsing input. Please try again.\n");
						continue;
					}

					printf("Now Enter the Base to Convert To: ");
					baseTo = retrieveNumericInput(success);

					if(*success != 1) {
						printf("\nError parsing input. Please try again.\n");
						continue;
					} else if(baseTo < 2 || baseTo > 36) {
						printf("\nError: Please Enter a Base Between 2 and 36 (Inclusive)\n");
						*success = 0;
						continue;
					}

					strResult = baseConversion(baseFrom, baseTo, a, success);
					if(*success != 1) {
						printf("\nError Converting Number. Please try again.\n");
						continue;
					}
				} while(*success != 1);

				printf("The Base %d Number %s in Base %d is:\n%s\n", baseFrom, a, baseTo, strResult);

				*success = '\0';
				baseFrom = '\0';
				free(a);
				a = NULL;
				baseTo = '\0';
				free(strResult);
				strResult = NULL;
				break;

			//find greatest common divisor
			case 5:
				do {
					printf("\n~~~~~~~~~~~~~~~~~~~~\n\n");
					printf("Greatest Common Divisor:\n");
					printf("Enter Number 1: ");

					i = retrieveNumericInput(success);

					if(*success != 1) {
						printf("\nError parsing input. Please try again.\n");
						continue;
					}

					if(i == 0) {
						printf("\nError: Please Enter a Non-Zero Number.\n");
						continue;
					}

					printf("Now Enter Number 2: ");
					i2 = retrieveNumericInput(success);

					if(*success != 1) {
						printf("\nError parsing input. Please try again.\n");
						continue;
					}

					if(i == 0) {
						printf("\nError: Please Enter a Non-Zero Number.\n");
						continue;
					}

					longResult = gcd(i, i2, success);

					if(*success != 1) {
						printf("\nError getting result. Please try again.\n");
						continue;
					}

				} while(*success != 1);

				printf("The Greatest Common Divisor of %ld and %ld is\n%ld\n", i, i2, longResult);

				*success = '\0';
				i = '\0';
				i2 = '\0';
				break;
			
			//Checks if input is an Armstrong number 
			//The number itself is the sum of its  own digits raised to the power of the number of digits
			case 6: 
				do {
					int armstrongSuccess = 1;
					printf("\n~~~~~~~~~~~~~~~~~~~~\n\n");
					printf("Armstrong Number:\n");
					printf("Enter a Number: ");

					//Parsing numeric input from the command line input 
					i = retrieveNumericInput(success);
					
					if(*success != 1) {
						printf("\nError parsing input. Please try again.\n");
						continue;
					}

					if(i == 0) {
						printf("\nError: Please Enter a Non-Zero Number.\n");
						continue;
					}

					//longResult = gcd(i, i2, success); - FORMATTING EXAMPLE
					armstrongSuccess = checkArmstrong(i, success);

					if(*success != 1) {
						printf("\nError getting result. Please try again.\n");
						continue;
					}

					if(armstrongSuccess != 0) {
						printf("%d is not an Armstrong number.\n", armstrongSuccess);
					}

				} while (*success != 1);
				
				*success = '\0';
				i = '\0';

				break;

			//calculate factorial of a number 
			case 7:
                do {
                    int factorialSuccess = 1;
                    printf("\n~~~~~~~~~~~~~~~~~~~~\n\n");
                    printf("Factorial number:\n");
                    printf("Enter a number: ");

                    //Parsing numeric input from the command line input 
                    i = retrieveNumericInput(success);

                    if(*success != 1) {
                        printf("\nError parsing input. Please try again.\n");
                        continue;
                    }

                    factorialSuccess = factorial(i, success);
                    
                    if(*success != 1) {
                        printf("\nError getting result. Please try again.\n");
                        continue;
                    }

                    if(factorialSuccess != 0) {
                        printf("The factorial is %d\n", factorialSuccess);
                    }

                } while (*success != 1);

                *success = '\0';
                i = '\0';
                break;

            //test cases for Factorial.c 
            case 8:
                do {
                    int boundaryTestSuccess = 0;
					int structuredBasisSuccess = 0;
                    printf("\n~~~~~~~~~~~~~~~~~~~~\n\n");
                    printf("Test cases\n");

                    if(*success != 1) {
                        printf("\nError parsing input. Please try again.\n");
                        continue;
                    }

                    //testing boundary analysis cases - Anna and Daniella
                    //note: not all boundary cases are expected to pass in this program
                    boundaryTestSuccess = boundaryAnalysis(success);
                    if (boundaryTestSuccess == 1){
                        printf("All boundary analysis test cases passed.\n");
                    }
                    else {
                        printf("Not all boundary analysis cases passed.\n");
                    }

					//testing structured basis cases - Madi and Kabir
                    //note: one test case should throw a warning because testing doubles handling
                    structuredBasisSuccess = structuredBasisTesting(success);
                    if (structuredBasisSuccess == 1){
                        printf("\nAll structured basis test cases passed.\n");
                    }
                    else {
                        printf("\nNot all structured basis test cases passed.\n");
                    }
					
					//data flow testing - Wali and Diya
					printf("\n\nData Flow Test Cases:\n\n");
					dataFlow(success);

                } while (*success != 1);

                *success = '\0';
                i = '\0';
                break;


			//reset variables and exit program
			case 9: 
				free(success);
				success = NULL;
				return 0;
				break;


			//reprint the menu
			default:
				free(success);
				success = NULL;
				return 1;
		}
		printf("\n~~~~~~~~~~~~~~~~~~~~\n\n");
	}	
}

//format user input to proper number format
long int retrieveNumericInput(int * success) {
	char * input = NULL;
	char * endptr = NULL;
	retrieveInput(&input, success, 10);

	if(input == NULL || *success != 1) {
		*success = 0;
		return '\0';
	}

	long int ret = '\0';
	errno = 0;
	ret = strtol(input, &endptr, 10);

	free(input);
	input = NULL;

	if(input == endptr) {
		*success = 0;
		return '\0';
	}

	if((ret == LONG_MAX || ret == LONG_MIN) && errno == ERANGE) {
		*success = 0;
		return '\0';
	}

	*success = 1;
	return ret;
}

//format alphanumeric user input
char * retrieveAlphanumericInput(int * success, int base) {
	char * input = NULL;
	retrieveInput(&input, success, base);

	if(input == NULL || *success != 1) {
		*success = 0;
		return NULL;
	}

	*success = 1;
	return input;
}

//retrieve the user input and allocate space for it
void retrieveInput(char ** input, int * success, int base) {
	if(input == NULL || success == NULL || (base < 2 || base > 36)) {
		return;
	} else {
		*success = '\0';
	}

	int size = 128;
	*input = (char *)malloc(sizeof(char) * size);

	(*input)[size - 1] = '\0';

	if(*input == NULL) {
		*success = 0;
		return;
	}

	char * newInput = NULL;
	char maxChar = '\0';
	char c = '\0';
	int len = 0;

	if(base <= 10) {
		maxChar = base + '0' - 1;
	} else {
		maxChar = 'A' + (base - 11);
	}

	do {
		c = getchar();
		c = toupper(c);

		if(isspace(c)) {
			continue;
		}

		//coding style note: prioritizing "all of statement in one line" rule over "lines are 100 characters max"
		if((!isalnum(c) && (c != '-' && c != '+')) || ((c == '-' || c == '+') && len != 0) || c > maxChar) {
			free(*input);
			*input = NULL;
			*success = 0;
			while ((c = getchar()) != '\n' && c != EOF);
			return;
		}

		if(len == (size - 1)) {
			size += 64;

			newInput = (char*)realloc(*input, sizeof(char) * size);

			if(newInput == NULL) {
				*success = 0;
				free(*input);
				*input = NULL;
				return;
			} else {
				*input = newInput;
				newInput = NULL;
			}
		}

		if(len == 0) {
			if(c != '-' && c != '+') {
				(*input)[len] = '+';
				len++;
			}
		}

		(*input)[len] = c;
		len++;

	} while(c != '\n' && c != EOF);

	if(len == 0) {
		free(*input);
		*input = NULL;
		*success = 0;
		return;
	}

	newInput = (char*)realloc(*input, sizeof(char) * len + 1);

	if(newInput == NULL) {
		*success = 0;
		free(*input);
		*input = NULL;
		return;
	} else {
		*input = newInput;
		newInput = NULL;
	}

	*success = 1;
	(*input)[len] = '\0';
}

//boundary analysis - Anna and Daniella
int boundaryAnalysis(int * success){

    printf("Boundary Analysis Test Cases\n\n");

    //variables
    int num = 0;
    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    int num4 = 0;
    
    //number is zero
    //note: case is expected to pass
    int test1 = factorial(0, success);
    printf("Expected result = 1\n");
    printf("Actual result = %d\n", test1);
    //check if case passed
    if (test1 == 1){
        printf("Test case 1 passed.\n\n");
        num1 = 1;
    }
    else {
        printf("Test case 1 failed.\n\n");
        num1 = 0;
    }

    //negative number
    //note: case is expected to pass
    int test2 = factorial(-2, success);
    printf("Expected result = -7 (Error code for negative number)\n");
    printf("Actual result = %d\n", test2);
    //check if case passed
    if (test2 == -7){
        printf("Test case 2 passed.\n\n");
        num2 = 1;
    }
    else {
        printf("Test case 2 failed.\n\n");
        num2 = 0;
    }

    //positive number (small)
    //note: case is expected to pass
    int test3 = factorial (9, success);
    printf("Expected result = 362880\n");
    printf("Actual result = %d\n", test3);
    //check if case passed
    if (test3 == 362880){
        printf("Test case 3 passed.\n\n");
        num3 = 1;
    }
    else {
        printf("Test case 3 failed.\n\n");
        num3 = 0;
    }

    //positive number (large)
    //note: program only gives correct values up to and including 12
    //note: case is expected to fail
    int test4 = factorial(13, success);
    printf("Expected result = 6227020800\n");
    printf("Actual result = %d\n", test4);
    //check if case passed
    if (test4 == 6227020800){
        printf("Test case 4 passed.\n");
        num4 = 1;
    } 
    else {
        printf("Test case 4 failed.\n\n");
        num4 = 0;
    }

    //check if all test cases are passed
    if (num1 == 1 && num2 == 1 && num3 == 1 && num4 == 1){
        num = 1;
    } 
    //if any cases failed, return 0
    else {
        num = 0;
    }
    
    return num;
}

//Structured Basis Testing - Madi and Kabir
int structuredBasisTesting(int * success){
	int testSuccess = 0;
    int num1 = 4;
    int num2 = 2.3; //checking for truncation
    int num3 = 0;
    int num4 = -3; //should print
	int num5 = 5;

	printf("\nStructured Basis Testing Cases\n\n");
    
    //Included in if statement - larger
    int test1 = factorial(num1, success);
    printf("Expected result = 24\n");
    printf("Actual result = %d\n\n", test1);
    if (test1 == 24){
        printf("Structured basis test case 1 passed.\n");
		testSuccess = 1;
    }

    //Include in if statement – larger decimal
    int test2 = factorial(num2, success);
    printf("Expected result = 2 (Truncates double)\n");
    printf("Actual result = %d\n", test2);
    if (test2 == 2){
        printf("\nStructured basis test case 2 passed.\n");
        testSuccess = 1;
    }

    //Included in if statement - same as 0
    int test3 = factorial (num3, success);
    printf("Expected result = 1\n");
    printf("Actual result = %d\n", test3);
	if (test3 == 1) {
		printf("\nStructured basis test case 3 passed.\n");
		testSuccess = 1;
	}

    //Excluded from if statement - smaller
	int test4 = factorial (num4, success);
    printf("Expected result = -7 (Prints error message)\n");
    printf("Actual result = %d\n", test4);
	if (test4 == -7) {
		printf("\nStructured basis test case 4 passed.\n");
		testSuccess = 1;
	}

	//Return value is positive, as all factorials are positive
	int test5 = factorial (num5, success);
    printf("Expected result = 120 (Prints error message)\n");
    printf("Actual result = %d\n", test5);
	if (test4 == 120) {
		printf("\nStructured basis test case 5 passed.\n");
		testSuccess = 1;
	}

    return testSuccess;
}

//Data Flow Testing - Wali and Diya
void dataFlow(int * success){
   int setOne;
   int setTwo;
   int setThree;
   int setFour;
 
   //Set 1 num is assigned a value of 1 to take if branch at Line 15
   setOne = factorial(2, success);
   printf("Input 2: The first call takes if Branch and should return 2: %d\n", setOne);
   if(setOne != 2) {
       printf("Test 1 Failed\n");
   } else {
       printf("Test 1 Passed\n");
   }
   //Set 2 num is assigned a value of -1 to traverse else branch at Line 21
   printf("Input -1: The second call takes else Branch and should print Error and return -7\n");
   setTwo = factorial(-1, success);
   printf("Return Value for call 2: %d\n", setTwo);
   if(setTwo != -7) {
       printf("Test 2 Failed\n");
   } else {
       printf("Test 2 Passed\n");
   }
   //Set 3 a float number is sent in as a parameter, should send error
   setThree = factorial (2.5, success);
  
   printf("Input 2.5: The third call test float input should return Error:\n");
   printf("Actual Result: %d\n", setThree);
   if(setThree != -7) {
       printf("Test 3 Failed\n");
   } else {
       printf("Test 3 Passed\n");
   }
   //Set 4 aschii value is sent in as a param, should send eror
   setFour = factorial('a', success);
   printf("Input char 'a': The fourth call is a char input and should return Error\n");
   printf("Actual Result: %d\n", setFour);
  
   if(setFour != -7) {
       printf("Test 4 Failed\n");
   } else {
       printf("Test 4 Passed\n");
   }
 
}
