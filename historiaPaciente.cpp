#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include "nuevoCalendario.cpp"

using namespace std;

struct Fecha{
    int dia;
    int mes;
    int hora;
};

struct Historia{
    int cedula;
    string sintomas;
    string diagnostico;
    string recipe;
    string examenes;
    string comentario;
    Fecha fechaNodo;
    struct Historia *siguienteHorizontal;
    struct Historia *siguienteVertical;

};

typedef Historia *ListaHistoria;
typedef Historia *NodoHistoria;

NodoHistoria definirNodoHistoria(int cedula,string sintomas, string diagnostico, string recipe, string examenes, string comentario,int dia, int mes, int hora){
    NodoHistoria Nodo = new (struct Historia); //Se encarga de generar un nodo inicializado con toda la informacion de la historia de un paciente
    Nodo->cedula = cedula;                      //Y devuelve ese nodo
    Nodo->sintomas = sintomas;
    Nodo->diagnostico = diagnostico;
    Nodo->recipe = recipe;
    Nodo->examenes = examenes;
    Nodo->comentario = comentario;
    Nodo->fechaNodo.dia = dia;
    Nodo->fechaNodo.mes = mes;
    Nodo->fechaNodo.hora = hora;
    Nodo->siguienteHorizontal = NULL;
    Nodo->siguienteVertical = NULL;
    
    return Nodo;
}

bool cedulaExistente(ListaHistoria Lista, int cedula){ //Recibe la lista de historias y una cedula
    NodoHistoria NodoHorizontal = Lista;                //Y se encarga de buscar en la lista si existe algun nodo con la cedula recibida
                                                        //y dependiendo devuelve verdadero o falso
    while(NodoHorizontal!=NULL){
        if(NodoHorizontal->cedula == cedula)return true;
        else
        {
            NodoHorizontal= NodoHorizontal->siguienteHorizontal;
        }        
    }
    return false;
}

void insertarNuevoPacienteHistoria(ListaHistoria &Lista, NodoHistoria Nodo){
    NodoHistoria NodoHorizontal = Lista;                        //Recibe la lista de historias y un nodo inicializado
    while(NodoHorizontal->siguienteHorizontal!=NULL){           //Esta funcion se encarga de insertar la primera historia de un paciente
        NodoHorizontal = NodoHorizontal->siguienteHorizontal;   //por ser la primera historia nos movemos de manera horizontal en la lista
    }
    NodoHorizontal->siguienteHorizontal = Nodo;    
}

void insertarPacienteHistoria(ListaHistoria &Lista, NodoHistoria Nodo){
    NodoHistoria NodoHorizontal = Lista;                            //Al igual que la funcion insertarNuevoPacienteHistoria se encarga de agregar un nuevo nodo
    NodoHistoria NodoVertical;                                      //a la lista de historias con la diferencia de que como ya el paciente contiene una historia
    while(NodoHorizontal!=NULL){                                    //por lo menos, hay que primero encontrar el nodo y luego moverse verticalmente
        if(NodoHorizontal->cedula==Nodo->cedula){
            NodoVertical = NodoHorizontal;
            while(NodoVertical->siguienteVertical!=NULL){
                NodoVertical = NodoVertical->siguienteVertical;
            }
            NodoVertical->siguienteVertical = Nodo;
        }
        NodoHorizontal = NodoHorizontal->siguienteHorizontal;
    }
}

int insertarHistoria(ListaHistoria &Lista, NodoHistoria Nodo){
                                                    //Esta funcion se encarga de gestionar todo lo relacionado a insertar un nuevo nodo a la lista de historias
    if(Lista == NULL){
        Lista = Nodo;        
        return 1;
    }

    if(cedulaExistente(Lista, Nodo->cedula)){
        
        insertarPacienteHistoria(Lista,Nodo);
    }else
    {
        
        insertarNuevoPacienteHistoria(Lista,Nodo);
    }
   
    return 1;    
}

void mostrarListaHistoria(ListaHistoria Lista){
    NodoHistoria NodoHorizontal = Lista;    
    NodoHistoria NodoVertical;
    while(NodoHorizontal!=NULL){
        NodoVertical = NodoHorizontal;
        while(NodoVertical!=NULL){             
            cout << NodoVertical->cedula << " ";
            NodoVertical = NodoVertical->siguienteVertical;
        }
        cout <<'\n';
        NodoHorizontal = NodoHorizontal->siguienteHorizontal;
    }
}

void guardarArchivoHistoriaPaciente(ListaHistoria Lista){
    NodoHistoria NodoHorizontal = Lista;    //Esta funcion se encarga de guardar toda la informacion que se encuentra en la lista de historias de los pacientes
    NodoHistoria NodoVertical;              //en un archivo .txt
    ofstream escritor("historias.txt");     //Al ser una multilista, primero nos ubicamos en el nodo horizontal y apartir de ahi nos movemos verticalmente
    while(NodoHorizontal!=NULL){            //hasta conseguir vacio y luego pasamos al siguiente nodo horizontal
        NodoVertical = NodoHorizontal;
        while(NodoVertical!=NULL){
            escritor << NodoVertical->cedula <<'\n';
            escritor << NodoVertical->sintomas <<'\n';
            escritor << NodoVertical->diagnostico <<'\n';
            escritor << NodoVertical->recipe <<'\n';
            escritor << NodoVertical->examenes <<'\n';
            escritor << NodoVertical->comentario <<'\n';
            escritor << NodoVertical->fechaNodo.dia <<'\n';
            escritor << NodoVertical->fechaNodo.mes <<'\n';
            escritor << NodoVertical->fechaNodo.hora <<'\n';
            escritor <<'\n';
            NodoVertical = NodoVertical->siguienteVertical;
        }
        NodoHorizontal = NodoHorizontal->siguienteHorizontal;
    }
    escritor.close();
}


void leerArchivoHistoriaPaciente(ListaHistoria &Lista){
    NodoHistoria NodoTemporal = NULL;   //Esta funcion se encarga de leer de un archivo .txt toda la informacion relacionada a historias
    string linea ="";
    string cedulaLetra;    
    string sintomas ="";
    string diagnostico ="";
    string recipes ="";
    string examenes ="";
    string comentario ="";
    string diaLetra ="";
    string mesLetra ="";
    string horaLetra ="";
    int cedula;
    int dia;
    int mes;
    int hora;
    ifstream lectorHistorias("historias.txt");
    while(getline(lectorHistorias,cedulaLetra)&&getline(lectorHistorias,sintomas)&&getline(lectorHistorias,diagnostico)&&getline(lectorHistorias,recipes)&&
    getline(lectorHistorias,examenes)&&getline(lectorHistorias,comentario)&&getline(lectorHistorias,diaLetra)&&getline(lectorHistorias,mesLetra)&&getline(lectorHistorias,horaLetra)){        
        cedula = stoi(cedulaLetra);
        dia = stoi(diaLetra);
        mes = stoi(mesLetra);        
        hora = stoi(horaLetra);        
        NodoTemporal = definirNodoHistoria(cedula,sintomas,diagnostico,recipes,examenes,comentario,dia,mes,hora);        
        
        insertarHistoria(Lista,NodoTemporal);
        
        getline(lectorHistorias, linea);//Salta linea blanca
    }
    lectorHistorias.close();
   
}

void pedirDatosHistoria(ListaHistoria &Lista, int cedula,int dia,int mes,int hora){
    NodoHistoria NodoTemporal = new (struct Historia); //Esta funcion recibe la lista de historias junto a la cedula, dia, mes y hora
                                                        //de la cita de un paciente, y apartir de esta informacion
    string sintomas ="";                            //le pide la informacion restante al usuario para luego mandarsela a una funcion que
    string diagnostico="";                          //inicializara el nodo que luego sera insertado en la lista de historias por la funcion 
    string recipes="";                              //insertarHistoria
    string examenes="";
    string comentario="";

    cin.get();
    cout << "Introduzca los sintomas que presenta el paciente"<<'\n';
    getline(cin,sintomas);
    
    cout << "Introduzca el diagnostico del paciente"<<'\n';
    getline(cin,diagnostico);
    
    cout << "Introduzca el recipe recetado para el paciente"<<'\n';
    getline(cin,recipes);
    
    cout << "Introduzca el/los examen/es que el paciente tiene que realizar"<<'\n';
    getline(cin,examenes);
    
    cout << "Introduzca un comentario"<<'\n';
    getline(cin,comentario);

    NodoTemporal = definirNodoHistoria(cedula,sintomas,diagnostico,recipes,examenes,comentario,dia,mes,hora);
    insertarHistoria(Lista,NodoTemporal);

    cout << "La historia sea registrado exitosamente!"<<'\n';
    cout << "Presione una tecla para continuar"<<'\n';
    getch();
}

void menuModificarHistoriaPaciente(){

    cout << "\n*******************************************" << endl;
    cout << " *        ESPECIFIQUE DATO A MODIFICAR.     *" << endl;
    cout << "********************************************" << endl<<endl;          		
    cout<<"1.Sintomas:"<<endl;
    cout<<"2.Diagnostico:"<<endl;
    cout<<"3.Recipe:"<<endl;
    cout<<"4.Examenes:"<<endl;
    cout<<"5.Comentario"<<endl;
    cout<<"6.Salir:"<<endl;
    
    cout<<"\n Ingrese opcion : ";
}

void mostrarHistoriaPaciente(NodoHistoria Nodo){  //Esta fucnion se encarga simplemente de mostrar toda la informacion contenida en un nodo de Lista Historia
    system("cls");
    NodoHistoria NodoHistoria = Nodo;    
    cout << "\n******************************************" << endl;
    cout << "*        HISTORIA DEL PACIENTE.               *" << endl;
    cout << "*******************************************" << endl<<endl;
    cout<<"Sintomas  : "<<NodoHistoria->sintomas<<'\n';
    cout<<"Diagostico: "<<NodoHistoria->diagnostico<<'\n';
    cout<<"Recipe: "<<NodoHistoria->recipe<<'\n';
    cout<<"Examenes: "<<NodoHistoria->examenes<<'\n';
    cout<<"Comentario : "<<NodoHistoria->comentario<<'\n';
    cout<<"Fecha de consulta: ";
    imprimirFecha(NodoHistoria->fechaNodo.dia,NodoHistoria->fechaNodo.mes);
}

void mostrarHistoriaPacienteCompleta(NodoHistoria Nodo){ //Esta funcion recibe un nodo horizontal, es decir, el primer nodo de los nodos verticales
    while(Nodo!=NULL){                                     //e imprime toda la informacion de cada nodo que haya en ese pilar vertical
        cout<<"Fecha de consulta: ";
        imprimirFecha(Nodo->fechaNodo.dia,Nodo->fechaNodo.mes);
        cout <<'\n';                                   
        cout<<"Sintomas  :  "<<Nodo->sintomas<<'\n';
        cout<<"Diagostico:  "<<Nodo->diagnostico<<'\n';
        cout<<"Recipe:      "<<Nodo->recipe<<'\n';
        cout<<"Examenes:    "<<Nodo->examenes<<'\n';
        cout<<"Comentario : "<<Nodo->comentario<<'\n';              
        Nodo = Nodo->siguienteVertical;
        cout<<'\n';
    }
}

int gestionMostrarHistoriaPaciente(ListaHistoria Lista){
    system("cls");                               //Esta funcion se encarga de gestionar todo lo relacionado cuando se quiere mostrar la historia de un paciente
    int cedula;
    NodoHistoria NodoHorizontal = Lista;
    NodoHistoria NodoVertical;
    cout <<"Ingrese la cedula del paciente del que quiere ver todo su historial"<<'\n';
    cin >>cedula;
    if(cedulaExistente(Lista,cedula)){
        while(NodoHorizontal!=NULL){
            if(NodoHorizontal->cedula == cedula){
                mostrarHistoriaPacienteCompleta(NodoHorizontal);
                cout << '\n';
                cout <<"Presione una tecla para continuar"<<'\n';
                getch();
                return 1;
            }
            NodoHorizontal = NodoHorizontal->siguienteHorizontal;       
        }
    }else
    {
        cout << "No hay ninguna historia registrada con la cedula de este paciente"<<'\n';
        cout << "Presione una tecla para continuar"<<'\n';
        getch();
    }
        
    return 1;
}

void modificarNodoHistoria(NodoHistoria &Nodo){ //Esta funcion se encarga de modificar los datos de un nodo especifico de la lista de historias recibido por parametro
    int opcionMenu;

    mostrarHistoriaPaciente(Nodo);
    menuModificarHistoriaPaciente();
    
    
    while(cin>>opcionMenu && opcionMenu!=6){
        
        switch(opcionMenu){
            case 1:
                cin.get();
                cout << "Ingrese los nuevos sintomas" <<'\n';
                getline(cin,Nodo->sintomas);
                cout << "Los datos se han modificado exitosamente"<<'\n';
                cout << "Presione una tecla para continuar"<<'\n';
                getch();
                break;
            case 2:
                cin.get();
                cout <<"Ingrese el nuevo diagnostico" <<'\n';
                getline(cin,Nodo->diagnostico);
                cout << "Los datos se han modificado exitosamente"<<'\n';
                cout << "Presione una tecla para continuar"<<'\n';
                getch();
            case 3:
                cin.get();
                cout <<"Ingrese el nuevo recipe"<<'\n';
                getline(cin,Nodo->recipe);
                cout << "Los datos se han modificado exitosamente"<<'\n';
                cout << "Presione una tecla para continuar"<<'\n';
                getch();
            case 4:
                cin.get();
                cout <<"Ingrese los nuevos examenes"<<'\n';
                getline(cin,Nodo->examenes);
                cout << "Los datos se han modificado exitosamente"<<'\n';
                cout << "Presione una tecla para continuar"<<'\n';
                getch();
            case 5:
                cin.get();
                cout <<"Ingrese el nuevo comentario"<<'\n';
                getline(cin,Nodo->comentario);
                cout << "Los datos se han modificado exitosamente"<<'\n';
                cout << "Presione una tecla para continuar"<<'\n';
                getch();
            default:
                if(opcionMenu!=1||opcionMenu!=2||opcionMenu!=3||opcionMenu!=4||opcionMenu!=5||opcionMenu!=6){
                    cout << "Ingrese una opcion valida"<<'\n';                    
                    cout << "Presione una tecla para continuar"<<'\n';
                    getch();
                }            
        }
        mostrarHistoriaPaciente(Nodo);
        menuModificarHistoriaPaciente();
        
    }

}

bool existenciaNodoHistoria(ListaHistoria ListaHistoria, int cedula){
    NodoHistoria NodoHorizontal = ListaHistoria;
    while(NodoHorizontal!=NULL){
        if(NodoHorizontal->cedula == cedula){
            return true;
        }
        NodoHorizontal = NodoHorizontal->siguienteHorizontal;
    }
    return false;
}

NodoHistoria encontrarNodoHistoria(ListaHistoria ListaHistoria, int cedula){
    NodoHistoria NodoHorizontal = ListaHistoria;
    while(NodoHorizontal!=NULL){
        if(NodoHorizontal->cedula == cedula){
            return NodoHorizontal;
        }
        NodoHorizontal = NodoHorizontal->siguienteHorizontal;
    }
    return NULL;
}

void modificarCedulaHistoria(ListaHistoria &ListaHistoria,int cedulaVieja, int cedulaNueva){
    NodoHistoria NodoHistoriaTemporal;
    if(existenciaNodoHistoria(ListaHistoria,cedulaVieja)){
        
        NodoHistoriaTemporal = encontrarNodoHistoria(ListaHistoria,cedulaVieja);        
        while(NodoHistoriaTemporal!=NULL){
            NodoHistoriaTemporal->cedula = cedulaNueva;
            NodoHistoriaTemporal = NodoHistoriaTemporal->siguienteVertical;            
        }        
    }
}

int buscarModificarHistoria(ListaHistoria &Lista, int cedula){ //Esta funcion se encarga de buscar en la lista de historias el ultimo nodo vertical relacionado con una cedula para luego ser modificado
    NodoHistoria NodoHorizontal = Lista;
    NodoHistoria NodoVertical;
    while(NodoHorizontal!=NULL){
        if(NodoHorizontal->cedula == cedula){
            NodoVertical = NodoHorizontal;
            while(NodoVertical->siguienteVertical !=NULL){
                NodoVertical = NodoVertical->siguienteVertical;                
            }
            modificarNodoHistoria(NodoVertical);
            return 1;
        }else{        
            NodoHorizontal = NodoHorizontal->siguienteHorizontal;
        }        
    }
}

void gestionModificacionHistoria(ListaHistoria &Lista){//Esta funcion se encarga de gestionar todas las funciones relacionadas a modificar la ultima historia de un paciente
    int cedula;
	NodoHistoria NodoHorizontal = Lista;
    NodoHistoria NodoVertical;
    cout <<"Ingrese la cedula del paciente al que quiere modificar datos de su historia mas reciente"<<'\n';
    cin >> cedula;
    if(cedulaExistente(Lista,cedula)){
       buscarModificarHistoria(Lista,cedula);

    }else
    {
        cout << "No hay ningun paciente registrado con esa cedula"<<'\n';
        cout << "Presione una tecla para continuar"<<'\n';
        getch();        
    }
    
    
}


