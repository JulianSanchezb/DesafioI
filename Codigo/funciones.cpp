#include <iostream>
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

void funcion_rotacion(unsigned char* img,unsigned char* arr,unsigned short int n,bool desplazamiento,int &ancho,int &alto){
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

void funcion_xor(unsigned char* img_D,unsigned char* img_M,unsigned char* arr,int &ancho,int &alto){
    //esta funcion aplica la operacion xor a dos arreglos
    unsigned int size= ancho * alto * 3;
    for(unsigned int i = 0; i < (size) ; i ++){ //recorro todo el arreglo
        arr[i] = img_D[i] ^ img_M[i];
    }
}

void funcion_desplazamiento(unsigned char* img,unsigned char* arr,unsigned short int n,bool desplazamiento,int &ancho,int &alto ){
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

int fucion_de_cambio(unsigned char* img_D,unsigned char* img_M,const char* M1,const char* M,unsigned char* Mascara,int &ancho,int &alto){
    /* esta funcion recibe imagenes y las cambia y comprueba
     */
    unsigned int size= ancho * alto * 3;
    unsigned char *img_F = new unsigned char[size];

    img_F = F_xor(img_D,img_M);
    M = img_D + Mascara; // S(k) = ID(k + s) + M(k) para 0 ≤ k < i × j × 3
    if (M == M1){
        cout<<"la operacion es XOR"<<endl;
        return o;
    }else{
        img_D = F_xor(img_D,img_M);
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
        img_D = funcion_rotacion(img_D,i,1);
        M = img_D + Mascara;
        if(M == M1){
            cout<< "La transformacion fue i rotacion a la derecha"<<endl;
            return 0;
        }else{
            img_D = funcion_rotacion(img_D,i,0);
        }
        img_D = funcion_rotacion(img_D,i,0);
        M = img_D + Mascara;
        if(M == M1){
            cout<< "La transformacion fue i rotacion a la izquierda"<<endl;
            return 0;
        }else{
            img_D = funcion_rotacion(img_D,i,0);
        }

    }
    delete[] img_F;
}
