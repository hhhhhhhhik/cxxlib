###############################
#      user program           #
###############################
TARGETS = TestThreadPool

ALL_SRCS := $(wildcard *.cpp)
ALL_OBJS := $(ALL_SRCS:.cpp=.o)

all:$(ALL_OBJS) $(TARGETS)

###############################
#      compiler setting       #
###############################

CXX = c++
CXXFLAGS += -g -W -std=c++0x
LDFLAGS := $(LDFLAGS) -lpthread

###############################
#      make all               #
###############################

ALL_OBJS := $(ALL_OBJS)
$(TARGETS): $(ALL_OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(ALL_OBJS)

###############################
#      clean                  #
###############################

clean::
	rm -f $(TARGETS)
	rm -f *.o *.so
