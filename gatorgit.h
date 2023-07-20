int gatorgit_init(void);
int gatorgit_add(const char* filename);
int gatorgit_rm(const char* filename);
int gatorgit_commit(const char* message);
int gatorgit_status();
int gatorgit_log();

// Number of bytes in a commit id
#define COMMIT_ID_BYTES 40

// Preprocessor macros capturing the maximum size of different structures
#define FILENAME_SIZE 512
#define COMMIT_ID_SIZE (COMMIT_ID_BYTES+1)
#define MSG_SIZE 512