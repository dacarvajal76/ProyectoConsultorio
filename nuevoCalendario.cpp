#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <conio.h>
#include "RegistroPaciente.cpp"

using namespace std;

typedef struct{         //Esta estructura nos permite relacionar una cedula y una hora con un dia
    int hora;
    int long cedula = 0;
}THora;

struct Calendario{  //estructura principal de la multilista del calendario
    int dia;
    int mes;
    THora HoraNodo;    
    struct Calendario *siguienteHorizontal;
    struct Calendario *siguienteVertical;
};

typedef Calendario *ListaCalendario;
typedef Calendario *NodoCalendario;

NodoCalendario definirNodo(int dia, int mes, int hora, int cedula){ //recibe por parametro la informacion necesaria para inicializar el nodo
    NodoCalendario NodoTemporal = new (struct Calendario);          // y luego este nodo ser retornado
    NodoTemporal ->dia = dia;
    NodoTemporal ->mes = mes;
    NodoTemporal ->HoraNodo.hora= hora;
    NodoTemporal ->HoraNodo.cedula = cedula;

    NodoTemporal ->siguienteHorizontal = NULL;
    NodoTemporal ->siguienteVertical = NULL;  
    return NodoTemporal;
}

void insertarAlFinalHorizontal(ListaCalendario &Lista, NodoCalendario Nodo){ //Se encarga de insertar un nodo recibido por parametro al final
    ListaCalendario ListaTemporal = new(struct Calendario); //de una lista recibida por referencia de manera horizontal
    if(Lista == NULL) Lista = Nodo;
    else{
        ListaTemporal = Lista;
        while (ListaTemporal->siguienteHorizontal != NULL){
            ListaTemporal = ListaTemporal -> siguienteHorizontal;
        }
        ListaTemporal -> siguienteHorizontal = Nodo;
    }    
}

void insertarAlFinalVertical(ListaCalendario &Lista, NodoCalendario Nodo){ //Se encarga de insertar un nodo recibido por parametro al final
    ListaCalendario ListaTemporal = new (struct Calendario);    //de un nodo horizontal pero por la parte vertical
    if(Lista->siguienteVertical == NULL)Lista->siguienteVertical = Nodo;
    else{
        ListaTemporal = Lista;
        while(ListaTemporal->siguienteVertical !=NULL){
            ListaTemporal = ListaTemporal->siguienteVertical;            
        }
        ListaTemporal->siguienteVertical = Nodo;
    }
}
 
void inicializarCalendario(ListaCalendario &Lista){ //Se encarga de inicializar con las fechas predeterminadas a los nodos de lista de calendario
    int cont;
    int contDias =1;
    int mes;
    int hora = 8;    
    NodoCalendario NodoTemporalHorizontal;
    NodoCalendario NodoTemporalVertical;

   for(int i=7;i!=38;i++){
       

       if(contDias==5){
           i = i + 2;
           contDias = 0;
       }
       cont = i;
       mes = 7;     

       if(i>=32){
           cont = i-31;
           mes = 8;
       }

        NodoTemporalHorizontal = definirNodo(cont,mes,hora,0);
        insertarAlFinalHorizontal(Lista,NodoTemporalHorizontal);  

        
        for(int j=1;j<5;j++){           
            NodoTemporalVertical = definirNodo(cont,mes,hora+j,0);
            insertarAlFinalVertical(NodoTemporalHorizontal,NodoTemporalVertical);
        }
        contDias++;
   }
}

void mostrarCalendario(ListaCalendario Lista){
    NodoCalendario NodoHorizontal = Lista;
    NodoCalendario NodoVertical = Lista;
    while(NodoHorizontal!=NULL){
       
        cout << NodoHorizontal ->dia <<", ";
        cout << NodoHorizontal ->mes <<", ";
        cout << NodoHorizontal ->HoraNodo.hora <<":00| ";
        NodoVertical = NodoHorizontal->siguienteVertical;        
        while(NodoVertical != NULL){
                      
            cout << NodoVertical ->dia <<"; ";
            cout << NodoVertical ->mes <<"; ";
            cout << NodoVertical ->HoraNodo.hora<<":00| ";;
            NodoVertical = NodoVertical->siguienteVertical;
        }
        cout << '\n';
        NodoHorizontal = NodoHorizontal->siguienteHorizontal;        
    }
}

void guardarArchivoCalendario(ListaCalendario Lista){ //Se encarga de guardar la informacion relacionada a los nodos de la lista de calendario
    NodoCalendario NodoHorizontal = Lista;  //en un archivo .txt
    NodoCalendario NodoVertical;
    std::ofstream escritor;
    escritor.open("calendario.txt");
    while(NodoHorizontal!=NULL){
        escritor << NodoHorizontal->HoraNodo.cedula<<";";
        NodoVertical = NodoHorizontal->siguienteVertical;
        while(NodoVertical != NULL){
            escritor << NodoVertical->HoraNodo.cedula<<";";
            NodoVertical = NodoVertical->siguienteVertical;
        }
        escritor<<'\n';
        NodoHorizontal = NodoHorizontal->siguienteHorizontal;
    }
    escritor.close();
}

void leerArchivoCalendario(ListaCalendario &Lista){ //Se encarga de leer la informacion guardada en un archivo txt para igualarsele a la lista inicializada de calendario
    NodoCalendario NodoTemporalHorizontal = Lista;
    NodoCalendario NodoTemporalVertical;
    string tempCedulaLetra = "";
    ifstream lectorCalendario("calendario.txt");    
    
    for(string linea;getline(lectorCalendario,linea);){
        
        istringstream iss(linea);
        getline(iss,tempCedulaLetra,';');
        NodoTemporalHorizontal->HoraNodo.cedula = stoi(tempCedulaLetra);

        NodoTemporalVertical = NodoTemporalHorizontal->siguienteVertical;

        getline(iss,tempCedulaLetra,';');
        NodoTemporalVertical->HoraNodo.cedula = stoi(tempCedulaLetra);
       
        getline(iss,tempCedulaLetra,';');
        NodoTemporalVertical->siguienteVertical->HoraNodo.cedula = stoi(tempCedulaLetra);
         
        getline(iss,tempCedulaLetra,';');
        NodoTemporalVertical->siguienteVertical->siguienteVertical->HoraNodo.cedula = stoi(tempCedulaLetra);
        
        getline(iss,tempCedulaLetra,';');
        NodoTemporalVertical->siguienteVertical->siguienteVertical->siguienteVertical->HoraNodo.cedula = stoi(tempCedulaLetra);
        
        NodoTemporalHorizontal = NodoTemporalHorizontal->siguienteHorizontal;
    }
    lectorCalendario.close();
    
}

int agendarCita(ListaCalendario &Lista, int cedula){ //Se encarga de buscar la fecha disponible mas proxima y ofrecerla como fecha para cita para el usuario
    int opcion;
    NodoCalendario NodoHorizontal = Lista;
    NodoCalendario NodoVertical;
    while(NodoHorizontal!=NULL){
        NodoVertical = NodoHorizontal;
        while(NodoVertical!=NULL){
            if(NodoVertical->HoraNodo.cedula==0){
                cout << NodoVertical->dia <<"/"<<NodoVertical->mes<<"/"<<"2000"<<'\n';
                cout << NodoVertical->HoraNodo.hora<<":00"<<'\n';
                cout << "Si esta fecha le satisface presione 1, sino presione 2"<<'\n';                
                cin >> opcion;
                if(opcion == 1){
                    NodoVertical->HoraNodo.cedula = cedula;
                    cout << "Se ha reservado la cita exitosamente"<<'\n';
                    cout << "Presione una tecla para continuar"<<'\n';
                    getch();
                    return 1;
                }
                
            }
            
            NodoVertical= NodoVertical->siguienteVertical;
        }
        NodoHorizontal= NodoHorizontal->siguienteHorizontal;
    }
    cout << "Se han agotado las fechas"<<'\n';
    cout << "Presione una tecla para continuar"<<'\n';
    getch();
    return 1;
}

bool existenciaCita(ListaCalendario Lista,int cedula){   //Dada una cedula, se busca en la lista de calendario si hay una cita reservada con esta
    NodoCalendario NodoHorizontal = Lista;
    NodoCalendario NodoVertical;
    while(NodoHorizontal!=NULL){
        NodoVertical=NodoHorizontal;
        while(NodoVertical!=NULL){
            if(NodoVertical->HoraNodo.cedula==cedula){
                return true;
            }
            NodoVertical = NodoVertical->siguienteVertical;
        }
        NodoHorizontal = NodoHorizontal->siguienteHorizontal;
    }
    return false;
}

int gestionamientoCitas(ListaCalendario &ListaCalendario, ListaPaciente ListaPaciente){ //Se encarga de todo el gestionamiento relacionado al querer agendar una cita
    int cedula;
    cout << "Introduzca la cedula del paciente que quiere reservar una cita"<<'\n';
    cin >> cedula;
    if(existenciaCita(ListaCalendario,cedula)){
        cout << "Ya hay un paciente con esta cedula, si quiere modificar su cita seleccion la opcion MODIFICAR CITA"<<'\n';
        cout << "Presione una tecla para continuar"<<'\n';
        getch();
        return 1;
    }
    if(buscarPacienteCedula(ListaPaciente,cedula)==NULL){
        cout << "La cedula que ingreso no pertence a ningun paciente que este registrado"<<'\n';
        cout << "Presione una tecla para continuar"<<'\n';
        getch();
        return 1;
    }
    agendarCita(ListaCalendario,cedula);
    return 1;
}

void gestionamientoCalendario(ListaCalendario &Lista){ //Funcion que se utiliza para inicializar la lista de calendario y luego igualarsele la informacion de un archivo .txt
    inicializarCalendario(Lista);
    leerArchivoCalendario(Lista);
}

int eliminarCita(ListaCalendario &Lista,int cedula,int condicion){// condicion es 0 cuando se va a modificar la cita, 1 cuando a el paciente se le actualizo la historia
    NodoCalendario NodoHorizontal = Lista;
    NodoCalendario NodoVertical;
    while(NodoHorizontal!=NULL){
        NodoVertical=NodoHorizontal;
        while(NodoVertical!=NULL){
            if(NodoVertical->HoraNodo.cedula == cedula){
                NodoVertical->HoraNodo.cedula = condicion;
                return 1;
            }
            NodoVertical = NodoVertical->siguienteVertical;
        }
        NodoHorizontal = NodoHorizontal->siguienteHorizontal;
    }
    return 1;
}

void imprimirFecha(int dia, int mes){ //recibido un dia y un mes como enteros, se encarga de imprimir la fecha en formato
    if(dia>=10){
        cout <<dia<<"/"<<"0"<<mes<<"/"<<"2020";
    }else
    {
        cout<<"0"<<dia<<"/"<<"0"<<mes<<"/"<<"2020";
    }    
}

void imprimirHora(int hora){ // dada la hora en entero, se encarga de imprimir la hora en formato
    if(hora>=10){
        cout <<hora<<":00";
    }else
    {
        cout <<"0"<<hora<<":00";
    }
    
}

NodoCalendario informacionCita(ListaCalendario Lista, int cedula){ //Se encarga de buscar un nodo marcado por una cedula en la lista de calendario y lo retorna
    NodoCalendario NodoHorizontal = Lista;
    NodoCalendario NodoVertical;
    while(NodoHorizontal!=NULL){
        NodoVertical = NodoHorizontal;
        while(NodoVertical!=NULL){
            if(NodoVertical->HoraNodo.cedula==cedula){
                return NodoVertical;                
            }
            NodoVertical = NodoVertical->siguienteVertical;
        }
        NodoHorizontal = NodoHorizontal->siguienteHorizontal;
    }
    return NodoVertical;
}

void mostrarNodoInformacionCita(NodoCalendario Nodo){ //Recibe un nodo por parametro e imprime toda la informacion relacionada con el
    
    cout <<"Informacion de la cita"<<'\n';
    cout <<"Cedula del paciente : "<<Nodo->HoraNodo.cedula<<'\n';
    cout <<"Fecha : ";
    imprimirFecha(Nodo->dia,Nodo->mes);
    cout <<" "<<"Hora : ";
    imprimirHora(Nodo->HoraNodo.hora);
    cout << '\n';
}

void mostrarInformacionCita(ListaCalendario Lista){ //Se encarga de gestionar el mostrar la infomracion relacionada a una cita marcada por una cedula
    NodoCalendario Nodo;
    int cedula;
    cout << "Ingrese la cedula del paciente al que quiere ver su cita"<<'\n';
    cin>>cedula;
    if(existenciaCita(Lista,cedula)){
        Nodo = informacionCita(Lista,cedula);
        cout << " ";
        mostrarNodoInformacionCita(Nodo);
        cout << "Presione una tecla para continuar"<<'\n';
        getch();
    }else
    {
        cout << "No hay ninguna cita reservada con esta cedula"<<'\n';
        cout << "Presione una tecla para continuar"<<'\n';
        getch();
    }
    
}

bool mostrarInformacionModificarCita(ListaCalendario Lista, int cedula){//Esta funcion se encarga de mostrar y preguntar si se quiere modificar la cita de un paciente
    int opcion;
    NodoCalendario NodoHorizontal = Lista;
    NodoCalendario NodoVertical;
    while(NodoHorizontal!=NULL){
        NodoVertical=NodoHorizontal;
        while(NodoVertical!=NULL){
            if(NodoVertical->HoraNodo.cedula==cedula){
                cout <<"Informacion de la cita"<<'\n';
                cout <<"Cedula del paciente : "<<cedula<<'\n';
                cout <<"Fecha : ";
                imprimirFecha(NodoVertical->dia,NodoVertical->mes);
                cout<<'\n';
                cout << "Hora : ";                
                imprimirHora(NodoVertical->HoraNodo.hora);
                cout <<'\n';
                cout << "Si quiere modificar la fecha de esta cita presione 1, si la quiere dejar como esta presione 2"<<'\n';
                cin>>opcion;
                if(opcion==1)return true;
                else{
                    return false;
                }
            }
            NodoVertical = NodoVertical->siguienteVertical;
        }
        NodoHorizontal = NodoHorizontal->siguienteHorizontal;
    }
    return false;
}

int modificarCita(ListaCalendario &Lista){ //Esta funcion se encarga de gestionar todo lo relaciona al modificar de una cita
    int cedula;
    cout <<"Introduzca la cedula del paciente que quiere modificar su cita"<<'\n';
    cin >> cedula;
    if(!existenciaCita(Lista,cedula)){
        cout << "No se ha encontrado ninguna cita con la cedula de este paciente"<<'\n';
        cout << "Presiona una tecla para continuar"<<'\n';
        getch();
        return 1;
    }
    if(mostrarInformacionModificarCita(Lista,cedula)==true){
    eliminarCita(Lista,cedula,0);
    agendarCita(Lista,cedula);
    }else
    {
        cout << "No se realizo ningun cambio en la fecha de la cita"<<'\n';
        cout << "Presione una tecla para continuar"<<'\n';
        getch();
        return 1;
    }
    
    return 1;
}

void imprimirCitasFecha(ListaCalendario Lista,int dia,int mes){ //Se encarga de imprimir todas las citas que hay para una fecha
    NodoCalendario NodoHorizontal = Lista;
    NodoCalendario NodoVertical;
    while(NodoHorizontal!=NULL){
        if(NodoHorizontal->dia==dia && NodoHorizontal->mes==mes){
            NodoVertical = NodoHorizontal;
            while(NodoVertical!=NULL){

            }
        }
    }
}

NodoCalendario encontrarNodoFecha(ListaCalendario ListaCalendario,int dia, int mes){
    NodoCalendario NodoHorizontal = ListaCalendario;
    
    while(NodoHorizontal!=NULL){
        if(NodoHorizontal->dia==dia &&NodoHorizontal->mes==mes){
            return NodoHorizontal;
        }
        NodoHorizontal = NodoHorizontal->siguienteHorizontal;
    }
    return NULL; 
}

bool fechaCorrecta(ListaCalendario Lista, int dia1, int dia2, int mes1,int mes2){ //Se encarga de verificar si los dias y meses recibidos por parametro corresponden a una fecha existente en la lista de calendario
    NodoCalendario Nodo1 = Lista;
    NodoCalendario Nodo2;
    while(Nodo1!=NULL){
        if(Nodo1->dia==dia1 && Nodo1->mes==mes1){
            Nodo2 = Nodo1;
            while(Nodo2!=NULL){
                if(Nodo2->dia==dia2 && Nodo2->mes==mes2){
                    return true;
                }
                Nodo2 = Nodo2->siguienteHorizontal;
            }
        }
        Nodo1 = Nodo1->siguienteHorizontal;
    }
    return false;
}

int numeroDeDias(ListaCalendario Lista, int dia1, int dia2, int mes1, int mes2){ //se encarga de contar la cantidad de dias que hay entre dos fechas y retorna este numero
    int cont = 0;
    NodoCalendario Nodo1 = Lista;
    NodoCalendario Nodo2;
    while(Nodo1!=NULL){
        if(Nodo1->dia==dia1 && Nodo1->mes==mes1){
            Nodo2 = Nodo1;
            while(Nodo2!=NULL){
                if(Nodo2->dia==dia2 && Nodo2->mes==mes2){
                    return cont;
                }
                cont++;
                Nodo2 = Nodo2->siguienteHorizontal;
            }
        }
        Nodo1 = Nodo1->siguienteHorizontal;
    }
    
}

NodoCalendario fechaInicial(ListaCalendario ListaCalendario,int dia1,int mes1){
    NodoCalendario NodoHorizontal = ListaCalendario;
    while(NodoHorizontal!=NULL){
        if(NodoHorizontal->dia==dia1 && NodoHorizontal->mes==mes1){
            return NodoHorizontal;
        }
        NodoHorizontal = NodoHorizontal->siguienteHorizontal;
    }
    return NULL;
}

