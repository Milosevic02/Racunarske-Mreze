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
	printf("Enter a character to find the frequency: ");
	scanf("%c", &ch);
	for (; str[i] != '\0'; ++i)
	{
		if (ch == str[i])
			++frequency;
	}
	printf("Frequency of %c = %d", ch, frequency);
	return 0;
}