#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
pid_t pid;
void EXT(int sig)
{
	kill(pid, 1);
}
int main(void)
{
	char  *dir  =  (char  *)malloc((1024)  * sizeof(char));
	char  *cmdline;
	char  *cmdarg1;
	char  *cmdarg2;
	char  *command  =  (char  *)malloc((255)  * sizeof(char));
	int sizecl = 0;
	int sizearg1 = 0;
	int sizearg2 = 0;
	int sizetmp = 0;
	int i = 0;
	int temp;
	int forkkol = 0;
	(void) signal(SIGINT, EXT);
	for (;;) {
		getcwd(dir, 1024);
		printf("\n%s$ ", dir);
		sizecl = 0;
		sizearg1 = 0;
		sizearg2 = 0;
		sizetmp = 0;
		fgets(command, 255, stdin);
		if (command[sizeof(command)-2]  ==  '&')
						printf("Olol");
		printf("\n(%c)\n", command[sizeof(command)-2]);
		while (command[sizetmp] != ' ' && (int)command[sizetmp] != 10) {
			sizecl++;
			sizetmp++;
		}
		if ((int)command[sizetmp+1] != 0 && (int)command[sizetmp+1] != 10) {
				while (command[sizetmp+1] != ' ' && (int)command[sizetmp+1] != 10) {
					sizearg1++;
					sizetmp++;
				}
			sizetmp += 1;
			if ((int)command[sizetmp+1] != 0) {
				while (command[sizetmp+1] != ' ' && (int)command[sizetmp+1] != 10) {
					sizearg2++;
					sizetmp++;
				}
			}
		}
		temp = 0;
		if (command[sizetmp-1]  ==  '&') {
			printf("|||command %c\n", command[sizetmp-1]);
			command[sizetmp-1]  ==  '\0';
			temp = 1;
		}
		printf("command %c\n", command[sizetmp]);
		printf("Temp = %d\n", temp);
		cmdline  =  (char  *)malloc((sizecl)  * sizeof(char));
		for (i = 0; i <= sizecl-1; i++)
						cmdline[i] = command[i];
		int n = 0;
		if (sizearg1  != 0) {
			cmdarg1  =  (char  *)malloc((sizearg1)  * sizeof(char));
			for (i = sizecl+1; i <= (sizecl+sizearg1); i++) {
				cmdarg1[n] = command[i];
				n++;
			}
			puts(cmdarg1);
		}
		n = 0;
		if (sizearg2  != 0) {
			cmdarg2  =  (char  *)malloc((sizearg2)  * sizeof(char));
			for (i = (sizecl+sizearg1+2); i <= (sizecl+sizearg1+sizearg2+1); i++) {
				cmdarg2[n] = command[i];
				n++;
			}
		puts(cmdarg2);
		}
		int arg  =  1;
		if (sizearg1 != 0)
						arg = 2;
		if (sizearg2 != 0)
					arg = 3;
		if (cmdline[0]  ==  'c' && cmdline[1]  ==  'd' && (int)cmdline[2]  ==  0) {
						printf("--CD--\n");
						chdir(cmdarg1);
						getcwd(dir, 1024);
						puts(dir);
		};
		pid  =  fork();
		chdir(dir);
		switch (pid) {
		case -1:
				perror("fork filed");
				exit(1);
				break;
		case 0:
			/* 0 */
			if (arg   ==   1)
				execlp(cmdline, cmdline, (char *)NULL);
			else if (arg   ==   3)
				execlp(cmdline, cmdline, cmdarg1, cmdarg2, (char *)NULL);
			else if (arg   ==   2)
				execlp(cmdline, cmdline, cmdarg1, (char *)NULL);
			break;
		default: /* parent */
			if (temp   ==   0)
				wait(0);
			break;
		printf("-----\n");
		puts(dir);
		printf("-----\n");
		puts(cmdarg2);
		puts(cmdarg1);
		puts(cmdline);
		free(command);
		free(cmdline);
		free(cmdarg1);
		free(cmdarg2);
		exit(0);
		}
	}
}

