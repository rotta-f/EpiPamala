OUTPUT_DIR = ./bin/

NAME = pamela.so

OUTPUT = $(OUTPUT_DIR)$(NAME)

SOURCES = .

SRCS = $(SOURCES)/pamela.cpp

OBJS = $(SRCS:.cpp=.o)

INCLUDE_PATH = -I./include

RM = rm -rf

CXX = g++

CPPFLAGS = -g3 -fPIC $(INCLUDE_PATH) -std=c++11

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) -shared -o $(OUTPUT) $(OBJS)
	vagrant destroy -f && vagrant up
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(OUTPUT)

re: fclean all

.PHONY: all clean fclean re