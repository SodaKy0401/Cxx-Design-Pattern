#include <iostream>
#include <memory>
#include <string>



/*原型模式（Prototype Pattern）是一种 创建型设计模式，用于通过复制现有对象来创建新对象，而不是通过构造函数直接实例化。它的核心是 “克隆”：通过一个原型对象来创建新的对象副本。
适用场景
    创建对象成本较高（如初始化耗时、复杂构造等）。
    需要多个相似对象，并希望避免重复创建。
    不希望暴露对象的内部结构（封装性更强）。

主要角色有：

    Prototype（原型接口）：声明克隆方法。

    ConcretePrototype（具体原型类）：实现克隆方法。

    Client（客户端）：通过调用原型的克隆方法来复制对象。

*/
// 原型接口
class Prototype {
public:
    virtual ~Prototype() = default;

    // 克隆方法，返回一个指向自身副本的指针
    virtual std::unique_ptr<Prototype> clone() const = 0;

    // 显示对象内容的虚方法
    virtual void show() const = 0;
};

// 具体原型类1
class ConcretePrototypeA : public Prototype {
private:
    std::string data;

public:
    explicit ConcretePrototypeA(const std::string& data) : data(data) {}

    // 实现克隆方法
    std::unique_ptr<Prototype> clone() const override {
        return std::make_unique<ConcretePrototypeA>(*this);
    }

    void show() const override {
        std::cout << "ConcretePrototypeA: " << data << std::endl;
    }
};

// 具体原型类2
class ConcretePrototypeB : public Prototype {
private:
    int value;

public:
    explicit ConcretePrototypeB(int value) : value(value) {}

    // 实现克隆方法
    std::unique_ptr<Prototype> clone() const override {
        return std::make_unique<ConcretePrototypeB>(*this);
    }

    void show() const override {
        std::cout << "ConcretePrototypeB: " << value << std::endl;
    }
};
// 客户端使用
int main() {
    // 创建具体原型对象
    std::unique_ptr<Prototype> prototypeA = std::make_unique<ConcretePrototypeA>("ExampleA");
    std::unique_ptr<Prototype> prototypeB = std::make_unique<ConcretePrototypeB>(42);

    // 克隆新对象
    std::unique_ptr<Prototype> clonedA = prototypeA->clone();
    std::unique_ptr<Prototype> clonedB = prototypeB->clone();

    // 显示原型和克隆对象的信息
    prototypeA->show();
    clonedA->show();

    prototypeB->show();
    clonedB->show();

    return 0;
}
