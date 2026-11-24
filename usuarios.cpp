#include <iostream>
#include <fstream>
#include "usuarios.h"
#include "inventario.h"
#include "ventas.h"

using namespace std;


int iniciarSesion(Usuario usuarios[], int cantidadUsuarios) {

    string nombreUsuario;
    string contrasena;

    cout << "\n===== INICIO DE SESION =====" << endl;

    cout << "Usuario: ";
    cin >> nombreUsuario;

    cout << "Contrasena: ";
    cin >> contrasena;

    for (int i = 0; i < cantidadUsuarios; i++) {

        if (usuarios[i].usuario == nombreUsuario &&
            usuarios[i].contrasena == contrasena &&
            usuarios[i].activo == true) {

            cout << "\nBienvenido, " << usuarios[i].nombre << endl;
            return i;
        }
    }

    cout << "\nUsuario o contrasena incorrectos." << endl;
    return -1;
}


int agregarUsuario(Usuario usuarios[], int cantidadUsuarios, int maxUsuarios) {

    if (cantidadUsuarios >= maxUsuarios) {
        cout << "\nNo hay espacio para registrar mas usuarios." << endl;
        return cantidadUsuarios;
    }

    Usuario nuevoUsuario;

    cout << "\n===== REGISTRAR USUARIO =====" << endl;

    nuevoUsuario.id = cantidadUsuarios + 1;

    cout << "Nombre completo: ";
    cin.ignore();
    getline(cin, nuevoUsuario.nombre);

    cout << "Nombre de usuario: ";
    cin >> nuevoUsuario.usuario;

    cout << "Contrasena: ";
    cin >> nuevoUsuario.contrasena;

    cout << "Rol (administrador/vendedor): ";
    cin >> nuevoUsuario.rol;

    nuevoUsuario.activo = true;

    usuarios[cantidadUsuarios] = nuevoUsuario;

    cout << "\nUsuario registrado correctamente." << endl;

    return cantidadUsuarios + 1;
}


void desactivarUsuario(Usuario usuarios[], int cantidadUsuarios) {

    int idBuscado;
    bool encontrado = false;

    cout << "\n===== DESACTIVAR USUARIO =====" << endl;
    cout << "Ingrese el ID del usuario: ";
    cin >> idBuscado;

    for (int i = 0; i < cantidadUsuarios; i++) {

        if (usuarios[i].id == idBuscado) {

            encontrado = true;

            if (usuarios[i].activo == true) {

                usuarios[i].activo = false;

                cout << "\nUsuario desactivado correctamente." << endl;
            }
            else {

                cout << "\nEl usuario ya se encuentra desactivado." << endl;
            }

            break;
        }
    }

    if (encontrado == false) {
        cout << "\nNo se encontro ningun usuario con ese ID." << endl;
    }
}


int buscarUsuario(Usuario usuarios[], int cantidadUsuarios, int idBuscado) {

    for (int i = 0; i < cantidadUsuarios; i++) {

        if (usuarios[i].id == idBuscado) {
            return i;
        }
    }

    return -1;
}


void cerrarSesion() {

    cout << "\nSesion cerrada correctamente." << endl;
}


bool guardarUsuarios(const Usuario usuarios[], int cantidadUsuarios) {

    ofstream archivo("usuarios.txt");

    if (!archivo) {
        cout << "\nError al guardar los usuarios." << endl;
        return false;
    }

    for (int i = 0; i < cantidadUsuarios; i++) {

        archivo << usuarios[i].id << "|"
                << usuarios[i].nombre << "|"
                << usuarios[i].usuario << "|"
                << usuarios[i].contrasena << "|"
                << usuarios[i].rol << "|"
                << usuarios[i].activo << endl;
    }

    archivo.close();

    cout << "\nUsuarios guardados correctamente." << endl;

    return true;
}


int cargarUsuarios(Usuario usuarios[], int maxUsuarios) {

    ifstream archivo("usuarios.txt");

    if (!archivo) {
        return 0;
    }

    int cantidadUsuarios = 0;

    string idTexto;
    string nombre;
    string usuario;
    string contrasena;
    string rol;
    string activoTexto;

    while (cantidadUsuarios < maxUsuarios &&
           getline(archivo, idTexto, '|') &&
           getline(archivo, nombre, '|') &&
           getline(archivo, usuario, '|') &&
           getline(archivo, contrasena, '|') &&
           getline(archivo, rol, '|') &&
           getline(archivo, activoTexto)) {

        usuarios[cantidadUsuarios].id = stoi(idTexto);
        usuarios[cantidadUsuarios].nombre = nombre;
        usuarios[cantidadUsuarios].usuario = usuario;
        usuarios[cantidadUsuarios].contrasena = contrasena;
        usuarios[cantidadUsuarios].rol = rol;
        usuarios[cantidadUsuarios].activo = (activoTexto == "1");

        cantidadUsuarios++;
    }

    archivo.close();

    cout << "\nUsuarios cargados: " << cantidadUsuarios << endl;

    return cantidadUsuarios;
}

Contadores menuAdministrador(
    Usuario usuarios[],
    Producto productos[],
    Venta ventas[],
    DetalleVenta detalles[],
    Contadores contadores
) {

    int opcion = 0;

    do {
        cout << "\n===== MENU ADMINISTRADOR =====" << endl;
        cout << "1. Agregar usuario" << endl;
        cout << "2. Desactivar usuario" << endl;
        cout << "3. Agregar producto" << endl;
        cout << "4. Mostrar inventario" << endl;
        cout << "5. Modificar producto" << endl;
        cout << "6. Desactivar producto" << endl;
        cout << "7. Registrar entrada de mercancia" << endl;
        cout << "8. Consultar stock bajo" << endl;
        cout << "9. Consultar todas las ventas" << endl;
        cout << "10. Cerrar sesion" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {

            case 1:
                contadores.cantidadUsuarios = agregarUsuario(
                    usuarios,
                    contadores.cantidadUsuarios,
                    50
                );
                break;

            case 2:
                desactivarUsuario(
                    usuarios,
                    contadores.cantidadUsuarios
                );
                break;

            case 3:
                contadores.cantidadProductos = agregarProducto(
                    productos,
                    contadores.cantidadProductos,
                    100
                );
                break;

            case 4:
                mostrarProductos(
                    productos,
                    contadores.cantidadProductos
                );
                break;

            case 5:
                modificarProducto(
                    productos,
                    contadores.cantidadProductos
                );
                break;

            case 6:
                desactivarProducto(
                    productos,
                    contadores.cantidadProductos
                );
                break;

            case 7:
                registrarEntrada(
                    productos,
                    contadores.cantidadProductos
                );
                break;

            case 8:
                consultarStockBajo(
                    productos,
                    contadores.cantidadProductos
                );
                break;

            case 9:
                consultarVentas(
                    ventas,
                    contadores.cantidadVentas,
                    detalles,
                    contadores.cantidadDetalles,
                    productos,
                    contadores.cantidadProductos,
                    0,
                    true
                );
                break;

            case 10:
                cout << "\nCerrando sesion de administrador..." << endl;
                break;

            default:
                cout << "\nOpcion invalida." << endl;
        }

    } while (opcion != 10);

    return contadores;
}


Contadores menuVendedor(
    Usuario usuarios[],
    Producto productos[],
    Venta ventas[],
    DetalleVenta detalles[],
    Contadores contadores,
    int idVendedor
) {

    int opcion = 0;

    do {
        cout << "\n===== MENU VENDEDOR =====" << endl;
        cout << "1. Consultar inventario" << endl;
        cout << "2. Registrar venta" << endl;
        cout << "3. Consultar mis ventas" << endl;
        cout << "4. Cerrar sesion" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {

            case 1:
                mostrarProductos(
                    productos,
                    contadores.cantidadProductos
                );
                break;

            case 2: {
                ResultadoOperacionVentas resultado;

                resultado = registrarVenta(
                    productos,
                    contadores.cantidadProductos,
                    ventas,
                    contadores.cantidadVentas,
                    100,
                    detalles,
                    contadores.cantidadDetalles,
                    500,
                    idVendedor
                );

                if (resultado.exito == true) {
                    contadores.cantidadVentas = resultado.cantidadVentas;
                    contadores.cantidadDetalles = resultado.cantidadDetalles;
                }

                break;
            }

            case 3:
                consultarVentas(
                    ventas,
                    contadores.cantidadVentas,
                    detalles,
                    contadores.cantidadDetalles,
                    productos,
                    contadores.cantidadProductos,
                    idVendedor,
                    false
                );
                break;

            case 4:
                cout << "\nCerrando sesion de vendedor..." << endl;
                break;

            default:
                cout << "\nOpcion invalida." << endl;
        }

    } while (opcion != 4);

    return contadores;
}