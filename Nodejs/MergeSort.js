async function mergesort(arr, l, r){
    if (l >= r) return;

    const m = l + Math.floor((r - l) / 2);

    mergesort(arr, l, m);
    mergesort(arr, m + 1, r);

    merge(arr, l, m, r);
}

async function merge(arr, l, m, r){
    let n1 = m - l + 1;
    let n2 = r - m;

    let L = new Array(n1);
    let R = new Array(n2);

    for (let i = 0; i < n1; i++){
        L[i] = arr[l + i];
    }
    for (let j = 0; j < n2; j++){
        R[j] = arr[m + 1 + j];
    }

    let i = 0, j = 0, k = l;

    while (i < n1 && j < n2){
        if (L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    for(; i < n1; i++){
        arr[k] = L[i];
        k++;
    }
    for(; j < n2; j++){
        arr[k] = R[j];
        k++;
    }
}

async function main(){
    let size = 1000000;
    let arr = [];

    for(let i = 0; i < size; i++){
        arr.push(Math.floor(Math.random() * size));
    }
    // console.log("Given array is: " + arr);

    console.time("MergeSort Time");
    mergesort(arr, 0, arr.length - 1);
    console.timeEnd("MergeSort Time");

    console.log(`sorted? ${((arr) => {for(let i = 0, j = 1; j < arr.length; ++i,++j){if(arr[i] > arr[j]) return false;} return true;})(arr)}`);
}

main();