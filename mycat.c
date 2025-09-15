
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv){
    if(argc==1){
        printf("\nNo file provided\n");
        return 1;
    }
if(argc>3){
    perror("\nMore that 2 files were provided\n");
    return 1;
}
FILE * fp;
char buffer[1024];
for(int i=1;i<argc;i++){
fp=fopen(argv[i],"r");
if(fp==NULL){
    perror("Error opening file");
    return 1;
}
while(fgets(buffer,sizeof(buffer),fp)!=NULL){
    printf("%s",buffer);
}
printf("\n");
fclose(fp);
}
return 0;
}