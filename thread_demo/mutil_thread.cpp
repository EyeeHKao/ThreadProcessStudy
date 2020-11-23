#include <thread>
#include <iostream>
#include <mutex>
#include <atomic>

/*
多线程下通信或数据共享，一般需要用到各种锁去保证共享数据的完整性
　互斥锁：任何时刻只允许一个线程独享共享数据或关键代码区，其他线程阻塞等待（此时ｃｐｕ可以暂时放下阻塞线程处理其他线程任务）
　自旋锁：同互斥锁，不同点在于，被阻塞的线程一直不停尝试获取锁，ｃｐｕ不能去处理其他线程任务，ｃｐｕ占用率高
　读写锁：多个线程可以同时读某个共享的数据或关键代码区，但是写操作时只能一个线程独占，同时读写操作也不能同时进行
　条件锁（条件变量）：有条件的阻塞某个线程，设置某个信号变量（条件变量），一直阻塞等待，直到某个条件满足为止
　递归锁：防止死锁而应用的一种，一种常见的死锁情形：获取某个互斥量后，调用了某个函数，而该函数内部有递归的要去获取那个互斥量，于是该线程会一直阻塞等待解锁，而导致线程卡死，形成死锁
　无锁编程（原子量）：使用原子操作的变量，可以不考虑各种复杂的加锁解锁情形




*/


using namespace std;

int i = 0;
//atomic_int i{0}; //使用原子操作，实现无锁编程，避免死锁问题
 
mutex mut;	//使用互斥锁

void iplusplus(){
  int c = 10000;
  while (c--){
   // lock_guard<mutex> lock(mut);
    mut.lock();
    i++;
   mut.unlock();
  // lock.unlock();		
  }
};

void readi(){
  int c = 10000;
  while(c--) {
    std::cout << "read i: " << i << std::endl;
  }
};

	
int main()
{
//  thread t1(iplusplus);
//  thread t2(iplusplus);
//  t1.join();
//  t2.join();
  thread t3(readi);
  thread t4(readi);
  cout << "i = " << i << endl;
  return 0;
}


