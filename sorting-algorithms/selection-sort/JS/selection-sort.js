function selectionSort(arr){

    const size = arr.length;
    const sorted = [...arr];
    
    for(let i = 0; i < size - 1; ++i){
        let minIndex = i;
        for(let j = i + 1; j < size; ++j){
            if(sorted[j] < sorted[minIndex]){
                minIndex = j;
            }
        }
        if(minIndex != i){
            [sorted[minIndex],sorted[i]] = [sorted[i],sorted[minIndex]];
        }
    }

    return sorted;

}

let arr = [64,25,12,22,11];

selectionSort(arr);
console.log(arr);