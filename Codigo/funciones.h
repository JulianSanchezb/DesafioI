#ifndef FUNCIONES_H
#define FUNCIONES_H

unsigned char mascara_desplazamiento(bool desplazamiento,unsigned short int N);
void funcion_rotacion(unsigned char* img,unsigned char* arr,unsigned short int n,bool desplazamiento,int &ancho,int &alto);
void funcion_xor(unsigned char* img_D,unsigned char* img_M,unsigned char* arr,int &ancho,int &alto);
void funcion_desplazamiento(unsigned char* img,unsigned char* arr,unsigned short int n,bool desplazamiento,int &ancho,int &alto );
int fucion_de_cambio(unsigned char* img_D,unsigned char* img_M,const char* M1,const char* M,unsigned char* Mascara,int &ancho,int &alto);

#endif // FUNCIONES_H
