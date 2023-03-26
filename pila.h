#ifndef PILA_H
#define PILA_H

#include <stdio.h>
#include <stdlib.h>

struct nodo{
    char dato;
    struct nodo *siguiente;
};

struct pila{
    struct nodo *ultimo;
    int contador;
};

struct nodo* crearNodo(char dato1);
char reemplazar(struct pila *miPila, char dato1);
void apilar(struct pila *miPila, char dato1);
char desapilar(struct pila *miPila);
void imprimirPila(struct pila *miPila);
struct pila crearPila(char cabeza);
struct pila invertirPila(struct pila *miPila);

#endif
