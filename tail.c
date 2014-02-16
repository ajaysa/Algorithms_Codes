#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void tailN(char *str, int n)
{
	if ( str == NULL )
		return;

	if ( n <= 0 )
		return;

	FILE *fp = fopen(str, "r");
	if ( !fp )
		return;

	int i, j, len, rd, start;
	char *buf;
	char **lastN;

	lastN = (char **)malloc(sizeof(char *) * n);
	i = 0;
	len = 0;
	buf = NULL;
	start = 0;

	while( (rd = getline(&buf, &len, fp) ) != -1 )
	{
		if ( i < n )
		{
			lastN[i] = (char *)malloc(strlen(buf) + 1);
			strcpy(lastN[i], buf);
			i++;
		}
		else
		{
			if ( strlen(buf) > strlen(lastN[start]) )
				lastN[start] = (char *)realloc(lastN[start], strlen(buf) + 1);

			strcpy(lastN[start], buf);
			start++;
			if ( start >= n )
				start = 0;
		}
	}
	fclose(fp);

	if ( i<n )
	{
		for(j=0; j<i; j++)
			printf("%s", lastN[j]);

		for(j=0; j<i; j++)
			free(lastN[j]);
	}
	else
	{
		for(i=start; i<n; i++)
			printf("%s", lastN[i]);
		for(i=0; i<start; i++)
			printf("%s", lastN[i]);

		for(i=start; i<n; i++)
			free(lastN[i]);
		for(i=0; i<start; i++)
			free(lastN[i]);
	}

	free(lastN);
	free(buf);
}

int main()
{
	tailN("output", 1);

	return 0;
}
