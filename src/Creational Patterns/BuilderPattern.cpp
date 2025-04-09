#include <iostream>
#include <string>

// 产品类：Computer
class Computer {
public:
    std::string CPU;
    std::string RAM;
    std::string storage;
    std::string GPU;

    void show() {
        std::cout << "Computer Configuration: \n"
                  << "CPU: " << CPU << "\n"
                  << "RAM: " << RAM << "\n"
                  << "Storage: " << storage << "\n"
                  << "GPU: " << GPU << std::endl;
    }
};

// 抽象建造者类
class ComputerBuilder {
public:
    virtual void buildCPU() = 0;
    virtual void buildRAM() = 0;
    virtual void buildStorage() = 0;
    virtual void buildGPU() = 0;
    virtual Computer getResult() = 0;
    virtual ~ComputerBuilder() = default;
};

// 具体建造者：GamingComputerBuilder
class GamingComputerBuilder : public ComputerBuilder {
private:
    Computer computer;

public:
    void buildCPU() override {
        computer.CPU = "Intel i9 13900K";
    }

    void buildRAM() override {
        computer.RAM = "32GB DDR5";
    }

    void buildStorage() override {
        computer.storage = "1TB SSD";
    }

    void buildGPU() override {
        computer.GPU = "NVIDIA RTX 4090";
    }

    Computer getResult() override {
        return computer;
    }
};

// 具体建造者：WorkstationComputerBuilder
class WorkstationComputerBuilder : public ComputerBuilder {
private:
    Computer computer;

public:
    void buildCPU() override {
        computer.CPU = "AMD Ryzen Threadripper 3990X";
    }

    void buildRAM() override {
        computer.RAM = "128GB DDR4";
    }

    void buildStorage() override {
        computer.storage = "2TB SSD + 10TB HDD";
    }

    void buildGPU() override {
        computer.GPU = "NVIDIA Quadro RTX 8000";
    }

    Computer getResult() override {
        return computer;
    }
};

// 指挥者类
class Director {
private:
    ComputerBuilder* builder;

public:
    // 构造函数接受一个具体的建造者
    Director(ComputerBuilder* builder) : builder(builder) {}

    void construct() {
        builder->buildCPU();
        builder->buildRAM();
        builder->buildStorage();
        builder->buildGPU();
    }
};

/*
建造者模式（Builder Pattern）是一种创建型设计模式，旨在使用相同的构建过程创建不同类型的对象。建造者模式允许你将一个复杂对象的构建过程与它的表示分离，使得同样的构建过程可以创建不同的表示。

在建造者模式中，通常会有一个 Builder 类，它负责逐步构建一个复杂的对象。Director 类负责指挥 Builder 类的构建过程，最终得到一个完整的产品。

主要角色：
    Product（产品）：最终被构建的复杂对象，包含多个组成部分。

    Builder（建造者）：定义了构建产品的步骤和接口，用来构建产品的各个部分。

    ConcreteBuilder（具体建造者）：实现了 Builder 接口，负责具体构建产品的各个部分。

    Director（指挥者）：指挥 Builder 执行构建步骤，并最终返回产品。
*/


// 客户端代码
int main() {
    // 创建指挥者并传入具体的建造者
    GamingComputerBuilder gamingBuilder;
    Director director(&gamingBuilder);

    // 指挥者指示建造者创建复杂产品
    director.construct();
    Computer gamingComputer = gamingBuilder.getResult();
    gamingComputer.show();

    std::cout << "-------------------\n";

    // 创建工作站计算机
    WorkstationComputerBuilder workstationBuilder;
    Director workstationDirector(&workstationBuilder);
    workstationDirector.construct();
    Computer workstationComputer = workstationBuilder.getResult();
    workstationComputer.show();

    return 0;
}
