#include<iostream>
#include<fstream>
#include<vector>
#include<math.h>
#define maxfiles 5000                //.5 GB
int chunk = 1000;
#define left (2*lv)
#define right (2*lv+1)
using namespace std;
typedef int ll;

class heap
{
	private:
		ll n;
		pair<ll, ll> *array = NULL;
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
			cout<<"destructor called\n";
			//free(array);
			cout<<"destructed\n";
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
				//cout<<"(build heap) reallocating mem from "<<n<<" to "<<2*eles<<endl;
				array = (pair<ll,ll> *)realloc(array, 2*eles*sizeof(pair<ll,ll>));
				//cout<<"reallocated memory\n";
			}
			else
			{
				//cout<<"(build heap)  allocating mem from "<<n<<" to "<<2*eles<<endl;
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
				cout<<'('<<array[i].first<<" ,"<<array[i].second<<')'<<' ';
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
			/*if(n < ll(capacity/3) && n >10)
			{
				cout<<"n :"<<n<<" capacity :"<<capacity<<endl;
				cout<<"(pop) reallocating mem from "<<n<<" to "<<capacity/3<<endl;
				this->array = (pair<ll, ll> *)realloc(array, sizeof(pair<ll, ll>)*(capacity/3));
				capacity /= 3;
			}*/	
			return ret;
		}

		void push(pair<ll,ll> ele)
		{
			if(this->capacity <= this->n)
			{
				cout<<"(push) reallocating mem from "<<n<<" to "<<2*capacity<<endl;
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
	ll incounter = 0;
	ifstream inpf;
	ofstream opf;
	inpf.open(argv[1]);
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
		vector<ll> tvec;
		inpf.seekg(last_pos, ios::beg);
		
		while(inpf.tellg()-last_pos <= chunk /*&& inpf.tellg() <= ip_size*/ && inpf.tellg() != -1)
		{
			
			inpf>>ele;
			//cout<<"read element "<<ele<<endl;
			if(inpf.tellg() != -1)
			{
				tvec.push_back(ele);
			}
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
	//cout<<"last val :"<<curr_chunk<<endl;
	
	vector<pair<ll,ll>> tvec;
	ifstream in_descriptors[num_chunks];
	
	for(int lv=0; lv<curr_chunk;lv++)
	{
		in_descriptors[lv].open(filename+to_string(lv));
		in_descriptors[lv]>>ele;
		++incounter;
		tvec.push_back(make_pair(ele, lv));
	}
	//cout<<"incounter "<<incounter<<endl;
	heap hp;
	hp.build_heap(&tvec[0], &tvec[tvec.size()-1]);

	opf.open(argv[2]);
	

	cout<<"heap size :"<<hp.syze()<<endl;
	ll index;
	bool terminate = false;
	
	ll integer;
	pair<ll,ll> popped;
	while(hp.syze())
	{
		//cout<<"stuck here\n";
		if(terminate == true)
		{
			popped = hp.pop();
			opf<<popped.first<<endl;
			//cout<<"outcounter :"<<++outcounter<<endl;
		}
		else
		{
			popped = hp.pop();
			opf<<popped.first<<endl;
			//cout<<"outcounter :"<<++outcounter<<endl;
			index = popped.second;
			ll iters = 0;
			while(iters < curr_chunk)
			{
				//cout<<"stuck here 2\n";
				in_descriptors[(index+iters)%curr_chunk]>>integer;
				if(in_descriptors[(index+iters)%curr_chunk].tellg() == -1)
				{	
					//cout<<"terminate true\n";
					terminate = true;
					
				}
				else
				{
					//cout<<"terminate false\n";
					terminate = false;
					hp.push(make_pair(integer, (index+iters)%curr_chunk));
					//cout<<"incounter "<<++incounter<<endl;
					break;
				}
				iters += 1;
				//cout<<"iters :"<<iters<<endl;
			}
		}
		
	}

	/*cout<<"heap size at end :"<<hp.syze()<<endl;
	for(int lv=0;lv<curr_chunk;lv++)
		cout<<end[lv]<<' ';
	cout<<endl;*/
	
	cout<<"deleting temp files and closing i/o stream\n";
	
	string numb_file;
	
	for(long int lv=0;lv<curr_chunk;lv++)
	{
		/*cout<<"closing input file descriptor #"<<lv<<endl;
		in_descriptors[lv].close();
		cout<<"closing output file descriptor #"<<lv<<endl;
		out_descriptors[lv].close();
		cout<<"closed i/o file descriptors #"<<lv<<endl;*/
		numb_file = filename+to_string(lv);
		cout<<"deleting file "<<numb_file.c_str()<<endl;
		remove(numb_file.c_str());
		cout<<"deleted file "<<numb_file.c_str()<<endl;
	}
	cout<<"closing output file\n";
	opf.close();
	cout<<"closing input file\n";
	//inpf.close();
	cout<<"closed\n";
}

