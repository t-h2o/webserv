NAME	=	webserv
LIB		=	lib$(NAME).a


CXX		=	g++
AR		=	ar rs 2> /dev/null
DB		=	lldb
MAKE	=	make --no-print-directory 1> /dev/null
ADOC	=	asciidoctor --require=asciidoctor-diagram


DOCU	=	docs/README.adoc
INDEX	=	docs/index.html


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
SRCS	+=	$(SRCD)/arguments/check_argc_number.cpp


#	Headers

INCD	=	inc

INCS	+=	$(INCD)/arguments.hpp


#	Objets

OBJD	=	obj
OBJS	=	$(patsubst $(SRCD)/%.cpp, $(OBJD)/%.o, $(SRCS))

RM		=	rm -rf


all : $(NAME)

$(NAME):	$(OBJS)
	@printf "$(YELLOW)Creating executable..$(DEFAULT)\n"
	@$(CXX) $(OBJS) $(OFLAGS) -o $(NAME)
	@printf "$(GREEN)---> $(NAME) is ready$(DEFAULT)\n"

$(OBJD)/%.o: $(SRCD)/%.cpp
	@mkdir -p $(@D)
	@$(CXX) -c $(<) $(CFLAGS) -I$(INCD) -o $(@)

$(LIB): $(OBJS)
	@$(AR) $(LIB) $(OBJS)

test: $(LIB)
	@$(MAKE) --directory=test
	@printf "$(YELLOW)Launching test..$(DEFAULT)\n"
	@(test/test && printf "$(GREEN)test: SUCCESS$(DEFAULT)\n") || printf "$(RED)test: ERROR$(DEFAULT)\n"

db: $(NAME)
	$(DB) $(NAME)

format:
	@printf "$(YELLOW)Formating the sources..$(DEFAULT)\n"
	@clang-format -i $(shell find . -name "*.hpp" -or -name "*.cpp")

doc:
	@printf "$(YELLOW)Generating documentations..$(DEFAULT)\n"
	@$(ADOC) $(DOCU) -o $(INDEX)

docdocker:
	@printf "$(YELLOW)launch the asciidoctor/docker-asciidoctor docker image..$(DEFAULT)\n"
	@docker run --rm -v $(shell pwd):/documents/ asciidoctor/docker-asciidoctor make doc

clean:
	@$(RM) $(OBJD)
	@printf "$(RED)Removed $(CYAN)$(OBJD)$(DEFAULT)\n"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIB)
	@printf "$(RED)Removed $(CYAN)$(NAME)$(DEFAULT)\n"

fullclean: fclean
	@$(MAKE) --directory=test fclean
	@$(MAKE) --directory=test/framework fclean

re:	fclean all


.PHONY: all clean fclean libclean fullclean test doc


#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
DEFAULT = \033[0m
