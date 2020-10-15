#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int *push(int *array, int *num, int elem) {
  if(*num < MAX){
    array[*num] = elem;
    *num += 1;
      return array;
  } else {
    printf("error: num > MAX\n");
      return array;
  }
}

int pop(int *array, int *num) {
  int array2;
  
  if(*num > 0){
      *num -= 1;
      array2 = array[*num];
    return array2;
  } else {
    printf("there is no info store\n");
    return 0;
  }
}

int isempty(int array[MAX], int num) {
  if(num == 0)
  return 1;
  
  else
  return 0;
  
}

void stkPrint(int array[MAX], int num) {
  int i = num;
  
  if(isempty(array, num) == 1)
      return;
  
  while(i>0){
    printf("%d\n", array[--i]);
  }
}

int main(void) {
  int *array = calloc(MAX, sizeof(int));
  int num=0;
  int vibor = 0;
  int elem;
    
      while(vibor!=4){
          printf("1)ADD\n2)DELETE\n3)PRINT\n4)exit\nCHOOSE: ");
    
          scanf("%d", &vibor);
  
  switch(vibor){
            case 1:
                printf("enter arrayent:");
                scanf("%d", &elem);
                array = push(array, &num, elem);
            break;
            
            case 2:
                printf("delete %d\n", pop(array, &num));
            break;
            
            case 3:
                stkPrint(array, num);
            break;
            
            case 4:
                exit(0);
            break;
  
        }

    }
    
    return 0;
    
}
