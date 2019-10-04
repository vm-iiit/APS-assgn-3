#include<iostream>
using namespace std;
typedef unsigned long long int ll;

struct trie_node
{
	bool bit;
	struct trie_node *left;
	struct trie_node *right;
	bool start;
}

typedef struct trie_node tnode;

tnode *newnode(bool b)
{
	tnode node = new trie_node;
	node->bit = b;
	node->l = NULL;
	node->r = NULL;
	node->start = false;
}

tnode *insert_in_trie(tnode *root, ll num, ll_max_set_bit)
{
	if(root == NULL)
	{
		root = newnode(1);
		root->start = true;
		return root;
	}
	else
	{
		for(int lv = max_set_bit; lv>-1; lv--)
		{
			bool curr_bit = (num & (1<<lv))?1:0;
			if(curr_bit == 1)
			{
				root->right = newnode(true);
				root->right = insert_in_trie(root->right, (num & ~(1<<lv)), max_set_bit-1);
			}
			else
			{
				root->left = newnode(false);
				root->left = insert_in_trie(root->left, (num & ~(1<<lv)), max_set_bit-1);	
			}
		}
	}
}

int main()
{
	ll n, lv;
	cin>>n;
	ll arr[n];
	for(lv=0;lv<n;lv++)
		cin>>arr[lv];

	ll max_set_bit;
	ll total_or=0;
	for(lv=0;lv<n;lv++)
	{
		total_or = (total_or | arr[lv]);
	}

	for(lv = 0; lv < 64; lv++)
		if(total_or & (1<<lv))
			max_set_bit = lv;

	tnode *root = NULL;
	root = insert_in_trie(root, 0, 0);
	for(lv=0;lv<n;lv++)
		root = insert_in_trie(root, arr[lv], max_set_bit);

	ll quer, number;
	cin>>quer;
	while(quer--)
	{
		cin>>number;
		tnode *ptr=root;
		ll ans = 0;
		ans = (ans | (number));
		ll stop_bit;
		for(lv=max_set_bit; lv>-1;lv--)
		{
			bool curr_bit = (number & (1<<lv))?1:0;
			if(curr_bit)
			{
				if(ptr->left)
				{
					ptr = ptr->left;
					ans = (ans | (1<<lv));
				}
				else
				{
					stop_bit = lv;
					break;
				}
			}
			else
			{
				if(ptr->right)
				{
					ptr = ptr->rightt;
					ans = (ans | (1<<lv));
				}
				else
				{
					stop_bit = lv;
					break;
				}
			}
		}
		while(lv=63; lv>max_set_bit; lv--)
			ans = (ans | ((1<<lv) & number));
		while(lv=stop_bit; lv>=0;lv--)
			ans = (ans | ((1<<lv) & number));
	}
}