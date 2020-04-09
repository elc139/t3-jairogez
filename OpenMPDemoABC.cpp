#include <algorithm>
#include <iostream>
#include <string>
#include <omp.h>

int omp_get_thread_num();

class SharedArray {
private:
   char* array;
   int index = 0;
   int size;
public:
   SharedArray(int n) : size(n) {
      array = new char[size];
      std::fill(array, array+size, '-');
   }

   ~SharedArray() {
      delete[] array;
   }
   void addChar(char c) {
      #pragma omp critical 
      {
      array[index] = c;
      spendSomeTime();
      index++;
      }
   }

   int countOccurrences(char c) {
      return std::count(array, array+size, c);
   }

   std::string toString() {
      return std::string(array, size);
   }

private:
   int spendSomeTime() {
      for (int i = 0; i < 10000; i++) {
         for (int j = 0; j < 100; j++) {
            // These loops shouldn't be removed by the compiler
         }
      }
      return 1;
   }
};


class ArrayFiller{
private:
   SharedArray* array;
   int chunk , n = 60;
public:
   int option = 0;
   ArrayFiller(int c) {
      this->array = new SharedArray(n);
      this->chunk = c;
   }
   void fillArrayConcurrently(int option) {
        switch (option) {
            case 1:
               #pragma omp parallel for schedule(static, chunk)
               for (int i = 0; i < n; i++)
                   array->addChar('A' + omp_get_thread_num());
               break;
               case 2:
               #pragma omp parallel for schedule(static)
               for (int i = 0; i < n; i++)
                   array->addChar('A' + omp_get_thread_num());
               break;
            case 3:
               #pragma omp parallel for schedule(dynamic, chunk)
                for (int i = 0; i < n; i++)
                    array->addChar('A' + omp_get_thread_num());
                break;
             case 4:
                #pragma omp parallel for schedule(dynamic)
                for (int i = 0; i < n; i++)
                    array->addChar('A' + omp_get_thread_num());
                break;
            case 5:
                #pragma omp parallel for schedule(guided, chunk)
                for (int i = 0; i < n; i++)
                    array->addChar('A' + omp_get_thread_num());
                break;
            case 6:
                #pragma omp parallel for schedule(guided)
                for (int i = 0; i < n; i++)
                    array->addChar('A' + omp_get_thread_num());
                break;
            case 7:
                #pragma omp parallel for schedule(runtime)
                for (int i = 0; i < n; i++)
                    array->addChar('A' + omp_get_thread_num());
                break;
            case 8:
                #pragma omp parallel for schedule(auto)
                for (int i = 0; i < n; i++)
                    array->addChar('A' + omp_get_thread_num());
                break;
        }
    }
   void printStats() {
      std::cout << array->toString() << std::endl;
      for (int i = 0; i < 3; ++i)
         std::cout << (char) ('A'+i) << "="
                   << array->countOccurrences('A'+i) << " ";
      std::cout << std::endl;
   }
   ~ArrayFiller() {
      delete array;
   }
};


int main(int argc, char const *argv[]) {
   ArrayFiller af(atoi(argv[1]));
   af.fillArrayConcurrently(atoi(argv[2]));
   af.printStats();

}
