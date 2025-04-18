#include <iostream>
#include <Funciones.cpp>
using namespace std;


int main(){
    unsigned char img[3] = {114,103,98};
    int ancho = 1, alto = 1;
    funcion_desplazamiento(img,3,false,ancho,alto);
    for(int i = 0;i< ancho * alto * 3;i++){
        cout<<img[i]<<endl;
    }
    return 0;
}
