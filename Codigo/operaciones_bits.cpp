#include <iostream>
using namespace std;

bool recuperar_con_mascara(unsigned char desplazado, int n, unsigned int original,bool desplazamiento,unsigned int masca) {

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


        unsigned int resultado = desplazado | mascara;
        resultado += masca;
        if (resultado == original) {
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
    unsigned int size= ancho * alto * 3;
    for(unsigned int i = 0; i < (size) ; i ++){ //recorro todo el arreglo y lo desplazo
        if (desplazamiento){
            arr[i] = img[i]  >> n ;//desplazo n valores a la derecha
        }else{
            arr[i] = img[i]  << n ;//desplazo n valores a la izquierda
        }
    }

}

