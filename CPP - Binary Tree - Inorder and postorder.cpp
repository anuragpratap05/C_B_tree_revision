# C_B_tree_revision#include<bits/stdc++.h>
using namespace std;

class node
{
public:
	int data;
	node* left;
	node* right;

	node(int d)
	{
		data = d;
		left = NULL;
		right = NULL;
	}
};

node* buildtree()
{
	int d;
	cin >> d;
	if (d == -1)
	{
		return NULL;
	}

	node* root = new node(d);
	root->left = buildtree();
	root->right = buildtree();

	return root;

}

void print(node* root)
{
	if (root == NULL)
	{
		return;
	}

	cout << root->data << " ";
	print(root->left);
	print(root->right);
	return;
}

void printinorder(node* root)
{
	if (root == NULL)
	{
		return;
	}
	printinorder(root->left);
	cout << root->data << " " ;
	printinorder(root->right);
	return;
}

void printpostorder(node* root)
{
	if (root == NULL)
	{
		return;
	}

	printpostorder(root->left);
	printpostorder(root->right);
	cout << root->data << " ";
}

int main()
{
#ifndef ONLINE_jUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	//node* root=NULL;
	node* root = buildtree();
	print(root);
	cout << endl;
	printinorder(root);
	cout << endl;
	printpostorder(root);


}
