#include<iostream>
#define left (2*lv)
#define right (2*lv+1)
using namespace std;
typedef int ll;

class heap
{
	private:
		ll n;
		ll *array;
		ll capacity;
	public:
		heap()
		{
			this->capacity = 5;
			this->n = 0;
			array = (ll *)malloc(sizeof(ll)*5);
		}
		~heap()
		{
			delete array;
		}

		void fix(ll ind)
		{
			//cout<<"fixing element "<<array[ind]<<endl<<endl;
			ll lv = ind;
			if(left > n)
				return;
			if(left <= n && right > n)
			{
				if(array[lv] > array[left])
				{
					ll temp = array[lv];
					array[lv] = array[left];
					array[left] = temp;
					fix(left);
				}
				else
					return;
			}
			else 
			{
				//cout<<"parent :"<<array[lv]<<endl;
				//cout<<"children :"<<array[left]<<' '<<array[right]<<endl;
				if(array[lv] <= array[left] && array[lv] <= array[right])
					return;
				else if(array[lv] > array[left] && array[lv] > array[right])
				{
					//cout<<"case 1\n";
					ll smaller = (array[left] < array[right])?left:right;
					//cout<<"swapping "<<array[lv]<<" with "<<array[smaller]<<endl;
					ll temp = array[smaller];
					array[smaller] = array[lv];
					array[lv] = temp;
					fix(smaller);
				}
				else if(array[right] >= array[lv] && array[lv] > array[left] )
				{
					//cout<<"case 2\n";
					//cout<<"swapping "<<array[lv]<<" with "<<array[left]<<endl;
					//ll smaller = (array[left] < array[right])?left:right;
					ll temp = array[left];
					array[left] = array[lv];
					array[lv] = temp;
					fix(left);
				}
				else if(array[left] >= array[lv] && array[lv]> array[right] )
				{
					//cout<<"case 3\n";
					//cout<<"swapping "<<array[lv]<<" with "<<array[right]<<endl;
					ll temp = array[right];
					array[right] = array[lv];
					array[lv] = temp;
					fix(right);
				}
				
			}
			return;
		}

		void build_heap(ll *beg, ll *end)
		{
			ll eles = end-beg+1;
			//cout<<"elemnts :"<<eles<<endl;
			if(n)
			{
				array = (ll *)realloc(array, 2*eles*sizeof(ll));
				//cout<<"reallocated memory\n";
			}
			else
			{
				array = (ll *)malloc(sizeof(2*eles*sizeof(ll)));
				//cout<<"allocated memory\n";
			}
			/*for(int i=1;i<=eles;i++)
				cout<<array[i]<<' ';
			cout<<"print alloc\n";*/

			capacity = 2*eles;
			n = eles;
			ll *ptr = beg;
			
			while(ptr-beg <= eles){
				array[ptr-beg+1] = *ptr;
				ptr = ptr+1;
			}

			
			//cout<<"printed inside "<<endl;

			for(ll lv = n; lv>0; lv--)
			{
				cout<<"building\n";
				fix(lv);
				this->print_heap();
			}
			//cout<<"build finished\n";
		}

		void print_heap()
		{
			if(n==0)
			{
				cout<<"heap empty\n";
				return;
			}
			cout<<"heap contents :";
			for(int i=1;i<=n;i++)
				cout<<array[i]<<' ';
			cout<<endl<<endl;
		}

		void heapify(ll lv)
		{
			fix(lv);
		}

		ll top()
		{
			return array[1];
		}

		ll pop()
		{
			ll ret = array[1];
			array[1] = array[n];
			n -= 1;
			if(n)
				heapify(1);
			if(n < capacity/3 && n >10)
				this->array = (ll *)realloc(array, sizeof(ll)*(capacity/3));	
			return ret;
		}

		void push(ll ele)
		{
			if(this->capacity <= this->n)
			{
				this->array = (ll *)realloc(array, sizeof(ll)*2*capacity);
				capacity *= 2;
			}
			n += 1;
			array[n] = ele;
			ll lv = n;
			while(lv > 1 && array[lv] < array[lv/2])
			{
				ll temp = array[lv];
				array[lv] = array[lv/2];
				array[lv/2] = temp;
				lv = lv/2;
			}
			return;
		}

};


int main()
{
	heap hp;
	ll array[] = {5, 45, 2, 9, 3, 10, 7, 4, 15, 3, 0, 4};
	cout<<"initialized\n";
	hp.build_heap(array, array+11);
	int count=8;
	while(count--)
	{
		hp.print_heap();
		//cout<<endl;
		cout<<"popped out :"<<hp.top()<<endl;
		hp.pop();
	}
	cout<<"pushing 4\n";
	hp.push(4);
	hp.print_heap();
	cout<<"pushing 3\n";
	hp.push(3);
	hp.print_heap();
	count=6;
	while(count--)
	{
		hp.print_heap();
		//cout<<endl;
		cout<<"popped out :"<<hp.top()<<endl;
		hp.pop();
	}
	hp.print_heap();
	cout<<"pushing 5\n";
	hp.push(5);
	hp.print_heap();
	cout<<"pushing 6\n";
	hp.push(6);
	hp.print_heap();
	cout<<"pushing 1\n";
	hp.push(1);
	hp.print_heap();
	cout<<"pushing 2\n";
	hp.push(2);
	hp.print_heap();
}

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/*class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        
        
    }
};*/