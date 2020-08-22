#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <list>
#include <unordered_map>
#include <set>
#include <algorithm>

using namespace std;

/*
A producer continuously produces a stream of characters. 
There are multiple consumer threads which read the chars
and match to one of known strings and increment the counter
for that pattern. Write the consumer function. 
Show how you will synchronize and maintain parallelism. 

Ex: Producer: abcdegabccaabbaacv ...... 
Known strings[] = {"ab", "aa", "fff" ... } 
patternMatchCount[] = {3, 2, 0 ... }

/*
Solution:
1) Clarification of patternMatchcount is required: do overlaping 
   patterns count or not: e.g. in "AAA" how many times does "AA"
   occure 1 or 2 times? assumption: 2, overlaping counts

2) The syncronization can depend on the pattern matching approach:
   a) The use of brute force or Rabin-Karp requires to hold
      a buffer of length of the pattern to verify if it's a
	  match.
	  Such a buffer can be held by each consumer-thread which
	  can be efficient in terms of synchronization but inefficient
	  in terms of memory usage (if there are a lot of patterns)
   b) If it's automaton based, no buffer is required. Automaton
      based is preferable, but much more complicated to implement
	  (I doubt it is expected to derive the algorithm in an 
	  interview...)

3) For simplicity I would assume the first implementation is that
   each consumer has his own buffer and later on I would correct
   this with an automaton based approach.

4) Synchronization in this case is now, the producer has to 
   push a character to all consumers, this can be done using
   a waitable queue. The waitable queue will be inefficient 
   in terms of syncrhonization needed and because it may 
   dynamically create items, thus a critical section is 
   held over a heap allocation etc...   
   
   It could be improved
   with a lockless buffer which is going to be quite tricky 
   to implement in a non-managed language such as C++ if 
   multicore support is required. If you're not a hard core
   C++ low level programmer with experience in writing drivers
   and lockless stuff it's maybe a good idea to point out 
   that you wont get it error-free and efficient.

5) An other thing to consider is how the system shuts down
   once the producer decides to terminate (reaches the end of 
   the input stream)  

   Here the rather messy code in C++ 11
*/

#include <memory>
#include <iostream>
#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class WaitableQueue
{
private:
	mutex mutex_;
	condition_variable signal_;
	queue<char> queue_;

public:
	void push(char item) 
	{
		{
			unique_lock<mutex> cs(mutex_);
			queue_.push(item);
		}
		signal_.notify_one();
	}

	char pop() 
	{
		unique_lock<mutex> cs(mutex_);
		signal_.wait(cs, [&](){ return queue_.size() > 0; });
		char result = queue_.front(); 
		queue_.pop();
		return result;
	}	
};

class Consumer
{
private:
	WaitableQueue queue_;
	string pattern_;
	string buffer_;
	int bufferEnd_;
	int counter_;
	thread thread_;

public:
	Consumer(const string& pattern) : counter_(0), 
		bufferEnd_(0), pattern_(pattern)
	{ 
		thread_ = thread([&]{
			while(true) {
				char item = queue_.pop();
				if(item == '\0') break; // end signal
				if(matchNext(item)) counter_++;
			}
		});
	}

	WaitableQueue* getQueue() { return &queue_; }	
	int getCounter() const { return counter_; } 
	string getPattern() const { return pattern_; }
	void join() { thread_.join(); }

private:
	bool matchNext(char next) 
	{
		// this match code is inefficient, improvements possible 
		// by using Rabin-Karp or an automaton based approach
		int m = pattern_.length();
		if(buffer_.length() < bufferEnd_ + 1) buffer_.append(1, next);
		else buffer_[bufferEnd_] = next;
		bufferEnd_ = (bufferEnd_ + 1) % m;
		bool match = buffer_.length() == m; 
		for(int i = 0; i < m && match; ++i) 
			match = buffer_[(bufferEnd_ + i) % m] == pattern_[i]; 
		return match;
	}
};

class Producer
{
private:
	vector<WaitableQueue*> queues_;
	string input_;
	thread thread_;

public:
	Producer(const vector<WaitableQueue*>& queues, const string& input) 
		: queues_(queues), input_(input)
	{
		thread_ = thread([&] {
			// send input
			for(auto ch : input_) { 
				for(auto co : queues) co->push(ch);
			}
			
			// signal end of input
			for(auto co : queues) co->push('\0');		
		});
	}

	void join() { thread_.join(); }	
};


int main()
{
	// create consumers
	vector<Consumer*> consumers({
		new Consumer("ab"),
		new Consumer("aa"),
		new Consumer("ffff")
	});
	
	// get queues from consumers
	vector<WaitableQueue*> queues;
	for(auto& co : consumers) queues.push_back(co->getQueue());

	// create producer
	Producer p(queues, "abcdegabccaabbaacv");
	
	// wait for producer
	p.join();	

	//  wait and print result of consumer
	for(auto& co : consumers) {
		co->join();
		cout << "pattern: " << co->getPattern() 
			<< " count: " 
			<< co->getCounter() << endl;
	}
}
