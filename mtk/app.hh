#ifndef __MTK_APP_HH__
#define __MTK_APP_HH__

#include <mtk/mtk.hh>

MTK_NS_BEGIN

class AppImpl;

class App
{
public:
  // implemented by platform layer
  int run();
  void quit(int exit_code=0);
  const String& getProgramName() const;
  const StringList& getArgumentVector() const;

  // singleton
  static App& instance(int argc=0, char **argv=0)
  {
    static App inst(argc, argv);
    return inst;
  }

private:
  // implemented by platform layer
  AppImpl *p;
  App(int argc, char **argv);
  virtual ~App();

  // not implemented
  App(const App&);
  App& operator=(const App&);
};

// Type of the main()-like program entry point, must be implemented in the
// application using MTK. The function must be called `mtk_main`.
typedef int (*MainFunc) (App&);

#ifdef MTK_WIN32
// Use on main()-like program entry point `mtk_main` to ensure the symbol
// is exported, which isn't the default on Win32 platform.
# define MTK_EXPORT_FUNC __declspec(dllexport)
#else
// Does nothing on non-Win32 platforms.
# define MTK_EXPORT_FUNC
#endif

MTK_NS_END

#endif // __MTK_APP_HH__
