#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
            // accion normal
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
                } // cierre switch debuff
            }
        }

        // Enemigo
        if (enemigo->dano < enemigo->HP) {
            if (enemigo->juega == false ) {
                enemigo->juega = true; // de nuevo corrijo pero para enemigo 
                } else {
                    // accion normal
                }
                if (enemigo->duracef > 0) {
            enemigo->duracef --; // voy restando al contador de turnos que da duracion del buff o debuff 
            if (enemigo->duracef == 0) { // una vez que da las vueltas y va restando, ya cuando da 0, pasa a esto
                if (enemigo->buff == true) { // aqui determino si toca restar o sumar
                    switch (enemigo->atribmod) // recibo el atributo modificado, donde guarde cual cambió
                { // AQUI reciclé un poco del codigo anterior 
                case 1: // ya con los cases, restauro las stats a su punto anterior 
                    enemigo->Attkfis = enemigo->Attkfis - 2;
                    break;
                case 2:
                    enemigo->Attkmag = enemigo->Attkmag - 2;
                    break;
                case 3:
                    enemigo->Deffis = enemigo->Deffis - 2;
                    break;
                case 4:
                    enemigo->Defmag = enemigo->Defmag - 2; 
                    break;
                default:
                    break;
                } // llave switch si fue buff
            } else {
                    switch (enemigo->atribmod) // recibo el atributo modificado, donde guarde cual cambió
                {
                case 1: // ya con los cases, restauro las stats a su punto anterior 
                    enemigo->Attkfis = enemigo->Attkfis + 2;
                    break;
                case 2:
                    enemigo->Attkmag = enemigo->Attkmag + 2;
                    break;
                case 3:
                    enemigo->Deffis = enemigo->Deffis + 2;
                    break;
                case 4:
                    enemigo->Defmag = enemigo->Defmag + 2; 
                    break;
                default:
                    break;
                        } // llave switch si fue debuff
                    }
                } 
            }
        }
    }
}
}






/*           Mis 3 funciones de magia         */

// Perder turno 
void magiaPerderTurno(void * enemigo) { // con el void * enemigo, apunto al enemigo que quiero afectar 
    personaje * enemigoReal = (personaje *) enemigo; // como enemigo es void, uso otro de personaje para poder acceder al "menu" de datos y casteo a enemigo a personaje
    enemigoReal->juega = false; // como enemigoReal como tal tiene dentro al enemigo apuntado, estoy modificando el booleano de si juega o no el wey
    if (enemigoReal->tipo == 0) {
        printf("Chicken little levanta un amparo y hace que el enemigo pierda turno\n");
    } else {
        printf("El partido político al mando manda instrucciones de retener en el aeropuerto a Anaya y pierde su turno\n");
    }
}
/*
En esa de perder turno, la deje asi de momento, porque como tal, creo que tendriamos que poner tmb algo como que 
administre los turnos por fuera, incluirlo dentro haria que el false de que juegue el personaje en cuestion dure una
nadotaaaaaa - UPDATE -> ya quedó
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

    if (elaf == 1 ) { // aka que me afecte a mi mismo -> SELF👤
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
            selfReal->duracef = 4; // aqui lo que hago es que agrego la duracion de 3 turnos, NOTA -> use 4 porque al usar la magia se descuenta uno inmediatamente, ponerlo a 4 fue una solución facil y rapida tbh 
            selfReal->atribmod = elmg; // con esto recordare el atributo modificado
            selfReal->buff = true;
            if (selfReal->tipo == 0) {
                printf("Richy entrenó gym la semana pasada y ahora pega más fuerte durante 3 turnos! (+2 ataque físico)\n");
            } else {
                printf("%s completó una gira de campaña cargando bebes, lonas y cajas de despensa, lo que l@ hace pegar más fuerte! (+2 ataque físico)\n", selfReal->nombre);
            }
            break;
        case 2:
            selfReal->Attkmag = selfReal->Attkmag + 2;
            selfReal->duracef = 4; // igual aca
            selfReal->atribmod = elmg; // same 
            selfReal->buff = true;
            if (selfReal->tipo == 0) {
                printf("Richy reune maná y ahora su magia es más fuerte durante 3 turnos! (+2 ataque mágico)\n");
            } else {
                printf("%s empieza a citar encuestas que nadie sabe de dónde salieron y su poder mágico aumenta! (+2 ataque mágico)\n", selfReal->nombre);
            }
            break;
        case 3:
            selfReal->Deffis = selfReal->Deffis + 2;
            selfReal->duracef = 4; // igual aca
            selfReal->atribmod = elmg;
            selfReal->buff = true;
            if (selfReal->tipo == 0) {
                printf("Richy se pone su chaleco de campaña y ahora aguanta más vara durante 3 turnos! (+2 defensa física)\n");
            } else {
                printf("%s se pone chaleco antibalas de campaña y ahora está blindado durante 3 turnos! (+2 defensa física)\n", selfReal->nombre);
            }
            break;
        case 4:
            selfReal->Defmag = selfReal->Defmag + 2;
            selfReal->duracef = 4; // los 4 casos 
            selfReal->atribmod = elmg;
            selfReal->buff = true;
            if (selfReal->tipo == 0) {
                printf("Richy publica un video de 14 minutos defendiéndose de las acusaciones y obtiene mayor defensa mágica por 3 turnos! (+2 defensa mágica)\n");
            } else {
                printf("%s lanza un comunicado de 12 cuartillas negándolo absolutamente todo y obtiene +2 defensa magica durante 3 turnos! (+2 defensa mágica)\n", selfReal->nombre);
            }
            break;
        default:
            break;
        }
    } else if (elaf == 2 ) { // aka que afecte al enemigo -> ENEMIGO👹
        printf("Que atributo quieres reducir durante 3 turnos?\n");
        printf("1 - Ataque Fisico\n");
        printf("2 - Ataque magico\n");
        printf("3 - Defensa fisica\n");
        printf("4 - Defensa magica\n");
        scanf("%d", &elmg);
        // SWITCH para cuando es al ENEMIGO, al que LE RESTARÉ, el DEBUFF
        switch (elmg)
        {
        case 1:
            enemigoReal->Attkfis = enemigoReal->Attkfis - 2; // asigno y cambio la variable para que se entienda que ahora vamos por tu enemigo tbh 
            enemigoReal->duracef = 3; // tmb aca asigno duracion de tiempo libre 
            enemigoReal->atribmod = elmg;
            enemigoReal->buff = false;
             if (selfReal->tipo == 0) {
                 printf("Richy acusa a %s en cadena nacional y ahora le tiembla la mano durante 3 turnos! (-2 ataque físico)\n", enemigoReal->nombre);
                } else {
                printf("%s filtra una investigación en contra de Richy y le entra miedo político durante 3 turnos! (-2 ataque físico)\n", selfReal->nombre);
            }
            break;
        case 2:
            enemigoReal->Attkmag = enemigoReal->Attkmag - 2;
            enemigoReal->duracef = 3; // same here
            enemigoReal->atribmod = elmg;
            enemigoReal->buff = false;
            if (selfReal->tipo == 0) {
                printf("Richy le tumba el discurso a %s con datos el INEGI y l@ hace perder poder mágico durante 3 turnos! (-2 ataque mágico)\n", enemigoReal->nombre);
            } else {
                printf("%s saca una encuesta donde Richy sale con 2 por ciento de intención de voto, su magia se debilita 3 turnos! (-2 ataque mágico)\n", selfReal->nombre);
            }
            break;
        case 3:
            enemigoReal->Deffis = enemigoReal->Deffis - 2;
            enemigoReal->duracef = 3; // same here
            enemigoReal->atribmod = elmg;
            enemigoReal->buff = false;
            if (selfReal->tipo == 0) {
                printf("Richy encuentra una irregularidad en la declaración patrimonial de %s y lo deja expuesto durante 3 turnos! (-2 defensa fisica)\n", enemigoReal->nombre);
            } else {
                printf("%s manda a quitarle el equipo de campaña a Richy y lo deja sin protección durante 3 turnos! (-2 defensa fisica)\n", selfReal->nombre);
            }
            break;
        case 4:
            enemigoReal->Defmag = enemigoReal->Defmag - 2;
            enemigoReal->duracef = 3; // same same same 
            enemigoReal->atribmod = elmg;
            enemigoReal->buff = false;
            if (selfReal->tipo == 0) {
                printf("Richy saca una presentación de PowerPoint con 83 diapositivas y destruye la narrativa de %s! (-2 defensa magica durante 3 turnos)\n", enemigoReal->nombre);
            } else {
                printf("%s presenta 46 capturas de pantalla fuera de contexto y destruye temporalmente la narrativa de Richy! (-2 defensa magica durante 3 turnos)\n", selfReal->nombre);
            }
            break;
        default:
            break;
        }
    }

}

// void bolafuego(void ¨)
void bolafuego(void * objetivo, void * emisor) { // necesito atacante y atacado
    int danof = 0;

    personaje * objReal = (personaje *) objetivo; // es decir, quien recibirá el ataque
    personaje * emiReal = (personaje *) emisor; // y quien tirará el ataque 
    danof = emiReal->Attkmag - (objReal->Defmag); // el daño por fuego lo calculo a partir del ataque magico del emisor - la defensa magica de quien lo recibe 

    if (objReal->Defmag > emiReal->Attkmag || objReal->Defmag == emiReal->Attkmag) {
        objReal->dano ++;
    } else {
        objReal->dano = objReal->dano + danof;
    }
}


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
