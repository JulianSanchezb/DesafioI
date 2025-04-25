#ifndef OPERACIONES_BITS_H
#define OPERACIONES_BITS_H

unsigned char mascara_desplazamiento(bool desplazamiento,unsigned short int N);
void funcion_rotacion(unsigned char* img,unsigned char* arr,unsigned short int n,bool desplazamiento,int ancho,int alto);
void funcion_xor(unsigned char* img_D,unsigned char* img_M,unsigned char* arr,int ancho,int alto);
void funcion_desplazamiento(unsigned char* img,unsigned char* arr,unsigned short int n,bool desplazamiento,int ancho,int alto );
bool recuperar_con_mascara(unsigned char desplazado, int n, unsigned int original,bool desplazamiento,unsigned int masca);
#endif // OPERACIONES_BITS_H
