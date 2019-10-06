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

void merge_sort(ll *beg, ll *end)
{
	if(beg == end)
		return;
	int difference = end-beg;
	merge_sort(beg, beg+difference/2);
	merge_sort(beg+difference/2 + 1, end);
	ll *temp = (ll *)malloc(sizeof(ll)*(difference+1));
	ll *first = beg;
	ll *second = beg+difference/2 + 1;
	int counter=0;
	while(first != beg+difference/2 + 1 && second != end+1)
	{
		//cout<<"first sec "<<*first<<' '<<*second<<endl;
		if(*first < *second)
		{
			//cout<<"inserting first's "<<*first<<endl;
			temp[counter] = *first;
			++first;
		}
		else
		{
			//cout<<"inserting second's "<<*second<<endl;
			temp[counter] = *second;
			++second;	
		}
		++counter;
	}
	//cout<<"intermediate count :"<<counter<<endl;
	if(counter < difference+1)
	{
		if(second == end+1)
			while(counter < difference+1)
			{
				//cout<<"inserting first's "<<*first<<endl;
				temp[counter] = *first;
				++counter;
				++first;
			}
		else
			while(counter < difference+1)
			{
				//cout<<"inserting second's "<<*second<<endl;
				temp[counter] = *second;
				++counter;
				++second;
			}
	}
	ll *ptr;
	ptr = beg;
	/*cout<<"counter :"<<counter<<endl;
	cout<<"temp conts :";
	for(int lv=0;lv<counter;lv++)
		cout<<temp[lv]<<' ';
	cout<<endl;*/
	for(int lv=0;lv<counter;lv++)
	{
		*(beg+lv) = temp[lv];
		//++ptr;
		//++lv;
	}
	delete temp;
	/*cout<<"returning :";
	for(ptr = beg; ptr <=end;ptr++)
		cout<<*ptr<<' ';
	cout<<endl;*/
	//return beg;
}


int main()
{
	
	ll array[] = {5, 0, 45, 2, 9, 3, 10, -96, -885,  7, 4, 15, 3, 0, 4};
	//cout<<"size "<<sizeof(array)<<endl;
	//cout<<"last "<<array[sizeof(array)/sizeof(array[0])-1]<<endl;
	//ll *end=array;
	//cout<<array<<' '<<end<<endl;
	//int lv=11;
	//while(lv--)
	//	++end;
	//cout<<array<<' '<<end<<endl;
	//end = &array + sizeof(array)/sizeof(array[0])-1;
	//end = end+11;
	merge_sort(array, &array[sizeof(array)/sizeof(array[0])-1]);
	for(int lv=0;lv<15;lv++)
		cout<<array[lv]<<' ';
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