#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

//DEFINIMOS LAS ESTRUCTURAS
typedef struct Diccionario {
    struct SoA *A;
    struct SoA *S;
    struct Diccionario *hijo[26];
    int fdp;
    char letra;
} Dic;

typedef struct SoA{
    struct SoA *next;
    char palabra[];
}SoA;

//FUNCIONES DE LA LIBRERIA//

//Funcion crear los nodos de sinonimos y antonimos
SoA *crear_SoA(char *palabra){
    SoA* nodo= (SoA*)calloc(1, sizeof(SoA));
    strcpy(nodo->palabra,palabra);
    nodo->next=NULL;
    return nodo;
}

//Funcion crear los nodos del arbol Trie
Dic* crear_Dic(char letra) {
    Dic* node = (Dic*)calloc(1, sizeof(Dic));

    for (int i=0; i<26; i++){
        node->hijo[i] = NULL;
    }
    node->fdp = 0;
    if (letra >= 'A' && letra <= 'Z')
        letra = letra - 'A' + 'a';

    node->letra=letra;
    return node;
}

//Funcion insertar las palabras en el arbol
Dic *insertar_Dic(Dic* raiz, char* palabra,char* palabra2, char tipo){
    Dic* temp = raiz;
    int idx=0;

    for (int i=0; palabra[i] != '\0'; i++){
        if (palabra[i]<'a'){
            idx = (int) palabra[i] - 'A';
        }else
            idx = (int) palabra[i] - 'a';

        if (temp->hijo[idx] == NULL) {
            temp->hijo[idx] = crear_Dic(palabra[i]);
        }
        temp = temp->hijo[idx];
    }
    temp->fdp = 1;
    if (tipo == 'S'){
        SoA *newp=crear_SoA(&palabra2[1]);
        newp->next=temp->S;
        temp->S=newp;
    }
    if(tipo == 'A'){
        SoA *newp=crear_SoA(&palabra2[1]);
        newp->next=temp->A;
        temp->A=newp;
    }
    return raiz;
}

//Funcion buscar palabras en el arbol
Dic *buscar_palabra(Dic* raiz, char *palabra){
    Dic* temp = raiz;
    int idx=0;

    for(int i=0; palabra[i+1]!='\0'; i++){
        if (palabra[i]<'a'){
            idx = (int) palabra[i] - 'A';
        }else
            idx = (int) palabra[i] - 'a';

        if (temp->hijo[idx] == NULL)
            return NULL;

        temp = temp->hijo[idx];
    }
    if (temp != NULL && temp->fdp == 1)
        return temp;
    return NULL;
}

//Funcion comprobar la expresion regular
int comprobar(char *expresion, char *palabra){
    regex_t regex;
    int value,value2,bol=0;

    value = regcomp(&regex,expresion,REG_EXTENDED);
    value2 =regexec(&regex,palabra,0,NULL,0);
    if (value2==0){
        bol=1;
    }
    else
    if (value2== REG_NOMATCH){
        bol=0;
    }
    return bol;
}

//Funcion imprimir sinonimos
void printsinonimos(Dic *nodo){
    SoA* head;
    head=nodo->S;
    if (nodo != NULL){
        for(;nodo->S != NULL;nodo->S=nodo->S->next){
            char *aux=nodo->S->palabra;
            int lenght = strlen(aux);
            if(aux[lenght-1]=='\n')
                aux[lenght-1] = '\0';

            printf("%s",aux);
            if (nodo->S->next !=NULL)
                printf(", ");
        }
        nodo->S=head;
        printf("\n");
    }
}

//Funcion imprimir antonimos
void printantonimos(Dic *nodo){
    SoA* head;
    head=nodo->A;
    if (nodo != NULL){
        for(;nodo->A != NULL;nodo->A=nodo->A->next){
            char *aux=nodo->A->palabra;
            int lenght = strlen(aux);
            if(aux[lenght-1]=='\n')
                aux[lenght-1] = '\0';

            printf("%s",aux);
            if (nodo->A->next !=NULL)
                printf(", ");
        }
        nodo->A=head;
        printf("\n");
    }
}

//Funcion buscar sinonimos
void sinonimos(char *palabra, Dic *raiz){
    Dic* temp=raiz;
    Dic* nodo=buscar_palabra(temp,palabra);
    printsinonimos(nodo);
}

//Funcion buscar antonimos
void antonimos(char *palabra, Dic *raiz){
    Dic* temp=raiz;
    Dic* nodo=buscar_palabra(temp,palabra);
    printantonimos(nodo);
}

//Funcion expresiones regulares
void expresiones(Dic *raiz, char *palabra, int lenght, char *expresion){
    if (raiz == NULL) return;
    char* imprimir;
        strncat(palabra, &raiz->letra, 1);

        lenght++;
    palabra[lenght] ='\0';
    if (raiz->fdp){
        if (comprobar(expresion, palabra)) {
            printf("%c%s\n", toupper(palabra[0]), &palabra[1]);
            printf("s: ");
            printsinonimos(raiz);
            printf("a: ");
            printantonimos(raiz);
            printf("\n");
        }
    }
    for (int i=0; i<26; i++){
        expresiones( raiz->hijo[i], palabra, lenght, expresion );
        palabra[lenght-1] = '\0';
    }
    return;
}
