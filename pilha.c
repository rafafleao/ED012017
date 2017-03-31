#include <stdio.h>

	typedef struct{
		int top;
		int vetor[10];
	}Pilha;

void Push(Pilha*p, int x){
		p->vetor[p->top] = x;
		p->top = p->top+1;
}

int Pop(Pilha*p){
	
	p->top = p->top-1;
	return p->vetor[p->top];
}

int main(){
	
	int vetor[10] = {1,2,3,4,5,6,7,8,9,10};
	Pilha p; 
	p.top=0;
	int i;
	
	for(i=0;i<10;i++){
	Push(&p,vetor[i]);
	}
	
	for(i=0;i<10;i++){
		printf("%d\n",Pop(&p));
	}
	
	
	return 0;
	
}
