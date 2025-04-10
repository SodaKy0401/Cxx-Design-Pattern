#include <iostream>
#include <vector>
#include <string>


/*
过滤器模式（Filter Pattern）或标准模式（Criteria Pattern）是一种设计模式，这种模式允许开发人员使用不同的标准来过滤一组对象，通过逻辑运算以解耦的方式把它们连接起来。
这种类型的设计模式属于结构型模式，它结合多个标准来获得单一标准。

使用场景
    当对象集合需要根据不同的标准进行筛选时。
    当筛选逻辑可能变化，或者需要动态地组合多个筛选条件时。

实现方式
    定义筛选接口：创建一个筛选接口，定义一个筛选方法。
    实现具体筛选器：为每个筛选标准实现筛选接口，封装具体的筛选逻辑。
    组合筛选器：允许筛选器之间进行组合，形成复杂的筛选逻辑。


*/




// 1. Person 类
class Person {
public:
    std::string name;
    std::string gender;
    std::string maritalStatus;

    Person(std::string n, std::string g, std::string m) 
        : name(n), gender(g), maritalStatus(m) {}
};

// 2. Filter 接口
class Filter {
public:
    virtual std::vector<Person*> filter(std::vector<Person*>& persons) = 0;
};

// 3. 具体过滤器：根据性别过滤
class GenderFilter : public Filter {
public:
    std::string gender;

    GenderFilter(std::string g) : gender(g) {}

    std::vector<Person*> filter(std::vector<Person*>& persons) override {
        std::vector<Person*> filtered;
        for (auto& person : persons) {
            if (person->gender == gender) {
                filtered.push_back(person);
            }
        }
        return filtered;
    }
};

// 4. 具体过滤器：根据婚姻状况过滤
class MaritalStatusFilter : public Filter {
public:
    std::string maritalStatus;

    MaritalStatusFilter(std::string m) : maritalStatus(m) {}

    std::vector<Person*> filter(std::vector<Person*>& persons) override {
        std::vector<Person*> filtered;
        for (auto& person : persons) {
            if (person->maritalStatus == maritalStatus) {
                filtered.push_back(person);
            }
        }
        return filtered;
    }
};

// 5. 组合标准：与逻辑
class AndCriteria : public Filter {
private:
    Filter* filter1;
    Filter* filter2;

public:
    AndCriteria(Filter* f1, Filter* f2) : filter1(f1), filter2(f2) {}

    std::vector<Person*> filter(std::vector<Person*>& persons) override {
        std::vector<Person*> firstFilter = filter1->filter(persons);
        return filter2->filter(firstFilter);
    }
};

int main() {
    // 创建人员列表
    std::vector<Person*> persons = {
        new Person("John", "Male", "Single"),
        new Person("Jane", "Female", "Married"),
        new Person("Tom", "Male", "Married"),
        new Person("Lucy", "Female", "Single")
    };

    // 过滤器：性别为"Male"的人员
    GenderFilter maleFilter("Male");
    std::vector<Person*> malePersons = maleFilter.filter(persons);
    
    std::cout << "Male Persons: " << std::endl;
    for (auto& person : malePersons) {
        std::cout << person->name << " " << person->gender << " " << person->maritalStatus << std::endl;
    }

    // 过滤器：婚姻状况为"Single"的人员
    MaritalStatusFilter singleFilter("Single");
    std::vector<Person*> singlePersons = singleFilter.filter(persons);

    std::cout << "\nSingle Persons: " << std::endl;
    for (auto& person : singlePersons) {
        std::cout << person->name << " " << person->gender << " " << person->maritalStatus << std::endl;
    }

    // 组合过滤器：性别为"Male"并且婚姻状况为"Single"的人员
    AndCriteria maleAndSingleFilter(&maleFilter, &singleFilter);
    std::vector<Person*> maleAndSinglePersons = maleAndSingleFilter.filter(persons);

    std::cout << "\nMale and Single Persons: " << std::endl;
    for (auto& person : maleAndSinglePersons) {
        std::cout << person->name << " " << person->gender << " " << person->maritalStatus << std::endl;
    }

    // 清理内存
    for (auto& person : persons) {
        delete person;
    }

    return 0;
}
