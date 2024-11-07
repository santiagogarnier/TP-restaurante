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

int main()
{
    Mesas mesa[15];
    for (int i = 0; i <= 14; i++)
    {
        mesa[i].numero_mesa = i + 1;
        mesa[i].esta_libre = false;
        mesa[i].ganancias_acumuladas = 0;
    }

    FILE *archivo = fopen("mesas.dat", "wb");
    fwrite(mesa, sizeof(Mesas), 15, archivo);
    
}

