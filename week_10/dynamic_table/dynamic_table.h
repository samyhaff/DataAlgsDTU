#pragma once

class DynamicTable {
private:
    int *array;
    int actual_size;
    int allocated_size;
public:
    DynamicTable();
    ~DynamicTable();
    void insert(int x);
    void pop();
    void print();
    void size();
};
