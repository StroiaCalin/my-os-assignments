#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>


void extract(char* path, char* section, char* line)
{	


	int ok=0;
	char magic[5] = "TO2Y";
	
	int size_aux=0;
	int offset_aux=0;
	
	int a=atoi(section);/// conversie la int
	int b=atoi(line);

    magic[4] = '\0';
    int fd;
    short header_size=0;
    int version=0;
    short number_of_section=0;
    fd = open(path, O_RDONLY);
	char * str = calloc(strlen(magic)+1,sizeof(char));
	read(fd,str,4);
	read(fd,&header_size,2);
	//printf("%d\n",header_size);
	read(fd,&version,4);

	read(fd,&number_of_section,1);
	int * array=calloc(number_of_section,sizeof(int));
	int aux=0;
	
	
	//// bucla pentru a introduce memType in array

	for(int i=0;i<number_of_section;i++)
	{
	int aux;
	lseek(fd,13,SEEK_CUR);
	read(fd,&aux,4);
	array[i]=aux;  ////// array pentru sect_type
	lseek(fd,8,SEEK_CUR);
	}

	for(int i=0;i<number_of_section;i++)
	{
	if(array[i]!=37 && array[i]!=94 && array[i]!=87 && array[i]!=14)
	{
	printf("ERROR\ninvalid file");
	ok++;
	aux++;
	}
	}
	int linii=0;
	if(aux == 0)
	{
	lseek(fd,11,SEEK_SET);/// se intoarce unde trebe sa citeasca
	for(int i=0;i<number_of_section;i++)
	{
	char * SECTION_HEADERS = calloc(13,sizeof(char));
	read(fd,SECTION_HEADERS,13);
	int SECT_TYPE=0;
	
	read(fd,&SECT_TYPE,4);

	//printf("SECT_TYPE%d\n",SECT_TYPE);
	
	
	int SECT_OFFSET=0;
	
	read(fd,&SECT_OFFSET,4);
	//printf("SECT_OFFSET%d\n",SECT_OFFSET);
	int SECT_SIZE=0;
	read(fd,&SECT_SIZE,4);
	if(a>number_of_section)
	{
	printf("ERROR\ninvalid section");
	ok++;
	break;
	}
	if(i==a-1)
	{
	
	int pas=lseek(fd,0,SEEK_CUR);
	offset_aux=SECT_OFFSET;
	size_aux=SECT_SIZE;
	
	lseek(fd,offset_aux,SEEK_CUR);
	
	char aux;
	
	for(int i=0;i<size_aux;i++)
	{
	read(fd,&aux,1);
	if(aux=='\n')
	{
	linii++;
	}
	
	}
	lseek(fd,pas,SEEK_SET);
	if(b>linii)
	{
	printf("ERROR\ninvalid line");
	ok++;
	break;
	
	}
	}
	if(strcmp(magic,str)!= 0)
	{
	printf("ERROR\ninvalid file");
	ok++;
	break;
	}
	if(version<108 || version> 140)
	{
	printf("ERROR\ninvalid file");
	ok++;
	break;
	}
	if(number_of_section<5 || number_of_section>13)
	{
	printf("ERROR\ninvalid file");
	ok++;
	break;
	}
	}
	}
	
	char calinutz;
	//int iteratii=1;
	//printf("SUCCESS\n");
	//printf("BBBBBBBBBBBBBBBBBBBB\n%d\nBBBBBBBBBBBBBBBBBBB",b);
	//	printf("LLLL\n%d\n",linii);
	lseek(fd,offset_aux,SEEK_SET);
	char * iesire = calloc(size_aux+1,sizeof(char));
	for(int i=0;i<size_aux;i++)
	{
	read(fd,&calinutz,1);
	iesire[i]=calinutz;
	}
	iesire[size_aux]='\0';
	char *token;
    int linie = b;
    int i = linii;
    
    
   //printf("%s",iesire);
   printf("SUCCESS\n");
 
 	//printf("\nBBBBBBBBBBBBB%d\n",b);
    
    token = strtok(iesire, "\n");
    
    while (token != NULL) {
        if (i == linie-2) {
            printf("%s\n", token);
            break;
        }
        token = strtok(NULL, "\n");
        i--;
    }
    
	
	
	/*
	int iteratii=1;
	for(int i=0;i<size_aux;i++)
	{
	read(fd,&calinutz,1);
  //printf("%c",calinutz);
	if(calinutz=='\n')
	{
	iteratii++;
	}
	
	if(iteratii == linii+b)
	{
	break;
	}
	}
	char frumuselul;
	while(frumuselul!='\n')
	{
	read(fd,&frumuselul,1);
	printf("%c",frumuselul);
	}
	*/
	free(array);
	close(fd);
}





void cautareRec(const char *path)//////////////////////////// cautare recursiva
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

int cautare(char *path)////////////////////////// cautare simpla
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

void print_permission(struct stat fileStat,char * perm,char *path,char * string) {/////////////////// pentru permisiuni
    char* permissions = (char*) malloc(sizeof(char) * 10);
    memset(permissions, 0, 10);
   
    permissions[0] = (fileStat.st_mode & S_IRUSR) ? 'r' : '-';///////// stackoverflow " How to print ls -l in C"
    permissions[1] = (fileStat.st_mode & S_IWUSR) ? 'w' : '-';
    permissions[2] = (fileStat.st_mode & S_IXUSR) ? 'x' : '-';
    permissions[3] = (fileStat.st_mode & S_IRGRP) ? 'r' : '-';
    permissions[4] = (fileStat.st_mode & S_IWGRP) ? 'w' : '-';
    permissions[5] = (fileStat.st_mode & S_IXGRP) ? 'x' : '-';
    permissions[6] = (fileStat.st_mode & S_IROTH) ? 'r' : '-';
    permissions[7] = (fileStat.st_mode & S_IWOTH) ? 'w' : '-';
    permissions[8] = (fileStat.st_mode & S_IXOTH) ? 'x' : '-';
    permissions[9] ='\0';
	if(strcmp(perm,permissions)==0)
	{
	printf("%s/%s\n" ,path,string);
	}
}


int cautare_perm(char *path, char *perm)////////////////////////////////// cautare cu optiuni
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
	print_permission(statbuf,perm,path,entry->d_name);
    }
    }
    closedir(dir);
    return 0;
}


void Parse(char *path)
{
char magic[5] = "TO2Y";
    magic[4] = '\0';
    int fd;
    short header_size=0;
    int version=0;
    short number_of_section=0;
    fd = open(path, O_RDONLY);
	char * str = calloc(strlen(magic)+1,sizeof(char));
	read(fd,str,4);
	read(fd,&header_size,2);
	//printf("%d\n",header_size);
	read(fd,&version,4);

	read(fd,&number_of_section,1);
	int * array=calloc(number_of_section,sizeof(int));
	int aux=0;
	
	
	//// bucla pentru a introduce memType in array
	
	for(int i=0;i<number_of_section;i++)
	{
	int aux;
	lseek(fd,13,SEEK_CUR);
	read(fd,&aux,4);
	array[i]=aux;  ////// array pentru sect_type
	lseek(fd,8,SEEK_CUR);
	}

	for(int i=0;i<number_of_section;i++)
	{
	if(array[i]!=37 && array[i]!=94 && array[i]!=87 && array[i]!=14)
	{
	printf("ERROR\nwrong sect_types");
	aux++;
	}
	}
	
	if(aux == 0)
	{
	lseek(fd,11,SEEK_SET);/// se intoarce unde trebe sa citeasca
	for(int i=0;i<number_of_section;i++)
	{
	char * SECTION_HEADERS = calloc(13,sizeof(char));
	read(fd,SECTION_HEADERS,13);
	int SECT_TYPE;
	read(fd,&SECT_TYPE,4);
	//printf("SECT_TYPE%d\n",SECT_TYPE);
	int SECT_OFFSET;
	read(fd,&SECT_OFFSET,4);
	//printf("SECT_OFFSET%d\n",SECT_OFFSET);
	int SECT_SIZE;
	read(fd,&SECT_SIZE,4);
	
	if(strcmp(magic,str)!= 0)
	{
	printf("ERROR\nwrong magic");
	break;
	}
	if(version<108 || version> 140)
	{
	printf("ERROR\nwrong version");
	break;
	}
	if(number_of_section<5 || number_of_section>13)
	{
	printf("ERROR\nwrong sect_nr");
	
	break;
	}
	if(strcmp(magic,str)==0 && version>=108 && version <=140 && number_of_section>=5 && number_of_section <=13)
	{
	if(SECT_TYPE==37 || SECT_TYPE==94 || SECT_TYPE==87 || SECT_TYPE==14)
	{
	if(i==0){
	printf("SUCCESS\n");
	printf("version=%d\n",version);
	printf("nr_sections=%d\n",number_of_section);
	}
	printf("section%d: %s ",i+1,SECTION_HEADERS);
	printf("%d ",SECT_TYPE);
	printf("%d\n",SECT_SIZE);
	}
	}
	}
	}
	free(array);
		close(fd);
		
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
        if(strcmp(argv[1],"parse") == 0) 
        {
	char* start = strchr(argv[2],'=')+1;// imi ia pathu
	char* end = argv[2] + strlen(argv[2]);
	char path[end-start];
	strncpy(path,start,end-start);	
	path[end-start]='\0';
        Parse(path);
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
        else if(argc == 5 && strcmp(argv[1],"extract")==0)
        {
        char* start = strchr(argv[2],'=')+1;// imi ia pathu
	char* end = argv[2] + strlen(argv[2]);
	char path[end-start];
	strncpy(path,start,end-start);
	path[end-start]='\0';
        char* start1 = strchr(argv[3],'=')+1;// imi ia section
	char* end1 = argv[3] + strlen(argv[3]);
	char section[end1-start1];
	strncpy(section,start1,end1-start1);
	section[end1-start1]='\0';
	char* start2 = strchr(argv[4],'=')+1;// imi ia line
	char* end2 = argv[4] + strlen(argv[4]);
	char line[end2-start2];
	strncpy(line,start2,end2-start2);
	line[end2-start2]='\0';
	//printf("%s\n%s\n%s\n",path,section,line);
	extract(path,section,line);	
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
