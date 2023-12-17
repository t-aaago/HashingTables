#ifndef ChainedHash
#include <string>
#include <bitset>
using std::bitset;

#include "IntLinkedList.cpp"
#include "StringLinkedList.cpp"
using std::string;


class ChainedHash
{
public:

    //-------------------------------- Métodos -----------------------------------
    ChainedHash(int);
    ~ChainedHash();

    //Métodos Hash para inteiros e strings
    int Hash(int);
    int Hash(string);

    //Método que converte string em inteiro para realizar o hashing
    int stringToInt(string);

    //Método para adicionar elementos na tabela
    void append(int);
    void append(string);

    //Método para remover elementos da tabela
    void remove(int);
    void remove(string);

    //Método para buscar elementos
    bool search(int);
    bool search(string);

    // Método para printar a tabela
    void print();

    //-------------------------------- Atributos -----------------------------------
    
    // Tamanho da tabela escolhida pelo usuário
    int intPositions; // tamanho da tabela de inteiros
    int stringPositions; // tamanho da tabela de strings
    
    // Quantidade de chaves em cada tabela
    int intKeysAmount;
    int stringKeysAmount;
    
    //Tabela de inteiros e strings
    StringLinkedList* estruturaString;
    IntLinkedList* estruturaInt;

};

//-------------------Construtor e Destrutor-------------------------------
ChainedHash::ChainedHash(int positions)
: intKeysAmount(0), stringKeysAmount(0), intPositions(positions), stringPositions(positions)
{

    estruturaString = new StringLinkedList[positions];
    estruturaInt = new IntLinkedList[positions];
}

ChainedHash::~ChainedHash()
{
    delete [] estruturaInt;
    delete [] estruturaString;
}

//-----------------------------------------------------------------------

int ChainedHash::Hash(int inteiro)
{
    int local = (inteiro % intPositions);
    return local; 
}
int ChainedHash::Hash(string word)
{
    int local = (stringToInt(word) % stringPositions);
    return local; 
}

//-----------------------------------------------------------------------

int ChainedHash::stringToInt(string word)
{   
    int aux;
    bitset<32> currentBitSet(word[word.length() - 1]);
    currentBitSet <<= 4;

    for (int i = word.length() - 2 ; i>=0; i--){
       bitset<32>currentWB(word[i]);

       aux = currentBitSet.to_ulong() + currentWB.to_ulong(); 
       bitset<32>auxBit(aux);
       currentBitSet = auxBit;
       if (i == 0){
        break;
       }
       currentBitSet <<= 4;         
    }
    /* cout << currentBitSet << endl;
    cout << currentBitSet.to_ulong() << endl; */
    int result = currentBitSet.to_ulong();
    result = abs(result);
    return result;
}

//-----------------------------------------------------------------------

void ChainedHash::append(int value){
    int position = Hash(value);
    estruturaInt[position].append(value);
    intKeysAmount++;
}

void ChainedHash::append(string value){
    int position = Hash(value);
    estruturaString[position].append(value);
    stringKeysAmount++;
}

//-----------------------------------------------------------------------

void ChainedHash::remove(int value){
    if(this->search(value)){
        int position = Hash(value);
        estruturaInt[position].removeValue(value);
        intKeysAmount--;
        cout << value << " removido" << endl;
        return;
    }
    cout << value << "nao esta na lista" << endl;
    
}


void ChainedHash::remove(string value){
    if (this->search(value)){
        int position = Hash(value);
        estruturaString[position].removeValue(value);
        stringKeysAmount--;
        cout << value << " removido" << endl;
        return;
    }
    cout << value << "nao esta na lista" << endl;
}

//-----------------------------------------------------------------------

bool ChainedHash::search(int value){
    int position = Hash(value);

    if (estruturaInt[position].SearchValue(value)){
        return true;
    };
    return false;
}

bool ChainedHash::search(string value){
    int position = Hash(value);
    if (estruturaString[position].SearchValue(value)){
        return true;
    };
    return false;
}

//-----------------------------------------------------------------------

void ChainedHash::print(){
    cout << "----Tabela Hash de inteiros----" << endl;
    for (int i = 0; i < intPositions; i++){
        cout << "Posicao " << i << ": ";
        estruturaInt[i].print();
    }

    cout << "----Tabela Hash de strings----" << endl;
    for (int i = 0; i < stringPositions; i++){
        cout << "Posicao " << i << ": ";
        estruturaString[i].print();
    }
}

#endif //ChainedHash