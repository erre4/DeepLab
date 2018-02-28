#ifndef BACKPROP_H
#define BACKPROP_H

struct BackElem
{
  double **d_w;
  double *err;
};

typedef struct BackElem BackElem;

#endif
