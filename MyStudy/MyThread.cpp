#include<mutex>
#include<iostream>
#include<thread>
#include<vector>
namespace MyThead {
	using namespace std;
	void anywork1(int*);
	
	void Main() {
		int result=0;
		vector<thread> workers;
		workers.push_back(thread(anywork1,&result));
		for (int i = 0; i < workers.size(); i++) {
			workers[i].join();
		}
		cout << result;
	}
	void anywork1(int* result) {
		for (int i = 0; i < 10000; i++) {
			(*result)++;
		}
	}
}