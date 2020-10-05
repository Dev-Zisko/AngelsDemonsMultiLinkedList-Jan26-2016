#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//STRUCTS

typedef struct fecha
{
        int dia, mes, anio, contador;
        struct fecha *proxfe;
        struct nacimiento *primernac;
}fec;
fec *primerf=NULL;
    
typedef struct nacimiento
{
        int maldad, bondad, expiacion, codigo;
        char nombre[40];
        char genero[1];
        char pais[20];
        struct nacimiento *proxnac;
        struct pecados *ppecado;
        struct bondades *pbondad;
}nac;

typedef struct pecados 
{
	char pecado[20];
	int vt, dia, mes, anio; //valor total
	struct pecados *proxp;
} pec;

typedef struct bondades
{
	char bondad[20];
	int vt, dia, mes, anio; //valor total
	struct bondades *proxb;
} bond;


typedef struct categoria
{
        char categoria[20];
        int valorc;
        struct acciones *primeracc;
        struct categoria *proxctg;
} ctg;
ctg *primerctgp=NULL;
ctg *primerctgb=NULL;
	
typedef struct acciones
{
        char accion[20];
        int valoracc;
        struct acciones *proxacc;
} acc;


//PROTOTIPOS
void menu();
fec *comprobarFecha(fec *p);
fec *crearFecha(fec *p,int d,int m,int a);
fec *crearNacimiento(fec *p);
ctg *crearCategoria(ctg *p);
void mostrarCategoria(ctg *p);
void mostrarNacimiento(fec*p);
ctg *crearAccion(ctg *q);
ctg *modificarCTG(ctg *p);
ctg *modificarAccion(ctg*p);
ctg *EliminarCategoria(ctg *p);
void MostrarComportamiento(fec *p);
void FaltasCometidas(fec**q, ctg*p);

//PROCESOS FECHA-NACIMIENTO

fec *comprobarFecha(fec *p) // Comprueba si la fecha existe en la lista de Fechas , en caso contrario crea la nueva fecha
{
	int dia, mes, anio, codigo;      
	fec *auxf;
	auxf=p; 
	
		printf("Dia del nacimiento?:  ");
     	scanf("%d",&dia);
     	printf("mes del nacimiento?:  ");
     	scanf("%d",&mes);
     	printf("anio del nacimiento?: ");
     	scanf("%d",&anio);
	
     while(auxf!=NULL)
     {
      if((dia==auxf->dia)&&(mes==auxf->mes)&&(anio==auxf->anio))
      {	  
      auxf=crearNacimiento(auxf); 
      return(p);
	     
      }
      else
      auxf=auxf->proxfe;
    
     }
	 
	 if(auxf==NULL)
	 {
	 
		p=crearFecha(p,dia,mes,anio);
	
	 	p=crearNacimiento(p);//AQUI
	 
	 } 
	 
	 return(p);
}

fec *crearFecha(fec *p,int d,int m,int a) //Funcion que crea un nodo en las fechas
{
	fec *nuevo; 	
	
     	nuevo=(fec*)malloc(sizeof(fec));         
     	nuevo->dia=d;     
     	nuevo->mes=m;     	
     	nuevo->anio=a; 	 
		nuevo->proxfe=p;
		nuevo->primernac=NULL;
		nuevo->contador=0; 
		
     	return(nuevo);      
}

fec *crearNacimiento(fec *q)  
{
	
	char nomb[40];
	char gen[1];
	char pa[20];
	
	
 		
	
	nac *nuevo;	
	nuevo=(nac*)malloc(sizeof(nac));
	nuevo->proxnac=q->primernac;
	nuevo->ppecado=NULL;
	nuevo->pbondad=NULL;
	nuevo->maldad=0;
	nuevo->bondad=0;
	nuevo->expiacion=0;
	
	printf("Ingrese su nombre completo:  \n");
	scanf("%s",&nomb);
	strcpy(nuevo->nombre,nomb);
	printf("Indique su pais:  \n");
	scanf("%s",&pa);
	strcpy(nuevo->pais,pa);
	printf("Ingrese su genero(m/f)):  \n");
	scanf("%s",&gen);
	strcpy(nuevo->genero,gen);
	nuevo->codigo=q->contador + 1;
	q->contador=nuevo->codigo;
	
	q->primernac=nuevo;	
	
	return(q);
}

void mostrarNacimiento(fec *p) 
{
	nac *auxn;
	fec *auxf;
	auxf=p;
	while(auxf!=NULL)
    {
       auxn=auxf->primernac;
       while(auxn!=NULL)
       {
       	printf("%s [%d]->",auxn->nombre,auxn->codigo);
		auxn=auxn->proxnac;
       }
       printf("NULL");
       printf("\n"); 
       auxf=auxf->proxfe;
    }		
}

ctg *crearCategoria(ctg *p)
{
	char nombrec[20];
	int valor;
	ctg *nuevo;
	nuevo=((ctg*)malloc(sizeof(ctg)));
    printf("Ingrese el nombre de la categoria a crear:  \n");
	scanf("%s",&nombrec);
	strcpy(nuevo->categoria,nombrec);
	printf("Indique el valor de la categoria:  \n");
	scanf("%d",&valor);
	nuevo->valorc=valor;
	nuevo->proxctg=p;
	nuevo->primeracc=NULL;
    
	return(nuevo);
	
}

void mostrarCategoria(ctg *p) 
{
	ctg *aux;
	aux=p;
	while(aux!=NULL)
	{
		printf("%s[%d]->",aux->categoria,aux->valorc);
		aux=aux->proxctg;
	}
		printf("NULL \n");
}

ctg *crearAccion(ctg *q) // verificar creacion de nuevo (cajita)
{
	char nombrea[20], nombrec[20];
	int valor,comparar; 
	ctg *auxc; acc *auxa;
	auxc=q;
	printf("Ingrese el nombre de la categoria a donde desea ingresar la accion:  \n");
	scanf("%s",&nombrec);
	while(auxc!=NULL)
	{
        comparar=strcmp(auxc->categoria,nombrec);
		if(comparar==0)
		{	
		acc *nuevo;
		nuevo=(acc*)malloc(sizeof(acc));
		nuevo->proxacc=auxc->primeracc;
		auxc->primeracc=nuevo;
		printf("Ingrese el nombre de la accion:  \n");
		scanf("%s",&nombrea);
		strcpy(nuevo->accion,nombrea);
		printf("Ingrese el valor de la accion:  \n");
		scanf("%d",&valor);
		nuevo->valoracc=valor;
		return(q); 		
	    }
	    else
	  	auxc=auxc->proxctg;
	  	
	}	
	if(auxc==NULL)
		{
			printf("La categoria indicada no existe, para agregar un pecado cree primero la categoria desde el menu principal. \n");
			system("PAUSE");
			menu();
		}
	
}

void mostrarAccionpC(ctg *q)
{
     ctg *auxc; acc *auxa;
     int comparar;
     char nombrec[20];
     auxc=q;
     printf("Ingrese el nombre de la categoria:  \n");
     scanf("%s",nombrec);
     while(auxc!=NULL)
     {
      comparar=strcmp(auxc->categoria,nombrec);
      if(comparar==0)
      {
       auxa=auxc->primeracc;
       while(auxa!=NULL)
       {
       	printf("%s[%d]->",auxa->accion,auxa->valoracc);
		auxa=auxa->proxacc;
       }
 	   printf("NULL \n");  
 	   break;
      }
      else
      auxc=auxc->proxctg;
      	  
     }
	    if(auxc==NULL)
        { printf("La categoria no existe.\n");
          system("PAUSE");
          menu();
		}      
}
 

void mostrarAcciones(ctg *p) // no funciona si se elimina el que apunta al NULL;
{
	acc *auxa; ctg *auxc;
	auxc=p;
	if(auxc==NULL)
	{
		printf("No hay acciones para mostrar. \n");
		system("PAUSE");
		menu();
	}
	else
	{
	
    	while(auxc!=NULL)
     	{
     		auxa=auxc->primeracc;
     		if(auxa==NULL)
     		{
     			printf("No hay acciones para mostrar. \n");
				system("PAUSE");
				menu();     			
			}
       		while(auxa!=NULL)
       		{
       			printf("%s[%d]->",auxa->accion,auxa->valoracc);
				auxa=auxa->proxacc;
      	 	}		
       		printf("NULL \n");       
       		auxc=auxc->proxctg;
      	}      	
	}	 	
}

ctg *modificarCTG(ctg *p)
{
	ctg *aux;  
	int valor,comparar;
	char nombre[20];
	aux=p; 
	
	printf("Ingrese el nombre de la categoria a la cual modificara el valor:   \n");
	scanf("%s",&nombre);
	printf("Ingrese el nuevo valor:   \n");
	scanf("%d",&valor);
		
	while(aux!= NULL)
	{
        comparar=strcmp(aux->categoria,nombre);
		if(comparar==0) //preguntar comparacion de strings
		{
			aux->valorc=valor;
		}
		aux=aux->proxctg;
		
	}
	return(p); 
}

ctg *modificarAccion(ctg*p)
{
	acc *auxa;  ctg*auxc;
	int valor,comparar;
	char nombre[20];
	auxc=p;
	
	printf("Ingrese el nombre de la accion al cual modificara el valor:  \n");
	scanf("%s",&nombre);
	printf("Ingrese el nuevo valor:   \n");
	scanf("%d",&valor);
		
	while(auxc!= NULL)
	{
		auxa=auxc->primeracc;
		while(auxa!=NULL)
		{
            comparar=strcmp(auxa->accion,nombre);
			if(comparar==0) //preguntar comparacion de strings	
			{	
			auxa->valoracc=valor;
			return(p);
			}
			else
			auxa=auxa->proxacc;			
		}
		auxc=auxc->proxctg;
					
	}
	printf("La accion indicada no existe. Intente nuevamente.");
	system("PAUSE");
	system("cls");
	menu();
}
ctg *EliminarCategoria(ctg *p) // Se elimina la categoria pero siguen sus respectivas listas como basura.
{
	ctg *auxc, *antc;
	acc*auxa;
	char nombre[20];
	auxc=p;
	int i=0; // boolean que indica si se debe borrar la primera o las demas.
	int comparar; // boolean que indica si las categorias tienen la misma longitud.
	
	printf("Ingrese el nombre de la categoria a eliminar: \n");
	scanf("%s",&nombre);
	while(auxc!=NULL)
	{
		auxa=auxc->primeracc;
        comparar=strcmp(auxc->categoria,nombre);
		if((comparar==0)&&(auxa==NULL)&&(i==0)) //primer elemento de la lista... Problema si se elimina el primero de la lista queda basura y si se agrega otra categoria queda en ciclo infinito.
		{	antc=auxc->proxctg; 
			free(auxc);
			auxc=antc;
			return(p);
	
			
		}
		else if((comparar==0)&&(auxa==NULL)&&(i!=0))
		{
			antc->proxctg=auxc->proxctg;
			free(auxc);
			auxc=antc;	
			return(p);	
				
		}	

		else
		{
			antc=auxc;
			auxc=auxc->proxctg;
			i++;
		}		
	}
//	return(p); 
}

ctg *EliminarAccion(ctg *p)
{
	ctg*auxc; acc*auxa,*ant;
	int i=0; int comparar;
	char nombre[20];
	auxc=p;
	printf("Ingrese el nombre de la accion que desea eliminar:  \n");
	scanf("%s",&nombre);
	
	while(auxc!=NULL)
	{
		auxa=auxc->primeracc;
		while(auxa!=NULL)
		{
        	comparar=strcmp(auxa->accion,nombre);          
			if((comparar==0)&&(i==0)) //primer elemento de la lista
			{
				auxc->primeracc=auxc->primeracc->proxacc; 
				free(auxa);
				auxa=auxc->primeracc;
				return(p);
			
			
			}
			if((comparar==0)&&(i!=0))
			{
				ant->proxacc=auxa->proxacc;
				free(auxa);
				auxa=ant;
				return(p);		
				
			}	

			else
			{
				ant=auxa;
				auxa=auxa->proxacc;
				i++;
			}		
		
		}
		auxc=auxc->proxctg; i=0;
	}
	printf("la accion no existe. Intente Nuevamente.");
	system("PAUSE");
	menu();
	
}

void FaltasCometidas(fec **q, ctg*p)
{
	fec *auxf; nac *auxn; ctg *auxc; acc *auxa;
	pec *nuevo;
	char nomp[20]; //nombre persona
	char noma[20]; // nombre accion
	int comparar1,comparar2,vt;
	
	
	printf("Ingrese el nombre de la persona:  \n");
	scanf("%s",&nomp);
	printf("Ingrese el nombre de la accion realizada por la persona:  \n");
	scanf("%s",&noma);
	auxc=p;
	auxf=*q;
	while(auxc!=NULL)
	{
		auxa=auxc->primeracc;
		while(auxa!=NULL)
		{
			comparar1=strcmp(auxa->accion,noma);
			if(comparar1==0)
			{
				while(auxf!=NULL)
				{
					auxn=auxf->primernac;
					while(auxn!=NULL)
					{
						comparar2=strcmp(auxn->nombre,nomp);
						if(comparar2==0)
						{
							nuevo=(pec*)malloc(sizeof(pec));
							nuevo->proxp=auxn->ppecado;
							auxn->ppecado=nuevo;
							nuevo->vt=auxa->valoracc + auxc->valorc;
							strcpy(nuevo->pecado,auxa->accion);	
							printf("ingrese el dia en el cual se realizo la falta:  \n");
							scanf("%d",&nuevo->dia);
							printf("ingrese el mes en el cual se realizo la falta:  \n");
							scanf("%d",&nuevo->mes);
							printf("ingrese el año en el cual se realizo la falta:  \n");
							scanf("%d",&nuevo->anio);
							auxn->ppecado=nuevo;
							
						
							
						}
						
						auxn=auxn->proxnac;	
					}
				
					
					auxf=auxf->proxfe;
				}
			}	
			auxa=auxa->proxacc;
		}
		auxc=auxc->proxctg;
	}
	
}
void BuenasAcciones(fec**q, ctg*p)
{
	fec *auxf; nac *auxn; ctg *auxc; acc *auxa;
	bond *nuevo;
	char nomp[20]; //nombre persona
	char noma[20]; // nombre accion
	int comparar1,comparar2,vt;
	
	
	printf("Ingrese el nombre de la persona:  \n");
	scanf("%s",&nomp);
	printf("Ingrese el nombre de la accion realizada por la persona:  \n");
	scanf("%s",&noma);
	auxc=p;
	auxf=*q;
	while(auxc!=NULL)
	{
		auxa=auxc->primeracc;
		while(auxa!=NULL)
		{
			comparar1=strcmp(auxa->accion,noma);
			if(comparar1==0)
			{
				while(auxf!=NULL)
				{
					auxn=auxf->primernac;
					while(auxn!=NULL)
					{
						comparar2=strcmp(auxn->nombre,nomp);
						if(comparar2==0)
						{
							nuevo=(bond*)malloc(sizeof(bond));
							nuevo->proxb=auxn->pbondad;
							auxn->pbondad=nuevo;
							nuevo->vt=auxa->valoracc + auxc->valorc;
							strcpy(nuevo->bondad,auxa->accion);	
							printf("ingrese el dia en el cual se realizo la buena accion:  \n");
							scanf("%d",&nuevo->dia);
							printf("ingrese el mes en el cual se realizo la bondad:  \n");
							scanf("%d",&nuevo->mes);
							printf("ingrese el año en el cual se realizo la bondad:  \n");
							scanf("%d",&nuevo->anio);
							auxn->pbondad=nuevo;
							
						
							
						}
						
						auxn=auxn->proxnac;	
					}
				
					
					auxf=auxf->proxfe;
				}
			}	
			auxa=auxa->proxacc;
		}
		auxc=auxc->proxctg;
	}
		
}


void MostrarComportamiento(fec *p)
{
	fec *auxf; nac*auxn; pec *auxp; bond *auxb;
	auxf=p;
	int opcion, comparar;
	char nom[20];
	
	printf("Ingrese el nombre de la persona de la cual desea ver su comportamiento:  \n");
	scanf("%s",&nom);	
	while(auxf!=NULL)
	{
		
		auxn=auxf->primernac;
		while(auxn!=NULL)
		{
		
			comparar=strcmp(auxn->nombre,nom);
			if(comparar==0)
			{
				printf("Ingrese 1 si desea mostrar los pecados de la persona o 2 si desea mostrar las buenas accionesde la persona:  \n");
				scanf("%d",&opcion);
				if(opcion==1)
				{
					
					auxp=auxn->ppecado;
					while(auxp!=NULL)
					{
							printf("%s[%d]->",auxp->pecado,auxp->vt);
							auxn->maldad= auxn->maldad + auxp->vt;
							auxp=auxp->proxp;
       				}
       						printf("NULL \n");
       						printf("indice maldad = %d", auxn->maldad);
							auxn->maldad=0;
       						system("PAUSE");
							menu();
				}
				else if(opcion==2)
				{
					
					auxb=auxn->pbondad;
					while(auxb!=NULL)
					{
						printf("%s[%d]->",auxb->bondad,auxb->vt);
						auxn->bondad= auxn->bondad + auxb->vt;
						auxb=auxb->proxb;	
					
										
					}
					printf("NULL \n");
					printf("indice bondad= %d", auxn->bondad);
					auxn->bondad=0;
					system("PAUSE");
					menu();
				}
				else
				{
		  			printf("Opcion Invalida, intente nuevamente. \n");
		  			system("PAUSE");
					menu();
				}
					
			}
			else
			auxn=auxn->proxnac;	
		}
		auxf=auxf->proxfe;
	} 
	printf("El nombre indicado no existe. Intente nuevamente.");
}


//MENUS

void menu()
{
 int opcion, opcionacc, opcionctg;
 system("cls");
 system("color 72"); 
 printf("                    Arbol de la vida \n\n");
 printf("		Administracion de nacimientos \n\n");
 printf("1. Crear Nacimiento \n\n");
 printf("		Administracion de categorias (Buenas y malas) \n\n");
 printf("2. Crear Categoria \n");  
 printf("3. Crear accion \n");
 printf("4. Muestra la lista de Categorias (Malas o buenas acciones)\n");
 printf("5. Muestra la lista de acciones por categoria \n");
 printf("6. Muestra la lista de acciones en General (todos los pecados o buenas acciones) \n");
 printf("7. Cambiar el Valor de una categoria \n");
 printf("8. Cambiar el Valor de una accion \n");
 printf("9. Eliminar una categoria que no contenga acciones\n");
 printf("10. Eliminar una accion de la lista de categorias\n\n");
 printf(" 		Administracion de personas\n\n");
 printf("11. Agregar una accion una persona\n");
 printf("12. Consultar el comportamiento de una persona \n");
 scanf("%d",&opcion);
 system("cls");
  switch(opcion)
  {
   case 1:
   	      system("color F1");
   	      primerf=comprobarFecha(primerf);
   	      mostrarNacimiento(primerf);
   	      system("PAUSE");
		  system("cls");
   	      menu();
          break;
   case 2:
   	      system("color F1");
   	   	  printf("Que desea ingresar? \n");
   	      printf("Coloque 1 para categoria de malas acciones.  \n");
   	      printf("Coloque 2 para categoria de buenas acciones.  \n");
   	      scanf("%d",&opcionctg);
   	      if(opcionctg==1)
   	      {
   	      	          system("color 04");
   	      	   	      primerctgp=crearCategoria(primerctgp);
   	                  mostrarCategoria(primerctgp);
			 }
		  else if(opcionctg==2)
		  {
		  	          system("color F1");
		  	   	      primerctgb=crearCategoria(primerctgb);
   	                  mostrarCategoria(primerctgb);
		  }
		  else
		  printf("Opcion Invalida, intente nuevamente. \n");
		  system("PAUSE");
		  system("cls");
		  menu();
          break;
   case 3:
   	      printf("Que desea ingresar?:  \n");
   	      printf("Coloque 1 para Pecados.  \n");
   	      printf("Coloque 2 para Bondades.  \n");
   	      scanf("%d",&opcionacc);
   	      if(opcionacc==1)
   	      {
   	      	    system("color 04");
   	        	primerctgp=crearAccion(primerctgp);
   	            
			 }
	      else if(opcionacc==2)
	      {		
	      		system("color F1");
	      	    primerctgb=crearAccion(primerctgb);
	      	
		  }
		  else
		  printf("Opcion Invalida, intente nuevamente. \n");
		  system("PAUSE");
		  system("cls");
		  menu();
          break;
          
	case 4:
   	      printf("Cual lista de categorias desea consultar?:  \n");
   	      printf("Coloque 1 para Malas acciones.  \n");
   	      printf("Coloque 2 para Buenas acciones.  \n");
   	      scanf("%d",&opcionacc);
   	      if(opcionacc==1)
   	      {
   	      		system("color 04");
   	        	mostrarCategoria(primerctgp);
   	            
			 }
	      else if(opcionacc==2)
	      {
	      		system("color F1");
	      		mostrarCategoria(primerctgb);
	      	
		  }
		  else
		  printf("Opcion Invalida, intente nuevamente. \n");
		  system("PAUSE");
		  system("cls");
		  menu();
          break;
   case 5:
          printf("Coloque 1 para ingresar una categoria mala.  \n");
   	      printf("Coloque 2 para ingresar una categoria buena.  \n");
   	      scanf("%d",&opcionctg);
   	      if(opcionctg==1)
   	      {
   	      			  system("color 04");
   	      	   	      mostrarAccionpC(primerctgp);
   	                  
			 }
		  else if(opcionctg==2)
		  {
		  			  system("color F1");
		  	   	      mostrarAccionpC(primerctgb);
   	                  
		  }
		  else
		  printf("Opcion Invalida, intente nuevamente. \n");
          system("PAUSE");
          system("cls");
          menu();
          break;
   case 6:
          printf("Coloque 1 para mostrar todos los pecados.  \n");
   	      printf("Coloque 2 para mostrar todas las buenas acciones.  \n");
   	      scanf("%d",&opcionctg);
   	      if(opcionctg==1)
          {
          system("color 04");	
   	      mostrarAcciones(primerctgp);
   	                  
          }
		  else if(opcionctg==2)
		  {
		  system("color F1");
          mostrarAcciones(primerctgb);
   	                  
		  }
		  else
		  printf("Opcion Invalida, intente nuevamente. \n");
		  system("PAUSE");          
          menu();
          break;
    case 7:
          printf("Coloque 1 para modificar el valor de una categoria mala.  \n");
   	      printf("Coloque 2 para modificar el valor de una categoria buena.  \n");
   	      scanf("%d",&opcionctg);
   	      if(opcionctg==1)
          {
          	system("color 04");
   	    	modificarCTG(primerctgp);
   	                  
          }
		  else if(opcionctg==2)
		  {
		  system("color F1");
          modificarCTG(primerctgb);
   	                  
		  }
		  else
		  printf("Opcion Invalida, intente nuevamente. \n");
		  system("PAUSE");          
          menu();
          break;
    case 8:
          printf("Coloque 1 para modificar el valor de un pecado.  \n");
   	      printf("Coloque 2 para modificar el valor de una buena accion.  \n");
   	      scanf("%d",&opcionctg);
   	      if(opcionctg==1)
          {
          	system("color 04");
   	    	modificarAccion(primerctgp);
   	                  
          }
		  else if(opcionctg==2)
		  {
		  system("color F1");
          modificarAccion(primerctgb);
   	                  
		  }
		  else
		  printf("Opcion Invalida, intente nuevamente. \n");
		  system("PAUSE");          
          menu();
          break;
    case 9:
    	  printf("Coloque 1 para eliminar una categoria mala.  \n");
   	      printf("Coloque 2 para para eliminar una categoria buena.  \n");
   	      scanf("%d",&opcionctg);
   	      if(opcionctg==1)
          {
          	system("color 04");
   	    	primerctgp=EliminarCategoria(primerctgp);
   	    
   	                  
          }
		  else if(opcionctg==2)
		  {
		  system("color F1");
          primerctgb=EliminarCategoria(primerctgb);
   	                  
		  }
		  else
		  printf("Opcion Invalida, intente nuevamente. \n");
		  system("PAUSE");          
          menu();
          break;
    case 10:
    	  printf("Coloque 1 para eliminar un pecado.  \n");
   	      printf("Coloque 2 para para eliminar una buena accion.  \n");
   	      scanf("%d",&opcionctg);
   	      if(opcionctg==1)
          {
          	system("color 04");
   	    	primerctgp=EliminarAccion(primerctgp);
   	        menu();
   	                  
          }
		  else if(opcionctg==2)
		  {
		  system("color F1");
          primerctgb=EliminarAccion(primerctgb);
   	      menu();         
		  }
		  else
		  printf("Opcion Invalida, intente nuevamente. \n");
		  system("PAUSE");          
          menu();
          break;
    case 11:
    	  printf("Coloque 1 para agregar un pecado a una persona.  \n");
   	      printf("Coloque 2 para agregar una buena accion a una persona.  \n");
   	      scanf("%d",&opcionctg);
   	      if(opcionctg==1)
          {
            system("color 04");
   	    	FaltasCometidas(&primerf, primerctgp);
   	    	system("PAUSE");
   	        menu();
   	                  
          }
		  else if(opcionctg==2)
		  {
		  	system("color F1");
          	BuenasAcciones(&primerf, primerctgb);
          	system("PAUSE");
          	menu();
   	                  
		  }
		  else
		  printf("Opcion Invalida, intente nuevamente. \n");
		  system("PAUSE");          
          menu();
          break;
    case 12:
    	  MostrarComportamiento(primerf);
		  system("PAUSE");          
          menu();
          break;
    	  
        
          
   default:
   	       printf("Ha marcado una opcion incorrecta por favor intente nuevamente.  \n");
   	       system("PAUSE");
   	       system("cls");
   	       system("cls");
   		   menu();
           break;
                        
  }
}



main()
{
	printf("Notas importantes: \n\n");
	printf("- En cualquier cadena de caracteres reequerida en el programa se deben sustuir los espacios por ( _ ) \n");
	printf("- Por la falta de tiempo solo se pueden introducir categorias de distintas longitudes.\n");
	printf("- Por la falta de tiempo solo se pueden introducir acciones de distintas longitudes.\n\n");
	printf("Pedimos Disculpas por estos inconvenientes, estos seran arreglados para la entrega final.\n");
	
	system("PAUSE");
	menu();
}

