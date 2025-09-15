#include <stdio.h>

int main(int argc,char ** argv){
FILE * fp;
char buffer[1024];
if(argc==1){
    printf("No file provided\n");
    return 1;
}
if(argc>2){
printf("Too many files\n");
return 1;
}
fp = fopen(argv[1],"r");
if(fp==NULL){
    perror("Error opening file");
    return 1;
}
int i=0;
while(fgets(buffer,sizeof(buffer),fp)!=NULL&&i<3){
    printf("%s",buffer);
    i++;
}
printf("\n");
fclose(fp);
return 0;
}