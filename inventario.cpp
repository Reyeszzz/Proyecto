#include "inventario.h"

#include <iomanip>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int buscarProducto(
    const Producto productos[],
    int cantidadProductos,
    int idBuscado
) {
    for (int i = 0; i < cantidadProductos; i++) {
        if (productos[i].id == idBuscado) {
            return i;
        }
    }

    return -1;
}

int agregarProducto(
    Producto productos[],
    int cantidadProductos,
    int maxProductos
) {
    if (cantidadProductos >= maxProductos) {
        std::cout << "El inventario esta lleno.\n";
        return cantidadProductos;
    }

    int mayorId = 0;

    for (int i = 0; i < cantidadProductos; i++) {
        if (productos[i].id > mayorId) {
            mayorId = productos[i].id;
        }
    }

    Producto nuevoProducto;
    nuevoProducto.id = mayorId + 1;

    std::cout << "Nombre: ";
    std::getline(std::cin >> std::ws, nuevoProducto.nombre);

    std::cout << "Categoria: ";
    std::getline(std::cin >> std::ws, nuevoProducto.categoria);

    std::cout << "Talla: ";
    std::getline(std::cin >> std::ws, nuevoProducto.talla);

    std::cout << "Color: ";
    std::getline(std::cin >> std::ws, nuevoProducto.color);

    do {
        std::cout << "Precio (mayor que 0): ";
        std::cin >> nuevoProducto.precio;

        if (nuevoProducto.precio <= 0) {
            std::cout << "El precio debe ser mayor que cero.\n";
        }
    } while (nuevoProducto.precio <= 0);

    do {
        std::cout << "Stock inicial (0 o mas): ";
        std::cin >> nuevoProducto.stock;

        if (nuevoProducto.stock < 0) {
            std::cout << "El stock no puede ser negativo.\n";
        }
    } while (nuevoProducto.stock < 0);

    do {
        std::cout << "Stock minimo (0 o mas): ";
        std::cin >> nuevoProducto.stockMinimo;

        if (nuevoProducto.stockMinimo < 0) {
            std::cout << "El stock minimo no puede ser negativo.\n";
        }
    } while (nuevoProducto.stockMinimo < 0);

    nuevoProducto.activo = true;

    productos[cantidadProductos] = nuevoProducto;
    cantidadProductos++;

    std::cout << "Producto agregado con ID " << nuevoProducto.id << ".\n";

    return cantidadProductos;
}

void modificarProducto(Producto productos[], int cantidadProductos) {
    int idBuscado;

    std::cout << "ID del producto que quieres modificar: ";
    std::cin >> idBuscado;

    int posicion = buscarProducto(productos, cantidadProductos, idBuscado);

    if (posicion == -1) {
        std::cout << "No se encontro ese producto.\n";
        return;
    }

    std::cout << "Producto: " << productos[posicion].nombre << '\n';
    std::cout << "Que dato quieres modificar?\n";
    std::cout << "1. Nombre\n";
    std::cout << "2. Categoria\n";
    std::cout << "3. Talla\n";
    std::cout << "4. Color\n";
    std::cout << "5. Precio\n";
    std::cout << "6. Stock minimo\n";

    int opcion;
    std::cout << "Opcion: ";
    std::cin >> opcion;

    if (opcion == 1) {
        std::cout << "Nuevo nombre: ";
        std::getline(std::cin >> std::ws, productos[posicion].nombre);
    } else if (opcion == 2) {
        std::cout << "Nueva categoria: ";
        std::getline(std::cin >> std::ws, productos[posicion].categoria);
    } else if (opcion == 3) {
        std::cout << "Nueva talla: ";
        std::getline(std::cin >> std::ws, productos[posicion].talla);
    } else if (opcion == 4) {
        std::cout << "Nuevo color: ";
        std::getline(std::cin >> std::ws, productos[posicion].color);
    } else if (opcion == 5) {
        double nuevoPrecio;
        std::cout << "Nuevo precio: ";
        std::cin >> nuevoPrecio;

        if (nuevoPrecio <= 0) {
            std::cout << "El precio debe ser mayor que cero.\n";
            return;
        }

        productos[posicion].precio = nuevoPrecio;
    } else if (opcion == 6) {
        int nuevoStockMinimo;
        std::cout << "Nuevo stock minimo: ";
        std::cin >> nuevoStockMinimo;

        if (nuevoStockMinimo < 0) {
            std::cout << "El stock minimo no puede ser negativo.\n";
            return;
        }

        productos[posicion].stockMinimo = nuevoStockMinimo;
    } else {
        std::cout << "Opcion invalida.\n";
        return;
    }

    std::cout << "Producto modificado correctamente.\n";
}

void desactivarProducto(Producto productos[], int cantidadProductos) {
    int idBuscado;

    std::cout << "ID del producto que quieres retirar: ";
    std::cin >> idBuscado;

    int posicion = buscarProducto(productos, cantidadProductos, idBuscado);

    if (posicion == -1) {
        std::cout << "No se encontro ese producto.\n";
        return;
    }

    if (!productos[posicion].activo) {
        std::cout << "Ese producto ya esta retirado.\n";
        return;
    }

    productos[posicion].activo = false;
    std::cout << "Producto retirado del catalogo.\n";
}

void registrarEntrada(Producto productos[], int cantidadProductos) {
    int idBuscado;

    std::cout << "ID del producto que recibio mercancia: ";
    std::cin >> idBuscado;

    int posicion = buscarProducto(productos, cantidadProductos, idBuscado);

    if (posicion == -1) {
        std::cout << "No se encontro ese producto.\n";
        return;
    }

    if (!productos[posicion].activo) {
        std::cout << "El producto fue retirado por el administrador.\n";
        return;
    }

    int cantidadEntrante;

    do {
        std::cout << "Cantidad recibida (mayor que 0): ";
        std::cin >> cantidadEntrante;

        if (cantidadEntrante <= 0) {
            std::cout << "La cantidad debe ser mayor que cero.\n";
        }
    } while (cantidadEntrante <= 0);

    productos[posicion].stock += cantidadEntrante;

    std::cout << "Entrada registrada. Nuevo stock: "
              << productos[posicion].stock << '\n';
    std::cout << "El producto vuelve a estar disponible.\n";
}

void consultarStockBajo(const Producto productos[], int cantidadProductos) {
    bool encontroProductos = false;

    std::cout << "=== PRODUCTOS CON STOCK BAJO ===\n";

    for (int i = 0; i < cantidadProductos; i++) {
        if (productos[i].activo &&
            productos[i].stock <= productos[i].stockMinimo) {
            encontroProductos = true;
            std::cout << "ID: " << productos[i].id
                      << " | " << productos[i].nombre
                      << " | Talla: " << productos[i].talla
                      << " | Color: " << productos[i].color
                      << " | Stock: " << productos[i].stock
                      << " | Minimo: " << productos[i].stockMinimo
                      << '\n';
        }
    }

    if (!encontroProductos) {
        std::cout << "No hay productos activos con stock bajo.\n";
    }
}

bool guardarProductos(const Producto productos[], int cantidadProductos) {
    std::ofstream archivo("productos.txt");

    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir productos.txt para guardar.\n";
        return false;
    }

    archivo << std::fixed << std::setprecision(2);

    for (int i = 0; i < cantidadProductos; i++) {
        archivo << productos[i].id << '|'
                << productos[i].nombre << '|'
                << productos[i].categoria << '|'
                << productos[i].talla << '|'
                << productos[i].color << '|'
                << productos[i].precio << '|'
                << productos[i].stock << '|'
                << productos[i].stockMinimo << '|'
                << (productos[i].activo ? 1 : 0) << '\n';
    }

    if (!archivo) {
        std::cout << "Ocurrio un error al guardar los productos.\n";
        return false;
    }

    return true;
}

int cargarProductos(Producto productos[], int maxProductos) {
    std::ifstream archivo("productos.txt");

    if (!archivo.is_open()) {
        return 0;
    }

    int cantidadProductos = 0;
    std::string linea;

    while (cantidadProductos < maxProductos && std::getline(archivo, linea)) {
        if (linea.empty()) {
            continue;
        }

        std::stringstream registro(linea);
        Producto producto;
        char separador;
        int activoComoNumero;

        if (!(registro >> producto.id >> separador) || separador != '|') {
            continue;
        }

        if (!std::getline(registro, producto.nombre, '|') ||
            !std::getline(registro, producto.categoria, '|') ||
            !std::getline(registro, producto.talla, '|') ||
            !std::getline(registro, producto.color, '|')) {
            continue;
        }

        if (!(registro >> producto.precio >> separador) || separador != '|') {
            continue;
        }

        if (!(registro >> producto.stock >> separador) || separador != '|') {
            continue;
        }

        if (!(registro >> producto.stockMinimo >> separador) || separador != '|') {
            continue;
        }

        if (!(registro >> activoComoNumero)) {
            continue;
        }

        if (producto.id <= 0 || producto.precio <= 0 ||
            producto.stock < 0 || producto.stockMinimo < 0 ||
            (activoComoNumero != 0 && activoComoNumero != 1)) {
            continue;
        }

        producto.activo = (activoComoNumero == 1);
        productos[cantidadProductos] = producto;
        cantidadProductos++;
    }

    return cantidadProductos;
}

void mostrarProductos(const Producto productos[], int cantidadProductos) {
    if (cantidadProductos == 0) {
        std::cout << "No hay productos registrados.\n";
        return;
    }

    std::cout << std::fixed << std::setprecision(2);

    for (int i = 0; i < cantidadProductos; i++) {
        std::cout << "\nID: " << productos[i].id << '\n';
        std::cout << "Nombre: " << productos[i].nombre << '\n';
        std::cout << "Categoria: " << productos[i].categoria << '\n';
        std::cout << "Talla: " << productos[i].talla << '\n';
        std::cout << "Color: " << productos[i].color << '\n';
        std::cout << "Precio: $" << productos[i].precio << '\n';
        std::cout << "Stock: " << productos[i].stock << '\n';
        std::cout << "Stock minimo: " << productos[i].stockMinimo << '\n';

        if (!productos[i].activo) {
            std::cout << "Estado: Retirado por el administrador\n";
        } else if (productos[i].stock == 0) {
            std::cout << "Estado: Agotado\n";
        } else {
            std::cout << "Estado: Disponible\n";
        }

        if (productos[i].activo &&
            productos[i].stock > 0 &&
            productos[i].stock <= productos[i].stockMinimo) {
            std::cout << "Aviso: stock bajo\n";
        }

        std::cout << "------------------------------\n";
    }
}
