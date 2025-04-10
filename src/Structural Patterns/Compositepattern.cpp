#include <iostream>
#include <vector>
#include <string>


/*
组合模式（Composite Pattern），又叫部分整体模式，是用于把一组相似的对象当作一个单一的对象。
    组合模式依据树形结构来组合对象，用来表示部分以及整体层次。这种类型的设计模式属于结构型模式，它创建了对象组的树形结构。
    
    需要表现部分-整体层次结构的系统（例如树、目录、组织结构）!
    希望用户统一处理单个对象和对象集合!
    
组合模式通常包含以下几个角色：

    Component（组件）：定义所有对象的公共接口（包括叶子对象和组合对象）。

    Leaf（叶子对象）：表示组成部分中的基本元素，叶子对象没有子对象。

    Composite（组合对象）：包含叶子对象或其他组合对象的子对象，并实现与子对象的操作接口。
*/






// 1. Component（组件）类
class Employee {
public:
    virtual void showDetails() = 0;  // 展示员工/部门信息
    virtual ~Employee() {}
};

// 2. Leaf（叶子节点）类：员工
class Developer : public Employee {
private:
    std::string name;
    std::string position;

public:
    Developer(std::string n, std::string p) : name(n), position(p) {}

    void showDetails() override {
        std::cout << "Developer: " << name << " - " << position << std::endl;
    }
};

class Manager : public Employee {
private:
    std::string name;
    std::string position;

public:
    Manager(std::string n, std::string p) : name(n), position(p) {}

    void showDetails() override {
        std::cout << "Manager: " << name << " - " << position << std::endl;
    }
};

// 3. Composite（组合节点）类：部门
class Department : public Employee {
private:
    std::string name;
    std::vector<Employee*> employees;

public:
    Department(std::string n) : name(n) {}

    void addEmployee(Employee* employee) {
        employees.push_back(employee);
    }

    void showDetails() override {
        std::cout << "Department: " << name << std::endl;
        for (auto& employee : employees) {
            employee->showDetails();
        }
    }

    ~Department() {
        // 删除所有子员工对象
        for (auto& employee : employees) {
            delete employee;
        }
    }
};

// 客户端代码
int main() {
    // 创建叶子节点（员工）
    Developer* dev1 = new Developer("John", "C++ Developer");
    Developer* dev2 = new Developer("Alice", "Python Developer");
    Manager* manager1 = new Manager("Bob", "Project Manager");

    // 创建组合节点（部门）
    Department* devDept = new Department("Development Department");
    devDept->addEmployee(dev1);
    devDept->addEmployee(dev2);

    Department* managerDept = new Department("Management Department");
    managerDept->addEmployee(manager1);

    // 创建公司并显示结构
    Department* company = new Department("Company");
    company->addEmployee(devDept);
    company->addEmployee(managerDept);

    // 展示公司的全部信息
    company->showDetails();

    // 清理内存
    delete company;

    return 0;
}
