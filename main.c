//main.c
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

int 	signalCounter=0;

int main(int argc, char const *argv[])
{
	pid_t	pid, wpid;
	int		*apuestaHijo;
	int		*combinacionGanadora;
	int 	**myPipe;
	HIJO 	*hijos;
	int 	buffer;
	int 	i=1, j;
	int 	cont=0;
	
	int 	fatherOn=0;
	union 	sigval v;


	sa.sa_sigaction = signalHandler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGRTMIN, &sa, NULL);

	//Reservamos el array de hijos
	hijos=(HIJO*)malloc(atoi(argv[2])*sizeof(HIJO));


	//reservamos memorria
	myPipe=(int**)malloc(atoi(argv[2])*sizeof(int*));
	for(i=0;i<atoi(argv[2]);i++)
		myPipe[i]=(int*)malloc(2*sizeof(int));
	//creamos las pipes
	for(i=0;i<atoi(argv[2]);i++)
		pipe(myPipe[i]);

	if (argc == 3)
	{	
		
		for(i=0;i<atoi(argv[2]);i++){
			
			pid =fork();
			if(pid == 0){
				//hijo
				//printf("Soy hijo: %d--%d\n", getppid(), getpid());
				int 	betCounter, j;

				close(myPipe[i][1]);
				//printf("\t[%d:%d/%d]PPID:%d PID:%d-->", atoi(argv[1]), i, atoi(argv[2]), getppid(), getpid());
				apuestaHijo=rand_bet();
				//show_bet(apuestaHijo);



				
				//printf("Envio señal SIGRTMIN \n");
				v.sival_int=getpid();
				sigqueue(getppid(), SIGRTMIN, v);

				betCounter=check_bet(read_from_pipe(myPipe[i]), apuestaHijo);
				//printf("Aciertos [%d]: %d\n", i, betCounter);
				/*close(myPipe[i][0]);
				write(myPipe[i][1], int2Char2(pid), sizeof(pid));
				close(myPipe[i][1]);
				*/

 				
				
				exit(betCounter);
				
			}
			else if(pid < 0){
				//error
				printf("Error en el fork\n");
			}
			else{
				hijos[i].pid=pid;
				hijos[i].num=i;
			}

		}

				
				
	}
	else{
		printf("Número de parámetros inválido\n");		
	}
			
			//bloqueo
				while(signalCounter < atoi(argv[2])){
					pause();
				}
	 
				combinacionGanadora=rand_bet();
				//printf("-----------------\n");
				//printf("\tPID:%d-|%d-> ", getpid(), i);
				//show_bet(combinacionGanadora);
				//printf("-----------------\n");
				write_to_pipe(myPipe, int2Char(combinacionGanadora), atoi(argv[2]));
				


				int *resultados, h=0, g=0;
				resultados=(int*)malloc(atoi(argv[2])*sizeof(int));
				while((wpid = wait(&cont)) >=0){
					for(h=0;h<atoi(argv[2]);h++){
						if(hijos[h].num == g){
							hijos[g].premio=(long)premios(cont/256);
							//te devuelve el numero en multiplo de 256
							//printf("%d-> %d [%d]\n ", (int)wpid, cont/256, g);
							cont=0;
						}
					}
					g++;
				}

				gen_Snr(atoi(argv[1]), hijos, atoi(argv[2]));

	return 0;
}