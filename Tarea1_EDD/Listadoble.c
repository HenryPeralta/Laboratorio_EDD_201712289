#include <stdio.h>
#include <conio.h>

typedef struct nodo{
    int dato;
    struct nodo* siguiente;
    struct nodo* atras;
}nodo;

nodo* primero = NULL;
nodo* ultimo = NULL;

void insertarNodo();
void MostrarLista();
void BuscarNodo();
void EliminarNodo();
/*void desplegarListaUp();*/

int main(){
    insertarNodo();
    insertarNodo();
    insertarNodo();
    insertarNodo();
    insertarNodo();
    insertarNodo();
    insertarNodo();
    insertarNodo();
    printf("\n");
    MostrarLista();
    printf("\n");
    BuscarNodo();
    EliminarNodo();
    generar();
    MostrarLista();
    /*desplegarListaUp();*/
    return 0;
}

void insertarNodo(){
    nodo* nuevo = (nodo*)malloc(sizeof(nodo));
    printf("ingresar el dato que contendra el nuevo nodo: ");
    scanf("%d", &nuevo->dato);

    if (primero==NULL)
    {
        primero = nuevo;
        primero->siguiente = NULL;
        primero->atras = NULL;
        ultimo = primero; 
    }else
    {
        ultimo->siguiente = nuevo;
        nuevo->siguiente = NULL;
        nuevo->atras = ultimo;
        ultimo = nuevo;
    }
    printf("\n Nodo Ingresado con Exito \n");    
}

void MostrarLista(){
    nodo* actual = (nodo*)malloc(sizeof(nodo));
    actual = primero;
    if(primero != NULL){
        while (actual != NULL)
        {
            printf("\n %d", actual->dato);
            actual = actual->siguiente;
        }
        
    }else
    {
        printf("\n la lista se encuentra vacia \n");
    }
    
}

/*void desplegarListaUp(){
    nodo* actual = (nodo*)malloc(sizeof(nodo));
    actual = ultimo;
    if(primero != NULL){
        while (actual != NULL)
        {
            printf("\n %d", actual->dato);
            actual = actual->atras;
        }
        
    }else
    {
        printf("\n la lista se encuentra vacia \n");
    }
}*/

void generar(){
    FILE * fp;
    fp=fopen("./cadigo.txt","w");
    if(fp==NULL){
        printf("Error");
        return;
    }
    char cad[1024];
    sprintf(cad,"digraph G{ \n node[shape=\"box\",style=\"filled\",fillcolor=\"#EEEEE\",color=\"#EEEEE\"];\n");
    fputs(cad,fp);
    nodo* aux;
    aux= primero;
    guardarRecursivo(aux,fp,cad);
    sprintf(cad,"}\n");
    fputs(cad,fp);
    fclose(fp);
}

void guardarRecursivo(nodo* aux,FILE* fp,char c[]){
    if(aux==NULL){
        return;
    }else{
        if(aux->siguiente!=NULL){
            
            sprintf(c,"node%p[label=\"%i\"]\n",&(*aux),aux->dato);
            fputs(c,fp);
            guardarRecursivo(aux->siguiente,fp,c);
            sprintf(c,"node%p->node%p;\n node%p->node%p;\n",&(*aux),&(*aux->siguiente),&(*aux->siguiente),&(*aux));
            fputs(c,fp);
        }else{
            sprintf(c,"node%p[label=\"%i\"]\n",&(*aux),aux->dato);
            fputs(c,fp);
        }
    }
}

void BuscarNodo(){
    nodo* actual = (nodo*)malloc(sizeof(nodo));
    actual = primero;
    int nodobuscado = 0, encontrado = 0;
    printf("ingrese el dato del nodo a buscar");
    scanf("%d", &nodobuscado);
    if(primero != NULL){
        while (actual != NULL && encontrado != 1)
        {
            if(actual->dato == nodobuscado){
                printf("\n el nodo con el dato (%d) encontrado\n", nodobuscado);
                encontrado = 1;
            }

            actual = actual->siguiente;
        }
        if (encontrado == 0)
        {
            printf("nodo no encontrado");
        }
        
        
    }else
    {
        printf("\n la lista se encuentra vacia \n");
    }
}

void EliminarNodo(){
    nodo* actual = (nodo*)malloc(sizeof(nodo));
    actual = primero;
    nodo* anterior = (nodo*)malloc(sizeof(nodo));
    anterior = NULL;
    int nodobuscado = 0, encontrado = 0;
    printf("ingrese el dato del nodo a buscar para eliminar");
    scanf("%d", &nodobuscado);
    if(primero != NULL){
        while (actual != NULL && encontrado != 1)
        {
            if(actual->dato == nodobuscado){

                if (actual==primero)
                {
                    primero=primero->siguiente;
                    primero->atras=NULL;                    
                }else if(actual==ultimo)
                {
                    anterior->siguiente=NULL;
                    ultimo=anterior;                    
                }else
                {
                    anterior->siguiente = actual->siguiente;
                    actual->siguiente->atras=anterior;
                }
                printf("\n Nodo eliminado con exito \n");
                                
                encontrado = 1;
            }
            anterior = actual;
            actual = actual->siguiente;
        }
        if (encontrado == 0)
        {
            printf("nodo no encontrado");
        }else{
            free(anterior);
        }
        
        
    }else
    {
        printf("\n la lista se encuentra vacia \n");
    }
}