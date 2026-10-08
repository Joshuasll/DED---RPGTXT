#include <stdbool.h>
#include <stdio.h>

/*
Ximena Sanchez Lomeli
Jonathan Joshua Sosa Llamas
*/

typedef struct {
    char nombre[30]; // puse de tamaño 30 solo por si acaso 
    int HP;
    int dano;
    bool juega;
    int Attkfis;
    int Attkmag;
    int Deffis;
    int Defmag;
    int tipo; //para saber si es humano o villano       0 -> 👤 humano  1 -> 👹 enemigo
    int escudo; //para mi funcion
    int duracef; // duracef -> duracion de efecto(s)
    int atribmod; // para guardar el atributo modificado y reconocer cual es
    bool buff; // fue mejora o disminucion? es decir true -> +2 o false -> -2 para el aumento o disminucion de atributos aka para poder recordar que hacerle tras los 3 turnos 
} personaje;

/*           Motor de turnos                
    ya lo necesitaba para lo de la reduccion de atributos y asi, si no estaba medio matado solo hacerlo al aire     */
void motordeTurnos (personaje * jugador, personaje * enemigo) { // aqui necesito que los turnos controlen a los 2 
    while ((jugador->dano < jugador->HP) && (enemigo->dano < enemigo->HP)) { // esta linea la pongo porque en realidad necesito que hayan turnos mientras la batalla siga aka que sigan vivos los dos 
        // Humano
        if (jugador->juega == false ) { // reviso si pierde turno o no
            jugador->juega = true; // corrijo y dejo listo para la siguiente tirada 
        } else {

        }
        // por si hay buff o debuff - humano
        if (jugador->duracef > 0) {
            jugador->duracef --; // voy restando al contador de turnos que da duracion del buff o debuff 
            if (jugador->duracef == 0) { // una vez que da las vueltas y va restando, ya cuando da 0, pasa a esto
                if (jugador->buff == true) { // aqui determino si toca restar o sumar
                    switch (jugador->atribmod) // recibo el atributo modificado, donde guarde cual cambió
                {
                case 1: // ya con los cases, restauro las stats a su punto anterior 
                    jugador->Attkfis = jugador->Attkfis - 2;
                    break;
                case 2:
                    jugador->Attkmag = jugador->Attkmag - 2;
                    break;
                case 3:
                    jugador->Deffis = jugador->Deffis - 2;
                    break;
                case 4:
                    jugador->Defmag = jugador->Defmag - 2; 
                    break;
                default:
                    break;
                } // llave switch si fue buff
            } else {
                    switch (jugador->atribmod) // recibo el atributo modificado, donde guarde cual cambió
                {
                case 1: // ya con los cases, restauro las stats a su punto anterior 
                    jugador->Attkfis = jugador->Attkfis + 2;
                    break;
                case 2:
                    jugador->Attkmag = jugador->Attkmag + 2;
                    break;
                case 3:
                    jugador->Deffis = jugador->Deffis + 2;
                    break;
                case 4:
                    jugador->Defmag = jugador->Defmag + 2; 
                    break;
                default:
                    break;
                } // llave switch si fue debuff
            }
        }

        // Enemigo
        if (enemigo->dano < enemigo->HP) {
            if (enemigo->juega == false ) {
                enemigo->juega = true; // de nuevo corrijo pero para enemigo 
                } else {

            }
        }
    } 
}


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
            selfReal->atribmod = elmg; // con esto recordare el atributo modificado
            selfReal->buff = true;
            break;
        case 2:
            selfReal->Attkmag = selfReal->Attkmag + 2;
            selfReal->duracef = 3; // igual aca
            selfReal->atribmod = elmg; // same 
            selfReal->buff = true;
            break;
        case 3:
            selfReal->Deffis = selfReal->Deffis + 2;
            selfReal->duracef = 3; // igual aca
            selfReal->atribmod = elmg;
            selfReal->buff = true;
            break;
        case 4:
            selfReal->Defmag = selfReal->Defmag + 2;
            selfReal->duracef = 3; // los 4 casos 
            selfReal->atribmod = elmg;
            selfReal->buff = true;
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
            enemigoReal->atribmod = elmg;
            enemigoReal->buff = false;
            break;
        case 2:
            enemigoReal->Attkmag = enemigoReal->Attkmag - 2;
            enemigoReal->duracef = 3; // same here
            enemigoReal->atribmod = elmg;
            enemigoReal->buff = false;
            break;
        case 3:
            enemigoReal->Deffis = enemigoReal->Deffis - 2;
            enemigoReal->duracef = 3; // same here
            enemigoReal->atribmod = elmg;
            enemigoReal->buff = false;
            break;
        case 4:
            enemigoReal->Defmag = enemigoReal->Defmag - 2;
            enemigoReal->duracef = 3; // same same same 
            enemigoReal->atribmod = elmg;
            enemigoReal->buff = false;
            break;
        default:
            break;
        }
    }

}

// void bolafuego(void ¨)


//funciones de ximena

//para generar un escudo
void add_escudo(void *self){
    personaje *usuario = (personaje*)self;
    usuario->escudo ++ ;
    if(usuario->tipo==0){
        printf("Expones el ataque presidencial en los medios, ahora todo el mundo lo sabe!\n");
        printf("conseguiste +1 escudo, puedes bloquear el proximo ataque\n");
    }
    else {
        printf("El presidente inicio una cortina de humo, oculta la informacion de los medios\n");
        printf("consiguio +1 escudo, ahora puede bloquear tu proximo ataque !!\n");
    }
}

//para usar el escudo
int usar_escudo(personaje *defensor){
    if(defensor->escudo == 0){
        return 0;
    }
    if(defensor->tipo == 0){
        int eleccion;

        printf("Tienes %d escudos, quieres bloquear un ataque?\n", defensor->escudo);
        printf("1. si\n 2. no");
        scanf("%d", &eleccion);

            if(eleccion == 1){
                defensor->escudo --;
                printf("El ataque se ha bloqueaado\n");
                printf("te quedan %d escudos\n", defensor->escudo);
                return 1;
            }
        }

    else{
        defensor->escudo --;
        printf("El presidente ha bloqueado tu ataque, te ha podido silenciar\n");
        printf("le quedan %d escudos\n", defensor->escudo);
        return 1;
    }
return 0;
}

// si vas a hacer una funcion de ataque agrega este if al inicio de tu funcion para q pueda usar el escudo pls


/*  este merito ⬇
if(usar_escudo(//nombre del q atacaras)){
    return;
}*/

/*
[0] -> nuestro personaje
[1] -> enemigo facil
[2] -> enemigo intermedio 
[3] -> enemigo dificil
[4] -> jefe final
*/

// orden de datos para personajes : nombre -> hp -> dano -> juega -> attkfis -> attkmag -> deffis -> defmag -> tipo -> escudo -> duracef -> atribmod -> buff 
int main( ) {
    personaje personajess[5] = {
        {"Richy Anaya", 100, 0, true, 15, 14, 5, 4, 0, 0, 0, 0, false}, // jugador
        {"Lemus", 75, 0, true, 12, 10, 3, 3, 1, 0, 0, 0, false}, // easy
        {"AMLO", 90, 0, true, 16, 14, 5, 4, 1, 0, 0, 0, false}, // medium
        {"ShameBee", 110, 0, true, 19, 18, 7, 6, 1, 0, 0, 0, false}, // hard 
        {"Trump", 140, 0, true, 23, 21, 9, 8, 1, 0, 0, 0, false} // final boss 
    };
    return 0;
}
