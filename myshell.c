#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

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
                int argc=0, fargc =0, use_fargs=0;

                char * token= strtok(l," ");
                char * fargs[64];
                
                while(token!=NULL && (argc< 63&& fargc<63)){
                    
                    if((strncmp(token,"-o",2)==0)){
                        use_fargs=1;

                    }
                    else if(use_fargs){
                        fargs[fargc++]= token;
                    }
                    else{
                        args[argc++]= token;
                    }

                    
                    token = strtok(NULL, " ");



                }
                args[argc] = NULL;
                fargs[fargc] = NULL;
                if(use_fargs && fargc==0){
                    printf("No output file specified after -o\n");
                    continue;
                }
                if(use_fargs && fargc>1){
                    printf("Too many arguments after -o\n");
                    continue;
                }
                int fdout;
                int saved_stdout;
                if(use_fargs){
                //Output to a file 
                fdout = open(fargs[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                saved_stdout = dup(1);
                
                
                dup2(fdout, 1); // Redirect stdout to file
                }



                // execvp(args[0], args);
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
                    if(use_fargs){
                        // Restore original stdout
                  dup2(saved_stdout, 1);
                    close(saved_stdout);
                    close(fdout);
                    }

                    //printf("Child [%d] finished with status %d \n",pid, WEXITSTATUS(status));
                }
                
                
            }
            
            
            
        
        }

    }
    return 0;
}