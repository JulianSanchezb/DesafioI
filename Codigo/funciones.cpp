#include <iostream>
#include <usoimg.h>
#include <operaciones_bits.h>

using namespace std;

void aplicacion_Mascara(unsigned char* Mascara, unsigned char* img_D,unsigned int* arr){
    /*Esta funcion recibe dos arreglo con los datos de una imagen cada uno, suma los valores de cada una de sus posiciones y
     * los guarda en otro arreglo*/

    for(unsigned short int i = 0;i < 15;i++){
        arr[i] = img_D[i] + (*(Mascara + i));
    }
}

bool comparar_txt(unsigned int* txt,unsigned int* mascara_aplicada){
    /*Esta funcion recibe un arreglo con datos de un txt y un arreglo con los datos de una imagen con una mascara aplicada
     * y compara si son iguales ambos arreglos
     */
    unsigned short int j = 0;
    for (unsigned short int i = 0;i< 15 ;i++){
        if(*(txt + i) == mascara_aplicada[i]){
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
    /*Esta funcion recibe un arreglo con los datos de una imagen y almacena una parte de la imagen, desde una posicion semilla
     *en un arreglo mas pequeño*/
    for(unsigned short int i = 0; i < 15; i ++){
        img_porcion[i] = img_o[seed + i];
    }
}

int fucion_de_cambio(unsigned char* img_D,unsigned char* Mascara,int ancho,int alto,unsigned int* txt,int seed){
    /* Esta funcion recibe un arreglo con los datos de una imagen, un arreglo con los datos de una mascara, alto y ancho de la imagen,
     * un arreglo con los datos de un txt y un numero entero que es la posicion en la que se aplico la mascara
     * Hace pruebas para verificar que transformacion se necesita para regresar la imagen a un estado antes de una transformacion y aplica
     * dicha transformacion
     */
    QString imgM = "I_M.bmp";
    unsigned char img_F[15];    //Arreglo para almacenar seccion de la img_D
    unsigned char img_h[15];    //Arreglo para almacenar seccion de img_M y despues para almacenar transformaciones en img_F
    unsigned int img_pp[15];    //Arreglo para almacenar datos de la mascara aplicada a img_F

    unsigned char *img_M = loadPixels(imgM, ancho, alto);   //Arreglo que almacena la imagen mascara para los Xor
    unsigned short int c = 0;

    seccion_img_original(img_M,img_h,seed);
    seccion_img_original(img_D,img_F,seed);
    funcion_xor(img_F, img_h, img_F, 5, 1);
    aplicacion_Mascara(Mascara,img_F,img_pp);

    if (comparar_txt(txt,img_pp)){  //Comparamos si los datos de la imagen con la mascara aplicada coinciden con los del txt
        cout<<"La operacion fue XOR"<<endl;
        funcion_xor(img_D, img_M, img_D, ancho, alto);  //Se le aplica el XOR a toda la imagen
        delete[] img_M; //Liberamos la memoria reservada para almacenar la imagen mascara

        return 0;

    }else{
        delete[] img_M; //Liberamos la memoria reservada para almacenar la imagen mascara
    }

    seccion_img_original(img_D,img_F,seed);

    bool value = false;

    for(unsigned short int i = 1; i < 8; i++){ // Comprueba rotaciones

        funcion_rotacion(img_F, img_h, i, true, 5, 1);
        aplicacion_Mascara(Mascara,img_h,img_pp);
        value = comparar_txt(txt,img_pp);

        if(value){
            cout << "Se hizo una rotacion de " << i << " bits hacia la izquierda o " << (8 - i)<< " bits a la derecha\n";

            funcion_rotacion(img_D,img_D,i,true,ancho,alto);    //Se rota toda la imagen con la cantidad de bits encontrada

            return 0;
        }
    }

    for(unsigned short int i=1;i<8;i++){ //Comprueba el desplazamiento

        funcion_desplazamiento(img_F,img_h,i,1,5,1);

        for (unsigned short int k = 0 ; k<15 ; k ++){

            if(recuperar_con_mascara(img_h[k],i,*(txt + k),0,*(Mascara + k))){  //Se compara valor a valor con el txt

                c ++;

            }else{

                break;

            }
        }

        if (c == 15){   //Cuando c es igual a 15 es por que todos los valores de la seccion coincidieron con el txt

            cout<<"El desplazamiento fue de "<<(8-i)<<" hacia la derecha"<<endl;

            funcion_desplazamiento(img_D,img_D,i,0,ancho,alto); //Se desplaza la cantidad de bits encontrada hacia la izquierda

            //direccion = true;
            //bits = 8 - i;

            return 0;
        }

        c= 0;

        funcion_desplazamiento(img_F,img_h,i,0,5,1);

        for (unsigned short int k = 0 ; k<15 ; k ++){

            if(recuperar_con_mascara(img_h[k],(8-i),*(txt + k),1,*(Mascara + k))){//Se compara valor a valor con el txt

                c ++;

            }else{

                break;

            }
        }

        if (c == 15){   //Cuando c es igual a 15 es por que todos los valores de la seccion coincidieron con el txt

            cout<<"El desplazamiento fue de "<<(8-i)<<" hacia la izquierda"<<endl;

            funcion_desplazamiento(img_D,img_D,(8-i),1,ancho,alto); //Se desplaza la cantidad de bits encontrada hacia la derecha

            //direccion = false;
            //bits = 8 - i;

            return 0;
        }

        c =  0;
    }

    return 1;
}
