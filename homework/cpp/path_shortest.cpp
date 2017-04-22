#include<iostream>
#define maxValue 21474836
using namespace std;

class path{
	private:
		int length;
		int** pic_table;//save the connection of this point
		int*  in_map;//save the point already in map
		int*  in_point;//save the point which point to this point
		int*  min_path;//save the shorest path between the first point to this point
	public:
		void input();
		void search();
		~path();
};
void path::input(){
	cin>>length;

	int i;
	int j;

	pic_table = new int*[length];
	in_map = new int[length]();
	in_point = new int[length]();
	min_path = new int[length]();

	for(i=0;i<length;i++){
		pic_table[i] = new int[length];
		min_path[i] = maxValue;
	}

	for(i=0;i<length;i++){
		for(j=0;j<length;j++){
			cin>>pic_table[i][j];
			if(!pic_table[i][j]){
				pic_table[i][j] = maxValue;
			}
		}
	}
}
void path::search(){
	in_map[0] = 1;//push the first point to map
	min_path[0] = 0;
	in_point[0] = -1;

	int i;
	int j;

	int x;
	int y;

	int min;

	while(!in_map[length-1]){
		x = 0;
		y = 0;
		min = maxValue;

		for(i=0;i<length;i++){
			for(j=0;j<length;j++){
				if(in_map[i]&&!in_map[j]&&min_path[i]+pic_table[i][j]<min){
					x = i;
					y = j;
					min = min_path[i]+pic_table[i][j];
					//cout<<"now input "<<i<<" to "<<j<<" the path is "<<min<<endl;
				}
			}
		}

		in_map[y] = 1;
		in_point[y] = x;
		min_path[y] = min;
	}
	
	cout<<min_path[length-1]<<endl;
}
path::~path(){

	while(length){
		delete [] pic_table[length-1];
		length--;
	}
	delete [] pic_table;
	delete [] in_map;
	delete [] in_point;
	delete [] min_path;
}
int main(){

	path pa;
	pa.input();
	pa.search();

	return 0;
}
