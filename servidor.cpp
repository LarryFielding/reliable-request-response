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
    char message[20] = {0x0};
    int a = 0, b = 0, c = 0, nbd = 0, idRecibido = 0, idEsperado = 1;

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
            memset(message, 0, sizeof(message));
     		break;
        case deposito:
        //TODO: caMBIar la logica, tambien responder si no llega:
            idRecibido = msj->requestId;
            if (idRecibido == 1)
            {
                nbd = 0;
                idEsperado = 1;
            }
            if (idEsperado == idRecibido)
            {
                cout << "Saldo actual: $" << nbd << ".00\t";
                sscanf(msj->arguments, "%d", &c);
                nbd += c;
                cout << "Nuevo saldo: $" << nbd << ".00" << endl;
                sprintf(message, "%d", nbd);
                respuesta.sendReply(message);
                idEsperado ++;
            }
            else if (idEsperado == idRecibido + 1)
            {
                cout << "Saldo actual: $" << nbd << ".00" << ". Se reenvía, no se recalcula."<< endl;
                sprintf(message, "%d", nbd);
                respuesta.sendReply(message);
            }
            memset(message, 0, sizeof(message));
            c = 0;
            break;
 		default:
 			strcpy(message, "operación no soportada\n");
     		break;
     }
     
  }
	return 0;
}
