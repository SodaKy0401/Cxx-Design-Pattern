#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm> 
using namespace std;

/*
观察者模式
    观察者模式是一种行为型设计模式，它定义了一种一对多的依赖关系，当一个对象的状态发生改变时，其所有依赖者都会收到通知并自动更新。

当对象间存在一对多关系时，则使用观察者模式（Observer Pattern）。比如，当一个对象被修改时，则会自动通知依赖它的对象。观察者模式属于行为型模式。


意图
    创建了对象间的一种一对多的依赖关系，当一个对象状态改变时，所有依赖于它的对象都会得到通知并自动更新。。

主要解决的问题
    观察者模式解决的是一个对象状态改变时，如何自动通知其他依赖对象的问题，同时保持对象间的低耦合和高协作性。
使用场景
    当一个对象的状态变化需要同时更新其他对象时。
实现方式
    定义观察者接口：包含一个更新方法。
    创建具体观察者：实现观察者接口，定义接收到通知时的行为。
    定义主题接口：包含添加、删除和通知观察者的方法。
    创建具体主题：实现主题接口，管理观察者列表，并在状态改变时通知它们。

*/


// 观察者接口
class Observer {
public:
    virtual void update(const string& weather) = 0;
    virtual ~Observer() = default;
};

// 具体观察者：手机设备
class PhoneDisplay : public Observer {
private:
    string phoneName;
public:
    explicit PhoneDisplay(const string& name) : phoneName(name) {}

    void update(const string& weather) override {
        cout << phoneName << " 接收到天气更新：" << weather << endl;
    }
};

// 主题接口
class Subject {
public:
    virtual void attach(shared_ptr<Observer> observer) = 0;
    virtual void detach(shared_ptr<Observer> observer) = 0;
    virtual void notify() = 0;
    virtual ~Subject() = default;
};

// 具体主题：天气预报中心
class WeatherStation : public Subject {
private:
    vector<shared_ptr<Observer>> observers;//管理观察者列表
    string weather;
public:
    void attach(shared_ptr<Observer> observer) override {
        observers.push_back(observer);
    }

    void detach(shared_ptr<Observer> observer) override {
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notify() override {
        for (const auto& observer : observers) {
            observer->update(weather);
        }
    }

    void setWeather(const string& newWeather) {
        weather = newWeather;
        notify(); // 通知所有观察者
    }
};


// 测试
int main() {
    // 创建主题
    auto weatherStation = make_shared<WeatherStation>();

    // 创建观察者
    auto phone1 = make_shared<PhoneDisplay>("手机A");
    auto phone2 = make_shared<PhoneDisplay>("手机B");

    // 注册观察者
    weatherStation->attach(phone1);
    weatherStation->attach(phone2);

    // 更新天气
    weatherStation->setWeather("晴天");
    weatherStation->setWeather("下雨");

    // 移除一个观察者
    weatherStation->detach(phone1);

    // 再次更新天气
    weatherStation->setWeather("阴天");

    return 0;
}
