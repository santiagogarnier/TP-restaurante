#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

struct Mesas
{
    int numero_mesa;
    bool esta_libre;
    int ganancias_acumuladas;
    char nombreCliente[50]; // campo p guardar el nombre del cliente, sin esto no asignaba bien las mesas
};

struct NodoCliente
{
    char nombre[50];
    NodoCliente *siguiente;
};

//PROTOTIPO DE FUNCIONES
void cargarMesas(Mesas mesa[]);
void ingresaCliente(Mesas mesa[], NodoCliente *&frente, NodoCliente *&final);
void actualizarGanancia(Mesas mesa[]);
void liberarMesa(Mesas mesa[], NodoCliente *&frente, NodoCliente *&final);
void guardarMesas(Mesas mesa[]);
void encolar(NodoCliente *&frente, NodoCliente *&final, char nombre[50]);
void desencolar(NodoCliente *&frente, NodoCliente *&final, char nombre[50]);

int main()
{
    Mesas mesa[15];
    NodoCliente *frente = NULL;
    NodoCliente *final = NULL;

    cargarMesas(mesa);

    int opcion;
    do
    {
        cout << "\nMenu de opciones:\n";
        cout << "1. Asignar cliente a una mesa\n";
        cout << "2. Actualizar ganancia de una mesa\n";
        cout << "3. Guardar cambios\n";
        cout << "4. Liberar mesa\n";
        cout << "5. Salir\n";
        cout << "Elija una opcion: ";
        cin >> opcion;
        system("cls");
        switch (opcion)
        {
        case 1:
            ingresaCliente(mesa, frente, final);
            break;
        case 2:
            actualizarGanancia(mesa);
            break;
        case 3:
            guardarMesas(mesa);
            break;
        case 4:
            liberarMesa(mesa, frente, final);
            break;
        case 5:
            cout << "Saliendo del menu...\n";
            break;
        default:
            cout << "Opcion invalida..\n";
        }
    } while (opcion != 5);

    return 0;
}

//Funcion que carga las mesas iniciales desde el archivo
void cargarMesas(Mesas mesa[])
{
    for (int i = 0; i < 15; i++)
    {
        mesa[i].numero_mesa = i + 1;
        mesa[i].esta_libre = true;
        mesa[i].ganancias_acumuladas = 0;
        strcpy(mesa[i].nombreCliente, "");
    }

    FILE *archivo = fopen("mesas.dat", "wb");
    if (archivo)
    {
        fwrite(mesa, sizeof(Mesas), 15, archivo);
        fclose(archivo);
    }
}

/*esto se encarga de asignar los clientes o a la mesa o a la cola d espera */
void ingresaCliente(Mesas mesa[], NodoCliente *&frente, NodoCliente *&final)
{
    char nombre[50];
    cout << "Ingrese el nombre del cliente: ";
    cin >> nombre;
    /*esta seccion busca la primera mesa libre y se la asigna*/
    bool mesaAsignada = false;
    for (int i = 0; i < 15; i++)
    {
        if (mesa[i].esta_libre)
        {
            mesa[i].esta_libre = false;
            strcpy(mesa[i].nombreCliente, nombre);
            cout << "La mesa nro: " << mesa[i].numero_mesa << " esta ahora ocupada por " << nombre << endl;
            mesaAsignada = true;
            break;
        }
    }
    //En caso de que ya no haya mesas libres, encola al siguiente cliente que quiera sentarse
    if (!mesaAsignada)
    {
        encolar(frente, final, nombre);
        cout << "Cliente " << nombre << " agregado en la cola de espera.\n";
    }
}
/*actualiza las ganancias d la mesa especifica q le digas: */
void actualizarGanancia(Mesas mesa[])
{
    int numeroDeMesa, ganancia;
    cout << "Ingrese el numero de mesa: ";
    cin >> numeroDeMesa;

    if (numeroDeMesa < 1 || numeroDeMesa > 15 || mesa[numeroDeMesa - 1].esta_libre)
    {
        cout << "La mesa no esta siendo ocupada por nadie.\n";
        return;
    }

    cout << "Ingrese la ganancia a agregar: ";
    cin >> ganancia;
    mesa[numeroDeMesa - 1].ganancias_acumuladas += ganancia;
    cout << "Ganancia actualizada. Ganancia acumulada de la mesa " << numeroDeMesa << " es: " << mesa[numeroDeMesa - 1].ganancias_acumuladas << endl;
}

//Funcion que se encarga de liberar la mesa elegida segun su numero
void liberarMesa(Mesas mesa[], NodoCliente *&frente, NodoCliente *&final)
{
    int numeroDeMesa;
    cout << "Ingrese el numero de mesa a liberar: ";
    cin >> numeroDeMesa;

    if (numeroDeMesa < 1 || numeroDeMesa > 15 || mesa[numeroDeMesa - 1].esta_libre)
    {
        cout << "Numero de mesa invalido o ya esta libre.\n";
        return;
    }

    mesa[numeroDeMesa - 1].esta_libre = true;
    strcpy(mesa[numeroDeMesa - 1].nombreCliente, "");
    cout << "Mesa " << numeroDeMesa << " liberada.\n";
    // si hay cola, asigna el primero a esta mesa:
    if (frente != NULL)
    {
        char nombreCliente[50];
        desencolar(frente, final, nombreCliente);
        mesa[numeroDeMesa - 1].esta_libre = false;
        strcpy(mesa[numeroDeMesa - 1].nombreCliente, nombreCliente);
        cout << "Cliente " << nombreCliente << " asignado a la mesa " << numeroDeMesa << " desde la cola de espera.\n";
    }
}
// este void guarda la info actual d las mesas en uso en el archivo:
void guardarMesas(Mesas mesa[])
{
    FILE *archivo = fopen("mesas.dat", "wb");
    if (archivo)
    {
        fwrite(mesa, sizeof(Mesas), 15, archivo);
        fclose(archivo);
        cout << "Datos de las mesas guardados en el archivo.\n";
    }
    else
    {
        cout << "Error al guardar en el archivo.\n";
    }
}
// Funcion para encolar al cliente a una lista de espera

void encolar(NodoCliente *&frente, NodoCliente *&final, char nombre[50])
{
    NodoCliente *nuevoCliente = new NodoCliente;
    strcpy(nuevoCliente->nombre, nombre);
    nuevoCliente->siguiente = NULL;

    if (final != NULL)
    {
        final->siguiente = nuevoCliente;
    }
    else
    {
        frente = nuevoCliente;
    }
    final = nuevoCliente;
}
//Funcion para liberar los clientes que ocuapan el numero de una mesa
void desencolar(NodoCliente *&frente, NodoCliente *&final, char nombre[50])
{
    if (frente == NULL)
        return;

    NodoCliente *aux = frente;
    strcpy(nombre, frente->nombre);
    frente = frente->siguiente;

    if (frente == NULL)
    {
        final = NULL;
    }

    delete aux;
}
