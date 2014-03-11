#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct tree
{
	char val;
	int freq;
	tree *left;
	tree * right;
};

struct compare
{
	bool operator() ( tree *left, tree *right )
	{
		return (left->freq) > (right->freq);
	}
};

bool find_code(tree *node, char ch, string &str);
void release_mem(tree *node);

int main()
{
	priority_queue <tree *, vector<tree*>, compare> pri_queue;
	char input_char[6] = { 'a', 'b', 'c', 'd', 'e', 'f' };
	int  input_freq[6] = {  45,  13,  12,  16,  9,   5 };
	tree *temp, *root;
	int i, count;

	for(i=0; i<6; i++)
	{
		temp = new tree;
		temp->val = input_char[i];
		temp->freq = input_freq[i];
		temp->left = temp->right = NULL;
		pri_queue.push(temp);
	}

	count = pri_queue.size();
	for ( i=0; i<count-1; i++)
	{
		temp = new tree;
		temp->left  = pri_queue.top();
		pri_queue.pop();
		temp->right = pri_queue.top();
		pri_queue.pop();

		temp->val = '\0';
		temp->freq = temp->left->freq + temp->right->freq;

		pri_queue.push(temp);
	}

	root = pri_queue.top();
	pri_queue.pop();
	cout<<" root->freq = "<<root->freq<<"\n";

	for(i=0; i<6; i++)
	{
		string str;
		find_code(root,input_char[i],str);
		cout<<" Hufman code for "<< input_char[i] << " = ";
		for (string::reverse_iterator rit=str.rbegin(); rit!=str.rend(); ++rit)
			cout<<*rit;
		cout<<"\n";
	}

	release_mem(root);

	return 0;
}

bool find_code(tree *node, char ch, string &str)
{
	if ( node->left == NULL && node->right == NULL )
	{
		if ( node->val == ch )
			return true;
		else
			return false;
	}

	if ( find_code(node->left, ch, str) )
	{
		str += '0';
		return true;
	}
	else if ( find_code(node->right, ch, str) )
	{
		str += '1';
		return true;
	}
	else
		return false;
}

void release_mem(tree *node)
{
	if ( node == NULL )
		return;

	release_mem(node->left);
	release_mem(node->right);

	node->left = node->right = NULL;
	delete node;
}
