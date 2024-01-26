#include<mutex>
#include<iostream>
#include<thread>
#include<vector>
#include"MyThread.h"
#include<atomic>
#include <queue>
#include<string>
#include <chrono>
#include <condition_variable>
#include <functional>
namespace MyThead {
	using namespace std;
	
	void Main() {
		//case1();
		//case2();
		case3();
	}
	void anywork1(int& result,mutex& m) {
		bool lockflag=false;
		for (int i = 0; i < 10000; i++) {
			m.lock();
			result++;
			m.unlock();
			
		}
	}
	void anywork2(int& result, mutex& m) {
		bool lockflag = false;
		for (int i = 0; i < 10000; i++) {
			//lock guard는 객체 소멸 시 자동으로 unlock함.
			lock_guard<mutex> guad(m);
			result++;
		}
	}
	void case1() {
		int result = 0;
		vector<thread> workers;
		mutex m;
		workers.push_back(thread(anywork1, std::ref(result),std::ref(m)));
		workers.push_back(thread(anywork2, std::ref(result), std::ref(m)));
		for (int i = 0; i < workers.size(); i++) {
			workers[i].join();
		}
		cout << result;
	}
	void producer(queue<string>* datas, mutex* m,int index) {
		for (int i = 0; i < 5; i++) {
			//some processing time
			this_thread::sleep_for(chrono::milliseconds(100*index));
			string content = "cotent " + to_string(i)+" working thread : "+to_string(index);
			m->lock();
			datas->push(content);
			m->unlock();
		}
		
	}
	
	void consumer(queue<string>* datas, mutex* m,int* work,int index) {
		while (*work > 0) {
			m->lock();
			if (datas->empty()) {
				m->unlock();
				//some waiting time
				this_thread::sleep_for(chrono::milliseconds(10));
				continue;
			}
			string content = datas->front();
			datas->pop();
			(*work)--;
			m->unlock();
			//some processing time
			this_thread::sleep_for(chrono::milliseconds(80));
			printf("work : %s  working thread : %d \n",content.c_str(), index);
		}
	}
	
	
	void case2() {
		queue<string> datas;
		mutex m;
		vector<thread> producerlist;
		int work=25;
		for (int i = 0; i < 5; i++) {
			//thread함수는 오버로딩된 함수 중 어떤 함수를 가져와야 할지 모르므로 명시적으로 표시해줘야 한다.
			//이를 위한 방법으로 static_cast와 람다 함수를 사용하는 방법이 있다.
			//아레는 static_cast를 사용하는 방법이다.
			producerlist.push_back(thread(static_cast<void (*)(queue<string>*,mutex*,int)>(producer), &datas, &m, i));
		}
		
		vector<thread> consumerlist;
		for (int i = 0; i < 5; i++) {
			consumerlist.push_back(thread(static_cast<void (*)(queue<string>*,mutex*,int*,int)>(consumer), &datas,&m, &work,i));
		}

		for (int i = 0; i < 5; i++) {
			producerlist[i].join();
		}
		for (int i = 0; i < 5; i++) {
			consumerlist[i].join();
		}
	}
	void producer(queue<string>* datas, mutex* m, int index, condition_variable* cv) {
		for (int i = 0; i < 5; i++) {
			//some processing time
			this_thread::sleep_for(chrono::milliseconds(100 * index));
			string content = "cotent " + to_string(i) + " working thread : " + to_string(index);
			m->lock();
			datas->push(content);
			m->unlock();
			cv->notify_one();
		}
	}
	void consumer(queue<string>* datas, mutex* m, int* work, int index,condition_variable* cv) {
		while (*work > 0) {
			unique_lock<mutex> ul(*m);
			cv->wait(ul, [&work, &datas] {return *work == 0 || !datas->empty(); });
			if (*work <= 0) {
				ul.unlock();
				return;
			}
			string content = datas->front();
			datas->pop();
			(*work)--;
			ul.unlock();
			//some processing time
			this_thread::sleep_for(chrono::milliseconds(80));
			printf("work : %s  working thread : %d \n", content.c_str(), index);
		}
	}

	void case3() {
		queue<string> datas;
		mutex m;
		condition_variable cv;
		vector<thread> producerlist;
		int work = 25;
		for (int i = 0; i < 5; i++) {
			//thread함수는 오버로딩된 함수 중 어떤 함수를 가져와야 할지 모르므로 명시적으로 표시해줘야 한다.
			//이를 위한 방법으로 static_cast와 람다 함수를 사용하는 방법이 있다.
			//아레는 람다 함수를 사용하는 방법이다.
			producerlist.push_back(thread([](queue<string>* datas, mutex* m, int i, condition_variable* cv)->void{ producer(datas, m, i, cv); }, &datas, &m, i, &cv));
		}
		vector<thread> consumerlist;
		for (int i = 0; i < 5; i++) {
			consumerlist.push_back(thread([](queue<string>* datas, mutex* m, int* work, int index, condition_variable* cv)->void { consumer(datas,m,work,index,cv); }, &datas, &m, &work, i,&cv));
		}
		
		for (int i = 0; i < 5; i++) {
			producerlist[i].join();
		}
		//모든 일을 끝냈으나 일부 쓰레드가 일을 기다리며 sleep상태일 때 모든 쓰레드를 깨워 쓰레드를 종료할 수 있도록 한다.
		cv.notify_all();
		for (int i = 0; i < 5; i++) {
			consumerlist[i].join();
		}
	}
}