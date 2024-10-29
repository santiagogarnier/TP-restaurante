#include<iostream>
#include<cstring>
#include<fstream>

using namespace std;

struct Mesas {
    int numero_mesa;
    bool esta_libre;
    int ganancias_acumuladas;
};

int main(){
    Mesas mesa;
}

void cargarMesa (Mesas mesa[] ){
     Mesas mesa;
     bool esta_libre = false;
    FILE* archivo=fopen("archivo.dat", "rb");
    if(archivo != NULL){
      while (fread (&mesa, sizeof(Mesas),1,archivo)==1)
      {
        cout <<"Ingrese el numero de la mesa:"<<endl;
        cin >> mesa->numero_mesa;
        
      }
      
    }
    
}