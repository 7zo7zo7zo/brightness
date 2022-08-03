#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {
  if(argc < 3) return 1;
  char basename[50] = "/sys/class/backlight/";
  strcat(basename, argv[1]);
  char location[50];
  strcpy(location, basename);
  strcat(location, "/max_brightness");

  char input[50];

  FILE *fmax = fopen(location, "r");
  fscanf(fmax, "%s", input);
  fclose(fmax);
  int max = atoi(input);

  strcpy(location, basename);
  strcat(location, "/brightness");

  FILE *fcurr = fopen(location, "w+");
  fscanf(fcurr, "%s", input);
  int curr = atoi(input);

  int perc = atoi(argv[2]);
  int amount;

  if(argc < 4) amount = perc * max / 100;
  else if(strcmp(argv[3], "+") == 0) amount = curr + perc * max / 100;
  else if(strcmp(argv[3], "-") == 0) amount = curr - perc * max / 100;
  else {
    fclose(fcurr);
    return 1;
  }

  if(amount > max) amount = max;
  else if (amount < 0) amount = 0;

  fprintf(fcurr, "%d", amount);
  fclose(fcurr);

  return 0;
}
