#include <iostream>
#include <fstream>

using namespace std;

struct Empleado {
    string nombre;
    string apellido;
    float salario;
};

int heapSize = 0;  
Empleado empleados[1000]; 

void leerArchivo() {
    ifstream file("empleados.txt"); 
   
    if (!file.is_open()) {
        cout << "Error: No se pudo abrir el archivo. Verifique la ruta." << endl;
        return;
    } else {
        cout << "Archivo abierto correctamente." << endl;
    }

    string line;
    while (getline(file, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);

        string nombre = line.substr(0, pos1);
        string apellido = line.substr(pos1 + 1, pos2 - pos1 - 1);
        float salario = stof(line.substr(pos2 + 1)); // Convertir a float

        if (heapSize < 1000) { // Asegúrate de no exceder el tamaño del arreglo
            empleados[heapSize].nombre = nombre;
            empleados[heapSize].apellido = apellido;
            empleados[heapSize].salario = salario;
            heapSize++;
        } else {
            cout << "Se alcanzó el número máximo de empleados." << endl;
            break;
        }
    }
    file.close();
}

void heapMaximo(Empleado arrLocal[], int l, int i) { //Función para mantener propiedad de heap maximo.
    int cabezera = i;
    int izquierda = 2 * i + 1;
    int derecha = 2 * i + 2;

    if (izquierda < l && arrLocal[izquierda].salario > arrLocal[cabezera].salario) {
        cabezera = izquierda;
    }
    if (derecha < l && arrLocal[derecha].salario > arrLocal[cabezera].salario) {
        cabezera = derecha;
    }
    if (cabezera != i) {
        swap(arrLocal[i], arrLocal[cabezera]);
        heapMaximo(arrLocal, l, cabezera);
    }
}

void construirMonticuloMax(Empleado arrLocal[], int l){
    for (int i = (l / 2) - 1; i >= 0; i--) { //Constuyendo heap máximo.
        heapMaximo(arrLocal, l, i);
    }
}



void ordenarMonticulo(Empleado arrLocal[], int l) {

    construirMonticuloMax(arrLocal, l);

    for (int i = l - 1; i >= 0; i--) {
        swap(arrLocal[0], arrLocal[i]);
        heapMaximo(arrLocal, i, 0);
    }
}

void mostrarDescendente() {
    ordenarMonticulo(empleados, heapSize);
    
    for (int i = heapSize - 1; i >= 0; i--) {
        cout << empleados[i].nombre << " " << empleados[i].apellido << " Salario: " << empleados[i].salario << "\n";
    }
}

int main() {
    leerArchivo();
    
    int opcion;

    do {
        cout << "1. Buscar empleado" << "\n";
        cout << "2. Eliminar empleado" << "\n";
        cout << "3. Mostrar salarios en orden descendente" << "\n";
        cout << "4. Salir" << "\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                // Implementar búsqueda de empleado aquí
                break;
            case 2:
                // Implementar eliminación de empleado aquí
                break;
            case 3:
                mostrarDescendente();
                cout << "\n";
                break;
            case 4:
                cout << "Finalizando programa" << "\n";
                break;
            default:
                cout << "Opción incorrecta" << "\n";
                break;
        }
    } while (opcion != 4);

    return 0;
}
