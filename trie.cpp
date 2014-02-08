#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Node
{
	char val;
	bool marker;
	vector <Node *> child;
	public:
		Node()
		{
			val = ' ';
			marker = false;
		}

		Node * findchar(char ch)
		{
			int i;
			for(i=0; i<child.size(); i++)
			{
				if ( child[i]->val == ch )
					return child[i];
			}
			return NULL;
		}

		void setchar(char ch);
		void addchild(Node *temp);
		
		void setmarker()
		{
			marker = true;
		}

		bool getmarker()
		{
			return marker;
		}
};

void Node::setchar(char ch)
{
	val = ch;
}

void Node::addchild(Node *temp)
{
	child.push_back(temp);
}

class Trie
{
	Node *root;
	public:
		Trie()
		{
			root = new Node;
		}

		void add(string str)
		{
			Node *current = root;
			int i;

			if ( str.length() == 0 )
				return;

			for(i=0; str[i] != '\0'; i++)
			{
				Node *temp = current->findchar(str[i]);
				if ( temp )
				{
					current = temp;
				}
				else
				{
					temp = new Node;
					temp->setchar(str[i]);

					current->addchild(temp);
					current = temp;
				}
			}

			current->setmarker();
		}

		bool findstr(string str)
		{
			Node *current = root;
			int i;

			if ( current )
			{
				for(i=0; str[i] != '\0'; i++)
				{
					Node *temp = current->findchar(str[i]);
					if ( !temp )
						return false;
					current = temp;
				}
				return current->getmarker();
			}
		}					
};

int main()
{
	Trie tr;

	tr.add("ajay");
	tr.add("saini");

	if ( tr.findstr("ajay") )
		cout<<"ajay found\n";
	else
		cout<<"ajay not found\n";
	
	if ( tr.findstr("sainiii") )
		cout<<"sainiii found\n";
	else
		cout<<"sainiii not found\n";

	return 0;
}
