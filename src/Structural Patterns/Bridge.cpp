#include <iostream>


/*

用于将抽象部分与实现部分分离，使得它们可以独立地变化 , 避免使用继承导致的类爆炸问题，提供更灵活的扩展方式。

使用场景
    当系统可能从多个角度进行分类，且每个角度都可能独立变化时，桥接模式是合适的。

以下是桥接模式的几个关键角色：

    抽象（Abstraction）：定义抽象接口，通常包含对实现接口的引用。
    扩展抽象（Refined Abstraction）：对抽象的扩展，可以是抽象类的子类或具体实现类。
    实现（Implementor）：定义实现接口，提供基本操作的接口。
    具体实现（Concrete Implementor）：实现实现接口的具体类。


*/










// 实现类接口：颜色
class Color {
public:
    virtual void fillColor() = 0; // 颜色的填充
    virtual ~Color() = default;
};

// 具体实现类：红色
class Red : public Color {
public:
    void fillColor() override {
        std::cout << "Filling with Red color." << std::endl;
    }
};

// 具体实现类：蓝色
class Blue : public Color {
public:
    void fillColor() override {
        std::cout << "Filling with Blue color." << std::endl;
    }
};

// 抽象类：形状
class Shape {
protected:
    Color* color; // 持有颜色的引用

public:
    Shape(Color* c) : color(c) {}
    virtual void draw() = 0; // 绘制形状

    void applyColor() {
        color->fillColor(); // 使用颜色填充
    }
    virtual ~Shape() = default;
};

// 扩充抽象类：圆形
class Circle : public Shape {
public:
    Circle(Color* c) : Shape(c) {}

    void draw() override {
        std::cout << "Drawing Circle" << std::endl;
        applyColor(); // 填充颜色
    }
};

// 扩充抽象类：矩形
class Rectangle : public Shape {
public:
    Rectangle(Color* c) : Shape(c) {}

    void draw() override {
        std::cout << "Drawing Rectangle" << std::endl;
        applyColor(); // 填充颜色
    }
};

int main() {
    // 创建具体的颜色对象
    Color* red = new Red();
    Color* blue = new Blue();

    // 创建不同形状并为其赋予不同颜色
    Shape* circle = new Circle(red);
    Shape* rectangle = new Rectangle(blue);

    // 绘制形状并应用颜色
    circle->draw();    // 绘制圆形，并填充红色
    rectangle->draw(); // 绘制矩形，并填充蓝色

    // 清理内存
    delete red;
    delete blue;
    delete circle;
    delete rectangle;
    return 0;
}
