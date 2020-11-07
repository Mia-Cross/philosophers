NAME = philo_one

SRCDIR =	srcs
OBJDIR =	.obj
INCLUDES =	-I include/

SRCS = 	philo_one.c \
		utils.c \
		utils_itoa.c \
		parsing_and_setup.c \
		end_program.c

OBJS =	$(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
DPDCS =	$(OBJS:.o=.d)

CFLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=address -g

opti:
	@make -j all

all :
	@make $(NAME)

-include $(DPDCS)

$(NAME) : $(OBJS)
	@printf "[$(NAME)] "
	gcc $(CFLAGS) -o $(NAME) ${OBJS}
	@echo Compiled $(NAME) successfully !

$(OBJDIR)/%.o : $(SRCDIR)/%.c | $(OBJDIR)
	gcc $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR) :
	@mkdir -p .obj

clean :
	@rm -rf $(OBJDIR)

fclean : clean
	@rm -rf $(NAME)

re :
	@make fclean
	@make opti