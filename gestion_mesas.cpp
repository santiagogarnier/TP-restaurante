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

bool estaLibre(int numero_mesa);

int main()
{
  Mesas mesa;
  system("pause");
}


Mesas mesa()
{
  Mesas mesa;
  bool estaLibre;
  int gananciasAcumuladas;

  cout << "Ingrese el numero de la mesa: " << endl;
  cin >> mesa.numero_mesa;
}

bool estaLibre(int numero_mesa)
{
  Mesas mesa;
  bool libre = false;

  FILE *archivo = fopen("mesas.dat", "rb");
  if (archivo != NULL)
  {
    while (fread(&mesa, sizeof(Mesas), 1, archivo) == 1)
    {
      if (mesa.numero_mesa == numero_mesa)
      {
        libre = true;
        break;
      }
    }
    fclose(archivo);
  }

  if (libre)
  {
    cout << "La mesa numero " << mesa.numero_mesa << " esta ocupada. " << endl;
  }
  else
  {
    cout << "La mesa numero " << mesa.numero_mesa << " esta libre. " << endl;
  }
  return libre;
}