NAME	=	test

CXX		=	g++
DB		=	lldb
MAKE	=	make --no-print-directory 1> /dev/null

CFLAGS	=	-Wall
CFLAGS	+=	-Wextra
CFLAGS	+=	-Werror
CFLAGS	+=	-g
CFLAGS	+=	-Wfatal-errors
CFLAGS	+=	-std=c++98

OFLAGS	=	-fsanitize=address


#	Sources

SRCD	=	src

SRCS	=	$(SRCD)/main.cpp
SRCS	+=	$(SRCD)/arguments/00_launcher.cpp
SRCS	+=	$(SRCD)/arguments/01_test.cpp
SRCS	+=	$(SRCD)/arguments/02_test.cpp


#	Headers

INCD	=	inc

INCS	+=	$(INCD)/tests.hpp

INCD_FLAGS	=	$(addprefix -I, $(INCD) framework/inc ../inc)

LIBS_FLAGS	=	$(addprefix -l, webserv unit) $(addprefix -L, .. framework)

#	Objets

OBJD	=	obj
OBJS	=	$(patsubst $(SRCD)/%.cpp, $(OBJD)/%.o, $(SRCS))

RM		=	rm -rf


all : $(NAME)

$(NAME):	$(OBJS)
	@$(MAKE) --directory=framework
	@printf "$(YELLOW)Creating executable..$(DEFAULT)\n"
	@$(CXX) $(OBJS) $(LIBS_FLAGS) $(OFLAGS) -o $(NAME)
	@printf "$(GREEN)---> $(NAME) is ready$(DEFAULT)\n"

$(OBJD)/%.o: $(SRCD)/%.cpp
	@mkdir -p $(@D)
	@$(CXX) -c $(<) $(CFLAGS) $(INCD_FLAGS) -o $(@)

db: $(NAME)
	$(DB) $(NAME)

format:
	@printf "$(YELLOW)Formating the sources..$(DEFAULT)\n"
	@clang-format -i $(shell find . -name "*.hpp" -or -name "*.cpp")

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
