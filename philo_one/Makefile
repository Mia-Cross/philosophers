NAME = philo_one

SRCDIR = srcs
OBJDIR = .obj
INCDIR = include

SRCS = 	philo_one.c \
		utils.c

OBJS =		$(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
INCLUDES =	philo_one.h
DPDCS =		$(OBJS:.o=.d)

CFLAGS = -Wall -Wextra -Werror

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
	gcc $(CFLAGS) -c $< -o $@

$(OBJDIR) :
	@mkdir -p .obj

clean :
	@rm -rf $(OBJDIR)

fclean : clean
	@rm -rf $(NAME)

re :
	@make fclean
	@make opti