CXX ?= g++

CXXFLAGS ?= -std=c++17 -O2 -g
BUILDDIR ?= ./build/
SRCDIR ?= ./

COMMONINC = -I./lfu_cache -I./ideal_cache

CXXFLAGS += $(COMMONINC)

CCSRCS = $(SRCDIR)lfu_cache/lfu_cache.cpp $(SRCDIR)ideal_cache/ideal_cache.cpp $(SRCDIR)tests/tests.cpp

SUBS := $(CCSRCS)
SUBS := $(subst $(SRCDIR), $(BUILDDIR), $(SUBS))

OBJS = $(SUBS:.cpp=.o)

DEPS = $(SUBS:.cpp=.d)

.PHONY: all
all: $(OBJS)

$(BUILDDIR)%.o: $(SRCDIR)%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -o $@

include $(DEPS)

$(BUILDDIR)%.d: $(SRCDIR)%.cpp
	@echo "Collecting deps for $<"
	@mkdir -p $(dir $@)
	@$(CXX) -E $(CXXFLAGS) $< -MM -MT $(@:.d=.o) > $@

.PHONY: clean
clean:
	rm -rf $(BUILDDIR)

