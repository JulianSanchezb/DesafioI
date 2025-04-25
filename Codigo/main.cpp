#include <QCoreApplication>
#include <funciones.h>
#include <usoimg.h>
#include <iostream>

using namespace std;


int main()
{
    int altura, ancho,alturaM,anchoM,seed,n_pixel;
    QString archivoMascara = "M.bmp";
    QString imgD = "I_D.bmp";
    QString imagen = "P2.bmp";
    //const string ruta = "ruta/a/tu/carpeta";
    const char* txt_ar = "M2.txt";
    unsigned char *Mascara = loadPixels(archivoMascara, anchoM, alturaM);
    unsigned char *imgP = loadPixels(imgD, ancho, altura);
    unsigned int *txt = loadSeedMasking(txt_ar,seed,n_pixel);
    fucion_de_cambio(imgP,Mascara,ancho,altura,txt,seed);
    txt_ar = "M1.txt";
    txt = loadSeedMasking(txt_ar,seed,n_pixel);
    fucion_de_cambio(imgP,Mascara,ancho,altura,txt,seed);
    txt_ar = "M0.txt";
    txt = loadSeedMasking(txt_ar,seed,n_pixel);
    fucion_de_cambio(imgP,Mascara,ancho,altura,txt,seed);
    exportImage(imgP,ancho,altura,imagen);





    return 0;
}
