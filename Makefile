# GNU classpath installation path
prefix = /usr/local
with_classpath_install_dir = /usr/

GLIBJ		= $(with_classpath_install_dir)/share/classpath/glibj.zip
BOOTCLASSPATH	= lib/classes.zip:$(GLIBJ)

ARCH		:= $(shell uname -m | sed  -e s/i.86/i386/)
OS		:= $(shell uname -s | tr "[:upper:]" "[:lower:]")

# Make the build silent by default
V =

PROGRAM		= java

ARCH_OBJS = \
	arch/$(ARCH)/emit-code.o	\
	arch/$(ARCH)/instruction.o	\
	arch/$(ARCH)/insn-selector.o	\
	arch/$(ARCH)/stack-frame.o	\
	arch/$(ARCH)/use-def.o

JIT_OBJS = \
	jit/alloc.o		\
	jit/arithmetic-bc.o	\
	jit/basic-block.o	\
	jit/branch-bc.o		\
	jit/bytecode-to-ir.o	\
	jit/cfg-analyzer.o	\
	jit/compilation-unit.o	\
	jit/compiler.o		\
	jit/disass-common.o	\
	jit/disass.o		\
	jit/emit.o		\
	jit/expression.o	\
	jit/interval.o		\
	jit/invoke-bc.o		\
	jit/linear-scan.o	\
	jit/liveness.o		\
	jit/load-store-bc.o	\
	jit/object-bc.o		\
	jit/ostack-bc.o		\
	jit/statement.o		\
	jit/trace-jit.o		\
	jit/tree-printer.o	\
	jit/typeconv-bc.o

VM_OBJS = \
	vm/backtrace.o		\
	vm/bitset.o		\
	vm/buffer.o		\
	vm/bytecodes.o		\
	vm/debug-dump.o		\
	vm/natives.o		\
	vm/stack.o		\
	vm/string.o		\
	vm/types.o		\
	vm/zalloc.o

JAMVM_OBJS = \
	jato/jato.o		\
	jamvm/access.o		\
	jamvm/alloc.o		\
	jamvm/cast.o		\
	jamvm/class.o		\
	jamvm/direct.o		\
	jamvm/dll.o		\
	jamvm/dll_ffi.o		\
	jamvm/excep.o		\
	jamvm/execute.o		\
	jamvm/frame.o		\
	jamvm/hash.o		\
	jamvm/hooks.o		\
	jamvm/init.o		\
	jamvm/interp.o		\
	jamvm/jni.o		\
	jamvm/lock.o		\
	jamvm/natives.o		\
	jamvm/os/$(OS)/i386/dll_md.o \
	jamvm/os/$(OS)/i386/init.o \
	jamvm/os/$(OS)/os.o	\
	jamvm/properties.o	\
	jamvm/reflect.o		\
	jamvm/resolve.o		\
	jamvm/string.o		\
	jamvm/thread.o		\
	jamvm/utf8.o		\
	jamvm/zip.o

LIBHARNESS_OBJS = \
	test/libharness/libharness.o

JATO_OBJS = $(ARCH_OBJS) $(JIT_OBJS) $(VM_OBJS)

OBJS = $(JAMVM_OBJS) $(JATO_OBJS)

CC		= gcc
MONOBURG	= ./monoburg/monoburg
JIKES		= jikes

CFLAGS		+= -g -Wall -rdynamic -std=gnu99

WARNINGS	= -Wsign-compare -Wundef
CFLAGS		+= $(WARNINGS)

OPTIMIZATIONS	+= -Os
CFLAGS		+= $(OPTIMIZATIONS)

INCLUDES	= -Iinclude -Ijit -Ijamvm -Ijit/glib -include arch/config.h $(ARCH_INCLUDE)
CFLAGS		+= $(INCLUDES)

DEFINES = -DINSTALL_DIR=\"$(prefix)\" -DCLASSPATH_INSTALL_DIR=\"$(with_classpath_install_dir)\"
CFLAGS		+= $(DEFINES)

LIBS		= -lpthread -lm -ldl -lz -lbfd -lopcodes $(ARCH_LIBS)

ARCH_INCLUDE_DIR = include/arch
ARCH_H = include/vm/arch.h

ifeq ($(strip $(V)),)
	E = @echo
	Q = @
else
	E = @\#
	Q =
endif
export E Q

all: monoburg $(PROGRAM) test
.PHONY: all
.DEFAULT: all

monoburg:
	$(Q) make -C monoburg/
.PHONY: monoburg

%.o: %.c
	$(E) "  CC      " $@
	$(Q) $(CC) -c $(CFLAGS) $< -o $@

$(ARCH_H):
	$(E) "  LN      " $@
	$(Q) ln -fsn ../../jamvm/arch/$(ARCH).h $@

arch/$(ARCH)/insn-selector.c: FORCE
	$(E) "  MONOBURG" $@
	$(Q) $(MONOBURG) -p -e arch/$(ARCH)/insn-selector.brg > $@

$(PROGRAM): $(ARCH_INCLUDE_DIR) $(ARCH_H) compile
	$(E) "  CC      " $@
	$(Q) $(CC) $(CFLAGS) $(LIBS) $(OBJS) -o $(PROGRAM)

compile: $(OBJS)

$(ARCH_INCLUDE_DIR): FORCE
	$(E) "  LN      " $@
	$(Q) ln -fsn arch-$(ARCH) $@

test: $(ARCH_INCLUDE_DIR) $(ARCH_H) monoburg
	make -C test/vm/ test
	make -C test/jit/ test
	make -C test/arch-i386/ test
.PHONY: test

%.class: %.java
	$(E) "  JIKES   " $@
	$(Q) $(JIKES) -cp $(BOOTCLASSPATH):regression -d regression $<

REGRESSION_TEST_SUITE_CLASSES = \
	regression/jamvm/TestCase.class \
	regression/jamvm/ExitStatusIsOneTest.class \
	regression/jamvm/ExitStatusIsZeroTest.class \
	regression/jamvm/LoadConstantsTest.class \
	regression/jamvm/IntegerArithmeticTest.class \
	regression/jamvm/ObjectCreationAndManipulationTest.class \
	regression/jamvm/MethodInvocationAndReturnTest.class

vm-classes:
	make -C lib/
.PHONY: vm-classes

regression: monoburg vm-classes $(PROGRAM) $(REGRESSION_TEST_SUITE_CLASSES)
	$(E) "  REGRESSION"
	$(Q) cd regression && /bin/bash run-suite.sh $(JAVA_OPTS)
.PHONY: regression

clean:
	$(E) "  CLEAN"
	$(Q) - rm -f $(OBJS)
	$(Q) - rm -f $(LIBHARNESS_OBJS)
	$(Q) - rm -f $(ARCH_TEST_OBJS)
	$(Q) - rm -f arch/$(ARCH)/insn-selector.c
	$(Q) - rm -f $(PROGRAM)
	$(Q) - rm -f $(ARCH_H)
	$(Q) - rm -f $(ARCH_TEST_SUITE)
	$(Q) - rm -f test-suite.o
	$(Q) - rm -f $(ARCH_TESTRUNNER)
	$(Q) - rm -f $(REGRESSION_TEST_SUITE_CLASSES)
	$(Q) - rm -f tags
	$(Q) - rm -f include/arch
	$(Q) - make -C monoburg/ clean
	$(Q) - make -C test/vm/ clean
	$(Q) - make -C test/jit/ clean
	$(Q) - make -C test/arch-i386/ clean
.PHONY: clean

PHONY += FORCE
FORCE:
