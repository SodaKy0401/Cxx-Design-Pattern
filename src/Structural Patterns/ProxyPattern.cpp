#include <iostream>
#include <string>

/*
代理模式

在代理模式（Proxy Pattern）中，一个类代表另一个类的功能，这种类型的设计模式属于结构型模式。

    代理模式通过引入一个代理对象来控制对原对象的访问。代理对象在客户端和目标对象之间充当中介，负责将客户端的请求转发给目标对象，同时可以在转发请求前后进行额外的处理。

    在代理模式中，我们创建具有现有对象的对象，以便向外界提供功能接口。

使用场景:当需要在访问一个对象时进行一些控制或额外处理时。


实现方式
    增加中间层：创建一个代理类，作为真实对象的中间层。
    代理与真实对象组合：代理类持有真实对象的引用，并在访问时进行控制。
关键代码
    代理类：实现与真实对象相同的接口，并添加额外的控制逻辑。
    真实对象：实际执行任务的对象。

*/



// 抽象主题角色：网页接口
class WebPage {
public:
    virtual void request() = 0;  // 获取网页内容
    virtual ~WebPage() {}
};

// 真实主题角色：具体网页
class RealWebPage : public WebPage {
private:
    std::string url;

public:
    RealWebPage(const std::string& url) : url(url) {}

    void request() override {
        std::cout << "Loading web page: " << url << std::endl;
    }
};

// 代理角色：网页代理
class WebPageProxy : public WebPage {
private:
    RealWebPage* realWebPage;  // 持有真实网页对象
    std::string url;
public:
    WebPageProxy(const std::string& url) : url(url), realWebPage(nullptr) {}
    // 延迟加载真实网页对象
    void request() override {
        if (realWebPage == nullptr) {
            // 如果还没有真实对象，则创建它
            realWebPage = new RealWebPage(url);
        }
        // 记录日志
        std::cout << "Logging: Accessing web page: " << url << std::endl;
        // 使用真实网页对象来处理请求
        realWebPage->request();
    }
    ~WebPageProxy() {
        delete realWebPage;  // 清理内存
    }
};

int main() {
    // 使用代理对象来访问网页
    WebPage* webPage1 = new WebPageProxy("https://example.com");
    WebPage* webPage2 = new WebPageProxy("https://anotherexample.com");

    // 代理将会延迟加载真实对象并记录日志
    webPage1->request();
    webPage2->request();

    delete webPage1;
    delete webPage2;

    return 0;
}
