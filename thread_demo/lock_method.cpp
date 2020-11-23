/*
一般有三种加锁解锁方法：
1.直接调用std::mutex的对象的lock()/unlock()
2.为了避免忘记解锁,<mutex>库封装了一个RAII模板类std::lock_guard，可随该对象的创建立和销毁自动加解锁，创建对象时必须给一个mutex_type参数初始化
3.更加灵活强大的加锁方法，std::unique_lock模板类，除了有方法２的功能，还能延迟锁定，递归锁定，和条件变量配合使用，但时间和性能成本相应较高　
*/

#include <mutex>


int g_i = 0;	///全局变量，可能被多个线程读写
int main(int argc, char** argv) {
    std::mutex m;
    int i = 0; 
	
    //这里只是列举使用方法，并不是多线程加解锁的流程
    //method 1:
    m.lock();
    ++i;
    m.unlock();
　　
　　//method 2:
    {
      std::lock_guard<std::mutex> lk(m);	///这里必须要用某个mutex_type类型的对象参数构造
　    ++i;
    }	///对象析构时解锁了
　　
　　//method 3:
   {
     std::unique_lock<std::mutex> lk1(m);
     ++i;
　 　std::unique_lock<std::mutex> emy_lk; ///创建一个锁，不拥有任何mutex_type
     emy_lk.try_lock(m); ///尝试加锁，成功则执行
　　 std::unique_lock<std::mutex> delay_lk(m, std::defer_lock); ///延迟加锁　	　
   }	
		


}
