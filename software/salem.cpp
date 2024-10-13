#include <iostream>
#include <fstream>

using namespace std;

struct Empleado {
    string nombre;
    string apellido;
    float salario;
};

int heapSize = 0;  //capacidad actual
int maxSize = 1200; //capacidad maxima
Empleado empleados[1200];  //Heap global

void leerArchivo() {
    ifstream file("empleados.txt"); 
   
    if (!file.is_open()) {
        cout << "Error: No se pudo abrir el archivo." << endl;
        return;
    } 

    string line;
    while (getline(file, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);

        string nombre = line.substr(0, pos1);
        string apellido = line.substr(pos1 + 1, pos2 - pos1 - 1);
        float salario = stof(line.substr(pos2 + 1)); 

        if (heapSize < 1000) { 
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


void insertar(Empleado empleado) {// Insertar en heap
    if (heapSize == maxSize) {
        cout << "El heap de empleados está lleno\n";
        return;
    }
    empleados[heapSize] = empleado;
    heapSize++;
    construirMonticuloMax(empleados, heapSize);  // Asegurar propiedad de max-heap
}

int buscar(Empleado empleado) { //Funcion de buscar por valor
    for (int i = 0; i < heapSize; i++) {
        if (empleados[i].nombre == empleado.nombre && empleados[i].apellido == empleado.apellido ) {
            return i;
        }
    }
    return -1;
}

void eliminar(Empleado empleado) { //Funcion de eliminar por valor 
    int indice = buscar(empleado);
    if (indice == -1) { 
        cout << "No se encontró el elemento.\n";
        return;
    }

    empleados[indice] = empleados[heapSize - 1];
    heapSize--;
    construirMonticuloMax(empleados, heapSize); 
}


void ordenarMonticulo(Empleado arrLocal[], int l) { //Ordenar heap

    construirMonticuloMax(arrLocal, l);

    for (int i = l - 1; i >= 0; i--) {
        swap(arrLocal[0], arrLocal[i]);
        heapMaximo(arrLocal, i, 0);
    }
}



void mostrarDescendente() {//Mostrar heap
    ordenarMonticulo(empleados, heapSize);
    
    for (int i = heapSize - 1; i >= 0; i--) {
        cout << empleados[i].nombre << " " << empleados[i].apellido << " Salario: " << empleados[i].salario << "\n";
    }
}

int main() {
    leerArchivo();
    
    int opcion;

    do {
        cout << "1. Mostrar salarios en orden descendente" << "\n";
        cout << "2. Salir" << "\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarDescendente();
                cout << "\n";
                break;
            case 2:
                cout << "Finalizando programa" << "\n";
                break;
            default:
                cout << "Opción incorrecta" << "\n";
                break;
        }
    } while (opcion != 2);

    return 0;
}
