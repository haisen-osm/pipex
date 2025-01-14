#include <unistd.h>
#include <stdio.h>

int che(char *str, char c, int i)
{
    // int i = 0;
    int flag = 0;
    // if (str[0] == c)
    // {
    //     printf("%c",c);
    //     return;
    // }
    int j = 0;
    while (j < i)
    {
        if (str[j] == c)
            flag = 1;
        j++;
    }
    // if (!str[i] && flag == 1)
    //     printf("%c",c);
    return flag;
}

int main(int argc, char const *argv[])
{
    // printf("%s               ",argv[1]);
    // printf("%s",argv[2]);
    // char str1[256] = {0};
    // int j = 0;
    // while (j < 256)
    // {
    //   printf("%d\n",str1[j]);
    //   j++;  
    // }

    int i = 0;
    while (argv[1][i])
    {
        if (che((char *)argv[1],argv[1][i],i) == 0)
            printf("%c",argv[1][i]);
        i++;
    }
    // zpadinto
    // qfwtjey
    int j = 0;
    // printf("\n------------\n");
    while (argv[2][j])
    {
        if (che((char *)argv[2],argv[2][j],j) == 0)
        {
            if(che((char *)argv[1],argv[2][j],i) == 0)
                printf("%c",argv[2][j]);
        }
        j++;
    }
    
    // while (argv[1][i])
    // {
    //     if (str1[i] == 0)
    //     {
    //         str1[i] = argv[1][i];
    //     }
    //     che(str1,str1[i]);
    //     i++;
    // }
    // j = 0;
    // while (j < 256)
    // {
    //   printf("%d\n",str1[j]);
    //   j++;  
    // }
    
    return 0;
}
