# The executable file name.
# It must be specified.
# PROGRAM := a.out # the executable name
PROGRAM := test_unixsocket

# The directories in which source files reside.
# At least one path should be specified.
# SRCDIRS := . # current directory
SRCDIRS := .
SRCDIRS += ../
SRCDIRS += ../../../cmockery/src/

# The source file types (headers excluded).
# At least one type should be specified.
# The valid suffixes are among of .c, .C, .cc, .cpp, .CPP, .c++, .cp, or .cxx.
# SRCEXTS := .c # C program
# SRCEXTS := .cpp # C++ program
# SRCEXTS := .c .cpp # C/C++ program
SRCEXTS := .c

# The flags used by the cpp (man cpp for more).
# CPPFLAGS := -Wall -Werror # show all warnings and take them as errors
#CPPFLAGS := -g

# The compiling flags used only for C.
# If it is a C++ program, no need to set these flags.
# If it is a C and C++ merging program, set these flags for the C parts.
CFLAGS := -g
CFLAGS := -DDEBUG
CFLAGS += -I./
CFLAGS += -I../
CFLAGS += -I../../../cmockery/src/google/

# The compiling flags used only for C++.
# If it is a C program, no need to set these flags.
# If it is a C and C++ merging program, set these flags for the C++ parts.
CXXFLAGS :=

# The library and the link options ( C and C++ common ).
LDFLAGS :=

## Implict Section: change the following only when necessary.
##=============================================================================
# The C program compiler. Uncomment it to specify yours explicitly.
#CC = gcc
CC = gcc
STRIP = strip
#CC = arm-himix200-linux-gcc
#STRIP = arm-himix200-linux-strip

# The C++ program compiler. Uncomment it to specify yours explicitly.
#CXX = g++

# Uncomment the 2 lines to compile C programs as C++ ones.
#CC = $(CXX)
#CFLAGS = $(CXXFLAGS)

# The command used to delete file.
RM = rm -f

## Stable Section: usually no need to be changed. But you can add more.
##=============================================================================
SHELL = /bin/sh
SOURCES = $(foreach d,$(SRCDIRS),$(wildcard $(addprefix $(d)/*,$(SRCEXTS))))
OBJS = $(foreach x,$(SRCEXTS), \
		$(patsubst %$(x),%.o,$(filter %$(x),$(SOURCES))))
DEPS = $(patsubst %.o,%.d,$(OBJS))

.PHONY : all objs clean cleanall rebuild

all : $(PROGRAM)

# Rules for creating the dependency files (.d).
#---------------------------------------------------
%.d : %.c
	@$(CC) -MM -MD $(CFLAGS) $<

%.d : %.C
	@$(CC) -MM -MD $(CXXFLAGS) $<

%.d : %.cc
	@$(CC) -MM -MD $(CXXFLAGS) $<

%.d : %.cpp
	@$(CC) -MM -MD $(CXXFLAGS) $<

%.d : %.CPP
	@$(CC) -MM -MD $(CXXFLAGS) $<

%.d : %.c++
	@$(CC) -MM -MD $(CXXFLAGS) $<

%.d : %.cp
	@$(CC) -MM -MD $(CXXFLAGS) $<

%.d : %.cxx
	@$(CC) -MM -MD $(CXXFLAGS) $<

# Rules for producing the objects.
#---------------------------------------------------
objs : $(OBJS)

%.o : %.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

%.o : %.C
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $<  -o $@

%.o : %.cc
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@

%.o : %.cpp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@

%.o : %.CPP
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@

%.o : %.c++
	$(CXX -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@

%.o : %.cp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@
 
%.o : %.cxx
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@

# Rules for producing the executable.
#----------------------------------------------
$(PROGRAM) : $(OBJS)
ifeq ($(strip $(SRCEXTS)), .c) # C file
	$(warning "OBJS" $(OBJS))
	$(CC) -o $(PROGRAM) $(OBJS) $(LDFLAGS)
	$(STRIP) $(PROGRAM)
	cp $(PROGRAM) ~/tmp/tmp/ -rf
else # C++ file
	$(CXX) -o $(PROGRAM) $(OBJS) $(LDFLAGS)
endif

-include $(DEPS)

rebuild: clean all

clean :
	@$(RM) *.o *.d

cleanall: clean
	@$(RM) $(PROGRAM) $(PROGRAM).exe
