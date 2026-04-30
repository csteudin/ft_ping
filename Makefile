# REQUIREMENTS #
NAME = ft_ping
CC = cc
CCFLAGS = -Wall -Wextra -Werror -D_GNU_SOURCE

# DIRECTORYZ #
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj

# FILEZ #
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# RULEZ #
.SILENT :

all : $(NAME)

$(NAME) : $(OBJ_FILES)
	$(CC) $(CCFLAGS) $^ -o $@
	echo "$(NAME) got compiled"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CCFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ_DIR)
	echo "deleted object files"

fclean : clean
	rm -rf $(NAME)
	echo "deleted all files"

re : fclean all
	echo "re-creating . . ."

.PHONY : all clean fclean re