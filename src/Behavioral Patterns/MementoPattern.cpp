#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

/*

备忘录模式（Memento Pattern）保存一个对象的某个状态，以便在适当的时候恢复对象，备忘录模式属于行为型模式。

备忘录模式允许在不破坏封装性的前提下，捕获和恢复对象的内部状态。


意图
    在不破坏封装性的前提下，捕获一个对象的内部状态，并允许在对象之外保存和恢复这些状态。

主要解决的问题
    允许捕获并保存一个对象的内部状态，以便在将来可以恢复到该状态，实现撤销和回滚操作。
使用场景
    当需要提供一种撤销机制，允许用户回退到之前的状态时。
实现方式
    创建备忘录类：用于存储和封装对象的状态。
    创建发起人角色：负责创建备忘录，并根据需要恢复状态。
    创建备忘录管理类（可选）：负责管理所有备忘录对象。
关键代码
    备忘录：存储发起人的状态信息。
    发起人：创建备忘录，并根据备忘录恢复状态。

*/




// 备忘录类,负责存储原发器对象的内部状态。备忘录可以保持原发器的状态的一部分或全部信息
class Memento {
private:
    string state; // 保存的状态
public:
    explicit Memento(const string& state) : state(state) {}
    string getState() const { return state; }
};

// 发起者类,创建一个备忘录对象，并且可以使用备忘录对象恢复自身的内部状态。原发器通常会在需要保存状态的时候创建备忘录对象，并在需要恢复状态的时候使用备忘录对象
class Originator {
private:
    string state; // 当前状态
public:
    void setState(const string& newState) {
        state = newState;
        cout << "设置状态为：" << state << endl;
    }

    string getState() const { return state; }

    // 创建备忘录
    shared_ptr<Memento> saveToMemento() const {
        return make_shared<Memento>(state);
    }

    // 从备忘录恢复状态
    void restoreFromMemento(const shared_ptr<Memento>& memento) {
        if (memento) {
            state = memento->getState();
            cout << "从备忘录恢复状态为：" << state << endl;
        }
    }
};

// 负责人类,负责保存备忘录对象，但是不对备忘录对象进行操作或检查。负责人只能将备忘录传递给其他对象。
class Caretaker {
private:
    vector<shared_ptr<Memento>> history; // 保存状态的历史
public:
    void addMemento(const shared_ptr<Memento>& memento) {
        history.push_back(memento);
    }

    shared_ptr<Memento> getMemento(size_t index) const {
        if (index < history.size()) {
            return history[index];
        }
        return nullptr;
    }
};

int main() {
    Originator originator;
    Caretaker caretaker;

    // 设置初始状态
    originator.setState("状态1");
    caretaker.addMemento(originator.saveToMemento());

    // 修改状态
    originator.setState("状态2");
    caretaker.addMemento(originator.saveToMemento());

    // 再次修改状态
    originator.setState("状态3");

    // 从备忘录恢复状态
    originator.restoreFromMemento(caretaker.getMemento(0)); // 恢复到状态1
    originator.restoreFromMemento(caretaker.getMemento(1)); // 恢复到状态2

    return 0;
}
