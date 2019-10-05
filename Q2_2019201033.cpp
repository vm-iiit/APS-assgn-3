#include<iostream>
using namespace std;
typedef long long int ll;

struct trie_node
{
	bool bit;
	struct trie_node *left;
	struct trie_node *right;
	bool start;
};

typedef struct trie_node tnode;

tnode *newnode(bool b)
{
	tnode *node = new trie_node;
	node->bit = b;
	node->left = NULL;
	node->right = NULL;
	node->start = false;
	return node;
}

tnode *insert_in_trie(tnode *root, ll num, ll max_set_bit)
{
	if(root == NULL)
	{
		root = newnode(1);
		root->start = true;
		return root;
	}
	else if(num==0)
		return root;
	else
	{
		cout<<"max bit "<<max_set_bit<<endl;
		cout<<num<<endl;
		
			bool curr_bit = (num & (1<<max_set_bit))?1:0;
			cout<<"current bit "<<((curr_bit)?1:0)<<endl;
			if(curr_bit == 1)
			{
				root->right = newnode(true);
				root->right = insert_in_trie(root->right, (num & ~(1<<max_set_bit)), max_set_bit-1);
			}
			else
			{
				root->left = newnode(false);
				root->left = insert_in_trie(root->left, (num & ~(1<<max_set_bit)), max_set_bit-1);	
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

	ll max_set_bit=0;
	ll total_or=0;
	for(lv=0;lv<n;lv++)
	{
		total_or = (total_or | arr[lv]);
	}
	cout<<"cumulative or is "<<total_or<<endl;

	for(lv = 63; lv >=0; lv--)
		if(total_or & (1<<lv))
		{
			max_set_bit = max(lv, max_set_bit);
			break;
		}

	tnode *root = NULL;
	root = insert_in_trie(root, 0, 0);
	for(lv=0;lv<n;lv++)
		root = insert_in_trie(root, arr[lv], max_set_bit);

	ll quer, number;
	cout<<"num of queries :";

	cin>>quer;
	cout<<"highest set bit "<<max_set_bit<<endl;
	while(quer--)
	{
		cin>>number;
		tnode *ptr=root;
		ll ans = 0;
		ans = (ans | (number));
		ll stop_bit;
		for(lv=max_set_bit; lv>-1;lv--)
		{
			cout<<"iteration running for bit "<<lv<<endl;
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
					ptr = ptr->right;
					ans = (ans | (1<<lv));
				}
				else
				{
					stop_bit = lv;
					break;
				}
			}
		}
		for(lv=63;lv>max_set_bit; lv--)
			ans = (ans | ((1<<lv) & number));
		for(lv=stop_bit; lv>=0;lv--)
			ans = (ans | ((1<<lv) & number));

		cout<<ans<<endl;
	}
}