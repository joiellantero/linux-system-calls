#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

//sig_atomic_t sig_handler_status;
int child = 0, checker = 0;

void sig_handler(int signo){
	FILE* fcontestant = fopen("contestant.txt", "a+");

	if (signo == SIGUSR1){
		checker = 1;
		printf("%d won\n", child);
   		fprintf(fcontestant, "%d - W\n", child);
	}

	if (signo == SIGUSR2){
		checker = 1;
		printf("%d lost\n", child);
   		fprintf(fcontestant, "%d - L\n", child);
	}

	fclose(fcontestant);

	//wait(&sig_handler_status);
}

int main(int argc, char *argv[]){
	if (argc == 1){
		puts("[ERROR] No argument for pipe name.");
	}

	else{ 
		int fd;
   		char secretCode[80], *guess, *pid_guess, *child_pid; 
		guess = (char *) malloc (80);
		pid_guess = (char *) malloc (160);
		child_pid = (char *) malloc (5);
 
   		mkfifo(argv[1], 0666);

		printf("Process pid %d\n", getpid());
				
		while(1){
			pid_t child = fork();

			if (child < 0){
				perror("fork");
				exit(1);
			}
	
			else if (child == 0){
				child = getpid();

				sprintf(child_pid, "%d", child);
				
				fd = open(argv[1], O_WRONLY);
				write(fd, child_pid, sizeof(child_pid));
				close(fd);

				signal(SIGUSR1, sig_handler);
				signal(SIGUSR2, sig_handler);

				sleep(1);

				while(1){				

					printf("%d Please guess the code: ", child);
					scanf("%s", guess);
					
					sprintf(pid_guess, "%s %s", child_pid, guess);
							//printf("[pid_guess]: %s\n", pid_guess);
							//printf("[child_pid]: %s\n", child_pid);
							//printf("[guess]: %s\n", guess);

					fd = open(argv[1], O_WRONLY);
					write(fd, pid_guess, sizeof(pid_guess));
					close(fd);	

					sleep(1);
				}
				
				exit(0);
			}

			else {
				sleep(1);
				wait(NULL);
			}
	
			free (guess);
			free (pid_guess);
			free (child_pid);

		} 
	}
   	return 0;
}


