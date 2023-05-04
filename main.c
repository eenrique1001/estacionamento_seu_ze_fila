#include <stdio.h>
#define max 5
/*typedef struct Cars{
    int placa;
    int movs;
} Cars;*/

typedef struct Fila{

    int data[max];
    int start;
    int end;

} Fila;

void init(Fila* f){

    f->start=0;
    f->end=0;

}

int insert(Fila* f, int x){

    if(f->end==max) return 0;
    f->data[f->end] = x;
    f->end++;
    return 1;

}

int detach(Fila* f, int* x){

    if(f->end==f->start) return 0;
    *x = f->data[f->start];
    for(int i=0;i<max-1;i++)
        f->data[i] = f->data[i+1];
    f->end--;

}

/*int dequeue(Fila* f, int* x){
    if(f->end==f->start) return 0;
    *x = f->data[f->start];
    f->start++;

}*/

int main()

{

    Fila f1, f2, f3;
    char acao;
    int placa, i, flag, aux=0, cont=0;
 
    init(&f1);
    init(&f2);
    init(&f3);

    printf("Estacionamento do Seu Ze, entre com uma acao e a placa (digite \"Q\" para sair):\n");

    do{
        scanf("%c %d", &acao, &placa);
        getchar();

        if(acao=='C'){
            if(insert(&f1, placa))
                printf("Existe vaga! Carro colocado no estacionamento.\n");
            else{
                insert(&f3, placa);
                printf("Estacionamento lotado, carro colocado na espera!\n");
                cont++;
            }
        }

        else if(acao == 'P'){
            flag=0;
            i=0;

            do{
                if(f1.data[i]==placa)
                    flag=1;
                i++;

            }while(i<max&&!flag);
            i=-1;

            if(flag){
                while(aux!=placa){
                    detach(&f1, &aux);
                    if(aux!=placa){ 
                        insert(&f2, aux);
                        printf("Carro de placa %d movido do principal para o auxiliar.\n", aux);
                    }
                    i++;
                }

                printf("Carro de placa %d partindo.\n", aux);
                if(i){
                    while(detach(&f1, &aux)){
                        printf("Carro de placa %d sendo movido do principal ao auxilar.\n", aux);
                        insert(&f2, aux);
                    }
                    while(detach(&f2, &aux)){
                        printf("Carro de placa %d sendo movido do auxiliar ao principal.\n", aux);
                        insert(&f1, aux);
                    }
                }

                if(cont){
                    detach(&f3, &aux);
                    insert(&f1, aux);
                    cont--;
                    printf("Carro de placa %d sendo movido da espera ao principal.\n", aux);
                }
            }
            else printf("Carro nao encontrado, entre novamente!\n");
        }
        else if(acao == 'Q') printf("Saindo.\n");
        else printf("Acao Invalida! Entre novamente.\n");
    }while(acao!='Q');
    return 0;

}