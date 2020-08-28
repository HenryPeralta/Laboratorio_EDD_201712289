
#include<stdlib.h>
#include<iostream>
using namespace std;

class Nodo{
public:
    int dato;
    Nodo *der;
    Nodo *izq;
    Nodo *padre;
};

void menu();
Nodo *crearNodo(int, Nodo *);
void insertarNodo(Nodo *&, int, Nodo *);
void mostrarArbol(Nodo *,int);
bool busqueda(Nodo *, int);
void preOrden(Nodo *);
void inOrden(Nodo *);
void postOrden(Nodo *);
void eliminar(Nodo *, int);
void eliminarNodo(Nodo *);
Nodo *minimo(Nodo *);
void reemplazar(Nodo *, Nodo *);
void destruirNodo(Nodo *);

Nodo *arbol = NULL;

int main(){
    menu();

    return  0;
}

//funcion de menu
void menu(){
    int dato,opcion, contador=0;

    do{
        cout<<"\t.:MENU:."<<endl;
        cout<<"1. Insertar un nuevo nodo"<<endl;
        cout<<"2. Mostrar el arbol completo"<<endl;
        cout<<"3. Buscar un elemento en el arbol"<<endl;
        cout<<"4. Recorrer el arbol en PreOrden"<<endl;
        cout<<"5. Recorrer el arbol en InOrden"<<endl;
        cout<<"6. Recorrer el arbol en PostOrden"<<endl;
        cout<<"7. Eliminar un node del arbol"<<endl;
        cout<<"8. Salir"<<endl;
        cin>>opcion;

        switch (opcion) {
        case 1: cout<<"\n Digite un numero: ";
            cin>>dato;
            insertarNodo(arbol, dato, NULL);//insertamos un nuevo dato
            cout<<"\n";
            system("pause");
            break;
        case 2: cout<<"\n Mostrando el arbol completo: \n\n ";
            mostrarArbol(arbol, contador);
            cout<<"\n";
            system("pause");
            break;
        case 3: cout<<"\n digite el numero a buscar: ";
            cin>>dato;
            if(busqueda(arbol,dato)==true){
                cout<<"\nElemento "<<dato<<" a sido encontrado en el arbol";
            }else{
                cout<<"\nElemento no encontrado \n";
            }
            cout<<"\n";
            system("pause");
            break;
        case 4: cout<<"\n Recorrido en PreOrden: ";
            preOrden(arbol);
            cout<<"\n\n";
            system("pause");
            break;
        case 5: cout<<"\n Recorrido en InOrden: ";
            inOrden(arbol);
            cout<<"\n\n";
            system("pause");
            break;
        case 6: cout<<"\n Recorrido en PostOrden: ";
            postOrden(arbol);
            cout<<"\n\n";
            system("pause");
            break;
        case 7: cout<<"\n Digite el numero a eliminar: ";
            cin>>dato;
            eliminar(arbol, dato);
            cout<<"\n";
            system("pause");
            break;
            }
        system("cls");
    }
    while(opcion != 8);
}

//funcion para crear un nuevo nodo
Nodo *crearNodo(int n, Nodo *padre){
    Nodo *nuevo_nodo = new Nodo();

    nuevo_nodo->dato = n;
    nuevo_nodo->der= NULL;
    nuevo_nodo->izq= NULL;
    nuevo_nodo->padre= padre;

    return nuevo_nodo;
}

//funcion para insertar elementos en el arbol
void insertarNodo(Nodo *&arbol, int n, Nodo *padre){
    if(arbol == NULL){//si el arbol esta vacio
        Nodo *nuevo_nodo = crearNodo(n, padre);
        arbol = nuevo_nodo;
    }
    else{//si el arbol tiene un nodo o mas
        int valorRaiz = arbol->dato;//obtenemos el valor de la raiz
        if(n < valorRaiz){// si el elemento es menor a la raiz, insertamos en la izq
            insertarNodo(arbol->izq, n, arbol);
        }
        else{//si el elemento es mayor a la raiz, insertamos en la der
            insertarNodo(arbol->der, n, arbol);
        }
    }
}

//funcion para mostrar el arbol completo
void mostrarArbol(Nodo *arbol, int cont){
    if(arbol==NULL){//si el arbol esta vacio
        return;
    }
    else{
        mostrarArbol(arbol->der, cont+1);
        for(int i=0; i<cont; i++){
            cout<<"   ";
        }
        cout<<arbol->dato<<endl;
        mostrarArbol(arbol->izq, cont+1);
    }
}

//funcion para buscar un elemento en el arbol
bool busqueda(Nodo *arbol, int n){
    if(arbol == NULL){
        return false;
    }
    else if(arbol->dato == n){//si el nodo es igual al elemento
        return true;
    }
    else if(n < arbol->dato){
        return busqueda(arbol->izq, n);
    }
    else{
        return busqueda(arbol->der, n);
    }
}

//funcion para recorrido en profundidad - PreOrden
void preOrden(Nodo *arbol){
    if(arbol == NULL){//si el arbol esta vacio
        return;
    }
    else{
        cout<<arbol->dato<<" - ";
        preOrden(arbol->izq);
        preOrden(arbol->der);
    }
}

//funcion para recorrido en profundidad - InOrden
void inOrden(Nodo *arbol){
    if(arbol == NULL){//si el arbol esta vacio
        return;
    }
    else{
        inOrden(arbol->izq);
        cout<<arbol->dato<<" - ";
        inOrden(arbol->der);
    }
}

//funcion para recorrido en profundidad - PostOrden
void postOrden(Nodo *arbol){
    if(arbol == NULL){//si el arbol esta vacio
        return;
    }
    else{
        postOrden(arbol->izq);
        postOrden(arbol->der);
        cout<<arbol->dato<<" - ";
    }
}

//Eliminar un nodo del arbol
void eliminar(Nodo *arbol, int n){
    if(arbol == NULL){//si el arbol esta vacio
        return;//no haces nada
    }
    else if(n < arbol->dato){//si el valor es menor
        eliminar(arbol->izq, n);//busca por la izq
    }
    else if(n > arbol->dato){//si el valor es mayor
        eliminar(arbol->der, n);//buscar por la der
    }
    else{//si ya encontraste el valor
        eliminarNodo(arbol);
    }
}

//funcion para eliminar el nodo encontrado
void eliminarNodo(Nodo *nodoEliminar){
    if(nodoEliminar->izq && nodoEliminar->der){//si el nodo tiene hijo izq y
        Nodo *menor = minimo(nodoEliminar->der);
        nodoEliminar->dato = menor->dato;
        eliminarNodo(menor);
    }else if(nodoEliminar->izq){//si tiene hijo izq
        reemplazar(nodoEliminar, nodoEliminar->izq);
        destruirNodo(nodoEliminar);
    }else if(nodoEliminar->der){
        reemplazar(nodoEliminar, nodoEliminar->der);
        destruirNodo(nodoEliminar);
    }else{//no tiene hijos
        reemplazar(nodoEliminar, NULL);
        destruirNodo(nodoEliminar);
    }
}

//funcion para determinar el nodo mas izq posible
Nodo *minimo(Nodo *arbol){
    if(arbol==NULL){//si el arbol esta vacio
        return NULL;//retornas nulo
    }
    if(arbol->izq){//si tiene hijo izq
        return minimo(arbol->izq);//buscamos la parte mas izq posible
    }
    else{//sino tiene hijo izq
        return arbol;//retornamos el mismo nodo
    }
}

//funcion para remplazar dos nodos
void reemplazar(Nodo *arbol, Nodo *nuevoNodo){
    if(arbol->padre){
        //arbol-> padre hay que asignarle su nuevo hijo
        if(arbol->dato == arbol->padre->izq->dato){
            arbol->padre->izq=nuevoNodo;
        }
        else if(arbol->dato == arbol->padre->der->dato){
            arbol->padre->der = nuevoNodo;
        }
    }
    if(nuevoNodo){
        //procedemos a asignarle su nuevo padre
        nuevoNodo->padre = arbol->padre;
    }
}

//funcion para destruir un nodo
void destruirNodo(Nodo *nodo){
    nodo->izq = NULL;
    nodo->der = NULL;

    delete nodo;
}
