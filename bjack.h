#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <termios.h>

using std::string;

class bjack {
public:
    char echoEnable();
    void run(int x, int y);
    void resetUI(int x, int y);

private:
    void print_simple(string out, int offset, char offset_filler);
    void print_simple(string out, int offset);
    void print_simple(string out);
    void print_card(string num, int cardNum);
    void print_card_small(std::string num, int cardNum);
    std::vector<int> cards;
    int total;
    int money;
    int pot;

    int dMoney;
    int dTotal;
};

