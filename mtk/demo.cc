#include <mtk/mtk.h>

extern "C" {

// Application entry-point
MTK_EXPORT_FUNC
int mtk_main(Mtk::App& app)
{
  return app.run();
}

} // extern "C"
