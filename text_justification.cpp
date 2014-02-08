#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include <string>

using namespace std;

int main()
{
	string line, word;
	int i, j;
	int total_len = 144;
	int EMPTY = 0;

	vector <string> carry;

	while(1)
	{
		int space = 0;
		int linelen = 0;

		vector <string> word_list;

		if ( carry.size() > 0 )
		{	
			int rem_carry=0;
			for(i=0; i<carry.size(); i++)
			{
				if ( linelen + carry[i].length() <= total_len )
				{
					word_list.push_back(carry[i]);
					linelen += carry[i].length();
					space++;
					linelen += 1;
					rem_carry++;
				}
				else
					break;
			}
			carry.erase(carry.begin(), carry.begin()+rem_carry);
		}

               if ( total_len > linelen )
               {
			while ( total_len > linelen )
			{
				int FLAG = 0;
				if ( getline(cin, line) )
				{
					stringstream str(line);
					while(str>>word)
					{
						if ( linelen + word.length() <= total_len && FLAG == 0 )
						{
							word_list.push_back(word);
							linelen += word.length();
							space++;
							linelen += 1;
						}
						else
						{
							FLAG = 1;
							carry.push_back(word);
						}
					}
				}
				else
				{
					EMPTY = 1;
					break;
				}

				if ( FLAG == 1 )
					break;
			}
		}

		space--;
		linelen -= 1;

		vector <int> space_list;
		for(i=0; i<space; i++)
			space_list.push_back(1);

		if ( total_len > linelen && EMPTY == 0 )
		{
			int left = total_len - linelen;
			while ( left > space )
			{
				for(i=0; i<space; i++)
					space_list[i]++;
				left = left - space;
			}
			if ( left > 0 )
			{
				srand(time(0));
				vector <int> rndm;
				for(i=0; i<left; i++)
				{
					int num = rand() % space;
					for(j=0; j<rndm.size(); j++)
					{
						if ( rndm[j] == num )
							break;
					}
					if ( rndm.size() == 0 || j == rndm.size() )
						rndm.push_back(num);
					else
						i--;
				}

				for(i=0; i<rndm.size(); i++)
					space_list[rndm[i]]++;
			}
		}

		for(i=0; i<word_list.size(); i++)
		{
			cout<<word_list[i];
			if ( i < word_list.size()-1 )
			{
				for(j=0; j<space_list[i]; j++)
					cout<<" ";
			}
		}
		if ( word_list.size() > 0 )
			cout<<"\n";

		if ( EMPTY == 1 )
		{
			for(i=0; i<carry.size(); i++)
			{
				cout<<carry[i];
				if ( i < carry.size() -1 )
					cout<<" ";
			}

			if ( carry.size() > 0 )
				cout<<"\n";
			break;
		}

		word_list.clear();
		space_list.clear();
	}
	return 0;
}
