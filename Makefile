LIB_NAME ?= thread-msg
DEBUG ?= n
VERBOSE ?= n

OBJ_DIR = obj

SRCS += messenger.cpp
SRCS += module.cpp
SRCS += msg.cpp
SRCS += sleep.cpp
SRCS += sleep-rt.cpp

LIB = lib$(LIB_NAME).a

ifeq ($(VERBOSE),y)
CC = g++
AR = ar rcs
else
CC = @echo '   ' CC $@; g++
AR = @echo '   ' AR $@; ar rcs
endif

INC_DIRS += .

CFLAGS += $(addprefix -I, $(INC_DIRS))
CFLAGS += -O0
CFLAGS += -Wno-format-truncation
ifeq ($(DEBUG),y)
CFLAGS += -g
endif

LDFLAGS += -lpthread

DEPS := $(shell find . -name "*.h")
OBJS := $(addprefix $(OBJ_DIR)/, $(patsubst %.cpp,%.o,$(SRCS)))

all: $(LIB)

$(LIB): $(OBJS)
	$(AR) $@ $^

$(OBJ_DIR)/%.o: %.cpp $(CPP_DEPS)
	@mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(LIB)
