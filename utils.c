#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <math.h>
#include <string.h>

extern int size;
extern float* b_x;
extern float* b_ox;
extern float* b_fx;
extern float* b_cx;
extern float* b1_dense;
extern float* b2_dense;
extern float* w_x;
extern float* w_m;
extern float* w_c;
extern float* w_fx;
extern float* w_fm;
extern float* w_fc;
extern float* w_cx;
extern float* w_cm;
extern float* w_ox;
extern float* w_om;
extern float* w_oc;
extern float* w1_dense;
extern float* w2_dense;


void print_matrix(float* m, int row, int cols){
	
	int i,j;
	for(i = 0; i < row; i++){
		for(j = 0;j < cols; j++){
			if(m[i*cols+j] > 10 || m[i*cols+j] < -10)
				printf("AAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
			//printf("%f    ",m[i*cols+j]);
		}
		
		//printf("\n");
	}
	
}
char* itoa(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}


void free_matrix(float** m, int rows){
	int i;
	for(i = 0; i < rows; i++){
		if(m[i]!=NULL)
			free(m[i]);
	}
	free(m);
}



float drand ()
{
  return (rand () + 1.0) / (RAND_MAX + 1.0);
}



float random_normal ()
{
  return sqrt (-2 * log (drand ())) * cos (2 * M_PI * drand ());
}


float random_general_gaussian(float mean, float dev){
	
	return mean + sqrtf(1/dev)*random_normal();
}

int shuffle_training_set_in_vector(char** m,int n){
	if (n > 1) {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
		  char* t = m[j];
          m[j] = m[i];
          m[i] = t;
        }
    
	}
	return 0;
}

int read_files(char** name)
{
  DIR           *d;
  struct dirent *dir;
  int count = 0;
  int index = 0;
  d = opendir("/media/riccardo/DatabaseLinux/binary_midi_files");
  if (d)
  {
    while ((dir = readdir(d)) != NULL)
    {
      //printf("%s\n", dir->d_name);
      strcpy(name[count],dir->d_name);
      count++;
    }

    closedir(d);
  }

  return(0);
}    


int save_network(int epoch){
	
	int i;
	
	char string[20];
	char *s = ".bin";
	FILE *write_ptr;
	
	itoa(epoch, string);
	
	strcat(string,s);
	
	write_ptr = fopen(string,"wb");
	
	fwrite(b_x,sizeof(float)*size,1,write_ptr);
	fwrite(b_ox,sizeof(float)*size,1,write_ptr);
	fwrite(b_fx,sizeof(float)*size,1,write_ptr);
	fwrite(b_cx,sizeof(float)*size,1,write_ptr);
	fwrite(b1_dense,sizeof(float)*(size-18),1,write_ptr);
	fwrite(b2_dense,sizeof(float)*18,1,write_ptr);
	fwrite(w_x,sizeof(float)*size*size,1,write_ptr);
	fwrite(w_m,sizeof(float)*size*size,1,write_ptr);
	fwrite(w_c,sizeof(float)*size*size,1,write_ptr);
	fwrite(w_fx,sizeof(float)*size*size,1,write_ptr);
	fwrite(w_fm,sizeof(float)*size*size,1,write_ptr);
	fwrite(w_fc,sizeof(float)*size*size,1,write_ptr);
	fwrite(w_cx,sizeof(float)*size*size,1,write_ptr);
	fwrite(w_cm,sizeof(float)*size*size,1,write_ptr);
	fwrite(w_ox,sizeof(float)*size*size,1,write_ptr);
	fwrite(w_om,sizeof(float)*size*size,1,write_ptr);
	fwrite(w_oc,sizeof(float)*size*size,1,write_ptr);
	fwrite(w1_dense,sizeof(float)*size*(size-18),1,write_ptr);
	fwrite(w2_dense,sizeof(float)*size*18,1,write_ptr);
	
	i = fclose(write_ptr);
	
	return i;
	
}


void load_network(){
	int i,j;
	char input[256];
	FILE *read_ptr = NULL;
	
	do{
		printf("Inserire il file da cui caricare il network: ");
		i = scanf("%s",input);
		read_ptr = fopen(input,"r");
	}while(read_ptr == NULL);
	
	
	i = fread(b_x,sizeof(float)*size,1,read_ptr);
	i = fread(b_ox,sizeof(float)*size,1,read_ptr);
	i = fread(b_fx,sizeof(float)*size,1,read_ptr);
	i = fread(b_cx,sizeof(float)*size,1,read_ptr);
	i = fread(b1_dense,sizeof(float)*(size-18),1,read_ptr);
	i = fread(b2_dense,sizeof(float)*18,1,read_ptr);
	i = fread(w_x,sizeof(float)*size*size,1,read_ptr);
	i = fread(w_m,sizeof(float)*size*size,1,read_ptr);
	i = fread(w_c,sizeof(float)*size*size,1,read_ptr);
	i = fread(w_fx,sizeof(float)*size*size,1,read_ptr);
	i = fread(w_fm,sizeof(float)*size*size,1,read_ptr);
	i = fread(w_fc,sizeof(float)*size*size,1,read_ptr);
	i = fread(w_cx,sizeof(float)*size*size,1,read_ptr);
	i = fread(w_cm,sizeof(float)*size*size,1,read_ptr);
	i = fread(w_ox,sizeof(float)*size*size,1,read_ptr);
	i = fread(w_om,sizeof(float)*size*size,1,read_ptr);
	i = fread(w_oc,sizeof(float)*size*size,1,read_ptr);
	i = fread(w1_dense,sizeof(float)*size*(size-18),1,read_ptr);
	i = fread(w2_dense,sizeof(float)*size*18,1,read_ptr);
	
	i = fclose(read_ptr);
	
	
	if(i == EOF){
		printf("error closing the file, the process will end\n");
		exit(1);
	}
	
	
}
