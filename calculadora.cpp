#include <iostream>
using namespace std;

int main() {

    int n1, n2, opcion, resultado;
    
    do
    {
        
        cout <<"Calculadora, elija una opcion" << endl;
        cout << "Opcion 1: suma" << endl;
        cout << "Opcion 2: resta" << endl;
        cout << "Opcion 3: multiplicacion" << endl;
        cout << "Opcion 4: division" << endl;
        cout << "Opcion 5: Salir"<< endl;
        cin >> opcion;

    } while (opcion != 5);
    
    
    return 0;
}
