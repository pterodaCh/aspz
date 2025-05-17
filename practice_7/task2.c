#include<sys/stat.h>
#include<dirent.h> 
 #include<stdio.h>
#include<time.h>
 main(int argc, char *argv[])
{
   int t=1, done;
   DIR *dir;
   struct dirent *ent;
   if(argc<3)
    {
     printf("The correct syntax is ls dirname\n");
     exit(0);
    }
   if((dir=opendir(argv[2])==NULL))  
    {
      perror("Unable to open");
      exit(1);
    }
  if(argc==3)
   {
     dir = opendir(argv[2]);
     while((ent = readdir(dir)) !=NULL)
      {
                printf("%s\t",ent->d_name);
             if(1)
             {
                 struct stat sbuf;
                 stat (ent->d_name,&sbuf);
              if(sbuf.st_size==0)   
                 printf("d");
                       
              if(sbuf.st_mode & S_IREAD)
                printf("r");
              if(sbuf.st_mode & S_IWRITE)
                printf("w");
              if(sbuf.st_mode & S_IEXEC)
                printf("x");
                  //Print the size
               printf("\t%ld",sbuf.st_size);
              printf("\t%s\n",ctime(&sbuf.st_ctime));
            }
    }
   pclose(dir);
  }
  if(argc==2)
  {
    while((ent=readdir(dir)) !=NULL)
      printf("%s\n",ent->d_name);
 }
     return(0);
}
