#include "../../../include/model/communication/communicator.hpp"

Communicator::Communicator(boost::asio::io_service &ioService)
: socket(ioService)
{

}
