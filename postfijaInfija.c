#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pila.h"
#define MAX 40

void intercambiar(char *ptrInfija, struct pila *miPila, struct pila *resultado);
void numero(char *ptrInfija, struct pila *resultado);
void sumaResta(char *ptrInfija, struct pila *resultado, struct pila *miPila);
void multDiv(char *ptrInfija, struct pila *resultado, struct pila *miPila);
void potencia(char *ptrInfija, struct pila *resultado, struct pila *miPila);
void parentesisAbre(char *ptrInfija, struct pila *miPila);
void parentesisCierra(struct pila *resultado, struct pila *miPila);
void postfija(char *ptrInfija, struct pila *resultado, struct pila *miPila);
void prefija(char *ptrInfija, struct pila *resultado, struct pila *miPila);
int menu();

int main(){
    
    struct pila miPila = crearPila('\0');                //Se crea la pila
    struct pila resultado = crearPila('\0');              //Se crea la pila que guarda la expresion resultado
    char infija[MAX];  
	char *ptrInfija = infija;  

	printf("Ingrese la expresion infija\n");
	*ptrInfija = '\0';                                  //Agrega un caracter nulo al incio de la cadena para saber donde incia
	ptrInfija++;
	*ptrInfija = '(';
	ptrInfija++;
	gets(ptrInfija);
	int tamano = strlen(ptrInfija)+2;
	infija[tamano] = ')';                               
	infija[tamano+1] = '\0';                            //Agrega un caracter nulo al final de la cadena para saber donde termina

	switch(menu()){
		case 1: prefija(ptrInfija, &resultado, &miPila); break;
		case 2: postfija(ptrInfija, &resultado, &miPila); break;
		case 3: exit(0); break;
		default: printf("\nIngrese una opcion correcta\n"); break;
	}
	fflush(stdin);
	getchar();

    return 0;
	}

void intercambiar(char *ptrInfija, struct pila *miPila, struct pila *resultado){   //Manda el dato de la pila a resultado y el carcater entrante a la pila
	char aux;
	aux = reemplazar(miPila, *ptrInfija);
	apilar(resultado, aux);
}

void numero(char *ptrInfija, struct pila *resultado){                         //Caso en el que encuentra un numero     
	char *i;
	for(i = ptrInfija; *i >= '0' && *i <= '9' ; i++)
		apilar(resultado, *i);
}

void sumaResta(char *ptrInfija, struct pila *resultado, struct pila *miPila){   //Caso en el que encuentra una suma o una resta
	switch (miPila->ultimo->dato){
		case '*':
			while(miPila->ultimo->dato == '/' || miPila->ultimo->dato == '*' || miPila->ultimo->dato == '^'){
				char aux = desapilar(miPila);
				apilar(resultado, aux);
				apilar(miPila, *ptrInfija);
			}
			break;
		case '/':
			while(miPila->ultimo->dato == '/' || miPila->ultimo->dato == '*' || miPila->ultimo->dato == '^'){
				char aux = desapilar(miPila);
				apilar(resultado, aux);
				apilar(miPila, *ptrInfija);
			}
			break;
		case '^':
			while(miPila->ultimo->dato == '/' || miPila->ultimo->dato == '*' || miPila->ultimo->dato == '^'){
				char aux = desapilar(miPila);
				apilar(resultado, aux);
				apilar(miPila, *ptrInfija);
			}
			break;
		case '+':
			intercambiar(ptrInfija, miPila, resultado);
			break;
		case '-':
			intercambiar(ptrInfija, miPila, resultado);
			break;
		case '(':
			apilar(miPila, *ptrInfija);
			break;
		case ')':
			apilar(miPila, *ptrInfija);
			break;
		case '\0': 
			apilar(miPila, *ptrInfija);
			break;
	}
}

void multDiv(char *ptrInfija, struct pila *resultado, struct pila *miPila){  //Caso en el que encuentra una multiplicacion o uina division 
	switch(miPila->ultimo->dato){
		case '(': 
			apilar(miPila, *ptrInfija);
			break;
		case ')':
			apilar(miPila, *ptrInfija);
			break;
		case '*':
			intercambiar(ptrInfija, miPila, resultado);
			break;
		case '/':
			intercambiar(ptrInfija, miPila, resultado);
			break;
		case '+':
			apilar(miPila, *ptrInfija);
			break;
		case '-': 
			apilar(miPila, *ptrInfija);
			break;
		case '^':
			while(miPila->ultimo->dato == '^'){
				char aux = desapilar(miPila);
				apilar(resultado, aux);
				apilar(miPila, *ptrInfija);
			}
			break;
		case '\0': 
			apilar(miPila, *ptrInfija);
			break;
	}
}

void potencia(char *ptrInfija, struct pila *resultado, struct pila *miPila){  //Caso en el que encuentra una potencia
	switch(miPila->ultimo->dato){
		case '(':
			apilar(miPila, *ptrInfija);
			break;
		case ')':
			apilar(miPila, *ptrInfija);
			break;
		case '*':
			apilar(miPila, *ptrInfija);
			break;
		case '/':
			apilar(miPila, *ptrInfija);
			break;
		case '+':
			apilar(miPila, *ptrInfija);
			break;
		case '-':
			apilar(miPila, *ptrInfija);
			break;
		case '^':
			intercambiar(ptrInfija, miPila, resultado);
			break;
		case '\0': 
			apilar(miPila, *ptrInfija);
			break;
	}
}

void parentesisAbrePost(char *ptrInfija, struct pila *miPila){  //Caso en el que encuentra un parentesis que abre para la expresion postfija
	apilar(miPila, *ptrInfija);
}

void parentesisAbrePre(struct pila *resultado, struct pila *miPila){    //Caso en el que encuentra un parentesis que abre para la expresion prefija
	while(miPila->ultimo->dato != '\0' && miPila->ultimo->dato != ')'){
		char aux;
		aux = desapilar(miPila);
		apilar(resultado, aux);
	}
	if(miPila->ultimo->dato == ')'){
		desapilar(miPila);
	}
}

void parentesisCierraPost(struct pila *resultado, struct pila *miPila){   //Caso en el que encuentra un parentesis que cierra para la expresion postfija 
	while(miPila->ultimo->dato != '\0' && miPila->ultimo->dato != '('){
		char aux;
		aux = desapilar(miPila);
		apilar(resultado, aux);
	}
	if(miPila->ultimo->dato == '('){
		desapilar(miPila);
	}
}

void parentesisCierraPre(char *ptrInfija, struct pila *miPila){           //Caso en el que encuentra un parentesis que cierra para la expresion prefija
	apilar(miPila, *ptrInfija);
}

void postfija(char *ptrInfija, struct pila *resultado, struct pila *miPila){        // Pra convertir a una expresion postfija
	while(*ptrInfija != '\0'){                                     
        if(*ptrInfija >= '0' && *ptrInfija <= '9')
			numero(ptrInfija, resultado);
		else
        switch(*ptrInfija){
                    case '*':
						multDiv(ptrInfija, resultado, miPila);
                        break;
                    case '/':
						multDiv(ptrInfija, resultado, miPila);
                        break;
                    case '+':
						sumaResta(ptrInfija, resultado, miPila);
                        break;
                    case '-':
						sumaResta(ptrInfija, resultado, miPila);
                        break;
                    case '^':
						potencia(ptrInfija, resultado, miPila);
                        break;
                    case '(':
						parentesisAbrePost(ptrInfija, miPila);
                        break;
                    case ')':
						parentesisCierraPost(resultado, miPila);
                        break;
					
                    default:
                        printf("No ingreso correctamente la expresion\n");
                        break;
        }
        ptrInfija++;
    }
	system("cls");
	*resultado = invertirPila(resultado);
	printf("Imprimiendo postfija\n");
	imprimirPila(resultado);
}

void prefija(char *ptrInfija, struct pila *resultado, struct pila *miPila){    //Para convertir a una expresion prefija
	int tamano = strlen(ptrInfija); 
	ptrInfija = ptrInfija + tamano -2;       //ptrInfija apunta al ultimo elemento de la cadena
	
	while(*ptrInfija != '\0'){                                     
        if(*ptrInfija >= '0' && *ptrInfija <= '9')
			numero(ptrInfija, resultado);
		else
        switch(*ptrInfija){
                    case '*':
						multDiv(ptrInfija, resultado, miPila);
                        break;
                    case '/':
						multDiv(ptrInfija, resultado, miPila);
                        break;
                    case '+':
						sumaResta(ptrInfija, resultado, miPila);
                        break;
                    case '-':
						sumaResta(ptrInfija, resultado, miPila);
                        break;
                    case '^':
						potencia(ptrInfija, resultado, miPila);
                        break;
                    case '(':
						parentesisAbrePre(resultado, miPila);
                        break;
                    case ')':
						parentesisCierraPre(ptrInfija, miPila);
                        break;
					
                    default:
                        printf("No ingreso correctamente la expresion\n");
                        break; 
        }
        ptrInfija--;
    }
	system("cls");
	printf("Imprimiendo prefija\n");
	imprimirPila(resultado);
}

int menu(){
int opcion;
printf("1. Presione 1 para convertir a una expresion prefija\n2. Presione 2 para convertir a una expresion postfija");
printf("\n");
scanf("%i", &opcion);
return opcion;
}
