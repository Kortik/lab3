#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
pid_t pid; //pid глобальные дабы он был видел в EXT
void EXT(int sig) {
	
	kill(pid, 1); // В теории убийство пида	
}
int main() {//некоторые переменные не используются
	char *dir = (char *)malloc((1024) * sizeof(char));
	//char *newdir = (char *)malloc((1024) * sizeof(char)); 
	char *commandline;
	char *commandarg1;
	char *commandarg2;
	char *command = (char *)malloc((255) * sizeof(char));
	int sizecl=0;
	int sizearg1=0;
	int sizearg2=0;
	int sizetmp=0;
	int i=0;
	int temp;
	int forkkol=0;
	(void) signal(SIGINT, EXT);
	for(;;){ 
	getcwd (dir, 1024); //взять адресс
	printf("\n%s$ ",dir); //вывод начала строки
	sizecl=0;
	sizearg1=0;
	sizearg2=0;
	sizetmp=0;
	fgets(command, 255, stdin); //ввод команды
	if (command[sizeof(command)-2]=='&') printf("Olol");
	printf("\n(%c)\n", command[sizeof(command)-2]);
	//for (int j=0; j<=255; j++)
	//{
	//	if (command[j]=='&' && ()command[j+1]==
	//}
	while (command[sizetmp]!=' ' && (int)command[sizetmp]!=10) {//скан количества символов команды 	
		sizecl++;
		sizetmp++;		
	}
	if ((int)command[sizetmp+1]!=0 && (int)command[sizetmp+1]!=10) { //кривая проверка на отстутствие аргументов
		while (command[sizetmp+1]!=' '  && (int)command[sizetmp+1]!=10) { //скан количества символов 1 аргумента
			sizearg1++;
			sizetmp++;	
		}
	sizetmp+=1;
	if( (int)command[sizetmp+1]!=0){ //проверка на наличие 2го аргумента
	while (command[sizetmp+1]!=' ' && (int)command[sizetmp+1]!=10) { //я знаю что это быдлогавно но хз как исправить. 10 это код NULL
		sizearg2++;
		sizetmp++;		
		}
	}
	}
	temp=0;
	printf ("---%d---", temp);
	if (command[sizetmp-1]=='&') {
		printf ("|||command %c \n", command[sizetmp-1]);
		command[sizetmp-1]=='\0';
		temp=1;
	}
	
	printf ("command %c \n", command[sizetmp]);
	printf ("Temp=%d\n", temp);
	commandline = (char *)malloc((sizecl ) * sizeof(char)); 
	for (i=0; i<=sizecl-1; i++) { //присвоение команды в массив команды
		commandline[i]=command[i];
	}
	//puts(commandline);
	int n=0;	
	if (sizearg1 !=0) {
		commandarg1 = (char *)malloc((sizearg1) * sizeof(char));
		for (i=sizecl+1; i<=(sizecl+sizearg1); i++) { //присвоение 1 аргумента 
			commandarg1[n]=command[i];
			n++;
			}
		puts(commandarg1);
	}
	n=0;
	if (sizearg2 !=0) {

		commandarg2 = (char *)malloc((sizearg2 ) * sizeof(char));
		for (i=(sizecl+sizearg1+2); i<=(sizecl+sizearg1+sizearg2+1); i++) {
			commandarg2[n]=command[i]; //присвоение 2го аргумента
			n++;
			}
	puts(commandarg2);
		}

	int arg = 1;
	if (sizearg1!=0) arg=2; //кривенькая проверка на наличие аргументов
	if (sizearg2!=0) arg=3;
	//printf("-----\n");
	//puts(dir);
	//printf("-----\n");
	if (commandline[0]=='c' && commandline[1]=='d' && (int)commandline[2]==0)
				{
					printf("--CD--\n");
					chdir(commandarg1); //команда cd. Выполняется до fork'a 
					getcwd (dir, 1024);
					puts(dir);
					
				};
	
	pid = fork();
	chdir(dir); //присвоение обоим процессам рабочей дериктории
	switch(pid)
	{
		case -1:
		perror("fork filed");
		exit(1);
		case 0: // 0 это PID ребенка(или как там)
			if (arg ==1) execlp (commandline, commandline, (char*)NULL);
			else if (arg==3) execlp(commandline,commandline,commandarg1,commandarg2,(char*)NULL);
			else if (arg==2) execlp(commandline,commandline,commandarg1, (char*)NULL);
			break;
		default:
			if (temp==0) wait(0); //это если родительский пид
			break;
		//В СВЯЗИ С ОСОБЕННОСТЯМИ exec не доходит до нижних строк. и я не совсем уверен нужны ли они
		// Осталось сделать & 
	printf("-----\n"); // до сюдова оно не доходит
	puts(dir);
	printf("-----\n");
	puts(commandarg2);
	puts(commandarg1);
	puts(commandline);
	free(command);
	free(commandline);
	free(commandarg1);
	free(commandarg2);
	exit(0);
}
}
}
//PS Извиняюсь за суперпепермегагавнокод

