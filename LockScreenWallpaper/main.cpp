#include <string>
#include <dirent.h>
#include <cstring>
#include <sys/stat.h>
#include <ctime>
void run()
{
    char* home = getenv("HOMEPATH");
    char homePath[128];
    sprintf(homePath,"%s%s","C:",home);
    char dirPath[256];
    const char* suffix = R"(\AppData\Local\Packages\Microsoft.Windows.ContentDeliveryManager_cw5n1h2txyewy\LocalState\Assets)";
    sprintf(dirPath,"%s%s",homePath,suffix);
    DIR* dir;
    struct dirent* entry;
    dir = opendir(dirPath);
    char filePath[256];
    if(dir == nullptr){
        printf("open dir failure,dir is: %s, error info: %s\n",dirPath,strerror(errno));
        return;
    }
    int cnt = 1;
    while((entry = readdir(dir))!=nullptr){
        memset(filePath,0, sizeof(filePath));
        sprintf(filePath,"%s%s%s",dirPath,"\\",entry->d_name);
        struct stat status{};
        stat(filePath,&status);
        long size = status.st_size;
        long fileTime = status.st_mtime;
        long now = time(nullptr);
        //时间近一周内，大小大于100kb
        if(now-fileTime < 7*24*60*60 && size > 100*1024){
            FILE* f1,*f2;
            int c;
            char desktop[256];
            memset(desktop,0, sizeof(desktop));
            sprintf(desktop,"%s%s%ld%s%d%s",homePath,"\\Desktop\\",now,"_",cnt,".jpg");
            printf("find out %d-th picture, load to desktop\n",cnt);
            cnt ++;
            f1 = fopen(filePath,"rb");
            f2 = fopen(desktop,"wb");
            while((c=fgetc(f1))!=EOF){
                fputc(c,f2);
            }
            fclose(f1);
            fclose(f2);
        }
    }

}
int main(int argc,char** argv,char** env) {
    run();
    system("pause");
    return 0;
}