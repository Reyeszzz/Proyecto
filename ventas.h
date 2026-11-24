#ifndef VENTAS_H
#define VENTAS_H

#include "modelos.h"

const int maxDetallesPorVenta = 50;

struct ResultadoOperacionVentas {
    int cantidadVentas;
    int cantidadDetalles;
    bool exito;
};

double calcularTotalVenta(
    const DetalleVenta detalles[],
    int cantidadDetalles,
    int idVenta
);

int agregarDetalleVenta(
    const Producto productos[],
    int cantidadProductos,
    DetalleVenta detallesTemporales[],
    int cantidadDetallesTemporales,
    int maxDetallesTemporales,
    int idVenta
);

ResultadoOperacionVentas registrarVenta(
    Producto productos[],
    int cantidadProductos,
    Venta ventas[],
    int cantidadVentas,
    int maxVentas,
    DetalleVenta detalles[],
    int cantidadDetalles,
    int maxDetalles,
    int idVendedor
);

void consultarVentas(
    const Venta ventas[],
    int cantidadVentas,
    const DetalleVenta detalles[],
    int cantidadDetalles,
    const Producto productos[],
    int cantidadProductos,
    int idVendedor,
    bool mostrarTodas
);

bool guardarVentas(
    const Venta ventas[],
    int cantidadVentas,
    const DetalleVenta detalles[],
    int cantidadDetalles
);

ResultadoOperacionVentas cargarVentas(
    Venta ventas[],
    int maxVentas,
    DetalleVenta detalles[],
    int maxDetalles
);

#endif
