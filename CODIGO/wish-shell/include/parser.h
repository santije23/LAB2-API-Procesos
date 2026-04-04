/* Estas líneas evitan que el archivo se lea dos veces, lo que causaría errores */
#ifndef PARSER_H
#define PARSER_H

/* Definimos una "Estructura": una caja que guarda toda la info de un comando */
typedef struct {
    char *command;       /* Nombre del programa (ej: "ls") */
    char **args;         /* Lista de palabras/argumentos (ej: "-l", "/home") */
    int background;      /* Vale 1 si el usuario puso '&' (ejecutar en paralelo), sino 0 */
    char *redirect_file; /* Nombre del archivo si se usa '>' (ej: "salida.txt"), sino NULL */
} Command;

/* Esta es la "promesa" de una función:
   Recibe: una frase (la línea que escribió el usuario)
   Devuelve: la estructura 'Command' con todo separado y organizado */
Command parse_input(char *line);

#endif