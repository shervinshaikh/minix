#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void UGrad(int num);
void UGrad2(int num);
void Grad(int num);
void Grad2(int num);
void UGradEat(int num);
void GradEat(int num);

int semEating;
int semUGrad;
int semGrad;

//int pizzaArray[8]={1,2,3,4,5,6,7,8};
int numStudents = 8;
int twoTables=0;

pid_t *childPids = NULL;
pid_t p;

int prev_student=0;

int main(void){
  //1-6 6 grads
  //7-8 2 ugrads

  semEating = sem_init(1); //1 means no one is eating, free.
  semUGrad  = sem_init(2); //2 total undergrads
  semGrad   = sem_init(2); //2 total undergrads

  int i;

  srand(time(NULL));
  while(1){
    for(i=0;i<numStudents;i++){
      int student = prev_student;
      while(prev_student == student)
	(rand() % (numStudents))+1;
      
      if( (p=fork()) == 0){//child process
	if(student < 7)
	  Grad(student);
	else
	  UGrad(student);
	prev_student=0;
	exit(0);
      }
      else
	childPids[i]=p;
    }
    
  }
  
  return 0;
}

void UGrad(int num){

  if(prev_student == 7 || prev_student==8){
    UGrad2(num);
  }
  else{
    sem_down(semUGrad);
    sem_down(semEating); 
    prev_student = num;
    UGradEat(num);
    prev_student = num;
    sem_up(semEating);
    sem_up(semUGrad);
  }
}

void UGrad2(int num){
  sem_down(semUGrad);
  UGradEat(num);
  sem_up(semUGrad);
}

void UGradEat(int num){
  printf("Under Grad %d Eating\n", num-6);
}

void Grad(int num){

   if(prev_student >= 1 && prev_student <= 6){
    Grad2(num);
  }
   else{
     sem_down(semGrad);
     sem_down(semEating); 
     prev_student = num;
     GradEat(num);
     //prev_student = num;
     sem_up(semEating);
     sem_up(semGrad);
   }
  
}

void Grad2(int num){
  sem_down(semGrad);
  GradEat(num);
  sem_up(semGrad);
}

void GradEat(int num){
  //eating move on to next;
  printf("Grad %d Eating\n", num);
}

