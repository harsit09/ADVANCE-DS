#include <bits/stdc++.h>
using namespace std;

class TreeNode
{
	int *keys;
	TreeNode **child;
	int n;
	bool leaf;
	public:
		TreeNode(bool leaf);
		void traverse();
		int findKey(int k);
		void insertNonFull(int k);
		void splitChild(int i, TreeNode *y);
		void remove(int k);
		void removeFromLeaf(int idx);
		void removeFromNonLeaf(int idx);
		int getPred(int idx);
		int getSucc(int idx);
		void fill(int idx);
		void borrowFromNext(int idx);
		void borrowFromPrev(int idx);
		void merge(int idx);
		friend class Tree;
};

class Tree
{
	TreeNode *root = NULL;
	public:
		void traverse()
		{
			if(root != NULL)
				root->traverse();
		}
		void insert(int k);
		void remove(int k);
};

TreeNode::TreeNode(bool leaf1)
{
	leaf = leaf1;
	keys = new int[3];
	child = new TreeNode *[4];
	n = 0;
}

int TreeNode::findKey(int k)
{
	int indx = 0;
	while(indx<n && keys[indx]<k)
		++indx;
	return indx;
}

void Tree::insert(int k)
{
	if(root == NULL)
	{
		root = new TreeNode(true);
		root->keys[0] = k;
		root->n = 1;
	}
	else{
		if(root->n == 3)
		{
			TreeNode *s = new TreeNode(false);
			s->child[0] = root;
			s->splitChild(0, root);
			int i = 0;
			if(s->keys[0]<k)
				i++;
			s->child[i]->insertNonFull(k);
			root = s;
		}
		else
			root->insertNonFull(k);
	}
}

void TreeNode::insertNonFull(int k)
{
	int i = n-1;
	if(leaf == true)
	{
		while(i>=0 && keys[i] > k)
		{
			keys[i+1] = keys[i];
			i--;
		}
		keys[i+1] = k;
		n = n + 1;
	}
	else{
		while(i>=0 && keys[i]>k)
			i--;
		if(child[i+1]->n == 3)
		{
			splitChild(i+1, child[i+1]);
			if(keys[i+1]<k)
				i++;
		}
		child[i+1]->insertNonFull(k);
	}
}

void TreeNode::splitChild(int i, TreeNode *y)
{
	TreeNode *z = new TreeNode(y->leaf);
	z->n = 1;
	z->keys[0] = y->keys[2];
	if(y->leaf == false)
	{
		for(int j=0; j<2; j++)
			z->child[j] = y->child[j+2];
	}
	y->n = 1;
	for(int j=n; j>=i+1; j--)
		child[j+1] = child[j];
	child[i+1] = z;
	for (int j = n-1; j >= i; j--) 
        	keys[j+1] = keys[j]; 
  
    	keys[i] = y->keys[1]; 
 
    	n = n + 1; 
}

void TreeNode::traverse()
{
	cout<<endl;
	int i;
	for(i=0; i<n; i++)
	{
		if(leaf == false)
			child[i]->traverse();
		cout<<" "<<keys[i];
	}
	if(leaf == false)
		child[i]->traverse();

	cout<<endl;
}

void TreeNode::remove(int k)
{
	int indx = findKey(k);
	if(indx<n && keys[indx] == k)
	{
		if(leaf)
			removeFromLeaf(indx);
		else
			removeFromNonLeaf(indx);
	}
	else
	{
		if(leaf)
		{
			cout<<"The key doesn't exist"<<endl;
			return;
		}
		bool flag = ((indx==n)?true : false);
		if(child[indx]->n < 2)
			fill(indx);
		if(flag && indx>n)
			child[indx-1]->remove(k);
		else
			child[indx]->remove(k);
	}
	return;
}

void TreeNode::removeFromLeaf(int indx)
{
	for(int i=indx+1; i<n; ++i)
		keys[i-1] = keys[i];
	n--;
	return;
}

void TreeNode::removeFromNonLeaf(int indx)
{
	int k = keys[indx];
	if(child[indx]->n >=2)
	{
		int pred = getPred(indx);
		keys[indx] = pred;
		child[indx]->remove(pred);
	}
	else if(child[indx+1]->n >= 2)
	{
		int succ = getSucc(indx);
		keys[indx] = succ;
		child[indx+1]->remove(succ);
	}
	else{
		merge(indx);
		child[indx]->remove(k);
	}
	return;
}

int TreeNode::getPred(int indx)
{
	TreeNode *curr = child[indx];
	while(!curr->leaf)
		curr = curr->child[curr->n];
	return curr->keys[curr->n-1];
}

int TreeNode::getSucc(int indx) 
{ 
	TreeNode *curr = child[indx+1]; 
    	while (!curr->leaf) 
    		curr = curr->child[0]; 
    	return curr->keys[0]; 
} 
  
void TreeNode::fill(int indx) 
{ 
	if(indx!=0 && child[indx-1]->n>=2) 
        	borrowFromPrev(indx); 

    	else if (indx!=n && child[indx+1]->n>=2) 
        	borrowFromNext(indx); 
    	else
    	{ 
        	if (indx != n) 
            		merge(indx); 
        	else
            		merge(indx-1); 
    	} 
    	return; 
} 

void TreeNode::borrowFromPrev(int indx) 
{ 
    	TreeNode *c=child[indx]; 
    	TreeNode *sibling=child[indx-1]; 

    	for (int i=c->n-1; i>=0; --i) 
        	c->keys[i+1] = c->keys[i]; 
  
    	if (!c->leaf) 
    	{ 
        	for(int i=c->n; i>=0; --i) 
        	    c->child[i+1] = c->child[i]; 
    	} 
    	c->keys[0] = keys[indx-1]; 

    	if(!c->leaf) 
        	c->child[0] = sibling->child[sibling->n]; 

    	keys[indx-1] = sibling->keys[sibling->n-1]; 
  
    	c->n += 1; 
    	sibling->n -= 1; 
 	return; 
} 

void TreeNode::borrowFromNext(int indx) 
{ 
    	TreeNode *c=child[indx]; 
    	TreeNode *sibling=child[indx+1]; 
  
    	c->keys[(c->n)] = keys[indx]; 

    	if (!(c->leaf)) 
        	c->child[(c->n)+1] = sibling->child[0]; 
  
    	keys[indx] = sibling->keys[0]; 
 
    	for (int i=1; i<sibling->n; ++i) 
        	sibling->keys[i-1] = sibling->keys[i]; 

    	if (!sibling->leaf) 
    	{ 
        	for(int i=1; i<=sibling->n; ++i) 
            		sibling->child[i-1] = sibling->child[i]; 
    	} 

    	c->n += 1; 
    	sibling->n -= 1; 
    	return; 
} 

void TreeNode::merge(int indx) 
{ 
    	TreeNode *c = child[indx]; 
    	TreeNode *sibling = child[indx+1]; 

    	c->keys[1] = keys[indx]; 
 
    	for (int i=0; i<sibling->n; ++i) 
        	c->keys[i+2] = sibling->keys[i]; 
  
    	if (!c->leaf) 
    	{ 
        	for(int i=0; i<=sibling->n; ++i) 
            		c->child[i+2] = sibling->child[i]; 
    	} 
  
    	for (int i=indx+1; i<n; ++i) 
        	keys[i-1] = keys[i]; 
 
    	for (int i=indx+2; i<=n; ++i) 
        	child[i-1] = child[i]; 

    	c->n += sibling->n+1; 
    	n--; 

    	delete(sibling); 
    	return; 
} 

void Tree::remove(int k) 
{ 
    	if (!root) 
    	{ 
        	cout << "Empty tree\n"; 
        	return; 
    	} 
 
    	root->remove(k); 

    	if (root->n==0) 
    	{ 
        	TreeNode *tmp = root; 
        	if (root->leaf) 
            		root = NULL; 
        	else
            		root = root->child[0]; 
 
        	delete tmp; 
    	} 
    	return; 
} 
				
int main() 
{ 
    	Tree t; 
	int num,k;
	cout<<"2-3 Tree (insertion and deletion)";
	cout<<"Enter the no. of elements"<<endl;
	cin>>num;
	cout<<"Enter the keys"<<endl;
	for(int i=0; i<num; i++)
	{
		cin>>k;
		t.insert(k);
	}
	cout << "Traversal of tree constructed is\n"; 
    	t.traverse();
	cout<<"Enter the key to be deleted"<<endl;
	cin>>k;
	t.remove(k);
	cout<<"Traversal after deletion is"<<endl;
	t.traverse();
	return 0;
}
