#include <iostream>
#include <memory>
/*
适配器模式（Adapter Pattern） 是一种结构型设计模式，主要用于解决接口不兼容的问题。它通过为不兼容的接口提供一个适配器，使得原本由于接口不兼容而不能一起工作的类可以在一起工作。

适配器模式的定义
    适配器模式定义了一个用于将一个类的接口转换成客户端所期望的另一个接口。适配器模式使得原本由于接口不兼容而无法一起工作的类能够在一起工作。

适配器模式的组成

    目标接口（Target）：客户所期望的接口。

    源接口（Adaptee）：需要适配的类的接口。

    适配器（Adapter）：实现目标接口，能够将源接口的方法转换为目标接口的方法。

    客户端（Client）：通过目标接口与适配器交互。

*/




// 目标接口（Target）
class Target {
public:
    virtual ~Target() = default;
    virtual void request() const {
        std::cout << "Default Target implementation.\n";
    }
};


// 需要适配的源接口类（Adaptee）
class Adaptee {
public:
    void specificRequest() const {
        std::cout << "Adaptee specific request.\n";
    }
};

// 适配器类（Adapter），将 Adaptee 转换为 Target
class Adapter : public Target {
private:
    std::shared_ptr<Adaptee> adaptee; // 适配器通过组合来访问源接口

public:
    explicit Adapter(std::shared_ptr<Adaptee> adaptee) : adaptee(std::move(adaptee)) {}
    void request() const override {
        // 调用适配者的方法
        adaptee->specificRequest();
    }
};


int main() {
    // 客户端使用目标接口
    std::shared_ptr<Target> target = std::make_shared<Target>();
    target->request();
    std::cout << std::endl;

    // 使用适配器将 Adaptee 转换为 Target
    std::shared_ptr<Adaptee> adaptee = std::make_shared<Adaptee>();
    std::shared_ptr<Target> adapter = std::make_shared<Adapter>(adaptee);
    adapter->request();

    return 0;
}
