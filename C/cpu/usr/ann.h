#ifndef ANN_H
#define ANN_H

/* Description
 * will be initialized as global variable
 * @int epochs
 * 		number of epochs we want to run
 * @int runned_epochs
 * 		number of epochs actually runned
 * @int mini_batch_size
 * 		size of a mini_batch
 * @int training_size
 * 		size of the training_set
 * @int test_size
 * 		size of the test_set
 * @int validation_size
 * 		size of the validation_Set
 * @int input_neurons:
 * 		number of input neurons
 * @int output_neurons
 * 		number of output neurons
 * @int hidden layers
 * 		number of hidden layers
 * 
 * */
struct AnnElem
{
  int epochs,
    runned_epochs,
    mini_batch_size,
    training_size,
    test_size,
    validation_size,
    input_neurons, output_neurons, hidden_layers, cost_function;
};

typedef struct AnnElem AnnElem;

#endif
