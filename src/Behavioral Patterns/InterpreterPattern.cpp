#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <sstream>

/*

解释器模式（Interpreter Pattern）提供了评估语言的语法或表达式的方式，它属于行为型模式。

    解释器模式给定一个语言，定义它的文法的一种表示，并定义一个解释器，这个解释器使用该表示来解释语言中的句子。
    这种模式被用在 SQL 解析、符号处理引擎等。


意图
    定义一种语言的文法表示，并创建一个解释器，该解释器能够解释该语言中的句子。。
主要解决的问题
    解释器模式用于构建一个能够解释特定语言或文法的句子的解释器。
使用场景
    当某一特定类型的问题频繁出现，并且可以通过一种简单的语言来表达这些问题的实例时。
实现方式
    定义文法：明确语言的终结符和非终结符。
    构建语法树：根据语言的句子构建对应的语法树结构。
    创建环境类：包含解释过程中所需的全局信息，通常是一个HashMap。
关键代码
    终结符与非终结符：定义语言的文法结构。
    环境类：存储解释过程中需要的外部环境信息。


*/











// 抽象表达式类
class Expression {
public:
    virtual int interpret() = 0;  // 解释表达式
    virtual ~Expression() = default;
};

// 终结符表达式类：数字
class Number : public Expression {
private:
    int number;
public:
    explicit Number(int num) : number(num) {}

    int interpret() override {
        return number;  // 返回数字本身
    }
};

// 非终结符表达式类：加法
class Add : public Expression {
private:
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;
public:
    Add(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
        : left(std::move(left)), right(std::move(right)) {}

    int interpret() override {
        return left->interpret() + right->interpret();  // 计算加法
    }
};

// 非终结符表达式类：乘法
class Multiply : public Expression {
private:
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;
public:
    Multiply(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
        : left(std::move(left)), right(std::move(right)) {}

    int interpret() override {
        return left->interpret() * right->interpret();  // 计算乘法
    }
};

// 上下文类：存储变量和值
class Context {
private:
    std::map<std::string, int> variables;
public:
    void assign(const std::string& var, int value) {
        variables[var] = value;
    }

    int getValue(const std::string& var) {
        return variables[var];
    }
};

// 客户端：解释一个表达式
int main() {
    // 构建表达式: 3 + 5 * 2
    std::shared_ptr<Expression> expression = std::make_shared<Add>(
        std::make_shared<Number>(3),
        std::make_shared<Multiply>(
            std::make_shared<Number>(5),
            std::make_shared<Number>(2)
        )
    );

    // 计算并输出结果
    std::cout << "Result: " << expression->interpret() << std::endl;

    return 0;
}
