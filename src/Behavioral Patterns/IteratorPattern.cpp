#include <iostream>
#include <vector>
#include <memory>



/*
迭代器模式提供一种方法顺序访问一个聚合对象中的各个元素，而又不暴露其内部的表示。

迭代器模式属于行为型模式。


允许顺序访问一个聚合对象中的元素，同时不暴露对象的内部表示。

主要解决的问题
    提供一种统一的方法来遍历不同的聚合对象。
使用场景
    当需要遍历一个聚合对象，而又不希望暴露其内部结构时。
实现方式
    定义迭代器接口：包含hasNext()和next()等方法，用于遍历元素。
    创建具体迭代器：实现迭代器接口，定义如何遍历特定的聚合对象。
    聚合类：定义一个接口用于返回一个迭代器对象。

    Seek more  in STL Iterator !
*/




// 迭代器接口
class Iterator {
public:
    virtual bool hasNext() = 0;  // 判断是否有下一个元素
    virtual std::string next() = 0;  // 获取下一个元素
    virtual ~Iterator() = default;
};

// 具体迭代器：遍历书籍的集合
class ConcreteIterator : public Iterator {
private:
    std::vector<std::string> books;
    size_t index = 0;  // 当前索引位置
public:
    ConcreteIterator(const std::vector<std::string>& books) : books(books) {}

    bool hasNext() override {
        return index < books.size();
    }

    std::string next() override {
        return hasNext() ? books[index++] : "";
    }
};

// 集合接口
class Aggregate {
public:
    virtual std::shared_ptr<Iterator> createIterator() = 0;  // 创建迭代器
    virtual ~Aggregate() = default;
};

// 具体集合：书籍集合
class BookCollection : public Aggregate {
private:
    std::vector<std::string> books;
public:
    void addBook(const std::string& book) {
        books.push_back(book);
    }

    std::shared_ptr<Iterator> createIterator() override {
        return std::make_shared<ConcreteIterator>(books);
    }
};

// 客户端代码
int main() {
    BookCollection collection;
    collection.addBook("C++ Programming");
    collection.addBook("Design Patterns");
    collection.addBook("Data Structures");

    // 创建迭代器并遍历书籍
    std::shared_ptr<Iterator> iterator = collection.createIterator();
    while (iterator->hasNext()) {
        std::cout << iterator->next() << std::endl;
    }

    return 0;
}
