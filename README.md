# reliable-request-response
Implementa el protocolo petición-respuesta sobre UDP con timeout de manera confiable.

Para compilar:

```make```

Para ejecutar el servidor:

```./servidor```

Para ejecutar el cliente (**Ejercicio 1**):

```time ./cliente <puerto> <IP> <número de depósitos>```

### Ejercicio 1

El tamaño del mensaje se estableció a 64K que es el máximo para un paquete UDP. Se probó con 300 000 depósitos y no se encontró disordancia.

Pueden comentarse o descomentarse las impresiones de los requestId que llegan del cliente en el método `getRequest` de `Respuesta.cpp`.
