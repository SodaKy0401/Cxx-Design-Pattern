
#include <iostream>
#include <vector>
 
/*
命令模式（Command Pattern）是一种数据驱动的设计模式，它属于行为型模式。

    命令模式将一个请求封装为一个对象，从而使你可以用不同的请求对客户进行参数化，对请求排队或记录请求日志，以及支持可撤销的操作。

    将请求封装为一个对象，允许用户使用不同的请求对客户端进行参数化。

主要解决的问题
    解决在软件系统中请求者和执行者之间的紧耦合问题，特别是在需要对行为进行记录、撤销/重做或事务处理等场景。
使用场景
    当需要对行为进行记录、撤销/重做或事务处理时，使用命令模式来解耦请求者和执行者。
实现方式
    定义命令接口：所有命令必须实现的接口。
    创建具体命令：实现命令接口的具体类，包含执行请求的方法。

    调用者：持有命令对象并触发命令的执行。
    接收者：实际执行命令的对象。
*/


/*命令（Command）：定义执行命令的接口。*/
class Command {
public:
    virtual void execute() = 0;  // 执行操作
    virtual void undo() = 0;     // 撤销操作
    virtual ~Command() = default;
};

/*Receiver 接收者（Receiver）类：执行命令的实际对象*/
class Light {
public:
    void on() {
        std::cout << "Light is ON\n";
    }

    void off() {
        std::cout << "Light is OFF\n";
    }
};
class Fan {
public:
    void on() {
        std::cout << "Fan is ON\n";
    }

    void off() {
        std::cout << "Fan is OFF\n";
    }
};

/*ConcreteCommand 类*/
class LightOnCommand : public Command {
private:
    Light& light;

public:
    LightOnCommand(Light& l) : light(l) {}

    void execute() override {
        light.on();
    }

    void undo() override {
        light.off();
    }
};
class LightOffCommand : public Command {
private:
    Light& light;

public:
    LightOffCommand(Light& l) : light(l) {}

    void execute() override {
        light.off();
    }

    void undo() override {
        light.on();
    }
};
class FanOnCommand : public Command {
private:
    Fan& fan;

public:
    FanOnCommand(Fan& f) : fan(f) {}

    void execute() override {
        fan.on();
    }

    void undo() override {
        fan.off();
    }
};
class FanOffCommand : public Command {
private:
    Fan& fan;

public:
    FanOffCommand(Fan& f) : fan(f) {}

    void execute() override {
        fan.off();
    }

    void undo() override {
        fan.on();
    }
};

/*Invoker 调用者类,使用命令对象的入口点*/
class RemoteControl {
private:
    Command* command;
    std::vector<Command*> commandHistory;  // 用于保存命令历史

public:
    void setCommand(Command* cmd) {
        command = cmd;
    }

    void pressButton() {
        if (command) {
            command->execute();
            commandHistory.push_back(command);  // 将执行的命令添加到历史记录中
        }
    }

    void pressUndoButton() {
        if (!commandHistory.empty()) {
            Command* lastCommand = commandHistory.back();
            lastCommand->undo();
            commandHistory.pop_back();  // 撤销后从历史记录中移除命令
        }
    }
};


int main() {
    // 创建设备
   Light light;
    Fan fan;

    // 创建命令对象
    LightOnCommand lightOn(light);
    LightOffCommand lightOff(light);
    FanOnCommand fanOn(fan);
    FanOffCommand fanOff(fan);

    // 创建遥控器
    RemoteControl remote;
    // 开灯
    remote.setCommand(&lightOn);
    remote.pressButton();  // 输出: Light is ON
    // 关灯
    remote.setCommand(&lightOff);
    remote.pressButton();  // 输出: Light is OFF
    // 开风扇
    remote.setCommand(&fanOn);
    remote.pressButton();  // 输出: Fan is ON
    // 关风扇
    remote.setCommand(&fanOff);
    remote.pressButton();  // 输出: Fan is OFF

    remote.pressUndoButton();  
    remote.pressUndoButton();  
    return 0;
 
}
