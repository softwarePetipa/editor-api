#ifndef petipa_file_fs_h_included
#define petipa_file_fs_h_included

#if !defined(__clang__) && defined(__GNUC__) && (__GNUC__ < 8)
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
//#include <experimental/filesystem>
//namespace fs = std::experimental::filesystem;
#endif

#endif
