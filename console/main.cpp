#include <iostream>
#include <Windows.h>
using namespace std;

struct node
{
	int data;
	char color;
	node *left, *right, *parent;
};

class RBTree : public node
{
public:
	node *root;

	RBTree() { root = NULL; }

	void addElement(int);
	node *grandparent(node*);
	node *uncle(node*);
	void insert_case1(node*);
	void insert_case2(node*);
	void insert_case3(node*);
	void insert_case4(node*);
	void insert_case5(node*);
	void rightRotate(node*);
	void leftRotate(node*);
	void printTree(node*, int) const;
};

int main()
{
	RBTree ob;
	int data;
	cout << "Enter numbers (till 0):\n";
	while (1)
	{
		cout << "-> "; cin >> data;
		if (!data) break;
		ob.addElement(data);
	}
	/*ob.addElement(1);
	ob.addElement(2);
	ob.addElement(3);
	ob.addElement(4);
	ob.addElement(5);
	ob.addElement(6);
	/*ob.addElement(7);
	ob.addElement(8);
	ob.addElement(9);*/
	ob.printTree(ob.root, 0);
	cout << "\n\n";
	system("pause");
	return 1;
}

void RBTree::addElement(int data)
{
	node *z = new node;
	z->data = data;
	z->left = z->right = z->parent = NULL;
	if (root == NULL)
	{
		z->color = 'B';
		root = z;
	}
	else
	{
		node *y = NULL;
		node *x = root;
		while (x != NULL)
		{
			y = x;
			if (z->data < x->data)
				x = x->left;
			else
				x = x->right;
		}
		z->parent = y;
		if (z->data > y->data)
			y->right = z;
		else
			y->left = z;
		z->color = 'R';
		insert_case1(z);
	}
}

node * RBTree::grandparent(node *n)
{
	if ((n != NULL) && (n->parent != NULL))
		return n->parent->parent;
	else
		return NULL;
}

node * RBTree::uncle(node *n)
{
	node *g = grandparent(n);
	if (g == NULL)
		return NULL;
	if (n->parent == g->left)
		return g->right;
	else
		return g->left;
}

void RBTree::insert_case1(node *n)
{
	if (n->parent == NULL)
		n->color = 'B';
	else
		insert_case2(n);
}

void RBTree::insert_case2(node *n)
{
	if (n->parent->color == 'B')
		return;
	else
		insert_case3(n);
}

void RBTree::insert_case3(node *n)
{
	node *u = uncle(n), *g;

	if ((u != NULL) && (u->color == 'R') && (n->parent->color == 'R')) {
		n->parent->color = 'B';
		u->color = 'B';
		g = grandparent(n);
		g->color = 'R';
		insert_case1(g);
	}
	else {
		insert_case4(n);
	}
}

void RBTree::insert_case4(node *n)
{
	node *g = grandparent(n);

	if ((n == n->parent->right) && (n->parent == g->left)) {
		leftRotate(n->parent);
		n = n->left;
	}
	else if ((n == n->parent->left) && (n->parent == g->right)) {
		rightRotate(n->parent);
		n = n->right;
	}
	insert_case5(n);
}

void RBTree::insert_case5(node *n)
{
	node *g = grandparent(n);

	n->parent->color = 'B';
	g->color = 'R';
	if ((n == n->parent->left) && (n->parent == g->left))
		rightRotate(g);
	else if ((n == n->parent->right) && (n->parent == g->right))
		leftRotate(g);
}

void RBTree::rightRotate(node *y)
{
	node *x = y->left;
	y->left = x->right;
	if (x->right != NULL)
		x->right->parent = y;
	x->parent = y->parent;
	if (x->parent == NULL)
		root = x;
	else if (y == y->parent->left)
		y->parent->left = x;
	else y->parent->right = x;
	x->right = y;
	y->parent = x;
}

void RBTree::leftRotate(node *x)
{
	node *y = x->right;
	x->right = y->left;
	if (x->right != NULL)
		x->right->parent = x;
	y->parent = x->parent;
	if (x->parent == NULL)
		root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else x->parent->right = y;
	y->left = x;
	x->parent = y;
}

void RBTree::printTree(node *root, int level) const
{
	if (!root->right && !root->left)
	{
		for (int i = 0; i < level; i++)
			cout << "\t";
		HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
		if (root->color == 'R')
			SetConsoleTextAttribute(hstdout, 0x0C);
		else
			SetConsoleTextAttribute(hstdout, 0x0B);
		cout << root->data << "\n";
		SetConsoleTextAttribute(hstdout, 0x0F);
	}
	else
	{
		if(root->right) printTree(root->right, level + 1);
		for (int i = 0; i < level; i++)
			cout << "\t";
		HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
		if (root->color == 'R')
			SetConsoleTextAttribute(hstdout, 0x0C);
		else
			SetConsoleTextAttribute(hstdout, 0x0B);
		cout << root->data << "\n";
		SetConsoleTextAttribute(hstdout, 0x0F);
		if(root->left) printTree(root->left, level + 1);
	}
}
