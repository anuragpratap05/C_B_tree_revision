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
	if (k == 0)
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

int replacesum(node* root)
{
	if (root == NULL)
	{
		return 0;
	}
	if (root->left == NULL and root->right == NULL)
	{
		return root->data;
	}

	int leftsum = replacesum(root->left);
	int rightsum = replacesum(root->right);

	int temp = root->data;
	root->data = leftsum + rightsum;
	return temp + root->data;

}

class pairs
{
public:
	int height;
	bool bal;
};

pairs isbalanced(node* root)
{
	pairs p;
	if (root == NULL)
	{
		p.height = 0;
		p.bal = true;
		return p;
	}

	pairs left = isbalanced(root->left);
	pairs right = isbalanced(root->right);

	p.height = max(left.height, right.height) + 1;
	if (abs(left.height - right.height) <= 1 and left.bal and right.bal)
	{
		p.bal = true;
	}
	else
	{
		p.bal = false;
	}
	return p;
}

node* buildtree_fromarray(int * a, int s, int e)
{
	if (s > e)
	{
		return NULL;
	}
	int mid = (s + e) / 2;
	node* root = new node(a[mid]);
	root->left = buildtree_fromarray(a, s, mid - 1);
	root->right = buildtree_fromarray(a, mid + 1, e);
	return root;
}

node* buildtree_from_trav(int* pre, int* in, int s, int e)
{
	if (s > e)
	{
		return NULL;
	}

	static int i = 0;
	node *root = new node(pre[i]);
	int index = -2;
	for (int j = s; j <= e; j++)
	{
		if (in[j] == pre[i])
		{
			index = j;
		}
	}
	i++;
	root->left = buildtree_from_trav(pre, in, s, index - 1);
	root->right = buildtree_from_trav(pre, in, index + 1, e);
	return root;

}
void rightview(node* root, int level, int & maxlevel)
{
	if (root == NULL)
	{
		return;
	}

	if (maxlevel < level)
	{
		cout << root->data << " ";
		maxlevel = level;
	}

	rightview(root->right, level + 1, maxlevel);
	rightview(root->left, level + 1, maxlevel);
	//return;


}

int print_at_distace_K(node* root, node* target, int k)
{
	if (root == NULL)
	{
		return -1;
	}

	if (root == target)
	{
		print_ktk_level(target, k);
		return 0;
	}

	int dl = print_at_distace_K(root->left, target, k);

	if (dl != -1)
	{
		if (dl + 1 == k)
		{
			cout << root->data << " ";

		}
		else
		{
			print_ktk_level(root->right, k - 2 - dl);

		}
		return dl + 1;
	}
	int dr = print_at_distace_K(root->right, target, k);

	if (dr != -1)
	{
		if (dr + 1 == k)
		{
			cout << root->data << " ";
		}
		else
		{
			print_ktk_level(root->left, k - 2 - dr);
		}
		return dr + 1;
	}

	return -1;
}
node* lca(node* root, int a, int b)
{
	if (root == NULL)
	{
		return NULL;
	}

	if (root->data == a or root->data == b)
	{
		return root;
	}

	node* leftans = lca(root->left, a, b);
	node* rightans = lca(root -> right, a, b);

	if (leftans != NULL and rightans != NULL)
	{
		return root;
	}

	if (leftans == NULL)
	{
		return rightans;
	}
	return leftans;
}

class newpair
{
public:
	int branchsum;
	int maxsum;
	newpair()
	{
		branchsum = 0;
		maxsum = 0;
	}
};


newpair maxsumpath(node* root)
{
	newpair p;
	if (root == NULL)
	{
		return p;
	}

	newpair leftans = maxsumpath(root->left);
	newpair rightans = maxsumpath(root->right);

	int op1 = root->data;
	int op2 = leftans.branchsum + root->data;
	int op3 = rightans.branchsum + root->data;
	int op4 = (leftans.branchsum + rightans.branchsum) + root->data;

	int curr_ans_thu_root = max(op1, max(op2, max(op3, op4)));

	p.branchsum = max(leftans.branchsum, max(rightans.branchsum, 0)) + root->data;
	p.maxsum = max(leftans.maxsum, max(rightans.maxsum, curr_ans_thu_root));
	return p;
}

int search(node* root, int key, int level)
{
	if (root == NULL)
	{
		return -1;
	}

	if (root->data == key)
	{
		return level;
	}

	int left = search(root->left, key, level + 1);
	int right = search(root->right, key, level + 1);

	if (left != -1)
	{
		return left;
	}
	return search(root->right, key, level + 1);
}

int shortest_dist(node* root, int a, int b)
{
	node* ans = lca(root, a, b);

	int l1 = search(ans, a, 0);
	int l2 = search(ans, b, 0);
	return l1 + l2;
}

int main()
{
#ifndef ONLINE_jUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	//node* root=NULL;
	node* root = buildtree();
	bfs(root);
	cout << endl;
	newpair ans = maxsumpath(root);
	cout << ans.maxsum << endl;
	cout << shortest_dist(root, 14, 7);
	/*print(root);
	cout << endl;
	printinorder(root);
	cout << endl;
	printpostorder(root);*/
	/*cout << endl;
	cout << length(root) << endl;
	print_all_levels(root);*/
	/*cout << endl;
	bfs(root);
	cout << endl;*/
	/*cout << count(root) << endl;
	cout << "diameter= " << diameter(root) << endl;
	Pair ans = fastdiameter(root);
	cout << ans.height << " " << ans.diameter << endl;*/
	/*replacesum(root);
	bfs(root);

	cout << endl;

	pairs ans = isbalanced(root);
	if (ans.bal)
	{
		cout << "balanced tree";
	}
	else
	{
		cout << " unbalnced tree";
	}*/
	/*int pre[] = {1, 2, 3, 4, 8, 5, 6, 7};
	int in[] = {3, 2, 8, 4, 1, 6, 7, 5};
	int n = 8;

	node* root = buildtree_from_trav(pre, in, 0, n - 1);

	bfs(root) ;
	int maxlevel = -1;
	rightview(root, 0, maxlevel);*/

	/*node* target = root->left;
	cout << "data = " << target->data << endl;
	print_at_distace_K(root, target, 3);
	cout << endl;
	node* ans = lca(root, 7, 14);
	cout << ans->data;*/





}
