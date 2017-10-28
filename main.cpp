#include <iostream>
#include "bjack.h"

using std::cout;
using std::endl;

int main() {
    cout << "Please resize terminal to 128(l) * 22(h)" << endl;
    bjack bj;
    bj.run(128, 21);
}
