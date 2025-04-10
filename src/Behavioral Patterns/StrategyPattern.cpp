#include <iostream>
#include <memory>

// 策略接口：定义算法的统一接口
class Strategy {
public:
    virtual ~Strategy() = default;
    virtual void execute() const = 0;  // 执行算法
};
// 具体策略类A
class ConcreteStrategyA : public Strategy {
public:
    void execute() const override {
        std::cout << "Executing Strategy A\n";
    }
};
// 具体策略类B
class ConcreteStrategyB : public Strategy {
public:
    void execute() const override {
        std::cout << "Executing Strategy B\n";
    }
};
// 具体策略类C
class ConcreteStrategyC : public Strategy {
public:
    void execute() const override {
        std::cout << "Executing Strategy C\n";
    }
};

// 上下文类：用于维护策略对象，并调用策略的算法
class Context {
private:
    std::shared_ptr<Strategy> strategy_;  // 策略接口

public:
    // 构造函数：注入策略
    Context(std::shared_ptr<Strategy> strategy) : strategy_(strategy) {}
    // 设置新的策略
    void setStrategy(std::shared_ptr<Strategy> strategy) {
        strategy_ = strategy;
    }
    // 执行当前策略的算法
    void executeStrategy() const {
        strategy_->execute();
    }
};

int main() {
    // 创建不同的策略对象
    std::shared_ptr<Strategy> strategyA = std::make_shared<ConcreteStrategyA>();
    std::shared_ptr<Strategy> strategyB = std::make_shared<ConcreteStrategyB>();
    std::shared_ptr<Strategy> strategyC = std::make_shared<ConcreteStrategyC>();

    // 创建上下文对象，并选择策略A
    Context context(strategyA);
    context.executeStrategy();  // 执行策略A

    // 动态切换策略
    context.setStrategy(strategyB);
    context.executeStrategy();  // 执行策略B
    // 动态切换策略
    context.setStrategy(strategyC);
    context.executeStrategy();  // 执行策略C

    return 0;
}
