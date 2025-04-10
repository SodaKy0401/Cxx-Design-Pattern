#include <iostream>
#include <memory>
using namespace std;


/*
在状态模式（State Pattern）中，类的行为是基于它的状态改变的，这种类型的设计模式属于行为型模式。

在状态模式中，我们创建表示各种状态的对象和一个行为随着状态对象改变而改变的 context 对象。

状态模式允许对象在内部状态改变时改变其行为，使得对象在不同的状态下有不同的行为表现。通过将每个状态封装成独立的类，可以避免使用大量的条件语句来实现状态切换。

允许一个对象在其内部状态改变时改变其行为，看起来就像是改变了其类一样。

主要解决的问题
    状态模式解决对象行为依赖于其状态的问题，使得对象可以在状态变化时切换行为。
使用场景
    当代码中存在大量条件语句，且这些条件语句依赖于对象的状态时。
实现方式
    定义状态接口：声明一个或多个方法，用于封装具体状态的行为。
    创建具体状态类：实现状态接口，根据状态的不同实现具体的行为。
    定义上下文类：包含一个状态对象的引用，并在状态改变时更新其行为。
*/

// 抽象状态类
class ElevatorState {
public:
    virtual void handleRequest() = 0;
    virtual ~ElevatorState() = default;
};

// 上下文类
class ElevatorContext {
private:
    unique_ptr<ElevatorState> state;
public:
    void setState(unique_ptr<ElevatorState> newState) {
        state = move(newState);
    }
    void request() {
        if (state) state->handleRequest();
    }
};

// 具体状态类：停止状态
class StoppedState : public ElevatorState {
public:
    void handleRequest() override {
        cout << "电梯处于停止状态。" << endl;
    }
};

// 具体状态类：运行状态
class RunningState : public ElevatorState {
public:
    void handleRequest() override {
        cout << "电梯正在运行。" << endl;
    }
};

int main() {
    ElevatorContext elevator;

    elevator.setState(make_unique<StoppedState>());
    elevator.request();
    
    elevator.setState(make_unique<RunningState>());
    elevator.request();

    std::unique_ptr<ElevatorState> stop =make_unique<StoppedState>();
    elevator.setState(std::move(stop));
    elevator.request();
    return 0;
}
