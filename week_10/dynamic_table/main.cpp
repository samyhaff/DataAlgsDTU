#include <iostream>
#include "dynamic_table.h"

using namespace std;

int main() {
    char instruction;
    int x;
    DynamicTable table;

    while (cin >> instruction) {
        switch (instruction) {
            case 'I':
                cin >> x;
                table.insert(x);
            break;
            case 'D':
                table.pop();
            break;
            case 'P':
                table.print();
            break;
            case 'S':
                table.size();
            break;
        }
    }

    return 0;
}
