CC := clang++
CFLAGS := -g -Wall -std=c++11
OBJFLAGS := $(CFLAGS) -c
INC := -I include
LIB := -pthread -lreadline -lsfml-graphics -lsfml-window -lsfml-system -llua

SRCDIR := src
BUILDDIR := build
TARGET := bin/systeme

SOURCES := $(shell find $(SRCDIR) -type f -name '*.cpp')
OBJECTS := $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.cpp=.o))
DEPS := $(OBJECTS:%.o=%.d)

.SECONDEXPANSION:
.PHONY: clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo -e "Linking"
	@mkdir -p $$(dirname $@)
	$(CC) $(INC) $(LIB) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $$(dirname $@)
	@echo -e "Building $@"
	$(CC) $(INC) $(OBJFLAGS) -o $@ -MMD -MP -MF ${@:.o=.d} $<

clean:
	rm -rf $(BUILDDIR) $(TARGET) vgcore* core log
	rmdir bin

-include $(DEPS)
