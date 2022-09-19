#include <stdio.h>
#include "Delicias.h"
#include "Funciones.h"

#ifndef _MENUS_
#define _MENUS_

void MenuPrincipal();
void MenuVentas();
void MenuProductos();
void MenuSistema();
void MenuUsuarios(); 
void MenuClientes(); 

void MenuPrincipal(){
	fflush(stdin);
	int opc=0;
	while (opc!=3) {
		opc = '\0';
		system("cls");
		
		printf(">>========================================<<\n");
		printf("             'Las Delicias C.A.'            \n");
		printf(">>========================================<<\n");
		printf("|(1) Menu del Sistema                      |\n");
		printf("|(2) Menu de Ventas                        |\n");
		printf("|(3) Cerrar                                |\n");
		printf("+__________________________________________+\n");
		
		while (opc < 1 || opc > 3) {	
			printf("  >>: ");
			scanf("%d%*c",&opc);
		}
		
		switch (opc) {
			case 1: MenuSistema();
			break;
			case 2: MenuVentas();
			break;
			case 3: break;
		}
	}
	return;
}

void MenuVentas() {
	fflush(stdin);
	int opc=0;
	while (opc!=2) {
		opc = '\0';
		system("cls");
		
		printf(">>========================================<<\n");
		printf("                Menu de Ventas              \n");
		printf(">>========================================<<\n");
		printf("|(1) Facturacion                           |\n");
		printf("|(2) Volver                                |\n");
		printf("+__________________________________________+\n");
		
		while (opc < 1 || opc > 2) {	
			printf("  >>: ");
			scanf("%d%*c",&opc);
		}
		
		switch (opc) {
			case 1: Facturacion();
			break;
			case 2: break;	
		}
	}
	return;
}

void MenuSistema(){
	fflush(stdin);
	int opc=0;
	while (opc!=5) {
		opc = '\0';
		system("cls");
		
		printf(">>========================================<<\n");
		printf("                Menu Sistemas               \n");
		printf(">>========================================<<\n");
		printf("|(1) Usuarios                              |\n");
		printf("|(2) Clientes                              |\n");
		printf("|(3) Productos                             |\n");
		printf("|(4) Sobre el Programa...                  |\n");
		printf("|(5) Volver                                |\n");
		printf("+__________________________________________+\n");
		
		while (opc < 1 || opc > 5) {	
			printf("  >>: ");
			scanf("%d%*c",&opc);
		}
		
		switch (opc) {
			case 1: MenuUsuarios();
			break;
			case 2: MenuClientes();
			break;
			case 3: MenuProductos();
			break;
			case 4: nosotros();
			break;
			case 5: break;
		}
	}
	return;
}

void MenuProductos(){
	fflush(stdin);
	int opc=0;
	while (opc != 6) {
		opc = '\0';
		system("cls");
		
		printf(">>========================================<<\n");
		printf("               Menu Productos               \n");
		printf(">>========================================<<\n");
		printf("|(1) Restaurar Predeterminado              |\n");
		printf("|(2) Mostrar Productos                     |\n");
		printf("|(3) Modificar Productos                   |\n");
		printf("|(4) Registrar Producto                    |\n");
		printf("|(5) Eliminar Producto                     |\n");
		printf("|(6) Volver                                |\n");
		printf("+__________________________________________+\n");
		
		while (opc < 1 || opc > 6) {	
			printf("  >>: ");
			scanf("%d%*c",&opc);
		}
		
		switch (opc){
			case 1: ProdCargarPred();
			break;
			case 2: ProdMostrar();
				system("pause");
			break;
			case 3: ProdModif();
			break;
			case 4: ProdReg();
			break;
			case 5: ProdDel();
			break;
			case 6: break;
		}
	}
	return;
}

void MenuUsuarios() {
	fflush(stdin);
	int opc=0;
	while (opc != 2) {
		opc = '\0';
		system("cls");
		
		printf(">>========================================<<\n");
		printf("               Menu Usuarios                \n");
		printf(">>========================================<<\n");
		printf("|(1) Cambiar Usuario / Contrasena          |\n");
		printf("|(2) Volver                                |\n");
		printf("+__________________________________________+\n");
		
		while (opc < 1 || opc > 2) {	
			printf("  >>: ");
			scanf("%d%*c",&opc);
		}
		
		switch (opc){
			case 1: ChangePass(user);
			break;
			case 2: break;
		}
	}
	return;
}

void MenuClientes(void) {
	fflush(stdin);
	int opc=0;
	while (opc != 2) {
		opc = '\0';
		system("cls");
		
		printf(">>========================================<<\n");
		printf("               Menu Clientes                \n");
		printf(">>========================================<<\n");
		printf("|(1) Consultar Clientes                    |\n");
		printf("|(2) Volver                                |\n");
		printf("+__________________________________________+\n");
		
		while (opc < 1 || opc > 2) {	
			printf("  >>: ");
			scanf("%d%*c",&opc);
		}
		
		switch (opc){
			case 1: verClientes();
			break;
			case 2: break;
		}
	}
	return;
}



#endif //_MENUS_
