//tip de data generic (pentru moment este intreg)
typedef struct {
	//capacitate
	int cp;
	//dimensiune
	int n;
	//elemente
	void** e;
} VectorDinamic;


//constructor
VectorDinamic* creeaza(int cp);

//destructor
void distruge(VectorDinamic* v);

void redim(VectorDinamic* v);

//dimensiunea vectorului (numar de elemente)
int dim(VectorDinamic* v);

//elementul al i-lea (1 <= i <= numar de elemente)
void* element(VectorDinamic* v, int);

//adaugare la sfarsit
void adaugaSfarsit(VectorDinamic* v, void* e);