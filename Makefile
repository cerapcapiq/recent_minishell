NAME		= minishell
INC			= include
HEADER		= -I include
LIBFT		= libft/
SRC_DIR		= src/
OBJ			= $(SRC:.c=.o)
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -g -fsanitize=address
RM			= rm -f

GREEN		=	\033[1;92m
YELLOW		=	\033[1;93m
BLUE		=	\033[0;94m
WHITE		=	\033[0;97m

BLT_DIR		=	builtin/
BLT_FILES	=	ft_echo ft_pwd ft_exit ft_cd export_unset ft_cd_utils
EXECUTE_DIR	=	execute/
EXECUTE_FILES	=	execute_utils execute_builtin ft_execve execute 
MAIN_DIR	=	main/
MAIN_FILES	=	main signal
PARSE_DIR	=	parse/
PARSE_FILES	=	parser  token parser_utils new_split token_utils
ENV_DIR     =	env/
ENV_FILES	=	env env_helper var_space mem_free env_utils var_space_utils var_space_helper
REDIR_DIR	=   redirect/
REDIR_FILES =   dollar pipe quote redirection redirection_utils

SRC_FILES	=	$(addprefix $(BLT_DIR), $(BLT_FILES))\
					$(addprefix $(EXECUTE_DIR), $(EXECUTE_FILES))\
					$(addprefix $(MAIN_DIR), $(MAIN_FILES))\
					$(addprefix $(PARSE_DIR), $(PARSE_FILES))\
					$(addprefix $(ENV_DIR), $(ENV_FILES))\
					$(addprefix $(REDIR_DIR), $(REDIR_FILES))

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))

start:
			@echo "$(YELLOW)Start Make:$(WHITE)"
			@make all

all:		$(NAME)

$(NAME):	$(OBJ)
			@make -C $(LIBFT)
			@cp libft/libft.a .
			@$(CC) $(CFLAGS) $(OBJ) $(HEADER) libft.a -o $(NAME) -lreadline 
			@echo "$(GREEN)minishell Done!$(WHITE)"
			@clear

%.o: %.c
			@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

clean:
			@$(RM) $(OBJ)
			@make clean -C $(LIBFT)
			@echo "$(BLUE)minishell: object files have been cleaned!$(WHITE)"

fclean:		clean
			@$(RM) $(NAME)
			@$(RM) libft.a
			@$(RM) $(LIBFT)/libft.a
			@echo "$(BLUE)Libft: files have been cleaned!$(WHITE)"
			@echo "$(BLUE)minishell: files have been cleaned!$(WHITE)"


re:			fclean all
			@echo "$(GREEN)Cleaned and rebuilt everything for minishell\n$(WHITE)"

.PHONY:		all clean fclean re
