#include <iostream>
#include <bitset>
using namespace std;

int main(){
    bitset<32> a(0uL);
    bitset<32> mask(0uL);
    mask.set(31);
    mask.flip();

    for (int i = 11; i < 15; i++) a.set(i);

    if ((a&mask).any()) cout << "masked" << endl;

    cout << mask << endl;
    cout << a << endl;
    cout << (a&mask) << endl;
}