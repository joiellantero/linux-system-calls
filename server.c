#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
 
int main(int argc, char *argv[]){
	
	if (argc == 1){
		puts("[ERROR] No argument for pipe name.");
	}

	else {
    	int fd, trials, child, i;
		char secretCode[80], *guess, *child_pid, *pid_guess, *og_child_pid;
		pid_guess = (char *) malloc (160);
		child_pid = (char *) malloc (5);
		guess = (char *) malloc (80);
		og_child_pid = (char *) malloc (80);
 
    	mkfifo(argv[1], 0666);
		
		while(1){
			printf("Enter the number of trials per contestant: ");
			scanf("%d", &trials);
 		
			printf("Enter secret code: ");
			scanf("%s", secretCode);

			printf("Starting a new game with secret code %s\n", secretCode);

			fd = open(argv[1], O_RDONLY);
			read(fd, og_child_pid, sizeof(og_child_pid));
			
			printf("%s joins the game\n", og_child_pid);
			child = atoi(og_child_pid);
			close(fd);
			
			for (i = 0; i < trials; i++){

				fd = open(argv[1], O_RDONLY);
				read(fd, pid_guess, sizeof(pid_guess));
				sscanf(pid_guess, "%s %s", child_pid, guess);
							//printf("[og_child_pid] %s\n", og_child_pid); 
							//printf("[pid_guess]: %s\n", pid_guess);
							//printf("[child_pid]: %s\n", child_pid);
							//printf("[guess]: %s\n", guess);
				close(fd);	

				if(strcmp(og_child_pid, child_pid) == 0){
					
					if(strncmp(guess, secretCode, strlen(secretCode)) == 0){
									
						printf("%d answers %s correctly\n", child, guess);

						FILE* fwinners = fopen("winners.txt", "a+");
						fprintf(fwinners, "%d\n", child);
						fclose(fwinners);

						kill(child, SIGUSR1);
						break;
		
					}

					else{
						printf("%d answers %s incorrectly\n", child, guess);					
					}
				}

				else {
					i--;
				}
				
			}

			if(i == trials){
				printf("%d exceeded number of trials, process will be terminated\n", child);
				kill(child, SIGUSR2);
			}

			kill(child, SIGKILL);			
		}

		free (guess);
		free (pid_guess);
		free (child_pid);
	}

    return 0;

}


