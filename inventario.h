#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "modelos.h"

void mostrarProductos(const Producto productos[], int cantidadProductos);

int buscarProducto(
    const Producto productos[],
    int cantidadProductos,
    int idBuscado
);

int agregarProducto(
    Producto productos[],
    int cantidadProductos,
    int maxProductos
);

void modificarProducto(Producto productos[], int cantidadProductos);

void desactivarProducto(Producto productos[], int cantidadProductos);

void registrarEntrada(Producto productos[], int cantidadProductos);

void consultarStockBajo(const Producto productos[], int cantidadProductos);

bool guardarProductos(const Producto productos[], int cantidadProductos);

int cargarProductos(Producto productos[], int maxProductos);

#endif
