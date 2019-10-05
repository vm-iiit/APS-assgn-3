#include<iostream>
#include<climits>
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
    ll one =1;
    //cout<<"inserting "<<num<<" with bit "<<max_set_bit<<endl;
    if(root == NULL)
    {
        root = newnode(1);
        root->start = true;
        return root;
    }
    else if(max_set_bit <0)
        return root;
    else
    {
        //cout<<"max bit "<<max_set_bit<<endl;
        //cout<<num<<endl;
        
            bool curr_bit = (num & (one<<max_set_bit))?1:0;
            //cout<<"current bit "<<((curr_bit)?1:0)<<endl;
            if(curr_bit == 1)
            {
                if(root->right == NULL)
                    root->right = newnode(true);
                root->right = insert_in_trie(root->right, num, max_set_bit-1);
            }
            else
            {
                if(root->left == NULL)
                    root->left = newnode(false);
                root->left = insert_in_trie(root->left, num, max_set_bit-1);    
            }
        return root;
    }
}

void inorder(tnode *root)
{
    if(root == NULL)
        return;
    inorder(root->left);
    if(root->start==false)
        cout<<root->bit<<endl;
    else
        cout<<'s'<<endl;
    inorder(root->right);
}

int main()
{
    ll n, lv;
    ll largest = LLONG_MAX;
    int upper_b=-1;
    while(largest)
    {
        ++upper_b;
        largest = (largest>>1);
    }
    //cout<<"maximum possible set bit index :"<<upper_b<<endl;
    cin>>n;
    ll arr[n];
    for(lv=0;lv<n;lv++)
        cin>>arr[lv];

    ll max_set_bit=1;
    ll total_or=0;
    for(lv=0;lv<n;lv++)
    {
        total_or = (total_or | arr[lv]);
    }
    //cout<<"cumulative or is "<<total_or<<endl;
    ll one = 1;
    for(lv = upper_b; lv >=0; lv--)
    {
        ll temp = (one<<lv);
        //cout<<"temporary "<<temp<<endl;
        //cout<<"loop variable "<<lv<<endl;
        if(total_or & temp)
        {
            //cout<<"finding "<<lv<<endl;
            max_set_bit = lv;
            break;
        }
    }
    //cout<<"maximum set bit is "<<max_set_bit<<endl;
    tnode *root = NULL;
    root = insert_in_trie(root, 0, 0);

    for(lv=0;lv<n;lv++)
        root = insert_in_trie(root, arr[lv], max_set_bit);

    ll quer, number;
    //cout<<"num of queries :";
    /*cout<<"inorder begins\n";
    inorder(root);
    cout<<"inorder ends\n";*/
    cin>>quer;
    //cout<<"highest set bit "<<max_set_bit<<endl;
    while(quer--)
    {
        cin>>number;
        tnode *ptr=root;
        ll ans = 0;
        //ans = (ans | (number));
        ll stop_bit;
        for(lv=max_set_bit; lv>-1;lv--)
        {
            //cout<<"current answer = "<<ans<<endl;
            //cout<<"iteration running for bit "<<lv<<endl;
            bool curr_bit = (number & (1<<lv))?1:0;
            if(curr_bit)
            {
                if(ptr->left)
                {
                    ptr = ptr->left;
                    ans = (ans | (1<<lv));
                    //cout<<"updated answer = "<<ans<<endl;
                }
                else
                {
                    if(ptr->right)
                        ptr = ptr->right;
                }
            }
            else
            {
                if(ptr->right)
                {
                    ptr = ptr->right;
                    ans = (ans | (1<<lv));
                    //cout<<"updated answer = "<<ans<<endl;
                }
                else
                {
                    if(ptr->left)
                        ptr = ptr->left;
                }
            }
        }
        ll one = 1;
        for(lv=upper_b;lv>max_set_bit; lv--)
        {
            ans = (ans | ((one<<lv) & number));
            //cout<<"updated answer (leftover) = "<<ans<<endl;
        }
        /*for(lv=stop_bit; lv>=0;lv--)
            ans = (ans | ((1<<lv) & number));*/

        cout<<ans<<endl;
    }
}