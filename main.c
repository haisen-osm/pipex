#include "pipex.h"

char *check_if_valid(const char *cmd)
{
	size_t	arglen = ft_strlen(cmd);
	while (arglen)
	{
		if (cmd[arglen] != '/')
			arglen--;
		else
			break;
	}
	while (arglen)
	{
		if (cmd[arglen] != '/')
		{
			return (char *)cmd;
		}
		arglen--;
	}
	return NULL;
}

int main(int argc, char const *argv[])
{
	if (argv[1])
	{
		char *test = check_if_valid(argv[1]);
		if (test)
		{
		int access_status = access(test, X_OK | F_OK);
		printf("%d\n",access_status);
		}
		else{
			printf("error !\n");
		}
	}
	return 0;
}
