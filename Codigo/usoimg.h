#include <QCoreApplication>
#ifndef USOIMG_H
#define USOIMG_H


unsigned char* loadPixels(QString input, int &width, int &height);
bool exportImage(unsigned char* pixelData, int width,int height, QString archivoSalida);
unsigned int* loadSeedMasking(const char* nombreArchivo, int &seed, int &n_pixels);

#endif // USOIMG_H
