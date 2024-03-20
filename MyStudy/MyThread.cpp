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
#include <future>
#include <memory>
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
		//case8();
		//case9();
		//case10();
		//case11();
		//case12();
		//case13();
		//case14();
		//case15();
		case16();
	}
	void anywork1(int& result, mutex& m) {
		bool lockflag = false;
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
		workers.push_back(thread(anywork1, std::ref(result), std::ref(m)));
		workers.push_back(thread(anywork2, std::ref(result), std::ref(m)));
		for (int i = 0; i < workers.size(); i++) {
			workers[i].join();
		}
		cout << result;
	}
	void producer(queue<string>* datas, mutex* m, int index) {
		for (int i = 0; i < 5; i++) {
			//some processing time
			this_thread::sleep_for(chrono::milliseconds(100 * index));
			string content = "cotent " + to_string(i) + " working thread : " + to_string(index);
			m->lock();
			datas->push(content);
			m->unlock();
		}

	}

	void consumer(queue<string>* datas, mutex* m, int* work, int index) {
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
			printf("work : %s  working thread : %d \n", content.c_str(), index);
		}
	}


	void case2() {
		queue<string> datas;
		mutex m;
		vector<thread> producerlist;
		int work = 25;
		for (int i = 0; i < 5; i++) {
			//thread함수는 오버로딩된 함수 중 어떤 함수를 가져와야 할지 모르므로 명시적으로 표시해줘야 한다.
			//이를 위한 방법으로 static_cast와 람다 함수를 사용하는 방법이 있다.
			//아레는 static_cast를 사용하는 방법이다.
			producerlist.push_back(thread(static_cast<void (*)(queue<string>*, mutex*, int)>(producer), &datas, &m, i));
		}

		vector<thread> consumerlist;
		for (int i = 0; i < 5; i++) {
			consumerlist.push_back(thread(static_cast<void (*)(queue<string>*, mutex*, int*, int)>(consumer), &datas, &m, &work, i));
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
	void consumer(queue<string>* datas, mutex* m, int* work, int index, condition_variable* cv) {
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
			producerlist.push_back(thread([](queue<string>* datas, mutex* m, int i, condition_variable* cv)->void { producer(datas, m, i, cv); }, &datas, &m, i, &cv));
		}
		vector<thread> consumerlist;
		for (int i = 0; i < 5; i++) {
			consumerlist.push_back(thread([](queue<string>* datas, mutex* m, int* work, int index, condition_variable* cv)->void { consumer(datas, m, work, index, cv); }, &datas, &m, &work, i, &cv));
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
			threadlist.push_back(thread(counter, &count));
		}
		for (int i = 0; i < threadlist.size(); i++) {
			threadlist[i].join();
		}
		cout << count << endl;

	}

	void readwrite1(atomic<int>* a, atomic<int>* b) {
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
	void producer(atomic<int>(&data)[n], atomic<bool>& ready) {
		data[0].store(1, memory_order_relaxed);
		data[1].store(1, memory_order_relaxed);
		data[2].store(1, memory_order_relaxed);
		ready.store(true, memory_order_release);
	}
	template<size_t n>
	void consumer(atomic<int>(&data)[n], atomic<bool>& ready) {
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
	void read_a_than_b1(atomic<bool>* a, atomic<bool>* b, atomic<int>* c) {
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
		cout << result << endl;

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
	atomic<int> x(0), y(0), r1, r2, r3;
	void Thread1() {
		x.store(1, std::memory_order_seq_cst); // A
		y.store(1, std::memory_order_release); // B
	}
	void Thread2() {
		r1 = y.fetch_add(1, std::memory_order_seq_cst); // C
		r2 = y.load(std::memory_order_relaxed); // D
	}

	void Thread3() {
		y.store(3, std::memory_order_seq_cst); // E
		r3 = x.load(std::memory_order_seq_cst); // F
	}
	void case9() {
		thread t1, t2, t3;
		t1 = thread(Thread1);
		t2 = thread(Thread2);
		t3 = thread(Thread3);
		t1.join();
		t2.join();
		t3.join();
		cout << r1 << r2 << r3 << endl;
	}
	void anywork3(promise<int>* i) {
		i->set_value(1);
	}
	void case10() {
		promise<int> pro;
		future<int> data = pro.get_future();
		//promise는 복상 생성이 불가하다.
		//아레는 promise에 주소를 넘겨주는 방식.
		thread t1(anywork3, &pro);

		data.wait();

		//wait가 리턴됬다면 결과값이 준비되었다는 의미다.
		//wait 없이 get을 하더라도 wait한 후 결과를 돌려준다.
		//get은 데이터를 이동시킨다. 그러므로 get을 두 번 호출하면 안된다.
		cout << data.get() << endl;
		t1.join();
	}
	void anywork4(promise<int>* pro) {
		try {
			throw runtime_error("some error");
		}
		catch (...) {
			pro->set_exception(current_exception());
		}
	}

	void case11() {
		promise<int> pro;
		future<int> result = pro.get_future();
		thread t1(anywork4, &pro);
		result.wait();
		try {
			cout << result.get() << endl;
		}
		catch (const exception& e) {
			cout << "exception : " << e.what() << endl;
		}

		t1.join();
	}
	void anywork5(promise<void>* p) {
		this_thread::sleep_for(chrono::seconds(5));
		p->set_value();
	}
	void case12() {
		//void의 경우 어떤한 객체도 전달하지 않지만, future의 set의 여부에 따라 플래그 역할을 수행 가능
		promise<void> pro;
		//get_future를 통해 future 객체를 받는 것은 한번만 가능하다.
		future<void> data = pro.get_future();

		thread t1 = thread(anywork5, &pro);
		while (data.wait_for(chrono::seconds(1)) != future_status::ready) {
			cout << ">";
		}
		cout << "done" << endl;
		t1.join();
	}
	void anywork6(shared_future<void> sf) {
		sf.get();
		printf("go \n");
	}
	void case13() {
		promise<void> pro;
		shared_future<void> sf = pro.get_future();
		thread t1(anywork6, sf), t2(anywork6, sf), t3(anywork6, sf), t4(anywork6, sf);
		cout << "ready" << endl;
		this_thread::sleep_for(chrono::seconds(2));
		cout << "start" << endl;
		pro.set_value();
		t1.join();
		t2.join();
		t3.join();
		t4.join();
	}

	int anywork7(int n) {
		return n + 1;
	}
	void case14() {
		// 직접 promise를 전달할 필요 없이 함수를 비동기적으로 처리가능하게 만든다.
		// 예외가 발생할 경우 알아서 future로 예외를 담아 던진다.
		packaged_task<int(int)> task(anywork7);
		future<int> result = task.get_future();
		//packaged_task는 복사 생성이 불가하다.
		thread t1(move(task), 1);
		cout << "result " << result.get() << endl;
		t1.join();
	}
	int anywork8(const vector<int>& list, int start, int end) {
		int total = 0;
		for (int i = start; i < end; i++) {
			total += list[i];
		}
		return total;
	}
	int parallelSum(const vector<int>& list) {
		future<int> future1 = async(std::launch::async, anywork8, cref(list), 0, list.size() / 2);
		int half = anywork8(list, list.size() / 2, list.size());
		return half + future1.get();
	}
	void case15() {
		vector<int> ilist;
		ilist.resize(1000);
		for (int i = 0; i < ilist.size(); i++) {
			ilist[i] = i+1;
		}
		cout <<"1부터 1000까지 합 : " << parallelSum(ilist) << endl;

	}
	class tpool {
	private:
		size_t limit;
		vector<thread> workers;
		queue<function<void()>> jobs;
		condition_variable cv;
		mutex checkJobs;
		bool shutdown;
		void worker() {
			while (!shutdown) {
				unique_lock<mutex> ul(checkJobs);
				cv.wait(ul, [job = &jobs, shutdown = &shutdown]() {
					return *shutdown || !job->empty();
					});
				if (shutdown) {
					return;
				}
				function<void()> work = move(jobs.front());
				jobs.pop();
				cout << "working..." << endl;
				ul.unlock();
				work();
			}
		}
		void init() {
			workers.reserve(limit);
			for (size_t i = 0; i < limit; i++) {
				workers.push_back( move( thread( mem_fn(&tpool::worker), this) ) );
			}
		}
	public:
		tpool() :shutdown(false),limit(static_cast<size_t>(thread::hardware_concurrency())) {
			init();
		}
		tpool(int value) : limit(value), shutdown(false) {
			init();
		}

		//read invoke_result_t
		template<typename T,typename... args>
		future<typename invoke_result<T, args...>::type> push(T work, args... value) {
			if (shutdown) {
				throw exception("already shutdown");
			}
			
			using ReturnType = typename invoke_result<T, args...>::type;
			//packaged_task<ReturnType()> works(bind(work,value...));
			packaged_task<ReturnType()>* some = new packaged_task<ReturnType()>(bind(work,value...));
			future<ReturnType> result = some->get_future();
			{
				lock_guard<mutex> lg(checkJobs);
				jobs.push([some]() {(*some)(); delete some; });
			}
			some = NULL;
			cv.notify_one();
			return result;
		}
		template<typename T>
		void push(T work) {
			if (shutdown) {
				throw exception("already shutdown");
			}
			{
				lock_guard<mutex> lg(checkJobs);
				jobs.push(
					[work]() {work(); }
				);
			}
			cv.notify_one();
		}

		~tpool() {
			shutdown = true;
			cv.notify_all();
			for (size_t i = 0; i < workers.size();i++) {
				workers[i].join();
			}
		}

	};
	class anyclass {
	public:
		anyclass() {
			cout << "default constructor\n";
		}
		anyclass(const anyclass& value) {
			cout << "copy constructor\n";
		}
		anyclass(anyclass&& value) noexcept {
			cout << "move constructor\n";
		}
		~anyclass() {
			cout << "destructor\n";
		}
		anyclass& operator=(const anyclass& value) {
			cout << "copy value assignment\n";
		}
		anyclass& operator=(anyclass&& value) noexcept {
			cout << "move value assignemt\n";
		}
		
	};
	void anywork9() {
		cout << "void function test" << endl;
	}
	int anywork9(int i) {
		this_thread::sleep_for(chrono::seconds(3));
		return i;
	}
	
	void case16() {
		tpool mypool;
		auto test=mypool.push(static_cast<int(*)(int)>(anywork9), 1);
		test.wait();
		cout << test.get() << endl;
	}

}