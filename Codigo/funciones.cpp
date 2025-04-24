#include <iostream>
#include <QCoreApplication>
#include <usoimg.h>
using namespace std;


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
    ya sea rotando los bits hacia la derecha o hacia la izquierda una cantidad de i veces y retorna la imagen tranformada. */
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
    unsigned int size= ancho * alto * 3;
    for(unsigned int i = 0; i < (size) ; i ++){ //recorro todo el arreglo
        arr[i] = img_D[i] ^ img_M[i];
    }
}

void funcion_desplazamiento(unsigned char* img,unsigned char* arr,unsigned short int n,bool desplazamiento,int ancho,int alto ){
    /* la funcion mascara_desplazamiento recibe un arreglo con valores RGB de la imagen,
     * recibe un booleano (desplazamiento) si es true(1) se desplaza a la derecha y si es false(0) a la izquierda
     * y tambien un N que va a determinar que cantidad de bits es la que se esta realizando el desplazamiento
     */
    unsigned int size= ancho * alto * 3;
    for(unsigned int i = 0; i < (size) ; i ++){ //recorro todo el arreglo y lo desplazo
        if (desplazamiento){
            arr[i] = img[i]  >> n ;//desplazo n valores a la derecha
        }else{
            arr[i] = img[i]  << n ;//desplazo n valores a la izquierda
        }
    }

}

unsigned int* aplicacion_Mascara(unsigned char* Mascara, unsigned char* img_D, int anchoM, int altoM){  //DECIDIR SI PASAR LA SEMILLA COMO PARAMETRO SI SE VA A PASAR TODA LA IMAGEN
    size = anchoM * altoM * 3;
    unsigned int* arr = new int[size / 2];
    for(int i = 0;i < (size / 2);i++){
        arr[i] = img_D[i] + Mascara[i];
    }
    return arr; //Lo retorno para compararlo afuera
}

void comparar_txt(unsigned int* txt,unsigned int* mascara_aplicada){

}

int fucion_de_cambio(unsigned char* img_D,unsigned char* Mascara,int ancho,int alto){
    /* esta funcion recibe imagenes y las cambia y comprueba
     */
    QString imgM = "Im.bmp";
    unsigned int size= ancho * alto * 3;
    unsigned char *img_F = new unsigned char[size]; //Arreglo para guardar los resultados que iremos obteniendo
    unsigned char *img_M = loadPixels(imgM, ancho, alto);   //Arreglo que guarda la imagen mascara para los Xor

    F_xor(img_D, img_M, img_F, ancho, alto);

    if (M == M1){
        cout<<"la operacion es XOR"<<endl;

    }else{
        img_D = F_xor(img_D,img_M);
    }
    bool value = false;
    for(int i = 1; i < 8; i++){ // Comprueba rotaciones
        funcion_rotacion(s, img_F, i, true, ancho, alto);

        value = true;

        for(int t = 0; t < 12; t++){
            if(j[t] != img_F[t]){ //HAY QUE CAMBIAR EL ARREGLO J QUE ES CON EL QUE SE COMPARA EL RESULTADO
                value = false;
                break;
            }
        }
        if(value){
            cout << "Se hizo una rotacion de " << i<< " bits hacia la izquierda o " << (8 - i)<< " bits a la derecha\n";
            break;
        }
    }

    for(i=1;i<=8;i++){
        img_F = funcion_desplazamiento(img_D,img_F,i,1,ancho,alto);
        // para el desplazamiento en caso de usar mi propuesta se tiene que guardar los bits perdidos y
        //usar la mascara para volver al original
        M = img_D + Mascara;
        if(M == M1){
            cout << "La transformacion fue i desplazamiento a la derecha"<<endl;
            unsigned int size= ancho * alto * 3;
            for(unsigned int i = 0; i < (size) ; i ++){ //recorro todo el arreglo
                img_D[i] = img_F[i] ;
            }
        }else{
            img_D = img_D | mascara_desplazamiento(1,i);
        }
        img_D = funcion_desplazamiento(img_D,0,i);
        M = img_D + Mascara;
        if(M == M1){
            cout<< "La transformacion fue i desplazamiento a la izquierda"<<endl;
            return 0;
        }else{
            img_D = img_D | mascara_desplazamiento(0,i);
        }


    }
    delete[] img_F;
}
