function bubbleSort(arr){

	let size = arr.length;
	let flag = true;


	for(let i = 0; i < size - 1; ++i){
		for(let j = 0; j < size - 1 - i; ++j){
			if(arr[j] > arr[j + 1]){
				let tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
				flag = false;
			}
			
			if(flag){
				return;
			}
		}
	}
}
