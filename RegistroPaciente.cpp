#pragma once
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "nuevoCalendario.cpp"


using namespace std;



struct EstructuraPaciente{ //Esta sera la estructura relacionada con cada paciente que sera registrado
    string nombre;
    string apellido;
    int cedula;
    string fechaNacimiento;
    string sexo;
    string direccion;
    int ID_Pacientes;
    struct EstructuraPaciente *siguiente;
};

typedef EstructuraPaciente *ListaPaciente;
typedef EstructuraPaciente *NodoPaciente;



NodoPaciente crearNodo(){                      //Funcion que se encarga de crear un nodo para luego ser definido por otra funcion
    NodoPaciente NodoTemporal = new (struct EstructuraPaciente);//Devuelve el nodo con su espacio de memoria reservado
    NodoTemporal->siguiente = NULL;
    return NodoTemporal;
}

NodoPaciente definirNodoPaciente(string nombre, string apellido, int long cedula, string fechaNacimiento,string sexo, string direccion){
    NodoPaciente NodoTemporal = crearNodo();   //Esta funcion se encarga de inicializar un nodo con los datos del paciente
    NodoTemporal->nombre = nombre;          //Devuelve el nodo con toda la informacion cargada
    NodoTemporal->apellido = apellido;
    NodoTemporal->cedula = cedula;
    NodoTemporal->fechaNacimiento = fechaNacimiento;
    NodoTemporal->sexo = sexo;
    NodoTemporal->direccion = direccion;
    return NodoTemporal;
}

void insertarPaciente(ListaPaciente &Lista, NodoPaciente Nodo){ //Se encarga de insertar un nodo recibido por parametro
    ListaPaciente ListaTemporal = new(struct EstructuraPaciente);// al final de la lista recibida por referencia
    if(Lista == NULL) Lista = Nodo;
    else{
        ListaTemporal = Lista;
        while (ListaTemporal->siguiente != NULL){
            ListaTemporal = ListaTemporal -> siguiente;
        }
        ListaTemporal -> siguiente = Nodo;
    }
   // Salvar_archivo_paciente(Lista);
}

bool sonDigitos(const std::string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}

int pedirCedula(){
    bool bandera =false;
    string cedulaLetra;
    int cedula;    
    while(bandera ==false){
                
        getline(cin,cedulaLetra);
        if(sonDigitos(cedulaLetra)){
            cedula = stoi(cedulaLetra);
            if(cedula>1000000 && cedula<99999999){
                bandera = true;
            }else
            {
                cout << "La cedula que ingreso no es valida"<<'\n';
                cout << "Una cedula valida contiene entre 7 y 9 digitos"<<'\n';
                cout<<"Ingrese el numero de cedula del paciente: "<<'\n';
                getch();
            }
            
            
        }else
        {
            cout << "La cedula que introdujo contiene letras"<<'\n';
            cout << "Una cedula valida solo contiene numeros y tiene entre 7 y 9 digitos"<<'\n';
            cout<<"Ingrese el numero de cedula del paciente: "<<'\n';
            getch();
        }
        

    }
    return cedula;
   


/*
    while(cin>>cedula && cedula<1000000 || cedula>99999999){
        cout << "Introduzca una cedula valida"<<'\n';
        cout << "Una cedula valida esta comprendida entre los 6 y 8 digitos  "<<'\n';
    }*/
}

int pedirCedulaHistoria(){
    bool bandera =false;
    string cedulaLetra;
    int cedula;
    
    while(bandera ==false){
        cin.get();        
        getline(cin,cedulaLetra);
        if(sonDigitos(cedulaLetra)){
            cedula = stoi(cedulaLetra);
            if(cedula>1000000 && cedula<99999999){
                bandera = true;
            }else
            {
                cout << "La cedula que ingreso no es valida"<<'\n';
                cout << "Una cedula valida contiene entre 7 y 9 digitos"<<'\n';
                cout<<"Ingrese el numero de cedula del paciente: "<<'\n';
                getch();
            }
            
            
        }else
        {
            cout << "La cedula que introdujo contiene letras"<<'\n';
            cout << "Una cedula valida solo contiene numeros y tiene entre 7 y 9 digitos"<<'\n';
            cout<<"Ingrese el numero de cedula del paciente: "<<'\n';
            getch();
        }
        

    }
    return cedula;
   


/*
    while(cin>>cedula && cedula<1000000 || cedula>99999999){
        cout << "Introduzca una cedula valida"<<'\n';
        cout << "Una cedula valida esta comprendida entre los 6 y 8 digitos  "<<'\n';
    }*/
}

string pedirGenero(){
    bool bandera = false;
    int opcion;
    string Genero;
    while(bandera == false){
        cout << "Ingrese 1 si es masculino"<<'\n';
        cout << "Ingrese 2 si es femenino"<<'\n';
        cin >> opcion;
        if(opcion==1){
            Genero = "Masculino";
            bandera = true;
        }else if (opcion==2)
        {
            Genero = "Femenino";
            bandera = true;
        }else
        {
            cout <<"Ingreso una opcion erronea"<<'\n';
        }      
        
        
    }
    return Genero;
}

string pedirFechaNacimiento(){
    string fechaNacimientoTemporal;
    string fechaNacimiento;
    bool bandera = false;
    while(bandera == false){
        cout << "El formado debe ser dd/mm/aaaa (Ejemplo : 04/12/2000)"<<'\n';
        cin >> fechaNacimientoTemporal;
        
        if(fechaNacimientoTemporal.length()==10){
            if(fechaNacimientoTemporal[2]=='/'&&fechaNacimientoTemporal[5]=='/'){
                stringstream ss;
                ss <<fechaNacimientoTemporal[0]<<fechaNacimientoTemporal[1]<<fechaNacimientoTemporal[3]<<fechaNacimientoTemporal[4]<<fechaNacimientoTemporal[6]<<fechaNacimientoTemporal[7]<<fechaNacimientoTemporal[8]<<fechaNacimientoTemporal[9];
                fechaNacimiento = ss.str();            
                if(sonDigitos(fechaNacimiento)){   
                    bandera = true;            
                }else
                {
                    cout << "La fecha de nacimiento que ingreso contiene letras"<<'\n';
                    cout << "Presione una tecla para continuar"<<'\n';
                    getch();
                }
                
            }else
            {
                cout << "La fecha de nacimiento que ingreso no es valida. Recuerde utilizar / para la separacion entre dia-mes y mes-anio"<<'\n';
                cout << "Presione una tecla para continuar"<<'\n';
                getch();
            }        
        }else
        {
            cout << "La fecha de nacimiento que ingreso no es valida. Recuerde utilizar / para la separacion entre dia-mes y mes-anio"<<'\n';
            cout << "Presione una tecla para continuar"<<'\n';
            getch();
        }
    
    }
    return  fechaNacimientoTemporal;
}

bool existePaciente(ListaPaciente Lista, int cedula){ //Recibe la lista de pacientes por parametro y uan cedula para verificar si hay algun paciente
    NodoPaciente Nodo = Lista;                      //registrado con esa cedula
    while(Nodo!=NULL){
        if(Nodo->cedula == cedula)return true;
        else
        {
            Nodo = Nodo->siguiente;
        }
        
    }
    return false;
}

void pedirDatosPaciente(ListaPaciente &Lista){//Se encarga de pedir los datos que van a ser usados para definir el nodo de paciente y luego ser agregado a la lista
    NodoPaciente NodoTemporal = crearNodo();
    bool bandera = false;
    string tempNombre = "";
    string tempApellido = "";
    int tempCedula = 0;
    string tempNacimiento = "";
    string tempSexo = "";
    string tempDireccion = "";


    cout << "\n*******************************************" << endl;
	cout << "*        INSERTAR DATOS DEL PACIENTE.       *" << endl;
	cout << "********************************************" << endl<<endl;

	cin.get();
    cout<<"Ingrese  el nombre del paciente:  "<<endl;
    getline(cin,tempNombre);
    
	
    cout<<"Ingrese el apellido del paciente: "<<endl;
    getline(cin,tempApellido);
	
	
    cout<<"Ingrese el numero de cedula del paciente: "<<endl;
    while(bandera==false){
        tempCedula = pedirCedula();   
        if(existePaciente(Lista,tempCedula)){
            cout << "La cedula que ingreso ya le pertenece a un paciente"<<'\n';
            cout << "Intente de nuevo"<<'\n';
        }else
        {
            bandera = true;
        }
        
    }
       
	
	
    cout << "Ingrese la fecha de nacimiento del paciente"<<'\n';
    tempNacimiento = pedirFechaNacimiento();
    
	cin.get();
    cout<<"Ingrese el sexo del paciente :  "<<endl;
    tempSexo =pedirGenero();

	cin.get();
    cout<<"Ingrese la direccion del paciente:  "<<endl;
    getline(cin,tempDireccion);

     
    NodoTemporal = definirNodoPaciente(tempNombre,tempApellido,tempCedula,tempNacimiento,tempSexo,tempDireccion);
    insertarPaciente(Lista,NodoTemporal);

    cout <<"Se registro el nuevo paciente exitosamente"<<'\n';
    cout <<"Presione una tecla para continuar"<<'\n';
    getch();

}

void guardarArchivoPaciente(ListaPaciente Lista){
    NodoPaciente  Nodo = Lista; //Se encarga de guardar toda la informacion que hay en los nodos de la lista de pacientes en un archivo .txt
    std::ofstream escritor;
    escritor.open("pacientes.txt");
    if(Nodo){
        while(Nodo){
            escritor << Nodo->nombre;
            escritor << ';';
            escritor << Nodo->apellido;
            escritor << ';';
            escritor << Nodo->cedula;
            escritor << ';';
            escritor << Nodo->fechaNacimiento;
            escritor << ';';
            escritor << Nodo->sexo;
            escritor << ';';
            escritor << Nodo->direccion;            
            escritor << '\n';
            Nodo = Nodo->siguiente;
        }
    }
    escritor.close();   
}

void menuModificarDatoPaciente(){

    cout << "\n*******************************************" << endl;
    cout << " *        ESPECIFIQUE DATO A MODIFICAR.     *" << endl;
    cout << "********************************************" << endl<<endl;          		
    cout<<"1.Nombre:                          "<<endl;
    cout<<"2.Apellido:                        "<<endl;
    cout<<"3.Numero de cedula:                "<<endl;
    cout<<"4.Fecha de nacimiento:             "<<endl;
    cout<<"5.Sexo:                            "<<endl;
    cout<<"6.Direccion:                       "<<endl;
    cout<<"7. Salir                           "<<endl;
    cout<<"\n Ingrese opcion : ";
}

bool listaEsVacia(ListaPaciente Lista){ //funcion que verifica si la lista de pacientes es vacia
	bool bandera = false;
	if(Lista == NULL)bandera = true;
	return bandera;
}

void menuDatosPaciente(ListaPaciente Lista){
    ListaPaciente ListaTemporal = Lista;
    system("cls");
    cout << "\n******************************************" << endl;
    cout << "*        DATOS DEL PACIENTE.               *" << endl;
    cout << "*******************************************" << endl<<endl;
    cout<<" NOMBRES  : "<<ListaTemporal->nombre<<endl;
    cout<<" APELLIDOS: "<<ListaTemporal->apellido<<endl;
    cout<<" Numero de cedula: "<<ListaTemporal->cedula<<endl;
    cout<<" Fecha de nacimiento: "<<ListaTemporal->fechaNacimiento<<endl;
    cout<<" Sexo: : "<<ListaTemporal->sexo<<endl;
    cout<<" Direccion : "<<ListaTemporal->direccion<<endl;
}

void menuModificarRegistroPaciente(){
    system("cls");
    cout << "\n*******************************************" <<'\n';
    cout << "*       MODIFICAR DATOS DEL PACIENTE        *" <<'\n';
    cout << "********************************************" <<'\n'<<'\n';
}


void leerArchivoPaciente(ListaPaciente &Lista){ //Se encarga de la lectura de la informacion de un archivo .txt que pertenece a los nodos de la lista de pacientes
    NodoPaciente Nodo;   
    string tempNombre = "";
    string tempApellido = "";
    string tempCedulaLetra = "";
    int long tempCedula = 0;
    string tempFechaNacimiento = "";
    string tempSexo = "";
    string tempDireccion ="";
    ifstream lectorPacientes("pacientes.txt");

    for (string linea; getline(lectorPacientes, linea); ){
            
            istringstream iss(linea);
            getline(iss, tempNombre, ';');                                 
            getline(iss, tempApellido,';');                                 
            getline(iss, tempCedulaLetra,';'); 
            tempCedula = stoi(tempCedulaLetra);
            getline(iss, tempFechaNacimiento,';'); 
            getline(iss, tempSexo,';'); 
            getline(iss, tempDireccion);   
            Nodo = definirNodoPaciente(tempNombre,tempApellido,tempCedula,tempFechaNacimiento,tempSexo,tempDireccion);                
            insertarPaciente(Lista,Nodo);
        }

    lectorPacientes.close();

}


int eliminarPaciente(ListaPaciente &Lista, int long auxCedula){
    NodoPaciente NodoTemporal;
	ListaPaciente ListaTemporal = Lista;
	if (ListaTemporal)
	   if (ListaTemporal->cedula==auxCedula){
	   	   Lista=Lista->siguiente;
	   	   delete ListaTemporal;
	   	   return 1;
	   }
	   else {
	   	    while ((ListaTemporal->siguiente)&&(ListaTemporal->siguiente->cedula != auxCedula)) 
			   ListaTemporal=ListaTemporal->siguiente;
	   	   if (ListaTemporal->siguiente){
	   	   	   NodoTemporal = ListaTemporal->siguiente;
	   	   	   ListaTemporal->siguiente = ListaTemporal->siguiente->siguiente;
	   	   	   delete NodoTemporal;
	   	   	   return 1;
			  }
	   }
}


void mostrarListaPaciente(ListaPaciente Lista){
    ListaPaciente ListaTemporal = Lista;
    int enumerador=1;
    while(ListaTemporal!=NULL){

        cout<<"\n\tDATOS DEL PACIENTE ["<<enumerador<<"] ";
        cout<<"\n\t******************************"<<endl;
        cout<<"   1.NOMBRES:   "<< std:: setw(2) << ListaTemporal->nombre <<endl;
        cout<<"   2.APELLIDOS:   "<<setw(2)<<ListaTemporal->apellido<<endl;
        cout<<"   3.NUMERO DE CEDULA:  "<<setw(2)<<ListaTemporal->cedula<<endl;
        cout<<"   4.FECHA DE NACIMIENTO:"<<setw(2)<<ListaTemporal->fechaNacimiento<<endl;
        cout<<"   5.SEXO: "<<setw(2)<<ListaTemporal->sexo<<endl;
        cout<<"   6.DIRECCION: "<< setw(2)<<ListaTemporal->direccion<<endl;
        
        enumerador++;
        ListaTemporal = ListaTemporal->siguiente;
    }
}

NodoPaciente buscarPacienteCedula(ListaPaciente Lista,int cedula){ //Se encarga de buscar el nodo de un paciente mediante su cedula y este nodo ser retornado 
    NodoPaciente Nodo = Lista;
    while(Nodo!=NULL){
        if(Nodo->cedula==cedula){
            return Nodo;
        }
        Nodo = Nodo->siguiente;
    }
    return NULL;
}



