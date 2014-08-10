#include <mtk/app.hh>
#include <mtk/log.hh>
#include <mtk/win32.hh>
#include <iostream>

MTK_NS_BEGIN

//////////////////////////////////////////////////////////////////////////////
// Private app implementation for Win32                                     //
//////////////////////////////////////////////////////////////////////////////

class AppImpl
{
public:
  int exit_code;
  bool quitting;
  String program_name;
  StringList args;

  AppImpl(int argc=0, char **argv=0)
    : exit_code(0),
      quitting(false),
      program_name((argc > 0) ? argv[0] : ""),
      args(argc)
  {
    for (int i=0; i < argc; i++)
      args.push_back(argv[i]);
  }

  ~AppImpl()
  {
  }

  int run()
  {
    MSG message;

    exit_code = 0;
    quitting = false;

    while (! quitting && GetMessage(&message, NULL, 0, 0))
      {
        TranslateMessage(&message);
        DispatchMessage(&message);
      }

    quitting = false;

    return exit_code;
  }

  void quit(int exit_code_ = 0)
  {
    exit_code = exit_code_;
    quitting = true;
    PostQuitMessage(exit_code);
  }
};

//////////////////////////////////////////////////////////////////////////////
// Mtk::App implementation, uses private platform class above               //
//////////////////////////////////////////////////////////////////////////////

App::App(int argc, char **argv) : p (new AppImpl) {}
App::~App() { delete p; }
int App::run() { return p->run(); }
void App::quit(int exit_code) { p->quit(exit_code); }
const String& App::getProgramName() const { return p->program_name; }
const StringList& App::getArgumentVector() const { return p->args; }

MTK_NS_END

//////////////////////////////////////////////////////////////////////////////
// Win32 Platform Entry-Point                                               //
//////////////////////////////////////////////////////////////////////////////

MTK_EXTERNC_BEGIN

int CALLBACK WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine,
                     int nCmdShow)
{
  Mtk::App& app = Mtk::App::instance(); // construct singleton (early)
  Mtk::MainFunc main_func =
    (Mtk::MainFunc) GetProcAddress(GetModuleHandle(0), "mtk_main");

  if (! main_func)
    {
      Mtk::error(
        "Failed to find `mtk_main' entry point, is it implemented? "
        "Did you forget to export the symbol (ex. `MTK_EXPORT_FUNC') or prevent "
        "C++ name manging by using `extern \"C\"' (ex. `MTK_EXTERNC_BEGIN/END')?"
      );
    }

  return main_func(app);
}

MTK_EXTERNC_END
