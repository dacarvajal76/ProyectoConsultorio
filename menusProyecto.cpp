#pragma once
#include <iostream>

using namespace std;

void menuDos(){
    system("cls");
    cout<<"1. Historias de pacientes"<<'\n';
    cout<<"2. Citas de pacientes"<<'\n';
    cout<<"3. Salir"<<'\n';
    cout<<"Ingrese una opcion : ";
}

void menuRegistroPaciente(){
    system("cls");
    cout<<"\t MENU DE HISTORIA DE PACIENTES   \n";
    cout<<"************************************************\n\n";
    cout<<" 1. Registro de paciente"<<'\n';
    cout<<" 2. Modificacion de registro de paciente"<<'\n';
    cout<<" 3. Registro de historia"<<'\n';    
    cout<<" 4. Modificacion de actualizacion de historia"<<'\n';
    cout<<" 5. Mostrar historial de un paciente"<<'\n';
    cout<<" 6. SALIR"<<'\n';
	cout<<" Ingrese una opcion : ";
}

void menuCitaPaciente(){
    system("cls");
    cout<<"\n\t\t MENU DE CITA DE PACIENTES   \n";
    cout<<"\t\t************************************************\n\n";
    cout<<" 1. Registro de cita"<<'\n';
    cout<<" 2. Modificar cita"<<'\n';
    cout<<" 3. Mostrar la cita para un paciente"<<'\n';
    cout<<" 4. Mostrar citas para una fecha"<<'\n';
    cout<<" 5. Mostrar citas para un rango de fechas"<<'\n';
    cout<<" 6. Salir"<<'\n';   
	cout<<" Ingrese una opcion : ";

}

