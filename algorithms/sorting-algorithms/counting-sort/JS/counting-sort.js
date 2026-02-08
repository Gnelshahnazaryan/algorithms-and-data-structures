function countingSort(arr) {
  if (arr.length <= 1) return arr;

  const size = arr.length;
  const max = Math.max(...arr);
  const min = Math.min(...arr);

  const count = new Array(max - min + 1).fill(0);
  const sorted = [];

  for (let i = 0; i < size; ++i) {
    count[arr[i] - min]++;
  }

  for (let i = 0; i < count.length; ++i) {
    while (count[i] > 0) {
      sorted.push(i + min);
      count[i]--;
    }
  }
  return sorted;
}

let arr = [2, 0];
console.log(countingSort(arr));
