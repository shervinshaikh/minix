#include <stdio.h>
#include <stdlib.h>

int semEating = sem_init(1); //1 means no one is eating, free.
int semUGrad  = sem_init(2); //2 total undergrads
int semGrad   = sem_init(6); //6 total grad students

int pizzaArray[8]={1,2,3,4,5,6,7,8};
int index =0;
int twoTables=0;

int main(void){
  //1-6 6 grads
  //7-8 2 ugrads

  int n = sizeof(pizzaArray)/ sizeof(pizzaArray[0]);
  randomize (PizzaArray, n);
  printArray(PizzaArray, n);
 
  while(1){
    if(pizzaArray[index] < 7)
      Grad();
    else
      UGrad();

  }
  
  return 0;
}

void UGrad(){
  sem_down(semEating);//undergrads now eating
  
  sem_down(semUGrad);
  UGradEat();//undergrad1 now eat
  
  if(pizzaArray[index] == 7 || pizzaArray[index]==8){
    sem_down(semUGrad); //only if(next 2 students in queue is ugrad then)
    twoTables = 1;
    UGradEat();//undergrad2 now eat
  }

  
  sem_up(semEating); //done eating
  if(twoTables == 1){
    sem_up(semUGrad);
    twoTables = 0;
  }

  sem_up(semUGrad);  //only (if 2 undergrads eating, not just one)
}

void UGradEat(){
  //eating move on to next;
  if(index == 7)
    index = 0;
  else
    index++
}

void Grad(){
  sem_down(semEating);//grads now eating
  
  sem_down(semGrad);
  GradEat();
  //first table grad now eat pizza
  if(pizzaArray[index] != 7 &&  pizzaArray[index] != 8) //only (if 2 grads)
  {
    sem_down(semGrad);
    twoTables = 1;
    GradEat();
    //second table grad now eat pizza
  }

  sem_up(semEating);

  sem_up(semGrad);
  if( twoTables == 1){
    sem_up(semGrad);
     twoTables = 0;
  }
  
}

void GradEat(){
  //eating move on to next;
  if(index == 7)
    index = 0;
  else
    index++
}

void swap (int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}
 
// A utility function to print an array
void printArray (int arr[], int n)
{
  for (int i = 0; i < n; i++)
    printf("%d ", arr[i]);
   printf("\n");
}
 
// A function to generate a random permutation of arr[]
void randomize ( int arr[], int n )
{
  // Use a different seed value so that we don't get same
  // result each time we run this program
  srand ( time(NULL) );
 
  // Start from the last element and swap one by one. We don't
  // need to run for the first element that's why i > 0
  for (int i = n-1; i > 0; i--)
    {
      // Pick a random index from 0 to i
      int j = rand() % (i+1);
 
      // Swap arr[i] with the element at random index
      swap(&arr[i], &arr[j]);
    }
}
