#include "ventas.h"

#include "inventario.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace {

bool respuestaAfirmativa(std::string respuesta) {
    return respuesta == "si" || respuesta == "Si" ||
           respuesta == "SI" || respuesta == "sI";
}

bool respuestaNegativa(std::string respuesta) {
    return respuesta == "no" || respuesta == "No" ||
           respuesta == "NO" || respuesta == "nO";
}

int obtenerSiguienteIdVenta(const Venta ventas[], int cantidadVentas) {
    int mayorId = 0;

    for (int i = 0; i < cantidadVentas; i++) {
        if (ventas[i].id > mayorId) {
            mayorId = ventas[i].id;
        }
    }

    return mayorId + 1;
}

} // namespace

double calcularTotalVenta(
    const DetalleVenta detalles[],
    int cantidadDetalles,
    int idVenta
) {
    double total = 0.0;

    for (int i = 0; i < cantidadDetalles; i++) {
        if (detalles[i].idVenta == idVenta) {
            total += detalles[i].cantidad * detalles[i].precioUnitario;
        }
    }

    return total;
}

int agregarDetalleVenta(
    const Producto productos[],
    int cantidadProductos,
    DetalleVenta detallesTemporales[],
    int cantidadDetallesTemporales,
    int maxDetallesTemporales,
    int idVenta
) {
    if (cantidadDetallesTemporales >= maxDetallesTemporales) {
        std::cout << "La venta alcanzo el maximo de productos distintos.\n";
        return cantidadDetallesTemporales;
    }

    int idProducto;
    int cantidad;

    std::cout << "ID del producto: ";
    std::cin >> idProducto;

    std::cout << "Cantidad a vender: ";
    std::cin >> cantidad;

    int posicion = buscarProducto(productos, cantidadProductos, idProducto);

    if (posicion == -1) {
        std::cout << "No se encontro ese producto.\n";
        return cantidadDetallesTemporales;
    }

    if (!productos[posicion].activo) {
        std::cout << "Ese producto fue retirado por el administrador.\n";
        return cantidadDetallesTemporales;
    }

    if (productos[posicion].stock == 0) {
        std::cout << "Ese producto esta agotado.\n";
        return cantidadDetallesTemporales;
    }

    if (cantidad <= 0) {
        std::cout << "La cantidad debe ser mayor que cero.\n";
        return cantidadDetallesTemporales;
    }

    int cantidadYaAgregada = 0;

    for (int i = 0; i < cantidadDetallesTemporales; i++) {
        if (detallesTemporales[i].idVenta == idVenta &&
            detallesTemporales[i].idProducto == productos[posicion].id) {
            cantidadYaAgregada += detallesTemporales[i].cantidad;
        }
    }

    if (cantidad + cantidadYaAgregada > productos[posicion].stock) {
        std::cout << "No hay suficiente stock. Disponible para esta venta: "
                  << productos[posicion].stock - cantidadYaAgregada << '\n';
        return cantidadDetallesTemporales;
    }

    detallesTemporales[cantidadDetallesTemporales] = {
        idVenta,
        productos[posicion].id,
        cantidad,
        productos[posicion].precio
    };

    cantidadDetallesTemporales++;

    std::cout << "Producto agregado: " << productos[posicion].nombre << '\n';
    return cantidadDetallesTemporales;
}

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
) {
    ResultadoOperacionVentas resultado = {
        cantidadVentas,
        cantidadDetalles,
        false
    };

    if (cantidadProductos <= 0) {
        std::cout << "No hay productos en el inventario.\n";
        return resultado;
    }

    if (cantidadVentas >= maxVentas) {
        std::cout << "Se alcanzo el maximo de ventas que se pueden guardar.\n";
        return resultado;
    }

    if (cantidadDetalles >= maxDetalles) {
        std::cout << "No queda espacio para guardar detalles de venta.\n";
        return resultado;
    }

    int idVentaActual = obtenerSiguienteIdVenta(ventas, cantidadVentas);
    DetalleVenta detallesTemporales[maxDetallesPorVenta];
    int cantidadDetallesTemporales = 0;
    std::string respuesta = "si";

    while (respuestaAfirmativa(respuesta) &&
           cantidadDetallesTemporales < maxDetallesPorVenta) {
        cantidadDetallesTemporales = agregarDetalleVenta(
            productos,
            cantidadProductos,
            detallesTemporales,
            cantidadDetallesTemporales,
            maxDetallesPorVenta,
            idVentaActual
        );

        if (cantidadDetallesTemporales >= maxDetallesPorVenta) {
            break;
        }

        do {
            std::cout << "Agregar otro producto? (si/no): ";
            std::cin >> respuesta;

            if (!respuestaAfirmativa(respuesta) &&
                !respuestaNegativa(respuesta)) {
                std::cout << "Escribe si o no.\n";
            }
        } while (!respuestaAfirmativa(respuesta) &&
                 !respuestaNegativa(respuesta));

        if (respuestaNegativa(respuesta)) {
            break;
        }
    }

    if (cantidadDetallesTemporales == 0) {
        std::cout << "Venta cancelada: no se agregaron productos validos.\n";
        return resultado;
    }

    if (cantidadDetalles + cantidadDetallesTemporales > maxDetalles) {
        std::cout << "No hay suficiente espacio para guardar los detalles.\n";
        return resultado;
    }

    std::cout << "\n=== RESUMEN DE VENTA ===\n";
    for (int i = 0; i < cantidadDetallesTemporales; i++) {
        int posicion = buscarProducto(
            productos,
            cantidadProductos,
            detallesTemporales[i].idProducto
        );

        if (posicion != -1) {
            double subtotal = detallesTemporales[i].cantidad *
                              detallesTemporales[i].precioUnitario;
            std::cout << productos[posicion].nombre << " ("
                      << productos[posicion].talla << ", "
                      << productos[posicion].color << "): "
                      << detallesTemporales[i].cantidad << " x $"
                      << std::fixed << std::setprecision(2)
                      << detallesTemporales[i].precioUnitario
                      << " = $" << subtotal << '\n';
        }
    }

    double total = calcularTotalVenta(
        detallesTemporales,
        cantidadDetallesTemporales,
        idVentaActual
    );

    std::cout << "Total: $" << std::fixed << std::setprecision(2)
              << total << '\n';

    std::string confirmar;
    do {
        std::cout << "Confirmar venta? (si/no): ";
        std::cin >> confirmar;

        if (!respuestaAfirmativa(confirmar) &&
            !respuestaNegativa(confirmar)) {
            std::cout << "Escribe si o no.\n";
        }
    } while (!respuestaAfirmativa(confirmar) &&
             !respuestaNegativa(confirmar));

    if (respuestaNegativa(confirmar)) {
        std::cout << "Venta cancelada. El stock no cambio.\n";
        return resultado;
    }

    std::string fecha;
    std::cout << "Fecha de la venta (AAAA-MM-DD): ";
    std::cin >> fecha;

    ventas[cantidadVentas] = {idVentaActual, idVendedor, fecha};
    cantidadVentas++;

    for (int i = 0; i < cantidadDetallesTemporales; i++) {
        detalles[cantidadDetalles] = detallesTemporales[i];
        cantidadDetalles++;

        int posicion = buscarProducto(
            productos,
            cantidadProductos,
            detallesTemporales[i].idProducto
        );

        if (posicion != -1) {
            productos[posicion].stock -= detallesTemporales[i].cantidad;
        }
    }

    std::cout << "Venta #" << idVentaActual << " registrada.\n";

    resultado.cantidadVentas = cantidadVentas;
    resultado.cantidadDetalles = cantidadDetalles;
    resultado.exito = true;
    return resultado;
}

void consultarVentas(
    const Venta ventas[],
    int cantidadVentas,
    const DetalleVenta detalles[],
    int cantidadDetalles,
    const Producto productos[],
    int cantidadProductos,
    int idVendedor,
    bool mostrarTodas
) {
    bool encontroVentas = false;

    for (int i = 0; i < cantidadVentas; i++) {
        if (!mostrarTodas && ventas[i].idVendedor != idVendedor) {
            continue;
        }

        encontroVentas = true;
        std::cout << "\nVenta #" << ventas[i].id
                  << " | Fecha: " << ventas[i].fecha
                  << " | Vendedor: " << ventas[i].idVendedor << '\n';

        for (int j = 0; j < cantidadDetalles; j++) {
            if (detalles[j].idVenta == ventas[i].id) {
                int posicion = buscarProducto(
                    productos,
                    cantidadProductos,
                    detalles[j].idProducto
                );

                double subtotal = detalles[j].cantidad *
                                  detalles[j].precioUnitario;

                if (posicion != -1) {
                    std::cout << "  " << productos[posicion].nombre << " ("
                              << productos[posicion].talla << ", "
                              << productos[posicion].color << ")";
                } else {
                    std::cout << "  Producto ID " << detalles[j].idProducto;
                }

                std::cout << " | Cantidad: " << detalles[j].cantidad
                          << " | Precio: $" << std::fixed
                          << std::setprecision(2) << detalles[j].precioUnitario
                          << " | Subtotal: $" << subtotal << '\n';
            }
        }

        double total = calcularTotalVenta(detalles, cantidadDetalles, ventas[i].id);
        std::cout << "  Total: $" << std::fixed << std::setprecision(2)
                  << total << '\n';
    }

    if (!encontroVentas) {
        std::cout << "No hay ventas para mostrar.\n";
    }
}

bool guardarVentas(
    const Venta ventas[],
    int cantidadVentas,
    const DetalleVenta detalles[],
    int cantidadDetalles
) {
    std::ofstream archivoVentas("ventas.txt");
    std::ofstream archivoDetalles("detalles_venta.txt");

    if (!archivoVentas.is_open() || !archivoDetalles.is_open()) {
        std::cout << "No se pudieron abrir los archivos de ventas.\n";
        return false;
    }

    for (int i = 0; i < cantidadVentas; i++) {
        archivoVentas << ventas[i].id << '|'
                      << ventas[i].idVendedor << '|'
                      << ventas[i].fecha << '\n';
    }

    archivoDetalles << std::fixed << std::setprecision(2);
    for (int i = 0; i < cantidadDetalles; i++) {
        archivoDetalles << detalles[i].idVenta << '|'
                        << detalles[i].idProducto << '|'
                        << detalles[i].cantidad << '|'
                        << detalles[i].precioUnitario << '\n';
    }

    if (!archivoVentas || !archivoDetalles) {
        std::cout << "Ocurrio un error al guardar las ventas.\n";
        return false;
    }

    return true;
}

ResultadoOperacionVentas cargarVentas(
    Venta ventas[],
    int maxVentas,
    DetalleVenta detalles[],
    int maxDetalles
) {
    std::ifstream archivoVentas("ventas.txt");
    std::ifstream archivoDetalles("detalles_venta.txt");

    bool existeArchivoVentas = archivoVentas.is_open();
    bool existeArchivoDetalles = archivoDetalles.is_open();

    if (!existeArchivoVentas && !existeArchivoDetalles) {
        return {0, 0, true};
    }

    if (!existeArchivoVentas || !existeArchivoDetalles) {
        std::cout << "Falta uno de los archivos de ventas o detalles.\n";
        return {0, 0, false};
    }

    int cantidadVentas = 0;
    int cantidadDetalles = 0;
    std::string linea;

    while (cantidadVentas < maxVentas &&
           std::getline(archivoVentas, linea)) {
        if (linea.empty()) {
            continue;
        }

        std::stringstream registro(linea);
        Venta venta;
        char separador;

        if (!(registro >> venta.id >> separador) || separador != '|') {
            continue;
        }

        if (!(registro >> venta.idVendedor >> separador) || separador != '|') {
            continue;
        }

        if (!std::getline(registro, venta.fecha) ||
            venta.id <= 0 || venta.fecha.empty()) {
            continue;
        }

        ventas[cantidadVentas] = venta;
        cantidadVentas++;
    }

    while (cantidadDetalles < maxDetalles &&
           std::getline(archivoDetalles, linea)) {
        if (linea.empty()) {
            continue;
        }

        std::stringstream registro(linea);
        DetalleVenta detalle;
        char separador;

        if (!(registro >> detalle.idVenta >> separador) || separador != '|') {
            continue;
        }

        if (!(registro >> detalle.idProducto >> separador) || separador != '|') {
            continue;
        }

        if (!(registro >> detalle.cantidad >> separador) || separador != '|') {
            continue;
        }

        if (!(registro >> detalle.precioUnitario) ||
            detalle.idVenta <= 0 || detalle.idProducto <= 0 ||
            detalle.cantidad <= 0 || detalle.precioUnitario <= 0) {
            continue;
        }

        detalles[cantidadDetalles] = detalle;
        cantidadDetalles++;
    }

    return {cantidadVentas, cantidadDetalles, true};
}
