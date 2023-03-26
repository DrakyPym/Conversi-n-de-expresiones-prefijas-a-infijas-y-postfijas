#include "pila.h"

struct nodo* crearNodo(char dato1){
    struct nodo *nuevo = (struct nodo*)malloc(sizeof(struct nodo));
    nuevo->dato = dato1;
    nuevo->siguiente = NULL;
    return nuevo;
}

char reemplazar(struct pila *miPila, char dato1){     //regresa el dato que sale de la pila
    struct nodo *nuevo = crearNodo(dato1);
    char aux = miPila->ultimo->dato;
    nuevo->siguiente = miPila->ultimo->siguiente;
    miPila->ultimo = nuevo;
    return aux;
}

void apilar(struct pila *miPila, char dato1){
    struct nodo *nuevo = crearNodo(dato1);
    nuevo->siguiente = miPila->ultimo;
    miPila->ultimo = nuevo;
    miPila->contador++;
}

char desapilar(struct pila *miPila){               //Regresa el dato que desapila
    struct nodo *temporal;
    temporal = miPila->ultimo;
    if(miPila->ultimo->siguiente != NULL){
    miPila->ultimo = miPila->ultimo->siguiente;
    return temporal->dato;
    free(temporal);
    miPila->contador--;
    }else printf("No se puede desapilar, la pila esta vacia\n"); 
}

void imprimirPila(struct pila *miPila){
    struct nodo *temp = miPila->ultimo;
    if(temp->siguiente != NULL)
        while(temp->siguiente != NULL){
            printf("%c", temp->dato);
            temp = temp->siguiente;              
    }
    else printf("La pila esta vacia\n");
}

struct pila crearPila(char cabeza){
    struct pila miPila;
    miPila.ultimo = NULL;
    miPila.contador = 0;
    apilar(&miPila, cabeza);
    return miPila;
}

struct pila invertirPila(struct pila *miPila){
    struct pila temp = crearPila('\0');
    while(miPila->ultimo->siguiente != NULL){
        char aux;
        aux = desapilar(miPila);
        apilar(&temp, aux);
    }
    return temp;
}
