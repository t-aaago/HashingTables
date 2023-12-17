#ifndef DOUBLEHASH_CPP

#include <string>
#include <bitset>
#include <chrono>
#include <iostream>

using namespace std;

struct IntElement
{
    int data = -100;
    int estado = -2; // 0 para ocupado, -1 para removido, -2 para livre
};

struct StrElement
{
    string data = "";
    int estado = -2; // 0 para ocupado, -1 para removido, -2 para livre
};

class DoubleHash
{
public:
    //-------------------------------- Métodos -----------------------------------
    DoubleHash(int positions);
    ~DoubleHash();

    //Métodos Hash para inteiros e strings
    int Hash(int);
    int Hash(string);

    int HashTwo(int); // segunda função de hashing para sondagem por hash duplo
    int HashTwo(string); // segunda função de hashing para sondagem por hash duplo

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

    //redimensionar
    void resizeInt();
    void resizeStr();

    //Verificação do próximmo número primo
    bool ehPrimo(int n);
    int proximoPrimo(int n);

    //-------------------------------- Atributos -----------------------------------
    int tablePositions; // Tamanho da tabela escolhida pelo usuário
    int intPositions; // tamanho da tabela de inteiros
    int stringPositions; // tamanho da tabela de strings

    // Quantidade de chaves em cada tabela
    int intKeysAmount;
    int stringKeysAmount;

    // Tabela de Inteiro e String
    struct IntElement* estruturaInt;
    struct StrElement* estruturaStr;
    

};

//------------------- Construtor e Destrutor -------------------------------
DoubleHash::DoubleHash(int positions)
    :tablePositions(positions), intPositions(positions), stringPositions(positions), 
    intKeysAmount(0), stringKeysAmount(0)
{
    estruturaInt = new IntElement[intPositions];
    estruturaStr = new StrElement[stringPositions];
}

DoubleHash::~DoubleHash()
{
    delete [] estruturaInt;
    delete [] estruturaStr;
}

//-----------------------------------------------------------------------

int DoubleHash::Hash(int inteiro)
{
    int local = (inteiro % intPositions);
    return local; 
}
int DoubleHash::Hash(string word)
{
    int local = (stringToInt(word) % stringPositions);
    return local; 
}

//     --------  Segundo Hashing ----------
int DoubleHash::HashTwo(int inteiro)
{
    int local = (inteiro % (intPositions-1)) + 1;
    return local; 
}
int DoubleHash::HashTwo(string word)
{
    int local = (stringToInt(word) % (stringPositions -1)) + 1;
    return local; 
}

//-----------------------------------------------------------------------

int DoubleHash::stringToInt(string word)
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

void DoubleHash::append(int value){
    auto inicio = chrono::steady_clock::now();
    int k = 0;
    int position = (Hash(value) + k*HashTwo(value)) % intPositions;
    int positionInsert = position;
    int colisao = 0;

        

    while (estruturaInt[position].estado == 0)
    {
        positionInsert = (Hash(value) + k*HashTwo(value)) % intPositions;

        if (estruturaInt[positionInsert].estado != 0){
            position = positionInsert;
        }
        colisao++;
        k++;
    }
    estruturaInt[position].data = value;
    estruturaInt[position].estado = 0;
    intKeysAmount++;

    auto final = chrono::steady_clock::now();
    auto intervalo = final - inicio;
    auto nano = chrono::duration_cast<chrono::nanoseconds>(intervalo).count();

    cout << value << " inserido" << endl;
    cout << "Colisoes: "<< colisao << endl;
    cout << "Tempo de execucao: " << nano << " nanossegundos"<< endl; 

    if(intKeysAmount > intPositions/2){
        this->resizeInt();
    }
}

void DoubleHash::append(string value){
    auto inicio = chrono::steady_clock::now();
    int k = 0;
    int position = (Hash(value) + k*HashTwo(value)) % stringPositions;
    int positionInsert = position;
    int colisao = 0;


    while (estruturaStr[position].estado == 0)
    {
        positionInsert = (Hash(value) + k*HashTwo(value)) % stringPositions;

        if (estruturaStr[positionInsert].estado != 0){
            position = positionInsert;
        }
        colisao++;
        k++;
    }
    estruturaStr[position].data = value;
    estruturaStr[position].estado = 0;
    stringKeysAmount++;
    
    auto final = chrono::steady_clock::now();
    auto intervalo = final - inicio;
    auto nano = chrono::duration_cast<chrono::nanoseconds>(intervalo).count();

    cout << value << " inserido" << endl;
    cout << "Colisoes: "<< colisao << endl;
    cout << "Tempo de execucao: " << nano << " nanossegundos"<< endl; 

    if(stringKeysAmount > stringPositions/2){
        this->resizeStr();
    }

}

//-----------------------------------------------------------------------

void DoubleHash::remove(int value){
    int k = 0;
    int position = (Hash(value) + k*HashTwo(value)) % intPositions;
    int positionRemove = position;
    bool found = false;

    while (estruturaInt[positionRemove].estado != -2)
    {
        if (estruturaInt[positionRemove].data == value){
            estruturaInt[positionRemove].estado = -1;
            found = true;
            intKeysAmount--;
            
            
            cout << "Elemento "<< value<< " Removido" << endl;
            break;
        } 

        positionRemove = (Hash(value) + k*HashTwo(value)) % intPositions;
        k++;

    }

    if (!found){
        cout << "Elemento "<< value <<" nao esta na tabela" << endl;
    }
}


void DoubleHash::remove(string value){
    int k = 0;
    int position = (Hash(value) + k*HashTwo(value)) % intPositions;
    int positionRemove = position;
    bool found = false;

    while (estruturaStr[positionRemove].estado != -2)
    {
        if (estruturaStr[positionRemove].data == value){
            estruturaStr[positionRemove].estado = -1;
            found = true;
            stringKeysAmount--;
            
            
            cout << "Elemento "<< value<< " Removido" << endl;
            break;
        } 

        positionRemove = (Hash(value) + k*HashTwo(value)) % intPositions;
        k++;

    }

    if (!found){
        cout << "Elemento "<< value <<" nao esta na tabela" << endl;
    }
}

//-----------------------------------------------------------------------

bool DoubleHash::search(int value){
    int k = 0;
    int position = (Hash(value) + k*HashTwo(value)) % intPositions;
    int positionFind = position;


    while (estruturaInt[positionFind].estado != -2)
    {
        if (estruturaInt[position].data == value && estruturaInt[position].estado != -1){
            return true;
        } 
        positionFind = (Hash(value) + k*HashTwo(value)) % intPositions;;
        k++;

    }
    return false;
}

bool DoubleHash::search(string value){
    int k = 0;
    int position = (Hash(value) + k*HashTwo(value)) % stringPositions;
    int positionFind = position;


    while (estruturaStr[positionFind].estado != -2)
    {
        if (estruturaStr[position].data == value && estruturaStr[position].estado != -1){
            return true;
        } 
        positionFind = (Hash(value) + k*HashTwo(value)) % stringPositions;
        k++;

    }
    return false;

}


//-----------------------------------------------------------------------

void DoubleHash::print(){

    cout << endl;
    cout << "-----------------------------------------------------"<< endl;
    cout << "Tabela Hash com sondagem por Hashing Duplo:" << endl;

    cout << "Tabela de Inteiros:" << endl;
    for (int i = 0; i < intPositions; i++){
        if(estruturaInt[i].estado == 0){
            cout << "Posicao " << i << ": " << estruturaInt[i].data << endl;  
        }
        else if (estruturaInt[i].estado == -1)
        {
           cout << "Posicao " << i << ": Removido" << endl;  
        }
        else if (estruturaInt[i].estado == -2)  
            cout << "Posicao " << i << ": Livre" << endl; 
        
    }

    cout << endl;

    cout << "Tabela de Strings: "<< endl;
    for (int i = 0; i < stringPositions; i++){
        if(estruturaStr[i].estado == 0){
            cout << "Posicao " << i << ": " << estruturaStr[i].data << endl;  
        } 
        else if (estruturaStr[i].estado == -1)
        {
           cout << "Posicao " << i << ": Removido" << endl;  
        }
        else if (estruturaStr[i].estado == -2)  
            cout << "Posicao " << i << ": Livre" << endl; 
    }
}

//-----------------------------------------------------------------------

void DoubleHash::resizeInt(){
    cout << "------- Redimensionando Tabela de Inteiros ----------" << endl;
    struct IntElement* oldEstruturaInt = estruturaInt;
    int oldIntPositions = intPositions;

    intPositions = proximoPrimo(intPositions);
    estruturaInt = new IntElement[intPositions];

    intKeysAmount = 0;

    for (int i = 0; i < oldIntPositions; i++){
        if (oldEstruturaInt[i].estado == 0){
            this->append(oldEstruturaInt[i].data);
        }
    }

    delete oldEstruturaInt;
}

void DoubleHash::resizeStr(){
    cout << "------- Redimensionando Tabela de strings ----------" << endl;
    struct StrElement* oldEstruturaStr = estruturaStr;
    int oldStrPositions = stringPositions;

    stringPositions = proximoPrimo(stringPositions);
    estruturaStr = new StrElement[stringPositions];

    stringKeysAmount = 0;

    for (int i = 0; i < oldStrPositions; i++){
        if (oldEstruturaStr[i].estado == 0){
            this->append(oldEstruturaStr[i].data);
        }
    }

    delete oldEstruturaStr;
}

//------------------------------------------------------------------------

bool DoubleHash::ehPrimo(int n) {
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

int DoubleHash::proximoPrimo(int n) {
  if (n <= 1) {
    return 2;
  }

  while (!ehPrimo(++n));
  return n;
}


#endif