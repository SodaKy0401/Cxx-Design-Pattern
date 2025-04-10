#include <iostream>
#include <memory>
#include <string>


/*

责任链模式（Chain of Responsibility Pattern）为请求创建了一个接收者对象的链。这种模式给予请求的类型，对请求的发送者和接收者进行解耦。这种类型的设计模式属于行为型模式。


    责任链模式通过将多个处理器（处理对象）以链式结构连接起来，使得请求沿着这条链传递，直到有一个处理器处理该请求为止。

责任链模式允许多个对象都有机会处理请求，从而避免请求的发送者和接收者之间的耦合关系。将这些对象连成一条链，并沿着这条链传递请求。


意图
    允许将请求沿着处理者链传递，直到请求被处理为止。。

主要解决的问题
    解耦请求发送者和接收者，使多个对象都有可能接收请求，而发送者不需要知道哪个对象会处理它。
使用场景
    当有多个对象可以处理请求，且具体由哪个对象处理由运行时决定时。
    当需要向多个对象中的一个提交请求，而不想明确指定接收者时。
实现方式
    定义处理者接口：所有处理者必须实现同一个接口。
    创建具体处理者：实现接口的具体类，包含请求处理逻辑和指向链中下一个处理者的引用。

*/




// 抽象处理者
class Approver {
protected:
    std::shared_ptr<Approver> nextApprover; // 下一个处理者
public:
    void setNextApprover(std::shared_ptr<Approver> approver) {
        nextApprover = approver;
    }

    virtual void handleRequest(int amount) = 0;
    virtual ~Approver() = default;
};

/*实现Handler接口，包含请求处理逻辑和对下一个处理者的引用。*/
// 具体处理者：经理
class Manager : public Approver {
public:
    void handleRequest(int amount) override {
        if (amount <= 1000) {
            std::cout << "Manager approved request of amount: " << amount << std::endl;
        } else if (nextApprover) {
            nextApprover->handleRequest(amount); // 转发给下一个处理者
        }
    }
};

// 具体处理者：总监
class Director : public Approver {
public:
    void handleRequest(int amount) override {
        if (amount <= 5000) {
            std::cout << "Director approved request of amount: " << amount << std::endl;
        } else if (nextApprover) {
            nextApprover->handleRequest(amount); // 转发给下一个处理者
        }
    }
};

// 具体处理者：CEO
class CEO : public Approver {
public:
    void handleRequest(int amount) override {
        std::cout << "CEO approved request of amount: " << amount << std::endl;
    }
};

// 客户端代码
int main() {
    // 创建各个处理者
    auto manager = std::make_shared<Manager>();
    auto director = std::make_shared<Director>();
    auto ceo = std::make_shared<CEO>();

    // 设置责任链
    manager->setNextApprover(director);
    director->setNextApprover(ceo);

    // 启动请求
    std::cout << "Requesting amount 500:\n";
    manager->handleRequest(500);  // Manager approved request of amount: 500

    std::cout << "\nRequesting amount 1500:\n";
    manager->handleRequest(1500);  // Director approved request of amount: 1500

    std::cout << "\nRequesting amount 7000:\n";
    manager->handleRequest(7000);  // CEO approved request of amount: 7000

    return 0;
}
