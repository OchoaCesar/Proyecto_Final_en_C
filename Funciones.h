#include <stdio.h>
#include "Delicias.h"

#ifndef _FUNCIONES_
#define _FUNCIONES_

char user[maxChar];

void Login();
char LimpiarStr(char[]);

void ChangePass();

void ProdDel();
void ProdReg();
void ProdMostrar();
void ProdModif();
void ProdCargarPred();

int Facturacion();
int fecha(char*);
int isalstr(char*);
int isnum(char*);
void printFac(Cliente, Factura, int);

void printfID(char*);
void printClient();
void verClientes();

void nosotros();

void Login(){
	
	FILE *fp;
    
    userData userD;           //Registro de usuarios 
    char usuario[maxChar];    //Usuario
    char pass[maxChar];    //Contraseña
    int check=0;
    
    fp = fopen("userdata.dat", "rb");
    
    do{    
        printf("Ingrese su nombre de usuario: ");
        gets(usuario);
        
    
        printf("\nIngrese su contrasena: ");
        gets(pass);
        
        fseek(fp, 0, SEEK_SET);                //Vuelve al inicio del archivo para leer desde ese punto (por comprobar)
        fread(&userD, sizeof(userData), 1, fp);
        while (!feof(fp)){
            
//            printf("Comparando... %s, %s | %s, %s\n", userD.name, userD.pass, user, pass);
            
            if ((strcmp(userD.name,usuario)==0) && ((strcmp(userD.pass,pass)==0))){       //Si ambos, usuario y contraseña introducidos por el usuario// 
                check+=1;                                                               //coinciden con alguno del archivo // 
                break;
            }
            fread(&userD, sizeof(userData), 1, fp);
        }
        
        
    
        if (check==1){
            strcpy(user, usuario);
			printf("\nBienvenido, %s.\n", user);
			sleep(3);
        }
        else{
        printf("\nDatos incorrectos, intente nuevamente.\n\n");
        }     
    }while(check!=1);
}

void Register(){
	
	FILE *fp;
	userData a;

    int check = 0;
    char name[maxChar];
    char pass[maxChar];
    
    fp = fopen("userdata.dat", "ab+");
    
    if (fp==NULL){
        printf("\nError al consultar el archivo de registro\n");
        return;
    }
        
    while (check<2){
        check=0;
        fseek(fp, SEEK_SET, 0);
        printf("Introduzca el nombre de usuario: ");
        scanf(" %s", name);
        fflush(stdin);
        printf("Introduzca la contrasena: ");
        scanf(" %s", pass);
        fflush(stdin);
        
        fread(&a, sizeof(userData), 1, fp);
        while (!feof(fp)){
            if (strcmp(name,a.name)==0){
                check++;
            }    
            fread(&a, sizeof(userData), 1, fp);
        }
        
        if (check==1){
            printf("\nEl usuario introducido ya se encuentra registrado. Intente nuevamente.\n");
        }
        else if(check==0){
            printf("\nUsuario registrado correctamente.\n");
            break;
        }
        printf("\n");    
    }
    strcpy(a.name,name);
    strcpy(a.pass,pass);
    fwrite(&a, sizeof(userData), 1, fp);
    fclose(fp);
    return;
}

char LimpiarStr(char str[]){
	int i;
	for (i = 0; i < strlen(str); i++){
		
		if (str[i] == '_'){
			str[i] = ' ';
		}
	}
	return *str;
}

void ProdCargarPred(){
	system("cls");
	
	FILE *fp, *ft;
	char fich[] = {"ProdData.dat"};
	char opc;
	char aux[80];
	int i;
	
	Producto p;
	
	printf("Esta seguro de querer restaurar los datos de los productos? S/N : ");
	scanf("%c%*c",&opc);
	if (toupper(opc)=='S'){
		
		fp = fopen("prodlist.txt","r");
		ft = fopen (fich, "wb");
		
		if (fp==NULL) {
		printf("Archivo no existe.");
		sleep(3);
		return;
		}
		
		
		if (ft==NULL) {
		printf("Archivo no existe.");
		sleep(3);
		return;
		}
		
		fseek(fp, 0, SEEK_SET);
		
		while (!feof(fp)) {
			
			fscanf(fp,"%d %f %d %s", &p.prodID, &p.cost, &p.stock, aux); //saca del txt los datos y los guarda en un struct
			LimpiarStr(aux);
			strcpy(p.prodName,aux);
			
			i++;
			if (i >= 999) break;
			
			//printf("%d %.2f %d %s\n", p.prodID, p.cost, p.stock, p.prodName);	//Para verificar
			
			fwrite(&p, sizeof(Producto), 1, ft); //escribe el struct en el .dat
		}
	}
	
	else {
		printf("\nOperacion abortada.");
		sleep(2);	
		return;
	}
	
	printf("\nDatos restaurados con exito.");
	fclose(fp);
	fflush(fp);
	fclose(ft);
	fflush(ft);
	
	sleep(3);
	fflush(stdin);
	return;
}

void ProdMostrar(){
	system("cls");
	
	FILE *fp;
	Producto p;
	
	fp = fopen("ProdData.dat","rb");
	
	if (fp==NULL) {
		printf("Error al abrir el archivo.");
		sleep(3);
		return;
	}
	
	puts("ID\tCOSTO\tSTOCK\tNOMBRE\n");
	
	fread(&p, sizeof(Producto), 1, fp);
	
	while (!feof(fp)){
		if (strcmp(p.prodName,"*")!=0 && p.cost!=-1 && p.stock!=-1) {
			printf("%d\t%.2f\t%d\t%s\n", p.prodID, p.cost, p.stock, p.prodName);
		}
		fread(&p, sizeof(Producto), 1, fp);
	}
	
	printf("\n");
	
	fflush(fp);
	fclose(fp);

	return;
}

void ProdModif(){
	
	system("cls");
	
	FILE *fp;
	
	int check=0;
	char Nombre[100]; 
	int opc=0;
	int pos;
	int id=0;
	
	Producto p;
	
	fp = fopen("ProdData.dat","rb+");
	
	if (fp==NULL) {
		printf("Archivo no existe.");
		sleep(3);
		return;
	}	

	ProdMostrar(); //Muestra productos
	printf("Ingrese el ID de producto (O esciba 999 para regresar): ");
	scanf("%d", &id);
	
	if (id==999) return;
	
	fflush(stdin);
	
	fseek(fp,0,SEEK_SET);
	
	fread(&p, sizeof(Producto), 1, fp);
	
	while(check==0){
	
		while (!feof(fp)){
			
			if (p.prodID==id){
				
				while (opc!=4) {
					opc=5;
					system("cls");
						
					printf("Que parametro desea modificar del producto: \n\n");
					printf("1. Nombre: %s\n",p.prodName);
					printf("2. Stock: %d\n",p.stock);
					printf("3. Costo: %.2f\n",p.cost);
					printf("4. Salir\n");
					
					while ((opc<1)||(opc>4)) {	
							printf("  >>: ");
							scanf(" %d",&opc);
							fflush(stdin);
					}
							
					switch (opc){
						case 1: 
								
							printf("\nIngrese nuevo nombre: ");
							gets(Nombre);
							fflush(stdin);
							
							strcpy(p.prodName,Nombre);
							
							pos=ftell(fp)-sizeof(Producto);
	/*						printf("%d",pos);
							sleep(1);*/
							fseek(fp,pos,SEEK_SET);
							fwrite(&p,sizeof(Producto),1,fp);
							break;
						case 2: 
								
							printf("\nIngrese Stock actual: ");
							scanf("%d",&p.stock);
							fflush(stdin);
									
							pos=ftell(fp)-sizeof(Producto);
	/*						printf("%d",pos);
							sleep(1);*/
							fseek(fp,pos,SEEK_SET);
							fwrite(&p,sizeof(Producto),1,fp);
							break;
						case 3: 
							
							printf("\nIngrese nuevo Costo: ");
							scanf("%f",&p.cost);
							fflush(stdin);
									
							pos=ftell(fp)-sizeof(Producto);
	/*						printf("%d",pos);
							sleep(1);*/
							fseek(fp,pos,SEEK_SET);
							fwrite(&p,sizeof(Producto),1,fp);
							break;
						case 4: 
							check=1;
							break;
					}
					if (check==1){
						break;
					}
				}	
			}
		if (check==1){
		break;
		}
		fread(&p, sizeof(Producto), 1, fp);
		}
	
		if (check==0) {		
			printf("\nID de producto no encontrado. Ingrese nuevamente: ");
			scanf("%d",&id);
			fseek(fp,0,SEEK_SET);
		}
	}
	
	fclose(fp);
	return;
}

void ProdReg(){
	system("cls");
	
	FILE *fp;
	int aux = 0, check = 0, pos = 0,c;
	char nombre[100];
	
	Producto p;
	
	fp = fopen("ProdData.dat","rb+");
	
	if (fp==NULL) {
	printf("Archivo no existe.");
	sleep(3);
	return;
	}
	
	fseek(fp,0,SEEK_SET);
	
	fread(&p, sizeof(Producto), 1, fp);
	
	while (!feof(fp)){
		
		aux=p.prodID;									//Guarda id del producto que lee 
		
		if (strcmp(p.prodName,"*")==0 && p.cost==-1 && p.stock==-1)	{	//chequea si hay algun espacio de producto sin usar. De ser el caso, lo utiliza
			
			printf("Ingrese Nombre del producto: ");
			gets(nombre);
			strcpy(p.prodName,nombre);
		
			printf("\nIngrese Costo del producto: ");
			scanf("%f",&p.cost);
		
			printf("\nIngrese Stock del producto: ");
			scanf("%d",&p.stock);
			
			pos=ftell(fp)-sizeof(Producto);
			fseek(fp,pos,SEEK_SET);
			
			fwrite(&p,sizeof(Producto),1,fp);
			
			check++;									//Verifica que se consiguio un espacio
			break;
		}
		
		fread(&p, sizeof(Producto), 1, fp);
	}
	
	if (check==0){										//Si no se encontro ningun espacio disponible
		
		p.prodID=aux+1;
		
		printf("Ingrese Nombre del producto: ");
		gets(nombre);
		strcpy(p.prodName,nombre);
		
		printf("\nIngrese Costo del producto: ");
		scanf("%f",&p.cost);
		
		printf("\nIngrese Stock del producto: ");
		scanf("%d",&p.stock);
		
		fseek(fp,0,SEEK_END);							//situa al final del archivo
		
		fwrite(&p,sizeof(Producto),1,fp);
	}
	
	fclose(fp);
	fflush(fp);
	return;
}

void ProdDel(){
	
	system("cls");
	
	FILE *fp;
	int pos = 0, id = 0, check = 0, c;
	char opt = '\0';
	
	Producto p;
	
	fp = fopen("ProdData.dat","rb+");
	
	if (fp==NULL) {
	printf("Archivo no existe.");
	sleep(3);
	return;
	}
	
	ProdMostrar();
	
	printf("Ingrese ID del producto a eliminar: ");
	scanf("%d",&id);
	
	fseek(fp,0,SEEK_SET);
	
	fread(&p,sizeof(Producto),1,fp);
	
	while (check==0){
	
		while (!feof(fp)){
		
			if (p.prodID==id && strcmp(p.prodName,"*")!=0) { //Busca ID seleccionado
				
				printf("\nEsta seguro de querer borrar este producto? S/N : ");
				scanf("%c%*c",&opt);
				
				if (toupper(opt)!='N') {
					p.cost=-1;
					p.stock=-1;
					strcpy(p.prodName,"*"); //Lo vacia
					
					pos=ftell(fp)-sizeof(Producto);
					fseek(fp,pos,SEEK_SET);
				
					fwrite(&p, sizeof(Producto), 1, fp);
					check++;			//chequea	
					break;
				}
			}
			
			fread(&p, sizeof(Producto), 1, fp);
		}
			
		if (check==0) { 						//Si no encontro nada, vuelve a pedir id
		printf("\nID de producto no encontrado. Ingrese nuevamente: ");
		scanf("%d",&id);
		fseek(fp,0,SEEK_SET);
		}
	}
	
	fclose(fp);
	fflush(fp);
	return;
} 

void ChangePass(){
	
	system("cls");
	
	FILE *fp;
	
	int pos=0;
	userData userD; 
	char pass[maxChar] = {"A"};
	char pass2[maxChar] = {"B"};
	int check=0;
	int opt=0;
	fp = fopen("userdata.dat", "r+b");
	
	if (fp==NULL) printf("No se ha podido abrir el archivo");
	printf("1. Cambiar usuario\n2. Cambiar Contraseña\n");
	
	printf("%s\n",user);
    system("pause");
			
	while (opt!=1 && opt!=2){
		
		scanf("%d",&opt);
		fflush(stdin);
		if ((opt==1) || (opt==2)) break;
		else{
			printf("\nOpcion incorrecta, intentelo nuevamente\n");
		}
	}
	
	fseek(fp, 0, SEEK_SET);   
	
	while (!feof(fp) && check == 0) {
		
		fread(&userD, sizeof(userData), 1, fp);
		
		if (strcmp(user,userD.name)==0){
			
			while(check==0) {
				
				
				if (opt==1){
					printf("\nIngrese su nuevo nombre de usuario: ");
					gets(pass);
					fflush(stdin);
		
					pos=ftell(fp)-sizeof(userData);
					fseek(fp,pos,SEEK_SET);
					strcpy(userD.name,pass);
					strcpy(userD.pass,userD.pass);
					fwrite(&userD, sizeof(userData), 1, fp);
					printf("\nCambio de usuario efectuado exitosamente!\n");
					check=1;
					strcpy(user,pass);
				} 
				
				
				else{
					printf("\nIngrese su nueva contrasena: ");
					gets(pass);
					fflush(stdin);
					
					printf("\nConfirme su nueva contrasena: ");
					gets(pass2);
					fflush(stdin);
					
					if (strcmp(pass,pass2)==0){
						pos=ftell(fp)-sizeof(userData);
						fseek(fp,pos,SEEK_SET);
						strcpy(userD.pass,pass);
						strcpy(userD.name,user);
						fwrite(&userD, sizeof(userData), 1, fp);
						printf("\nCambio de contrasena efectuado exitosamente!\n");
						check=1;
						} 
					else {
						printf("\nContrasena no coincide. Ingrese nuevamente\n");
				}
				
				}
			}
		}
	}
	sleep(3);
	fflush(fp);
    fclose(fp);
	return;
}

int fecha(char *q){

  int b;
  
  time_t tiempo; 
  tiempo = time(NULL);
  struct tm tiempolocal;
   
  tiempolocal = *localtime(&tiempo);

  char fHora[70];

  char *format = "%Y-%m-%d %H:%M";

  int bytesEscritos =
      strftime(fHora, sizeof(fHora), format, &tiempolocal);
  if (b != 0) {

	strcpy(q, fHora);

	return 0;
  } else {
    printf("Error");
  	return 1;
  }
}

int isalstr(char *s){
	int i=0;
	int check=0;
	
	while(s[i]!='\0'){
  	
  		if((isdigit(s[i]))||(ispunct(s[i]))){
			check++;
			break;
	  	}
		i++;
  	}

	if(check==1){
		return 1;
	}
	else{
		return 0;
	}
}


int isnum(char *s){
	int i=0;
	int check=0;
	
	while(s[i]!='\0'){
  	
  		if(!isdigit(s[i])){
			check++;
			break;
	  	}
		i++;
  	}

	if(check==1){
		return 1;
	}
	else{
		return 0;
	}
}

void printFac(Cliente a, Factura b, int len){
	float iva[2];
	float sub[2];
	float total[2];
	int i;
	Producto c;
	FILE *fp;
	
	fp = fopen("ProdData.dat","rb");
		
	puts("                     SENIAT\n");
	puts("                  J-000000000\n");
	puts("                 Las Delicias C.A\n");
	puts("           Av. Atlantico, Ciudad Guayana\n");
	puts("                   Edo. Bolivar\n");
	puts("                 TLF: 000 000 000\n");
	puts("-------------------------------------------------\n");
	printf("Factura no. %d\n", b.nfactura);
	printf("Fecha       : %s", b.date);
	
	printf("\nUsuario     : Anon\n");
	printf("Cliente     : %s\n", a.titular);
	printf("Direccion   : %s\n", a.direccion);
	puts("-------------------------------------------------\n");

	fseek(fp,0,SEEK_SET);
	fread(&c, sizeof(Producto), 1, fp);


	while (!feof(fp)){
		
		for(i=0;i<len;i++){
			if (c.prodID==b.productos[0][i]){
				printf("%dx %s $%.2f Bs %.2f\n",b.productos[1][i], c.prodName, c.cost, (c.cost)*8);
				sub[0]+=b.productos[1][i]*((c.cost)*8);
				sub[1]+=b.productos[1][i]*c.cost;
			}
		}
		
		fread(&c, sizeof(Producto), 1, fp);
	}
	
	iva[0] = sub[0]*0.16;
	iva[1] = sub[1]*0.16;
	
	puts("\n-------------------------------------------------\n");	
	printf("Subtotal           : $%.2f     Bs.%.2f\n", sub[1], sub[0]);
	printf("IVA 16             : $%.2f     Bs.%.2f\n", iva[1], iva[0]);
	puts("-------------------------------------------------\n");
	puts("\n");
	printf("Total              : $%.2f     Bs.%.2f", sub[1]+iva[1], sub[0]+iva[0]);
	puts("\n");
	puts("\n");	
	
	system("pause");
	fclose(fp);	
}




int Facturacion(){
	system("cls");
	
	//---------------->Variables Temporales
	int ids[2][50];
	int id[2][2];
	int check=0, c2=0;
	int on =0;
	int sz;
	int pos=0;
	int nstock=0;
	int rl=0;
	
	float total[2];
	char tlf[15];
	char cedula[9];
	char cant[10];
	char pid[10];
	char direcc[100];
	char nom[50];
	char opc;
	int op=0;
	//------------------------------------//
	int i,l,j, k=0;

	Cliente c, c1;
	Factura f, f1;
	Producto p;
	FILE *fp;
	FILE *f_fact;
	FILE *f_client;
	fecha(f.date);
	
	fp = fopen("ProdData.dat","rb+");
	f_fact = fopen("Facturas.dat", "ab+");
	
	
//--------------------------------------------->Introducción de datos del cliente	
		
	while (check==0){
		
		while(op==0){
			printf("Nombre del cliente: ");
			gets(nom);
			
			if(isalstr(nom)==0){
				break;
			}
			else{
				puts("\nNombre incorrecto");
				nom[0]='\0';
			}
		}
			
		
		fflush(stdin);
		
		while (check==0){
			printf("\nNumero de cedula: ");
			scanf("%s", cedula);
			fflush(stdin);	
			
			if((isnum(cedula)==1)||((atoi(cedula))>40000000)){
				puts("\nCedula de identidad invalida.\n\n");
				
			}
			else{
				break;
			}
		}
		
		while (check==0){
			printf("\nNumero telefonico: ");
			scanf("%s", tlf);
			fflush(stdin);	
			
			if((isnum(tlf)==1)||(strlen(tlf)!=11)){
				puts("\nNumero telefonico incorrecto.\n\n");
			}
			else{
				break;
			}
		}
		
		
		printf("\nDireccion del cliente: ");
		gets(direcc);
		fflush(stdin);
		
		printf("\n¿Esta seguro que desea continuar? S/N\n:");
		while(c2==0){
			scanf(" %c", &opc);
			fflush(stdin);
			if (tolower(opc)=='s'){
				check=3;
				break;
			}
			else if (tolower(opc)=='n'){
				nom[0]='\0';
				system("cls");
				break;
			}
			else;
		}
	
	
	}
	check=0;
	strcpy(f.clnte, nom);
	strcpy(c.titular, nom);


	
	strcpy(c.telefono, tlf);
	strcpy(c.CI, cedula);
	strcpy(f.cedula, cedula);
	strcpy(c.direccion, direcc);	
	fflush(stdin);
	
	//---------------------------------------------------------------//
	printf("\nA continuacion introduzca la informacion solicitada, digite 0 en cada campo para finalizar.\n\n");
	system("pause");
	
	check==0;
	
	
	
	
	
	//------------------------>Obtención de los productos a comprar
	for(i=0;i<50;i++){
		
		while (check==0){
			on=0;
			fseek(fp,0,SEEK_SET);
			ProdMostrar();
			
			printf("\nIntroduzca la ID del producto: ");
			scanf("%s", pid);
			fflush(stdin);
			
			printf("\nCantidad: ");
			scanf("%s", cant);
			fflush(stdin);
			

			fread(&p, sizeof(Producto), 1, fp);
			
			if((pid[0]=='0')&&(cant[0]=='0')){
				l=i;
				i+=60;
				check++;
				break;
			}	
			
			if (((isnum(pid))==0)&&(isnum(cant))==0){
				id[0][0] = atoi(pid);
				id[1][0] = atoi(cant);

				if(id[1][0]==0){
					puts("\nCantidad no valida.\n");
					sleep(2);
				}
					
				else{
					while (!feof(fp)){

						if ((p.prodID==id[0][0])&&(id[1][0]>p.stock)){
							puts("\nCantidad no disponible.\n");
							i--;
							sleep(2);
							on++;
							break;
						}
						else if ((p.prodID==id[0][0])&&(id[1][0]<=p.stock)){

							ids[0][i]=id[0][0];
							ids[1][i]=id[1][0];
							total[0] += (p.cost*id[1][0])+(((p.cost*id[1][0])*0.16)); 
							total[1] += (p.cost*id[1][0])*8+((((p.cost*id[1][0])*8)*0.16)); 
							
							pos=ftell(fp)-sizeof(Producto);
							fseek(fp,pos,SEEK_SET);
							p.stock-=id[1][0];
							fwrite(&p, sizeof(Producto), 1, fp);
							
							rl++;
							check++;
							on++;
//							sleep(2);
							break;
						}
						fread(&p, sizeof(Producto), 1, fp);
					}
					if (on==0){
						puts("\nProducto no encontrado.\n\n");	
						sleep(2);

					}
					
						
				}
			}
			else{
				puts("\nValores incorrectos\n");
				sleep(2);
			}		
						
			if (on==1){
				break;
			
			}
		}

check=0;
	}



	system("cls");
	
//-------------------------------------->Eliminación de productos repetidos en el array	
	for (i=0;i<l;i++){  
	    for(j=i+1;j<l;j++){   
	    	
			if(ids[0][i]==ids[0][j]){  
	            ids[1][i] += ids[1][j];
				rl--;
				for(k=j;k<l-1;k++){  
	                ids[0][k] = ids[0][k+1];  
	            	
				}  
	            l--;  
	            j--;      
	        }  
	    }  
	}  
//--------------------------------------------------------------------------------------//


//----------------------------------------Escritura de los id de los productos comprados
	f.productos[0][0]= ids[0][0];		
	for(i=0;i<l;i++){
			f.productos[0][i] = ids[0][i];
			f.productos[1][i] = ids[1][i];	

		
	}
	puts("\n");
	f.lenp=rl;
	f.nfactura=0;
	f.total[0]=total[0];
	f.total[1]=total[1];


	fseek(f_fact, 0L, SEEK_END);
	sz = ftell(f_fact);
	fseek(f_fact,0,SEEK_SET);
	
	if (sz==0){
		fwrite(&f, sizeof(Factura), 1, f_fact);
	}

	else{
		fread(&f1, sizeof(Factura), 1, f_fact);
		while(!feof(f_fact)){
			f.nfactura++;
			fread(&f1, sizeof(Factura), 1, f_fact);	
		}
	
	
	fwrite(&f, sizeof(Factura), 1, f_fact);	
	}

	//--------------------------------------->Guardado de la información del cliente	
	f_client = fopen("Clientela.dat", "ab+");
	fread(&c1, sizeof(Cliente), 1, f_client);
	
	check=0;
	while(!feof(f_client)){
		if (strcmp(c.CI, c1.CI)==0){
			check++;
			break;
		}
		fread(&c1, sizeof(Cliente), 1, f_client);
	}
	
	if (check==0){
		fwrite(&c, sizeof(Cliente), 1, f_client);
	}
		
	
	
	
	system("cls");
	fclose(f_client);
	fclose(fp);
	fclose(f_fact);
	printFac(c, f, l);

	
}

void nosotros(){
	system("cls");
    char *alumnos [2][5]={"Antoniel Noriega", "Cesar Ochoa", "Jose Sotillo", "Manuel Escobar", "Sebastian Ortiz",
                       "31.318.324",    "30.453.175",    "31.636.771",    "30.578.567",      "30.576.350" }; 
    int i=0;
    
        printf(">>========================================<<\n");
        printf("             'Las Delicias C.A.'            \n");
        printf(">>========================================<<\n\n");
        printf("                2do Semestre \n");    
        printf("                  2 0 2 2\n\n");
        printf("               Desarrolladores\n\n");
    for (i=0;i<5;i++){

        printf("       %s C.I: %s", alumnos[0][i], alumnos[1][i]);
    
        printf("\n");
        printf("\n");
    }
system("pause");
}

void printClient(){
	
	FILE *fc;
	Cliente c;	
	fc = fopen("Clientela.dat", "rb");
	
	fread(&c, sizeof(Cliente), 1, fc);		
		while(!feof(fc)){
		
		printf("CI: %s  -----  Cliente: %s\n\n", c.CI, c.titular);
		fread(&c, sizeof(Cliente), 1, fc);	
		}
	fclose(fc);
	return;
}


void printfID(char *CI){
    FILE *fp;
    Factura f;    
    fp = fopen("Facturas.dat", "rb");

    fread(&f, sizeof(Factura), 1, fp);    
    while(!feof(fp)){    
        if (strcmp(CI, f.cedula)==0){
            printf("\n%s | ID Factura: %d", f.date, f.nfactura);    
        }
                
        fread(&f, sizeof(Factura), 1, fp);    
    }
    fclose(fp);            
}

void verClientes(){
	char cedula[13];
	int check[]={0,0,0,0};
	char opt[10];
	int posC=0;
	
	FILE *fp;
	Factura f;	
	fp = fopen("Facturas.dat", "rb");


	FILE *fc;
	Cliente c;	
	fc = fopen("Clientela.dat", "rb");
	

//----------------------------------------Petición de datos al usuario(C.I)
	while(check[1]==0){
		fread(&c, sizeof(Cliente), 1, fc);		
		printClient();
		
		fseek(fc,0,SEEK_SET);
		
		while (check[1]==0){
			printf("\n\nIntroduzca su numero de cedula.\n(0)Salir\n\n>>:");
			scanf("%s", cedula);
			puts("");
			puts("");
			fflush(stdin);	
			
			if((isnum(cedula)==1)||((atoi(cedula))>40000000)){
				system("cls");
				puts("\nCedula de identidad invalida.\n\n");
				
			}
			
			else{
				break;
				}
			}
		if(cedula[0]=='0'){
			check[1]++;
			break;
		}
	
		fread(&c, sizeof(Cliente), 1, fc);

//---------------------------------------------Impresión en pantalla de los datos del cliente registrado
		while(!feof(fc)){
		
			if (strcmp(c.CI, cedula)==0){
				
				posC=ftell(fc)-sizeof(Cliente);
				printf("Cliente: %s\nCedula: %s\nNumero telefonico: %s\n", c.titular, c.CI, c.telefono);
				printf("Direccion: %s\n", c.direccion);
				printf("\nCompras:");	
				printfID(c.CI);
				
				puts("\n\n");
				check[2]++;
			}
			
	
		fread(&c, sizeof(Cliente), 1, fc);	
		}
		fseek(fc,0,SEEK_SET);
	
		if ((check[2]==0)&&(cedula[0]!='0')){
			puts("\n");
			puts("Cedula no encontrada");
			sleep(2);
		}
		else{                        //-----------------------Petición de datos para la muestra de facturas
				while (opt[0]!='q'){
					puts("\nID a consultar. ");
					puts("(q)Salir");
					printf("\n>>:");
					scanf("%s", opt);
					fflush(stdin);
					
					if ((opt[0]!='q')&&(isnum(opt)==0)){

						fseek(fc,posC, SEEK_SET);
						fread(&c, sizeof(Cliente), 1, fc);
						fseek(fp, 0, SEEK_SET);
						
						while(!feof(fp)){
				
							if ((strcmp(c.CI, f.cedula)==0)&&((atoi(opt))==f.nfactura)){

								printFac(c, f, f.lenp);	
								system("cls");

							}		
				
							fread(&f, sizeof(Factura), 1, fp);	
						}
					}
					
					printfID(c.CI);
					puts("\n");
				}
		
			opt[0]='0';
			system("cls");
		}
		check[2]=0;
	
	}
}

#endif // _FUNCIONES_ 
