#pragma once
#include <iostream>
#include <conio.h>
#include "nuevoCalendario.cpp"
#include "historiaPaciente.cpp"
#include "RegistroPaciente.cpp"


using namespace std;
/*
typedef Historia *ListaHistoria;
typedef Historia *NodoHistoria;

typedef Calendario *ListaCalendario;
typedef Calendario *NodoCalendario;*/

void registrarHistoriaPaciente(ListaHistoria &ListaHistoria,ListaCalendario &ListaCalendario){ //Recibiendo la lista de historias y la lista del calendario
    NodoCalendario NodoCalendario;                                                              //esta funcion se encarga de registrar la historia de un paciente
    int cedula;                                                                                 //Saca la informacion de la cita almacenada relacionada con la cedula del paciente
    cout << "Introduzca el numero de cedula del paciente del que quiere registrar una historia"<<'\n';  //y la utiliza para crear un nuevo nodo en la lista de historias
    cin >> cedula;
    if(existenciaCita(ListaCalendario,cedula)){          
        NodoCalendario = informacionCita(ListaCalendario,cedula);
        pedirDatosHistoria(ListaHistoria,cedula,NodoCalendario->dia,NodoCalendario->mes,NodoCalendario->HoraNodo.hora);
        eliminarCita(ListaCalendario,cedula,1);
    }else
    {
        cout <<"No hay ninguna cita registrada para este paciente"<<'\n';
        cout <<"Presione una tecla para continuar"<<'\n';
        getch();
    }
    
}

bool fechaExiste(ListaCalendario Lista, int dia, int mes){ //Se encarga de verificar si una fecha introducida por el usuario esta contemplada en el calendario del programa
    NodoCalendario NodoHorizontal = Lista;
    while(NodoHorizontal!=NULL){
        if(NodoHorizontal->dia == dia && NodoHorizontal->mes==mes){
            return true;
        }
        NodoHorizontal = NodoHorizontal->siguienteHorizontal;
    }
    return false;
}

void imprimirNodoFechas(NodoCalendario Nodo, ListaPaciente ListaPaciente){ //Recibe un primer nodo vertical y la lista de pacientes
    NodoPaciente NodoPaciente;                                              //Esta funcion se encarga de imprimir todas las citas que hay para una fecha determinada
    while(Nodo!=NULL){
        if(Nodo->HoraNodo.cedula!=0 &&Nodo->HoraNodo.cedula!=1){
            NodoPaciente = buscarPacienteCedula(ListaPaciente, Nodo->HoraNodo.cedula);
            imprimirFecha(Nodo->dia,Nodo->mes);            
            cout <<" "<<NodoPaciente->nombre <<", "<<NodoPaciente->apellido<<", ";
            imprimirHora(Nodo->HoraNodo.hora);
            cout <<'\n';            
        }
        
        Nodo = Nodo->siguienteVertical;    
    }
}

void mostrarCitasFecha(ListaCalendario ListaCalendario,ListaPaciente ListaPaciente){//Esta funcion se encarga de pedir la fecha para la que se quiere
    NodoCalendario NodoCalendario;                                              //ver todas las citas de ese dia
    int dia,mes;
    cout << "Este programa tiene un calendario comprendido entre las fechas 07/07/2020 y 06/08/2020"<<'\n';    
    cout << "Introduzca el dia (Ejemplo : 7,26...)"<<'\n';
    cin >>dia;
    cout << "Introduzca el mes (Ejemplo 7,8...)"<<'\n';
    cin>>mes;
    if(fechaExiste(ListaCalendario,dia,mes)){
        NodoCalendario = encontrarNodoFecha(ListaCalendario,dia,mes);
        if(NodoCalendario == NULL){
            cout <<"No hay ninguna cita para esta fecha"<<'\n';
            cout <<"Presione una tecla para continuar"<<'\n';
            getch();
        }else
        {
            cout<<'\n';        
            imprimirNodoFechas(NodoCalendario,ListaPaciente);
            cout <<'\n';
            cout <<"Presione una tecla para continuar"<<'\n';
            getch();
        }       
    }else
    {
        cout << "La fecha que introdujo no existe en este programa"<<'\n';
        cout <<"Presione una tecla para continuar"<<'\n';
        getch();
    }    
}

void mostrarCitasFechas(ListaCalendario ListaCalendario,ListaPaciente ListaPaciente){//Esta funcion se encarga de gestionar toda la informacion necesaria
    NodoCalendario NodoCalendario;                                                      //para mostrar las citas que hay en un rango de fechas
    int dia1,dia2,mes1,mes2;
    int ContadorDia;
    cout << "Este programa tiene un calendario comprendido entre las fechas 07/07/2020 y 06/08/2020"<<'\n'; 
    cout << "Introduzca el dia de inicio (Ejemplo : 7,26...)"<<'\n';
    cin >>dia1;
    cout << "Introduzca el mes de inicio (Ejemplo 7,8...)"<<'\n';
    cin>>mes1;
    cout << "Introduzca el dia final (Ejemplo : 7,26...)"<<'\n';
    cin >>dia2;
    cout << "Introduzca el mes final (Ejemplo 7,8...)"<<'\n';
    cin>>mes2;
    if(fechaExiste(ListaCalendario,dia1,mes1)){
        if(fechaExiste(ListaCalendario,dia2,mes2)){
            if(fechaCorrecta(ListaCalendario,dia1,dia2,mes1,mes2)){
                ContadorDia = numeroDeDias(ListaCalendario,dia1,dia2,mes1,mes2);
                NodoCalendario = fechaInicial(ListaCalendario,dia1,mes1);
                for(int i = 0; i<=ContadorDia;i++){
                    imprimirNodoFechas(NodoCalendario,ListaPaciente);
                    NodoCalendario = NodoCalendario->siguienteHorizontal;
                }
                cout <<'\n';
                cout <<"Presione una tecla para continuar"<<'\n';
                getch();
            }
            else
            {
                cout <<"La segunda fecha que introdujo no se encuentra despues de la primera fecha"<<'\n';
                cout <<"Presione una tecla para continuar"<<'\n';
                getch();
            }
            
        }else
        {
            cout<<"La segunda fecha que introdujo no esta contemplada en el calendario del programa"<<'\n';
            cout <<"Presione una tecla para continuar"<<'\n';
            getch();
        }
        

    }else
    {
        cout<<"La primera fecha que introdujo no esta contemplada en el calendario del programa"<<'\n';
        cout <<"Presione una tecla para continuar"<<'\n';
        getch();
    }
    
}

int ModificarDatoPaciente(ListaPaciente &Lista,ListaCalendario &ListaCalendario,ListaHistoria &ListaHistoria,int auxCedula){ //recibido una cedula y la lista por referencia, se encarga de buscar el paciente al que pertenece dicha cedula
	int cedulaVieja;
    ListaPaciente ListaTemporal = Lista;                                                            // y permite modificar los datos contenidos en ella                     
    int cedulaTemporal;
    string sexoTemporal;
    string fechaNacimientoTemporal;   
    int oMenu = 0;
    bool bandera = false;

    
    menuModificarRegistroPaciente();

    while(ListaTemporal !=NULL){
        if(ListaTemporal->cedula == auxCedula){
            do{ 
                    menuDatosPaciente(ListaTemporal);
			        menuModificarDatoPaciente();
			        cin>>oMenu;
                    switch(oMenu){
                    case 1:  cout<<" Por favor ingresa el nombre que quiera modificar "<<endl;
                            cin.get();
                            getline(cin,ListaTemporal->nombre);
                            cout <<"Se modifico el dato exitosamente"<<'\n';
                            getch();
                            break;
                            
                    case 2:  cout<<" Por favor ingrese el apellido que quiera modificar"<<endl;
                            cin.get();
                            getline(cin,ListaTemporal->apellido);
                            cout <<"Se modifico el dato exitosamente"<<'\n';
                            getch();
                            break;
                            
                    case 3: cout<<"Por favor ingrese el numero de cedula que quiera modificar"<<endl;
                            
                            cedulaVieja = ListaTemporal->cedula;
                            
                            while(bandera==false){
                                cedulaTemporal = pedirCedulaHistoria();  
                                if(existePaciente(Lista,cedulaTemporal)){
                                    cout << "La cedula que ingreso ya le pertenece a un paciente"<<'\n';
                                    cout << "Intente de nuevo"<<'\n';
                                }else
                                {
                                    bandera = true;
                                }
                                
                            }
                            


                            
                            
                            
                                                        
                            ListaTemporal->cedula = cedulaTemporal;

                             
                            
                            if(existenciaCita(ListaCalendario,cedulaVieja)){
                                eliminarCita(ListaCalendario,cedulaVieja,cedulaTemporal);  
                            }
                             
                            modificarCedulaHistoria(ListaHistoria,cedulaVieja,cedulaTemporal);

                            cout <<"Se modifico el dato exitosamente"<<'\n';
                            getch();
                            break;
                            
                    case 4: cout<<" Por favor ingrese la fecha de nacimiento que quiera modificar"<<endl;
                            
                            cin.get();
                            fechaNacimientoTemporal = pedirFechaNacimiento();
                            cout <<"Se modifico el dato exitosamente"<<'\n';
                            getch();
                            break;
                            
                    case 5: cout<<" Por favor ingrese el sexo que quiera modificar"<<endl;
                            cin.get();                            
                            sexoTemporal =pedirGenero();
                            ListaTemporal->sexo = sexoTemporal;
                            cout <<"Se modifico el dato exitosamente"<<'\n';
                            getch();
                            break;
                            
                    case 6: cout<<" Por favor ingresa la direccion que quiera modificar"<<endl;
                            cin.get();
                            getline(cin,ListaTemporal->direccion);
                            cout <<"Se modifico el dato exitosamente"<<'\n';
                            getch();
                            break;

                    case 7: 
                        
                        return 1;                          
                    
                    default:cout<<"\nINGRESE UNA OPCION VALIDA...\n"; 
                            cout << "Presione una tecla para continuar"<<"\n";
                            getch();
                            break;			 	
			    }
               
                    
            }while(oMenu != 7);       
                
        }else{
            ListaTemporal = ListaTemporal->siguiente; 
        }
    }    
}

int gestionarModificacionRegistroPaciente(ListaPaciente &Lista, ListaCalendario &ListaCalendario, ListaHistoria &ListaHistoria){ //Se encarga de gestionar todo lo relacionado a la parte de modificar los datos de un paciente
    if(listaEsVacia(Lista)){                                     //recibe por referencia la lista de pacientes 
        cout <<"No se encuentra ningun paciente registrado todavia"<<'\n';
        cout <<"Presione una tecla para continuar"<<'\n';
        getch();
        return 1;
    }

    int cedula;
    cout << "Introduzca la cedula del paciente al que quere modificar su registro"<<'\n';
    cin >> cedula;
    if(existePaciente(Lista,cedula)){
        ModificarDatoPaciente(Lista,ListaCalendario,ListaHistoria,cedula);
        return 1;
      
    }else{
        cout << "La cedula que introdujo no pertence a ningun paciente registrado"<<'\n';       
        cout <<"Presione una tecla para continuar"<<'\n';
        getch();
        return 1;
    }
   return 1; 
}