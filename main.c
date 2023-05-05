#include <stdio.h>
#define max 5
typedef struct Cars{
    int plate;
    int movs;
} Cars;

typedef struct Fila{

    Cars data[max];
    int start;
    int end;

} Fila;

void init(Fila* f){

    f->start=0;
    f->end=0;

}

int insert(Fila* f, Cars x){

    if(f->end==max) return 0;
    f->data[f->end] = x;
    f->end++;
    return 1;

}

int detach(Fila* f, Cars* x){

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
    int placa, i, flag, aux=0, cont=0, movs;
    Cars c1, caux;

    caux.movs=0;
 
    init(&f1);
    init(&f2);
    init(&f3);

    printf("Estacionamento do Seu Ze, entre com uma acao e a placa (digite \"Q\" para sair):\n");

    do{
        scanf("%c %d", &acao, &c1.plate);
        getchar();
        c1.movs=0;

        if(acao=='C'){
            if(insert(&f1, c1))
                printf("Existe vaga! Carro colocado no estacionamento.\n");
            else{
                insert(&f3, c1);
                printf("Estacionamento lotado, carro colocado na espera!\n");
                cont++;
            }
        }

        else if(acao == 'P'){
            flag=0;
            i=0;

            while(i<max&&!flag){
                if(f1.data[i].plate==c1.plate)
                    flag=1;
                i++;
            }
            i=-1;

            if(flag){
                while(caux.plate!=c1.plate){
                    detach(&f1, &caux);
                    if(caux.plate!=c1.plate){
                        caux.movs++; 
                        insert(&f2, caux);
                        printf("Carro de placa %d movido do principal para o auxiliar.\n", caux.plate);
                    }
                    i++;
                }

                printf("Carro de placa %d partindo, ele foi movido %d vezes.\n", caux.plate, caux.movs);
                if(i){
                    while(detach(&f1, &caux)){
                        printf("Carro de placa %d sendo movido do principal ao auxilar.\n", caux.plate);
                        caux.movs++;
                        insert(&f2, caux);
                    }
                    while(detach(&f2, &caux)){
                        printf("Carro de placa %d sendo movido do auxiliar ao principal.\n", caux.plate);
                        caux.movs++;
                        insert(&f1, caux);
                    }
                }

                if(cont){
                    detach(&f3, &caux);
                    insert(&f1, caux);
                    cont--;
                    printf("Carro de placa %d sendo movido da espera ao principal.\n", caux.plate);
                }
            }
            else{
                printf("Carro nao encontrado, entre novamente!\n");
                if(f1.end==f1.start) printf("Estacionamento vazio!\n");
            } 
        }
        else if(acao == 'Q') printf("Saindo.\n");
        else printf("Acao Invalida! Entre novamente.\n");
    }while(acao!='Q');
    return 0;

}