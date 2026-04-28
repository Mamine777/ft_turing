
# Compiler and flags
CXX      = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -MMD -MP
CPPFLAGS = -Iinc -I$(shell brew --prefix nlohmann-json 2>/dev/null)/include

# Executable
NAME = turing

# Sources and objects
SRCS = src/main.cpp src/parsing/utils1.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)

# Default target
all: $(NAME)

# Link executable
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Compile .cpp to .o
%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# Clean object and dependency files
clean:
	rm -f $(OBJS) $(DEPS)

# Full clean
fclean: clean
	rm -f $(NAME)

# Rebuild
re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
