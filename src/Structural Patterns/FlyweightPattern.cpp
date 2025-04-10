#include <iostream>
#include <unordered_map>
#include <string>



/*

享元模式（Flyweight Pattern）主要用于减少创建对象的数量，以减少内存占用和提高性能。这种类型的设计模式属于结构型模式，它提供了减少对象数量从而改善应用所需的对象结构的方式。
    享元模式尝试重用现有的同类对象，如果未找到匹配的对象，则创建新对象。

    避免因创建大量对象而导致的内存溢出问题。
    通过共享对象，提高内存使用效率。

使用场景
    当系统中存在大量相似或相同的对象。
    对象的创建和销毁成本较高。
    对象的状态可以外部化，即对象的部分状态可以独立于对象本身存在。
    
*/










/*一个文字排版系统，每个字符都需要一个对象来表示，如果每个字符都独立存储，系统会消耗大量内存。
我们可以通过享元模式来共享相同的字符对象。*/



// 享元接口：字符接口
class Character {
public:
    virtual void display() = 0;  // 显示字符
    virtual ~Character() {}
};

// 具体享元类：字母字符
class ConcreteCharacter : public Character {
private:
    char character;  // 内部状态：字符

public:
    ConcreteCharacter(char c) : character(c) {}

    void display() override {
        std::cout << "Character: " << character << std::endl;
    }
};

// 享元工厂：用于管理享元对象的创建和共享
class CharacterFactory {
private:
    std::unordered_map<char, Character*> characterPool;

public:
    Character* getCharacter(char c) {
        // 如果池中存在这个字符对象，则直接返回
        if (characterPool.find(c) != characterPool.end()) {
            return characterPool[c];
        }

        // 否则创建新的字符对象并存入池中
        Character* character = new ConcreteCharacter(c);
        characterPool[c] = character;
        return character;
    }

    ~CharacterFactory() {
        for (auto& pair : characterPool) {
            delete pair.second;
        }
    }
};

// 客户端代码
int main() {
    CharacterFactory factory;

    // 获取字符对象，字符 "a" 和 "b" 将共享
    Character* charA1 = factory.getCharacter('a');
    Character* charA2 = factory.getCharacter('a');
    Character* charB = factory.getCharacter('b');

    // 显示字符对象
    charA1->display();
    charA2->display();
    charB->display();

    // 验证两个 "a" 字符是否是同一个对象
    if (charA1 == charA2) {
        std::cout << "Adress of A1 is " << charA1 <<"  and Adress of A2 is " << charA2 << std::endl;
        std::cout << "Adress of A1 is " << &charA1 <<"  and Adress of A2 is " << &charA2 << std::endl; //Different!
        std::cout << "'a' characters are the same instance!" << std::endl;
    /*&charA1 和 &charA2 是变量 charA1 和 charA2 本身的地址   charA1 和 charA2 是两个不同的指针变量（在栈上）  它们虽然**指向同一个对象**，但它们**自己不是同一个指针变量** */
    /*&charA1 是变量的地址（在栈上），charA1 是对象的地址*/
    }

    return 0;
}
