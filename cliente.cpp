#include "Solicitud.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <time.h>
#include <iostream>

using namespace std;


int main(int argc, char const *argv[])
{
    if (argc != 4)
    {
    	cout << "Debe ingresar: ./main_c <puerto> <IP> <num depósitos>" << endl;
    	return -1;
    }

    // Semilla para el generador de números aleatorios:
    srand(time(NULL));
    int puertoRemoto = atoi(argv[1]), n = atoi(argv[3]);
    char ipRemota[50];
    strcpy(ipRemota, argv[2]);
    
    Solicitud solicitud = Solicitud();
    cout << "Se harán " << n << " depósitos." << endl;

    int cuenta = 0;

    for (int i = 0; i < n; ++i)
    {

        int random, saldo = 0;
        random = (rand() % 8) + 1;
        string s = to_string(random);
        const char * cargs = s.c_str();

        cuenta += random;

        char * respuesta = solicitud.doOperation(ipRemota, puertoRemoto, deposito, cargs);

        if (strlen(respuesta) > 0)
        {
            //cout << "Respuesta del servidor: " << respuesta << endl;
            saldo = atoi(respuesta);
            if (saldo != cuenta)
            {
                printf("El saldo obtenido ($%d.00) es diferente a lo esperado: ($%d.00)\n", saldo, cuenta);
                exit(1);
            }
        }
        else
        {
            cout << "No se obtuvo respuesta." << endl;   
        }
        
    }

	return 0;
}
