function cumulativeCountingSort(arr){
    if(arr.length <= 1) return arr;

    let max = Math.max(...arr);
    let min = Math.min(...arr);
    let size = arr.length;
    let range = max - min + 1;
    let count = new Array(range).fill(0);
    let sorted = new Array(size).fill(0);

    for(let i = 0; i < size; ++i){
        count[arr[i] - min]++;
    }

    for(let i = 1; i < range; ++i){
        count[i] += count[i - 1];
    }

    for(let i = size - 1; i >= 0; --i){
        let val = arr[i];
        let index = val - min;
        let pos = count[index] - 1;
        sorted[pos] = val;
        count[index]--;
    }
    return sorted;
}

let arr = [563,560,561,563,560,570];
console.log(cumulativeCountingSort(arr));