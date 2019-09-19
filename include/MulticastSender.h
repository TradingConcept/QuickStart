#pragma once
// http://www.boost.org/doc/libs/1_37_0/doc/html/boost_asio/example/multicast/sender.cpp

#include <iostream>
#include <sstream>
#include <string>
#include <boost/asio.hpp>
#include "boost/bind.hpp"
#include "boost/date_time/posix_time/posix_time_types.hpp"

// Ver https://code.visualstudio.com/docs/languages/cpp cuando haya problemas con paths



class MulticastSender
{

    boost::asio::ip::udp::endpoint endpoint_;
    boost::asio::ip::udp::socket socket_;
    boost::asio::deadline_timer timer_;

    int message_count_;
    std::string message_;

    void AsyncSendTo();

public:

    MulticastSender(boost::asio::io_service& io_service, const boost::asio::ip::address& multicast_address) ;

    void handle_send_to(const boost::system::error_code& error);
    void handle_timeout(const boost::system::error_code& error);     

    static void Run();

};