#ifndef LINEARHASH_CPP

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

class LinearHash
{
public:
    //-------------------------------- Métodos -----------------------------------
    LinearHash(int positions);
    ~LinearHash();

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
LinearHash::LinearHash(int positions)
    :tablePositions(positions), intPositions(positions), stringPositions(positions), 
    intKeysAmount(0), stringKeysAmount(0)
{
    estruturaInt = new IntElement[intPositions];
    estruturaStr = new StrElement[stringPositions];
}

LinearHash::~LinearHash()
{
    delete [] estruturaInt;
    delete [] estruturaStr;
}

//-----------------------------------------------------------------------

int LinearHash::Hash(int inteiro)
{
    int local = (inteiro % intPositions);
    return local; 
}
int LinearHash::Hash(string word)
{
    int local = (stringToInt(word) % stringPositions);
    return local; 
}

//-----------------------------------------------------------------------

int LinearHash::stringToInt(string word)
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

void LinearHash::append(int value){
    auto inicio = chrono::steady_clock::now();
    int position = Hash(value);
    int colisao = 0;


    while (estruturaInt[position].estado == 0)
    {
        position = (position+1) % intPositions;
        colisao++;
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

void LinearHash::append(string value){
    auto inicio = chrono::steady_clock::now();
    int position = Hash(value);
    int colisao = 0;


    while (estruturaStr[position].estado == 0)
    {
        position = (position+1) % stringPositions;
        colisao++;
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

void LinearHash::remove(int value){
    int position = Hash(value);
    int initialPosition = position;
    bool found = false;
    while (estruturaInt[position].estado != -2)
    {
        if (estruturaInt[position].data == value){
            estruturaInt[position].estado = -1;
            found = true;
            intKeysAmount--;
            

            cout << "Elemento "<< value<< " Removido" << endl;
            break;
        } 
        position = (position+1) % intPositions;
        if (position == initialPosition){
            break;
        }
    }

    if (!found){
        cout << "Elemento "<< value <<" nao esta na tabela" << endl;
    }
}


void LinearHash::remove(string value){
    int position = Hash(value);
    int initialPosition = position;
    bool found = false;
    while (estruturaStr[position].estado != -2)
    {
        if (estruturaStr[position].data == value){
            estruturaStr[position].estado = -1;
            found = true;
            stringKeysAmount--;
            
            
            cout << "Elemento "<< value<< " Removido" << endl;
            break;
        } 
        position = (position+1) % stringPositions;
        if (position == initialPosition){
            break;
        }
    }

    if (!found){
        cout << "Elemento "<< value <<" nao esta na tabela" << endl;
    }
}

//-----------------------------------------------------------------------

bool LinearHash::search(int value){
    int position = Hash(value);
    int initialPosition = position;

    while (estruturaInt[position].estado != -2){
        if (estruturaInt[position].data == value && estruturaInt[position].estado != -1){
            return true;
        }
        position = (position+1) % intPositions;
        if (position == initialPosition){
            break;
        }
    }
    return false;
    
}

bool LinearHash::search(string value){
   int position = Hash(value);
    int initialPosition = position;

    while (estruturaStr[position].estado != -2){
        if (estruturaStr[position].data == value && estruturaStr[position].estado != -1){
            return true;
        }
        position = (position+1) % stringPositions;
        if (position == initialPosition){
            break;
        }
    }
    return false;

}


//-----------------------------------------------------------------------

void LinearHash::print(){

    cout << endl;
    cout << "-----------------------------------------------------"<< endl;
    cout << "Tabela Hash com sondagem linear:" << endl;

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

void LinearHash::resizeInt(){
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

void LinearHash::resizeStr(){
    cout << "------- Redimensionando Tabela de Strings ----------" << endl;
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

bool LinearHash::ehPrimo(int n) {
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

int LinearHash::proximoPrimo(int n) {
  if (n <= 1) {
    return 2;
  }

  while (!ehPrimo(++n));
  return n;
}


#endif