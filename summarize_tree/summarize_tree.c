#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

static int num_dirs, num_regular;

bool is_dir(const char* path) {
  /*
   * Use the stat() function (try "man 2 stat") to determine if the file
   * referenced by path is a directory or not.  Call stat, and then use
   * S_ISDIR to see if the file is a directory. Make sure you check the
   * return value from stat in case there is a problem, e.g., maybe the
   * the file doesn't actually exist.
   */
  bool b = false;
  struct stat s;
  if( stat(path, &s) == 0){
    printf("in stat stuff\n");
    if(S_ISDIR(s.st_mode) ){
      b = true;
    }
  }
  return b;
}


/* 
 * I needed this because the multiple recursion means there's no way to
 * order them so that the definitions all precede the cause.
 */
void process_path(const char* path);

void process_file(const char* path) {
  /*
   * Update the number of regular files.
   */
  num_regular++;
  printf("This is number of regular %d\n", num_regular++);
}
void process_directory(const char* path) {
  /*
   * Update the number of directories seen, use opendir() to open the
   * directory, and then use readdir() to loop through the entries
   * and process them. You have to be careful not to process the
   * "." and ".." directory entries, or you'll end up spinning in
   * (infinite) loops. Also make sure you closedir() when you're done.
   *
   * You'll also want to use chdir() to move into this new directory,
   * with a matching call to chdir() to move back out of it when you're
   * done.
   */
  num_dirs++;
   printf("This is number of directories %d\n", num_dirs++);
  DIR *dir = opendir(path);
  struct dirent *entry;

  chdir(path);
 
    while((entry = readdir(dir)) != NULL){
      if(strcmp(entry->d_name, ".") != 0 || strcmp(entry->d_name, "..") != 0){
	process_path(entry->d_name);
      }
      
    }
 closedir(dir);
 chdir("..");
  }



void process_path(const char* path) {
  printf("In process path\n");
  if (is_dir(path)) {
    printf("Going to process directory\n");
    process_directory(path);
  } else {
    process_file(path);
  }
}

int main (int argc, char *argv[]) {
  // Ensure an argument was provided.
  if (argc != 2) {
    printf ("Usage: %s <path>\n", argv[0]);
    printf ("       where <path> is the file or root of the tree you want to summarize.\n");
    return 1;
  }

  num_dirs = 0;
  num_regular = 0;

  process_path(argv[1]);

  printf("Processed all the files from <%s>.\n", argv[1]);
  printf("There were %d directories.\n", num_dirs);
  printf("There were %d regular files.\n", num_regular);

  return 0;
}
