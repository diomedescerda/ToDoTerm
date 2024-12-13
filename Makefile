CC = gcc
CFLAGS = -Wall -I./include

OBJDIR = src/obj
BINDIR = bin
SRCDIR = src
MODDIR = src/modules

SRCS = $(wildcard $(SRCDIR)/*.c) $(wildcard $(MODDIR)/*.c)
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
	TARGET = $(BINDIR)/ToDoTerm

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS) | $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR) $(BINDIR):
	mkdir -p $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)
