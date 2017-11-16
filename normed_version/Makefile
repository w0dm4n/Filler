# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/20 17:57:50 by frmarinh          #+#    #+#              #
#    Updated: 2017/11/07 02:01:27 by frmarinh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_FILLER	=	filler
EXE_NAME	=	frmarinh.filler

NAME		=   filler
NAMEBASE    =   $(shell basename $(NAME))
LENGTHNAME	=	`printf "%s" $(NAMEBASE) | wc -c`
MAX_COLS	=	$$(echo "$$(tput cols)-24-$(LENGTHNAME)"|bc)

CC			= gcc
FLAGS		=
FLAGS_O		=
#FLAGS		= -Wall -Wextra -Werror
#FLAGS_O		= -Wall -Wextra -Werror

SRCDIR_FILLER		=	srcs/
OBJDIR_FILLER		=	objs/

INCDIR				=	includes/
LIBFT_DIR			=	libft/
LIBFT_LIB			=	$(LIBFT_DIR)libft.a

SRCBASE_FILLER	=	\
					main.c						\
					filler.c					\
					map.c						\
					logger.c					\
					piece.c						\
					utils.c						\
					finder.c					\
					point.c						\
					resolver.c					\
					solution.c					\
					enemy.c						\

SRCS_FILLER			=	$(addprefix $(SRCDIR_FILLER), $(SRCBASE_FILLER))
OBJS_FILLER			=	$(addprefix $(OBJDIR_FILLER), $(SRCBASE_FILLER:.c=.o))

.SILENT:

all:		$(NAME)

$(NAME):
	if test -f $(EXE_NAME) ; then												\
		echo "make: Nothing to be done for \`all\`.";				        		\
	else																			\
		make re -C libft/ &&														\
		make FILLER && 																\
		echo "\r\033[38;5;184m👥  AUTHOR(s): \033[0m\033[K" && 						\
		echo "\r\033[38;5;15m`cat auteur | sed s/^/\ \ \ \ -/g`\033[0m\033[K" &&	\
		echo "\033[38;5;44m☑️  ALL    $(NAMEBASE) is done\033[0m\033[K";				\
	fi

$(OBJDIR_FILLER):
	mkdir -p $(OBJDIR_FILLER)
	mkdir -p $(dir $(OBJS_FILLER))

$(OBJDIR_FILLER)%.o : $(SRCDIR_FILLER)%.c | $(OBJDIR_FILLER)
	$(CC) $(FLAGS) -MMD -c $< -o $@											\
		-I $(LIBFT_DIR)$(INCDIR)											\
		-I $(INCDIR)														\

fcleanlib:	fclean
	make -C $(LIBFT_DIR) fclean

re:			fclean all

relib:		fclean fcleanlib all

.PHONY:		fclean fcleanlib clean re relib

FILLER: $(OBJDIR_FILLER) $(OBJS_FILLER)
	make -C $(LIBFT_DIR)
	$(CC) $(FLAGS) $(FLAGS_O) -o $(EXE_NAME) $(OBJS_FILLER) $(LIBFT_LIB)
	echo "\r\033[38;5;22m📗  MAKE $(NAME_FILLER)"

clean:
	@rm -rf $(OBJDIR_FILLER)
	@make -C $(LIBFT_DIR) clean
	echo "\r\033[38;5;124m📕  CLEAN $(OBJDIR_FILLER)\033[0m\033[K";

fclean:		clean
	@rm -rf $(EXE_NAME)
	@make -C $(LIBFT_DIR) fclean
	echo "\r\033[38;5;124m📕  FCLEAN $(NAME_FILLER)\033[0m\033[K";

-include $(OBJS:.o=.d)
