#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/stat.h>

#include "gatorgit.h"
#include "util.h"
#include "dirent.h"
#include "math.h"
#include "string.h"
#define gatorgit_DIR_NAME_SIZE  9
#define COMMIT_DIR_PATH_SIZE (gatorgit_DIR_NAME_SIZE + COMMIT_ID_SIZE)
#define COMMIT_FILE_PATH_SIZE (COMMIT_DIR_PATH_SIZE + FILENAME_SIZE)

/* Implementation Notes:
 *
 * - Functions return 0 if successful, 1 if there is an error.
 * - All error conditions in the function description need to be implemented
 *   and written to stderr. We catch some additional errors for you in main.c.
 * - Output to stdout needs to be exactly as specified in the function description.
 * - Only edit this file (gatorgit.c)
 * - You are given the following helper functions:
 *   * fs_mkdir(dirname): create directory <dirname>
 *   * fs_rm(filename): delete file <filename>
 *   * fs_mv(src,dst): move file <src> to <dst>, overwriting <dst> if it exists
 *   * fs_cp(src,dst): copy file <src> to <dst>, overwriting <dst> if it exists
 *   * write_string_to_file(filename,str): write <str> to filename (overwriting contents)
 *   * read_string_from_file(filename,str,size): read a string of at most <size> (incl.
 *     NULL character) from file <filename> and store it into <str>. Note that <str>
 *     needs to be large enough to hold that string.
 *  - You NEED to test your code. The autograder we provide does not contain the
 *    full set of tests that we will run on your code. See "Step 5" in the homework spec.
 */

/* gatorgit init
 *
 * - Create .gatorgit directory
 * - Create empty .gatorgit/.index file
 * - Create .gatorgit/.prev file containing 0..0 commit id
 *
 * Output (to stdout):
 * - None if successful
 */

int gatorgit_init(void) {
  fs_mkdir(".gatorgit");

  FILE *findex = fopen(".gatorgit/.index", "w");
  fclose(findex);
  FILE *fprev = fopen(".gatorgit/.prev", "w");

  fprintf(fprev, "%s\n", "0000000000000000000000000000000000000000");
  // write_string_to_file(".gatorgit/.prev", "0000000000000000000000000000000000000000");
  return 0;
}


/* gatorgit add <filename>
 *
 * - Append filename to list in .gatorgit/.index if it isn't in there yet
 *
 * Possible errors (to stderr):
 * >> ERROR: File <filename> already added
 *
 * Output (to stdout):
 * - None if successful
 */

int gatorgit_add(const char *filename) {
  FILE *findex = fopen(".gatorgit/.index", "r");
  if(findex == NULL) {
    fprintf(stderr, "ERROR: File .gatorgit/.index does not exist, creating a new one, try again...\n");
    FILE *fnewindex = fopen(".gatorgit/.index", "w");
    fclose(fnewindex);
    return 1;
  }
  FILE *fnewindex = fopen(".gatorgit/.newindex", "w");

  if(filename[0] == '.') {
    //print all files in the given directory
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (filename)) != NULL) {
      /* print all the files and directories within directory */
      while ((ent = readdir (dir)) != NULL) {
        if(ent->d_name[0] == '.') continue;
        fprintf (fnewindex, "%s\n", ent->d_name);
      }
      fclose(fnewindex);
      fclose(findex);
      fs_mv(".gatorgit/.newindex", ".gatorgit/.index");
      closedir (dir);
    } else {
      /* could not open directory */
      perror ("");
      return EXIT_FAILURE;
    }
    return 0;
  }

  char line[FILENAME_SIZE];
  while (fgets(line, sizeof(line), findex)) {
    strtok(line, "\n");
    if (strcmp(line, filename) == 0) {
      fprintf(stderr, "ERROR: File %s already added\n", filename);
      fclose(findex);
      fclose(fnewindex);
      fs_rm(".gatorgit/.newindex");
      return 3;
    }

    fprintf(fnewindex, "%s\n", line);
  }

  fprintf(fnewindex, "%s\n", filename);
  fclose(findex);
  fclose(fnewindex);

  fs_mv(".gatorgit/.newindex", ".gatorgit/.index");

  return 0;
}


/* gatorgit rm <filename>
 *
 * See "Step 2" in the homework 1 spec.
 *
 */

int gatorgit_rm(const char *filename) {
  /* COMPLETE THE REST */
  FILE *findex = fopen(".gatorgit/.index", "r");
  FILE *fnewindex = fopen(".gatorgit/.newindex", "w");
  if(findex == NULL) {
    fprintf(stderr, "ERROR: File .gatorgit/.index does not exist, try again...\n");
    FILE *fnewindex = fopen(".gatorgit/.index", "w");
    fclose(fnewindex);
    return 1;
  }
  char line[FILENAME_SIZE];
  int found = 0;
  while(fgets(line, sizeof(line), findex)) {
    strtok(line, "\n");
    if(strcmp(line, filename) != 0) {
      fprintf(fnewindex, "%s\n", line);
    }
    else {
      found = 1;
    }
  }
  if(found==0){
    fprintf(stderr, "ERROR: File %s not found in .gatorgit/.index, try again...\n", filename);
    fclose(findex);
    fclose(fnewindex);
    fs_rm(".gatorgit/.newindex");
    return 2;
  }
  fclose(findex);
  fclose(fnewindex);
  fs_mv(".gatorgit/.newindex", ".gatorgit/.index");
  
}

/* gatorgit commit -m <msg>
 *
 * See "Step 3" in the homework 1 spec.
 *
 */

const char *golden_gator = "GOLDEN GATOR!";

int is_commit_msg_ok(const char *msg) {
  /* COMPLETE THE REST */
  int i = 0;
  if(getlength(msg) < getlength(golden_gator)){
    return 0;
  }
  else{
    while(i < 13){
    if(*msg == golden_gator[i]){
      i++;
    }
    else{
      return 0;
    }
    msg++;
  }
  return 1;
  }

}

const char FIRST_COMMIT_ID[COMMIT_ID_SIZE] = "1111111111111111111111111111111111111111";

void next_commit_id(char *commit_id) {
  /* COMPLETE THE REST */

  int cnt = 0;
  for(int i=0;i<strlen(commit_id);i++){
    if(commit_id[i] == '0'){
      cnt++;
    }
  }
  if(cnt == strlen(commit_id)){
    while(cnt>0){
      *commit_id = *FIRST_COMMIT_ID;
      commit_id++;
      cnt--;
    }
  }
  else{
    int i=strlen(commit_id)-2;
    while(i>=0){
      if(commit_id[i] == 'c') i--;
      else {
        if(commit_id[i] == '1'){
          commit_id[i] = '6';
        }
        else if(commit_id[i] == '6'){
          commit_id[i] = 'c';
        }
        else{
          commit_id[i] = '1';
        }
        break;
      }
    }
  }

}

int gatorgit_commit(const char *msg) {
  if (!is_commit_msg_ok(msg)) {
    fprintf(stderr, "ERROR: Message must contain \"%s\"\n", golden_gator);
    return 1;
  }

  char commit_id[COMMIT_ID_SIZE];
  read_string_from_file(".gatorgit/.prev", commit_id, COMMIT_ID_SIZE);
  next_commit_id(commit_id);

  /* COMPLETE THE REST */

  char new_dir[COMMIT_ID_SIZE+40] = ".gatorgit/";
  const char *commit_dir = strcat(new_dir, commit_id);
  fs_mkdir(commit_dir);
  const char *index_dir = strcat(new_dir, "/.index");
  fs_cp(".gatorgit/.index", index_dir);
  new_dir[strlen(new_dir)-7] = '\0';
  const char *prev_dir = strcat(new_dir, "/.prev");
  fs_cp(".gatorgit/.prev", prev_dir);
  new_dir[strlen(new_dir)-6] = '\0';
  const char *msg_dir = strcat(new_dir, "/.msg");
  FILE *fmsg = fopen(msg_dir, "w");
  // write_string_to_file(fmsg, msg);
  fprintf(fmsg, "%s\n", msg);
  fclose(fmsg);
  FILE *fprev = fopen(".gatorgit/.prev", "w");
  // write_string_to_file(fprev, commit_id);
  fprintf(fprev, "%s\n", commit_id);
  fclose(fprev);
  return 0;

}

/* gatorgit status
 *
 * See "Step 1" in the homework 1 spec.
 *
 */

int gatorgit_status() {
  /* COMPLETE THE REST */
  FILE *findex;

  findex = fopen(".gatorgit/.index", "r");

  if(findex == NULL){
    printf("Index file was missing, created a new one, try again \n");
    fclose(findex);
    FILE *findex = fopen(".gatorgit/.index", "w");
    fclose(findex);
    return 0;
  }
  char line[FILENAME_SIZE];
  printf("Tracked files: \n\n");
  int cnt=0;
  while(fgets(line, sizeof(line), findex)){
    strtok(line, "\n");
    printf("\t%s\n", line);
    cnt++;
  }
  printf("\n%d files in total", cnt);
  fclose(findex);
  return 0;
  
}

/* gatorgit log
 *
 * See "Step 4" in the homework 1 spec.
 *
 */

int gatorgit_log() {
  /* COMPLETE THE REST */
  char commit_id[COMMIT_ID_SIZE];
  read_string_from_file(".gatorgit/.prev", commit_id, COMMIT_ID_SIZE);
  printf("\n");
  while(strcmp(commit_id, "0000000000000000000000000000000000000000\n")){
    printf("commit %s\n", commit_id);
    char new_dir[COMMIT_ID_SIZE] = ".gatorgit/";
    const char *commit_dir = strcat(new_dir, commit_id);
    const char *msg_dir = strcat(new_dir, "/.msg");
    FILE *fmsg = fopen(new_dir, "r");
    char msg[MSG_SIZE];
    fgets(msg, sizeof(msg), fmsg);
    strtok(msg, "\n");
    printf("\t%s\n\n", msg);
    fclose(fmsg);
    new_dir[strlen(new_dir)-5] = '\0';
    const char *prev_dir = strcat(new_dir, "/.prev");
    read_string_from_file(prev_dir, commit_id, COMMIT_ID_SIZE);   
  }

}