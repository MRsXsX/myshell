#include <stdio.h>
#include <string.h>
int main(int argc, char ** argv){
if(argc>3){
    printf("Too many arguments\n");
    return 1;
}
if(argc==1){
    printf("No arguments provided\n");
    return 1;
}
FILE * fp;
char buffer[1024];
int count=1;
if(argc==2){
    if(strcmp(argv[1],"-c")==0){
        printf("No file provided\n");
        return 1;
    }
}
if(argc==3){
    fp = fopen(argv[2],"r");
    }
else {
    fp = fopen(argv[1],"r");
}


if(fp==NULL){
    perror("Error opening file");
    return 1;
}
char prev[1024]; 
fgets(buffer,sizeof(buffer),fp);
strncpy(prev,buffer,1024);

while(fgets(buffer,sizeof(buffer),fp)!=NULL){
    if(strncmp(buffer,prev,1024)==0){
        while(fgets(buffer,sizeof(buffer),fp)!=NULL&&strncmp(buffer,prev,1024)==0){
            count++;

            }

            if(argc==3 && strcmp(argv[1],"-c")==0){
                printf("%d %s",count+1,prev);
            } else {
                printf("%s",prev);
            }
            
            count=1;
        }

       strncpy(prev,buffer,1024);

        
    }
    fclose(fp);
    
}