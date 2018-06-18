#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <math.h>
#include "functions.h"
#include "struct.h"
#define M_PI 3.14159265358979323846

int size;
int THREAD_NUM;

float** container3;
float** container4;
float* b_x;
float* b_ox;
float* b_fx;
float* b_cx;
float* b1_dense;
float* b2_dense;
float* w_x;
float* w_m;
float* w_c;
float* w_fx;
float* w_fm;
float* w_fc;
float* w_cx;
float* w_cm;
float* w_ox;
float* w_om;
float* w_oc;
float* w1_dense;
float* w2_dense;

float* delta_b_x;
float* delta_b_ox;
float* delta_b_fx;
float* delta_b_cx;
float* delta_b1_dense;
float* delta_b2_dense;
float* delta_w_x;
float* delta_w_m;
float* delta_w_c;
float* delta_w_fx;
float* delta_w_fm;
float* delta_w_fc;
float* delta_w_cx;
float* delta_w_cm;
float* delta_w_ox;
float* delta_w_om;
float* delta_w_oc;
float* delta_w1_dense;
float* delta_w2_dense;



	

void initialization(int size){
	

	b_x = (float*)calloc(size,sizeof(float));
	b_ox = (float*)calloc(size,sizeof(float));
	b_fx = (float*)calloc(size,sizeof(float));
	b_cx = (float*)calloc(size,sizeof(float));
	w_x = (float*)malloc(sizeof(float)*size*size);
	w_m = (float*)malloc(sizeof(float)*size*size);
	w_c = (float*)malloc(sizeof(float)*size*size);
	w_fx = (float*)malloc(sizeof(float)*size*size);
	w_fm = (float*)malloc(sizeof(float)*size*size);
	w_fc = (float*)malloc(sizeof(float)*size*size);
	w_cx = (float*)malloc(sizeof(float)*size*size);
	w_cm = (float*)malloc(sizeof(float)*size*size);
	w_ox = (float*)malloc(sizeof(float)*size*size);
	w_om = (float*)malloc(sizeof(float)*size*size);
	w_oc = (float*)malloc(sizeof(float)*size*size);
	w1_dense = (float*)malloc(sizeof(float)*(size-18)*size);
	w2_dense = (float*)malloc(sizeof(float)*18*size);
	b1_dense = (float*)calloc(size-18,sizeof(float));
	b2_dense = (float*)calloc(18,sizeof(float));
	
	int i,j;
	
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			w_x[i*size+j] = random_general_gaussian(0, size);
			w_m[i*size+j] = random_general_gaussian(0, size);
			w_c[i*size+j] = random_general_gaussian(0, size);
			w_fx[i*size+j] = random_general_gaussian(0, size);
			w_fm[i*size+j] = random_general_gaussian(0, size);
			w_fc[i*size+j] = random_general_gaussian(0, size);
			w_cx[i*size+j] = random_general_gaussian(0, size);
			w_cm[i*size+j] = random_general_gaussian(0, size);
			w_ox[i*size+j] = random_general_gaussian(0, size);
			w_om[i*size+j] = random_general_gaussian(0, size);
			w_oc[i*size+j] = random_general_gaussian(0, size);
			if(i<(size-18))
				w1_dense[i*size+j] = random_general_gaussian(0, size);
			if(i<18)
				w2_dense[i*size+j] = random_general_gaussian(0, size);
		}
	}
	

}


void update_params(int mini_batch_size, float** dw, float** db, float lr, float m);

void init_delta(){
	delta_b_x = (float*)calloc(size,sizeof(float));
	delta_b_ox = (float*)calloc(size,sizeof(float));
	delta_b_fx = (float*)calloc(size,sizeof(float));
	delta_b_cx = (float*)calloc(size,sizeof(float));
	delta_b1_dense = (float*)calloc(size-18,sizeof(float));
	delta_b2_dense = (float*)calloc(18,sizeof(float));
	delta_w_x = (float*)calloc(size*size,sizeof(float));
	delta_w_m = (float*)calloc(size*size,sizeof(float));
	delta_w_c = (float*)calloc(size*size,sizeof(float));
	delta_w_fx = (float*)calloc(size*size,sizeof(float));
	delta_w_fm = (float*)calloc(size*size,sizeof(float));
	delta_w_fc = (float*)calloc(size*size,sizeof(float));
	delta_w_cx = (float*)calloc(size*size,sizeof(float));
	delta_w_cm = (float*)calloc(size*size,sizeof(float));
	delta_w_ox = (float*)calloc(size*size,sizeof(float));
	delta_w_om = (float*)calloc(size*size,sizeof(float));
	delta_w_oc = (float*)calloc(size*size,sizeof(float));
	delta_w1_dense = (float*)calloc((size-18)*size,sizeof(float));
	delta_w2_dense = (float*)calloc(18*size,sizeof(float));
}

     
int main(int argc, char** argv)
{	
	if(argc != 3){
		printf("per runnare digitare ./lstm grandezza_vettore_input numero_di_istanze_di_training\n");
		exit(1);
	}
	
	
	int i,j,z,k,epoch,mini_batch_size;
	float lr, momentum;
	char* input = (char*)malloc(sizeof(char)*256);
	char** name = (char**)malloc(sizeof(char*)*atoi(argv[2])+2);
	srand(time(NULL));
	
	for(i = 0; i < atoi(argv[2])+2; i++){
		name[i] = (char*)malloc(sizeof(char)*256);
	}
	
	size = atoi(argv[1]);
	
	do{
		printf("Inserire il numero di thread da utilizzare: ");
		i = scanf("%s",input);
		i = atoi(input);
	}while(i == 0);
	
	THREAD_NUM = i;
	
	do{
		printf("Caricare una rete?(y/n): ");
		i = scanf("%s",input);
	}while(input[0] != 'y' && input[0] != 'Y' && input[0] != 'n' && input[0] != 'N');
	
	
	if(input[0] == 'y' || input[0] == 'Y'){
		initialization(size);
		load_network();
	}
	else
		initialization(size);
		
	
	
	init_delta();
		
	do{
		printf("Inserire il numero di epoche da effettuare: ");
		i = scanf("%s",input);
		i = atoi(input);
	}while(i == 0);
	
	epoch = i;
	
	do{
		printf("Inserire la grandezza del minibatch: ");
		i = scanf("%s",input);
		i = atoi(input);
	}while(i == 0 || atoi(argv[2])%i != 0);
	
	mini_batch_size = i;
	
	do{
		printf("Inserire la grandezza del learning rate: ");
		i = scanf("%s",input);
		lr = atof(input);
	}while(lr == 0);
	
	do{
		printf("Inserire la grandezza del learning momentum: ");
		i = scanf("%s",input);
		momentum = atof(input);
	}while(momentum == 0);
	
	read_files(name);
	
	
	
	container3 = (float**)malloc(100000*THREAD_NUM*sizeof(float*));
	container4 = (float**)malloc(100000*THREAD_NUM*sizeof(float*));
	
	pthread_t threads[THREAD_NUM];
    thread_args* args[THREAD_NUM];
    
    float** dw = (float**)malloc(sizeof(float*)*13*THREAD_NUM);
    float** db = (float**)malloc(sizeof(float*)*6*THREAD_NUM);
    
    for(i = 0; i < 13*THREAD_NUM; i++){
		if((i+2)%13 == 0)
			dw[i] = (float*)calloc((size-18)*size,sizeof(float));
		
		else if((i+1)%13 == 0)
			dw[i] = (float*)calloc(18*size,sizeof(float));
		
		else
			dw[i] = (float*)calloc(size*size,sizeof(float));
			
		if(i<6*THREAD_NUM){
			if((i+2)%6 == 0)
				db[i] = (float*)calloc((size-18),sizeof(float));
			
			else if((i+1)%6 == 0)
				db[i] = (float*)calloc(18,sizeof(float));
			
			else
				db[i] = (float*)calloc(size,sizeof(float));
			}
	}
    
    printf(">>>>>>>>>> start first epoch\n");
    //print_matrix(dw[1],size,size);
	for(i = 0; i < epoch; i++){
		
		
		shuffle_training_set_in_vector(&name[2],atoi(argv[2]));
		
		
		
		for(j = 0; j < atoi(argv[2])/(mini_batch_size);j++){
			
			for(k = 0; k < mini_batch_size; k+=THREAD_NUM){
				
				for(z = 0; z < THREAD_NUM && k+z < mini_batch_size; z++){
					printf(">>>>>>>>>> thread number %d starts training an instance\n",z);
					args[z] = (thread_args*)malloc(sizeof(thread_args));
					args[z]->mini_batch = j;
					args[z]->k = k;
					args[z]->thread = z;
					args[z]->mini_batch_size = mini_batch_size;
					args[z]->len = atoi(argv[2]);
					args[z]->name = name;
					args[z]->dw = dw+(13*z);
					args[z]->db = db+(6*z);
					pthread_create(threads+z, NULL, thread_func, args[z]);
				}
				
				for(z = 0; z<THREAD_NUM && k+z < mini_batch_size; z++) {
					pthread_join(threads[z], NULL);
					free(args[z]);
				}	
			
			}
			
			//printf("mini batch effettuato\n");
			//print_matrix(dw[7],size,size);
			//printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");

			//print_matrix(dw[4],size,size);

			update_params(mini_batch_size,dw,db,lr,momentum);
			
			printf(">>>>>>>>>> mini batch %d/%d, epoch: %d/%d\n",j+1,atoi(argv[2])/(mini_batch_size),i+1,epoch);
			//printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
			
			
			
			
		
		}
		
		save_network(i);
		
	}
	
}



void update_params(int mini_batch_size, float** dw, float** db, float lr, float m){
	
	int i,j,k,z;
	for(i = 1; i < THREAD_NUM; i++){
		for(j = 0; j < 13; j++){
			for(k = 0; k < size; k++){
				for(z = 0; z < size; z++){
					
					if(j == 11){
						if(k < (size-18)){
							dw[j][k*size+z] += dw[i*13+j][k*size+z];
							dw[i*13+j][k*size+z] = 0;
						}
					}
					
					else if(j == 12){
						if(k < 18){
							dw[j][k*size+z] += dw[i*13+j][k*size+z];
							dw[i*13+j][k*size+z] = 0;
						}
					}
					
					else{
						dw[j][k*size+z] += dw[i*13+j][k*size+z];
						dw[i*13+j][k*size+z] = 0;
					}

				}
				
						 
			}
		}
	}
	
	/*
	print_matrix(dw[1],size,size);
	exit(0);
	*/
	for(i = 1; i < THREAD_NUM; i++){
		for(j = 0; j < 6; j++){
			for(k = 0; k < size; k++){
				if(j == 4){
					if(k < size-18){
						db[j][k] += db[i*6+j][k];
						db[i*6+j][k] = 0;
					}
				}
				
				else if(j == 5){
					if(k < 18){
						db[j][k] += db[i*6+j][k];
						db[i*6+j][k] = 0;
					}
				}
				
				else{
					db[j][k] += db[i*6+j][k];
					db[i*6+j][k] = 0;
				}
				
				
			}
		}
	}
	
	
	
	
	for(i = 0; i < size; i++){
		if(i < size-18){
			for(j = 0; j < size; j++){
				
				if(i < 18){
					delta_w2_dense[i*size+j] = (((float)((dw[12][i*size+j]*lr)/mini_batch_size))*(1+m)*-1)+(m*m*delta_w2_dense[i*size+j]);
					w2_dense[i*size+j] += delta_w2_dense[i*size+j];
					dw[12][i*size+j] = 0;
					}
				
				delta_w1_dense[i*size+j] = (((float)((dw[11][i*size+j]*lr)/mini_batch_size))*(1+m)*-1)+(m*m*delta_w1_dense[i*size+j]);
				w1_dense[i*size+j] += delta_w1_dense[i*size+j];
				dw[11][i*size+j] = 0;
			}
			
			if(i < 18){
				delta_b2_dense[i] = (((float)((db[5][i]*lr)/mini_batch_size))*(1+m)*-1)+(m*m*delta_b2_dense[i]);
				b2_dense[i]+=delta_b2_dense[i];
				db[5][i] = 0;
			}
			
			delta_b1_dense[i] = (((float)((db[4][i]*lr)/mini_batch_size))*(1+m)*-1)+(m*m*delta_b1_dense[i]);
			b1_dense[i]+=delta_b1_dense[i];
			db[4][i] = 0;
		}
		
	}
	
	for(i = 0; i < size; i++){
		if(i < size){
			for(j = 0; j < size; j++){
				
				delta_w_x[i*size+j] = (((float)((dw[3][i*size+j]*lr)/mini_batch_size))*(1+m)*-1)+(m*m*delta_w_x[i*size+j]);
				w_x[i*size+j] += delta_w_x[i*size+j];
				dw[3][i*size+j] = 0;
				
				delta_w_m[i*size+j] = (((float)((dw[7][i*size+j]*lr)/mini_batch_size))*(1+m)*-1)+(m*m*delta_w_m[i*size+j]);
				w_m[i*size+j] += delta_w_m[i*size+j];
				dw[7][i*size+j] = 0;
				
				delta_w_c[i*size+j] = (((float)((dw[10][i*size+j]*lr)/mini_batch_size))*(1+m)*-1)+(m*m*delta_w_c[i*size+j]);
				w_c[i*size+j] += delta_w_c[i*size+j];
				dw[10][i*size+j] = 0;
				
				delta_w_fx[i*size+j] = (((float)((dw[2][i*size+j]*lr)/mini_batch_size))*(1+m)*-1)+(m*m*delta_w_fx[i*size+j]);
				w_fx[i*size+j] += delta_w_fx[i*size+j];
				dw[2][i*size+j] = 0;
				
				delta_w_fm[i*size+j] = (((float)((dw[6][i*size+j]*lr)/mini_batch_size))*(1+m)*-1)+(m*m*delta_w_fm[i*size+j]);
				w_fm[i*size+j] += delta_w_fm[i*size+j];
				dw[6][i*size+j] = 0;
				
				delta_w_fc[i*size+j] = (((float)((dw[9][i*size+j]*lr)/mini_batch_size))*(1+m)*-1)+(m*m*delta_w_fc[i*size+j]);
				w_fc[i*size+j] += delta_w_fc[i*size+j];
				dw[9][i*size+j] = 0;
				
				delta_w_cx[i*size+j] = (((float)((dw[1][i*size+j]*lr)/mini_batch_size))*(1+m)*-1)+(m*m*delta_w_cx[i*size+j]);
				w_cx[i*size+j] += delta_w_cx[i*size+j];
				/*
				if(i == size -1 && j == size-14){
					printf("%f\n",w_cx[i*size+j]);
					exit(0);
				}
				* */
				dw[1][i*size+j] = 0;
				
				delta_w_cm[i*size+j] = (((float)((dw[5][i*size+j]*lr)/mini_batch_size))*(1+m)*-1)+(m*m*delta_w_cm[i*size+j]);
				w_cm[i*size+j] += delta_w_cm[i*size+j];
				dw[5][i*size+j] = 0;
				
				delta_w_ox[i*size+j] = (((float)((dw[0][i*size+j]*lr)/mini_batch_size))*(1+m)*-1)+(m*m*delta_w_ox[i*size+j]);
				w_ox[i*size+j] += delta_w_ox[i*size+j];
				dw[0][i*size+j] = 0;
				
				delta_w_om[i*size+j] = (((float)((dw[4][i*size+j]*lr)/mini_batch_size))*(1+m)*-1)+(m*m*delta_w_om[i*size+j]);
				w_om[i*size+j] += delta_w_om[i*size+j];
				dw[4][i*size+j] = 0;
				
				delta_w_oc[i*size+j] = (((float)((dw[8][i*size+j]*lr)/mini_batch_size))*(1+m)*-1)+(m*m*delta_w_oc[i*size+j]);
				w_oc[i*size+j] += delta_w_oc[i*size+j];
				dw[8][i*size+j] = 0;
			
			}
			
			delta_b_ox[i] = (((float)((db[0][i]*lr)/mini_batch_size))*(1+m)*-1)+(m*m*delta_b_ox[i]);
			b_ox[i] += delta_b_ox[i];
			db[0][i] = 0;
			
			delta_b_x[i] = (((float)((db[2][i]*lr)/mini_batch_size))*(1+m)*-1)+(m*m*delta_b_x[i]);
			b_x[i] += delta_b_x[i];
			db[2][i] = 0;
			
			delta_b_fx[i] = (((float)((db[3][i]*lr)/mini_batch_size))*(1+m)*-1)+(m*m*delta_b_fx[i]);
			b_fx[i] += delta_b_fx[i];
			db[3][i] = 0;
			
			delta_b_cx[i] = (((float)((db[1][i]*lr)/mini_batch_size))*(1+m)*-1)+(m*m*delta_b_cx[i]);
			b_cx[i] += delta_b_cx[i];
			db[1][i] = 0;
		}
		
	}
	
}




