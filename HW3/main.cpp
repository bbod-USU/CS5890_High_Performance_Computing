///
///Brady Bodily
///A00987897
///


#include <iostream>
#include <omp.h>
#include <string>
#include <iomanip>

void Count_sort(int a[], int n, int thread_count);
void PrintArray(int a[], int n);
int main(int argc, char* argv[]) {
    int n = std::stoi(argv[1]);
    int thread_count = std::stoi(argv[2]);
    srand(100);
    int *a = (int *)malloc(n*sizeof(int));
    for(auto i =0;i<n;i++){
        a[i] = rand()%n;
    }


    std::cout<<"Initial Array: " << std::endl;
    PrintArray(a, n);
    Count_sort(a,n,thread_count);
    std::cout<<"Sorted Array: " << std::endl;
    PrintArray(a, n);

//    for(auto i = 0;i<n;i++){
//        std::cout << a[i] << " ";
//        if(i %10 ==0)
//            std::cout << std::endl;
//    }

    return 0;
}

void Count_sort( int a[], int n, int thread_count) {
  int i, j, count;
  int * temp = static_cast<int *>(malloc(n * sizeof(int)));
  #pragma omp parallel for num_threads(thread_count) default(none) private(i,j,count) shared(a,n,temp)
  for (i = 0; i < n; i++) {
    count = 0;
    for (j = 0; j < n; j++)
      if (a[j] < a[i])
        count++;
      else if (a[j] == a[i] && j < i)
        count++;
    temp[count] = a[i];
  }
  memcpy(a, temp, n*sizeof(int));
  free(temp);
} /* Count_sort */

void PrintArray(int a[], int n){
    for(auto i = 0;i<n;i++){
        std::cout << std::setw(3) << a[i] << " ";
        if((i+1) %10 == 0)
            std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
}