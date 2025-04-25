#include <iostream>
#include <QCoreApplication>
#include <usoimg.h>
#include <string>
#include <filesystem> // verificar posibilidad de uso
using namespace std;

bool recuperar_con_mascara(unsigned char desplazado, int n, unsigned int original,bool desplazamiento) {
    int total = 1 << n;
    for (int i = 0; i < total; ++i) {
        unsigned char mascara = 0;

        // Ahora colocamos los bits perdidos en las posiciones correctas (desde la izquierda)
        if (desplazamiento){
            for (int bit = 0; bit < n; ++bit) {
                if (i & (1 << bit)) {
                    int pos = 7 - bit; // para que bit 0 vaya a 7, 1 a 6, 2 a 5, etc.
                    mascara |= (1 << pos);
                }
            }
        }else{
            // Ahora colocamos los bits perdidos en las posiciones de derecha a izquierda
            for (int bit = 0; bit < n; ++bit) {
                if (i & (1 << bit)) {
                    int pos = bit; // bit 0 va a posición 0, bit 1 a 1, etc.
                    mascara |= (1 << pos);
                }
            }
        }


        unsigned char resultado = desplazado | mascara;
        if (resultado == original) {
            //cout << (int)resultado <<endl;
            cout <<(int)resultado << ": "<<static_cast<int>(mascara)<< "n:" <<n << endl;
            return true;
        }
    }
    return false;
}


unsigned char mascara_desplazamiento(bool desplazamiento,unsigned short int N){
    /* la funcion mascara_desplazamiento recibe un boolena (desplazamiento) si es true(1) se desplaza a la derecha y si es false(0) a la izquierda
     * y tambien un N que va a determinar que cantidad de bits es la que se esta realizando el desplazamiento
     * esto para definir una mascara que  tenga N cantidad de 1 y el resto cero
     */
    unsigned char mascara;
    if (desplazamiento){ // uso de unsigned char dado que nuestros valores son de exactamente 8 bits y la capacidad de este es de exactamente 8 bits
        mascara = (1 << N) - 1;
    }else{
        mascara = ((1 << N) - 1) << (8 - N); //
    }
    return mascara;
}


void funcion_rotacion(unsigned char* img,unsigned char* arr,unsigned short int n,bool desplazamiento,int ancho,int alto){
    /*Esta función recibe un arreglo con valores RGB de la imagen (img)y recibe la cantidad de bits que se roto(n).
    La función realiza una rotación de bits en los valores de cada píxel,
    ya sea rotando los bits hacia la derecha o hacia la izquierda una cantidad de i veces y retorna la imagen tranformada.*/
    unsigned char num;
    unsigned char mask = mascara_desplazamiento(desplazamiento,n);
    int size = ancho * alto * 3;
    for(int i = 0; i < size; i++){
        num = img[i];
        unsigned char temp_mask = num & mask;
        if(desplazamiento){
            num = num >> n;
            temp_mask = temp_mask << (8-n);
        }else{
            num = num << n;
            temp_mask = temp_mask >> (8-n);
        }
        arr[i] = num |temp_mask;
    }
}

void funcion_xor(unsigned char* img_D,unsigned char* img_M,unsigned char* arr,int ancho,int alto){
    //esta funcion aplica la operacion xor a dos arreglos
    unsigned int size= ancho * alto * 3 ;
    for(unsigned int i = 0; i < (size) ; i ++){ //recorro todo el arreglo
        arr[i] = img_D[i] ^ img_M[i];

    }
}

void funcion_desplazamiento(unsigned char* img,unsigned char* arr,unsigned short int n,bool desplazamiento,int ancho,int alto ){
    /* la funcion mascara_desplazamiento recibe un arreglo con valores RGB de la imagen,
     * recibe un booleano (desplazamiento) si es true(1) se desplaza a la derecha y si es false(0) a la izquierda
     * y tambien un N que va a determinar que cantidad de bits es la que se esta realizando el desplazamiento
     */
    unsigned int size= ancho * alto ;
    for(unsigned int i = 0; i < (size) ; i ++){ //recorro todo el arreglo y lo desplazo
        if (desplazamiento){
            arr[i] = img[i]  >> n ;//desplazo n valores a la derecha
        }else{
            arr[i] = img[i]  << n ;//desplazo n valores a la izquierda
        }
    }

}

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
    cout<<img_D[0]<<endl;
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
        seccion_img_original(img_D,img_F,seed);
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

    for(unsigned short int i=1;i<=8;i++){ //comprueba el desplazamiento
        funcion_desplazamiento(img_D,img_F,i,1,5,1);
        aplicacion_Mascara(Mascara,img_F,img_pp);
        for (unsigned short int k = 0 ; k<15 ; k ++){
            if(recuperar_con_mascara(img_F[k],k,txt[k],1)){
                c ++;
            }else{
                break;
            }
        }
        if (c == 15){
            cout<<"El despalzamiento fue de "<<i<<" hacia la izquierda"<<endl;
            funcion_desplazamiento(img_D,img_D,i,1,ancho,alto);
            return 0;
        }
        for (unsigned short int k = 0 ; k<15 ; k ++){
            if(recuperar_con_mascara(img_F[k],k,txt[k],0)){
                c ++;
            }else{
                break;
            }
        }
        if (c == 15){
            cout<<"El despalzamiento fue de "<<i<<" hacia la derecha"<<endl;
            funcion_desplazamiento(img_D,img_D,i,1,ancho,alto);
            return 0;
        }
    }
    return 0;
}
