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
#include <typeinfo>
namespace MyThead {
	using namespace std;
	
	void Main() {
		//case1();
		//case2();
		//case3();
		//case4();
		//case5();
		//case6();
		//case7();
		case8();
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

	void counter(atomic<int>* count) {
		for (int i = 0; i < 10000; i++) {
			(*count)++;
		}
	}

	void case4() {
		vector<thread> threadlist;
		atomic<int> count = 0;
		for (int i = 0; i < 5; i++) {
			threadlist.push_back(thread(counter,&count));
		}
		for (int i = 0; i < threadlist.size(); i++) {
			threadlist[i].join();
		}
		cout << count<<endl;
		
	}

	void readwrite1(atomic<int> *a,atomic<int>* b) {
		//memory_order_relaxed : 단일 쓰레드 관점에서 결과가 동일하면 cpu명령 순서를 자유롭게 풀어준다.
		a->store(1, memory_order_relaxed);
		int result = b->load(memory_order_relaxed);
		printf("1. %d \n", result);
	}

	void readwrite2(atomic<int>* a, atomic<int>* b) {
		//memory_order_relaxed : 단일 쓰레드 관점에서 결과가 동일하면 cpu명령 순서를 자유롭게 풀어준다.
		b->store(1, memory_order_relaxed);
		int result = a->load(memory_order_relaxed);
		printf("2. %d \n", result);
	}
	
	void case5() {
		vector<thread> threadlist;
		atomic<int> a(0), b(0);

		threadlist.push_back(thread(readwrite1, &a, &b));
		threadlist.push_back(thread(readwrite2, &a, &b));

		//두 함수 모두 memory_order_relaxed로 풀어주었기에 1.과 2. 모두 0이 나올 수 도 있다.

		for (int i = 0; i < threadlist.size(); i++) {
			threadlist[i].join();
		}
		//memory_order_release : 메모리 저장 작업. 해당 명령 이전의 모든 메모리 명령들이 해당 명령 이후로 재배치 되는 것을 금지
		//memory_order_acquire : 메모리 로드 작업. 해당 명령 뒤에 오는 모든 메모리 명령들이 해당 명령 위로 재배치 되는 것을 금지
		//memory_order_acq_rel : acquire 와 release 를 모두 수행
		//memory_order_seq_cst : 순차적 일관성 보장. ARM cpu같은 경우 비싼 연산임.
		
	}
	template<size_t n>
	void producer(atomic<int> (&data)[n], atomic<bool>& ready) {
		data[0].store(1, memory_order_relaxed);
		data[1].store(1, memory_order_relaxed);
		data[2].store(1, memory_order_relaxed);
		ready.store(true, memory_order_release);
	}
	template<size_t n>
	void consumer(atomic<int> (&data)[n], atomic<bool>& ready) {
		while (!ready.load(memory_order_acquire)) {

		}
		cout << data[0] << endl;
		cout << data[1] << endl;
		cout << data[2] << endl;

	}

	void case6() {
		vector<thread> threadlist;
		vector <atomic<int>> data2;
		atomic<int> data[3];
		atomic<bool> ready;
		//static cast는 배열의 사이즈를 지정하는 방법밖에 못찾음.
		//threadlist.push_back(thread(static_cast<void(*)(atomic<int>(&)[3], atomic<bool>&)>(producer), ref(data),ref(ready)));

		//data를 참조로 캡쳐하여 가져옴.
		threadlist.push_back(thread([&data, &ready] {producer(data, ready); }));
		threadlist.push_back(thread([&data, &ready] {consumer(data, ready); }));

		threadlist[0].join();
		threadlist[1].join();


	}

	void write_a1(atomic<bool>* a) {
		a->store(true, memory_order_release);
	}
	void write_b1(atomic<bool>* b) {
		b->store(true, memory_order_release);
	}
	void read_b_than_a1(atomic<bool>* a, atomic<bool>* b, atomic<int>* c) {
		while (!b->load(memory_order_acquire)) {

		}
		if (a->load(memory_order_acquire)) {
			++(*c);
		}
	}
	void read_a_than_b1(atomic<bool>* a,atomic<bool>* b,atomic<int>* c) {
		while (!a->load(memory_order_acquire)) {

		}
		if (b->load(memory_order_acquire)) {
			++(*c);
		}
	}

	void case7() {
		
		thread t1, t2, t3, t4;
		atomic<bool> a, b;
		atomic<int> c(0);
		t1 = thread(write_a1, &a);
		t2 = thread(write_b1, &b);
		t3 = thread(read_a_than_b1, &a, &b, &c);
		t4 = thread(read_b_than_a1, &a, &b, &c);
		t1.join();
		t2.join();
		t3.join();
		t4.join();
		int result = c.load(memory_order_acquire);
		cout << result <<endl;
		
		// memory_order_seq_cst이외에 memory order는 상태가 어떻게 바뀔지는 동의하나, 
		// 각 쓰레드 사이에서 누가 먼저 상태를 변화할지는 동의하지 않음.
		// cpu 1 에서 write_a -> read_b_than_a 가능
		// cpu 2 에서 write_b -> read_a_than_b 가능
		// 그러므로 c가 0이 될 수 도 있음.
		// 이를 방지하기 위해 memory_order_seq_cst 필요
		// memory_order_seq_cst : 해당 명령을 사용하는 메모리 연산들 사이에는 모든 쓰레드에서 동일한 순서로 보일 것을 보장

	}
	void write_a2(atomic<bool>* a) {
		a->store(true, memory_order_seq_cst);
	}
	void write_b2(atomic<bool>* b) {
		b->store(true, memory_order_seq_cst);
	}
	void read_b_than_a2(atomic<bool>* a, atomic<bool>* b, atomic<int>* c) {
		while (!b->load(memory_order_seq_cst)) {

		}
		if (a->load(memory_order_seq_cst)) {
			++(*c);
		}
	}
	void read_a_than_b2(atomic<bool>* a, atomic<bool>* b, atomic<int>* c) {
		while (!a->load(memory_order_seq_cst)) {

		}
		if (b->load(memory_order_seq_cst)) {
			++(*c);
		}
	}

	void case8() {

		thread t1, t2, t3, t4;
		atomic<bool> a, b;
		atomic<int> c(0);
		t1 = thread(write_a2, &a);
		t2 = thread(write_b2, &b);
		t3 = thread(read_a_than_b2, &a, &b, &c);
		t4 = thread(read_b_than_a2, &a, &b, &c);
		t1.join();
		t2.join();
		t3.join();
		t4.join();
		int result = c.load(memory_order_acquire);
		cout << result << endl;

		// memory_order_seq_cst : 해당 명령을 사용하는 메모리 연산들 사이에는 모든 쓰레드에서 동일한 순서로 보일 것을 보장

	}
}