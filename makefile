A2: MathOperations.h MathOperations.c BaseConversion.o Fibonacci.o GreatestCommonDivisor.o MathOperations.o PrimalityTest.o PrimeFactorization.o Armstrong.o Factorial.o
	gcc MathOperations.c BaseConversion.o Fibonacci.o GreatestCommonDivisor.o PrimalityTest.o PrimeFactorization.o Armstrong.o Factorial.o -o A2
BaseConversion.o: BaseConversion.c BaseConversion.h
	gcc -c BaseConversion.c -o BaseConversion.o
Fibonacci.o: Fibonacci.c Fibonacci.h
	gcc -c Fibonacci.c -o Fibonacci.o
GreatestCommonDivisor.o: GreatestCommonDivisor.c GreatestCommonDivisor.h
	gcc -c GreatestCommonDivisor.c -o GreatestCommonDivisor.o
PrimalityTest.o: PrimalityTest.c PrimalityTest.h
	gcc -c PrimalityTest.c -o PrimalityTest.o
PrimeFactorization.o: PrimeFactorization.c PrimeFactorization.h
	gcc -c PrimeFactorization.c -o PrimeFactorization.o
Armstrong.o: Armstrong.c Armstrong.h
	gcc -c Armstrong.c -o Armstrong.o
Factorial.o: Factorial.c Factorial.h
	gcc -c Factorial.c -o Factorial.o
clean:
	rm *.o
	rm *A2