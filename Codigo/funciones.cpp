#include <iostream>
#include <QCoreApplication>
#include <usoimg.h>
#include <string>
#include <operaciones_bits.h>
using namespace std;

void aplicacion_Mascara(unsigned char* Mascara, unsigned char* img_D,unsigned int* arr){  //DECIDIR SI PASAR LA SEMILLA COMO PARAMETRO SI SE VA A PASAR TODA LA IMAGEN
    for(int i = 0;i < 15;i++){
        arr[i] = img_D[i] + Mascara[i];

    }
}

bool comparar_txt(unsigned int* txt,unsigned int* mascara_aplicada){
    unsigned short int j = 0;
    for (int i = 0;i< 15 ;i++){
        if(txt[i] == mascara_aplicada[i]){
            j ++ ;
        }else{
            break;
        }
    }
    if (j ==  15){
        return true;
    }else{
        return false;
    }
}

void seccion_img_original(unsigned char* img_o,unsigned char* img_porcion,int seed){
    for(unsigned int i = 0; i < 15; i ++){
        img_porcion[i] = img_o[seed + i];
    }
}

int fucion_de_cambio(unsigned char* img_D,unsigned char* Mascara,int ancho,int alto,unsigned int* txt,int seed){
    /* esta funcion recibe imagenes y las cambia y comprueba
     */
    QString imgM = "I_M.bmp";
    unsigned char img_F[15];    //Arreglo para guardar los resultados que iremos obteniendo
    unsigned char img_h[15];
    unsigned int img_pp[15];

    unsigned char *img_M = loadPixels(imgM, ancho, alto);//Arreglo que guarda la imagen mascara para los Xor
    unsigned short int c = 0;
    seccion_img_original(img_M,img_h,seed);
    seccion_img_original(img_D,img_F,seed);
    funcion_xor(img_F, img_h, img_F, 5, 1);
    aplicacion_Mascara(Mascara,img_F,img_pp);
    if (comparar_txt(txt,img_pp)){
        cout<<"la operacion es XOR"<<endl;
        funcion_xor(img_D, img_M, img_D, ancho, alto);
        delete[] img_M;
        return 0;
    }else{
        delete[] img_M;
    }
    seccion_img_original(img_D,img_F,seed);
    bool value = false;
    for(int i = 1; i < 8; i++){ // Comprueba rotaciones
        funcion_rotacion(img_F, img_h, i, true, 5, 1);
        aplicacion_Mascara(Mascara,img_h,img_pp);
        value = true;
        for(int t = 0; t < 15; t++){
            if(txt[t] != img_pp[t]){
                value = false;
                break;
            }
        }
        if(value){
            cout << "Se hizo una rotacion de " << i << " bits hacia la izquierda o " << (8 - i)<< " bits a la derecha\n";
            funcion_rotacion(img_D,img_D,i,true,ancho,alto);
            break;
        }
    }

    for(unsigned short int i=1;i<8;i++){ //comprueba el desplazamiento
        funcion_desplazamiento(img_F,img_h,i,1,5,1);
        //aplicacion_Mascara(Mascara,img_h,img_pp);
        for (unsigned short int k = 0 ; k<15 ; k ++){
            if(recuperar_con_mascara(img_h[k],i,txt[k],0,Mascara[k])){
                c ++;
            }else{
                break;
            }
        }
        if (c == 15){
            cout<<"El desplazamiento fue de "<<(8-i)<<" hacia la derecha"<<endl;
            funcion_desplazamiento(img_D,img_D,i,0,ancho,alto);
            return 0;
        }
        c= 0;
        funcion_desplazamiento(img_F,img_h,i,0,5,1);
        for (unsigned short int k = 0 ; k<15 ; k ++){
            if(recuperar_con_mascara(img_h[k],(8-i),txt[k],1,Mascara[k])){
                c ++;
            }else{
                break;
            }
        }
        if (c == 15){
            cout<<"El desplazamiento fue de "<<(8-i)<<" hacia la izquierda"<<endl;
            funcion_desplazamiento(img_D,img_D,(8-i),1,ancho,alto);
            return 0;
        }
        c =  0;
    }
    return 0;
}
