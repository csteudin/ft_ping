# REQUIREMENTS #
NAME = ft_ping
CC = cc
CCFLAGS = -Wall -Wextra -Werror -D_GNU_SOURCE

# DOCKER #
DOCKER_DIR = ft_ping_docker
COMPOSE = docker compose -f $(DOCKER_DIR)/docker-compose.yml

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

# DOCKER TESTING SUITE
test: 
	$(COMPOSE) down --volumes --remove-orphans
	$(COMPOSE) build --no-cache
	$(COMPOSE) run --rm --cap-add=NET_RAW ft_ping bash

clean :
	rm -rf $(OBJ_DIR)
	echo "deleted object files"

fclean : clean
	rm -rf $(NAME)
	echo "deleted all files"

re : fclean all
	echo "re-creating . . ."

.PHONY : all clean fclean re