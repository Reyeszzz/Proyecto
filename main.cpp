#include <iostream>
#include "modelos.h"
#include "usuarios.h"
#include "inventario.h"
#include "ventas.h"

using namespace std;

int main() {

    // Arreglos compartidos
    Usuario usuarios[50];
    Producto productos[100];
    Venta ventas[100];
    DetalleVenta detalles[500];

    // Contadores
    Contadores contadores;

    contadores.cantidadUsuarios = 0;
    contadores.cantidadProductos = 0;
    contadores.cantidadVentas = 0;
    contadores.cantidadDetalles = 0;

    int opcion = 0;
    int indiceUsuario = -1;

    // Cargar informacion desde archivos
    contadores.cantidadUsuarios = cargarUsuarios(usuarios, 50);

    contadores.cantidadProductos = cargarProductos(productos, 100);

    ResultadoOperacionVentas resultadoCarga;

    resultadoCarga = cargarVentas(ventas, 100, detalles, 500);

    contadores.cantidadVentas = resultadoCarga.cantidadVentas;
    contadores.cantidadDetalles = resultadoCarga.cantidadDetalles;

    do {

        cout << "\n===== SISTEMA DE INVENTARIO =====" << endl;
        cout << "1. Iniciar sesion" << endl;
        cout << "2. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {

            case 1:

                indiceUsuario = iniciarSesion(
                    usuarios,
                    contadores.cantidadUsuarios
                );

                if (indiceUsuario != -1) {

                    if (usuarios[indiceUsuario].rol == "administrador") {

                        contadores = menuAdministrador(
                            usuarios,
                            productos,
                            ventas,
                            detalles,
                            contadores
                        );

                    }
                    else if (usuarios[indiceUsuario].rol == "vendedor") {

                        contadores = menuVendedor(
                            usuarios,
                            productos,
                            ventas,
                            detalles,
                            contadores,
                            usuarios[indiceUsuario].id
                        );

                    }
                    else {

                        cout << "\nEl usuario tiene un rol no reconocido." << endl;

                    }

                    cerrarSesion();
                }

                break;

            case 2:

                cout << "\nCerrando el programa..." << endl;

                break;

            default:

                cout << "\nOpcion invalida." << endl;

        }

    } while (opcion != 2);

    // Guardar informacion en archivos
    guardarUsuarios(usuarios, contadores.cantidadUsuarios);

    guardarProductos(productos, contadores.cantidadProductos);

    guardarVentas(
        ventas,
        contadores.cantidadVentas,
        detalles,
        contadores.cantidadDetalles
    );

    cout << "\nInformacion guardada correctamente." << endl;

    return 0;
}