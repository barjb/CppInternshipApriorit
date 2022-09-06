#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <fstream>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/expressions/formatters/date_time.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/expressions.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
typedef sinks::synchronous_sink<sinks::text_ostream_backend> text_sink;

namespace expr = boost::log::expressions;

class Logger
{
public:
    Logger(std::string fileName);
    void Write(std::string input);
    virtual ~Logger();

private:
    src::logger logger;
    std::string fileName;
    boost::shared_ptr<text_sink> sink;
    void init();
};

#endif