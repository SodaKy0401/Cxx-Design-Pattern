#include <iostream>
#include <memory>

#include <unordered_map>
#include <functional>



// 抽象产品类
class Shape {
public:
    virtual void draw() = 0;  // 纯虚函数，所有形状类需要实现
    virtual ~Shape() = default;
};
// 具体产品类：圆形
class Circle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing Circle" << std::endl;
    }
};
// 具体产品类：矩形
class Rectangle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing Rectangle" << std::endl;
    }
};

// 简单工厂类
class ShapeFactory {
public:
    // 根据类型返回不同的图形对象
    static std::unique_ptr<Shape> createShape(const std::string& shapeType) {
        if (shapeType == "circle") {
            return std::make_unique<Circle>();
        } else if (shapeType == "rectangle") {
            return std::make_unique<Rectangle>();
        }
        return nullptr;  // 如果类型不匹配，返回空
    }
};

//枚举工厂类
enum class ShapeType {
  Circle,
  Rectangle
};

class enumShapeFactory {
public:
    static std::unique_ptr<Shape> createShape(ShapeType type) {
        switch (type) {
            case ShapeType::Circle: return std::make_unique<Circle>();
            case ShapeType::Rectangle: return std::make_unique<Rectangle>();
            default: return nullptr;
        }
    }
};


//反射式工厂
class ReflectionShapeFactory {
public:
     using Creator = std::function<std::unique_ptr<Shape>()>;

    // 单例模式：确保工厂的唯一性
    static ReflectionShapeFactory& instance() {
        static ReflectionShapeFactory factory;
        return factory;
    }

    // 注册函数
    static void registerShape(const std::string& name, Creator creator) {
        instance().creators[name] = std::move(creator);
    }

    // 根据名称创建对象
    std::unique_ptr<Shape> createShape(const std::string& name) {
        auto it = creators.find(name);
        if (it != creators.end()) {
            return (it->second)();
        }
        return nullptr;
    }

private:
    // 存储类型名称和创建函数的映射
    std::unordered_map<std::string, Creator> creators;
};


#define REGISTER_SHAPE(NAME, CLASS) \
    static bool registered_##CLASS = []() { \
        ReflectionShapeFactory::registerShape(NAME, []() { return std::make_unique<CLASS>(); }); \
        return true; \
    }();


REGISTER_SHAPE("circle", Circle)
REGISTER_SHAPE("rectangle", Rectangle)




int main() {
    // 使用工厂创建不同的形状
    auto shape1 = ShapeFactory::createShape("circle");
    shape1->draw();

    auto shape2 = ShapeFactory::createShape("rectangle");
    shape2->draw();
    auto shape3 = enumShapeFactory::createShape(ShapeType::Circle);
    shape3->draw();
    
  

    // 使用反射式工厂创建形状
     auto shape4 = ReflectionShapeFactory::instance().createShape("circle");
    if (shape4) {
        shape4->draw();
    } else {
        std::cout << "Shape 'circle' not found!" << std::endl;
    }

}
