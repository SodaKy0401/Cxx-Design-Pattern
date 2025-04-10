#include <iostream>

// 抽象类：定义了模板方法和一些抽象步骤
class AbstractClass {
public:
    // 模板方法
    void templateMethod() {
        step1();
        step2();
        step3();
    }

protected:
    // 抽象步骤：具体实现由子类提供
    virtual void step1() {
        std::cout << "Step 1: Default implementation\n";
    }
    // 抽象步骤：具体实现由子类提供
    virtual void step2() = 0;
    // 可选的钩子方法：子类可以重载它来改变默认行为
    virtual void step3() {
        std::cout << "Step 3: Default implementation\n";
    }
};

// 子类A：实现具体的步骤
class ConcreteClassA : public AbstractClass {
protected:
    void step2() override {
        std::cout << "Step 2: ConcreteClassA implementation\n";
    }

    // 可以选择重载step3方法
    void step3() override {
        std::cout << "Step 3: ConcreteClassA custom implementation\n";
    }
};

// 子类B：实现不同的具体步骤
class ConcreteClassB : public AbstractClass {
protected:
    void step2() override {
        std::cout << "Step 2: ConcreteClassB implementation\n";
    }

    // 使用父类的默认step3实现
};

int main() {
    // 创建子类A的对象并调用模板方法
    ConcreteClassA objA;
    objA.templateMethod();  // 调用模板方法

    std::cout << "-----\n";

    // 创建子类B的对象并调用模板方法
    ConcreteClassB objB;
    objB.templateMethod();  // 调用模板方法

    return 0;
}
