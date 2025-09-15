#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
int main(void){
    while(1){
        char * l = NULL;
        int nread;
        size_t len = 0;

        while(1){
            printf("myshell> ");
            fflush(stdout);
            nread = getline(&l,&len,stdin);
           // if(nread == -1){
             //   printf("\nExiting\n");
                //fflush(stdout);
              //  return 0;
            //}
            if(nread == -1){
                printf("\nRead EOF\n");
                //clearerr(stdin);
                return 0;
            }
            if(l[nread-1]=='\n'){
                l[nread-1]='\0';

            }
            if(strcmp(l,"quit")==0){
                printf("Exiting...\n");
                return 0;
                
            }
            if(nread!=-1){
                char *args[64];
                int argc=0;
                char * token= strtok(l," ");
                
                while(token!=NULL && argc< 63){
                    args[argc++]= token;
                    token = strtok(NULL, " ");



                }
                args[argc] = NULL;

                pid_t pid = fork();
                if(pid==0){
                    //printf("Child [%d] executing\n",getpid());
                execvp(args[0],args);
                perror("execvp failed");
                exit(1);
                }
                if(pid!=0){
                   //printf("Parent [%d] waiting for child [%d]\n",getpid(),pid);

                    int status;
                  waitpid(pid,&status,0);
                    //printf("Child [%d] finished with status %d \n",pid, WEXITSTATUS(status));
                }
                
                
            }
            
            
            
        
        }

    }
    return 0;
}