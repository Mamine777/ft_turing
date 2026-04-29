
# Compiler and flags
CXX       := c++
CXXFLAGS  := -Wall -Wextra -Werror -std=c++17
CPPFLAGS  := -Iinc -I$(shell brew --prefix nlohmann-json 2>/dev/null)/include
DEPFLAGS  := -MMD -MP

# Project
NAME      := turing
OBJDIR    := obj

# Sources and build files
SRCS      := src/main.cpp \
             src/parsing/utils1.cpp
OBJS      := $(SRCS:src/%.cpp=$(OBJDIR)/%.o)
DEPS      := $(OBJS:.o=.d)
LEGACY_OBJS := $(SRCS:.cpp=.o)
LEGACY_DEPS := $(SRCS:.cpp=.d)

# Default target
all: $(NAME)

# Link executable
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

# Compile .cpp to .o inside obj/
$(OBJDIR)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

# Clean object and dependency files
clean:
	rm -rf $(OBJDIR)
	rm -f $(LEGACY_OBJS) $(LEGACY_DEPS)

# Full clean
fclean: clean
	rm -f $(NAME)

# Rebuild
re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
