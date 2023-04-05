#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

void cautareRec(const char *path)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char fullPath[512];
    struct stat statbuf;

    dir = opendir(path);
    if(dir == NULL) {
        perror("Could not open directory");
        return;
    }
    while((entry = readdir(dir)) != NULL) {
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            snprintf(fullPath, 512, "%s/%s", path, entry->d_name);
            if(lstat(fullPath, &statbuf) == 0) {
                printf("%s\n", fullPath);
                if(S_ISDIR(statbuf.st_mode)) {
                    cautareRec(fullPath);
                }
            }
        }
    }
    closedir(dir);
}

int cautare(char *path)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char filePath[512];
    struct stat statbuf;

    dir = opendir(path);
    if(dir == NULL) {
        printf("ERROR\ninvalid directory path\n");
        return -1;
    }
    	   printf("SUCCESS\n");
    while((entry = readdir(dir)) != NULL) {
        snprintf(filePath, 512, "%s/%s", path, entry->d_name);
        if(lstat(filePath, &statbuf) == 0 && strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0 ){
        printf("%s/%s\n", path,entry->d_name);
    }
    }
    closedir(dir);
    return 0;

}

char* print_permission(const char *path) {
    struct stat st;
    static char mode_str[10];
    if (stat(path, &st) == 0) {
        const char *perms = "rwxrwxrwx";
        mode_str[0] = '-';
        mode_t mode = st.st_mode;
        if (S_ISREG(mode)) mode_str[0] = '-';
        if (S_ISDIR(mode)) mode_str[0] = 'd';
        if (S_ISLNK(mode)) mode_str[0] = 'l';
        if (mode & S_IRUSR) mode_str[1] = perms[0];
        if (mode & S_IWUSR) mode_str[2] = perms[1];
        if (mode & S_IXUSR) mode_str[3] = perms[2];
        if (mode & S_IRGRP) mode_str[4] = perms[3];
        if (mode & S_IWGRP) mode_str[5] = perms[4];
        if (mode & S_IXGRP) mode_str[6] = perms[5];
        if (mode & S_IROTH) mode_str[7] = perms[6];
        if (mode & S_IWOTH) mode_str[8] = perms[7];
        if (mode & S_IXOTH) mode_str[9] = perms[8];
    }
    return mode_str;
}




int cautare_perm(char *path, char *perm)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char filePath[512];
    struct stat statbuf;
	   printf("SUCCESS\n");
    dir = opendir(path);
    if(dir == NULL) {
        perror("Could not open directory");
        return -1;
    }
    while((entry = readdir(dir)) != NULL) 
    {
        snprintf(filePath, 512, "%s/%s", path, entry->d_name);
        if(lstat(filePath, &statbuf) == 0 && strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0)
        {
        if(strncmp(entry->d_name,perm,strlen(perm))==0)
       { 
        printf("%s/%s\n", path,entry->d_name);
	}
	if(strcmp(perm,print_permission(path)) == 0)
	{
	printf("%s/%s\n", path,entry->d_name);
	}
    }
    }
    closedir(dir);
    return 0;
}

int main(int argc, char **argv){
if(argc == 1)
{
printf("ERROR\nno arguments");
}
    if(argc >= 2){
        if(strcmp(argv[1], "variant") == 0){
            printf("93193\n");
        }
        if(strcmp(argv[1], "list") == 0 && strcmp(argv[2],"recursive") == 0){
        char* start = strchr(argv[3],'=')+1;
	char* end = argv[3] + strlen(argv[3]);
	char path[end-start];
	strncpy(path,start,end-start);
	path[end-start]='\0';
	printf("SUCCESS\n");
            cautareRec(path);
            }
      else if(argc == 4 && strcmp(argv[1], "list") == 0){   ////// aici am conditii
        char* start = strchr(argv[3],'=')+1;// imi ia pathu
	char* end = argv[3] + strlen(argv[3]);
	char path[end-start];
	strncpy(path,start,end-start);
	path[end-start]='\0';	      
        char* start1 = strchr(argv[2],'=')+1;// imi ia conditii
	char* end1 = argv[2] + strlen(argv[2]);
	char conditii_perm[end1-start1];
	strncpy(conditii_perm,start1,end1-start1);
	conditii_perm[end1-start1]='\0';
        cautare_perm(path,conditii_perm);
        }
        else if( argc == 3 && strcmp(argv[1],"list") == 0) {   /////// aici nu am conditii
       	char* start = strchr(argv[2],'=')+1;// imi ia pathu
	char* end = argv[2] + strlen(argv[2]);
	char path[end-start];
	strncpy(path,start,end-start);	
	path[end-start]='\0';
	cautare(path);
	}
    }
    return 0;
}
