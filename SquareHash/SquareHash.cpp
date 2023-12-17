#ifndef SQUAREHASH_CPP

#include <string>
#include <bitset>
#include <iostream>
#include <chrono>

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

class SquareHash
{
public:
    //-------------------------------- Métodos -----------------------------------
    SquareHash(int positions);
    ~SquareHash();

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
SquareHash::SquareHash(int positions)
    :tablePositions(positions), intPositions(positions), stringPositions(positions), 
    intKeysAmount(0), stringKeysAmount(0)
{
    estruturaInt = new IntElement[intPositions];
    estruturaStr = new StrElement[stringPositions];
}

SquareHash::~SquareHash()
{
    delete [] estruturaInt;
    delete [] estruturaStr;
}

//-----------------------------------------------------------------------

int SquareHash::Hash(int inteiro)
{
    int local = (inteiro % intPositions);
    return local; 
}
int SquareHash::Hash(string word)
{
    int local = (stringToInt(word) % stringPositions);
    return local; 
}

//-----------------------------------------------------------------------

int SquareHash::stringToInt(string word)
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

void SquareHash::append(int value){
    auto inicio = chrono::steady_clock::now();
    int position = Hash(value);
    int positionInsert = position;
    int k = 0;
    int colisao = 0;

    while (estruturaInt[position].estado == 0)
    {
        positionInsert = (position+k*k) % intPositions;

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

void SquareHash::append(string value){
    auto inicio = chrono::steady_clock::now();
    int position = Hash(value);
    int positionInsert = position;
    int colisao = 0;
    int k = 0;


    while (estruturaStr[position].estado == 0)
    {
        positionInsert = (position+k*k) % stringPositions;

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
    long long nano = chrono::duration_cast<chrono::nanoseconds>(intervalo).count();

    cout << value << " inserido" << endl;
    cout << "Colisoes: "<< colisao << endl;
    cout << "Tempo de execucao: " << nano << " nanossegundos"<< endl; 
    

    if(stringKeysAmount > stringPositions/2){
        this->resizeStr();
    }

}

//-----------------------------------------------------------------------

void SquareHash::remove(int value){
    int position = Hash(value);
    int positionRemove = position;
    int k = 0;
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

        positionRemove = (position+k*k) % intPositions;
        k++;

    }

    if (!found){
        cout << "Elemento "<< value <<" nao esta na tabela" << endl;
    }
}


void SquareHash::remove(string value){
    int position = Hash(value);
    int positionRemove = position;
    int k = 0;
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

        positionRemove = (position+k*k) % intPositions;
        k++;

    }

    if (!found){
        cout << "Elemento "<< value <<" nao esta na tabela" << endl;
    }
}

//-----------------------------------------------------------------------

bool SquareHash::search(int value){
    int position = Hash(value);
    int positionRemove = position;
    int k = 0;


    while (estruturaInt[positionRemove].estado != -2)
    {
        if (estruturaInt[position].data == value && estruturaInt[position].estado != -1){
            return true;
        } 
        positionRemove = (position+k*k) % intPositions;
        k++;

    }
    return false;
}

bool SquareHash::search(string value){
   int position = Hash(value);
    int positionRemove = position;
    int k = 0;


    while (estruturaStr[positionRemove].estado != -2)
    {
        if (estruturaStr[position].data == value && estruturaStr[position].estado != -1){
            return true;
        } 
        positionRemove = (position+k*k) % intPositions;
        k++;

    }
    return false;

}


//-----------------------------------------------------------------------

void SquareHash::print(){

    cout << endl;
    cout << "-----------------------------------------------------"<< endl;
    cout << "Tabela Hash com sondagem Square:" << endl;

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

void SquareHash::resizeInt(){
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

void SquareHash::resizeStr(){
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

bool SquareHash::ehPrimo(int n) {
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

int SquareHash::proximoPrimo(int n) {
  if (n <= 1) {
    return 2;
  }

  while (!ehPrimo(++n));
  return n;
}


#endif