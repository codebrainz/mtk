#include <mtk/log.hh>
#include <mtk/win32.hh>

MTK_NS_BEGIN

//////////////////////////////////////////////////////////////////////////////
// Private log implementation for Win32                                     //
//////////////////////////////////////////////////////////////////////////////

class LogImpl
{
public:
  LogImpl()
  {
    AllocConsole();
    AttachConsole(ATTACH_PARENT_PROCESS);
  }

  ~LogImpl()
  {
    FreeConsole();
  }

  bool vmsg(int log_level, const char *fmt, va_list& ap)
  {
    const char *prefix = "";

    switch (log_level)
    {
      case Log::DEBUG:
        prefix = "DEBUG";
        break;
      case Log::INFO:
        prefix = "INFO";
        break;
      case Log::MESSAGE:
        prefix = "MESSAGE";
        break;
      case Log::WARNING:
        prefix = "WARNING";
        break;
      case Log::CRITICAL:
        prefix = "CRITICAL";
        break;
      case Log::ERROR:
        prefix = "ERROR";
        break;
      default:
        break;
    }

    return false;
  }

  bool msg(int log_level, const char *fmt, ...)
  {
    return false;
  }
};

//////////////////////////////////////////////////////////////////////////////
// Mtk::Log implementation, uses private platform class above               //
//////////////////////////////////////////////////////////////////////////////

Log::Log()
  : p(new LogImpl)
{
}

Log::~Log()
{
  delete p;
}

bool Log::vmsg(int log_level, const char *fmt, va_list& ap)
{
  return p->vmsg(log_level, fmt, ap);
}

bool Log::msg(int log_level, const char *fmt, ...)
{
  va_list ap;
  bool res;
  va_start(ap, fmt);
  res = vmsg(log_level, fmt, ap);
  va_end(ap);
  return res;
}

MTK_NS_END
