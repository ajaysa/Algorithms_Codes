// https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-046j-introduction-to-algorithms-sma-5503-fall-2005/video-lectures/
// lecture 15 : Dynamic programming

/* Task:
 - Implementing both memoization and dynamic programming approach for longest common subsequence problem
 - Explain and Print space and Time complexity
 - Output both count and an instance of longest common subsequence for both algo approaches
*/

#include<stdio.h>
#include<string.h>

enum ALGORITHM
{
	MEMOIZATION=1,
	DYNAMIC
};

int lcs(int m, int n, int matrix[m][n], char *str1, char *str2, int i, int j, int flag[m][n])
{
	if ( i < 0 || j < 0 )
		return 0;

	if ( matrix[i][j] != -1 )
		return matrix[i][j];

	if (str1[i] == str2[j])
	{
		matrix[i][j] = 1 + lcs(m, n, matrix, str1, str2, i-1, j-1, flag);
		flag[i][j] = 1;
	}
	else
	{
		int t1 = lcs(m, n, matrix, str1, str2, i-1, j, flag);
		int t2 = lcs(m, n, matrix, str1, str2, i, j-1, flag);

		if (t1 > t2)
			matrix[i][j] = t1;
		else
			matrix[i][j] = t2;
	}

	return matrix[i][j];
}

void reconstruction(char *str1, int m, int n, int matrix[m][n], int flag[m][n], int i, int j, char *str, int *k)
{
	if (i < 0 || j < 0)
		return;

	if ( flag[i][j] == 1 )
	{
		str[*k] = str1[i];
		*k = (*k) + 1;
		reconstruction(str1, m, n, matrix, flag, i-1, j-1, str, k);
	}
	else
	{
		if (i-1 >= 0 && j-1 >= 0 )
		{
			if ( matrix[i-1][j] > matrix[i][j-1] )
				reconstruction(str1, m, n, matrix, flag, i-1, j, str, k);
			else
				reconstruction(str1, m, n, matrix, flag, i, j-1, str, k);
		}
		else if ( i-1 >= 0 )
			reconstruction(str1, m, n, matrix, flag, i-1, j, str, k);
		else
			reconstruction(str1, m, n, matrix, flag, i, j-1, str, k);
	}
}

void memoization_algo(char *str1, char *str2)
{
	int m, n;
	int i, j;

	m = strlen(str1);
	n = strlen(str2);
	int matrix[m][n];
	int flag[m][n];
	char str[100];
	int k;

	for(i=0; i<m; i++)
	{
		for(j=0; j<n; j++)
		{
			matrix[i][j] = -1;
			flag[i][j] = 0;
		}
	}

	printf("Length of Longest Common Subsequence = %d\n", lcs(m, n, matrix, str1, str2, m-1, n-1, flag));
/*
	printf("matrix array :: \n");
	for(i=0; i<m; i++)
	{
		for(j=0; j<n; j++)
			printf("%d\t", matrix[i][j]);
		printf("\n");
	}

	printf("flag array :: \n");
	for(i=0; i<m; i++)
	{
		for(j=0; j<n; j++)
			printf("%d\t", flag[i][j]);
		printf("\n");
	}
*/
	k = 0;
	reconstruction(str1, m, n, matrix, flag, m-1, n-1, str, &k);
//	printf("size of returned array :: %d\n", k);

	for(i=0, j=k-1; i<j; i++, j--)
	{
		char temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
	str[k] = '\0';

	printf("A longest Common Subsequence is %s\n", str);
}

void dynamic_prog_algo(char *str1, char *str2)
{

}

void main()
{
	char str1[100], str2[100];
	int input;
	enum ALGORITHM algo;

	printf("Enter first string ::\n");
	scanf("%s", str1);

	printf("Enter second string ::\n");
	scanf("%s", str2);

	printf("Enter 1 for memoization and 2 for Dynamic Programming paradigm ::\n");
	scanf("%d", &input);

	if ( input != 1 && input != 2 )
	{
		printf("wrong choice\n");
		return;
	}

	algo = input;

	if ( algo == MEMOIZATION )
		memoization_algo(str1, str2);
	else
		dynamic_prog_algo(str1, str2);
}
