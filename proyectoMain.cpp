#include <iostream>
#include <fstream>
#include <conio.h>
#include "nuevoCalendario.cpp"
#include "historiaPaciente.cpp"
#include "RegistroPaciente.cpp"
#include "menusProyecto.cpp"
#include "libreriasCombinadas.cpp"
#include "PrincipalDes.cpp"

using namespace std;

ListaPaciente ListaPacienteMain; //Estructura relacionada a PACIENTES
NodoPaciente NodoPacienteMain;

ListaHistoria ListaHistoriaMain; //Estructura relacionada a la HISTORIA de los pacientes
NodoHistoria NodoHistoriaMain;

ListaCalendario ListaCalendarioMain; //Estructura relacionada al CALENDARIO para citas;
NodoCalendario NodoCalendarioMain;


int main(){
    
    //pedirDatosUsuario();//uadmin01
                        //EelC3AN


    ListaPacienteMain = NULL;
    ListaHistoriaMain = NULL;
    ListaCalendarioMain = NULL;
    leerArchivoHistoriaPaciente(ListaHistoriaMain);    
    gestionamientoCalendario(ListaCalendarioMain);
    leerArchivoPaciente(ListaPacienteMain); 
    

    int opcionMenu1,opcionMenu2,opcionMenu3;

    
    menuDos(); 
    while(cin>>opcionMenu1 && opcionMenu1!=3){        
    
        
        switch(opcionMenu1){
            case 1://Historia
                menuRegistroPaciente();
                while(cin>>opcionMenu2 && opcionMenu2!=6){     
                              
                     
                    switch(opcionMenu2){
                        case 1://Registro de paciente
                            pedirDatosPaciente(ListaPacienteMain);
                            guardarArchivoPaciente(ListaPacienteMain);
                            break;
                        case 2://Modificacion de registro de paciente
                            gestionarModificacionRegistroPaciente(ListaPacienteMain,ListaCalendarioMain,ListaHistoriaMain);
                            guardarArchivoPaciente(ListaPacienteMain);
                            guardarArchivoCalendario(ListaCalendarioMain);
                            guardarArchivoHistoriaPaciente(ListaHistoriaMain);
                            break;
                        case 3://Registro de historia
                            registrarHistoriaPaciente(ListaHistoriaMain,ListaCalendarioMain);
                            guardarArchivoHistoriaPaciente(ListaHistoriaMain);
                            guardarArchivoCalendario(ListaCalendarioMain);
                            break;                        

                        case 4://Modificacion de actualizacion de historia
                            gestionModificacionHistoria(ListaHistoriaMain);
                            guardarArchivoHistoriaPaciente(ListaHistoriaMain);
                            break;

                        case 5://Mostrar historial de un paciente
                            gestionMostrarHistoriaPaciente(ListaHistoriaMain);
                            break;
                        /*case 6://Salir;

                            break;*/                            

                        default:
                            if(opcionMenu2!=1 ||opcionMenu2!=2 ||opcionMenu2!=3 ||opcionMenu2!=4 ||opcionMenu2!=5 ||opcionMenu2!=6){                            
                                cout << "Ingrese una opcion valida"<<'\n';
                                cout << "Presione una tecla para continuar"<<'\n';
                                getch();
                                break;
                            }
                    }
                    menuRegistroPaciente();
                }

                break; 
            case 2://Cita de paciente
                menuCitaPaciente();
                while(cin>>opcionMenu3&&opcionMenu3!=6){
                    

                    switch(opcionMenu3){
                        case 1://Registro de cita
                            gestionamientoCitas(ListaCalendarioMain,ListaPacienteMain);
                            guardarArchivoCalendario(ListaCalendarioMain);
                            break;
                        case 2://Modificar cita
                            modificarCita(ListaCalendarioMain);
                            guardarArchivoCalendario(ListaCalendarioMain);
                            break;
                        case 3://Mostrar la cita para un paciente
                            mostrarInformacionCita(ListaCalendarioMain);
                            break;
                        case 4://Mostrar citas para una fecha
                            mostrarCitasFecha(ListaCalendarioMain,ListaPacienteMain);
                            break;
                        case 5://Mostrar citas para un rango de fechas
                            mostrarCitasFechas(ListaCalendarioMain,ListaPacienteMain);
                            break;
                        default:
                           if(opcionMenu3!=1 ||opcionMenu3!=2 ||opcionMenu3!=3 ||opcionMenu3!=4 ||opcionMenu3!=5  ||opcionMenu3!=6){                            
                                cout << "Ingrese una opcion valida"<<'\n';
                                cout << "Presione una tecla para continuar"<<'\n';
                                getch();
                                break;
                            } 

                    }
                    menuCitaPaciente();
                }


                break;
            case 3://Salir

                break;
            default:
                if(opcionMenu1!=1 ||opcionMenu1!=2 ||opcionMenu1!=3){                            
                    cout << "Ingrese una opcion valida"<<'\n';
                    cout << "Presione una tecla para continuar"<<'\n';
                    getch();
                    break;
                }
                break;   
                           
        }
        menuDos(); 
}

    return 0;
}