NAME	= philo
HEADER	= inc/philo.h
####################################
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -pthread -fsanitize=thread -g -Iinc
COMPILE = $(CC) $(CFLAGS)
RM		= rm -f
####################################
AR		= ar
ARFLAGS	= -rc
ARCHIVE	= $(AR) $(ARFLAGS)
####################################
SRC 	=	src/init_table.c \
			src/main.c \
			src/philo.c \
			src/print.c \
			src/set_input.c \
			src/start_dinner.c \
			src/time.c

OBJ		= $(SRC:.c=.o)
####################################

all: $(NAME)

%.o: %.c $(HEADER)
	$(COMPILE) -c $< -o $@ 

$(NAME): $(OBJ)
	$(COMPILE) $^ -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean all fclean re bonus