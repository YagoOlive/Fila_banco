#include<stdio.h>
#include<stdlib.h>

#define TEMPO_FUNCIONAMENTO 5

#define NUM_CLIENTES_MAX 5 
#define NUM_CLIENTES_MIN 3
#define VALOR_MAX 10000
#define VALOR_MIN 100


// Estrutura de Dados Fila Din?mica
typedef struct TipoCelula *TipoApontador; 

typedef struct TipoCaixa { 
	int clientesAtendidos;
	float valorSaque;
	float valorDeposito;
	float valorPagamento;
} TipoCaixa;

typedef struct TipoItem{
	int cod;
	float valor; //1 a 10000
	int op; //0- Saque; 1- Depósito; 2- Pagamento
}TipoItem;

typedef struct TipoCelula {
	TipoItem Item;
	TipoApontador Prox;
} TipoCelula; 

typedef struct TipoFila {
	TipoApontador Frente, Tras;
	int tamanho;
}TipoFila;

// Fun??es de manipula??o da Fila Din?mica
void FFVazia(TipoFila *Fila ) { 
	Fila ->Frente = (TipoApontador) malloc(sizeof(TipoCelula )); 
	Fila ->Tras = Fila ->Frente; 
	Fila ->Frente ->Prox = NULL; 
	Fila->tamanho=0;
}

int Vazia(TipoFila Fila ) { 
	return ( Fila.Frente == Fila.Tras) ;
}

void Enfileira (TipoItem x, TipoFila *Fila ) { 
	Fila ->Tras ->Prox = (TipoApontador) malloc(sizeof(TipoCelula )); 
	Fila ->Tras = Fila ->Tras ->Prox;
	Fila ->Tras ->Item = x; 
	Fila ->Tras ->Prox = NULL; 
	Fila->tamanho++;
}

void Desenfileira(TipoFila *Fila , TipoItem *Item) { 
	TipoApontador q; 
	if (Vazia( *Fila ) ) { 
		printf ( "Erro fila esta vazia\n" ) ; return;
	} 
	q = Fila ->Frente; 
	Fila ->Frente = Fila ->Frente ->Prox; 
	*Item = Fila ->Frente ->Item; 
	free(q);
	Fila->tamanho--; 
}

void exibe (TipoFila fila){
	TipoApontador aux=fila.Frente->Prox;
	while(aux!=NULL){
		printf("\n%d", aux->Item.cod);
		printf("\n%d", aux->Item.op);
		printf("\n%f", aux->Item.valor);	
		aux=aux->Prox;
	}
}

main(){
	
	TipoItem item;
    TipoFila caixa1, caixa2, caixa3;
    TipoCaixa caixaB1, caixaB2, caixaB3;
    
    caixaB1.clientesAtendidos=0;
    caixaB1.valorDeposito=0;
    caixaB1.valorPagamento=0;
    caixaB1.valorSaque=0;
   
    caixaB2.clientesAtendidos=0;
    caixaB2.valorDeposito=0;
    caixaB2.valorPagamento=0;
    caixaB2.valorSaque=0;
    
    caixaB3.clientesAtendidos=0;
    caixaB3.valorDeposito=0;
    caixaB3.valorPagamento=0;
    caixaB3.valorSaque=0;
   
    FFVazia(&caixa1);
    FFVazia(&caixa2);
    FFVazia(&caixa3);
   

    int t=0, num_clientes;

    
    while( t < TEMPO_FUNCIONAMENTO || (!Vazia(caixa1) || !Vazia(caixa2) || !Vazia(caixa3))) {
        printf("Tempo: %d\n", t);
		int  i=0;
		if(t < TEMPO_FUNCIONAMENTO){
				
                num_clientes = rand() % (NUM_CLIENTES_MAX - NUM_CLIENTES_MIN + 1) + NUM_CLIENTES_MIN;

                for (int j = 0; j < num_clientes; j++) {
                    item.cod = rand() % 1000 + 1;
                    item.op = rand() % 3;
                    item.valor = rand() % (VALOR_MAX - VALOR_MIN + 1) + VALOR_MIN;

                    if (caixa1.tamanho <= caixa2.tamanho && caixa1.tamanho <= caixa3.tamanho) {
                        Enfileira(item, &caixa1);
                    } else if (caixa2.tamanho <= caixa1.tamanho && caixa2.tamanho <= caixa3.tamanho) {
                        Enfileira(item, &caixa2);
                    } else {
                        Enfileira(item, &caixa3);
                    }
                }
            
		}
		if(!Vazia(caixa1)){

			Desenfileira(&caixa1, &item);
			caixaB1.clientesAtendidos++;
			if(item.op== 0){
				caixaB1.valorSaque+=item.valor;
			}
        	if(item.op== 1){
				caixaB1.valorDeposito+=item.valor;
			}
        	if(item.op== 2){
				caixaB1.valorPagamento+=item.valor;
			}
        
	
			
		}
		if(!Vazia(caixa2)){
			
			Desenfileira(&caixa2, &item);
			caixaB2.clientesAtendidos++;
			if(item.op== 0){
				caixaB2.valorSaque+=item.valor;
			}
        	if(item.op== 1){
				caixaB2.valorDeposito+=item.valor;
			}
        	if(item.op== 2){
				caixaB2.valorPagamento+=item.valor;
			}
	    }
	    if(!Vazia(caixa3)){
			Desenfileira(&caixa3, &item);
			caixaB3.clientesAtendidos++;
			if(item.op== 0){
				caixaB3.valorSaque+=item.valor;
			}
        	if(item.op== 1){
				caixaB3.valorDeposito+=item.valor;
			}
        	if(item.op== 2){
				caixaB3.valorPagamento+=item.valor;
			}
		}
		t++;	
    }
printf("Quantidade de Clientes atendidos no Caixa 1: %d\n", caixaB1.clientesAtendidos);
printf("Total saque: %.2f\n", caixaB1.valorSaque);
printf("Total deposito: %.2f\n", caixaB1.valorDeposito);
printf("Total pagamento: %.2f\n", caixaB1.valorPagamento);

printf("Quantidade de Clientes atendidos no Caixa 2: %d\n", caixaB2.clientesAtendidos);
printf("Total saque: %.2f\n", caixaB2.valorSaque);
printf("Total deposito: %.2f\n", caixaB2.valorDeposito);
printf("Total pagamento: %.2f\n", caixaB2.valorPagamento);

printf("Quantidade de Clientes atendidos no Caixa 3: %d\n", caixaB3.clientesAtendidos);
printf("Total saque: %.2f\n", caixaB3.valorSaque);
printf("Total deposito: %.2f\n", caixaB3.valorDeposito);
printf("Total pagamento: %.2f\n", caixaB3.valorPagamento);
}
