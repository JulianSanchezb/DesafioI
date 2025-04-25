#ifndef FUNCIONES_H
#define FUNCIONES_H

unsigned char mascara_desplazamiento(bool desplazamiento,unsigned short int N);
void funcion_rotacion(unsigned char* img,unsigned char* arr,unsigned short int n,bool desplazamiento,int ancho,int alto);
void funcion_xor(unsigned char* img_D,unsigned char* img_M,unsigned char* arr,int &ancho,int &alto);
void funcion_desplazamiento(unsigned char* img,unsigned char* arr,unsigned short int n,bool desplazamiento,int ancho,int alto );
int fucion_de_cambio(unsigned char* img_D,unsigned char* Mascara,int ancho,int alto,unsigned int* txt,int seed);
//void numeroDePaso(unsigned short int i, string& m);
//unsigned short int numerodepasos(const string& carpeta);
bool recuperar_con_mascara(unsigned char desplazado, int n, unsigned int original,bool desplazamiento);
bool comparar_txt(unsigned int* txt,unsigned int* mascara_aplicada);
void aplicacion_Mascara(unsigned char* Mascara, unsigned char* img_D,unsigned int* arr);
void seccion_img_original(unsigned char* img_o,unsigned char* img_porcion,int seed);


#endif // FUNCIONES_H
