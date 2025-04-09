#include <iostream>
#include <memory>
/*
工厂方法模式通过定义一个创建对象的接口，让子类决定实例化哪一个类。它通过将对象的创建推迟到子类来实现产品的多样化。

关键特点：
每个工厂方法都只负责创建一种产品。

工厂方法模式是单一产品的工厂模式，每次工厂方法只会返回一种具体的产品。

适合在不知道具体产品类时使用，但可以通过工厂方法来生产这些产品。

适用场景：
客户端代码不需要知道产品的具体类，只需要知道产品的接口。

需要根据不同的条件或环境创建不同的产品。

系统不希望或不应该依赖于产品类的实现。
*/



// 抽象产品类
class Shape {
public:
    virtual void draw() = 0;
    virtual ~Shape() = default;
};
// 具体产品类：圆形
class Circle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing Circle" << std::endl;
    }
};
// 具体产品类：矩形
class Rectangle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing Rectangle" << std::endl;
    }
};

// 抽象工厂类
class ShapeFactory {
public:
    virtual std::unique_ptr<Shape> createShape() = 0;  // 工厂方法
    virtual ~ShapeFactory() = default;
};

// 具体工厂类：圆形工厂
class CircleFactory : public ShapeFactory {
public:
    std::unique_ptr<Shape> createShape() override {
        return std::make_unique<Circle>();
    }
};
// 具体工厂类：矩形工厂
class RectangleFactory : public ShapeFactory {
public:
    std::unique_ptr<Shape> createShape() override {
        return std::make_unique<Rectangle>();
    }
};
int main() {
    // 使用具体工厂创建对象
    std::unique_ptr<ShapeFactory> factory1 = std::make_unique<CircleFactory>();
    auto shape1 = factory1->createShape();
    shape1->draw();

    std::unique_ptr<ShapeFactory> factory2 = std::make_unique<RectangleFactory>();
    auto shape2 = factory2->createShape();
    shape2->draw();

    return 0;
}
