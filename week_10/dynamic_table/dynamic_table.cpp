#include <iostream>
#include "dynamic_table.h"

using namespace std;

DynamicTable::DynamicTable() {
    actual_size = 0;
    allocated_size = 1;
    array = (int *) malloc(sizeof(int));
}

DynamicTable::~DynamicTable() {
    free(array);
}

void DynamicTable::insert(int x) {
    if (actual_size == allocated_size) {
        allocated_size *= 2;
        array = (int *) realloc(array, sizeof(int) * allocated_size);
    }
    array[actual_size++] = x;
}

void DynamicTable::pop() {
    if (actual_size > 0) {
        actual_size--;
        if (actual_size <= allocated_size / 4 && allocated_size > 1) {
            allocated_size /= 2;
            array = (int *) realloc(array, sizeof(int) * allocated_size);
        }
    }
}

void DynamicTable::print() {
    for (int i = 0; i < actual_size; i++)
        cout << array[i] << " ";
    cout << endl;
}

void DynamicTable::size() {
    cout << actual_size << " " << allocated_size << endl;;
}
