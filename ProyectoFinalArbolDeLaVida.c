#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

#define TRUE 1
#define FALSE 0


enum {IZQUIERDO, DERECHO};

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
        int maldad, bondad, expiacion, comport, codigo;
        char nombre[40];
        char genero;
        char pais[20];
        int FE;
        struct nacimiento *derecho;
        struct nacimiento *izquierdo;
        struct nacimiento *padre;
        struct pecados *ppecado;
        struct bondades *pbondad;
        struct contricciones *pcont;
}nac;
nac *primerA=NULL;
nac *primerD=NULL;

typedef nac *pNodo;
typedef nac *Arbol;

typedef struct destino
{
	char nombre[40];
	char genero;
	char pais[20];
	int codigo, comport;
	struct destino *proxd;
} des;

des *primerciel=NULL;
des *primerinf=NULL;


typedef struct purgatorio
{
	char nombre[40];
	char genero;
	char pais[20];
	int codigo, comport, at, anio; //anio terrenal
	char penitencia[40];
	struct purgatorio *proxpurg;

} purg;
purg *primerpurg=NULL;

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

typedef struct contricciones
{
	char pecado[20];
	int vt, dia, mes, anio; //valor total
	struct contricciones *proxcont;
} cont;

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


//PROTOTIPOS:
// Procesos y funciones Propias:
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
void BuenasAcciones(fec**q, ctg*p);
void Arrepentimientos(fec **q);
des *insertarDestino(des *p, nac *auxn);
purg *insertarPurgatorio(purg *p, nac *auxn);
void mostrarDestino(des *p);
void mostrarPurgatorio(purg *p);
void Perdon(purg **p, des **q);
void MostrarDatos(fec *p);
void mostrarFechas(fec *p);
nac *BuscarDevolver(Arbol a, int dat);
void mostrararbol(fec *p);
void CalcularIndices(fec **p,int codigo);
void InsertarDemonio(nac **d, des **auxd);

// Rutinas básicas de Arboles:
void Insertar(Arbol *a, int dat, char nomb[40],char pa[20], char gen);
void Equilibrar(Arbol *a, pNodo nodo, int rama, int nuevo);
void Borrar(Arbol *a, int dat);
int Buscar(Arbol a, int dat);
int Vacio(Arbol r);
int EsHoja(pNodo r);
int NumeroNodos(Arbol a, int* c);
int AlturaArbol(Arbol a, int* altura);
int Altura(Arbol a, int dat);
void InOrden(Arbol, void (*func)(int*));
void PreOrden(Arbol, void (*func)(int*));
void PostOrden(Arbol, void (*func)(int*));
void Equilibrar(Arbol *raiz, pNodo nodo, int, int);
void RSI(Arbol *raiz, pNodo nodo);
void RSD(Arbol *raiz, pNodo nodo);
void RDI(Arbol *raiz, pNodo nodo);
void RDD(Arbol *raiz, pNodo nodo);
void Podar(Arbol *a);
void auxContador(Arbol a, int*);
void auxAltura(Arbol a, int, int*);
void dibujar (Arbol a, int nivel);


//Procesos Arboles

/* Poda: borrar todos los nodos a partir de uno, incluido */
void Podar(Arbol *a)
{
   /* Algoritmo recursivo, recorrido en postorden */
   if(*a)
    {
      Podar(&(*a)->izquierdo); /* Podar izquierdo */
      Podar(&(*a)->derecho);   /* Podar derecho */
      free(*a);                /* Eliminar nodo */
      *a = NULL;
		
   }
}

/* Insertar un dato en el árbol ABB */
void Insertar(Arbol *a, int dat, char nomb[40], char pa[20], char gen)
{
	
   pNodo padre = NULL;
   pNodo actual = *a;
	
   /* Buscar el dato en el árbol, manteniendo un puntero al nodo padre */
   while(!Vacio(actual) && dat != actual->codigo) {
      padre = actual;
      if(dat < actual->codigo) actual = actual->izquierdo;
      else if(dat > actual->codigo) actual = actual->derecho;
   }

   /* Si se ha encontrado el elemento, regresar sin insertar */
   if(!Vacio(actual)) return;
   
	
   /* Si padre es NULL, entonces el árbol estaba vacío, el nuevo nodo será
      el nodo raiz */
   if(Vacio(padre))
    {
      *a = (Arbol)malloc(sizeof(nac));
      (*a)->codigo = dat;
      (*a)->izquierdo = (*a)->derecho = NULL;
      (*a)->padre = NULL;
      (*a)->FE = 0;   
	   strcpy((*a)->nombre,nomb);fflush(stdin);
	   strcpy((*a)->pais,pa);	   
	   (*a)->genero=gen;
	   (*a)->bondad=0;
	   (*a)->maldad=0;
	   (*a)->expiacion=0;
	   (*a)->ppecado=NULL;
	   (*a)->pbondad=NULL;
	   (*a)->pcont=NULL;       	
   }
   /* Si el dato es menor que el que contiene el nodo padre, lo insertamos
      en la rama izquierda */
   else
     if(dat < padre->codigo) {
      actual = (Arbol)malloc(sizeof(nac));
      padre->izquierdo = actual;
      actual->codigo = dat;
      actual->izquierdo = actual->derecho = NULL;
      actual->padre = padre;
      actual->FE = 0;
      strcpy(actual->nombre,nomb);
	  strcpy(actual->pais,pa);	   
	  actual->genero=gen;
	  actual->bondad=0;
	  actual->maldad=0;
	  actual->expiacion=0;
	  actual->ppecado=NULL;
	  actual->pbondad=NULL;
	  actual->pcont=NULL;
      
      Equilibrar(a, padre, IZQUIERDO, TRUE);
     
   }
   /* Si el dato es mayor que el que contiene el nodo padre, lo insertamos
      en la rama derecha */
   else if(dat > padre->codigo) {
      actual = (Arbol)malloc(sizeof(nac));
      padre->derecho = actual;
      actual->codigo = dat;
      actual->izquierdo = actual->derecho = NULL;
      actual->padre = padre;
      actual->FE = 0;
      strcpy(actual->nombre,nomb);
	  strcpy(actual->pais,pa);	   
	  actual->genero=gen;
	  actual->bondad=0;
	  actual->maldad=0;
	  actual->expiacion=0;
	  actual->ppecado=NULL;
	  actual->pbondad=NULL;
	  actual->pcont=NULL;
      Equilibrar(a, padre, DERECHO, TRUE);     
  }	   
}

/* Equilibrar árbol AVL partiendo del nodo nuevo */
void Equilibrar(Arbol *a, pNodo nodo, int rama, int nuevo)
{
   int salir = FALSE;

   /* Recorrer camino inverso actualizando valores de FE: */
   while(nodo && !salir) {
      if(nuevo)
         if(rama == IZQUIERDO) nodo->FE--; /* Depende de si añadimos ... */
         else                  nodo->FE++;
      else
         if(rama == IZQUIERDO) nodo->FE++; /* ... o borramos */
         else                  nodo->FE--;
      if(nodo->FE == 0) salir = TRUE; /* La altura de las rama que
                                         empieza en nodo no ha variado,
                                         salir de Equilibrar */
      else if(nodo->FE == -2) { /* Rotar a derechas y salir: */
         if(nodo->izquierdo->FE == 1) RDD(a, nodo); /* Rotación doble  */
         else RSD(a, nodo);                         /* Rotación simple */
         salir = TRUE;
      }
      else if(nodo->FE == 2) {  /* Rotación a la izquierda y salir: */
         if(nodo->derecho->FE == -1) RDI(a, nodo); /* Rotación doble  */
         else RSI(a, nodo);                        /* Rotación simple */
         salir = TRUE;
      }
      if(nodo->padre)
         if(nodo->padre->derecho == nodo) rama = DERECHO;
        else rama = IZQUIERDO;
      nodo = nodo->padre; /* Calcular FE, siguiente nodo del camino. */
   }
}

/* Rotación doble a la derecha */
void RDD(Arbol *raiz, Arbol nodo)
{
   pNodo Padre = nodo->padre;
   pNodo P = nodo;
   pNodo Q = P->izquierdo;
   pNodo R = Q->derecho;
   pNodo B = R->izquierdo;
   pNodo C = R->derecho;

   if(Padre)
     if(Padre->derecho == nodo) Padre->derecho = R;
     else Padre->izquierdo = R;
   else *raiz = R;

   /* Reconstruir árbol: */
   Q->derecho = B;
   P->izquierdo = C;
   R->izquierdo = Q;
   R->derecho = P;

   /* Reasignar padres: */
   R->padre = Padre;
   P->padre = Q->padre = R;
   if(B) B->padre = Q;
   if(C) C->padre = P;

   /* Ajustar valores de FE: */
   switch(R->FE) {
      case -1: Q->FE = 0; P->FE = 1; break;
      case 0:  Q->FE = 0; P->FE = 0; break;
      case 1:  Q->FE = -1; P->FE = 0; break;
   }
   R->FE = 0;
}

/* Rotación doble a la izquierda */
void RDI(Arbol *a, pNodo nodo)
{
   pNodo Padre = nodo->padre;
   pNodo P = nodo;
   pNodo Q = P->derecho;
   pNodo R = Q->izquierdo;
   pNodo B = R->izquierdo;
   pNodo C = R->derecho;

   if(Padre)
     if(Padre->derecho == nodo) Padre->derecho = R;
     else Padre->izquierdo = R;
   else *a = R;

   /* Reconstruir árbol: */
   P->derecho = B;
   Q->izquierdo = C;
   R->izquierdo = P;
   R->derecho = Q;

   /* Reasignar padres: */
   R->padre = Padre;
   P->padre = Q->padre = R;
   if(B) B->padre = P;
   if(C) C->padre = Q;

   /* Ajustar valores de FE: */
   switch(R->FE) {
      case -1: P->FE = 0; Q->FE = 1; break;
      case 0:  P->FE = 0; Q->FE = 0; break;
      case 1:  P->FE = -1; Q->FE = 0; break;
   }
   R->FE = 0;
}

/* Rotación simple a la derecha */
void RSD(Arbol *a, pNodo nodo)
{
   pNodo Padre = nodo->padre;
   pNodo P = nodo;
   pNodo Q = P->izquierdo;
   pNodo B = Q->derecho;

   if(Padre)
     if(Padre->derecho == P) Padre->derecho = Q;
     else Padre->izquierdo = Q;
   else *a = Q;

   /* Reconstruir árbol: */
   P->izquierdo = B;
   Q->derecho = P;

   /* Reasignar padres: */
   P->padre = Q;
   if(B) B->padre = P;
   Q->padre = Padre;

   /* Ajustar valores de FE: */
   P->FE = 0;
   Q->FE = 0;
}

/* Rotación simple a la izquierda */
void RSI(Arbol *a, pNodo nodo)
{
   pNodo Padre = nodo->padre;
   pNodo P = nodo;
   pNodo Q = P->derecho;
   pNodo B = Q->izquierdo;

   if(Padre)
     if(Padre->derecho == P) Padre->derecho = Q;
     else Padre->izquierdo = Q;
   else *a = Q;

   /* Reconstruir árbol: */
   P->derecho = B;
   Q->izquierdo = P;

   /* Reasignar padres: */
   P->padre = Q;
   if(B) B->padre = P;
   Q->padre = Padre;

   /* Ajustar valores de FE: */
   P->FE = 0;
   Q->FE = 0;
}

/* Eliminar un elemento de un árbol ABB */
void Borrar(Arbol *a, int dat)
{
   pNodo padre = NULL;
   pNodo actual, temporal;
   pNodo nodo;
   int aux, cond;

   actual = *a;
   cond=FALSE;
   /* Mientras sea posible que el valor esté en el árbol */
   while(!Vacio(actual)) 
   {
      if(dat == actual->codigo)
	   { /* Si el valor está en el nodo actual */
			if(cond==FALSE)
			{
				temporal=actual;
            	printf("Persona que va a morir : %s \n",temporal->nombre);
			
            	
				if(temporal->comport > 500)
				{		
					primerciel=insertarDestino(primerciel, temporal);
					printf("La persona ira al cielo por su buen comportamiento. \n");				
				}
				else if((temporal->comport>=200)&(temporal->comport <= 500))
				{
					primerpurg=insertarPurgatorio(primerpurg, temporal);
					printf("La persona ira al purgatorio a saldar sus deudas. \n");				
				}
				else
				{
					primerinf=insertarDestino(primerinf, temporal);
					printf("La persona ira al infierno por su mal comportamiento. \n");
				}
				cond=TRUE;
				system("PAUSE");    
			}
		
			
         if(EsHoja(actual))
		  { /* Y si además es un nodo hoja: lo borramos */
            if(padre) /* Si tiene padre (no es el nodo raiz) */
            {
			
               /* Anulamos el puntero que le hace referencia */
               if(padre->derecho == actual)
			    padre->derecho = NULL;
               else if(padre->izquierdo == actual)
			    padre->izquierdo = NULL;
							   
				free(actual); /* Borrar el nodo */
            	actual = NULL;            
            
            /* El nodo padre del actual puede ser ahora un nodo hoja, por lo
            tanto su FE es cero, pero debemos seguir el camino a partir de
            su padre, si existe. */		  
            	if((padre->derecho == actual && padre->FE == 1) || (padre->izquierdo == actual && padre->FE == -1))
			 	{
			 
               		padre->FE = 0;
               		actual = padre;
               		padre = actual->padre;
            	}
          		if(padre)
               		if(padre->derecho == actual) Equilibrar(a, padre, DERECHO, FALSE);
               		else                         Equilibrar(a, padre, IZQUIERDO, FALSE);	                
		
            	return;
         	}
        	else
        	{
        		free(actual);
        		*a=NULL;
        		return;
			}
		 }
         else  /* Si el valor está en el nodo actual, pero no es hoja */
		  { 
            padre = actual;

            /* Buscar nodo más derecho de rama izquierda */
            if(actual->izquierdo) {
               nodo = actual->izquierdo;
               while(nodo->derecho) {
                  padre = nodo;
                  nodo = nodo->derecho;
               }
            }
            /* O Buscar nodo más izquierdo de rama derecha */
            else {
               nodo = actual->derecho;
               while(nodo->izquierdo) {
                  padre = nodo;
                  nodo = nodo->izquierdo;
               }
            }
            /* Intercambiar valores de no a borrar u nodo encontrado
            y continuar, cerrando el bucle. El nodo encontrado no tiene
            por qué ser un nodo hoja, cerrando el bucle nos aseguramos
            de que sólo se eliminan nodos hoja. */
            aux = actual->codigo;
            actual->bondad=nodo->bondad;
            actual->maldad=nodo->maldad;
            actual->expiacion=nodo->expiacion;
            actual->comport=nodo->comport;
            actual->genero=nodo->genero;
            actual->pbondad=nodo->pbondad;
            actual->ppecado=nodo->ppecado;
            actual->pcont=nodo->pcont;
            strcpy(actual->nombre,nodo->nombre);
            strcpy(actual->pais,nodo->pais);
            actual->codigo = nodo->codigo;
            nodo->codigo = aux;
            actual = nodo;
         }
      }
      else { /* Todavía no hemos encontrado el valor, seguir buscándolo */
         padre = actual;
         if(dat > actual->codigo) actual = actual->derecho;
         else if(dat < actual->codigo) actual = actual->izquierdo;
      }
   }
   			    
}

/* Recorrido de árbol en inorden, aplicamos la función func, que tiene
   el prototipo:
   void func(int*);
*/
void InOrden(Arbol a, void (*func)(int*))
{
   if(a->izquierdo) InOrden(a->izquierdo, func);
   func(&(a->codigo));
   if(a->derecho) InOrden(a->derecho, func);
}

/* Recorrido de árbol en preorden, aplicamos la función func, que tiene
   el prototipo:
   void func(int*);
*/
void PreOrden(Arbol a, void (*func)(int*))
{
   func(&a->codigo);
   if(a->izquierdo) PreOrden(a->izquierdo, func);
   if(a->derecho) PreOrden(a->derecho, func);
}

/* Recorrido de árbol en postorden, aplicamos la función func, que tiene
   el prototipo:
   void func(int*);
*/
void PostOrden(Arbol a, void (*func)(int*))
{
   if(a->izquierdo) PostOrden(a->izquierdo, func);
   if(a->derecho) PostOrden(a->derecho, func);
   func(&a->codigo);
}

/* Buscar un valor en el árbol */
int Buscar(Arbol a, int dat)
{
   pNodo actual = a;

   /* Todavía puede aparecer, ya que quedan nodos por mirar */
   while(!Vacio(actual))
    {
      if(dat == actual->codigo) return TRUE; /* dato encontrado */
      else if(dat < actual->codigo) actual = actual->izquierdo; /* Seguir */
      else if(dat > actual->codigo) actual = actual->derecho;
   	}

   	return FALSE; /* No está en árbol */
}


nac *BuscarDevolver(Arbol a, int dat) /* Busca y devuelve el nodo que contiene el codigo correspondiente*/
{
	pNodo actual = a;
	
    while(!Vacio(actual))
    {
      if(dat == actual->codigo)/* dato encontrado */
	   return(actual);
	   
      else if(dat < actual->codigo)
	   actual = actual->izquierdo; /* Seguir */
	   
      else if(dat > actual->codigo) 
	   actual = actual->derecho;
    }   
}

/* Calcular la altura del nodo que contiene el dato dat */
int Altura(Arbol a, int dat)
{
   int altura = 0;

   pNodo actual = a;

   /* Todavía puede aparecer, ya que quedan nodos por mirar */
   while(!Vacio(actual)) {
      if(dat == actual->codigo) return altura; /* encontrado: devolver altura */
      else {
         altura++; /* Incrementamos la altura, seguimos buscando */
         if(dat < actual->codigo) actual = actual->izquierdo;
         else if(dat > actual->codigo) actual = actual->derecho;
      }
   }
   return -1; /* No está en árbol, devolver -1 */
}
/* Contar el número de nodos */
int NumeroNodos(Arbol a, int *contador)
{
   *contador = 0;

   auxContador(a, contador); /* Función auxiliar */
   return *contador;
}

/* Función auxiliar para contar nodos. Función recursiva de recorrido en
   preorden, el proceso es aumentar el contador */
void auxContador(Arbol nodo, int *c)
{
   (*c)++; /* Otro nodo */
   /* Continuar recorrido */
   if(nodo->izquierdo) auxContador(nodo->izquierdo, c);
   if(nodo->derecho)   auxContador(nodo->derecho, c);
}

/* Calcular la altura del árbol, que es la altura del nodo de mayor altura. */
int AlturaArbol(Arbol a, int *altura)
{
   *altura = 0;

   auxAltura(a, 0, altura); /* Función auxiliar */
   return *altura;
}

/* Función auxiliar para calcular altura. Función recursiva de recorrido en
   postorden, el proceso es actualizar la altura sólo en nodos hojas de mayor
   altura de la máxima actual */
void auxAltura(pNodo nodo, int a, int *altura)
{
   /* Recorrido postorden */
   if(nodo->izquierdo) auxAltura(nodo->izquierdo, a+1, altura);
   if(nodo->derecho)   auxAltura(nodo->derecho, a+1, altura);
   /* Proceso, si es un nodo hoja, y su altura es mayor que la actual del
      árbol, actualizamos la altura actual del árbol */
   if(EsHoja(nodo) && a > *altura) *altura = a;
}

/* Comprobar si un árbol es vacío */
int Vacio(Arbol r)
{
   return r==NULL;
}

/* Comprobar si un nodo es hoja */
int EsHoja(pNodo r)
{
   return !r->derecho && !r->izquierdo;
}

/* mostrar Arbol*/
void Mostrar(int *d)
{
   printf("%d, ", *d);
}

void dibujar (Arbol a, int nivel)
{
 int i;

 if (a != NULL)
 {
   dibujar (a-> derecho, nivel + 1);
   for (i=1; i<=nivel; i++)
     printf ("  ");
   printf ("[%d]\n", a->codigo);
   dibujar (a-> izquierdo, nivel + 1);
 }
}

//PROCESOS FECHA-NACIMIENTO

fec *comprobarFecha(fec *p) // Comprueba si la fecha existe en la lista de Fechas , en caso contrario crea la nueva fecha
{
int dia, mes, anio, codigo;      
	fec *auxf;
	auxf=p; 
		
		printf("Dia del nacimiento:  ");
     	scanf("%d",&dia);
     	printf("Mes del nacimiento:  ");
     	scanf("%d",&mes);
     	printf("Anio del nacimiento: ");
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
	
	 	p=crearNacimiento(p);
	 	 
	 
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
fec *crearNacimiento(fec *q) //Funcion que crea un nodo en el arbol de nacimientos de cada fecha.
{
	int x; // codigo de la persona.
   int altura;
   int nnodos;
   	char nomb[40];
	char gen;
	char pa[20];
   nac *auxn; fec *auxf;
   auxf=q;
   
   	printf ("Insertar  el codigo con el que identificara a la persona en el Arbol: ");
	scanf ("%d",&x);  fflush(stdin);
	printf("Insertar el nombre completo : ");
	scanf("%s",&nomb); fflush(stdin);    
	printf("Indique su pais: ");
	scanf("%s",&pa);fflush(stdin); 
	printf("Ingrese su genero(m/f)): ");
	scanf("%c",&gen);fflush(stdin);     
    Insertar(&(auxf->primernac), x, nomb , pa, gen);
    CalcularIndices(&auxf,x);
    printf("\nNacimiento creado exitosamente. \n\n");
    dibujar(auxf->primernac,0);
    return(q);
}



ctg *crearCategoria(ctg *p) //Funcion que crea una categoria en la lista de categorias.
{
	char nombrec[20];
	int valor;
	ctg *nuevo;
	nuevo=((ctg*)malloc(sizeof(ctg)));
    printf("Ingrese el nombre de la categoria a crear: ");
	scanf("%s",&nombrec);fflush(stdin);
	strcpy(nuevo->categoria,nombrec);
	printf("Indique el valor de la categoria: ");
	scanf("%d",&valor);
	nuevo->valorc=valor;
	nuevo->proxctg=p;
	nuevo->primeracc=NULL;
    
	return(nuevo);
	
}

void mostrarCategoria(ctg *p)  //Funcion que muestra la lista de categorias.
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

ctg *crearAccion(ctg *q) //  Funcion que crea una accion en la lista de categorias correspondiente.
{
	char nombrea[20], nombrec[20];
	int valor,comparar; 
	ctg *auxc; acc *auxa;
	auxc=q;
	printf("Ingrese el nombre de la categoria a donde desea ingresar la accion: ");
	scanf("%s",&nombrec);fflush(stdin);
	while(auxc!=NULL)
	{
        comparar=strcmp(auxc->categoria,nombrec);
		if(comparar==0)
		{	
		acc *nuevo;
		nuevo=(acc*)malloc(sizeof(acc));
		nuevo->proxacc=auxc->primeracc;
		auxc->primeracc=nuevo;
		printf("Ingrese el nombre de la accion: ");
		scanf("%s",&nombrea);fflush(stdin);
		strcpy(nuevo->accion,nombrea);
		printf("Ingrese el valor de la accion: ");
		scanf("%d",&valor);
		nuevo->valoracc=valor;
		return(q); 		
	    }
	    else
	  	auxc=auxc->proxctg;	  	
	}	
	if(auxc==NULL)
		{
			printf("La categoria indicada no existe, para agregar un pecado cree primero la categoria. \n");
			system("PAUSE");
			menu();
		}
}

void mostrarAccionpC(ctg *q) //Funcion que muestra la lista de acciones de una categoria especifica.
{
     ctg *auxc; acc *auxa;
     int comparar;
     char nombrec[20];
     auxc=q;
     printf("Ingrese el nombre de la categoria: ");
     scanf("%s",nombrec);fflush(stdin);
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
 

void mostrarAcciones(ctg *p)  //Funcion que muestra las listas con todas las acciones de todas las categorias.
{
	acc *auxa; 
	ctg *auxc;
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

ctg *modificarCTG(ctg *p) //Funcion que permite modificar el valor de una categoria.
{
	ctg *aux;  
	int valor,comparar;
	char nombre[20];
	aux=p; 
	
	printf("Ingrese el nombre de la categoria a la cual modificara el valor: ");
	scanf("%s",&nombre);fflush(stdin);
	printf("Ingrese el nuevo valor: ");
	scanf("%d",&valor);
		
	while(aux!= NULL)
	{
        comparar=strcmp(aux->categoria,nombre);
		if(comparar==0) 
		{
			aux->valorc=valor;
		}
		aux=aux->proxctg;
		
	}
	return(p); 
}

ctg *modificarAccion(ctg *p) //Funcion que permite modificar el valor de una accion dentro de una categoria.
{
	acc *auxa;
	 ctg*auxc;
	int valor,comparar;
	char nombre[20];
	auxc=p;
	
	printf("Ingrese el nombre de la accion al cual modificara el valor: ");
	scanf("%s",&nombre);fflush(stdin);
	printf("Ingrese el nuevo valor: ");
	scanf("%d",&valor);
		
	while(auxc!= NULL)
	{
		auxa=auxc->primeracc;
		while(auxa!=NULL)
		{
            comparar=strcmp(auxa->accion,nombre);
			if(comparar==0) 	
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
ctg *EliminarCategoria(ctg *p) //Funcion que elimina una categoria indicada de la lista de categorias correspondiente.
{
	ctg *auxc, *antc;
	acc*auxa;
	char nombre[20];
	auxc=p;
	int i=0; // boolean que indica si se debe borrar la primera o las demas.
	int comparar; // boolean que indica si las categorias tienen la misma longitud.
	
	printf("Ingrese el nombre de la categoria a eliminar: ");
	scanf("%s",&nombre);fflush(stdin);
	while(auxc!=NULL)
	{
		auxa=auxc->primeracc;
        comparar=strcmp(auxc->categoria,nombre);
		if((comparar==0)&&(auxa==NULL)&&(i==0)) 
		{	antc=auxc->proxctg; 
			free(auxc);
			auxc=antc;
			p=auxc;
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

}

ctg *EliminarAccion(ctg *p) //Funcion que elimina una accion indicada de alguna de las listas de categoria.
{
	ctg*auxc;
	acc*auxa,*ant;
	int i=0;
	int comparar;
	char nombre[20];
	auxc=p;
	printf("Ingrese el nombre de la accion que desea eliminar: ");
	scanf("%s",&nombre);fflush(stdin);
	
	while(auxc!=NULL)
	{
		auxa=auxc->primeracc;
		while(auxa!=NULL)
		{
        	comparar=strcmp(auxa->accion,nombre);          
			if((comparar==0)&&(i==0)) // Si es el primer elemento de la lista.
			{
				auxc->primeracc=auxc->primeracc->proxacc; 
				free(auxa);
				auxa=auxc->primeracc;
				return(p);
			
			
			}
			if((comparar==0)&&(i!=0)) //Si es cualquier otro elemento menos el primero.
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
	printf("La accion no existe. Intente Nuevamente.");
	system("PAUSE");
	menu();
	
}

void FaltasCometidas(fec **q, ctg*p) //Proceso que agrega un pecado a la lista de pecados de la persona indicada.
{
	fec *auxf; nac *auxn, *nodo; ctg *auxc; acc *auxa;
	pec *nuevo;
	int codigo; // codigo de la persona
	char noma[20]; // nombre accion
	int comparar1,comparar2,vt;
	
	printf("Ingrese el codigo de la persona: ");
	scanf("%d",&codigo);
	printf("Ingrese el nombre de la accion realizada por la persona: ");
	scanf("%s",&noma);fflush(stdin);
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
				if(auxf==NULL)
				{
					printf("El codigo de la persona no se encuentra el el arbol \n");
					return;
					
				}
				while(auxf!=NULL)
				{
					auxn=auxf->primernac; 							
					comparar2=Buscar(auxn, codigo);
				
						if(comparar2==TRUE)
						{
							
							nodo=BuscarDevolver(auxn,codigo);
							nuevo=(pec*)malloc(sizeof(pec));
							nuevo->proxp=nodo->ppecado;
							nodo->ppecado=nuevo;
							nuevo->vt=auxa->valoracc + auxc->valorc;
							strcpy(nuevo->pecado,auxa->accion);	
							printf("Ingrese el dia en el cual se realizo la falta: ");
							scanf("%d",&nuevo->dia);
							printf("Ingrese el mes en el cual se realizo la falta: ");
							scanf("%d",&nuevo->mes);
							printf("Ingrese el anio en el cual se realizo la falta: ");
							scanf("%d",&nuevo->anio);
							nodo->ppecado=nuevo;
							nodo->maldad=0;													
						}
						else
						{
							printf("El codigo de la persona no se encuentra el el arbol \n");
							system("PAUSE");
							menu();
						}
						CalcularIndices(&auxf,codigo);		
						auxf=auxf->proxfe;					
				}
				printf("Pecado agregado exitosamente a la persona, verifique desde consultar comportamiento en el menu. \n");
				return;						
			}	
			
			auxa=auxa->proxacc;
					
		}	
		auxc=auxc->proxctg;
	}
			
	printf("La accion indicada no existe en la lista de categorias. \n");
	system("PAUSE");
	menu();			
	
	
}

void BuenasAcciones(fec**q, ctg*p) // Proceso que agrega una buena accion o bondad en la lista de bondades de la persona indicada.
{
	fec *auxf; nac *auxn, *nodo; ctg *auxc; acc *auxa;
	bond *nuevo;
	int codigo; // codigo de la persona
	char noma[20]; // nombre accion
	int comparar1,comparar2,vt;
		
	printf("Ingrese el codigo de la persona: ");
	scanf("%d",&codigo);
	printf("Ingrese el nombre de la accion realizada por la persona: ");
	scanf("%s",&noma);fflush(stdin);
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
				if(auxf==NULL)
				{
					printf("El codigo de la persona no se encuentra el el arbol \n");
					return;
					
				}
				while(auxf!=NULL)
				{
					auxn=auxf->primernac; //arbol							
					comparar2=Buscar(auxn, codigo);	
						if(comparar2==TRUE)
						{
							nodo=BuscarDevolver(auxn,codigo);
							nuevo=(bond*)malloc(sizeof(bond));
							nuevo->proxb=nodo->pbondad;
							auxn->pbondad=nuevo;
							nuevo->vt=auxa->valoracc + auxc->valorc;
							strcpy(nuevo->bondad,auxa->accion);	
							printf("Ingrese el dia en el cual se realizo la buena accion: ");
							scanf("%d",&nuevo->dia);
							printf("Ingrese el mes en el cual se realizo la bondad: ");
							scanf("%d",&nuevo->mes);
							printf("Ingrese el anio en el cual se realizo la bondad: ");
							scanf("%d",&nuevo->anio);
							nodo->pbondad=nuevo;
							nodo->bondad=0;						
						}
						else
						{
							printf("El codigo de la persona no se encuentra el el arbol \n");
							system("PAUSE");
							menu();
						}		
					CalcularIndices(&auxf,codigo);
					auxf=auxf->proxfe;
				}
					printf("Buena accion agregada exitosamente a la persona, verifique desde consultar comportamiento en el menu. \n");
					return;	
			}
			auxa=auxa->proxacc;
		}
		auxc=auxc->proxctg;
	}
	
	printf("La accion indicada no existe en la lista de categorias. \n");
	system("PAUSE");
	menu();	
		
}

void Arrepentimientos(fec **q) // Proceso que genera un arrepentimiento en la lista de arrepentimientos de la persona y elimina el pecado del mismo nombre de la lista de pecados de la persona indicada.
{
	fec *auxf;
	nac *auxn , *nodo;
	pec *auxp, *temporal;
	cont *auxcon;
		 
	

	cont *nuevo;
	pec *nuevo2;
	int codigo; // codigo de la persona
	char noma[20]; // nombre accion a arrepentirse
	int comparar1,comparar2,vt,i;
 	int condicion; //condicion para saber si encontro el pecado en la lista de pecados de la persona
	
	printf("Ingrese el codigo de la persona: ");
	scanf("%d",&codigo);
	printf("Ingrese el nombre del pecado arrepentido: ");
	scanf("%s",&noma);fflush(stdin);
	
	condicion=3;
	auxf= *q;
	temporal=NULL;
	
	if(auxf==NULL)
	{
		printf("La persona indicada no existe en el Arbol de la Vida \n\n");
		return;
					
	}
	while (auxf!= NULL)
	{
		auxn=auxf->primernac;
		comparar1=Buscar(auxn, codigo);
		if(comparar1==TRUE)
		{   
			nodo=BuscarDevolver(auxn,codigo);
			auxp=nodo->ppecado;
			while(auxp!=NULL)
			{
				comparar2=strcmp(auxp->pecado,noma);
				if(comparar2==0)
				{
					condicion=TRUE;
					nuevo=(cont*)malloc(sizeof(cont));
					nuevo->proxcont=auxn->pcont;
					nodo->pcont=nuevo;
					nuevo->vt=auxp->vt;
					strcpy(nuevo->pecado,auxp->pecado);	
					printf("Ingrese el dia en el cual se arrepintio del pecado: ");
					scanf("%d",&nuevo->dia);
					printf("Ingrese el mes en el cual se arrepintio del pecado: ");
					scanf("%d",&nuevo->mes);
					printf("Ingrese el anio en el cual se arrepintio del pecado: ");
					scanf("%d",&nuevo->anio);
					nodo->pcont=nuevo;	
					nodo->expiacion=0;
							
				}
				else	//actualiza la lista de pecados
				{
					condicion=FALSE;
					nuevo2=(pec*)malloc(sizeof(pec));
					nuevo2->proxp=temporal;
					nuevo2->anio=auxp->anio;
					nuevo2->mes=auxp->mes;
					nuevo2->dia=auxp->dia;
					strcpy(nuevo2->pecado,auxp->pecado);
					nuevo2->vt=auxp->vt;	
					temporal=nuevo2;
					
				}
				auxp=auxp->proxp;				
		    }
		   
		    nodo->ppecado=temporal;
		    if(condicion==FALSE)
		    {
		    	printf("El pecado no se encuentra en la lista de pecados de la persona indicada. \n");
				system("PAUSE");
				menu();	
			}
		  
		}
	
		CalcularIndices(&auxf,codigo);	
		auxf=auxf->proxfe;
	}
	if(condicion==3)
	{
	
		printf("El pecado no se encuentra en la lista de pecados de la persona indicada o la persona no existe en el arbol\npor favor verifique. \n");
		system("PAUSE");
		menu();
	}
	printf("Pecado arrepentido exitosamente, verifique desde consultar comportamiento en el menu. \n");
}

void CalcularIndices(fec **p,int codigo) //Proceso que recalcula los indices de comportamiento, bondad, maldad y expiacion de la persona indicada.
{
	fec *auxf; nac *auxn, *nodo; pec *auxp; bond *auxb; cont *auxcont;
	int comparar;
	
	auxf=*p;
	
	while(auxf!=NULL) // Calcula los indices desde 0
	{
		auxn=auxf->primernac;
		
		comparar=Buscar(auxn, codigo);
		if(comparar==TRUE)
		{
			nodo=BuscarDevolver(auxn,codigo);
			nodo->maldad=0;
			nodo->bondad=0;
			nodo->expiacion=0;
			auxp=nodo->ppecado;	
			while(auxp!=NULL) //calcula el indice de maldad de la persona.
			{
				nodo->maldad= nodo->maldad + auxp->vt; 
				auxp=auxp->proxp;
       		}
       		auxb=nodo->pbondad;	
			while(auxb!=NULL) // calcula el indice de bondad de la persona.
			{
				nodo->bondad= nodo->bondad + auxb->vt;
				auxb=auxb->proxb;
       		}
       		auxcont=nodo->pcont;	
			while(auxcont!=NULL) //calcula el indice de expiacion de la persona.
			{
				nodo->expiacion= nodo->expiacion + auxcont->vt;
				auxcont=auxcont->proxcont;
       		}
       		
       		nodo->comport=((nodo->bondad)-(nodo->maldad)+(nodo->expiacion)); //calcula el indice de comportamiento de la persona
		}
		auxf=auxf->proxfe;
	}
}

void Perdon(purg **p, des **q) //Proceso que permite quitar a una persona que haya cumplid su condena de la lista de purgatorio y la envia a la lista de cielo.
{
	purg *auxp, *temporal; des *auxc;
	int anio, i;
	
	printf("Ingrese el anio actual \n");
	scanf("%d",&anio);
	printf("si asigna anio actual \n");
	system("PAUSE");
	
	auxp=*p; auxc=*q; i=0; temporal=NULL;
	while(auxp!=NULL)
	{
		
		if(anio - auxp->anio >= auxp->at )
		{
			//Copia a la persona a la lista de cielo
			des *nuevo;	
			nuevo=(des*)malloc(sizeof(des));
			nuevo->proxd=*q;
			strcpy(	nuevo->nombre,auxp->nombre);	
			nuevo->genero=auxp->genero;
			strcpy(	nuevo->pais,auxp->pais);
			nuevo->codigo=auxp->codigo;
			nuevo->comport=auxp->comport;
		
			*q=nuevo;
		
		}
		else
		{
			//actualiza  la lista de purgatorio
			purg *nuevo2;
			nuevo2=(purg*)malloc(sizeof(purg));
			nuevo2->proxpurg=temporal;
			strcpy(	nuevo2->nombre,auxp->nombre);	
			nuevo2->genero=auxp->genero;
			strcpy(	nuevo2->pais,auxp->pais);
			strcpy(nuevo2->penitencia,auxp->penitencia);
			nuevo2->codigo=auxp->codigo;
			nuevo2->comport=auxp->comport;
			nuevo2->at=auxp->at;
			nuevo2->anio=auxp->anio;
			temporal=nuevo2;
		
		
		}
		auxp=auxp->proxpurg;
	}
	*p=temporal;	
}


void MostrarComportamiento(fec *p) //Proceso que permite consultar el comportamiento de una persona.
{
	fec *auxf; nac *auxn, *nodo ; pec *auxp; bond *auxb; cont *auxcont;
	auxf=p;
	int opcion, comparar, codigo;
	
	printf("Ingrese el codigo de la persona de la cual desea ver su comportamiento: ");
	scanf("%d",&codigo);
		
	while(auxf!=NULL)
	{
	
		auxn=auxf->primernac;
		comparar=Buscar(auxn, codigo);
			if(comparar==TRUE)
			{
				nodo=BuscarDevolver(auxn, codigo);
				printf("\nIngrese 1 si desea mostrar los pecados de la persona .\n");
				printf("Ingrese 2 si desea mostrar las buenas acciones de la persona.\n");
				printf("Ingrese 3 si desea mostrar las expiaciones de la persona.\n ");
				scanf("%d",&opcion);
				printf("\n");
				if(opcion==1)
				{
					auxp=nodo->ppecado;
					while(auxp!=NULL)
					{
						printf("%s[%d]->",auxp->pecado,auxp->vt);
						auxp=auxp->proxp;
					
       				}
       				
       				printf("NULL \n");
       				printf("indice maldad = %d\n\n", nodo->maldad);
       				system("PAUSE");
					menu();
				}
				else if(opcion==2)
				{
					auxb=nodo->pbondad;
					while(auxb!=NULL)
					{
						printf("%s[%d]->",auxb->bondad,auxb->vt);
						auxb=auxb->proxb;					
					}
					printf("NULL \n");
					printf("indice bondad= %d\n\n", nodo->bondad);
					system("PAUSE");
					menu();
				}
				else if(opcion==3)
				{
					auxcont=nodo->pcont;
					while(auxcont!=NULL)
					{
						printf("%s[%d]->",auxcont->pecado,auxcont->vt);
						auxcont=auxcont->proxcont;
					}
					printf("NULL \n");
					printf("Indice de expiacion= %d\n\n", nodo->expiacion);
					system("PAUSE");
					menu();
			    } 
				else
				{
		  			printf("Opcion invalida, intente nuevamente. \n");
		  			system("PAUSE");
					menu();
				}		
			}	
		auxf=auxf->proxfe;
	} 
	printf("El nombre indicado no existe. Intente nuevamente.");
}

void MostrarDatos(fec *p) // Proceso que permite consultar los datos generales de una persona en el arbol de la vida.
{
	fec *auxf; nac *auxn, *nodo;
	int codigo, comparar;
	
	printf("Ingrese el codigo de la persona a consultar \n");
	scanf("%d",&codigo);
	auxf=p;

	while(auxf!=NULL)
	{
		auxn=auxf->primernac;
		comparar=Buscar(auxn,codigo);
		if(comparar=TRUE)
		{
			nodo=BuscarDevolver(auxn,codigo);
			
			printf("Nombre: %s \n",nodo->nombre);
			printf("Pais: %s \n",nodo->pais);
			printf("Genero: %c \n",nodo->genero);
			printf("Indice de comportamiento: %d \n",nodo->comport);
			printf("Indice de bondad: %d \n",nodo->bondad); 
			printf("Indice de maldad: %d \n",nodo->maldad);
			printf("Indice de expiacion: %d \n",nodo->expiacion);
			return;
		}
		auxf=auxf->proxfe;
	}
}

void mostrarFechas(fec *p) // Proceso que muestra la lista de fechas que contiene los distintos arboles.
{
	fec *auxf;
	
	printf("Lista de Fechas: \n");
	auxf=p;
		if(auxf==NULL)
     		{
     			printf("No hay fechas para mostrar. \n");
				system("PAUSE");
				menu();     			
			}
       		while(auxf!=NULL)
       		{
       			printf("[%d/%d/%d]->",auxf->dia,auxf->mes,auxf->anio);
				auxf=auxf->proxfe; 
      	 	}		
       		printf("NULL \n \n");     
}
void mostrararbol(fec *p) //Proceso que muestra el arbol contenido en una fecha indicada de forma horizontal.
{
	fec *auxf; nac *auxn, *nodo;
	int d,m,a;
	mostrarFechas(p);
	printf("Ingrese la fecha que desea consultar: \n");
	printf("Dia: ");
	scanf("%d",&d);
	printf("Mes: ");
	scanf("%d",&m);
	printf("Anio: ");
	scanf("%d",&a);
	auxf=p;

	while(auxf!=NULL)
     {
      if((d==auxf->dia)&&(m==auxf->mes)&&(a==auxf->anio))
		{  
	
		printf("InOrden: ");
   		InOrden(auxf->primernac, Mostrar);
   		printf("\n");
  	 	printf("PreOrden: ");
   		PreOrden(auxf->primernac, Mostrar);
   		printf("\n");
		printf("PostOrden: ");
   		PostOrden(auxf->primernac, Mostrar);
   		printf("\n\n");
   		system ("PAUSE");
   		printf ("DIBUJO DEL ARBOL EN FORMA HORIZONTAL: \n\n");
   		dibujar (auxf->primernac, 0);
   		printf("\n");

   		}
    
      auxf=auxf->proxfe;
    
     }
	
}
void muerte(fec *p) //Proces que permite eliminar a una persona del arbol de la vida y la asigna a las listas de cielo, infierno o purgatorio.
{
	fec *auxf; nac *auxn, *ant;
	int comparar,codigo;
	
	printf("Ingrese el codigo de la persona a eliminar del Arbol de la Vida: ");
	scanf("%d",&codigo);
	
	auxf=p;
	while(auxf!=NULL)
	{
			Borrar(&auxf->primernac, codigo);			
			auxf=auxf->proxfe;
	}
}

des *insertarDestino(des *p, nac *auxn) //Ingresa personas ya sea en el cielo o el infierno
{
	
	des *nuevo;	
	nuevo=(des*)malloc(sizeof(des));
	nuevo->proxd=p;
	strcpy(	nuevo->nombre,auxn->nombre);	
	nuevo->genero=auxn->genero;
	strcpy(	nuevo->pais,auxn->pais);
	nuevo->codigo=auxn->codigo;
	nuevo->comport=auxn->comport;
		
	p=nuevo;
	return(p);
}

purg *insertarPurgatorio(purg *p, nac *auxn) // Ingresa personas en el purgatorio
 {
	char penitencia[20];
	//int anio;
	
	purg *nuevo;	
	nuevo=(purg*)malloc(sizeof(purg));
	nuevo->proxpurg=p;
	strcpy(	nuevo->nombre,auxn->nombre);
	nuevo->genero=auxn->genero;
	strcpy(	nuevo->pais,auxn->pais);
	nuevo->codigo=auxn->codigo;
	nuevo->comport=auxn->comport;
	
	if((nuevo->comport >= 200)&&(nuevo->comport <=250)) //200-250: 10 años terrenales
	{
		nuevo->at=10;
	}
	if((nuevo->comport >= 251)&&(nuevo->comport <=300)) // 251-300: 15 años terrenales
	{
		nuevo->at=15;
	}
	if((nuevo->comport >= 301)&&(nuevo->comport <=500)) // 301-500: 30 años terrenales
	{
		nuevo->at=30;
	}
	printf("Ingrese anio de muerte: ");
	scanf("%d",&nuevo->anio);
  	printf("Ingrese la penitencia a cumplir: ");
	scanf("%s", &penitencia);fflush(stdin);
	strcpy(nuevo->penitencia, penitencia);
	p=nuevo;
	return(p);	
	
}

void mostrarDestino(des *p) // Proceso que permite mostrar las listas de cielo o infierno.
{
	des *auxd;
	auxd=p;

     		if(auxd==NULL)
     		{
     			printf("No hay personas para mostrar. \n");
				system("PAUSE");
				menu();     			
			}
       		while(auxd!=NULL)
       		{
       			printf("%d[%s]->",auxd->codigo,auxd->nombre);
				auxd=auxd->proxd;
      	 	}		
       		printf("NULL \n");               	
}

void mostrarPurgatorio(purg *p) // Proceso que muestra la lista de Purgatorio.
{
	purg *aux;
	aux=p;

    if(aux==NULL)
    {
    	printf("No hay personas para mostrar. \n");
		system("PAUSE");
		menu();     			
	}
    while(aux!=NULL)
    {
    	printf("%d[%s][condena: %d]->",aux->codigo,aux->nombre,aux->at);
		aux=aux->proxpurg;
    }		
    printf("NULL \n");               	
}


void InsertarDemonio(nac **d, des **auxd) //Proceso que permite extraer a una persona de la lista de infierno y asignarla al arbol de demonios.
{
   int clave,x, clave2=777;
   nac *auxa;
   des *aux, *temporal;
   auxa=*d;
   aux=*auxd;
   temporal=NULL;
   printf("Ingrese clave: \n");
   scanf("%d", &clave);
   if(clave == clave2)
   {
    printf("Ingrese el valor de referencia para convertirse en demonio");
    scanf("%d",&x);
    while (aux!=NULL)
    {
   	 if (aux->comport < x) //x es el valor designado por San pedro para los demonios   	 
   		Insertar(&auxa, aux->codigo , aux->nombre , aux->pais, aux->genero);
     else
     {
         des *nuevo;	
	     nuevo=(des*)malloc(sizeof(des));
	     nuevo->proxd=temporal;
	     strcpy(nuevo->nombre,aux->nombre);	
	     nuevo->genero=aux->genero;
	     strcpy(nuevo->pais,aux->pais);
	     nuevo->codigo=aux->codigo;
	     nuevo->comport=aux->comport;
	     temporal=nuevo;
     }
     aux=aux->proxd;
   	}    
    *auxd=temporal;
    *d=auxa;
   }
   else
     printf("Clave incorrecta, persona no autorizada. \n");
   dibujar(auxa,0);
   
}

void InsertarAngel(nac **a, des **auxd) // Proceso que permite extraer a una persona de la lista de cielo y asignarla al arbol de angeles.
{
   int x;
   nac *auxa;
   des *aux, *temporal;
   auxa=*a;
   aux=*auxd;
   temporal=NULL;
   
    printf("Ingrese el valor de referencia para convertirse en angel");
    scanf("%d",&x);
    while (aux!=NULL)
    {
   	 if (aux->comport > x) //x es el valor designado por San pedro para los demonios   	 
   		Insertar(&auxa, aux->comport , aux->nombre , aux->pais, aux->genero);
     else //actualizar lista de cielo primerciel.
     {
         des *nuevo;	
	     nuevo=(des*)malloc(sizeof(des));
	     nuevo->proxd=temporal;
	     strcpy(nuevo->nombre,aux->nombre);	
	     nuevo->genero=aux->genero;
	     strcpy(nuevo->pais,aux->pais);
	     nuevo->codigo=aux->codigo;
	     nuevo->comport=aux->comport;
	     temporal=nuevo;
	     
     }
     aux=aux->proxd;
   	}
	    
     *auxd=temporal;
     *a=auxa;
   dibujar(auxa,0);
}
//MENUS

void menu()
{
	int opcion, opcion2;	
	system("cls");
	system("color F9");
	printf("   _ ,                                                           \n"); 
	printf("  / |  ._  |_    _   |     _|   _     |   _.    |  /  o   _|   _.\n"); 
	printf(" /--|  |   |_)  (_)  |    (_|  (/_    |  (_|    |/    |  (_|  (_|\n");
	printf("\n");
	printf("\n");
	printf("+-++-++-++-++-++-++-++-++-++-++          |    +-++-++-++-++-++-++-++-++-++-++\n");
	printf("|Administracion de Nacimientos|          |    |  Administracion de Personas |\n");
	printf("+-++-++-++-++-++-++-++-++-++-++          |    +-++-++-++-++-++-++-++-++-++-++\n");
	printf("                                         |\n"); 
	printf("1.Mostrar Arboles por Fecha              |   12.Agregar una accion una persona.");
	printf("\n");
	printf("2.Crear Nacimiento.                      |   13.Consultar el comportamiento.");
	printf("\n");
	printf("                                         |   14.Consultar datos generales de un mortal.\n"); 
	printf("                                         |\n");
	printf("+-++-++-++-++-++-++-++-++-++-++          |    +-++-++-++-++-++-++-++-++-++-++\n");
	printf("|Administracion de Categorias |          |    |  Administracion de Muertes  |\n");
	printf("+-++-++-++-++-++-++-++-++-++-++          |    +-++-++-++-++-++-++-++-++-++-++\n");
	printf("                                         |\n");
	printf("3.Crear Categoria.                       |   15.Quitar una Persona del Arbol.");
	printf("\n"); 
	printf("4.Crear una accion en categorias         |   16.Consultar lista de Cielo.");
	printf("\n");
	printf("5.Mostrar Categorias.                    |   17.Consultar lista de infierno.");
	printf("\n");
	printf("6.Mostrar Acciones Categoricas.          |   18.Consultar lista de Purgatorio.");
	printf("\n");
	printf("7.Mostrar Acciones Generales.            |   19.Crear arboles de Angeles o Demonios."); 
	printf("\n");
	printf("8.Cambiar el Valor de una categoria.     |   20.Mostrar arboles de Angeles o Demonios."); 
	printf("\n");
	printf("9.Cambiar el Valor de una accion.        |   21.Perdonar personas condenadas.");
	printf("\n");
	printf("10.Eliminar una categoria sin acciones.  |        +-++-++-++-++-++-++-++");
	printf("\n");
	printf("11.Eliminar una accion de las categorias.|        | Marque su opcion: ");                                                                                                                                                                  	
	scanf("%d",&opcion);
	system("cls");
  switch(opcion)
  {
   case 1:
          mostrararbol(primerf);
   		  system("PAUSE");
		  system("cls");
   	      menu();
   		  break; 
   case 2:
   	      primerf=comprobarFecha(primerf);
   	      printf("\n\n");
   	      system("PAUSE");
		  system("cls");
   	      menu();
          break;
   case 3:
   	      printf("Coloque 1 para categoria de malas acciones.  \n");
   	      printf("Coloque 2 para categoria de buenas acciones.  \n");
   	      printf("Coloque -1 para volver al menu.\n");
   	      printf("Opcion: ");
   	      scanf("%d",&opcion2);
   	      printf("\n");
   	      if(opcion2==1)
   	      {
   	      	   	      primerctgp=crearCategoria(primerctgp);
   	      	   	      printf("\n");
   	                  mostrarCategoria(primerctgp);
		  }
		  else if(opcion2==2)
		  {
		  	   	      primerctgb=crearCategoria(primerctgb);
		  	   	      printf("\n");
   	                  mostrarCategoria(primerctgb);
		  }
		  else if(opcion2==-1)
		  {
		  	menu();
		  }
		  else
		  printf("Opcion invalida, intente nuevamente. \n");
		  system("PAUSE");
		  system("cls");
		  menu();
          break;
   case 4:
   	        printf("Coloque 1 para crear Pecados.  \n");
   	        printf("Coloque 2 para crear Bondades.  \n");
   	        printf("Coloque -1 para volver al menu.\n");
   	        printf("Opcion: ");
   	        scanf("%d",&opcion2);
   	      if(opcion2==1)
   	      {
   	      		printf("Lista de Categorias Malas: \n");
   	      		mostrarCategoria(primerctgp);
   	      		printf("\n");
   	        	primerctgp=crearAccion(primerctgp);
   	        	printf("Pecado creado exitosamente, por favor consulte la lista de pecados en acciones categoricas en el menu \n\n"); 
				            
		  }
	      else if(opcion2==2)
	      {		
	      		printf("Lista de Categorias Buenas: \n");
   	      		mostrarCategoria(primerctgb);
   	      		printf("\n");
	      	    primerctgb=crearAccion(primerctgb);
	      	    printf("Bondad creada exitosamente, por favor consulte la lista de bondades en acciones categoricas en el menu \n\n");
	      	
		  }	
		   else if(opcion2==-1)
		  {
		  	menu();
		  }
		  else		  
		  printf("Opcion invalida, intente nuevamente. \n");
		  system("PAUSE");
		  system("cls");
		  menu();
          break;
      	 
	case 5:
		
   	      printf("Coloque 1 para Malas acciones.  \n");
   	      printf("Coloque 2 para Buenas acciones.  \n");
   	      printf("Coloque -1 para volver al menu.\n");
   	      printf("Cual lista de categorias desea consultar: ");
   	      scanf("%d",&opcion2);
   	      if(opcion2==1)
   	      {
   	        	mostrarCategoria(primerctgp);
   	            
			 }
	      else if(opcion2==2)
	      {
	      		mostrarCategoria(primerctgb);
	      	
		  }
		  else if(opcion2==-1)
		  {
		  	menu();
		  }
		  else
		  printf("Opcion invalida, intente nuevamente. \n");
		  system("PAUSE");
		  system("cls");
		  menu();
          break;
   case 6:
          printf("Coloque 1 para ingresar una categoria mala.  \n");
   	      printf("Coloque 2 para ingresar una categoria buena.  \n");
   	      printf("Coloque -1 para volver al menu.\n");
   	      printf("Opcion: ");
   	      scanf("%d",&opcion2);
   	      if(opcion2==1)
   	      {
   	      	   	      mostrarAccionpC(primerctgp);
   	                  
			 }
		  else if(opcion2==2)
		  {
		  	   	      mostrarAccionpC(primerctgb);
   	                  
		  }
 		  else if(opcion2==-1)
		  {
		  	menu();
		  }
		  else
		  printf("Opcion invalida, intente nuevamente. \n");
          system("PAUSE");
          system("cls");
          menu();
          break;
   case 7:
          printf("Coloque 1 para mostrar todos los pecados.  \n");
   	      printf("Coloque 2 para mostrar todas las buenas acciones.  \n");
   	      printf("Coloque -1 para volver al menu.\n");
   	      printf("Opcion: ");
   	      scanf("%d",&opcion2);
   	      if(opcion2==1)
          {	
   	      mostrarAcciones(primerctgp);
   	                  
          }
		  else if(opcion2==2)
		  {
          mostrarAcciones(primerctgb);
   	                  
		  }
		  else if(opcion2==-1)
		  {
		  	menu();
		  }
		  else
		  printf("Opcion invalida, intente nuevamente. \n");
		  system("PAUSE");          
          menu();
          break;
    case 8:
          printf("Coloque 1 para modificar el valor de una categoria mala.  \n");
   	      printf("Coloque 2 para modificar el valor de una categoria buena.  \n");
   	      printf("Coloque -1 para volver al menu.\n");
   	      printf("Opcion: ");
   	      scanf("%d",&opcion2);
   	      if(opcion2==1)
          {
   	    	modificarCTG(primerctgp);             
          }
		  else if(opcion2==2)
		  {
          modificarCTG(primerctgb);           
		  }
		  else if(opcion2==-1)
		  {
		  	menu();
		  }
		  else
		  printf("Opcion invalida, intente nuevamente. \n");
		  system("PAUSE");          
          menu();
          break;
    case 9:
          printf("Coloque 1 para modificar el valor de un pecado.  \n");
   	      printf("Coloque 2 para modificar el valor de una buena accion.  \n");
   	      printf("Coloque -1 para volver al menu.\n");
   	      printf("Opcion: ");
   	      scanf("%d",&opcion2);
   	      if(opcion2==1)
          {
   	    	modificarAccion(primerctgp);             
          }
		  else if(opcion2==2)
		  {
          modificarAccion(primerctgb);             
		  }
		  else if(opcion2==-1)
		  {
		  	menu();
		  }
		  else
		  printf("Opcion invalida, intente nuevamente. \n");
		  system("PAUSE");          
          menu();
          break;
    case 10:
    	  printf("Coloque 1 para eliminar una categoria mala.  \n");
   	      printf("Coloque 2 para para eliminar una categoria buena.  \n");
   	      printf("Coloque -1 para volver al menu.\n");
   	      printf("Opcion: ");
   	      scanf("%d",&opcion2);
   	      if(opcion2==1)
          {
   	    	primerctgp=EliminarCategoria(primerctgp);            
          }
		  else if(opcion2==2)
		  {
          primerctgb=EliminarCategoria(primerctgb);            
		  }
		  else if(opcion2==-1)
		  {
		  	menu();
		  }
		  else
		  printf("Opcion invalida, intente nuevamente. \n");
		  system("PAUSE");          
          menu();
          break;
    case 11:
    	  printf("Coloque 1 para eliminar un pecado.  \n");
   	      printf("Coloque 2 para para eliminar una buena accion.  \n");
   	      printf("Coloque -1 para volver al menu.\n");
   	      printf("Opcion: ");
   	      scanf("%d",&opcion2);
   	      if(opcion2==1)
          {
   	    	primerctgp=EliminarAccion(primerctgp);
   	        menu();            
          }
		  else if(opcion2==2)
		  {
          primerctgb=EliminarAccion(primerctgb);
   	      menu();         
		  }
		  else if(opcion2==-1)
		  {
		  	menu();
		  }
		  else
		  printf("Opcion invalida, intente nuevamente. \n");
		  system("PAUSE");          
          menu();
          break;
    case 12:
    	  printf("Coloque 1 para agregar un pecado a una persona.  \n");
   	      printf("Coloque 2 para agregar una buena accion a una persona.  \n");
   	      printf("Coloque 3 para arrepentirse de un pecado. \n");
   	      printf("Coloque -1 para volver al menu.\n");
   	      printf("Opcion: ");
   	      scanf("%d",&opcion2);
   	      if(opcion2==1)
          {
   	    	FaltasCometidas(&primerf, primerctgp);
   	    	system("PAUSE");
   	        menu();           
          }
		  else if(opcion2==2)
		  {
          	BuenasAcciones(&primerf, primerctgb);
          	system("PAUSE");
          	menu();
   	                  
		  }
		  else if(opcion2==3)
	      {		
	      	printf("Lista de pecados: \n");
   	      	mostrarAcciones(primerctgp);
   	      	printf("\n");
	      	Arrepentimientos(&primerf);
	      
	      	
		  }
		  else if(opcion2==-1)
		  {
		  	menu();
		  }
		  else
		  printf("Opcion invalida, intente nuevamente. \n");         
          menu();
          break;
    case 13:
    	  MostrarComportamiento(primerf);
		  system("PAUSE");          
          menu();
          break;      
    case 14:
    	  MostrarDatos(primerf);
		  system("PAUSE");          
          menu();
          break;
  	case 15:
    	  muerte(primerf);
    	  system("PAUSE");          
          menu();
          break;

    case 16:
    	  mostrarDestino(primerciel);
		  system("PAUSE");          
          menu();
          break;

	case 17:
    	  mostrarDestino(primerinf);
		  system("PAUSE");          
          menu();
          break;

	case 18:
    	  mostrarPurgatorio(primerpurg);
		  system("PAUSE");          
          menu();
          break;
    case 19:
          printf("Ingrese 1 si desea crear demonios  \n");
          printf("Ingrese 2 si desea crear Angeles \n");
          printf("Coloque -1 para volver al menu.\n");
          printf("Opcion: ");
          scanf("%d",&opcion2);
          if (opcion2==1)
    	  InsertarDemonio(&primerD,&primerinf);
    	  else if(opcion2==2)
    	  InsertarAngel(&primerA,&primerciel);
    	  else if(opcion2==-1)
		  {
		  	menu();
		  }
    	  else
    	  printf("Opcion invalida, intente nuevamente. \n");
		  system("PAUSE");          
          menu();
          break;
	case 20:
		  printf("Ingrese 1 si desea mostrar el arbol de demonios\n");
		  printf("Ingrese 2 si desea mostrar el arbol de angeles\n");
		  printf("Coloque -1 para volver al menu.\n");
		  printf("Opcion: ");
		  scanf("%d",&opcion2);
		  if(opcion2==1)
    	  dibujar(primerD,0);
    	  else if(opcion2==2)
    	  dibujar(primerA,0);
    	  else if(opcion2==-1)
		  {
		  	menu();
		  }
    	  else
    	  printf("Opcion invalida, intente nuevamente. \n");
    	  
		  system("PAUSE");          
          menu();
          break;
	case 21:
    	  Perdon(&primerpurg, &primerciel);
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
int main() // Mensaje Importante.
{
	system("color F9");
	printf("                           Cosas a tener en cuenta: \n\n");
	printf(" Este programa cumple con los requerimientos detallados en el informe anexo con la entrega, dichos requerimientos\nobtenidos directamente de la asignacion: Proyecto 'Destino Final', documento entregado en formato pdf a cada uno de los grupos que conforman la clase de Algoritmos y Programacion II NCR:15099.\n\n Teniendo en cuenta que se dio libertad de asumir cualquier postura ante algun detalle omitido en dicho documento,\nsiempre y cuando se cumpliera con lo estipulado en el mismo.\n\n ");
	printf("Para el correcto funcionamiento del programa se debe abstener a colocar datos unicamente del tipo que son pedidos, por\nejemplo si piden una fecha no colocar char ni cadena de caracteres. \n\n");
	printf("Abstengase de pedir los datos generales de una persona que no existe o ya fue borrada del arbol de la vida, a menos que se ingrese otra persona con el mismo codigo(aunque no se deberia hacer). \n\n");
	printf("Abstengase de Dibujar el arbol una vez eliminada la unica persona en el mismo, si se desea dibujar agregue otra antes. \n\n");
	printf("Recuerde que las acciones asignadas a las personas son definitivas a excepcion de los pecados, ya que estos se pueden arrepentir. \n\n");
	system("PAUSE");
	menu();
	return(0);
}
