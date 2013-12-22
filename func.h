//

struct sigaction sa;
union sigval v;

typedef struct{
	int pid;
	int num;
	long premio;
}HIJO;

//devuelve el premio en funcion del numero de aciertos
int premios(int aciertos);
//da la vuelta a un string pasado por parametro.
char* strrev(char *str);
//Recibe un numero como parametro y devuelve el numero en char*
char* int2Char2(int num);
//Devuelve el vector entero como un string CVS
char* int2Char(int *vector);
//devuelve el vector pasado como parámetro oredenado de menora a mayor
int* sortV(int *vector);
//genera el archivo snr, numero de sorteo, array de resultados y numero jugadores
int gen_Snr(int nsorteo, HIJO *hijos, int jugadores);
//devuelve el numero de aciertos de una combinación
int check_bet(char *combinacionStrCVS, int *combinacionGanadora);
//Manejador de señales
void signalHandler(int mySignal, siginfo_t *info, void *other);
//Reserva de memoria (punteros int para apuestas)
int* memoryAllocation(int jugadores);

//Lectura y escritura de un pipe
char* read_from_pipe(int *pipe);
void write_to_pipe(int **pipe, char *string, int jugadores);

//esta función genera una apuesta aleatoria
int* rand_bet();
//Mostramos una apuesta
void show_bet(int* bet);

