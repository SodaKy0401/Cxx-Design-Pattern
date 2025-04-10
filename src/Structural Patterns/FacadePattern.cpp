#include <iostream>
#include <string>

// 子系统 1: 投影仪
class Projector {
public:
    void on() {
        std::cout << "Projector is on.\n";
    }

    void off() {
        std::cout << "Projector is off.\n";
    }

    void wideScreenMode() {
        std::cout << "Projector is in widescreen mode.\n";
    }
};

// 子系统 2: DVD 播放器
class DvdPlayer {
public:
    void on() {
        std::cout << "DVD Player is on.\n";
    }

    void off() {
        std::cout << "DVD Player is off.\n";
    }

    void play() {
        std::cout << "DVD Player is playing movie.\n";
    }

    void stop() {
        std::cout << "DVD Player stopped.\n";
    }
};

// 子系统 3: 音响系统
class SoundSystem {
public:
    void on() {
        std::cout << "Sound System is on.\n";
    }

    void off() {
        std::cout << "Sound System is off.\n";
    }

    void setVolume(int level) {
        std::cout << "Sound System volume set to " << level << ".\n";
    }
};

// 子系统 4: 灯光系统
class Lights {
public:
    void dim() {
        std::cout << "Lights are dimmed.\n";
    }

    void brighten() {
        std::cout << "Lights are brightened.\n";
    }
};

// 外观类：家庭影院
class HomeTheaterFacade {
private:
    Projector* projector;
    DvdPlayer* dvdPlayer;
    SoundSystem* soundSystem;
    Lights* lights;

public:
    HomeTheaterFacade(Projector* p, DvdPlayer* d, SoundSystem* s, Lights* l)
        : projector(p), dvdPlayer(d), soundSystem(s), lights(l) {}

    void watchMovie() {
        std::cout << "Get ready to watch a movie...\n";
        lights->dim();
        projector->on();
        projector->wideScreenMode();
        soundSystem->on();
        soundSystem->setVolume(10);
        dvdPlayer->on();
        dvdPlayer->play();
    }

    void endMovie() {
        std::cout << "Shutting down...\n";
        dvdPlayer->stop();
        dvdPlayer->off();
        soundSystem->off();
        projector->off();
        lights->brighten();
    }
};

// 客户端代码
int main() {
    // 创建子系统对象
    Projector projector;
    DvdPlayer dvdPlayer;
    SoundSystem soundSystem;
    Lights lights;

    // 创建外观类对象
    HomeTheaterFacade homeTheater(&projector, &dvdPlayer, &soundSystem, &lights);

    // 客户端通过外观类调用复杂的子系统功能
    homeTheater.watchMovie();
    std::cout << "\n";
    homeTheater.endMovie();

    return 0;
}
