/*
  References : 
  http://articles.leetcode.com/longest-palindromic-substring-part-ii
*/

#include <iostream>
#include <string>

using namespace std;

class Pallindrome 
{
    public:
        string longestPalindrome(string s)
	{
            string new_str;
            int i;
            int len;
            int right, center;
            int *pall;
            int max_len, max_i;
    
            for (i=0; i<s.size(); i++)
            {
                new_str += '#';
                new_str += s[i];
            }
            new_str += '#';
    
            len = new_str.size();
            pall = new int[len];
    
            for (i=0; i<len; i++)
                pall[i] = 0;
    
            center = 0;
            right = 0;
            for(i=1; i<len; i++)
            {
                int i_mirror = center - (i - center);
    
                if (right > i)
                {
                    if (pall[i_mirror] < right-i)
                        pall[i] =pall[i_mirror];
                    else
                        pall[i] = right-i;
                }
                else
                    pall[i] = 0;
    
                while ( ( i+pall[i]+1 < len && i-pall[i]-1 >= 0 ) && new_str[i+pall[i]+1] == new_str[i-pall[i]-1] )
                    pall[i] += 1;
    
                if ( i+pall[i] > right )
                {
                    center = i;
                    right = i+pall[i];
                }
            }
    
            max_len = 0;
            for(i=0; i<len; i++)
            {
                if ( max_len < pall[i] )
                {
                    max_len = pall[i];
                    max_i = i;
                }
            }
    
            delete []pall;
            return s.substr( (max_i-max_len)/2, max_len);
    	}
};

int main()
{
	Pallindrome p;
	string str1 = "aaaaa";
	string str2 = "aaaaaa";
	string str3 = "aaaba";

	cout << str1 << " = " << p.longestPalindrome(str1) << "\n";
	cout << str2 << " = " << p.longestPalindrome(str2) << "\n";
	cout << str3 << " = " << p.longestPalindrome(str3) << "\n";

	return 0;
}
