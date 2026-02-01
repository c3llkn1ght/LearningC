#include <stdio.h>

int main()
{
	printf("Hello World.\n");

	int i;
	for (i = 0; i <= 100; i++) {
		if (i % 3 == 0 && i % 5 == 0){
			printf("%d, %s\n", i, "fizzbuzz");
		}
		else if (i % 3 == 0){
			printf("%d, %s\n", i, "fizz");
		}
		else if (i % 5 == 0){
			printf("%d, %s\n", i, "buzz");
		}
	}

	return 0;

}