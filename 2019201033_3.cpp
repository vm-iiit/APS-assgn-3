#include<iostream>
#include<fstream>
#include<vector>
#include<math.h>
#define maxfiles 5000                //.5 GB
int chunk = 1000000;
#define left (2*lv)
#define right (2*lv+1)
using namespace std;
typedef long long int ll;

class heap
{
	private:
		ll n;
		pair<ll, ll> *array;
		ll capacity;
	public:
		heap()
		{
			this->capacity = 5;
			this->n = 0;
			array = (pair<ll, ll> *)malloc(sizeof(pair<ll, ll>)*5);
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
				if(array[lv].first > array[left].first)
				{
					auto temp = array[lv];
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
				if(array[lv].first <= array[left].first && array[lv].first <= array[right].first)
					return;
				else if(array[lv].first > array[left].first && array[lv].first > array[right].first)
				{
					//cout<<"case 1\n";
					ll smaller = (array[left].first < array[right].first)?left:right;
					//cout<<"swapping "<<array[lv]<<" with "<<array[smaller]<<endl;
					auto temp = array[smaller];
					array[smaller] = array[lv];
					array[lv] = temp;
					fix(smaller);
				}
				else if(array[right].first >= array[lv].first && array[lv].first > array[left].first )
				{
					//cout<<"case 2\n";
					//cout<<"swapping "<<array[lv]<<" with "<<array[left]<<endl;
					//ll smaller = (array[left] < array[right])?left:right;
					auto temp = array[left];
					array[left] = array[lv];
					array[lv] = temp;
					fix(left);
				}
				else if(array[left].first >= array[lv].first && array[lv].first> array[right].first )
				{
					//cout<<"case 3\n";
					//cout<<"swapping "<<array[lv]<<" with "<<array[right]<<endl;
					auto temp = array[right];
					array[right] = array[lv];
					array[lv] = temp;
					fix(right);
				}
				
			}
			return;
		}

		void build_heap(pair<ll,ll> *beg, pair<ll,ll> *end)
		{
			ll eles = end-beg+1;
			//cout<<"elemnts :"<<eles<<endl;
			if(n)
			{
				array = (pair<ll,ll> *)realloc(array, 2*eles*sizeof(pair<ll,ll>));
				//cout<<"reallocated memory\n";
			}
			else
			{
				array = (pair<ll,ll> *)malloc(sizeof(2*eles*sizeof(pair<ll,ll>)));
				//cout<<"allocated memory\n";
			}
			/*for(int i=1;i<=eles;i++)
				cout<<array[i]<<' ';
			cout<<"print alloc\n";*/

			capacity = 2*eles;
			n = eles;
			pair<ll,ll> *ptr = beg;
			
			while(ptr-beg <= eles){
				array[ptr-beg+1] = *ptr;
				ptr = ptr+1;
			}

			
			//cout<<"printed inside "<<endl;

			for(ll lv = n; lv>0; lv--)
			{
				//cout<<"building\n";
				fix(lv);
				//this->print_heap();
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
				cout<<array[i].first<<' ';
			cout<<endl<<endl;
		}

		void heapify(ll lv)
		{
			fix(lv);
		}

		pair<ll,ll> top()
		{
			return array[1];
		}

		pair<ll,ll> pop()
		{
			auto ret = array[1];
			array[1] = array[n];
			n -= 1;
			if(n)
				heapify(1);
			if(n < capacity/3 && n >10)
				this->array = (pair<ll, ll> *)realloc(array, sizeof(pair<ll, ll>)*(capacity/3));	
			return ret;
		}

		void push(pair<ll,ll> ele)
		{
			if(this->capacity <= this->n)
			{
				this->array = (pair<ll, ll> *)realloc(array, sizeof(pair<ll, ll>)*2*capacity);
				capacity *= 2;
			}
			n += 1;
			array[n] = ele;
			ll lv = n;
			while(lv > 1 && array[lv] < array[lv/2])
			{
				auto temp = array[lv];
				array[lv] = array[lv/2];
				array[lv/2] = temp;
				lv = lv/2;
			}
			return;
		}

		ll syze()
		{
			return this->n;
		}

};

void merge_sort(ll *beg, ll *end)
{
	if(beg == end)
		return;
	ll difference = end-beg;
	merge_sort(beg, beg+difference/2);
	merge_sort(beg+difference/2 + 1, end);
	ll *temp = (ll *)malloc(sizeof(ll)*(difference+1));
	ll *first = beg;
	ll *second = beg+difference/2 + 1;
	ll counter=0;
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
	for(ll lv=0;lv<counter;lv++)
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


int main(int argc, char *argv[])
{
	ifstream inpf;
	ofstream opf;
	inpf.open(argv[1], ios::binary);
	inpf.seekg(0, ios::end);
	ssize_t ip_size = inpf.tellg();
	//inpf.seekg(0, ios::beg);
	cout<<"size of input file :"<<ip_size<<endl<<" bytes\n";
	int num_chunks;
	num_chunks = ceil(float(float(ip_size)/float(chunk)));
	do{
		chunk *= 2;
		num_chunks = ceil(float(float(ip_size)/float(chunk)));	
	}while(num_chunks >=maxfiles);
	
	cout<<"number of chunks :"<<num_chunks<<endl;
	cout<<"chunk size :"<<chunk<<endl;
	ofstream out_descriptors[num_chunks];
	cout<<"descriptors created\n";
	string filename = "temp_file";

	int curr_chunk = 0;
	ssize_t last_pos = 0;
	ll ele;
	
	while(inpf.tellg() != -1)
	{
		inpf.seekg(last_pos, ios::beg);
		//int dummy=15;
		vector<ll> tvec;
		while(inpf.tellg()-last_pos <= chunk /*&& inpf.tellg() <= ip_size*/ && inpf.tellg() != -1)
		{

			inpf>>ele;
			//cout<<"read element "<<ele<<endl;
			if(inpf.tellg() != -1)
				tvec.push_back(ele);
			//cout<<"read posn :"<<inpf.tellg()<<endl;

		}
		last_pos = inpf.tellg();
		

		merge_sort(&tvec[0], &tvec[tvec.size()-1]);
		out_descriptors[curr_chunk].open(filename+to_string(curr_chunk));
		for(ll lv=0; lv<tvec.size(); lv++)
		{
			//cout<<"write loop\n";
			out_descriptors[curr_chunk]<<tvec[lv]<<endl;
		}
		cout<<"created chunk #"<<curr_chunk<<endl;
		++curr_chunk;
	}
	cout<<"last val :"<<curr_chunk<<endl;
	vector<pair<ll,ll>> tvec;
	ifstream in_descriptors[num_chunks];
	for(int lv=0; lv<curr_chunk;lv++)
	{
		in_descriptors[lv].open(filename+to_string(lv));
		in_descriptors[lv]>>ele;
		tvec.push_back(make_pair(ele, lv));
	}
	heap hp;
	hp.build_heap(&tvec[0], &tvec[tvec.size()-1]);
	//hp.print_heap();

	opf.open(argv[2], ios::binary);
	bool end[curr_chunk] = {false};

	cout<<hp.syze()<<endl;
	ll index;
	bool terminate = false;
	while(hp.syze() && !terminate)
	{
		pair<ll,ll> element = hp.top();
		opf<<element.first<<endl;
		index = element.second;
		hp.pop();
		cout<<"popped out\n";
		in_descriptors[index]>>ele;
		if(in_descriptors[index].tellg() == -1)
		{
			end[index] = true;
			terminate = true;
			for(int lv = (index+1)%curr_chunk; lv != index; lv = (lv+1)%curr_chunk)
				if(end[lv]==false)
				{
					terminate=false;
					in_descriptors[lv]>>ele;
					hp.push(make_pair(ele, lv));
					cout<<"pushed in\n";
					break;
				}
		}
		else
		{
			hp.push(make_pair(ele, index));
			cout<<"pushed in\n";
		}
	}

	opf.close();
	inpf.close();
	for(int lv=0;lv<curr_chunk;lv++)
	{
		in_descriptors[lv].close();
		out_descriptors[lv].close();
		remove((filename+to_string(lv)).c_str());
	}

}

