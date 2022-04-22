NAME		=	philo

SRCS		= 	philo.c philo_action.c utils.c monitor.c

OBJ			=	$(SRCS:%.c=%.o)

#FLAGS		=	-fsanitize=thread -pthread

.PHONY		:	all clean fclean re

all			:	$(NAME)

%.o			:	%.c
					@gcc $(FLAGS) -c $< -o $@

$(NAME)		:	$(OBJ)
					@gcc $(FLAGS) -o $(NAME) $(OBJ)

clean		:	
					@rm -f $(OBJ)

fclean		:	clean
					@rm -f $(NAME)

re			:	fclean all
