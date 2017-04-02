CXXFLAGS =  -O2 -g -Wall -fmessage-length=0
LIBS = -lboost_system -lcurl
TARGET = example1 example2

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

example1: example1.o
	$(CXX) -o $@ $^ $(LIBS)

example2: example2.o
	$(CXX) -o $@ $^ $(LIBS) 
