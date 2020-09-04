#include <errno.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int busNumMaxLen = 16;
int devVenLen = 16;

int main()
{

    char *pciDevDirPath = "/sys/bus/pci/devices";
    int pciDevDirPathLen = strlen(pciDevDirPath);


    char *devPath = malloc(pciDevDirPathLen + busNumMaxLen + devVenLen);
    char *venPath = malloc(pciDevDirPathLen + busNumMaxLen + devVenLen);



    strcpy(devPath, pciDevDirPath);
    strcpy(venPath, pciDevDirPath);

    DIR *pciDevDir = opendir(pciDevDirPath);

    puts("vendorID -- deviceID");

    struct dirent *dire = NULL;

    while ( (dire = readdir(pciDevDir)) ){

        if (!strcmp(dire->d_name, ".") || !strcmp(dire->d_name, ".."))
            continue;

        sprintf(devPath + pciDevDirPathLen, "/%s/%s", dire->d_name, "device");
        sprintf(venPath + pciDevDirPathLen, "/%s/%s", dire->d_name, "vendor");

        char devCode[7] = {'\0'};
        char venCode[7] = {'\0'};

        int devCodeFD = open(devPath, O_RDONLY);
        int venCodeFD = open(venPath, O_RDONLY);

        if (devCodeFD == -1 || venCodeFD == -1){
            perror("ERROR");
            return 1;
        }

        read(devCodeFD, devCode, 6);
        read(venCodeFD, venCode, 6);

        close(devCodeFD);
        close(devCodeFD);

        printf("%s -- %s\n", venCode, devCode);

    }
    return 0;

}
