#ifndef __MTK_LOG_HH__
#define __MTK_LOG_HH__

#include <mtk/mtk.hh>
#include <cstdarg>
#include <exception>

MTK_NS_BEGIN

class LogImpl;

class Log
{
public:

  enum Level
  {
    DEBUG,
    INFO,
    MESSAGE,
    WARNING,
    CRITICAL,
    ERROR,
  };

  // implemented by the platform layer
  bool vmsg(int log_level, const char *fmt, va_list& ap);
  bool msg(int log_level, const char *fmt, ...);

  // singleton
  static Log& instance()
  {
    static Log inst;
    return inst;
  }

private:
  // implemented by platform layer
  LogImpl *p;
  Log();
  ~Log();

  // not implemented
  Log(const Log&);
  Log& operator=(const Log&);
};


// Shortcut inline functions
static inline void debug(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  Log::instance().vmsg(DEBUG, fmt, ap);
  va_end(ap);
}

static inline void info(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  Log::instance().vmsg(INFO, fmt, ap);
  va_end(ap);
}

static inline void message(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  Log::instance().vmsg(MESSAGE, fmt, ap);
  va_end(ap);
}

static inline void warning(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  Log::instance().vmsg(WARNING, fmt, ap);
  va_end(ap);
}

static inline void critical(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  Log::instance().vmsg(CRITICAL, fmt, ap);
  va_end(ap);
}

static inline void error(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  Log::instance().vmsg(ERROR, fmt, ap);
  va_end(ap);
  std::terminate();
}

MTK_NS_END

#endif // __MTK_LOG_HH__
