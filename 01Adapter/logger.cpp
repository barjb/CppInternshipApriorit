#include "logger.hpp"
Logger::Logger(std::string fileName) : fileName(fileName)
{
    init();
}

void Logger::Write(std::string input)
{
    BOOST_LOG(logger) << input;
}
Logger::~Logger()
{
    logging::core::get()->remove_sink(sink);
}
void Logger::init()
{
    sink = boost::make_shared<text_sink>();
    sink->locked_backend()->add_stream(boost::make_shared<std::ofstream>(fileName));
    sink->set_formatter(expr::stream << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S") << ": " << expr::smessage);
    logging::core::get()->add_sink(sink);
}