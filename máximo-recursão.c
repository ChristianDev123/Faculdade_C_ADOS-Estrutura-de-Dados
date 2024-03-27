int max(int* array, int size){  
  if(size == 1){
    return array[0];
  }
  int maxValue = max(array, size-1);
  
  if(array[size-1] < maxValue)
    return maxValue;
  else return array[size-1];
}

int main (void){
  int testArray[5] = {1,2,5,3,4};
  printf("%d", max(testArray, 5));
  return 0;
}