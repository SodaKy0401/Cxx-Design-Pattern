#include <iostream>
#include <memory>
#include <vector>




/*
在访问者模式（Visitor Pattern）中，我们使用了一个访问者类，它改变了元素类的执行算法。通过这种方式，元素的执行算法可以随着访问者改变而改变。这种类型的设计模式属于行为型模式。根据模式，元素对象已接受访问者对象，这样访问者对象就可以处理元素对象上的操作。


意图
    旨在将数据结构与在该数据结构上执行的操作分离，从而使得添加新的操作变得更容易，而无需修改数据结构本身。

主要解决的问题
    解决在稳定数据结构和易变操作之间的耦合问题，使得操作可以独立于数据结构变化。
使用场景
    当需要对一个对象结构中的对象执行多种不同的且不相关的操作时，尤其是这些操作需要避免"污染"对象类本身。
实现方式
    定义访问者接口：声明一系列访问方法，一个访问方法对应数据结构中的一个元素类。
    创建具体访问者：实现访问者接口，为每个访问方法提供具体实现。
    定义元素接口：声明一个接受访问者的方法。
    创建具体元素：实现元素接口，每个具体元素类对应数据结构中的一个具体对象。
关键代码
    访问者接口：包含访问不同元素的方法。
    具体访问者：实现了访问者接口，包含对每个元素类的访问逻辑。
    元素接口：包含一个接受访问者的方法。
    具体元素：实现了元素接口，提供给访问者访问的入口。

*/

// 抽象的元素类
class Shape {
public:
    virtual void accept(class Visitor& v) = 0;  // 接受访问者
    virtual ~Shape() = default;
};

// 具体元素类：Circle
class Circle : public Shape {
public:
    void accept(Visitor& v) override;
    double getRadius() const { return 5.0; }
};

// 具体元素类：Rectangle
class Rectangle : public Shape {
public:
    void accept(Visitor& v) override;
    double getWidth() const { return 4.0; }
    double getHeight() const { return 3.0; }
};

// 抽象访问者
class Visitor {
public:
    virtual void visit(Circle& circle) = 0;
    virtual void visit(Rectangle& rectangle) = 0;
    virtual ~Visitor() = default;
};




// 具体访问者：计算面积
class AreaVisitor : public Visitor {
public:
    void visit(Circle& circle) override {
        double area = 3.14 * circle.getRadius() * circle.getRadius();
        std::cout << "Area of Circle: " << area << std::endl;
    }

    void visit(Rectangle& rectangle) override {
        double area = rectangle.getWidth() * rectangle.getHeight();
        std::cout << "Area of Rectangle: " << area << std::endl;
    }
};

// 实现元素类的accept方法
void Circle::accept(Visitor& v) {
    v.visit(*this);
}

void Rectangle::accept(Visitor& v) {
    v.visit(*this);
}






// 对象结构类
class ShapeCollection {
private:
    std::vector<std::shared_ptr<Shape>> shapes;
public:
    void addShape(std::shared_ptr<Shape> shape) {
        shapes.push_back(shape);
    }

    void accept(Visitor& visitor) {
        for (auto& shape : shapes) {
            shape->accept(visitor);
        }
    }
};

int main() {
    // 创建形状
    std::shared_ptr<Shape> circle = std::make_shared<Circle>();
    std::shared_ptr<Shape> rectangle = std::make_shared<Rectangle>();

    // 创建一个访问者
    AreaVisitor areaVisitor;

    // 创建一个对象结构，添加形状
    ShapeCollection collection;
    collection.addShape(circle);
    collection.addShape(rectangle);

    // 计算并输出每个形状的面积
    collection.accept(areaVisitor);

    return 0;
}
