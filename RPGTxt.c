#include <stdbool.h>

/*
Ximena Sanchez Lomeli
Jonathan Joshua Sosa Llamas
*/

/*           ~ PERSONAJES ~
Atributos: 
    Nombre
    HP
    Dano
    Attk fisico
    Attk magico
    Def magica
    Def fisica
    Magias
    Invent
*/

typedef struct {
    int HP;
    int dano;
    bool juega;
    int Attkfis;
    int Attkmag;
    int Deffis;
    int Defmag;
    int duracef; // duracef -> duracion de efecto(s)
} personaje;

/*           Mis 3 funciones de magia         */

// Perder turno 
void magiaPerderTurno(void * enemigo) { // con el void * enemigo, apunto al enemigo que quiero afectar 
    personaje * enemigoReal = (personaje *) enemigo; // como enemigo es void, uso otro de personaje para poder acceder al "menu" de datos y casteo a enemigo a personaje
    enemigoReal->juega = false; // como enemigoReal como tal tiene dentro al enemigo apuntado, estoy modificando el booleano de si juega o no el wey

}
/*
En esa de perder turno, la deje asi de momento, porque como tal, creo que tendriamos que poner tmb algo como que 
administre los turnos por fuera, incluirlo dentro haria que el false de que juegue el personaje en cuestion dure una
nadotaaaaaa
*/

// Mejora o reduccion de atributos 
void modifAtributos(void * self, void * enemigo) { // como quiero poder usar la magia sobre mi mismo o el enemigo, mejor aclarar bien a quien le dare 
    personaje * selfReal = (personaje *) self; // igualito que arriba, tengo que hacer que sea personaje 
    personaje * enemigoReal = (personaje *) enemigo;

    int elaf; // elaf por eleccion afectado jajajajj
    int elmg; // elmg por eleccion de magia 

    // seleccion de a quien afectar

    printf("A quien quieres afectar?\n");
    printf("1 -> A ti mismo\n");
    printf("2 -> Al enemigo\n");
    scanf("%d", &elaf);

    if (elaf == 1 ) { // aka que me afecte a mi mismo
        // seleccion de atributo a modificar
        printf("Que atributo quieres mejorar durante 3 turnos?\n");
        printf("1 - Ataque Fisico\n");
        printf("2 - Ataque magico\n");
        printf("3 - Defensa fisica\n");
        printf("4 - Defensa magica\n");
        scanf("%d", &elmg); // utilizo las vairables temporales para asi pasar a los casos con el switch
        // SWITCH para cuando es al SELF 
        switch (elmg)
        {
        case 1:
            selfReal->Attkfis = selfReal->Attkfis + 2; // si pusiera solo selfReal->Attkfis+2 y attkfis = 5 daria 7 pero no se guardaria, so necesito asignar 
            selfReal->duracef = 3; // aqui lo que hago es que agrego la duracion de 3 turnos
            break;
        case 2:
            selfReal->Attkmag = selfReal->Attkmag + 2;
            selfReal->duracef = 3; // ifual aca
            break;
        case 3:
            selfReal->Deffis = selfReal->Deffis + 2;
            selfReal->duracef = 3; // igual aca
            break;
        case 4:
            selfReal->Defmag = selfReal->Defmag + 2;
            selfReal->duracef = 3; // los 4 cansos 
            break;
        default:
            break;
        }
    } else if (elaf == 2 ) { // aka que afecte al enemigo
        printf("Que atributo quieres reducir durante 3 turnos?\n");
        printf("1 - Ataque Fisico\n");
        printf("2 - Ataque magico\n");
        printf("3 - Defensa fisica\n");
        printf("4 - Defensa magica\n");
        scanf("%d", &elmg);
        // SWITCH para cuando es al ENEMIGO, al que LE RESTARÉ
        switch (elmg)
        {
        case 1:
            enemigoReal->Attkfis = enemigoReal->Attkfis - 2; // asigno y cambio la variable para que se entienda que ahora vamos por tu enemigo tbh 
            enemigoReal->duracef = 3; // tmb aca asigno duracion de tiempo libre 
            break;
        case 2:
            enemigoReal->Attkmag = enemigoReal->Attkmag - 2;
            enemigoReal->duracef = 3; // same here
            break;
        case 3:
            enemigoReal->Deffis = enemigoReal->Deffis - 2;
            enemigoReal->duracef = 3; // same here
            break;
        case 4:
            enemigoReal->Defmag = enemigoReal->Defmag - 2;
            enemigoReal->duracef = 3; // same same same 
            break;
        default:
            break;
        }
    }

}

// void bolafuego(void ¨)