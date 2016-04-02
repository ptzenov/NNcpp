#include "NN_io.hpp"

#include <stdio.h>
#include <stdlib.h>


void readNetwork_t(const char* filename, Neuron* &neurons, float* &weights_mtx, int&N, int&M)
{
	FILE* fp = fopen(filename, "r");
	char message[200];

	if (fp == NULL)
	{
		sprintf(message, "Error opening file %s", filename);
		log_msg(stderr, message,__FILE__,__LINE__);
		exit(EXIT_FAILURE);
	}

	fscanf(fp,"%d",&N);
	fscanf(fp,"%d",&M);

	neurons = new Neuron[N];
	// read and initialize the neurons
	for(int i = 0 ; i < N ;i ++)
	{
		float line[7];

		for(int f = 0 ; f<7; f++)
			fscanf(fp,"%f",line+f);
		neurons[i].fromFloatArray(line);

	}

	// TODO: the weights matrix will probably be small! Rework with sparse matrices!
	// the weights_mtx pointer is PASSED BY reference! it addresses memory on the HEAP!
	weights_mtx = new float[N*N];
	int nconn; int out_idx; float w;
	// for each neuron
	for (int i = 0 ; i < N; i ++)
	{
		// read how many outgoing synapses does it have
		fscanf(fp,"%d",&nconn);

		// for each synapse
		for(int j = 0; j < 2*nconn ; j+=2)
		{
			// read the target neuron
			fscanf(fp,"%d",&out_idx);
			// read the weight
			fscanf(fp,"%f",&w);
			weights_mtx[out_idx+N*i] = w;
		}
	}

	fclose(fp);

}

void readNetwork_b(const char* filename, Neuron* &neurons, float* &weights_mtx, int &N, int &M)
{

	FILE* fp = fopen(filename, "rb");
	char message[200];

	if (fp == NULL)
	{
		sprintf(message, "Error opening file %s", filename);
		log_msg( stderr, message,__FILE__,__LINE__);
		exit(EXIT_FAILURE);
	}

	fread(&N,sizeof(int),1,fp);
	fread(&M,sizeof(int),1,fp);

	// read and initialize the neurons
	neurons = new Neuron[N];
	for(int i = 0 ; i < N ;i ++)
	{
		float line[7];
		fread(line,sizeof(float),7,fp);
		neurons[i].fromFloatArray(line);
	}

	// TODO: the weights matrix will probably be small! Rework with sparse matrices!
	weights_mtx = new float[N*N];
	int nconn; int out_idx; float w;
	// for each neuron
	for (int i = 0 ; i < N; i ++)
	{
		// read how many outgoing synapses does it have
		fread(&nconn,sizeof(int),1,fp);
		// for each synapse
		for(int j = 0; j < 2*nconn ; j+=2)
		{
			// read the target neuron
			fread(&out_idx,sizeof(int),1,fp);
			// read the weight
			fread(&w, sizeof(float),1,fp);
			weights_mtx[out_idx+N*i] = w;
		}
	}
	fclose(fp);
}
void writeNetwork_t(const char* filename, Neuron const * neurons, float const * weights, const int& N, const int& M)
{
	FILE* fp = fopen(filename,"w");
	char message[200];
	if(fp ==NULL){
		sprintf(message,"Error opening file %s for writing.",filename);
		log_msg(stderr,message,__FILE__,__LINE__);
		exit(EXIT_FAILURE);
	}

	fprintf(fp,"%d\n",N);
	fprintf(fp,"%d\n",M);

	for(int i = 0; i< N;i++){
		Neuron n = neurons[i];
		float characteristics[NPROPS];
		n.toFloatArray(characteristics);
		for(int j = 0 ; j<NPROPS-2; j++)
			fprintf(fp,"%d ",(int)characteristics[j]);

		fprintf(fp,"%.2f ", characteristics[NPROPS-2]);
		fprintf(fp,"%.2f ", characteristics[NPROPS-1]);
		fprintf(fp,"\n");
	}

	for(int i =0 ; i<N; i++){
		// count how many outgoing synapses are there
		// TODO fix! extra counting unnecessary!
		int i_conns =0;

		for(int j = 0 ; j<N; j++)
			if(weights[j+N*i] != 0)
				i_conns++;

		fprintf(fp,"%d ",i_conns);
		for (int j = 0;j < N ; j++)
			if(weights[j+N*i] != 0.0){
				fprintf(fp,"%d ",j);
				fprintf(fp,"%.2f ",weights[j+N*i]);
			}
		fprintf(fp,"\n");

	}
	fclose(fp);

}



void writeNetwork_b(const char* filename, Neuron const * neurons, float const * weights, const int & N, const int & M)
{
	// TODO: implement me!
	int i = 1;
}


