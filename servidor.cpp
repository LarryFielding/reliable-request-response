#include "Respuesta.h"
	
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;


int main(int argc, char const *argv[])
{
    cout << "Soy servidor (cajero automático)" << endl;

    struct mensaje * msj;
    char message[20];
    int a = 0, b = 0, c = 0, nbd = 0, idRecibido = 0, idEsperado = 0;

	Respuesta respuesta = Respuesta(7200);

  while(1)
  {
     msj = respuesta.getRequest();

     // Construye una cadena con el resultado de la operación:

     switch (msj->operationId)
     {
     	case suma:
            // Obtiene números de la cadena:
            sscanf(msj->arguments, "%d %d", &a, &b);
     		sprintf(message, "%d + %d = %d", a, b, a+b);
     		break;
        case deposito:
            // Obtiene números de la cadena:
            idRecibido = msj->requestId;
            if (idRecibido == 1)
            {
                idEsperado = 0;
                nbd = 0;
            }
            sscanf(msj->arguments, "%d", &c);
            nbd += c;
            sprintf(message, "%d", nbd);
            c = 0;
            break;
 		default:
 			strcpy(message, "operación no soportada\n");
     		break;
     }

     // Condición inicial
     if (idEsperado == 0)
     {
         idEsperado = 1;
     }

     if (idEsperado == idRecibido)
     {
        respuesta.sendReply(message);
        idEsperado = idRecibido + 1;
     }
  }
    
	return 0;
}
