#include <stdio.h>
#include <stdlib.h>    // exit
#include <string.h>

void
writeFile(int count, char *oldBuff)
{
    fwrite(&count, 4, 1, stdout);
    fwrite(oldBuff, 1, 1, stdout);
}

int
main(int argc, char *argv[])
{
    FILE *fp;
    char buff[2], oldBuff[2];
    int count;

    if (argc <= 1) {
        printf("wzip: file1 [file2 ...]\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 1; i < argc; i++) {
        if ((fp = fopen(argv[i], "r")) == NULL) {
            printf("wzip: cannot open file\n");
            exit(EXIT_FAILURE);
        }

        while (fread(buff, 1, 1, fp)) {
            if (strcmp(buff, oldBuff) == 0) {
                count++;
            } else {
                if (oldBuff[0] != '\0')
                    writeFile(count, oldBuff);
                count = 1;
                strcpy(oldBuff, buff);
            }
        }
    }
    writeFile(count, oldBuff);
    fclose(fp);

    return 0;
}
