#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
Ximena Sanchez Lomeli
Jonathan Joshua Sosa Llamas
*/

typedef struct{
    char nombre[30];
    int atributo;
    int poder;
}objeto;

typedef struct {
    char nombre[30]; // puse de tamaño 30 solo por si acaso 
    int HP;
    int dano;
    bool juega;
    int Attkfis;
    int Attkmag;
    int Deffis;
    int Defmag;
    int tipo; //para saber si es humano o villano       
    int escudo; //para mi funcion
    int duracef; // duracef -> duracion de efecto(s)
    int atribmod; // para guardar el atributo modificado y reconocer cual es
    bool buff; // fue mejora o disminucion? es decir true -> +2 o false -> -2 para el aumento o disminucion de atributos aka para poder recordar que hacerle tras los 3 turnos 
    int jerez;
    bool evacion;
    objeto *inventario[5];
    void (*magias [3])(void *, void *); // aqui como tal uso lo que puso el profe, que sea un arreglo a punteros a funcion las magias y que solo se pueden 3 
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




/*           Mis 3 funciones de magia         */

// Perder turno 
void magiaPerderTurno(void * enemigo, void * emisor) { // con el void * enemigo, apunto al enemigo que quiero afectar 
    personaje * enemigoReal = (personaje *) enemigo; // como enemigo es void, uso otro de personaje para poder acceder al "menu" de datos y casteo a enemigo a personaje
    personaje * emisorReal = (personaje *) emisor;
    if (comprb_evadir(enemigoReal) == true) { // aqui pues como evadir funciona para todo, de una vez lo agregué a mi magia
        printf("%s lo evadio y no pasó nada!\n", enemigoReal->nombre);
        return;
    }
    if(enemigoReal->Defmag > emisorReal->Attkmag) { // aqui comparo tambien usando la regla del profe, si la def magica del enemigo es mayor al ataque, pues nachos
        printf("La magia no sirvió\n");
        return; // aqui corto a nivel funcion 
    }
    enemigoReal->juega = false; // como enemigoReal como tal tiene dentro al enemigo apuntado, estoy modificando el booleano de si juega o no el wey
    if (enemigoReal->tipo == 0) {
        printf("El partido político al mando manda instrucciones de retener en el aeropuerto a Anaya y pierde su turno\n");
    } else {
        printf("Richy little levanta un amparo y hace que el enemigo pierda turno\n");
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
    
    // seleccion de a quien afectar -> peero esto solo funciona para el humano, para nosotros
    
    // adición para la cpu
    /* rand() genera un numero aleatorio, normalmente sale uno grande 
       para limitar su rango -> rand() % [numero]
       peero
       si quiero que o¿por ejemplo se pueda solo 1 y 2 como abajo
       rand() % 2+1 <- es lo ideal 
    */
    // control si es humano o cpu 
    if (selfReal->tipo == 0) {
        printf("A quien quieres afectar?\n");
        printf("1 -> A ti mismo\n");
        printf("2 -> Al enemigo\n");
        scanf("%d", &elaf);
    } else {
        elaf = rand() % 2+1; // esto para que abarque hasta el 2 
    }
    
    
    if (elaf == 1 ) { // aka que me afecte a mi mismo -> SELF👤
        // seleccion de atributo a modificar
        // control si es humano o cpu
        if (selfReal->tipo == 0) {
            printf("Que atributo quieres mejorar durante 3 turnos?\n");
            printf("1 - Ataque Fisico\n");
            printf("2 - Ataque magico\n");
            printf("3 - Defensa fisica\n");
            printf("4 - Defensa magica\n");
            scanf("%d", &elmg); // utilizo las vairables temporales para asi pasar a los casos con el switch
            } else {
                elmg = rand() % 4+1;
            }

        // SWITCH para cuando es al SELF 
        switch (elmg)
        {
            case 1:
            selfReal->Attkfis = selfReal->Attkfis + 2; // si pusiera solo selfReal->Attkfis+2 y attkfis = 5 daria 7 pero no se guardaria, so necesito asignar 
            selfReal->duracef = 4; // aqui lo que hago es que agrego la duracion de 3 turnos, NOTA -> use 4 porque al usar la magia se descuenta uno inmediatamente, ponerlo a 4 fue una solución facil y rapida tbh 
            selfReal->atribmod = elmg; // con esto recordare el atributo modificado para despues regresarlo a la normalidad 
            selfReal->buff = true;
            if (selfReal->tipo == 0) {
                printf("Richy entrenó gym la semana pasada y ahora pega más fuerte durante 3 turnos! (+2 ataque físico)\n");
            } else {
                printf("%s completó una gira de campaña cargando bebes, lonas y cajas de despensa, lo que l@ hace pegar más fuerte! (+2 ataque físico)\n", selfReal->nombre);
            }
            break;
            case 2:
            selfReal->Attkmag = selfReal->Attkmag + 2; // buff
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
            selfReal->Deffis = selfReal->Deffis + 2; // buff
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
            selfReal->Defmag = selfReal->Defmag + 2; // buff
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
        if (comprb_evadir(enemigoReal) == true) { // aqui tambien toco implementar o incluir el que primero cheque si evadieron o no, porque pues ayudará a quien lo use a librar muchas cosas
            printf("%s evadio exitosamente el intento de ataque mágico! \n", enemigoReal->nombre);
            return; // es como la TERCERA vez que lo olvido, el return aqui como tal lo que hace es que corta funcion porque 
            /*  break -> salir de un ciclo for, while o switch
                return -> saca de una funcion completa
            */
        }

         if (enemigoReal->Defmag > selfReal->Attkmag){ // como en el documento dice que si la defensa magica es mayor no surte efecto, ues toca comparar primero
            printf("La magia no surtió efecto! \n"); // simplemente inform
            return; // cortan,
        }

        // control si es humano o cpu
        if (selfReal->tipo == 0) {
            printf("Que atributo quieres reducir durante 3 turnos?\n");
            printf("1 - Ataque Fisico\n");
            printf("2 - Ataque magico\n");
            printf("3 - Defensa fisica\n");
            printf("4 - Defensa magica\n");
            scanf("%d", &elmg);
        } else {
            elmg = rand() %4+1;
        }
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

    // comprobacion para evadir/evasion
    if (comprb_evadir(objReal) == true) { // utilizo de una vez el comprobar evadir con el objetivo, pues es quien recibira el quemazon en cuestion
        printf("%s evadió exitosamente el ataque!\n", objReal->nombre);
        return;
    }

    if (objReal->Defmag > emiReal->Attkmag) { // aqui como tal solo hago la comprobacion de daño porque si la defensa era mayor, no hace nada
        objReal->dano = objReal->dano + 0;
        printf("La magia falló\n");
    } else {
        objReal->dano = objReal->dano + danof;
        printf("%s presenta una denuncia termonuclear y quema a %s por %d de daño (le prendió fuego a un expediente y se lo aventó a %s)\n", emiReal->nombre, objReal->nombre, danof, objReal->nombre);
    }
}


//funciones de ximena

// MAGIA
//para generar un escudo
void add_escudo(void *self, void *enemigo){ // aqui aunque no usemos enemigo, le puse el void * enemigo para que como tal lleve la misma firma y las pueda meter sin lios a puntero y arreglo de las magias o com sea 
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
}
if(botellita_de_jerez(defensor, atacante, danyo_caus)){
return;
}*/

// MAGIA
//generar un reverzazo
void add_revezazo(void *self, void * enemigo){ // igual aca, necesito que las 5 magias lleven firma igual para que jalen bien todas al agregarlas 
    personaje *usuario= (personaje*)self;
    usuario->jerez ++;
    if(usuario->tipo==0){
        printf("");
        printf("conseguiste +1 reverzazo\n"); 
    }
    else{
        printf("");
        printf("consiguio +1 reverzazo");
    }
}

//utilizar el reverzazo
int botellita_de_jerez(personaje *defensor, personaje *atacante, int dano){
    if(defensor->jerez == 0){
        return 0;
    }
    if(defensor->tipo == 0){
        int eleccion;
        
        printf("Tienes %d reverzazos, quieres usar uno?\n", defensor->jerez);
        printf("1. si\n 2. no");
        scanf("%d", &eleccion);

        if(eleccion==1){
            defensor->jerez --;
            int dano_ref= dano/2;
            atacante->dano += dano_ref;
            printf("botellita de jerez todo lo que digas sera al revez\n");
            printf("lograste bloquear su ataque, y le devolviste %d de daño\n", dano_ref);
            return 1;
        }}
        else{ 
            defensor->jerez --;
            int dano_ref= dano/2;
            atacante->dano += dano_ref;
            printf("botellita de jerez todo lo que digas sera al revez\n");
            printf("El presidente ha bloqueado tu ataque, y te devolvio %d de daño\n", dano_ref);
            return 1;
        }
    return 0;
}

//funcion de evadir como en la presentacion dice la presentacion
// tmb subi estas aca arriba porque como tal con ataque fisico debes checar si evadio o no, asi que ocupaba tener esto arriba para que ataquefisico que esta abajo lo agarrara
void evadir(personaje *usuario) {
    usuario->evacion = true;
    printf("%s intento evadir el proximo ataque\n", usuario->nombre);
}
int comprb_evadir(personaje *usuario){ // ximena, cambie la funcion a int porque al ser void y regresar numero me marcaba error por todas partes y me andaba haciendo bolas JAJAJAJJA
    if(usuario->evacion == false){
        return 0;
    }
    usuario->evacion = false;
    if(rand()%2 == 0){
        printf("esquivaste la bala\n");
        return 1;
    }
    else{
        printf("igual te dio, pelaste\n");
        return 0;
    }
}

void ataque_fisico(personaje *atacante, personaje *defensor){
    int danyo_caus;
    danyo_caus= atacante->Attkfis - defensor->Deffis;
    if(danyo_caus <= 0){
        danyo_caus=0;
        printf("no le atinan al golpe, les falta calle\n"); 
    } else {
    if (comprb_evadir(defensor)) {
    return;
    } else {
    if(usar_escudo(defensor)){
    return;
    }
    if(botellita_de_jerez(defensor, atacante, danyo_caus)){
    return;
    }
    defensor->dano += danyo_caus;

    printf("%s le metio un madrazo a %s\n", atacante->nombre, defensor->nombre);
    printf("ahora %s tiene %d de daño, ¡aguas!\n", defensor->nombre, defensor->dano);
        }
    }
}



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
        {"AMLOVE", 90, 0, true, 16, 14, 5, 4, 1, 0, 0, 0, false}, // medium
        {"ShameBee", 110, 0, true, 19, 18, 7, 6, 1, 0, 0, 0, false}, // hard 
        {"Trump", 140, 0, true, 23, 21, 9, 8, 1, 0, 0, 0, false} // final boss 
    };

    printf("|=========================================|\n");
    printf("|                                         |\n");
    printf("|             Obrador Souls               |\n");
    printf("|        Amparos, madrazos y magia        |\n");
    printf("|                                         |\n");
    printf("|=========================================|\n");
    printf("|                                         |\n");
    printf("|            1. Iniciar juego             |\n");
    printf("|            2. Salir                     |\n");
    printf("|                                         |\n");
    printf("|=========================================|\n");
    int start; // aqui use este para el start o salida como variable local de main
    scanf("%d", &start); // scanf simple
    personaje * jugador = personajess; // apuntador de tipo personaje, llamado jugador al arreglo de arriba de personajess, con el usare mucha aritmetica de punteros 

    if (start == 1) {
        // continuo juego, empiezo por dar nombre a mi jugador/personaje creado
        printf("¿Cuál será el nombre de tu guerrero? Ingresalo y presiona ENTER\n");
        scanf(" %29[^\n]", jugador->nombre); // con el 29 me aseguro que no se pase de char's, aka que no se pasen de rosca con el nombre pero eso no me deja poner nombres con espacio - UPDATE, ya quedo, ya acepta espacios 
        printf("Nombre guardado.\n");

        // eleccion de magias

        printf("Tu personaje necesitará más que solo sus manos para ganar estas elecciones, elige 3 de las siguientes 5 magias\n");
        printf("Ingresa el número y luego enter, uno por uno*\n");
        printf("\n");
        for (int i = 0; i < 3; i++) { // ciclo para ir integrando las magias al arreglo de punteros a funcion de magias en vez de imprimir 3 veces o montones de veces todo el menu
            int pickmagia; // mejor que por iteracion esta variable se vaya reiniciando, creo que funciona 
            printf("1. Perder turno -> Hacer que tu oponente pierda su turno siguiente\n");
            printf("2. Modificación de atributos -> Generar un buff a ti o un debuff a la oposición\n");
            printf("3. Bola de fuego -> Bola de fuego que dará quemazón a tu rival \n");
            printf("4. Escudo -> \n"); 
            printf("5. Reversazo -> \n");
            scanf("%d", &pickmagia); // tomo cual fue la eleccion del jugador y justo con un switch ire metiendo la eleccion a cada una de las 3 posiciones

            switch (pickmagia) // el switch
            {
            case 1:
                *(jugador->magias + i) = magiaPerderTurno; // asignación a partir de desreferenciar el apuntador jugador, que manda llamar las magias y la aritmetica de posiciones usando i 
                break;
            case 2:
                *(jugador->magias + i) = modifAtributos;
                break;
            case 3:
                *(jugador->magias + i) = bolafuego;
                break;
            case 4:
                *(jugador->magias + i) = add_escudo;
                break;
            case 5:
                *(jugador->magias + i) = add_revezazo;
                break;
            default:
                printf("Opción inválida, utiliza un número dentro de las opciones disponibles\n");
                i--;
                break;
            } // llaves -> FIN SWITCH
        } // llaves -> FIN FOR 

        
    } /* llaves fin del if START */ else if (start == 2) {
        return 0;
    }

    return 0;
}


/*                                   ~ NOTAS DE GOOGLEADAS ~          
|   - " " en un scanf hace que e ignore cualquier espacio o ENTER que haya quedado pendiente de otros scanf                                     |
|   - [^\n] -> lee todo mientras no haya un salto de línea, aka lee aunque hayan espacios (este lo ocupé para hacer que el scanf del nombre del |
|     jugador funcionara con espacios)                                                                                                          |
|   - %s como tal lee solo una palabra                                                                                                          |
|   - %[^\n] -> lee hasta que haya un ENTER, acepta espacios -> para que funcione con el scanf del nombre, le necesito agregar el espacio al    |
|     inicio
|
|
|
|*/
