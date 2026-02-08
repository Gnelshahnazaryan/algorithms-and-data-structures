function insertionSort(arr){
    const size = arr.length;
    const sorted = [...arr];

    for(let i = 1; i < size; ++i){
        let j = i - 1;
        let key = sorted[i];

        while(j >= 0 && sorted[j] > key){
            sorted[j + 1] = sorted[j];
            --j;
        }

        sorted[j + 1] = key;
    }
    return sorted;
}

let arr = [8,3,5,2];

let sorted = insertionSort(arr);
console.log(sorted);