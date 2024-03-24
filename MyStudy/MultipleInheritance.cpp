#include "MultipleInheritance.h"
class top {
public:
    int value = 1;
};
class mid1 : public top {
public:
    int value =2;
    mid1() {
        value = 21;
    }
};
class mid2 : protected top {
public:
    int value=3;
    mid2() {
        value = 22;
    }
};
class bottom : public mid1, public mid2 {
public:
    int value = 4;
};
void MultipleInheritanceMain()
{
    bottom bot;
    std::cout << static_cast<mid1&>(bot).mid1::top::value << " 공통 상위 클래스 \n";
    //protected이므로 외부에서 접근불가
    //std::cout << bot.mid2::top::value1 << " 공통 상위 클래스 \n";
    std::cout << (&bot)->mid1::value << " 중간 클래스 \n";
    std::cout << bot.mid2::value << " 중간 클래스 \n";
    
    
    
    std::cout << bot.bottom::value << " 하위 클래스 \n";
}