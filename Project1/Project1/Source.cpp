#include <iostream>
#include <string>
#include "Container.h"
class Object {
public:
    Object() { count++; }
    virtual std::string toString() const = 0;
    ~Object() { count--; }
    static inline unsigned count{};

};

class Task : virtual public Object {
public:
    Task() { }
    std::string toString() const;
    int Isresult{};
    ~Task() {}
};

std::string Task::toString() const {
    return "it task\n";
}

class Named : virtual public Object {
public:
    Named() { }
    std::string toString() const;
    std::string name;
    ~Named() {}
};
std::string Named::toString() const {
    return "it named\n";
}
class Task1 : public Named, public Task {
public:
    Task1(float first_, float second_, char op) { Isresult = 1; name = "bin oper"; first = first_, second = second_, operation = op; }
    std::string toString() const;
    ~Task1() {}
private:
    float first;
    float second;
    char operation;
};
std::string Task1::toString() const {
    float result;
    if (operation == '+') {
        result = first + second;
        return std::to_string(first) + "+" + std::to_string(second) + "=" + std::to_string(result) + "\n";
    }
    if (operation == '*') {
        result = first * second;
        return std::to_string(first) + "*" + std::to_string(second) + "=" + std::to_string(result) + "\n";
    }
    if (operation == '-') {
        result = first - second;
        return std::to_string(first) + "-" + std::to_string(second) + "=" + std::to_string(result) + "\n";
    }
    if (operation == '/') {
        if (second != 0) {
            result = first / second;
            return std::to_string(first) + "/" + std::to_string(second) + "=" + std::to_string(result) + "\n";
        }
        else
            return "try to devide by 0\n";
    }
    return "use wrong operation\n";
}

class Task2 : public Named, public Task {//+
public:
    Task2(Container<Task*>* a_, Task* t_) { Isresult = 0; name = "add task"; cont = a_, task = t_; }
    std::string toString() const override;
    ~Task2() { }
private:
    Container<Task*>* cont;
    Task* task;
};
std::string Task2::toString() const {
    cont->AddFirst(task);
    return "Task was add\n";
}


class Task3 :public Named, public Task {//+
public:

    Task3() { Isresult = 1; name = "count of obj"; }
    std::string toString() const;
    ~Task3() { }
};
std::string Task3::toString() const {
    return "count obj=" + std::to_string(count) + "\n";
}

class Task4 : public Named, public Task {//+
public:
    Task4(Container<Task*>* a_) { Isresult = 1; cont = a_; name = "count obj in cont"; }
    std::string toString() const;
    ~Task4() {  }
private:
    Container<Task*>* cont;
};
std::string Task4::toString() const {
    return "count obj in cont=" + std::to_string(cont->GiveCount()) + "\n";;
}

class Task5 : public Named, public Task {//-
public:
    Task5(Container<Task*>* a_) { cont = a_; Isresult = 1; name = "count of result task"; }
    std::string toString() const;
    ~Task5() { }
private:
    Container<Task*>* cont;
};
std::string Task5::toString() const {

    return "it task5\n";
}

class Task6 : public Task {
public:
    Task6(Container<Task*>* a_) { Isresult = 0; cont = a_; }//+
    std::string toString() const;
    ~Task6() { }
private:
    Container<Task*>* cont;
};
std::string Task6::toString() const {
    cont->~Container();
    return "container is empty\n";
}

int main() {
    Container<Task*> newcont;
    Task1 a1(2, 3, '+');
    Task1 a2(4, 3, '*');
    Task3 b;
    Task1 a3(8, 3, '-');
    Task1 a4(6, 3, '/');
    std::cout << b.toString();
    Container<std::string> p;
    newcont.AddFirst(&a1);
    newcont.AddFirst(&a2);
    newcont.AddFirst(&a3);
    newcont.AddFirst(&a4);
    newcont.AddFirst(&b);
    while (newcont.GiveCount() != 0) {
        p.AddFirst(newcont.GiveFirst()->toString());
        newcont.GiveFirst()->~Task();
        newcont.DeleteFirst();
    }
    while (p.GiveCount() != 0) {
        std::cout << p.GiveFirst();
        p.DeleteFirst();
    }
    Task b1;
    if (b1.count == 1) {
        b1.~Task();
        std::cout << "zero obj";

    }
    return 0;
}