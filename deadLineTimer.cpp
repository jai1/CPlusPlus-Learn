// Motivation is to be able check if deadline timer works well with blocking calls
// Conclusion deadlinetimer will not work if the io_service is blocked in some other task
#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>

using namespace boost::asio;
using namespace std;

io_service io;

void callback(const boost::system::error_code& err) {
    if (err == boost::asio::error::operation_aborted) {
        std::cout<<"Timer cancelled: " << err.message()<<std::endl;
        return;
    } else if (err) {
        std::cout<<"Timer error: " << err.message() << std::endl;
        return;
    }
    std::cout<<"Hello World!!!!"<<std::endl;
    deadline_timer t(io, boost::posix_time::seconds(5));
}

void func() {
}

int main() {

    deadline_timer t(io, boost::posix_time::seconds(5));
    t.async_wait(callback);
    boost::asio::io_service::work work(io);
    boost::asio::detail::thread worker(boost::bind(&boost::asio::io_service::run, &io)); 
    while(1) {
        io.post(func);
    }
    return 0;
}
