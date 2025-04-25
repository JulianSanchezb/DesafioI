#include <QCoreApplication>
#include <funciones.h>
#include <usoimg.h>
#include <iostream>
#include <cstdio>

using namespace std;


int main()
{
    int altura, ancho,alturaM,anchoM,seed,n_pixel;
    QString archivoMascara = "M.bmp";
    QString imgD = "I_P.bmp";
    //QString imagen = "P2.bmp";
    //QString ruta = "C:/Users/Santiago/OneDrive/Escritorio/DesafíoI Publicar v2/DesafíoI/Caso 2";
    unsigned int* txt;
    unsigned short int p;
    unsigned char *Mascara = loadPixels(archivoMascara, anchoM, alturaM);
    unsigned char *imgP = loadPixels(imgD, ancho, altura);
    cout<< "Ingrese la cantidad de pasos"<<endl;
    cin >> p;
    for(unsigned short int i = p ;i >= 0 ;i--){
        char m[20]; // asegúrate de que el tamaño sea suficiente
        snprintf(m, sizeof(m), "M%d.txt", i);
        txt = loadSeedMasking(m,seed,n_pixel);
        cout<<m<<endl;
        fucion_de_cambio(imgP,Mascara,ancho,altura,txt,seed);
        if (i ==0){
            break;
        }
    }


    return 0;
}
