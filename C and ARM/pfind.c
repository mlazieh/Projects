/*******************************************************************************
 * Name        : pfind.c
 * Author      : Michael Lazieh
 * Pledge      : I pledge on my honor that I have abided by the Stevens Honor System
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
/*

Program that finds files with a specified set of permissions. This
program will recursively search for files whose permissions match the user specified permissions string under a
specific directory

*/

//PRINTING FILES WITH PERMISSION

// readdir() returns null when there's no more items to read
// stat() returns all the info for the item, like whether it's a file or directory

void search(char* directory, char* pstring) {
    //opendir() takes in string of directory name
    DIR *directory_pointer = opendir(directory);    //DIR is the pointer to the dirent struct
    struct dirent *entry_pointer;                   //dirent entry is a pointer to each item in the dirent
    struct stat stat_struct;

    while ((entry_pointer = readdir(directory_pointer)) != NULL) {  //goes through each file/directory
        if (strcmp(entry_pointer->d_name, ".") == 0 || strcmp(entry_pointer->d_name, "..") == 0) {
            continue;
        }
        
        char full_path[256];
        if (strcmp(directory, "/") == 0) {
            snprintf(full_path, sizeof(full_path), "%s%s", directory, entry_pointer->d_name);
        } else {
            snprintf(full_path, sizeof(full_path), "%s/%s", directory, entry_pointer->d_name);  //put a slash if there's not one there
        }
        
        int stat_val = stat(full_path, &stat_struct);   //(path,buffer)
        if (stat_val == -1) {
            exit(EXIT_FAILURE);
        }

        if (S_ISDIR(stat_struct.st_mode)) { //st.mode is the permissions
            search(full_path, pstring);
        }

        
        else if (S_ISREG(stat_struct.st_mode)) {
            char file_permissions[10]; //Array to store permission string
            int permission = S_IRUSR;   

            for (int i = 0; i <= 8; i++, permission >>= 1) {  //goes from 400 (r) to 200 (w) to 100 (x)
                file_permissions[i] = (stat_struct.st_mode & permission) ? "rwx"[i%3] : '-';  //assigns r w and x to corresponding spots
            }
            file_permissions[9] = '\0'; //put null terminator to stop seg fault

            if (strcmp(file_permissions, pstring) == 0) {
                printf("%s\n", full_path);
            }
        }
    
    }
    closedir(directory_pointer);
}


int main(int argc, char* argv[]) {
    
    //VALIDATE PERMISSION STRING
    char* pstring = argv[2];
    int pstringlen = strlen(pstring);
    
    for (int i = 0; i < 9; i++) {
        char current = pstring[i];

        if (pstringlen != 9) {
            fprintf(stderr, "Error: Permissions string '%s' is invalid.\n", pstring);
            exit(EXIT_FAILURE);
        }
        
        else if (i%3 == 0 && current != '-' && current != 'r') {
            fprintf(stderr, "Error: Permissions string '%s' is invalid.\n", pstring);
            exit(EXIT_FAILURE);
        } 
        
        else if (i%3 == 1 && current != '-' && current != 'w') {
            fprintf(stderr, "Error: Permissions string '%s' is invalid.\n", pstring);
            exit(EXIT_FAILURE);
        }

        else if (i%3 == 2 && current != '-' && current != 'x') {
            fprintf(stderr, "Error: Permissions string '%s' is invalid.\n", pstring);
            exit(EXIT_FAILURE);
        }
    }


    char* directory = argv[1];
    size_t dir_length = strlen(directory);
    
    while (dir_length > 0 && directory[dir_length - 1] == '/') {
        directory[dir_length - 1] = '\0';   //sets end to null termintor so it ends
        dir_length--;
    }

    search(directory, pstring);

    exit(EXIT_SUCCESS);
}