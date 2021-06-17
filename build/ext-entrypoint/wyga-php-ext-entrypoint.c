#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ARG_DEP_LONG "--dependencies"
#define ARG_DEP "-d"
#define ARG_QUIET_LONG "--quiet"
#define ARG_QUIET "-q"
#define ARG_INFO_LONG "--info"
#define ARG_INFO "-i"

#define WYGA "/wyga/php/ext"
#define MODULE "/module.dep"
#define VERSION "/version"
#define REQUIRE "/require"

/*
* Wyswietla plik w jeden lini (chomp(nl))
*/
int showfile(char *file,char *prefix,char *suffix) {
    FILE *fp;
    char line[255];
    
    if((fp = fopen(file,"r"))) {
        int _first=1;
        if(prefix) printf("%s",prefix);
        while(fgets (line, sizeof line, fp)) {
            line[strcspn(line, "\n")] = 0;
            if(_first) {
                if(strlen(line)) {
                    printf("%s",line);
                    _first=0;
                }
            } else {
                if(strlen(line)) printf(" %s",line);
            }
        }
        if(suffix) printf("%s",suffix);
        fclose(fp);
        return (0);
    }
    return (1);
}

/*
* wyszukuje pierwszy katalog w podanym katalogu
* sprawdza czy nie istnieja inne katalogi w podanej sciezszcze
*/
int find_first_dir(char *path,char *ext, int n) {
    DIR *dir;
    struct dirent* dent;
    struct stat st;
    int dirs=0;
    char found[512];
    
    if((dir = opendir(path))) {
        while((dent = readdir(dir)) && dirs < 2) {
            if(strcmp(dent->d_name, ".") == 0 || strcmp(dent->d_name, "..") == 0) continue;
            if (fstatat(dirfd(dir), dent->d_name, &st, 0) < 0) continue;
            if (S_ISDIR(st.st_mode)) {
                dirs++;
                if(dirs==1) strncpy(found,dent->d_name,sizeof found);
            }
        }
        closedir(dir);
    }
    if(dirs==1 && ext) {
        strncpy(ext,found,n);
        return (0);
    }    
    return (1);
}
int main(int ac, char **av) {
int a_deps = 0;
int f_quiet = 0;
int info = 0;
char ext[128];
char fn[256];
    if(ac>1) {
        for(int i=1;i<ac;i++) {
            if(strcmp(av[i], ARG_DEP_LONG) == 0) a_deps=1;
            if(strcmp(av[i], ARG_DEP) == 0) a_deps=1;
            if(strcmp(av[i], ARG_QUIET_LONG) == 0) f_quiet=1;
            if(strcmp(av[i], ARG_QUIET) == 0) f_quiet=1;
            if(strcmp(av[i], ARG_INFO_LONG) == 0) info=1;
            if(strcmp(av[i], ARG_INFO) == 0) info=1;
        }
    }
    if(info && find_first_dir(WYGA,ext,sizeof ext) == 0) {
        printf("ext: %s\n",ext);
        snprintf(fn,sizeof fn,"%s/%s/%s",WYGA,ext,VERSION);
        showfile(fn,"version: ","\n");
        snprintf(fn,sizeof fn,"%s/%s/%s",WYGA,ext,REQUIRE);
        showfile(fn,"require: ","\n");
        if(a_deps) {
            snprintf(fn,sizeof fn,"%s/%s/%s",WYGA,ext,MODULE);
            showfile(fn,"deps: ","\n");
	}
    }
    if(!f_quiet) {
        printf("This is intermeditate image for wyga/php. Please don't use it directly.\n");
        printf("See https://github.com/rjsocha/wyga-php for the usage guidelines.\n");
    }
    return (1);
}
