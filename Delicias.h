#include <stdio.h>

#ifndef _DELICIAS_
#define _DELICIAS_

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#define maxChar 50



typedef struct {
	int prodID; //Id del producto
	float cost; //Costo del producto en dolares (sin iva)
	int stock; //Stock del producto
	char prodName[80]; //Nombre del Producto
} Producto;

typedef struct{
    char name[maxChar];
    char pass[maxChar];
} userData;

typedef struct{
    char CI[9]; //cedula escrita 'v12345678'
    char titular[50]; //Nombre y apellido del Cliente
	char direccion[100];
	char telefono[12];
	int compras[50];
} Cliente;

typedef struct{
	int productos[2][50];
	int nfactura;
	char date[30];
	float total[2];
	char clnte[50];
	int lenp;
	char cedula[9];
}Factura;

#endif // _DELICIAS_


