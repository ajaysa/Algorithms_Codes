// https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-046j-introduction-to-algorithms-sma-5503-fall-2005/video-lectures/
// lecture 15 : Dynamic programming

/* Task:
 - Implementing both memoization and dynamic programming approach for longest common subsequence problem
 - Explain and Print space and Time complexity
 - Output both count and an instance of longest common subsequence for both algo approaches
*/

#include<iostream>
#include<string>
#include<vector>

using namespace std;

enum ALGORITHM
{
	MEMOIZATION=1,
	DYNAMIC
};

int lcs(vector < vector<int> > &matrix, vector < vector<int> > &flag, string &str1, string &str2, int i, int j)
{
	if ( i < 0 || j < 0 )
		return 0;

	if ( matrix[i][j] != -1 )
		return matrix[i][j];

	if (str1[i] == str2[j])
	{
		matrix[i][j] = 1 + lcs(matrix, flag, str1, str2, i-1, j-1);
		flag[i][j] = 1;
	}
	else
	{
		int t1 = lcs(matrix, flag, str1, str2, i-1, j);
		int t2 = lcs(matrix, flag, str1, str2, i, j-1);

		if (t1 > t2)
			matrix[i][j] = t1;
		else
			matrix[i][j] = t2;
	}

	return matrix[i][j];
}

void reconstruction(string &str, vector < vector<int> > &matrix, vector < vector<int> > &flag, int i, int j, string &lcs_str)
{
	if (i < 0 || j < 0)
		return;

	if ( flag[i][j] == 1 )
	{
		lcs_str = str[i] + lcs_str;
		reconstruction(str, matrix, flag, i-1, j-1, lcs_str);
	}
	else
	{
		if (i-1 >= 0 && j-1 >= 0 )
		{
			if ( matrix[i-1][j] > matrix[i][j-1] )
				reconstruction(str, matrix, flag, i-1, j, lcs_str);
			else
				reconstruction(str, matrix, flag, i, j-1, lcs_str);
		}
		else if ( i-1 >= 0 )
			reconstruction(str, matrix, flag, i-1, j, lcs_str);
		else
			reconstruction(str, matrix, flag, i, j-1, lcs_str);
	}
}

void memoization_algo(string &str1, string &str2)
{
	int m, n;
	int i, j;
	vector <int> vec;
	vector < vector<int> > matrix;
	vector < vector<int> > flag;
	string lcs_str;

	m = str1.size();
	n = str2.size();
	
	for(i=0; i<m; i++)
	{
		vec.clear();
		for(j=0; j<n; j++)
			vec.push_back(-1);

		matrix.push_back(vec);
	}

	for(i=0; i<m; i++)
	{
		vec.clear();
		for(j=0; j<n; j++)
			vec.push_back(0);

		flag.push_back(vec);
	}

	cout<<"Length of Longest Common Subsequence = "<<lcs(matrix, flag, str1, str2, m-1, n-1)<<"\n";
/*
	cout<<"matrix array :: \n";
	for(i=0; i<m; i++)
	{
		for(j=0; j<n; j++)
			cout<<matrix[i][j]<<"\t";
		cout<<"\n";
	}

	cout<<"flag array :: \n";
	for(i=0; i<m; i++)
	{
		for(j=0; j<n; j++)
			cout<<flag[i][j]<<"\t";
		cout<<"\n";
	}
*/
	lcs_str = "";
	reconstruction(str1, matrix, flag, m-1, n-1, lcs_str);
	cout<<"A longest common subsequence = "<<lcs_str<<"\n";
}

void dynamic_prog_algo(string str1, string str2)
{

}

int main()
{
	string str1, str2;
	int input;
	ALGORITHM algo;

	cout<<"Enter first string ::\n";
	cin>>str1;

	cout<<"Enter second string ::\n";
	cin>>str2;

	cout<<"Enter 1 for memoization and 2 for Dynamic Programming paradigm ::\n";
	cin>>input;

	if ( input != 1 && input != 2 )
	{
		cout<<"wrong choice\n";
		return 1;
	}

	algo = (ALGORITHM)input;

	if ( algo == MEMOIZATION )
		memoization_algo(str1, str2);
	else
		dynamic_prog_algo(str1, str2);

	return 0;
}
