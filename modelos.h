#ifndef MODELOS_H
#define MODELOS_H

#include <string>

using namespace std;

struct Usuario {
    int id;
    string nombre;
    string usuario;
    string contrasena;
    string rol;
    bool activo;
};

struct Producto {
    int id;
    string nombre;
    string categoria;
    string talla;
    string color;
    float precio;
    int stock;
    int stockMinimo;
    bool activo;
};

struct Venta {
    int id;
    int idVendedor;
    string fecha;
};

struct DetalleVenta {
    int idVenta;
    int idProducto;
    int cantidad;
    float precioUnitario;
};

struct Contadores {
    int cantidadUsuarios;
    int cantidadProductos;
    int cantidadVentas;
    int cantidadDetalles;
};

#endif
