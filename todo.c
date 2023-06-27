#include "stdio.h"
#include "string.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "stdlib.h"
#define PATH "/Users/abdelrahmanelhawary/.todos/"
#define DEFAULT "default" 

int stringToNum(char *string){
  int number = 0;
  int i = 0;
  int denomination = 1;
  while(string[i] != '\0'){
    number += (string[i] - '0') * denomination;
    i++;
    denomination *= 10;
  }
  return number;
}

char * getFileName(char *group){
  char * name = (char *)calloc(50, sizeof(char));
  strcpy(name, PATH);
  strcat(name, group);
  return name;
}

FILE * openFile(char *group, char* mode){
  FILE *fp = NULL;
  char *name = getFileName(group);
  fp = fopen(name, mode);
  free(name);
  return fp;
}

void listItems(char *group){
  FILE * fp = openFile(group, "r");
  if(fp == NULL){
    printf("Group %s Doesn't exist\n", group);
    return;
  }
  int i = 1;
  printf("%d. ", i);
  char c = (char)fgetc(fp);
  char isNewLine = 0;
  while(c != EOF){
    if(isNewLine){
      i++;
      printf("%d. ", i);
      isNewLine = 0;
    }
    printf("%c", c);
    if(c == '\n'){
      isNewLine = 1;
    }
    c = (char)fgetc(fp);
  }
  fclose(fp);
}

// Add this feature
void removeItem(char *group, int number){
  int index = number - 1;
  FILE * fp = openFile(group, "r");
  FILE * newFp = openFile("replica", "w");
  if(fp == NULL){
    printf("Group %s doens't exist!\n", group);
    return;
  }
  if(newFp == NULL){
    printf("Can't remove line\n");
  }
  char c = (char)fgetc(fp);
  char isNewLine = 0;
  int i = 1;
  while(c != EOF){
    if(i != number){
      fprintf(newFp, "%c", c);
    }

    if(c == '\n'){
      i = i + 1;
    }
    c = (char)fgetc(fp);
  }
  fclose(fp);
  fclose(newFp);
  char *replicaName = getFileName("replica");
  char *groupName = getFileName(group);
  rename(replicaName, groupName);
  free(replicaName);
  free(groupName);
}

void addGroup(char *group){
  FILE * fp = openFile(group, "w");
  fclose(fp);
  printf("Created Group %s\n", group);
}

void addItem(char *group, int itemc, char **items){
  FILE * fp = openFile(group, "a");
  for(int i = 0; i < itemc - 1; i++){
    fprintf(fp, "%s", items[i]);
    fprintf(fp, " ");
  }
  fprintf(fp, "%s", items[itemc - 1]);
  fprintf(fp, "\n");
  fclose(fp);
  printf("Added Item\n");
}

void printValidCommands(){
  printf("Valid Commands are:\n");
  printf("todo ls -> lists ungrouped items\n");
  printf("todo ls <group> -> lists items in a group\n");
  printf("todo mk <group> -> makes a group\n");
  printf("todo add <item> -> adds an item\n");
  printf("todo add -g <group> <item> -> adds an item to a group\n");
  printf("todo rm <number>\n");
  printf("todo rm -g <group> <number>\n");
}

int main(int argc, char **argv){
  // if no todos directory create one
  struct stat st = {0};
  if(stat(PATH, &st) == -1){
    mkdir(PATH, 0777);
    FILE *fp = NULL;
    char name[50] = PATH;
    strcat(name, DEFAULT);
    fp = fopen(name, "w");
    fclose(fp);
    printf("Created Home Directory: %s\n", PATH);
  }

  // there must be a command
  if(argc < 2){
    printf("No command entered...\n");
    printValidCommands();
    return 1;
  }

  // second param must be a valid command
  if(strcmp(argv[1], "ls") == 0){
    if(argc < 3){
      listItems(DEFAULT);
    }else{
      listItems(argv[2]);
    }
  }else if(strcmp(argv[1], "mk") == 0){
    if(argc < 3){
      printf("No Group Name Provided\n");
      printf("todo mk <group>\n");
    }
    addGroup(argv[2]);
  }else if(strcmp(argv[1], "add") == 0){
    if(argc < 3){
      printf("Improper Usage\n");
      printf("todo add <item>\n");
      printf("todo add -g <group> <item>\n");
      return 1;
    }

    if(strcmp(argv[2], "-g") == 0){
      if(argc < 5){
        printf("No Group Name Provided\n");
        printf("todo add -g <group> <item>\n");
        return 1;
      }
      addItem(argv[3], argc - 4, argv + 4);
    }else{
      addItem(DEFAULT, argc - 2, argv + 2);
    }
  }else if(strcmp(argv[1], "rm") == 0){
    if(argc < 2){
      printf("todo rm <number>");
      printf("todo rm -g <group> <number>");
      return 1;
    }
    if(strcmp(argv[2], "-g") == 0){
      if(argc < 4){
        printf("todo rm -g <group> <number>");
        return 1;
      }
      int number = stringToNum(argv[4]);
      removeItem(argv[3], number);
    }else{
      int number = stringToNum(argv[2]);
      removeItem("default", number);
    }
  }else{
    printf("Invalid command %s \n\n", argv[1]);
    printValidCommands();
    return 1;
  }

  return 0;
}
