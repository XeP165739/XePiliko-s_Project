#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>

//pick up an index
//have ponter L And R
//switch two pointer if the value is bigger else no
//if switch, move R--
//when two pointer meets, put the index there

void quicksort(int* intlist, int L, int R){
    if(L >= R){
        return;
    }

    int l = L, r = R - 1;

    while(l <= r){
        if(intlist[l] > intlist[R]){
            if(l != r){
                intlist[l] ^= intlist[r];
                intlist[r] ^= intlist[l];
                intlist[l] ^= intlist[r];
            }
            r--;
        } else {
            l++;
        }
    }

    if(l != R){
        intlist[l] ^= intlist[R];
        intlist[R] ^= intlist[l];
        intlist[l] ^= intlist[R];
    }

    quicksort(intlist, L, l - 1); // Left
    quicksort(intlist, l + 1, R); // Right

    return;
}

int main(){
    const int size = 1000000;
    srand(time(NULL));

    int* intlist = new int[size];

    for (int i = 0; i < size; i++) {
        intlist[i] = rand() % 1000;
    }

    quicksort(intlist, 0, size - 1);

    for (int i = 0 ; i < size; i++) {
        std::cout << std::to_string(intlist[i]) << " ";
    }

    delete intlist;
    return 0;
}
