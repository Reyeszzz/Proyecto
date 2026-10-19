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

        switch (opcion) {
            case 1:
                cout << "Ingrese el primer numero: ";
                cin >> n1;

                cout << "Ingrese el segundo numero: ";
                cin >> n2;

                cout << "Resultado: " << n1 + n2 << endl;
                break;

            case 2:
            case 3:
            case 4:
                cout << "Funcion pendiente." << endl;
                break;

            case 5:
                cout << "Saliendo..." << endl;
                break;

            default:
                cout << "Opcion invalida." << endl;
        }
    } while (opcion != 5);
    
    
    return 0;
}
