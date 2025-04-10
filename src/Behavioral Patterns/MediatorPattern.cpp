#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <mutex>

using namespace std;


/*

中介者模式（Mediator Pattern）是用来降低多个对象和类之间的通信复杂性，属于行为型模式。

中介者模式定义了一个中介对象来封装一系列对象之间的交互。中介者使各对象之间不需要显式地相互引用，从而使其耦合松散，且可以独立地改变它们之间的交互。

通过引入一个中介者对象来封装和协调多个对象之间的交互，从而降低对象间的耦合度。

主要解决的问题
    解决对象间复杂的一对多关联问题，避免对象之间的高度耦合，简化系统结构。
使用场景
    当系统中多个类相互耦合，形成网状结构时。
实现方式
    定义中介者接口：规定中介者必须实现的接口。
    创建具体中介者：实现中介者接口，包含协调各同事对象交互的逻辑。
    定义同事类：各个对象不需要显式地相互引用，而是通过中介者来进行交互。
关键代码
    中介者：封装了对象间的交互逻辑。
    同事类：通过中介者进行通信。

*/




// 定义 Colleague 类
class Colleague {
public:
    virtual void receiveMessage(const string& message) = 0;
    virtual string getName() const = 0;
    virtual ~Colleague() = default;
};

// Mediator 接口
class Mediator {
public:
    virtual void sendMessage(const string& message, const shared_ptr<Colleague>& sender) = 0;
    virtual ~Mediator() = default;
};

// 定义 User 类，继承自 Colleague
class User : public Colleague ,public enable_shared_from_this<User>{
private:
    string name;
    weak_ptr<Mediator> chatRoom;  // 使用 weak_ptr 避免循环引用
public:
    User(const string& userName) : name(userName) {}
  
    void receiveMessage(const string& message) override {
        cout << name << " received message: " << message << endl;
    }

    string getName() const override{
        return name;
    }
    void setChatRoom(shared_ptr<Mediator> room) {
        chatRoom = room;
    }
    void send(const string& message) {
        if (auto room = chatRoom.lock()) {
            room->sendMessage(message, shared_from_this());
        } else {
            cout << name << " has no chat room to send message." << endl;
        }
    }
};

// ChatRoom 类实现
class ChatRoom : public Mediator, public enable_shared_from_this<ChatRoom> {
private:
    vector<shared_ptr<Colleague>> users; // 聊天室中的用户
    vector<string> messageHistory; // 消息历史记录
    mutable mutex mtx; // 线程同步，保护聊天室的状态
public:
    void addUser(const shared_ptr<Colleague>& user) {
        lock_guard<mutex> lock(mtx);  // 使用锁保护线程安全
        users.push_back(user);
        if (auto userPtr = dynamic_pointer_cast<User>(user)) {
        userPtr->setChatRoom(shared_from_this());
        }
    
    }

    void removeUser(const shared_ptr<Colleague>& user) {
        lock_guard<mutex> lock(mtx);  // 使用锁保护线程安全
        auto it = remove(users.begin(), users.end(), user);
        if (it != users.end()) {
            users.erase(it, users.end());
        }
        if (auto userPtr = dynamic_pointer_cast<User>(user)) {
        userPtr->setChatRoom(nullptr);  // 清除指向 chatRoom 的 weak_ptr
    }
    }

    void sendMessage(const string& message, const shared_ptr<Colleague>& sender) override {
        string filteredMessage = filterMessage(message);
        {
            lock_guard<mutex> lock(mtx);  // 使用锁保护消息历史记录
            messageHistory.push_back(filteredMessage); // 保存消息
        }
        std::cout << sender->getName() << " send the message" << filteredMessage << std::endl;
        for (const auto& user : users) {
            if (user != sender) {
                user->receiveMessage(filteredMessage);
            }
        }
    }

    string filterMessage(const string& message) {
        // 简单示例：替换敏感词
        string filtered = message;
        size_t pos = filtered.find("badword");
        if (pos != string::npos) {
            filtered.replace(pos, 7, "*****");
        }
        return filtered;
    }
};

// 测试案例
int main() {
    // 创建一个聊天室
    auto chatRoom = make_shared<ChatRoom>();

    // 创建用户
    auto user1 = make_shared<User>("Alice");
    auto user2 = make_shared<User>("Bob");
    auto user3 = make_shared<User>("Charlie");

    // 将用户添加到聊天室
    chatRoom->addUser(user1);
    chatRoom->addUser(user2);
    chatRoom->addUser(user3);

    // 发送消息
   
    chatRoom->sendMessage("Hello everyone!", user1);

    // 发送带有敏感词的消息
   
    chatRoom->sendMessage("This is a badword test message", user2);

    // 移除用户 Bob
   
    chatRoom->removeUser(user2);

    // 发送消息，Bob 不会接收到
    
    chatRoom->sendMessage("Goodbye Bob!", user3);

    std::cout << "____________________________________" << std::endl;

    user1->send("Hi, I'm Alice.");

    user2->send("This is a badword from Bob!");

    user3->send("Hey guys, I'm Charlie.");

    return 0;
}
