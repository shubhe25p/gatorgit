#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/stat.h>

#include "gatorgit.h"
#include "util.h"

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

  write_string_to_file(".gatorgit/.prev", "0000000000000000000000000000000000000000");

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
  FILE *fnewindex = fopen(".gatorgit/.newindex", "w");

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

  
}

/* gatorgit commit -m <msg>
 *
 * See "Step 3" in the homework 1 spec.
 *
 */

const char *golden_gator = "GOLDEN GATOR!";

int is_commit_msg_ok(const char *msg) {
  /* COMPLETE THE REST */
}

const char FIRST_COMMIT_ID[COMMIT_ID_SIZE] = "1111111111111111111111111111111111111111";

void next_commit_id(char *commit_id) {
  /* COMPLETE THE REST */

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
}

/* gatorgit status
 *
 * See "Step 1" in the homework 1 spec.
 *
 */

int gatorgit_status() {
  /* COMPLETE THE REST */
  FILE *findex = fopen(".gatorgit/.index", "r");

  if(findex == NULL){
    findex = fopen("./gatorgit/.index", "w");
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
  
}