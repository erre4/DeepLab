#ifndef __CN_NETWORK_H__
#define __CN_NETWORK_H__

/*Description
 * there will be only one network as global variable with this parametres
 * @double*** w:
 * 			first dimension: len of layers -1, second and third dimension the size of the matrix of weights for each layer
 * @double** b: 
 * 			first dimension: number of layers - 1, second dimension: number of feature maps
 * @int** regularization:
 * 			first dimension number of layers - 1, second dimension: number of regularization thecniques per layer
 * @int* neurons:
 * 			the length of neurons = number of layers and for each layer neurons[i] contains number of total neurons for that layer
 * @int* reg_len_per_layer:
 * 			number of columns of regularization per each row
 * @int* activation:
 * 			first dimension number of layers - 1, values: type of activation function for layer
 * @int* feature_maps:
 * 			 number of feature maps per layer (for the input layer are the channels), len = number of layers
 * @int* pooling:
 * 			 pooling type per layer, len = number of layers -1 
 * @int* padding:
 * 			 padding type per layer
 * @int** kernel_size:
 * 			 kernel size per layer, len = number of layers -1  has 2 columns per row
 * @int* stride:
 * 			 stride per layer, len = number of layers -1 
 * */


struct CNNetwork
{
  double ***w;
  double **b;
  int **regularization;
  int *neurons;
  int *reg_len_per_layer;
  int *activation;
  int *feature_maps;
  int *pooling;
  int *padding;
  int **kernel_size;
  int *stride;

};


typedef struct CNNetwork CNNetwork;
#endif
