function partition(arr, low, high) {
  let pivot = arr[low];
  let i = low;
  let j = high;

  while (i <= j) {
    while (arr[i] <= pivot) ++i;
    while (arr[j] > pivot) --j;

    if (i < j) {
      [arr[i], arr[j]] = [arr[j], arr[i]];
    }
  }

  [arr[j], arr[low]] = [arr[low], arr[j]];

  return j;
}

function quickSort(arr, low = 0, high = arr.length - 1) {
  if (low >= high) return;

  let pi = partition(arr, low, high);
  quickSort(arr, low, pi - 1);
  quickSort(arr, pi + 1, high);
}

let arr = [5, 4, 3, 2, 1];
quickSort(arr);
console.log(arr);
