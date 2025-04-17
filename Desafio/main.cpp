#include <iostream>
#include <Funciones.cpp>
using namespace std;


int main(){
    unsigned char img[3] = {'r','g','b'};
    int ancho = 1, alto = 1;
    funcion_rotacion(img,3,true,ancho,alto);

    for(int i = 0;i< ancho * alto * 3;i++){
        cout<<img[i]<<endl;
    }
    return 0;
}
