NAME	=	libunit.a

AR		=	ar rs 2> /dev/null
DB		=	lldb

CFLAGS	=	-Wall
CFLAGS	+=	-Wextra
CFLAGS	+=	-Werror
CFLAGS	+=	-g
CFLAGS	+=	-Wfatal-errors
CFLAGS	+=	-std=c++98

OFLAGS	=	-fsanitize=address


#	Sources

SRCD	=	src

SRCS	+=	$(SRCD)/Unit_test.cpp
SRCS	+=	$(SRCD)/Test.cpp
SRCS	+=	$(SRCD)/Result.cpp


#	Headers

INCD	=	inc

INCS	+=	$(INCD)/Unit_test.hpp
INCS	+=	$(INCD)/Test.hpp
INCS	+=	$(INCD)/Result.hpp


#	Objets

OBJD	=	obj
OBJS	=	$(patsubst $(SRCD)/%.cpp, $(OBJD)/%.o, $(SRCS))

RM		=	rm -rf


all : $(NAME)

$(NAME):	$(OBJS)
	@printf "$(YELLOW)Creating archive..$(DEFAULT)\n"
	@$(AR) $(NAME) $(OBJS) > /dev/null
	@printf "$(GREEN)---> $(NAME) is ready$(DEFAULT)\n"

$(OBJD)/%.o: $(SRCD)/%.cpp
	@mkdir -p $(@D)
	@$(CXX) -c $(<) $(CFLAGS) -I$(INCD) -o $(@)

format:
	@printf "$(YELLOW)Formating the sources..$(DEFAULT)\n"
	@clang-format -i $(SRCS) $(INCS)

clean:
	@$(RM) $(OBJD)
	@printf "$(RED)Removed $(CYAN)$(OBJD)$(DEFAULT)\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "$(RED)Removed $(CYAN)$(NAME)$(DEFAULT)\n"

re:	fclean all


.PHONY: all clean fclean libclean fullclean


#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
DEFAULT = \033[0m
