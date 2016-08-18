/*
 *  Exercício Torre de Hanoi
 * 
 *  Carlos Henrique Reis - 30415
 *  
 *  Solução: Para a resolução desse problema foi aplicado o método iterativo, e  o uso do de uma estrutura chamada torre
 * 
 *  Análise: Esse algoritmo possui a complixade assintótica O(2^n) de tempo.
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#define V 0
#define F 1
#define VAZIA -1

/*Estrutura torre, tem um vetor que representa os discos, um contador (pos) e id da torre (c)*/
struct torre_t {
    int *torre;
    int pos;
    char c;
};
typedef struct torre_t torre_t;

/*alocação de memória  para uma torre. Parâmetros: n = Número de discos, qual = identificação da torre*/
torre_t *cria_torre (int n, char qual){
    torre_t *t;
    t = (torre_t*) malloc (sizeof(torre_t));
    if(!t)
        return NULL;
    t->torre = (int*) calloc (n, sizeof(int));
    if(!t->torre)
        return NULL;
    t->pos = VAZIA;
    t->c = qual;
    return t;/*Retorna a torre criada*/
}
/*Insere um disco na torre. Parâmetro: Torre, disco*/
void insere (torre_t *t, int disco){
    t->pos++;
    t->torre[t->pos] = disco;
    return;
}
/*Remove um disco na torre. Parâmetro: Torre, disco*/
int retira (torre_t *t){
    int a;
    a = t->torre[t->pos];
    t->pos--;
    return(a);/*Retorna a posição do disco removido*/
}
/*Insere todos os discos na torre de origem*/
void inicializa_orig (torre_t *orig, int n){
    int i;
    for (i = n; i > 0 ; i--)
        insere(orig, i);
    return;
}
/*Move o disco superior da torre origem para a torre auxiliar e incrementa a quantidade de movimentos*/
void move_orig_aux (torre_t *orig, torre_t *aux, int *qtd){
    int disco;
    ++*qtd;
    if (orig->pos == VAZIA){
        disco = retira (aux);
        insere (orig, disco);
        printf("%d) Move o disco %d da torre %c para a torre %c\n", *qtd, disco, aux->c, orig->c);
        return;
    }
    if (aux->pos == VAZIA){
        disco = retira (orig);
        insere (aux, disco);
        printf("%d) Move o disco %d da torre %c para a torre %c\n",*qtd, disco, orig->c, aux->c);
        return;
    }
    if (orig->torre[orig->pos] < aux->torre[aux->pos]){
        disco = retira (orig);
        insere (aux, disco);
        printf("%d) Move o disco %d da torre %c para a torre %c\n",*qtd, disco, orig->c, aux->c);
        return;
    }
    if (aux->torre[aux->pos] < orig->torre[orig->pos]){
        disco = retira (aux);
        insere (orig, disco);
        printf("%d) Move o disco %d da torre %c para a torre %c\n",*qtd, disco, aux->c, orig->c);
        return;
    }

}
/*Move o disco superior da torre de origem para a torre destino e incrementa a quantidade de movimentos*/
void move_orig_dest (torre_t *orig, torre_t *dest, int *qtd){
    int disco;
    ++*qtd;
    if (orig->pos == VAZIA){
        disco = retira (dest);
        insere (orig, disco);
        printf("%d) Move o disco %d da torre %c para a torre %c\n", *qtd,disco, dest->c, orig->c);
        return;
    }
    if (dest->pos == VAZIA){
        disco = retira (orig);
        insere (dest, disco);
        printf("%d) Move o disco %d da torre %c para a torre %c\n",*qtd, disco, orig->c,dest->c);
        return;
    }
    if (orig->torre[orig->pos]< dest->torre[dest->pos]){
        disco = retira (orig);
        insere (dest, disco);
        printf("%d) Move o disco %d da torre %c para a torre %c\n",*qtd, disco, orig->c, dest->c);
        return;
    }
    if (dest->torre[dest->pos] < orig->torre[orig->pos]){
        disco = retira (dest);
        insere (orig, disco);
        printf("%d) Move o disco %d da torre %c para a torre %c\n",*qtd, disco, dest->c, orig->c);
        return;
    }

}
/*Move o disco superior da torre auxiliar para a torre destino e incrementa a quantidade de movimentos*/
void move_aux_dest (torre_t *aux, torre_t *dest, int *qtd){
    int disco;
    ++*qtd;
    if (aux->pos == VAZIA){
        disco = retira (dest);
        insere (aux, disco);
        printf("%d) Move o disco %d da torre %c para a torre %c\n",*qtd, disco, dest->c, aux->c);
        return;
    }
    if (dest->pos == VAZIA){
        disco = retira (aux);
        insere (dest, disco);
        printf("%d) Move o disco %d da torre %c para a torre %c\n",*qtd, disco, aux->c,dest->c);
        return;
    }
    if (aux->torre[aux->pos] < dest->torre[dest->pos]){
        disco = retira (aux);
        insere (dest, disco);
        printf("%d) Move o disco %d da torre %c para a torre %c\n",*qtd, disco, aux->c, dest->c);
        return;
    }
    if (dest->torre[dest->pos] < aux->torre[aux->pos]) {
        disco = retira (dest);
        insere (aux, disco);
        printf("%d) Move o disco %d da torre %c para a torre %c\n",*qtd, disco, dest->c, aux->c);
        return;
    }

}

/*Função que inicializa as torres e faz as devidas chamdas das funções para reolver os problema
 *Parametros: n = Números de discos, torg= ID da torre de origem, tdst= ID da torre de destino, aux= ID da torre auxiliar,  
 */
void hanoi (int n, char torg, char tdst, char aux){
    torre_t *orig, *dest, *auxl;
    int i =0;
    int qtd = 0;
    /*Cria as torres*/
    orig = cria_torre (n, torg);
    dest = cria_torre (n, tdst);
    auxl = cria_torre (n, aux);
    /*Inicializa a torre de orgem com o n discos*/
    inicializa_orig (orig, n);
    /*Se o n de discos forem par*/
    if(n%2 == 0)
        while (dest->pos < n-1){
            move_orig_aux (orig, auxl,&qtd);
            if(dest->pos == n-1)
                break;
            move_orig_dest (orig, dest,&qtd);
            if(dest->pos == n-1)
                break;
            move_aux_dest (auxl, dest,&qtd);
        }
    else
        while (dest->pos < n){
            move_orig_dest (orig, dest,&qtd);
            if(dest->pos == n-1)
                break;
            move_orig_aux (orig, auxl,&qtd);
            if(dest->pos == n-1)
                break;
            move_aux_dest (auxl, dest,&qtd);
        }
    return;
}
int main (void){
    int discos;
    /*loop para os testes. Sai quando a qtd for menir que zero*/
    do{
        printf("Digite a quantidade de discos\n");
        scanf( "%d", &discos);
        /*Torres: Origem = A, dest = C, auxiliar = B*/
        hanoi ( discos, 'A', 'C', 'B');
    }while(discos>0);
    return 0;
}
