#include <iostream>
#include <thread>
#include <memory>
#include <mutex>
#include <functional>
#include <vector>

// 懒汉式，第一次调用 getinstance() 时才初始化
template<class T>
class LazySingleton {
private:
    LazySingleton() = default;
    LazySingleton(LazySingleton&) = delete;
    LazySingleton& operator=(LazySingleton&) = delete;

    std::mutex _lk;

public:
    static LazySingleton& getinstance() {
        static LazySingleton _ins;  // C++11 保证线程安全
        return _ins;
    }

    void function(std::function<T()> func, int thread_id) {
        std::lock_guard<std::mutex> lock(_lk);
        T result = func();
        std::cout << "[Lazy] Thread " << thread_id << ": result = " << result << "\n";
    }
};

// 饿汉式，程序启动时就初始化
template<class T>
class HungrySingleton {
private:
    HungrySingleton() = default;
    HungrySingleton(HungrySingleton&) = delete;
    HungrySingleton& operator=(HungrySingleton&) = delete;

    static HungrySingleton _ins;
    std::mutex _lk;

public:
    static HungrySingleton& getinstance() {
        return _ins;
    }

    void function(std::function<T()> func, int thread_id) {
        std::lock_guard<std::mutex> lock(_lk);
        T result = func();
        std::cout << "[Hungry] Thread " << thread_id << ": result = " << result << "\n";
    }
};

// 必须在类外定义静态成员变量
template<class T>
HungrySingleton<T> HungrySingleton<T>::_ins;

void test_lazy(int id) {
    auto& instance = LazySingleton<int>::getinstance();
    instance.function([id]() { return id*id; }, id);
}

void test_hungry(int id) {
    auto& instance = HungrySingleton<int>::getinstance();
    instance.function([id]() { return id*2; }, id);
}

int main() {
     std::srand(time(nullptr));
    const int thread_count = 10;
    std::vector<std::thread> threads;

    std::cout << "Testing LazySingleton...\n";
    for (int i = 0; i < thread_count; ++i) {
        threads.emplace_back(test_lazy, i);
    }
    for (auto& th : threads) th.join();
    threads.clear();

    std::cout << "\nTesting HungrySingleton...\n";
    for (int i = 0; i < thread_count; ++i) {
        threads.emplace_back(test_hungry, i);
    }
    for (auto& th : threads) th.join();

    return 0;

   
}
