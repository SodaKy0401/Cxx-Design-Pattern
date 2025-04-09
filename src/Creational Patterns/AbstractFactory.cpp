#include <iostream>
#include <memory>

/*

创建一组相关产品（产品族）。

抽象工厂模式（Abstract Factory Pattern）是一种创建型设计模式，它提供一个接口，用于创建一系列相关或相互依赖的对象，而无需指定它们具体的类。

关键组成部分：
抽象工厂（Abstract Factory）：声明创建抽象产品的方法。

具体工厂（Concrete Factory）：实现创建抽象产品的方法，生成具体产品的实例。

抽象产品（Abstract Product）：定义产品的接口。

具体产品（Concrete Product）：实现抽象产品接口的具体产品类。

*/


// 抽象产品类：按钮
class Button {
public:
    virtual void render() = 0;
    virtual ~Button() = default;
};
// 抽象产品类：文本框
class TextBox {
public:
    virtual void render() = 0;
    virtual ~TextBox() = default;
};
// 具体产品类：Windows按钮
class WindowsButton : public Button {
public:
    void render() override {
        std::cout << "Rendering Windows Button" << std::endl;
    }
};
// 具体产品类：Mac按钮
class MacButton : public Button {
public:
    void render() override {
        std::cout << "Rendering Mac Button" << std::endl;
    }
};
// 具体产品类：Windows文本框
class WindowsTextBox : public TextBox {
public:
    void render() override {
        std::cout << "Rendering Windows TextBox" << std::endl;
    }
};
// 具体产品类：Mac文本框
class MacTextBox : public TextBox {
public:
    void render() override {
        std::cout << "Rendering Mac TextBox" << std::endl;
    }
};

// 抽象工厂类
class GUIFactory {
public:
    virtual std::unique_ptr<Button> createButton() = 0;
    virtual std::unique_ptr<TextBox> createTextBox() = 0;
    virtual ~GUIFactory() = default;
};

// 具体工厂类：Windows工厂
class WindowsFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<WindowsButton>();
    }
    
    std::unique_ptr<TextBox> createTextBox() override {
        return std::make_unique<WindowsTextBox>();
    }
};

// 具体工厂类：Mac工厂
class MacFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<MacButton>();
    }

    std::unique_ptr<TextBox> createTextBox() override {
        return std::make_unique<MacTextBox>();
    }
};

// 具体工厂类：杂牌工厂
class HuaweiFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<WindowsButton>();
    }

    std::unique_ptr<TextBox> createTextBox() override {
        return std::make_unique<MacTextBox>();
    }
};






int main() {
    // 使用不同的工厂创建UI控件
    std::unique_ptr<GUIFactory> factory;
    
    // 可以根据平台选择工厂
    bool isWindows = true;  // 假设当前系统是Windows
    
    if (isWindows) {
        factory = std::make_unique<WindowsFactory>();
    } else {
        factory = std::make_unique<MacFactory>();
    }

    auto button = factory->createButton();
    button->render();
    auto textBox = factory->createTextBox();
    textBox->render();


    std::unique_ptr<GUIFactory> factory1; 
    factory1 = std::make_unique<HuaweiFactory>();
    auto button1 = factory1->createButton();
    button1->render();
    auto textBox1 = factory1->createTextBox();
    textBox1->render();
    
    return 0;
}
