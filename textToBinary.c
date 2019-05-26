#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  FILE *fd;
  FILE *bin;

  if ((fd = fopen("absenteeism.txt", "r")) == NULL) {
    printf("ERROR: Could not open file\n");
    exit(1);
  }

  if ((bin = fopen("absenteeism.bin", "w")) == NULL) {
    printf("ERROR: Could not open file\n");
    exit(1);
  }

  char firstLine[292];
  fread(&firstLine, sizeof(char), 293, fd);

  char line[1000];
  unsigned short int recordCount = 0;
  unsigned char id, age, children, pets, bmi, hoursAbsent;
  int rfa, numSeason, tf, dfrtw, serviceTime, hit, discipline, numEdu, numDrinker, numSmoker, weight, height;
  float workload;
  char month, dayOfWeek, season, drinker, smoker;
  char education[3];

  while(!feof(fd)){
    // ID
    fscanf(fd, "%hhu;", &id);
    fwrite(&id, sizeof(unsigned char), 1, bin);

    // TO SKIP (rfa or REASON FOR ABSENCE)
    fscanf(fd, "%d;", &rfa);

    // MONTH
    fscanf(fd, "%c;", &month);
    fwrite(&month, sizeof(char), 1, bin);

    // DAY OF THE WEEK
    fscanf(fd, "%c;", &dayOfWeek);
    fwrite(&dayOfWeek, sizeof(char), 1, bin);

    // SEASON
    fscanf(fd, "%d;", &numSeason);

    if (numSeason == 1){
      season = 'W';
    }
    if (numSeason == 2){
      season = 'P';
    }
    if (numSeason == 3){
      season = 'S';
    }
    if (numSeason == 4){
      season = 'F';
    }

    fwrite(&season, sizeof(char), 1, bin);

    // TO SKIP (Transportation Expense)
    fscanf(fd, "%d;", &tf);

    // TO SKIP (Distance from Residence to Work)
    fscanf(fd, "%d;", &dfrtw);

    // TO SKIP (Service Time)
    fscanf(fd, "%d;", &serviceTime);

    // AGE
    fscanf(fd, "%hhu;", &age);
    fwrite(&age, sizeof(unsigned char), 1, bin);

    // TO SKIP (Workload Average/day)
    fscanf(fd, "%f;", &workload);

    // TO SKIP (HIT TARGET)
    fscanf(fd, "%d;", &hit);

    // TO SKIP (Disciplinary Failure)
    fscanf(fd, "%d;", &discipline);

    // EDUCATION
    fscanf(fd, "%d;", &numEdu);

    if (numEdu == 1){
      education[0] = 'H';
      education[1] = 'S';
    }
    if (numEdu == 2){
      education[0] = 'G';
      education[1] = 'R';
    }
    if (numEdu == 3){
      education[0] = 'P';
      education[1] = 'G';
    }
    if (numEdu == 4){
      education[0] = 'M';
      education[1] = 'D';
    }

    fwrite(&education, sizeof(char), 1, bin);

    // NUMBER OF CHILDREN
    fscanf(fd, "%hhu;", &children);
    fwrite(&children, sizeof(unsigned char), 1, bin);

    // SOCIAL DRINKER
    fscanf(fd, "%d;", &numDrinker);

    if (numDrinker == 1){
      drinker = 'Y';
    }
    if (numDrinker == 0){
      drinker = 'N';
    }

    fwrite(&drinker, sizeof(char), 1, bin);

    // SOCIAL SMOKER
    fscanf(fd, "%d;", &numSmoker);

    if (numSmoker == 1){
      smoker = 'Y';
    }
    if (numSmoker == 0){
      smoker = 'N';
    }

    fwrite(&smoker, sizeof(char), 1, bin);

    // NUMBER OF PETS
    fscanf(fd, "%hhu;", &pets);
    fwrite(&pets, sizeof(unsigned char), 1, bin);

    // WEIGHT
    fscanf(fd, "%d;", &weight);

    // HEIGHT
    fscanf(fd, "%d;", &height);

    // BODY MASS INDEX
    fscanf(fd, "%hhu;", &bmi);
    fwrite(&bmi, sizeof(unsigned char), 1, bin);

    // HOURS ABSENT
    fscanf(fd, "%hhu;", &hoursAbsent);
    fwrite(&hoursAbsent, sizeof(unsigned char), 1, bin);

    fscanf(fd, "%[^\n]\n", line);

    recordCount++;
  }
  printf("%hu\n", recordCount);

  fclose(fd);
  fclose(bin);
}
