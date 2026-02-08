function bubbleSort(arr) {
  const size = arr.length;
  let flag = false;
  const sorted = [...arr];

  for (let i = 0; i < size - 1; ++i) {
    flag = false;
    for (let j = 0; j < size - 1 - i; ++j) {
      if (sorted[j] > sorted[j + 1]) {
        [sorted[j + 1], sorted[j]] = [sorted[j], sorted[j + 1]];
        flag = true;
      }

      if (!flag) {
        return sorted;
      }
    }
  }
  return sorted;
}

let arr = [5, 4, 3, 1, 2];
console.log(bubbleSort(arr));
