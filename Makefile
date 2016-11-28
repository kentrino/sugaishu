COMPILER  = g++

# -g はデバッグオプションだがこのままで良いのか
CFLAGS    = -pg -std=gnu++11 -MMD -MP -Wall -Wextra -Winit-self -Wno-missing-field-initializers

# リンカにもpgオプションがいる
LFLAGS    = -pg

ifeq "$(shell getconf LONG_BIT)" "64"
  LDFLAGS =
else
  LDFLAGS =
endif
LIBS      =
INCLUDE   = -I./include
#TARGET    = ./bin/$(shell basename `readlink -f .`)
TARGET    = ./bin/sugaish
SRCDIR    = ./src

# これ必要かどうか
ifeq "$(strip $(SRCDIR))" ""
  SRCDIR  = .
endif
SOURCES   = $(wildcard $(SRCDIR)/*.cc)
OBJDIR    = ./obj
ifeq "$(strip $(OBJDIR))" ""
  OBJDIR  = .
endif
OBJECTS   = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.cc=.o)))
DEPENDS   = $(OBJECTS:.o=.d)

$(TARGET): $(OBJECTS) $(LIBS)
	$(COMPILER) $(LFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	# -mkdir -p $(OBJDIR)
    # $@ $<はなに
	$(COMPILER) $(CFLAGS) $(INCLUDE) -o $@ -c $<

all: clean $(TARGET)

clean:
	-rm -f $(OBJECTS) $(DEPENDS) $(TARGET)

# これはなに
-include $(DEPENDS)
