#include "../lib/thread.h"
unsigned long balance = 100;
#define LOAD(x) x
#define STORE(x,y) (x) = (y)

void alipay_withdraw(int amt) {
    if (LOAD(balance) >= amt) {
        usleep(1);
        STORE(balance,LOAD(balance) - amt);
    }
}

void Talipay(int id){
    alipay_withdraw(100);
}

int main(){
    create(Talipay);
    create(Talipay);
    join();
    printf("balance=%lu\n", balance);
}