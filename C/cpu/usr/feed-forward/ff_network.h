#ifndef __FF_NETWORK_H__
#define __FF_NETWORK_H__

struct FFNetwork
{
  double ***w;
  double **b;
  int *reg_len_per_layer;
  int **regularization;
  int *activations;
};


typedef struct FFNetwork FFNetwork;
#endif
