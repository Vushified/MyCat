#include<stdio.h>

int main(int argc, char* argv[]){
fprintf(stderr,"this is the val of argc = %d\n",argc);
FILE* f;
fprintf(stderr,"this is argv[0]=%s\n",argv[0]);

if(argc==1){
fprintf(stderr,"this is argc=1 hence taking stdin and giving it to stdoutput\n");

int k;
k=getchar();
while(k!=EOF){
putchar(k);
k=getchar();
}

}
for(int i=1;i<argc;i++){

f=fopen(argv[i],"r");
fprintf(stderr,"this is argv [%d] = %s \n",i,argv[i]);
if(f==NULL){
fprintf(stderr,"file open failed\n");
continue;
}else{
fprintf(stderr,"file open successfull\n");}


int c;
c=getc(f);
while(c!=EOF){
putchar(c);
c=getc(f);
}

int j;
j=fclose(f);
if(j==EOF){
fprintf(stderr,"file close failed\n");
}else{
fprintf(stderr,"file close successfull\n");}
}

return 0;
}
