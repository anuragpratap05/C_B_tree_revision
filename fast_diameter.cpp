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

int length(node* root)
{
	if (root == NULL)
	{
		return 0;
	}

	int ls = length(root->left);
	int rs = length(root->right);
	return max(ls , rs) + 1;
}

void print_ktk_level(node* root, int k)
{
	if (root == NULL )
	{
		//cout << root->data << " ";
		return;
	}
	if (k == 1)
	{
		cout << root->data << " ";
		return;
	}

	print_ktk_level(root->left, k - 1);
	print_ktk_level(root->right, k - 1);
	return;
}

void print_all_levels(node* root)
{
	for (int i = 1; i <= length(root); i++)
	{
		print_ktk_level(root, i);
		cout << endl;
	}
}

void bfs(node* root)
{


	queue<node*> q;
	q.push(root);
	q.push(NULL);
	while (!q.empty())
	{
		if (q.front() == NULL)
		{
			cout << endl;
			q.pop();
			if (!q.empty())
			{
				q.push(NULL);
			}
		}
		else
		{
			node* f = q.front();
			cout << f->data << " ";
			q.pop();
			if (f->left)
			{
				q.push(f->left);

			}
			if (f->right)
			{
				q.push(f->right);
			}
		}


	}
	return;
}

int count(node*root)
{
	if (root == NULL)
	{
		return 0;
	}

	int lc = count(root->left);
	int rc = count(root->right);
	return 1 + (lc + rc);
}



int diameter(node* root)
{
	if (root == NULL)
	{
		return 0;
	}

	int h1 = length(root->left);
	int h2 = length(root->right);
	int op1 = h1 + h2;
	int op2 = diameter(root->left);
	int op3 = diameter(root->right);
	return max(op1, max(op2, op3));
}

class Pair
{
public:
	int height;
	int diameter;
};

Pair fastdiameter(node* root)
{
	Pair p;
	if (root == NULL)
	{

		p.height = p.diameter = 0;
		return p;
	}

	Pair left = fastdiameter(root->left);
	Pair right = fastdiameter(root->right);

	p.height = max(left.height , right.height) + 1;
	p.diameter = max(left.height + right.height, max(left.diameter, right.diameter));
	return p;
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
	/*cout << endl;
	cout << length(root) << endl;
	print_all_levels(root);*/
	cout << endl;
	bfs(root);
	cout << endl;
	cout << count(root) << endl;
	cout << "diameter= " << diameter(root) << endl;
	Pair ans = fastdiameter(root);
	cout << ans.height << " " << ans.diameter << endl;

}
