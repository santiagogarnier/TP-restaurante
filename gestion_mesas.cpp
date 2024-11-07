#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

struct Mesas
{
  int numero_mesa;
  bool esta_libre;
  int ganancias_acumuladas;
};
void cargarMesas(Mesas mesa[]);
void ingresaCliente();
void actualizarGanancia(Mesas mesa[]);
int main()
{
  Mesas mesa[15];
  cargarMesas(mesa);
  ingresaCliente();
  actualizarGanancia(mesa);
  for (int i = 0; i <= 14; i++)
  {
    cout << mesa[i].numero_mesa << endl;
    cout << mesa[i].ganancias_acumuladas << endl;
  }
}

void cargarMesas(Mesas mesa[])
{
  Mesas aux;
  int i = 0;
  FILE *archivo = fopen("mesas.dat", "rb");
  if (archivo != NULL)
  {
    while (fread(&aux, sizeof(Mesas), 1, archivo) == 1)
    {
      if (i <= 14)
      {
        mesa[i] = aux;
        i++;
      }
      else
      {
        break;
      }
    }
  }
}

void ingresaCliente()
{

  FILE *archivo = fopen("mesas.dat", "rb");
  if (archivo != NULL)
  {
    Mesas mesa;
    while (fread(&mesa, sizeof(Mesas), 1, archivo) == 1)
    {
      if (mesa.esta_libre == 0)
      {
        cout << "la mesa nro: " << mesa.numero_mesa << " esta ocupada" << endl;
      }
      else if (mesa.esta_libre == 1)
      {
        cout << "la mesa nro: " << mesa.numero_mesa << " esta libre" << endl;
      }

      // parte 1
      //  informo si hay alguna mesa disponible
      //  modifico el archivo cambiando la primera mesa libre en ocupada
      //  una vez modificado, vuelvo a informar los estados de las mesas
    }
    fclose(archivo);
  }
  else
  {
    cout << "error" << endl;
  }
}

void actualizarGanancia(Mesas mesa[])
{
  FILE *archivo = fopen("mesas.dat", "rb");
  if (archivo != NULL)
  {
    Mesas aux;
    while (fread(&aux,sizeof(Mesas),1,archivo) == 1)
    {
      for (int i = 0; i <= 14; i++)
      {
        cout << "Ingrese la ganancia acumulada de la mesa: "<< mesa[i].numero_mesa<<endl;
        cin >> mesa[i].ganancias_acumuladas;
        cout << "La ganancia de  la mesa "<<mesa[i].numero_mesa << " es: "<<mesa[i].ganancias_acumuladas<<endl;
      }
      
    }
    fclose(archivo);
  }
}
// Ahora deberia cargar el archivo con el numero de la mesa
// 2.1 Recorrer el array por cada posicion del array evaluar con un if si esta libre.
// Si esta libre poner una flag = 1 y una variable numeroMesa que guarde el valor de la mesa
//* Poner un break en el if para que guarde la primera mesa disponible */
// despues del for evaluo si la flag es 1 o 0, si es 1 la mesa esta libre, si el flag es 0, todo esta ocupado
// Si todo esta ocupado, hago la logica de la cola
/*--2.2. Para el tercer puntito es un pop, se desocupa una mesa y la asigno
 */
/*--2.3 Es ir cargando el array en el archivo. Recorro uno por uno en el array */
/*Mesas mesa(int numero_mesa)
{
}
bool estaLibre(Mesas mesa[], int numero_mesa)
{
  Mesas mesa;
  bool estaLibre = false;

  FILE *archivo = fopen("mesas.dat", "rb");
  if (archivo != NULL)
  {
    while (fread(&mesa, sizeof(Mesas), 1, archivo) == 1)
    {
      if (mesa->numero_mesa == numero_mesa)
      {
        estaLibre = true;
        break;
      }
    }
    fclose(archivo);
  }
  if (estaLibre)
  {
    cout << "La mesa " << numero_mesa << "se encuentra ocupada " << endl;
    cout << " La mesa " << numero_mesa << "esta libre, puede sentarse" << endl;

    return estaLibre;
  }
}

void ganAcumuladas(Mesas mesa[], int gananciasAcumuladas)
{
  gananciasAcumuladas = 0;

  for (int i = 1; i < mesa[i].numero_mesa; i++)
  {
    cout << "Ingrese la ganancia acumulada de la mesa " << mesa[i].numero_mesa << endl;
    cin >> gananciasAcumuladas;
  }
}


 void imprimirMesas(Mesas mesa[], int& cantidadMesas){
 for (int i = 1; i < cantidadMesas; i++)
 {
  cout << "Mesa nro " << mesa[i].numero_mesa << endl;
  cout << "-- Estado de la mesa" << mesa[i].esta_libre<< endl;
  cout << "-- La ganancia acumulada para la mesa "<< mesa[i].numero_mesa << " es de $ "<< endl;//mesa[i].ganancias_acumuladas?;

 }

}*/
