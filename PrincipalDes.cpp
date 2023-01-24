#pragma once
#include <iostream>
#include <string.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <conio.h>


#include "DES.h"

using namespace std;
string Desencriptar_clave(string ct);
string Encriptar_clave(char* temp_clave);
void MenuClave( );

void pedirDatosUsuario(){
    system("cls");    
    string usuario,usuarioArchivo,contraArchivo; //uadmin01
    string contrasena; //EelC3AN
    string contrasenaDescifrada;
    string nombre,especialidad,diasLaborales,horario;
    ifstream lectorDoctor("doctor.txt");
    while(getline(lectorDoctor,usuarioArchivo)&&getline(lectorDoctor,contraArchivo)&&getline(lectorDoctor,nombre)&&getline(lectorDoctor,especialidad)&&getline(lectorDoctor,diasLaborales)&&getline(lectorDoctor,horario)){        
        contraArchivo = Desencriptar_clave(contraArchivo);        
        cout << "Ingrese el usuario"<<'\n';
        while(cin>>usuario&&usuario!=usuarioArchivo){
            cout << "Usuario incorrecto, intente de nuevo"<<'\n';
        }
        cout << "Ingrese la contrasena"<<'\n';
        while(cin>>contrasena&&contrasena!=contraArchivo){
            cout << "Contrasena incorrecta, intente de nuevo"<<'\n';                    
        }
        cout << "Nombre del doctor         : "<< nombre<<'\n';
        cout << "Especialidad del doctor   : "<<especialidad<<'\n';
        cout << "Dias laborales del doctor : "<<diasLaborales<<'\n';
        cout << "Horas para cada dia       : "<<horario<<'\n';
        cout <<'\n';
        cout <<"Presione una tecla para continuar"<<'\n';
        getch();

	} 
}
