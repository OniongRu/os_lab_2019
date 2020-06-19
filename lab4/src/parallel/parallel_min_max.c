#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <getopt.h>

#include "find_min_max.h"
#include "utils.h"


void alarmHandler()
{
    fprintf(stderr,"Timeout. Next time give more time for this size of massive!\n");
    kill(0, SIGKILL);
    exit(1);
}


int main(int argc, char **argv) {
  int seed = -1;
  int array_size = -1;
  int pnum = -1;
  //
  int TimeW = -1;
  //
  bool with_files = false;

  while (true) {
    int current_optind = optind ? optind : 1;

    static struct option options[] = {{"seed", required_argument, 0, 0},
                                      {"array_size", required_argument, 0, 0},
                                      {"pnum", required_argument, 0, 0},
                                      {"by_files", no_argument, 0, 'f'},
				      {"timeout", required_argument, 0, 0},
                                      {0, 0, 0, 0}};

    int option_index = 0;
    int c = getopt_long(argc, argv, "f", options, &option_index);

    if (c == -1)
      break;

    switch (c) {
    case 0:
      switch (option_index) {
      case 0:
        seed = atoi(optarg);
        // your code here
        // error handling
        if (seed <= 0) {
          printf("seed is a positive number\n");
          return 1;
        }
        // V1
        break;
      case 1:
        array_size = atoi(optarg);
        // your code here
        // error handling
        if (array_size <= 0) {
          printf("array_size is a positive number\n");
          return 1;
        }
        break;
      case 2:
        pnum = atoi(optarg);
        // your code here
        // error handle
        if (pnum <= 0) {
          printf("pnum is a positive number\n");
          return 1;
        }
        if (pnum > array_size) {
          printf("pnum is too big for this array\nChoose another next time");
          return 1;
        }
        // V1

        // V1
        break;
      case 3:
        with_files = true;
        break;

      case 4:
	TimeW = atoi(optarg);
	if(TimeW <= 0)
	{
		printf("WorkTime is a positive number");
		return 1;
	}
	break;

      defalut:
        printf("Index %d is out of options\n", option_index);
      }
      break;
    case 'f':
      with_files = true;
      break;

    case '?':
      break;

    default:
      printf("getopt returned character code 0%o?\n", c);
    }
  }

  if (optind < argc) {
    printf("Has at least one no option argument\n");
    return 1;
  }

  if (seed == -1 || array_size == -1 || pnum == -1) {
    printf("Usage: %s --seed \"num\" --array_size \"num\" --pnum \"num\" \n",
           argv[0]);
    return 1;
  }

  //lab4
  signal(SIGALRM, alarmHandler);
  alarm(TimeW);
  //

  int *array = malloc(sizeof(int) * array_size);
  GenerateArray(array, array_size, seed);
  int active_child_processes = 0;

  struct timeval start_time;
  gettimeofday(&start_time, NULL);
  //
  int min_ft[pnum][2];
  int max_ft[pnum][2];
  for (int i = 0; i < pnum; i++) {
    pipe(min_ft[i]);
    pipe(max_ft[i]);
  }
  int step_beg = 0;
  int step_end = 0;
  int step = array_size / pnum;
  int check = 0;
  FILE *file;
  if(with_files)
	  file = fopen("file","wb+");
  if (array_size % pnum != 0) {
    check = 1;
  }
  //
  for (int i = 0; i < pnum; i++) {
    pid_t child_pid = fork();
    if ((check == 1) && (i == pnum - 1))
      step_end = array_size - 1;
    else
      step_end += step;
    if (child_pid < 0) {
      printf("Fork failed!\n");
      return 1;
    }
      // successful fork
      if (child_pid == 0) {
        // child process

        // parallel somehow
	int min = array[step_beg];
          int max = array[step_end];
          for (int j = step_beg + 1; j < step_end; j++) {
            if (array[j] < min)
              min = array[j];
            if (array[j] > max)
              max = array[j];
          }

        if (with_files) {
          // use files here
          // use files here
          // считать из файла и посчитать максимум/минимум
          // и записать в файл
	  int minmax[2];
	  minmax[0] = min;
	  minmax[1] = max;
	  fwrite(minmax,1,sizeof(minmax),file);
	  fclose(file);
	  //
        } else {
          // use pipe here
          // use pipe here
          // минимум/максимум ищем и запихиваем в pipe
          // fd[i][1]
          write(min_ft[i][1], &min, sizeof(int));
          write(max_ft[i][1], &max, sizeof(int));
        }
        return 0;
      }
    step_beg += step;
    active_child_processes += 1;
  }
  while (active_child_processes > 0) {
    // your code here
    wait(NULL);
    //
    active_child_processes -= 1;
  }
  //lab4
  alarm(0);
  //
  if(with_files)
  {
	  fclose(file);
	  file=fopen("file","rb");
  }
  struct MinMax min_max;
  min_max.min = INT_MAX;
  min_max.max = INT_MIN;

  for (int i = 0; i < pnum; i++) {
    if (with_files) {
      // read from files
      int lowhigh[2];
      fread(lowhigh,1,sizeof(lowhigh),file);
      if(lowhigh[0]<min_max.min) min_max.min = lowhigh[0];
      if(lowhigh[1]>min_max.max) min_max.max = lowhigh[1];
    } else {
      // read from pipes
      //
      // read(fp[i][1]); - типа такого
        int low;
        int high;
	read(min_ft[i][0], &low, sizeof(int));
        read(max_ft[i][0], &high, sizeof(int));
        if (low < min_max.min)
          min_max.min = low;
        if (high > min_max.max)
          min_max.max = high;
    }
  }
  if(with_files)
	  fclose(file);

  struct timeval finish_time;
  gettimeofday(&finish_time, NULL);

  double elapsed_time = (finish_time.tv_sec - start_time.tv_sec) * 1000.0;
  elapsed_time += (finish_time.tv_usec - start_time.tv_usec) / 1000.0;

  free(array);

  printf("Min: %d\n", min_max.min);
  printf("Max: %d\n", min_max.max);
  printf("Elapsed time: %fms\n", elapsed_time);
  fflush(NULL);
  return 0;
}
