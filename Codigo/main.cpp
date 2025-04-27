#include <funciones.h>
#include <usoimg.h>
#include <operaciones_bits.h>
#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    int altura, ancho, alturaM, anchoM, seed, n_pixel;
    //unsigned short int bits = 0;
    //bool direccion = false;
    QString archivoMascara = "M.bmp";
    QString imgD = "I_D.bmp";
    QString imagen = "I_O.bmp";

    unsigned int* txt;
    unsigned short int p;
    unsigned char *imgP = loadPixels(imgD, ancho, altura);

    if (!imgP) {
        cerr << "Error: No se pudo cargar la imagen " << imgD.toStdString() << endl;
        return -1;
    }

    unsigned char *Mascara = loadPixels(archivoMascara, anchoM, alturaM);

    if (!Mascara) {
        cerr << "Error: No se pudo cargar la mascara " << archivoMascara.toStdString() << endl;
        delete[] imgP;
        return -1;
    }

    //unsigned char aux[15];

    cout<< "Ingrese la cantidad de pasos"<<endl;
    cin >> p;

    for(unsigned short int i = p ;i >= 0 ;i--){

        char m[20];
        snprintf(m, sizeof(m), "M%d.txt", i);
        txt = loadSeedMasking(m,seed,n_pixel);

        /*if(bits != 0){
            for(int j = 0;j < 15;j++){
                aux[j] = txt[j] - Mascara[j];
            }
            funcion_desplazamiento(aux, aux, bits, direccion, 5, 1);
            aplicacion_Mascara(Mascara, aux, txt);
            funcion_desplazamiento(imgP, imgP, bits, direccion, ancho, altura);
        }*/

        cout<<"\nPaso: "<<i + 1<<endl;

        if(fucion_de_cambio(imgP, Mascara, ancho, altura, txt, seed) != 0){
            cout<<"No se hizo ninguna transformacion\n";
        }

        if (i == 0){
            break;
        }

        if(txt){
            delete[] txt;
        }

    }

    delete[] Mascara;

    exportImage(imgP,ancho,altura,imagen);
    delete[] imgP;

    return 0;
}
