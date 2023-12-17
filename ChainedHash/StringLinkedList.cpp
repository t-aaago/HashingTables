#ifndef STRINGLINKEDLIST
#include <iostream>
#include "StrNode.cpp"

using std::cout;
using std::endl;

class StringLinkedList
{
public:
    StringLinkedList();
    ~StringLinkedList();

    void append(string);
    void removeValue(string);
    bool SearchValue(string);
    void print();

    StrNode* head;
    int lastColisionCount;
};

StringLinkedList::StringLinkedList(): head(nullptr)
{
}

StringLinkedList::~StringLinkedList()
{
    while (head != nullptr){
        StrNode *aux = head;
        head= head->next;
        delete aux;
    }
}

void StringLinkedList::append(string newValue){
    auto inicio = chrono::steady_clock::now();
    StrNode* newNode = new StrNode(newValue);
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
        StrNode* aux = head;
        lastColisionCount++;

        while (aux->next != nullptr)
        {
            lastColisionCount++;
            aux = aux->next;
        }
        aux->next = newNode;
        auto final = chrono::steady_clock::now();
        auto intervalo = final - inicio;
        auto nano = chrono::duration_cast<chrono::nanoseconds>(intervalo).count();
        

        cout << "Node com valor " << newValue << " inserido" << endl;
        cout << "Ocorreram: " << lastColisionCount << " no processo" <<endl;
        cout << "Tempo de execucao: " << nano << " nanossegundos"<< endl;
    }
}

void StringLinkedList::removeValue(string value){
    StrNode *aux;

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
            StrNode *temp;
            temp = aux->next;
            aux->next = aux->next->next;
            delete temp;
            temp = nullptr;
            return;
        }
        aux = aux->next;
    }
    
    
}

bool StringLinkedList::SearchValue(string value){
    StrNode *aux;

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


void StringLinkedList::print(){
    if (head == nullptr){
        cout << "Nullptr" << endl;
        return;
    }

    StrNode *aux = head;
    while (aux != nullptr)
    {
        cout << aux->data << " -> " ;
        aux = aux->next;
    }
    cout << "Nullptr";

    cout << endl;
}

#endif