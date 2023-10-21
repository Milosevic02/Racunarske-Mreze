#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h> #include <stdlib.h>
int main()
{
	char str[1000], ch;
	int i = 0, frequency = 0;
	printf("Enter a string: ");
	gets_s(str,999);
	while (true) {
		printf("Enter a character to find the frequency: ");
		scanf("%c", &ch);
		getchar();
		if (ch == 'q') {
			break;
		}
		for (i=0; str[i] != '\0'; ++i)
		{
			if (ch == str[i])
				++frequency;
		}
		printf("Frequency of %c = %d", ch, frequency);
		frequency = 0;

	}

	return 0;
}