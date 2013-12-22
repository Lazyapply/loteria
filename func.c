//
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//si ponemos aqui tambien la cabecera se evitan problemas
//a la hora de la precedencia en el preprocesador
#include "func.h"

extern int 	signalCounter;


int premios(int aciertos){
	int a;

	switch(aciertos){

			case 3:
				a=10;
			break;

			case 4:
				a=50;
			break;

			case 5:
				a=500;
			break;

			case 6:
				a=10000;
			break;

			default:
				a=0;
			break;

		}
		return a;
}


int gen_Snr(int nsorteo, HIJO *hijos, int jugadores){
	int i;
	//int *d=(int*)malloc(jugadores * sizeof(int));
	char nombre[5];
	FILE *f;

	sprintf(nombre, "%s%i%s", "S", nsorteo, "R");
	//printf("Nombre->%s", nombre);
	f=fopen(nombre, "w");

	if(f==NULL)
		return 0;


	fputs("#Sorteo ", f);
	fputs(int2Char2(nsorteo), f);
	fputs("\n", f);

	for(i=0;i<jugadores;i++){

		
		//escribimos
		fputs(int2Char2(hijos[i].premio), f);
		fputs("\n", f);

	}
	fclose(f);
	return 1;
}



char* strrev(char *str){
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}

char* int2Char2(int num){
	char *cad;
	int nDigitos=1, aux=num, i;

	while(aux/10!=0){
		aux=aux/10;
		nDigitos++;
	}
	
	cad=(char*)malloc(nDigitos*sizeof(char));
	for(i=0;i<nDigitos;i++){
		cad[i]=(num%10)+'0';
		num=num/10;
	}
	//cad[j]=vector[i]+'0';

	return strrev(cad);

}

char* int2Char(int *vector){
	char *cad=(char*)malloc(27*sizeof(char));
	int i, j=0;
	for(i=0;i<6;i++){
		//2 digitos
		if(vector[i]/10==1){
			cad[j]=(vector[i]/10)+'0';
			cad[j+1]=(vector[i]%10)+'0';
			j++;
		}
		else
			cad[j]=vector[i]+'0';


		j++;
		cad[j]=',';
		j++;
	}

	return cad;

}


int check_bet(char *combinacionStrCVS, int *combinacionGanadora){
	int i=0, aciertos=0;
	char *aux;

	aux= strtok(combinacionStrCVS, ",");
	while(aux !=NULL){
		for(i=0;i<6;i++){
			if(combinacionGanadora[i] == atoi(aux)){
				aciertos++;
				i++;
			}

		}
		aux=strtok(NULL, ",");
	}
	return aciertos;
}


void signalHandler(int mySignal, siginfo_t *info, void *other){
	char *src;
	//printf("Manejador: SENAL RECIBIDA\n");
	switch(info->si_code){
		case SI_QUEUE: 
			src = "sigqueue";
			if(mySignal==SIGRTMIN)
				signalCounter++;
		break;

		case SI_TIMER:
			src = "timer";
		break;

		case SI_ASYNCIO: 
			src = "asyncio";
		break;

		case SI_MESGQ:
			src = "msg queue";
		break;
		
		default:
			src = "unknown!";
		break;
	}
	//printf("Signal= %d Source= %s data= %d\n", mySignal, src, info->si_value.sival_int);
}

int* memoryAllocation(int jugadores){

	//Reservo memoria para una combinación
	int *A;
	A=  (int*)malloc(jugadores * sizeof(int));
	return A;
}

char* read_from_pipe(int *pipe){
	char *cad=(char*)malloc(17*sizeof(char));
	
	close(pipe[1]);
	read(pipe[0], cad, 17);
	close(pipe[0]);

	return cad;
}

void write_to_pipe(int **pipe, char *string, int jugadores){
	
	int i;

	for(i=0;i<jugadores;i++){
		close(pipe[i][0]);
		write(pipe[i][1], string, strlen(string));
		close(pipe[i][1]);
	}
	
}

int* sortV(int *vector){
	int i, j;
    int aux;

    for (i=0;i<6;i++) {
        aux = vector[i];
        for (j = i; j > 0 && aux < vector[j - 1]; j--) {
            vector[j] = vector[j - 1];
        }
        vector[j] = aux;
    }
    return vector;
}

int* rand_bet(){
	//necesario para no propagar la misma semilla en random()
	srand(getpid()+12345678);
	
	int *bet = memoryAllocation(5);
	int num, i, j, d=0;

	for(i=0; i<6; i++){

		num = random()%(1-16) +1;
		for(j=0;j<=i;j++){
			if(num == bet[j]){
				d=1;
				break;
			}
		}
		if(d == 1){
			i--;
			d=0;
		}
		else
			bet[i]=num;
		
	}
	//Ordenamos de menor a mayor
	bet=sortV(bet);
	return bet;

}
void show_bet(int* bet){
	
	int i=0;
	for(i=0;i<6;i++){
		printf("%d ", bet[i]);
	}
	printf("\n");
}