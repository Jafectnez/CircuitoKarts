#include <iostream> // Funciones y comandos necesarios(cin,cout)
#include <stdio.h> // Inputs y Outputs
#include <conio.h> //Consola de entrada y salida
#include <cstdlib> //Funciones que sirven para controlar ciertos recursos del sistema operativo
#include <time.h> //Formato hora y fecha
#include <stdlib.h>//Busqueda y ordenamiento de datos
#include <unistd.h> //LibrerÌa que contiene funciones para el manejo de directorios y archivos
#include <Windows.h> //Funciones Windows API
#include "Semaforo.cpp"
#include "Semaforo.h"
//#include <wait.h> // esta libreria se agrego para poder hacer uso del metodo wait o espera en espa√±ol
//#include <sys/errno.h> // esta libreria se usa para el reconocimiento del comando errno, recurso

#include  <fcntl.h>
//#include  <sys/ipc.h> //librerias que llaman a semget semaforos identificadores
//#include  <sys/sem.h> //librerias que llaman a semget semaforos identificadores
//#include  <sys/stat.h>
//#include  <sys/types.h> //librerias que llaman a semget semaforos identificadores

#define SEM_CIR_A_OPEN = 1;
#define SEM_CIR_N_OPEN = 1;

using namespace std;

//Declaracion de metodos, arreglos y variables
bool circuitoAdulto;
bool circuitoNino;
void espera();
void generarClienteAdultos();
void generarClienteNinos();
void enviarSalaEsperaAdultos();
void sacarSalaEsperaAdultos();
void enviarSalaEsperaNinos();
void sacarSalaEsperaNinos();
void asignarKartAdulto();
void asignarKartNino();
void verificar_kart();
void verificar_clima();
//void inicializar(int);

string adultos[6] = {"Adulto 1", "Adulto 2", "Adulto 3", "Adulto 4", "Adulto 5", "Adulto 6"};
string ninos[6] = {"Nino 1", "Nino 2", "Nino 3", "Nino 4", "Nino 5", "Nino 6"};
string mecanico = "Mecanico 1";
string kartsAdultos[4] ={"KartA 1","KartA 2","KartA 3","KartA 4"};
string kartsNinos[4] ={"KartN 1","KartN 2","KartN 3","KartN 4"};
string kartsAdultosLibres[4] ={"libre","libre","libre","libre"};
string kartsNinosLibres[4] ={"libre","libre","libre","libre"};
string colaEsperaAdulto[2] = {"libre", "libre"};
string colaEsperaNino[2] = {"libre", "libre"};
string colaLlegadaAdultos[6] = {"libre", "libre", "libre", "libre", "libre", "libre"};
string colaLlegadaNino[6] = {"libre", "libre", "libre", "libre", "libre", "libre"};

int num_random = rand();
int num_random_clima = rand();
int kartsAdultosDisponibles = 4;
int kartsNinosDisponibles = 4;
int tiempoConduccion = 3;
Semaforo semaforo;

/*union senum {
	int val;
};

struct sembuf{0, 1, 0} arriba;
struct sembuf{0, -1, 0} abajo;*/

int main(int argc, char** argv) {
	
	/*sem = semget(IPC_PRIVATE, 2, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR); /* Se crea un nuevo conjunto de sem√°foros nsems si la clave tiene el valor IPC_PRIVATE o si ning√∫n conjunto de sem√°foros existente est√° asociado con la clave y IPC_CREAT est√° especificado en semflg.*/

	while(true){
		for(int i = 0; i < 24; i++){
			if(i == 3 || i == 7 || i == 11 || i == 15 || i == 19 || i == 23){ //Para que el circuito cierre
				cout << "El circuito esta cerrando" << endl;
				espera();
				espera();
				cout << "El circuito cerrÛ" << endl;
				espera();
				Sleep(1000);
				system("cls"); //Se limpia la pantalla
			}
			else{
				circuitoAdulto = true;//El circuito de adultos se habilita
				circuitoNino = true;//El circuito de ninos se habilita
				cout << "El circuito de adultos esta abierto " << endl;
				espera();
				cout << endl;
				cout << "El circuito de ninos esta abierto " << endl;
				espera();
				cout << endl;
				cout << "Esperando clientes "<< endl;
				semaforo.wait();
				cout << endl;
				
				//Clientes llegando
				generarClienteAdultos();
				generarClienteNinos();
				Sleep(1000); //Permite hacer una pausa por una determinada cantidad de segundos en la ejecucion de un programa

				asignarKartAdulto();
				Sleep(1000);
				asignarKartNino();
				Sleep(1000); 
				
				verificar_clima();
				cout<<"Conduciendo en el circuito: "<< endl;
				cout<<endl;
				for(int i = 0; i < tiempoConduccion; i++){//Verificacion tiempo de conduccion
					cout << "Las personas estan conduciendo"<<endl;						
					cout << endl;
					verificar_kart();
					Sleep(2000);
					verificar_clima();
				}
				
				cout << "El tiempo para conducir terminÛ" << endl;
				Sleep(1000);
				cout << "Las personas estan saliendo de los karts" << endl;
				kartsAdultosLibres[0] = "libre";
				kartsAdultosLibres[1] = "libre";
				kartsAdultosLibres[2] = "libre";
				kartsAdultosLibres[3] = "libre";
				kartsNinosLibres[0] = "libre";
				kartsNinosLibres[1] = "libre";
				kartsNinosLibres[2] = "libre";
				kartsNinosLibres[3] = "libre";
				Sleep(1000);
				cout << "Las personas estan saliendo del circuito" << endl;
				Sleep(2000);
				system("cls");
			}
		}
	}
	
	return 0;
}

void espera(){
	for(int i = 0; i < 8; i++){
		cout << ".";
		Sleep(600);
	}
}

void generarClienteAdultos(){
	int contador = 0;
	bool asignado = false;					
	while(contador < 6){
		if(contador == 0){
			num_random = rand()%6;
			colaLlegadaAdultos[0] = adultos[num_random];
			contador++;
		}
		num_random = rand()%6;
		string persona = adultos[num_random];
		for(int i=0; i<contador; i++){
			if(colaLlegadaAdultos[i] == persona)
				asignado = true;
		}
		if(asignado == false){
			colaLlegadaAdultos[contador] = persona;
			contador++;
		}
		asignado = false;
	}
}

void generarClienteNinos(){
	int contador = 0;
	bool asignado = false;					
	while(contador < 6){
		if(contador == 0){
			num_random = rand()%6;
			colaLlegadaNino[0] = ninos[num_random];
			contador++;
		}
		num_random = rand()%6;
		string persona = ninos[num_random];
		for(int i=0; i<contador; i++){
			if(colaLlegadaNino[i] == persona)
				asignado = true;
		}
		if(asignado == false){
			colaLlegadaNino[contador] = persona;
			contador++;
		}
		asignado = false;
	}
}

void enviarSalaEsperaAdultos(string p_adulto){
	for(int i=0; i<2; i++){
		if (colaEsperaAdulto[i] == "libre"){
			colaEsperaAdulto[i] = p_adulto;
		}
	}
}

void sacarSalaEsperaAdultos(){
	for(int i=0; i<2; i++){
		colaLlegadaAdultos[i]=colaEsperaAdulto[i];
	}
	colaLlegadaAdultos[0] = "libre";
	colaLlegadaAdultos[1] = "libre";
}

void enviarSalaEsperaNinos(string p_nino){
	for(int i=0; i<2; i++){
		if (colaEsperaNino[i] == "libre"){
			colaEsperaNino[i] = p_nino;
		}
	}
}

void sacarSalaEsperaNinos(){
	for(int i=0; i<2; i++){
		colaLlegadaNino[i] = colaEsperaNino[i];
	}
	colaEsperaNino[0] = "libre";
	colaEsperaNino[1] = "libre";
}

void asignarKartAdulto(){
	Semaforo semaforo;
	for(int k=0; k<6; k++){
		int asignado = 0;
		for(int i = 0; i < 4; i++){
			if(kartsAdultosLibres[i] == "libre"){
				semaforo.semWait(colaLlegadaAdultos[k]);
				kartsAdultosLibres[i] = colaLlegadaAdultos[k];
				asignado = 1;
				cout << "A la persona " << colaLlegadaAdultos[k] << " se le asigna el kart " << kartsAdultos[i] << endl;
				break;
			}
		}
		if (asignado != 1) {
			cout << "Karts ocupado, " << colaLlegadaAdultos[k] << " se le enviara a la sala de espera" << endl;
			enviarSalaEsperaAdultos(colaLlegadaAdultos[k]);
		}
	}
	colaLlegadaAdultos[0] = "libre";
	colaLlegadaAdultos[1] = "libre";
	colaLlegadaAdultos[2] = "libre";
	colaLlegadaAdultos[3] = "libre";
	colaLlegadaAdultos[4] = "libre";
	colaLlegadaAdultos[5] = "libre";
}

void asignarKartNino(){
	Semaforo semaforo;
	for(int k=0; k<6; k++){
		int asignado = 0;
		for(int i = 0; i < 4; i++){
			if(kartsNinosLibres[i] == "libre"){
				semaforo.semWait(colaLlegadaNino[k]);
				kartsNinosLibres[i] = colaLlegadaNino[k];
				asignado = 1;
				cout << "A la persona " << colaLlegadaNino[k] << " se le asigna el kart " << kartsNinos[i] << endl;
				break;
			}
		}
		if (asignado != 1) {
			cout << "Karts ocupado, " << colaLlegadaNino[k] << " se le enviara a la sala de espera" << endl;
			enviarSalaEsperaAdultos(colaLlegadaNino[k]);
		}
	}
	colaLlegadaNino[0] = "libre";
	colaLlegadaNino[1] = "libre";
	colaLlegadaNino[2] = "libre";
	colaLlegadaNino[3] = "libre";
	colaLlegadaNino[4] = "libre";
	colaLlegadaNino[5] = "libre";
}

void verificar_kart(){
	srand(time(NULL));
	num_random = 1 + rand()%8;
	if(num_random==1){
		system("COLOR 70");
		cout<<"OcurriÛ un accidente, esperando al mecanico"<< endl;
		semaforo.wait();
		cout<<"El mecanico " << mecanico << " a revisado el kart" <<endl;
		cout<< endl;
		num_random = rand()%2;
		if(num_random == 0){
			cout<<"El kart puede continuar"<< endl;
			system("COLOR 07" );
		}else{
			cout<<"El kart necesita mantenimiento"<< endl;
			semaforo.wait();
			cout<<"TerminÛ el mantenimiento"<< endl;
			system("COLOR 07" );
		}
	}
	if(num_random==2){
		system("COLOR 70" );
		cout<<"OcurriÛ una falla mecanica en un kart, esperando al mecanico"<< endl;
		semaforo.wait();
		cout<< endl;
		cout<<"El mecanico " << mecanico << " a revisado el kart" <<endl;
		cout<<"Se ha arreglado la falla"<< endl;
	    system("COLOR 07" );
	}
	
	else if (num_random >2){
		cout<< "El circuito anda correctamente"<< endl; 
	}
}

void verificar_clima(){
	srand(time(NULL));
	num_random_clima = 1 + rand()%3;
	int duracion_tormenta_random = rand();
	if(num_random_clima==1){
		cout<<"El clima esta perfecto"<< endl;
		cout<< endl;
	}
	if(num_random_clima==2){
		system("COLOR B0" );
		cout<<"Ha comenzado a Llover! Se han parado las actividades" << endl;
		semaforo.wait();
		cout<< endl;
		srand(time(NULL));
		duracion_tormenta_random = 1 + rand()%2;
		while(duracion_tormenta_random ==2){
			cout<<"Sigue Lloviendo"<<endl;
			semaforo.wait();
			cout<<endl;
			srand(time(NULL));
			duracion_tormenta_random = 1 + rand()%2;
		}
		cout<<"Ha Dejado de llover"<<endl<<endl;
	}
	if(num_random_clima==3){
		system("COLOR B0" );
		cout<<"Ha comenzado a Nevar! Se han parado las actividades" << endl;
		semaforo.wait();
		cout<< endl;
		srand(time(NULL));
		duracion_tormenta_random = 1 + rand()%2;
		while(duracion_tormenta_random ==2){
			cout<<"Sigue Nevando"<<endl;
			semaforo.wait();
			cout<<endl;
			srand(time(NULL));
			duracion_tormenta_random = 1 + rand()%2;
		}
		cout<<"Ha Dejado de Nevar"<<endl<<endl;
	}
	system("COLOR 07" );
}

