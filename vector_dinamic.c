#include "vector_dinamic.h"
#include <malloc.h>

VectorDinamic* creeaza(int cp) {
	VectorDinamic* v = (VectorDinamic*)malloc(sizeof(VectorDinamic));

	v->cp = cp;
	v->e = (void**)malloc(cp * sizeof(void*));
	v->n = 0;
	return v;
}


void distruge(VectorDinamic* v) {
	free(v->e);
	free(v);
}


void redim(VectorDinamic* v) {
	void** eNou = (void*)malloc(2 * v->cp * sizeof(void*));

	for (int i = 0; i < v->n; i++)
		eNou[i] = v->e[i];

	v->cp = 2 * v->cp;

	free(v->e);

	v->e = eNou;
}


int dim(VectorDinamic* v) {
	return v->n;
}


void* element(VectorDinamic* v, int i) {
	return v->e[i];
}


void adaugaSfarsit(VectorDinamic* v, void* e) {
	if (v->n == v->cp)
		redim(v);
	v->e[(v->n)++] = e;
}
