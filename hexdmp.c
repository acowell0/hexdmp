#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  if (argc < 2) 
  {
    printf("usage: ./hexdmp <file name>\n");
    return 1;
  }
  FILE *fp;

  if ((fp = fopen(argv[1], "rb")) == NULL) 
  {
    printf("unable to open file: %s\n", argv[1]);
    return 1;
  }
  else 
  { 
    fseek(fp, 0, SEEK_END);          
    int filelen = ftell(fp);            
    rewind(fp);  

    int j = 1;
    int buffsize = 16;
    unsigned char buffer[buffsize];

    do {
      fread(buffer, sizeof(buffer), 1, fp);
      
     // printf("chunk %4d: ", j);
      printf("%07X0: ", j-1);
      for(int i=0; i < buffsize; i++) 
      {
        printf("%02X",buffer[i]);
        if((i+1)%2 == 0)
          printf(" ");
      }

      printf("|");
      for(int i=0; i < buffsize; i++) 
      {  
        if(*(buffer+i)>=' ' && *(buffer+i)<='~')
          printf("%c", *(buffer+i));
        else
          printf(".");
      }      
     
      printf("|\n");

      // clear buffer
      memset(buffer,0,sizeof(buffer));

      j++;
    } while(ftell(fp) != filelen);
    
    if(feof(fp))
      printf("(end of file)\n");   

    fclose(fp);
  }

  return 0;
}
