#ifndef FUNCIONES_H
#define FUNCIONES_H

int fucion_de_cambio(unsigned char* img_D,unsigned char* Mascara,int ancho,int alto,unsigned int* txt,int seed);
bool comparar_txt(unsigned int* txt,unsigned int* mascara_aplicada);
void aplicacion_Mascara(unsigned char* Mascara, unsigned char* img_D,unsigned int* arr);
void seccion_img_original(unsigned char* img_o,unsigned char* img_porcion,int seed);


#endif // FUNCIONES_H
