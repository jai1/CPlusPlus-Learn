CXXFLAGS =  -O2 -g -Wall -fmessage-length=0
LIBS = -lcurl -lboost_system
TARGET = curl_asio_with_socket_reuse easy_interface_with_cb old_curl_asio_without_socket_reuse

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

curl_asio_with_socket_reuse: curl_asio_with_socket_reuse.o
	$(CXX) -o $@ $^ $(LIBS)

curl_asio_without_socket_reuse: curl_asio_without_socket_reuse.o
	$(CXX) -o $@ $^ $(LIBS)

old_curl_asio_without_socket_reuse: old_curl_asio_without_socket_reuse.o
	$(CXX) -o $@ $^ $(LIBS) 

easy_interface_with_cb: easy_interface_with_cb.o    
	$(CXX) -o $@ $^ $(LIBS) 
