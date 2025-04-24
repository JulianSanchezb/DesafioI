#include <QCoreApplication>
#include <funciones.h>
#include <usoimg.h>
#include <iostream>

using namespace std;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    int altura, ancho,alturaM,anchoM;
    QString archivoMascara = "M.bmp";
    QString imgD = ".bmp";
    unsigned char *Mascara = loadPixels(archivoMascara, anchoM, alturaM);
    unsigned char *imgP = loadPixels(imgD, ancho, altura);

    for(int i = 0;i < n;i++){
        fucion_de_cambio(img_D,Mascara,ancho, alto);
    }

    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    return 0;
}
