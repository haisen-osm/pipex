#include "pipex.h"

char *ft_strjoin(char *s1, char *s2)
{
    int (i), (j);
    char *joined_str;

    if (!s1 || !s2)
        return (NULL);
    i = 0;
    joined_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!joined_str)
        return (NULL);
    while (s1[i])
    {
        joined_str[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2[j])
    {
        joined_str[i + j] = s2[j];
        j++;
    }
    joined_str[i + j] = '\0';
    return (joined_str);
}
