#include "MulticastSender.h"

const short sender_multicast_port = 30001;
const int max_message_count = 16;

MulticastSender::MulticastSender(boost::asio::io_service &io_service, const boost::asio::ip::address &multicast_address) : 
    endpoint_(multicast_address, sender_multicast_port), socket_(io_service, endpoint_.protocol()), timer_(io_service), message_count_(0)
{

    // std::ostringstream os;
    // os << "Message " << message_count_++;
    // message_ = os.str();

    // socket_.async_send_to( boost::asio::buffer(message_), endpoint_, boost::bind(&MulticastSender::handle_send_to, this, 
    //        boost::asio::placeholders::error));

    this->AsyncSendTo();

}

void MulticastSender::handle_send_to(const boost::system::error_code &error)
{
    if (!error && message_count_ < max_message_count)
    {
        timer_.expires_from_now(boost::posix_time::seconds(1));
        timer_.async_wait(boost::bind(&MulticastSender::handle_timeout, this, boost::asio::placeholders::error));
    }
}

void MulticastSender::handle_timeout(const boost::system::error_code &error)
{
    if (!error)
    {
        this->AsyncSendTo();        
    }
}

void MulticastSender::AsyncSendTo() {

    std::cout << "Sending Message " << message_count_ << std::endl ;

    std::ostringstream os;
    os << "Message " << message_count_++;

    message_ = os.str();
    socket_.async_send_to(boost::asio::buffer(message_), endpoint_, boost::bind(&MulticastSender::handle_send_to, 
        this, boost::asio::placeholders::error));

}

void MulticastSender::Run()
{
    std::cout << "MulticastSender Run" << std::endl;

    auto multicast_address = boost::asio::ip::address::from_string( "239.255.0.1" );

    try
    {
        boost::asio::io_service io_service;
        MulticastSender s(io_service, multicast_address);
        io_service.run();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";        
    }
    
}
