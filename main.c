#include "libreria.h"

int main(int argc, char *argv[]){

    Dic *raiz= crear_Dic('\0');
    int flag=0,pos,i,j;
    char input[30],cadena[80],palabra[30],palabra2[30],tipo,*nombre;
    FILE *f;
    f=fopen("nombre.dic","rt");
        while (!feof(f)){
            if (!feof(f)){
                fgets(cadena,80,f);
                tipo=cadena[0];
                    for(i=2; cadena[i] != ' '; i++){
                        strncat(palabra, &cadena[i], 1);
                    }
                palabra[i] = '\0';
                strcpy(palabra2, &cadena[i++]);
                insertar_Dic(raiz,palabra,palabra2,tipo);
                memset(palabra, 0, 30);
            }
        }
    fclose(f);
    if(argc>1) flag=1;
    if(!flag) printf("Bienvenido al programa, ingrese el comando (si no conoce los comandos escriba 'ayuda')\n");

    if(argv[1]==NULL){
        argv[1]=" ";
    }

    while(1){
        if(!flag){
            printf(">");
            fgets(input,30,stdin);
        }

        if(strstr(input,"cargar ") != NULL){
            Dic *aux = crear_Dic('\0');
            raiz = aux;
            nombre=&input[7];
            nombre[strlen(nombre)-1] = '\0';
            f=fopen(nombre,"rt");
            while (!feof(f)){
                if (!feof(f)){
                    fgets(cadena,80,f);
                    tipo=cadena[0];
                    for(i=2; cadena[i] != ' '; i++){
                           strncat(palabra, &cadena[i], 1);
                    }
                    palabra[i] = '\0';
                    strcpy(palabra2, &cadena[i++]);
                    insertar_Dic(raiz,palabra,palabra2,tipo);
                    memset(palabra, 0, 30);
                }
            }
            fclose(f);
        }else if(input[0] == 's' && input[1] == ' ' || strcmp(argv[1], "s")==0){
            if(!flag) sinonimos(&input[2],raiz);
            else{
                strcpy(input,argv[2]);
                strncat(input, " ", 2);
                sinonimos(input, raiz);
                return 0;
            }
            printf("\n");
        }else if(input[0] == 'a' && input[1] == ' ' || strcmp(argv[1], "a")==0){
            if(!flag) antonimos(&input[2],raiz);
            else{
                strcpy(input,argv[2]);
                strncat(input, " ", 2);
                antonimos(input, raiz);
                return 0;
            }
            printf("\n");
        }else if(input[0] == 'e' && input[1] == ' ' || strcmp(argv[1], "e")==0){
            memset(palabra, 0, 30);
            if(!flag){
                input[strlen(input)-1]='\0';
                expresiones(raiz,palabra,0,&input[2]);
            }else{
                strcpy(input, argv[2]);
                strncat(input, " ", 2);
                input[strlen(input)-1]='\0';
                expresiones(raiz,palabra,0,input);
                return 0;
            }
        }else if (strcmp(input,"ayuda")==10){
            printf("\nlas entradas posibles son: \n\n");
            printf("cargar nombre - carga el diccionario desde el archivo nombre.dic\n");
            printf("s palabra – busca los sinónimos de la palabra ingresada\n");
            printf("a palabra – busca los antónimos de la palabra ingresada\n");
            printf("e expresión – muestras los sinónimos y antónimos de todas las palabras que comienza con expresión\n");
            printf("salir – sale de la aplicación\n\n");

        }else if (strcmp(input,"salir")==10){
            return 0;
        }
    }
    return 0;
}
