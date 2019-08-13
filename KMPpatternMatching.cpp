// implement KMP pattern matching algorithm
#include <iostream>
#include <string>
#include <vector>

using namespace std;
vector<int> findAllmatchingPattern(string word, string pattern)
{
	vector<int> vec;

	if(pattern.size() > word.size())
	{
		vec.push_back(-1);
		return vec;
	}

	int n = pattern.size();
	int KMP[n];
	int i, j, k;
	int count;
	bool bFound;
	
	KMP[0] = 0;
	for(i=1; i<n; i++)
	{
		j = 0;
		k = i;
		count = 0;
		while(j<i && k>0)
		{
			if (pattern[j] == pattern[k])
				count++;
			else
				break;
			j++;
			k--;
		}
		KMP[i] = count;
	}

	//cout<<"KMP Table :: ";
	//for(i=0; i<n; i++)
	//	cout<<KMP[i]<<" ";
	//cout<<"\n";

	i = 0;
	j = 0;
	k = 0;
	bFound = false;
	while(i<word.size())
	{
		//cout<<"i = "<<i<<" and j = "<<j<<"\n";
		if (word[i] == pattern[j])
		{
			i++;
			j++;
		}
		else
		{
			if (j > 0)
			{
				j = KMP[j-1];
				k = i - KMP[j-1];
			}
			else
			{
				j = 0;
				i = i+1;
				k = i;
			}
		}

		if (j >= pattern.size())
		{
			bFound = true;
			vec.push_back(k);
			//cout<<"found at position : " <<k<<"\n";
			k = i - KMP[j-1];
			j = KMP[j-1];
		}
	}

	if(!bFound)
		vec.push_back(-1);

	return vec;
}
 
int main()
{
	string pattern, word;

	cout<<"enter word\n";
	cin>>word;

	cout<<"enter pattern to search\n";
	cin>>pattern;

	vector <int> vec;
	vec = findAllmatchingPattern(word, pattern);

	int i;
	if (vec[0] == -1)
	{
		cout<<"No match\n";
	}
	else
	{
		for(i=0; i<vec.size(); i++)
		{
			cout<<vec[i]<<"\n";
		}
	}

	return 0;
}
