CC = cc

FLAGS = -Wall -Wextra -Werror

SRCFILES = pipex.c ft_split.c ft_strlen.c ft_strdup.c ft_substr.c ft_strjoin.c

all: $(SRCFILES)
	$(CC) $(FLAGS) $(SRCFILES) -g -o pipex

