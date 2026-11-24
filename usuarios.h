#include "modelos.h"

int iniciarSesion(Usuario usuarios[], int cantidadUsuarios);

int agregarUsuario(Usuario usuarios[], int cantidadUsuarios, int maxUsuarios);

void cerrarSesion();

void desactivarUsuario(Usuario usuarios[], int cantidadUsuarios);

int buscarUsuario(Usuario usuarios[], int cantidadUsuarios, int idBuscado);

bool guardarUsuarios(const Usuario usuarios[], int cantidadUsuarios);

int cargarUsuarios(Usuario usuarios[], int maxUsuarios);


Contadores menuAdministrador(
    Usuario usuarios[],
    Producto productos[],
    Venta ventas[],
    DetalleVenta detalles[],
    Contadores contadores
);


Contadores menuVendedor(
    Usuario usuarios[],
    Producto productos[],
    Venta ventas[],
    DetalleVenta detalles[],
    Contadores contadores,
    int idVendedor
);