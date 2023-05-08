#include <iostream>
#include <string>

template <class T>
class Container {
public:
    struct Node {
        T value{};
        Node* next;
        Node* prev;
        Node() { next = prev = NULL; }
    };
    
private:    
    Node* Head;
    Node* Tail;
    int count;
public:
    Node begin() { return Head; }
    Node end() { return Tail->next; }
    Container();
    void AddFirst(T value);
    void AddLast(T value);
    void DeleteFirst();
    void DeleteLast();
    T GiveFirst();
    T GiveLast();
    int GiveCount();    
    void SwapCont(Container* second);
    void Swap();
    void Detour();
    ~Container();
};



template <class T> Container<T>::Container() {
    count = 0;
    Head = Tail = NULL;
}

template <class T> void Container<T>::AddFirst(T value) {
    Node* cur = new Node;                                     
    cur->value = value;  
    count++;
    if (Head == NULL)                    
    {
        cur->next = NULL;
        cur->prev = NULL;
        Head = Tail = cur;
                            
    }
    else 
    {
        Head->prev = cur;
        cur->next = Head;  
        Head = cur;
        Head->prev = NULL;
    }
}
template <class T> void Container<T>::AddLast(T value) {
    Node* cur = new Node;   
    cur->value = value;
    this->count++;
    if (Head == NULL)
    {
        cur->next = NULL;
        cur->prev = NULL;
        Head = Tail = cur;

    }
    else
    {
        cur->prev = Tail;
        Tail->next = cur;
        Tail = cur;
        Tail->next = NULL;
    }
}
template <class T> void Container<T>::DeleteFirst() {
    if (count != 0) {
        if (count == 1) {
            Tail=Head = NULL;
            delete Head;
            count--;
            return;
        }
        Node* cur = Head;
        Head = Head->next;
        Head->prev = NULL;
        count--;
        delete cur;
        return;
    }
    throw "Zero elements!";
}
template <class T> void Container<T>::DeleteLast() {
    if (count != 0) {
        if (count == 1) {
            Tail=Head = NULL;
            delete Head;
            count--;
            return;
        }
        Node* cur = Tail;
        Tail = Tail->prev;
        Tail->next = NULL;
        count--;
        delete cur;
        return;
    }  
    throw "Zero elements!";
}
template <class T> T Container<T>::GiveFirst() {
    if(Head!=NULL)
    return this->Head->value;
    throw "Zero elements!";
}
template <class T> T Container<T>::GiveLast() {
    if(Tail!=NULL)
    return this->Tail->value;
    throw "Zero elements!";
}
template <class T> int Container<T>::GiveCount() {
    return count;
}
template <class T> Container<T>::~Container() {
    while (count != 0) {
        DeleteFirst();
    }
}
template <class T> void Container<T>::SwapCont(Container* second) {
    int val = count;
    count = second->count;
    second->count = val;
    Node* cur = Head;
    Head = second->Head;
    second->Head = cur;
    cur = Tail;
    Tail = second->Tail;
    second->Tail = cur;
}
template <class T> void Container<T>::Swap() {
    if (Head != NULL) {
        Node* cur = Head;
        Node* neew = cur->prev;
        for (int i = 0; i < count; i++) {
            neew = cur->prev;
            cur->prev = cur->next;
            cur->next = neew;
            cur = cur->prev;
        }
        cur = Head;
        Head = Tail;
        Tail = cur;
    }
}
template <class T> void Container<T>::Detour() {
    Node* cur = Head;
    for (int i = 0; i < count; i++) {
        std::cout << cur->value<<std::endl;
        cur = cur->next;
    }
}
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
    ~Task(){}
};

std::string Task::toString() const {
    return "it task\n";
}

class Named : virtual public Object {
public:
    Named() { }
    std::string toString() const;
    std::string name;
    ~Named(){}
}; 
std::string Named::toString() const {
    return "it named\n";
}
class Task1 : public Named, public Task {
public:
    Task1(float first_, float second_, char op) { Isresult = 1; name = "bin oper"; first = first_, second = second_, operation = op; }
    std::string toString() const ;
    ~Task1() {}
private:
    float first;
    float second;
    char operation;
};
std::string Task1::toString() const  {
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
            return std::to_string(first) + "/" + std::to_string(second) + "=" + std::to_string(result)+"\n";
        }
        else
            return "try to devide by 0\n";
    }
    return "use wrong operation\n";
}

class Task2 : public Named, public Task {//+
public:
    Task2(Container<Task*>* a_, Task* t_) { Isresult = 0; name = "add task"; cont = a_, task =t_; }
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
    return "count obj in cont="+ std::to_string(cont->GiveCount()) + "\n";;
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
    ~Task6(){ }
private:
    Container<Task*>* cont;
};
std::string Task6::toString() const {
    cont->~Container();
    return "container is empty\n";
}

int main() {
    Container<Task*> newcont;
    Task1 a1(2, 3, '+' );
    Task1 a2(4, 3, '*');
    Task3 b;
    std::cout << b.toString();
    Container<std::string> p;
    newcont.AddFirst(&a1);
    newcont.AddFirst(&a2);
    newcont.AddFirst(&b);
    while (newcont.GiveCount()!=0) {
        p.AddFirst( newcont.GiveFirst()->toString());
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