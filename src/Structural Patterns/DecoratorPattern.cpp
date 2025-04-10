#include <iostream>
#include <string>

// 1. Component（组件）类
class Beverage {
public:
    virtual ~Beverage() {}
    virtual std::string getDescription() = 0;  // 获取饮品的描述
    virtual double cost() = 0;  // 计算饮品的价格
};

// 2. ConcreteComponent（具体组件）类
class Coffee : public Beverage {
public:
    std::string getDescription() override {
        return "Coffee";
    }

    double cost() override {
        return 5.0;  // 基础价格
    }
};

class Tea : public Beverage {
public:
    std::string getDescription() override {
        return "Tea";
    }

    double cost() override {
        return 3.0;  // 基础价格
    }
};

// 3. Decorator（装饰器）类
class BeverageDecorator : public Beverage {
protected:
    Beverage* beverage;

public:
    BeverageDecorator(Beverage* b) : beverage(b) {}
    virtual ~BeverageDecorator() {
        delete beverage;
    }
};

// 4. ConcreteDecorator（具体装饰器）类
class MilkDecorator : public BeverageDecorator {
public:
    MilkDecorator(Beverage* b) : BeverageDecorator(b) {}

    std::string getDescription() override {
        return beverage->getDescription() + ", Milk";
    }

    double cost() override {
        return beverage->cost() + 1.0;  // 牛奶的附加费用
    }
};

class SugarDecorator : public BeverageDecorator {
public:
    SugarDecorator(Beverage* b) : BeverageDecorator(b) {}

    std::string getDescription() override {
        return beverage->getDescription() + ", Sugar";
    }

    double cost() override {
        return beverage->cost() + 0.5;  // 糖的附加费用
    }
};

// 客户端代码
int main() {
    Beverage* beverage = new Coffee();  // 创建一个咖啡
    std::cout << "Description: " << beverage->getDescription() << "\n";
    std::cout << "Cost: " << beverage->cost() << "\n";

    // 添加装饰器
    Beverage* milkCoffee = new MilkDecorator(beverage);  // 给咖啡加牛奶
    std::cout << "Description: " << milkCoffee->getDescription() << "\n";
    std::cout << "Cost: " << milkCoffee->cost() << "\n";

    Beverage* sweetMilkCoffee = new SugarDecorator(milkCoffee);  // 给牛奶咖啡加糖
    std::cout << "Description: " << sweetMilkCoffee->getDescription() << "\n";
    std::cout << "Cost: " << sweetMilkCoffee->cost() << "\n";

    // 清理内存
    delete sweetMilkCoffee;

    return 0;
}
