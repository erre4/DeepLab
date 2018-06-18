#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "functions.h"
#include "struct.h"


extern int size;
extern int THREAD_NUM;

extern float** container3;
extern float** container4;
extern float* b_x;
extern float* b_ox;
extern float* b_fx;
extern float* b_cx;
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
extern float* b1_dense;
extern float* b2_dense;



int bool_is_real(float d)
{
return (d != d);
}


void* thread_func(void* _args) {
	
	thread_args* args = (thread_args*) _args;
	int mini_batch = args->mini_batch;
	int k = args->k;
	int thread = args->thread;
	int mini_batch_size = args->mini_batch_size;
	int len = args->len;
	float** dw = args->dw;
	float** db = args->db;
	char** name = args->name;
	
	
	
	int i,j;
	char *fname = (char*)malloc(sizeof(char)*256);
	fname[0] = '\0';
	char* temps = "/media/riccardo/DatabaseLinux/binary_midi_files/";
	FILE *kfile;
	size_t kfilesize;
	char *ksource;
	float** music;
	char temp[2];
	
	
	strcat(fname,temps);
	strcat(fname,name[2+mini_batch*mini_batch_size+thread+k]);
	
	//printf("Thread %d, file: %s\n",thread,fname);
	kfile = fopen(fname, "r" );
	
	
	
	if(kfile == NULL){
		printf("Thread %d: error opening file %s\n",thread,fname);
		exit(1);
	}
	
	
	
	
	fseek( kfile, 0, SEEK_END );
	kfilesize = ((size_t)ftell(kfile));
	rewind( kfile );
	
	ksource = (char*)malloc(kfilesize*sizeof(char));
	i = fread(ksource, 1, kfilesize, kfile );
	fclose( kfile );
	
	music = (float**)malloc(sizeof(float*)*kfilesize/size);
	
	temp[1] = '\0';
	
	for(i = 0; i < kfilesize/size; i++){
		music[i] = (float*)malloc(sizeof(float)*size);
		for(j = 0; j < size; j++){
			
			temp[0] = ksource[i*size+j];
			
			music[i][j] = (float)(atof(temp));
		}
		
	}
	
	
	
	train(music,dw,db,thread,kfilesize/size);
	
	
	free_matrix(music,kfilesize/size);
	free(ksource);
	

}



void dense(int input, int output, float *x, float*w, float* b, int a, float* y){
	int i,j;
	float sum = 0, sum2 = 0;
	
	if(a == 0){
		
		for(i = 0; i < output; i++){
			for(j = 0; j < input; j++){
				sum+=w[i*input+j]*x[j];
			}
			
		sum+=b[i];
		y[i] = 	1 / (1 + exp (-sum));
		sum = 0;
			
		}
	}
	
	else{
		
		for(i = 0; i < output; i++){
			for(j = 0; j < input; j++){
				sum+=w[i*input+j]*x[j];
			}
			
		sum+=b[i];
		sum2+=exp(sum);
		y[i] = sum;
		sum = 0;
			
		}
		
		for(i = 0; i < output; i++){
			y[i] = exp(y[i])/sum2;
			if(bool_is_real(y[i])){
				printf("qui\n");
				exit(1);
			}
		}
	}
}

void dropout(float p, int flag, int *mask, float* x, float* output, int size){
	int i;
	if(!flag){
		for(i = 0; i<size; i++){
			if(((float)rand() / (float)RAND_MAX ) <= p){
				mask[i] = 0;
			}
			
			output[i] = (float)mask[i]*x[i];
			if(bool_is_real(output[i])){
				printf("qui2\n");
				exit(1);
			}
		}
	}
	
	else{
		for(i = 0; i < size; i++){
			output[i] = (float)mask[i]*x[i];
			if(bool_is_real(output[i])){
				printf("qui3, %f, componenti precedenti %f         %f\n",output[i],x[i],(float)mask[i]);
				exit(1);
			}
		}
	}
}


void lstm(float* w_x, float* w_m, float* w_c,float* x, float* last_m, float* last_c, float*b_x, int size_x, float* container, float* w_fx, float* w_fm, float* w_fc, float* b_fx, float* container2, float* w_cx, float* w_cm, float* b_cx, float* container3, float* w_ox, float* w_om, float* w_oc, float* b_ox, float* container4,float* zi, float* zf, float* zg, float* zo, float* o, float*f, float* it){
	int i,j;
	
	
	
	for(i = 0; i<size_x; i++){
		
		container[i] += b_x[i];
		container2[i] += b_fx[i];
		container3[i] += b_cx[i];
		container4[i] += b_ox[i];
		for(j = 0; j<size_x; j++){
			
			container[i] += w_x[size_x*i+j]*x[j];
			container[i] += w_m[size_x*i+j]*last_m[j];
			container[i] += w_c[size_x*i+j]*last_c[j];
			
			container2[i] += w_fx[size_x*i+j]*x[j];
			container2[i] += w_fm[size_x*i+j]*last_m[j];
			container2[i] += w_fc[size_x*i+j]*last_c[j];
			
			container3[i] += w_cx[size_x*i+j]*x[j];
			container3[i] += w_cm[size_x*i+j]*last_m[j];
			
		}
		
		zi[i] = container[i];
		container[i] = 1 / (1 + exp (-container[i]));
		it[i] = container[i];
		
		zf[i] = container2[i];
		container2[i] = 1 / (1 + exp (-container2[i]));
		f[i] = container2[i];
		
		zg[i] = container3[i];
		container3[i] = (exp(container3[i]) - exp(-container3[i])) / (exp(container3[i]) + exp(-container3[i]));
		container3[i] *= container[i];
		container3[i] += container2[i]*last_c[i];
		
		//printf("%f\n",x[i]);
		container[i] = 0;
		container2[i] = 0;
		
		for(j = 0; j<size_x; j++){
			
			container4[i] += w_ox[size_x*i+j]*x[j];
			container4[i] += w_om[size_x*i+j]*last_m[j];
			container4[i] += w_oc[size_x*i+j]*container3[j];
		}
		
		zo[i] = container4[i];
		container4[i] = 1 / (1 + exp (-container4[i]));
		o[i] = container4[i];
		
		//printf("%f\n",container3[i]);
		
		container4[i] *= (exp(container3[i]) - exp(-container3[i])) / (exp(container3[i]) + exp(-container3[i]));
		if(bool_is_real(container4[i])){
				print_matrix(container3,size,1);
				printf("ASSASASASA\n");
				print_matrix(zf,size,1);
				printf("qui4 %f componenti precedenti: %f          %f\n",container4[i],o[i],(container3[i]));
				exit(1);
				
			}
	}
	
}


void train(float** music, float** dw_t, float** db_t, int thread, int lunghezza_brano){
	
	int i,j,flag,k = 0; 
	
	float** dw = (float**)malloc(sizeof(float*)*13);
	float** db = (float**)malloc(sizeof(float*)*6);
	
	for (i = 0; i < 13; i++){
		if(i == 11)
			dw[i] = (float*)calloc(size*(size-18),sizeof(float));
			
		else if( i == 12)
			dw[i] = (float*)calloc(size*(18),sizeof(float));
			
		else
			dw[i] = (float*)calloc(size*(size),sizeof(float));
	}	
	
	for(i = 0; i < 6; i++){
		if(i == 4)
			db[i] = (float*)calloc((size-18),sizeof(float));
		else if(i == 5)
			db[i] = (float*)calloc((18),sizeof(float));
			
		else
			db[i] = (float*)calloc(size,sizeof(float));
			
	}
	
	int flag1 = 0;
	int flag2 = 0;
	int flag3 = 0;
	
	int* mask1 = (int*)malloc(sizeof(int)*size);
	int* mask2 = (int*)malloc(sizeof(int)*size);
	int* mask3 = (int*)malloc(sizeof(int)*size);
	
	
	float* output = (float*)calloc(size,sizeof(float));
	float* outputsec = (float*)calloc(size,sizeof(float));
	
	float** tempo = (float**)malloc(sizeof(float*)*12);
	
	for(i = 0; i < 12; i++){
		tempo[i] = (float*)malloc(sizeof(float)*size);
	}
	
	float** zi = (float**)malloc(sizeof(float*)*3*lunghezza_brano);
	float** zf = (float**)malloc(sizeof(float*)*3*lunghezza_brano); 
	float** zg = (float**)malloc(sizeof(float*)*3*lunghezza_brano);
	float** zo = (float**)malloc(sizeof(float*)*3*lunghezza_brano);
	float** o = (float**)malloc(sizeof(float*)*3*lunghezza_brano);
	float** f = (float**)malloc(sizeof(float*)*3*lunghezza_brano);
	float** it = (float**)malloc(sizeof(float*)*3*lunghezza_brano);
	float** output1 = (float**)malloc(sizeof(float*)*lunghezza_brano);
	float** output2 = (float**)malloc(sizeof(float*)*lunghezza_brano);
	
	float* container = (float*)calloc(size,sizeof(float));
	float* container2 = (float*)calloc(size,sizeof(float));
	
	float** matrix = (float**)malloc(sizeof(float*)*62);
	
	float** dc_t1 = (float**)malloc(3*sizeof(float*));
	dc_t1[0] = (float*)calloc(size,sizeof(float));
	dc_t1[1] = (float*)calloc(size,sizeof(float));
	dc_t1[2] = (float*)calloc(size,sizeof(float));
	
	float** y1 = (float**)malloc(sizeof(float*)*lunghezza_brano);
	float** y2 = (float**)malloc(sizeof(float*)*lunghezza_brano);
	
	k = 0;
	//printf("%d, %d\n",lunghezza_brano,thread);
	for(i = 0; i < (lunghezza_brano*4+3); i++){
		
		
		container3[i+thread*100000] = (float*)calloc(size,sizeof(float));
		
		if((i+1)%4==0){
			container4[i+thread*100000] = music[k];
			
			if(i != lunghezza_brano*4+3-4){
				y1[k] = music[k+1];
				y2[k] = &(music[k+1][size-18]);
			}
			else{
				y1[k] = (float*)calloc((size-18),sizeof(float));
				y1[k][size-19] = 1;
				y2[k] = (float*)calloc(18,sizeof(float));
			}
			
			k++;
		}
		else
			container4[i+thread*100000] = (float*)calloc(size,sizeof(float));
		
		if(i < 3*lunghezza_brano){
			zi[i]= (float*)malloc(sizeof(float)*size);
			zf[i]= (float*)malloc(sizeof(float)*size);
			zg[i]= (float*)malloc(sizeof(float)*size);
			zo[i]= (float*)malloc(sizeof(float)*size);
			o[i]= (float*)malloc(sizeof(float)*size);
			f[i]= (float*)malloc(sizeof(float)*size);
			it[i]= (float*)malloc(sizeof(float)*size); 
		}
		
		if(i<lunghezza_brano){
			output1[i] = (float*)malloc(sizeof(float)*(size-18));
			output2[i] = (float*)malloc(sizeof(float)*18);
		}
	}
	
	for(i = 0; i < size; i++){
		mask1[i] = 1;
		mask2[i] = 1;
		mask3[i] = 1;
	}
	
	
	
	
	
	
	/*feed_forward*/
	for(i = 0; i < lunghezza_brano; i++){
		//printf("i %d, thread: %d, lunghezza brano: %d\n",i,thread,lunghezza_brano);
		for(j = 0; j < 3; j++){
			//printf("j %d\n",j);
			if(j == 0){
				if(i == 0)
					lstm(w_x, w_m, w_c,container4[thread*100000+3+j],container4[thread*100000+i*3+i+j],container3[thread*100000+i*3+j], b_x, size, container, w_fx, w_fm, w_fc, b_fx, container2, w_cx, w_cm, b_cx, container3[thread*100000+3+i*3+j], w_ox, w_om, w_oc, b_ox, container4[thread*100000+4+j],zi[i*3+j], zf[i*3+j], zg[i*3+j], zo[i*3+j], o[i*3+j], f[i*3+j], it[i*3+j]);
				else
					lstm(w_x, w_m, w_c,container4[thread*100000+(i+1)*3+i+j],container4[thread*100000+i*3+i+j],container3[thread*100000+i*3+j], b_x, size, container, w_fx, w_fm, w_fc, b_fx, container2, w_cx, w_cm, b_cx, container3[thread*100000+3+i*3+j], w_ox, w_om, w_oc, b_ox, container4[thread*100000+(i+1)*3+i+j+1],zi[i*3+j], zf[i*3+j], zg[i*3+j], zo[i*3+j], o[i*3+j], f[i*3+j], it[i*3+j]);
				}
				
			else{
				
				if(i == 0)
					lstm(w_x, w_m, w_c,output,container4[thread*100000+i*3+i+j],container3[thread*100000+i*3+j], b_x, size, container, w_fx, w_fm, w_fc, b_fx, container2, w_cx, w_cm, b_cx, container3[thread*100000+3+i*3+j], w_ox, w_om, w_oc, b_ox, container4[thread*100000+4+j],zi[i*3+j], zf[i*3+j], zg[i*3+j], zo[i*3+j], o[i*3+j], f[i*3+j], it[i*3+j]);
				else
					lstm(w_x, w_m, w_c,output,container4[thread*100000+i*3+i+j],container3[thread*100000+i*3+j], b_x, size, container, w_fx, w_fm, w_fc, b_fx, container2, w_cx, w_cm, b_cx, container3[thread*100000+3+i*3+j], w_ox, w_om, w_oc, b_ox, container4[thread*100000+(i+1)*3+i+j+1],zi[i*3+j], zf[i*3+j], zg[i*3+j], zo[i*3+j], o[i*3+j], f[i*3+j], it[i*3+j]);
			}
			
			if(i == 0){
				if(j == 0)
					dropout(0.3, flag1, mask1, container4[thread*100000+4+j],output,size);
				else if(j == 1)
					dropout(0.3, flag2, mask2, container4[thread*100000+4+j],output,size);
				else
					dropout(0.3, flag3, mask3, container4[thread*100000+4+j],output,size);
				}
			
			else{
				if(j == 0)
					dropout(0.3, flag1, mask1, container4[thread*100000+(i+1)*3+i+j+1],output,size);
				else if(j == 1)
					dropout(0.3, flag2, mask2, container4[thread*100000+(i+1)*3+i+j+1],output,size);
				else
					dropout(0.3, flag3, mask3, container4[thread*100000+(i+1)*3+i+j+1],output,size);
				}
			if(j==2){
				dense(size, size-18, output, w1_dense, b1_dense, 0, output1[i]);
				
				dense(size, 18, output, w2_dense, b2_dense, 0, output2[i]);
			}
			
			
			
		}
		 
		flag1 = 1;
		flag2= 1;
		flag3 = 1;
		
	}
	
	/*backprppagation*/
	
	for(i = 0; i < 34; i++){
		if(i <= 12){
			if(i == 11)
				matrix[i] = (float*)calloc(size*(size-18),sizeof(float));
				
			else if(i == 12)
				matrix[i] = (float*)calloc(size*18,sizeof(float));
			else
				matrix[i] = (float*)calloc(size*size,sizeof(float));
			}
		
		else{
			
			if(i == 29)
				matrix[i] = (float*)calloc(18,sizeof(float));
				
			else if(i == 30)
				matrix[i] = (float*)calloc(size-18,sizeof(float));
			else
				matrix[i] = (float*)calloc(size,sizeof(float));
			}
	}
	
	
	matrix[34] = w_ox;
	matrix[35] = w_cx;
	matrix[36] = w_fx;
	matrix[37] = w_x;
	matrix[38] = w_om;
	matrix[39] = w_cm;
	matrix[40] = w_fm;
	matrix[41] = w_m;
	matrix[42] = w_oc;
	matrix[43] = w_fc;
	matrix[44] = w_c;
	matrix[45] = w1_dense;
	matrix[46] = w2_dense;
	
	
	
	for(i = lunghezza_brano-1; i >= 0; i--){
		
		for(j = 2; j>=0; j--){
			
			if(j == 2)
				flag = 0;
			else
				flag = 1;
			
			if(i == lunghezza_brano-1){
				if(j == 2){
					
					matrix[57] = output1[i];
					matrix[58] = output2[i];
					matrix[59] = y1[i];
					matrix[60] = y2[i];
					
					
				}
				
				else{
					
					free(matrix[25]);
					free(matrix[26]);
					free(matrix[27]);
					free(matrix[28]);
					
					matrix[25] = matrix[17];
					matrix[26] = matrix[18];
					matrix[27] = matrix[19];
					matrix[28] = matrix[20];
					
					matrix[17] = (float*)calloc(size,sizeof(float));
					matrix[18] = (float*)calloc(size,sizeof(float));
					matrix[19] = (float*)calloc(size,sizeof(float));
					matrix[20] = (float*)calloc(size,sizeof(float));
					
					/*salvare i dw e db [0-16] + dentro vettori e risettare questi a 0*/
					save_params(matrix,dw,db,thread);
					
				}
				
				free(matrix[31]);
				free(matrix[32]);
					
				matrix[31] = (float*)calloc(size,sizeof(float));
				matrix[32] = (float*)calloc(size,sizeof(float));
				
				if(j == 0)
					dropout(0.3, flag1, mask1, container4[thread*100000+(i+1)*3+i+j+1],output,size);
				else if(j == 1)
					dropout(0.3, flag2, mask2, container4[thread*100000+(i+1)*3+i+j+1],output,size);
				else
					dropout(0.3, flag3, mask3, container4[thread*100000+(i+1)*3+i+j+1],output,size);
				
				
				matrix[51] = output;
				matrix[52] = container3[thread*100000+3+i*3+j];
				
				if(j == 1)
					dropout(0.3, flag2, mask2, container4[thread*100000+(i+1)*3+i+j],outputsec,size);
				else if(j == 2)
					dropout(0.3, flag3, mask3, container4[thread*100000+(i+1)*3+i+j],outputsec,size);
				else
					outputsec = container4[thread*100000+(i+1)*3+i+j];
					
				matrix[53] = outputsec;
				matrix[54] = o[i*3+j];
				matrix[55] = container4[thread*100000+(i+1)*3+i+j-3];
				matrix[56] = container3[thread*100000+3+i*3+j-3];
				
				matrix[47] = zo[i*3+j];
				matrix[48] = zi[i*3+j];
				matrix[49] = zf[i*3+j];
				matrix[50] = zg[i*3+j];
				
				matrix[61] = it[i*3+j];
				
				//printf("thread: %d\n %d\n j: %d\n",thread,i,j);
				lstm_backpropagation(flag,matrix,tempo[0+4*(-j+2)],tempo[1+4*(-j+2)],tempo[2+4*(-j+2)],tempo[3+4*(-j+2)],dc_t1[j]);
				
				
			}
			
			else{
				
				save_params(matrix,dw,db,thread);
				
				if(i == lunghezza_brano -2 && j == 2){
					free(matrix[21]);
					free(matrix[22]);
					free(matrix[23]);
					free(matrix[24]);
					free(matrix[33]);
				}
				
				matrix[21] = tempo[0+4*(-j+2)];
				matrix[22] = tempo[3+4*(-j+2)];
				matrix[23] = tempo[2+4*(-j+2)];
				matrix[24] = tempo[1+4*(-j+2)];
				
				if(j == 2){
					
					free(matrix[25]);
					free(matrix[26]);
					free(matrix[27]);
					free(matrix[28]);
					free(matrix[17]);
					free(matrix[18]);
					free(matrix[19]);
					free(matrix[20]);
					
					matrix[25] = (float*)calloc(size,sizeof(float));
					matrix[26] = (float*)calloc(size,sizeof(float));
					matrix[27] = (float*)calloc(size,sizeof(float));
					matrix[28] = (float*)calloc(size,sizeof(float));
					
					matrix[17] = (float*)calloc(size,sizeof(float));
					matrix[18] = (float*)calloc(size,sizeof(float));
					matrix[19] = (float*)calloc(size,sizeof(float));
					matrix[20] = (float*)calloc(size,sizeof(float));
					
					matrix[57] = output1[i];
					matrix[58] = output2[i];
					matrix[59] = y1[i];
					matrix[60] = y2[i];
					
				}
				
				else{
					
					free(matrix[25]);
					free(matrix[26]);
					free(matrix[27]);
					free(matrix[28]);
					
					matrix[25] = matrix[17];
					matrix[26] = matrix[18];
					matrix[27] = matrix[19];
					matrix[28] = matrix[20];
					
					matrix[17] = (float*)calloc(size,sizeof(float));
					matrix[18] = (float*)calloc(size,sizeof(float));
					matrix[19] = (float*)calloc(size,sizeof(float));
					matrix[20] = (float*)calloc(size,sizeof(float));
					
					 
					
					
				}
				
				    
			   
				
				
				free(matrix[31]);
				free(matrix[32]);
				
				matrix[31] = (float*)calloc(size,sizeof(float));
				matrix[32] = (float*)calloc(size,sizeof(float));
				matrix[33] = f[i*3+j+3];
				
				if(j == 0)
					dropout(0.3, flag1, mask1, container4[thread*100000+(i+1)*3+i+j+1],output,size);
				else if(j == 1)
					dropout(0.3, flag2, mask2, container4[thread*100000+(i+1)*3+i+j+1],output,size);
				else
					dropout(0.3, flag3, mask3, container4[thread*100000+(i+1)*3+i+j+1],output,size);
				
				
				matrix[51] = output;
				matrix[52] = container3[thread*100000+3+i*3+j];
				
				if(j == 1)
					dropout(0.3, flag2, mask2, container4[thread*100000+(i+1)*3+i+j],outputsec,size);
				else if(j == 2)
					dropout(0.3, flag3, mask3, container4[thread*100000+(i+1)*3+i+j],outputsec,size);
				else
					outputsec = container4[thread*100000+(i+1)*3+i+j];	
				
					
					
				
				matrix[53] = outputsec;
				matrix[54] = o[i*3+j];
				matrix[55] = container4[thread*100000+(i+1)*3+i+j-3];
				matrix[56] = container3[thread*100000+3+i*3+j-3];
				
				
				matrix[47] = zo[i*3+j];
				matrix[48] = zi[i*3+j];
				matrix[49] = zf[i*3+j];
				matrix[50] = zg[i*3+j];
				
				matrix[61] = it[i*3+j];
				
				
				//printf("thread: %d\n i: %d\n j: %d\n",thread,i,j);
				lstm_backpropagation(flag,matrix,tempo[0+4*(-j+2)],tempo[1+4*(-j+2)],tempo[2+4*(-j+2)],tempo[3+4*(-j+2)],dc_t1[j]);
			}
			
			
			
		}
		
	}
	
	
	clipping_gradients(0.5,dw,db);
	for(i = 0; i < 13; i++){
		if (i == 11){
			for(j = 0; j < size-18; j++){
				for(k = 0; k < size; k++){
					dw_t[i][j*(size-18)+k]+=dw[i][j*(size-18)+k];
				}
			}
		}
		
		else if (i == 12){
			for(j = 0; j < 18; j++){
				for(k = 0; k < size; k++){
					dw_t[i][j*(18)+k]+=dw[i][j*(18)+k];
				}
			}
		}
		
		else{
			for(j = 0; j < size; j++){
				for(k = 0; k < size; k++){
					dw_t[i][j*(size)+k]+=dw[i][j*(size)+k];
				}
			}
		}
	}
	
	
	for(i = 0; i < 6; i++){
		if (i == 4){
			for(j = 0; j < size-18; j++){
				db_t[i][j]+=db[i][j];
			}
		}
		
		else if (i == 5){
			for(j = 0; j < 18; j++){
				db_t[i][j]+=db[i][j];
			}
		}
		
		else{
			for(j = 0; j < size; j++){
				db_t[i][j]+=db[i][j];
			}
		}
	}
	
	free_matrix(dw,13);
	free_matrix(db,6);
	
	
	matrix[21] = NULL;
	matrix[22] = NULL;
	matrix[23] = NULL;
	matrix[24] = NULL;
	matrix[33] = NULL;
	matrix[34] = NULL;
	matrix[35] = NULL;
	matrix[36] = NULL;
	matrix[37] = NULL;
	matrix[38] = NULL;
	matrix[39] = NULL;
	matrix[40] = NULL;
	matrix[41] = NULL;
	matrix[42] = NULL;
	matrix[43] = NULL;
	matrix[44] = NULL;
	matrix[45] = NULL;
	matrix[46] = NULL;
	matrix[47] = NULL;
	matrix[48] = NULL;
	matrix[49] = NULL;
	matrix[50] = NULL;
	matrix[51] = NULL;
	matrix[52] = NULL;
	matrix[53] = NULL;
	matrix[54] = NULL;
	matrix[55] = NULL;
	matrix[56] = NULL;
	matrix[57] = NULL;
	matrix[58] = NULL;
	matrix[59] = NULL;
	matrix[60] = NULL;
	matrix[61] = NULL;
	
	/*deallocation*/
	free(mask1);
	free(mask2);
	free(mask3);
	free(output);
	free(container);
	free(container2);
	free_matrix(dc_t1,3);
	free(y1[lunghezza_brano-1]);
	free(y2[lunghezza_brano-1]);
	free_matrix(tempo,12);
	free_matrix(zi,3*lunghezza_brano);
	free_matrix(zf,3*lunghezza_brano);
	free_matrix(zg,3*lunghezza_brano);
	free_matrix(zo,3*lunghezza_brano);
	free_matrix(o,3*lunghezza_brano);
	free_matrix(f,3*lunghezza_brano);
	free_matrix(it,3*lunghezza_brano);
	free_matrix(output1,lunghezza_brano);
	free_matrix(output2,lunghezza_brano);
	
	free_matrix(matrix,62);
	
	
	
	for(i = 0; i < (lunghezza_brano*4+3); i++){
		free(container3[i+thread*100000]);
		if((i+1)%4!=0){
			free(container4[i+thread*100000]);
		}
	}
	
	
}



void lstm_backpropagation(int flag, float** matrix,float* c1, float* c2, float* c3, float* c4, float* dc_t1){	
	int i,j;
	
	float* dw_oxt = matrix[0];
	float* dw_cxt = matrix[1];
	float* dw_fxt = matrix[2];
	float* dw_ixt = matrix[3];
	float* dw_omt = matrix[4];
	float* dw_cmt = matrix[5];
	float* dw_fmt = matrix[6];
	float* dw_imt = matrix[7];
	float* dw_oct = matrix[8];
	float* dw_fct = matrix[9];
	float* dw_ict = matrix[10];
	float* dw1 = matrix[11];
	float* dw2 = matrix[12];
	
	float* db_ot = matrix[13];
	float* db_gt = matrix[14];
	float* db_it = matrix[15];
	float* db_ft = matrix[16];
	
	float* dz_ot = matrix[17];
	float* dz_it = matrix[18];
	float* dz_ft = matrix[19];
	float* dz_gt = matrix[20];
	
	float* dz_ot1 = matrix[21];
	float* dz_it1 = matrix[22];
	float* dz_ft1 = matrix[23];
	float* dz_gt1 = matrix[24];
	
	float* dz_otup = matrix[25];
	float* dz_itup = matrix[26];
	float* dz_ftup = matrix[27];
	float* dz_gtup = matrix[28];
	
	float* db2 = matrix[29];
	float* db1 = matrix[30];
	
	float* dm_t = matrix[31];
	float* dc_t = matrix[32];
	float* f_t1 = matrix[33];
	
	float* w_oxt = matrix[34];
	float* w_cxt = matrix[35];
	float* w_fxt = matrix[36];
	float* w_ixt = matrix[37];
	float* w_omt = matrix[38];
	float* w_cmt = matrix[39];
	float* w_fmt = matrix[40];
	float* w_imt = matrix[41];
	float* w_oct = matrix[42];
	float* w_fct = matrix[43];
	float* w_ict = matrix[44];
	
	float* w1 = matrix[45];
	float* w2 = matrix[46];

	float* z_ot = matrix[47];
	float* z_it = matrix[48];
	float* z_ft = matrix[49];
	float* z_gt = matrix[50];
	
	float* m_t = matrix[51];
	float* c_t = matrix[52];
	float* x_t = matrix[53];
	float* o_t = matrix[54];
	float* c_minust = matrix[55];
	float* m_minust = matrix[56];
	float* out1 = matrix[57];
	float* out2 = matrix[58];
	float* y1 = matrix[59];
	float* y2 = matrix[60];
	
	float* i_t = matrix[61];
	
	
		
	if(!flag){
		
		for(i = 0; i < size; i++){
			
			if(i < 18)
				db2[i] = out2[i]-y2[i];
			
			else if(i < size-18)
				db1[i] = out1[i]-y1[i];
			
			if(i < size-18){
				for(j = 0; j < size; j++){
					if(i < 18)
						dw2[i*size + j] = (out2[i]-y2[i])*m_t[j];
					
					
					dw1[i*size + j] = (out1[i]-y1[i])*m_t[j];
					
					if(i < 18)
						dm_t[j] += (out2[i]-y2[i])*w2[i*size+j] + (out1[i]-y1[i])*w1[i*size+j];

					else
						dm_t[j] += (out1[i]-y1[i])*w1[i*size+j];
						
					dm_t[j] += dz_ot1[i]*w_omt[i*size+j] + dz_ft1[i]*w_fmt[i*size+j] + dz_gt1[i]*w_cmt[i*size+j] + dz_it1[i]*w_imt[i*size+j]; 
				}
			}
			
			else{
				for(j = 0; j < size; j++){
					dm_t[j] += dz_ot1[i]*w_omt[i*size+j] + dz_ft1[i]*w_fmt[i*size+j] + dz_gt1[i]*w_cmt[i*size+j] + dz_it1[i]*w_imt[i*size+j]; 
				}
			}
			
		}
		
	}
	
	
	else{
		for(i = 0; i < size; i++){
			
			for(j = 0; j < size; j++){
				
				dm_t[j] += dz_otup[i]*w_oxt[i*size+j] + dz_gtup[i]*w_cxt[i*size+j] + dz_ftup[i]*w_fxt[i*size+j] + dz_itup[i]*w_ixt[i*size+j];
					
				dm_t[j] += dz_ot1[i]*w_omt[i*size+j] + dz_ft1[i]*w_fmt[i*size+j] + dz_gt1[i]*w_cmt[i*size+j] + dz_it1[i]*w_imt[i*size+j]; 
			}
			
		}
	}
	
	
	for(i = 0; i < size; i++){
		dc_t[i] = dm_t[i]*o_t[i]*(1-(((exp(c_t[i])-exp(-c_t[i]))/(exp(c_t[i])+exp(-c_t[i])))*((exp(c_t[i])-exp(-c_t[i]))/(exp(c_t[i])+exp(-c_t[i])))));
		dc_t[i]+=dc_t1[i]*f_t1[i];
		for(j = 0; j < size; j++){
			dc_t[i]+=dz_ot1[j]*w_oct[j*size+i];
			dc_t[i]+=dz_ft1[j]*w_fct[j*size+i];
			dc_t[i]+=dz_it1[j]*w_ict[j*size+i];
		}
		dc_t1[i] = dc_t[i];
	}
	
	
	
	for(i = 0; i < size; i++){
		dz_ot[i] = dm_t[i]*((exp(c_t[i]) - exp(-c_t[i])) / (exp(c_t[i]) + exp(-c_t[i])))*((1/(1+exp(-z_ot[i])))*(1-(1/(1+exp(-z_ot[i])))));
		db_ot[i] = dz_ot[i];
		c1[i] = dz_ot[i];
		for(j = 0; j < size; j++){
			dw_oxt[i*size+j] = dz_ot[i]*x_t[j];
			dw_oct[i*size+j] = dz_ot[i]*c_t[j];
			dw_omt[i*size+j] = dz_ot[i]*m_minust[j];
		}
	}
	
	
	
	for(i = 0; i < size; i++){
		
		dz_ft[i] = dc_t[i]*c_minust[i]*((1/(1+exp(-z_ft[i])))*(1-(1/(1+exp(-z_ft[i])))));
		db_ft[i] = dz_ft[i];
		
		
		
		c3[i] = dz_ft[i];
		
		
		
		dz_it[i] = dc_t[i]*((exp(z_gt[i]) - exp(-z_gt[i])) / (exp(z_gt[i]) + exp(-z_gt[i])))*((1/(1+exp(-z_it[i])))*(1-(1/(1+exp(-z_it[i])))));
		db_it[i] = dz_it[i];
		c4[i] = dz_it[i];
		
		dz_gt[i] = dc_t[i]*i_t[i]*(1-(((exp(z_gt[i])-exp(-z_gt[i]))/(exp(z_gt[i])+exp(-z_gt[i])))*((exp(z_gt[i])-exp(-z_gt[i]))/(exp(z_gt[i])+exp(-z_gt[i])))));
		db_gt[i] = dz_gt[i];
		c2[i] = dz_gt[i];
		
		for(j = 0; j < size; j++){
			dw_cxt[i*size+j] = dz_gt[i]*x_t[j];
			dw_cmt[i*size+j] = dz_gt[i]*m_minust[j];
			dw_fxt[i*size+j] = dz_ft[i]*x_t[j];
			dw_fmt[i*size+j] = dz_ft[i]*m_minust[j];
			dw_fct[i*size+j] = dz_ft[i]*c_minust[j];
			dw_ixt[i*size+j] = dz_it[i]*x_t[j];
			dw_imt[i*size+j] = dz_it[i]*m_minust[j];
			dw_ict[i*size+j] = dz_it[i]*c_minust[j];
		}
	}
	
	
	
}

void save_params(float** matrix, float** dw, float** db,int thread){
	int i,j,k;
	for(i = 0; i < 13; i++){
		for(j = 0; j < size; j++){
			for(k = 0; k < size; k++){
				if(i == 11){
					if(j < size-18){
						dw[i][j*size+k] += matrix[i][j*size+k];
						matrix[i][j*size+k] = 0;
					}
				}
				
				else if(i == 12){
					if(j < 18){
						dw[i][j*size+k] += matrix[i][j*size+k];
						matrix[i][j*size+k] = 0;
					}
				}
				
				else{
					dw[i][j*size+k] += matrix[i][j*size+k];
					matrix[i][j*size+k] = 0;
				}
				
			}
		}
	}
	
	for(i = 0; i < 6; i++){
		for(j = 0; j < size; j++){
			if(i == 4){
				if(j < size-18){
					db[i][j] = matrix[30][j];
					matrix[30][j] = 0;
				}
			}
			
			else if(i == 5){
				if(j < 18){
					db[i][j] = matrix[29][j];
					matrix[29][j] = 0;
				}
			}
			
			else{
				db[i][j] = matrix[13+i][j];
				matrix[13+i][j] = 0;
			}
			
		}
		
			
	}
	
}




void clipping_gradients(float thereshold,float** dw,float** db){
	int k,i,j;
	float sum = 0;
	for(k = 0; k < 13; k++){
		if(k == 11){
			for(i = 0; i < size-18; i++){
				for(j = 0; j < size; j++){
					sum += dw[k][i*(size-18)+j]*dw[k][i*(size-18)+j];
					}
				}
			}
		else if(k == 12){
			for(i = 0; i < 18; i++){
				for(j = 0; j < size; j++){
					sum += dw[k][i*(18)+j]*dw[k][i*(18)+j];
				}
			}
		}
		
		else{
			for(i = 0; i < size; i++){
				for(j = 0; j < size; j++){
					sum += dw[k][i*(size)+j]*dw[k][i*(size)+j];
				}
			}
		}
	}
	
	for(k = 0; k < 6; k++){
		if(k == 4){
			for(i = 0; i < size-18; i++){
				sum += db[k][i]*db[k][i];
			}
		}
		else if(k == 5){
			for(i = 0; i < 18; i++){
				sum += db[k][i]*db[k][i];
			}
		}
		
		else{
			for(i = 0; i < size; i++){
				sum += db[k][i]*db[k][i];
			}
		}
	}
	
	sum = sqrtf(sum);
	
	if(sum > thereshold){
		for(k = 0; k < 13; k++){
			if(k == 11){
				for(i = 0; i < size-18; i++){
					for(j = 0; j < size; j++){
						dw[k][i*(size-18)+j] *= thereshold/sum;
						}
					}
				}
			else if(k == 12){
				for(i = 0; i < 18; i++){
					for(j = 0; j < size; j++){
						dw[k][i*(18)+j] *= thereshold/sum;;
					}
				}
			}
			
			else{
				for(i = 0; i < size; i++){
					for(j = 0; j < size; j++){
						dw[k][i*(size)+j] *= thereshold/sum;;
					}
				}
			}
		}
		
		for(k = 0; k < 6; k++){
			if(k == 4){
				for(i = 0; i < size-18; i++){
					db[k][i] *= thereshold/sum;;
				}
			}
			else if(k == 5){
				for(i = 0; i < 18; i++){
					db[k][i] *= thereshold/sum;;
				}
			}
			
			else{
				for(i = 0; i < size; i++){
					db[k][i] *= thereshold/sum;;
					}
			}
		}
	}
}
