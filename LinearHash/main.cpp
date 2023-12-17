
#include "LinearHash.cpp"


using namespace std;

int main()
{

    cout << "-------------------------Tabela Hash por Sondagem Linear-------------------------" << endl;
    cout << "indique o numero de posicoes da tabela: ";
    int positions;
    cin >> positions;

    while(positions < 0){
        cin >> positions;
    }

    LinearHash linear(positions);
    int running = true;
    int action;

    
    while(running){
        cout << "Digite o numero correspondente a acao que deseja executar" << endl;
        cout << "1 - Inserir na tabela" << endl;
        cout << "2 - Remover da tabela" << endl;
        cout << "3 - Buscar na tabela" << endl;
        cout << "4 - Imprimir a tabela" << endl;
        cout << "5 - Concluir programa" << endl;
        cin >> action;

        switch (action)
        {
        case 1:
        {
            char valueType;
            cout << "Digite I para inserir inteiro e S para strings: ";
            cin >> valueType;
            cin.ignore();

            while (valueType != 'I' && valueType != 'i' && valueType != 'S' && valueType != 's')
            {
                cout << "Digite I ou S";
                cin >> valueType;
            }
            
            if (valueType == 'I' || valueType == 'i'){
                int newValueInt;
                cout << "Insira um numero nao negativo: ";
                cin >> newValueInt;

                while (newValueInt < 0)
                {
                    cin >> newValueInt;
                }
                
                linear.append(newValueInt);
                
                break;
            } 
            string newValueStr;
            cout << "Insira uma string: ";
            cin >> newValueStr;

            while (newValueStr == "")
            {
                cin >> newValueStr;
            }
            
            linear.append(newValueStr);
            
            break;
                
            
        }
        case 2:
        {
            char valueType;
            cout << "Digite I para remover inteiro e S para strings: ";
            cin >> valueType;

            while (valueType != 'I' && valueType != 'i' && valueType != 'S' && valueType != 's')
            {
                cout << "Digite I ou S";
                cin >> valueType;
            }
            
            if (valueType == 'I' || valueType == 'i'){
                int newValueInt;
                cout << "Remover numero: ";
                cin >> newValueInt;

                while (newValueInt < 0)
                {
                    cin >> newValueInt;
                }
                
                linear.remove(newValueInt);
                break;
            } 
            string newValueStr;
            cout << "Remover string: ";
            cin >> newValueStr;

            while (newValueStr == "")
            {
                cin >> newValueStr;
            }
            
            linear.remove(newValueStr);
            cout << newValueStr << " removido" << endl;
            break;
        }
        case 3:
        {
            char valueType;
            cout << "Digite I para buscar inteiro e S para strings: ";
            cin >> valueType;

            while (valueType != 'I' && valueType != 'i' && valueType != 'S' && valueType != 's')
            {
                cout << "Digite I ou S";
                cin >> valueType;
            }
            
            if (valueType == 'I' || valueType == 'i'){
                int newValueInt;
                cout << "Buscar numero: ";
                cin >> newValueInt;

                while (newValueInt < 0)
                {
                    cin >> newValueInt;
                }
                
                if(linear.search(newValueInt)){
                    cout << newValueInt << " esta na tabela" << endl;
                    break;
                };
                cout << newValueInt << " nao esta na tabela" << endl;
                break;
            } 
            string newValueStr;
            cout << "Buscar string: ";
            cin >> newValueStr;

            while (newValueStr == "")
            {
                cin >> newValueStr;
            }
            
            if(linear.search(newValueStr)){
                    cout << newValueStr << " esta na tabela" << endl;
                    break;
                };
            cout << newValueStr << " nao esta na tabela" << endl;
            break;
        }
        case 4:
        {
            linear.print();
            break;
        }
        case 5:
        {
            running = false;
            break;
        }
        default:
            break;
        }

        cout <<endl;       
        cout <<"-------------------------------"<<endl;       
    }



    return 0;
}