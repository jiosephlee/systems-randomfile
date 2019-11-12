#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

int random_int(){
  int output[1];
  int file = open("/dev/random", O_RDONLY);
  int success = read(file, output, sizeof(int));
  if(success < 0){
    printf("Error: %d, %s",errno, strerror(errno));
    return -1;
  }else{
    return output[0];
  }
  close(file);
}

int main() {
  int arr1[10];
  int arr2[10];
  int i;
  int success;
  printf("Generating Random Numbers...\n");
  for (i = 0; i < 10; i++) {
    arr1[i] = random_int();
    printf("%d\n",arr1[i]);
  }

  printf("\nWriting numbers to file.txt...\n");
  int file = open("file.txt", O_CREAT | O_WRONLY, 0666);
  if(file < 0){
    printf("Error: %d, %s",errno, strerror(errno));
  } else{
    success = write(file, arr1, 10 * sizeof(int));
    if(success < 0){
      printf("Error: %d, %s",errno, strerror(errno));
    }
  }
  close(file);

  printf("\nCopying numbers from file.txt to arr2 ...\n");
  file = open("file.txt", O_RDONLY);
  if(file < 0){
    printf("Error: %d, %s",errno, strerror(errno));
  } else{
    success = read(file, arr2, 10 * sizeof(int));
    if(success < 0){
      printf("Error: %d, %s",errno, strerror(errno));
    }
  }
  close(file);

  printf("\nPrinting second array...\n");
  for (i = 0; i < 10; i++) {
    printf("%d\n",arr2[i]);
  }
  return 0;
}
