#include <iostream>
#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <Windows.h>
#include "Semaforo.h"
#include <string>
#include <stdlib.h> 

using namespace std;

void Semaforo::semWait(string trabajo){
	if(trabajo != ""){
		Sleep(200);
	}	
}

void Semaforo::wait(){
	for(int i = 0; i < 8; i++){
		cout << ".";
		Sleep(1000);
	}
}
