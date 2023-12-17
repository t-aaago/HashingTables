#ifndef INTLINKEDLIST
#include <iostream>
#include <chrono>
#include "IntNode.cpp"

using namespace std;

class IntLinkedList
{
public:
    IntLinkedList();
    ~IntLinkedList();

    void append(int);
    void removeValue(int);
    bool SearchValue(int);
    void print();

    IntNode* head;
    int lastColisionCount = 0;
};

IntLinkedList::IntLinkedList(): head(nullptr)
{
}

IntLinkedList::~IntLinkedList()
{
    IntNode *aux = head;
    while (head != nullptr){
        head= head->next;
        delete aux;
        aux = nullptr;
    }
}

void IntLinkedList::append(int newValue){
    auto inicio = chrono::steady_clock::now();
    IntNode* newNode = new IntNode(newValue);
    lastColisionCount = 0;
    

    if(head == nullptr){
        head = newNode;

        auto final = chrono::steady_clock::now();
        auto intervalo = final - inicio;
        auto nano = chrono::duration_cast<chrono::nanoseconds>(intervalo).count();
        
        cout << "Node com valor " << newValue << " inserido" << endl;
        cout << "Tempo de execucao: " << nano<< " nanosegundos"<< endl;
        return;
    } else {
        IntNode* aux = head;
        lastColisionCount++;

        while (aux->next != nullptr)
        {
            aux = aux->next;
            lastColisionCount++;
        }
        aux->next = newNode;

        auto final = chrono::steady_clock::now();
        auto intervalo = chrono::duration_cast<chrono::nanoseconds>(final - inicio);
        auto nano = intervalo.count();
        

        cout << "Node com valor " << newValue << " inserido" << endl;
        cout << "Ocorreram: " << lastColisionCount << " colisoes no processo" <<endl;
        cout << "Tempo de execucao: " << nano << " nanossegundos"<< endl;
    }
}

void IntLinkedList::removeValue(int value){
    IntNode *aux;

    //Caso da lista estar vazia
    if (head == nullptr){
        cout << "Lista vazia" << endl;
        return;
    }
    //Caso o head seja o valor a ser excluido
    else if (head->data == value)
    {
        
        //caso o head tenha filhos
        if (head->next != nullptr){
            aux = head;
            head = head->next;
            delete aux;
            return;
        }
        //caso head não tenha filhos
        delete head;
        head = nullptr;
        return;
    }
    
    //Caso valor a ser excluído esteja no meio ou no final
    aux = head;

    while (aux != nullptr)
    {
        if (aux->next->data == value){
            IntNode *temp;
            temp = aux->next;
            aux->next = aux->next->next;
            delete temp;
            temp = nullptr;
            return;
        }
        aux = aux->next;
    }
    
    
}

 bool IntLinkedList::SearchValue(int value){
    IntNode *aux;

    //Caso da lista estar vazia
    if (head == nullptr){
        return false;
    }

    aux = head;
    while (aux != nullptr)
    {
        if (aux->data == value){
            cout << "Valor encontrado" << endl;
            return true;
        }
        aux = aux->next;
    }
    cout << "Valor não encontrado" << endl;
    return false;
    
    
}


void IntLinkedList::print(){
    if (head == nullptr){
        cout << "Nullptr" << endl;
        return;
    }

    IntNode *aux = head;
    while (aux != nullptr)
    {
        cout << aux->data << " -> " ;
        aux = aux->next;
    }
    cout << "Nullptr";

    cout << endl;
}

#endif