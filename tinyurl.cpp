#include <string>
#include <iostream>
#include <map>
#include <math.h>

using namespace std;
unsigned guid;
char convertor[62] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
		      'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
		      '0','1','2','3','4','5','6','7','8','9'};

struct entry
{
    string uid;
    string url;
};
map<unsigned, entry*> mymap;

class Solution {
public:
    string base62(unsigned guid)
    {
        string str;
        str = "";
        while(guid/62)
        {
            str = convertor[guid%62] + str;
            guid = guid/62;
        }
        str = convertor[guid] + str;
        return str;
    }

    unsigned base10(string uid)
    {
        unsigned temp_guid;
        int i, k;

        temp_guid = 0;
        for(i=uid.size()-1, k=0; i>=0; i--, k++)
        {
            unsigned temp;
            if (uid[i] >= 'a' && uid[i] <= 'z')
                temp = uid[i] - 'a';
            else if (uid[i] >= 'A' && uid[i] <= 'Z')
                temp = uid[i] - 'A' + 26;
            else
                temp = uid[i] - '0' + 52;

            temp_guid += temp*pow(62,k);
        }
        return temp_guid;
    }

    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        entry *temp = new entry;
        string str;

        temp->uid = base62(guid);
        temp->url = longUrl;
        mymap.insert(pair<unsigned, entry*>(guid, temp));
        str = "https://myurl.com/" + temp->uid;

        guid++;
        return str;
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        string temp_uid;
        unsigned temp_guid;
        map<unsigned, entry*>::iterator it;

        temp_uid = shortUrl.substr(18);
        temp_guid = base10(temp_uid);

        it = mymap.find(temp_guid);
        if (it == mymap.end())
        {
            cout<<"error!!\n";
            return NULL;
        }

        return it->second->url;
    }
};

int main()
{
	string url; // = "https://leetcode.com/problems/design-tinyurl";
	// Your Solution object will be instantiated and called as such:
	Solution solution;

	while(cin>>url)
	{
		string str = solution.encode(url);
		cout<<"Encoded :: "<<str<<"\n";
		cout<<"Decoded :: " << solution.decode(str)<<"\n";
	}

	return 0;
}
