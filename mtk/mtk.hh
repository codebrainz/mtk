#ifndef __MTK_HH__
#define __MTK_HH__

#include <vector>
#include <string>

#define MTK_NS_BEGIN namespace Mtk {
#define MTK_NS_END   } // namespace Mtk

#define MTK_EXTERNC_BEGIN extern "C" {
#define MTK_EXTERNC_END   } // extern "C" {

MTK_NS_BEGIN

typedef std::string String;
typedef std::vector<std::string> StringList;

MTK_NS_END

#endif // __MTK_HH__
