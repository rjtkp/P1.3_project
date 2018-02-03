#ifndef __AP_ERROR_H__
#define __AP_ERROR_H__

#include <assert.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace ap {

  namespace internal {
    static std::string sep = " ";
  }

  template <typename T>
  void error(const T& s) {
    std::ostringstream os;
    os << s;
    throw std::runtime_error{os.str()};
  }

  template <typename T1, typename T2>
  void error(const T1& s, const T2& t) {
    std::ostringstream os;
    os << s << internal::sep << t;
    error(os.str());
  }

// variable template: do sth specific with the first 2 and then call the 3rd in a 
  template <typename T1, typename T2, typename... Tail> //variable template:
  void error(const T1& f, const T2& s, const Tail&... rest) {
    /* std::cout << __PRETTY_FUNCTION__ << std::endl; */
    std::ostringstream os;
    os << f << internal::sep << s;
    error(os.str(), rest...);
  }

  inline void set_separator(const std::string& s) { internal::sep = s; }

  inline void reset_separator() { internal::sep = " "; }

}  // close namespace ap

// some useful macros
#define AP_error(...)                                                 \
  ap::internal::pretty_error(__FILE__, __LINE__, __PRETTY_FUNCTION__, \
                             __VA_ARGS__)

// DEFINITION PF A MACRO: (NB: ... stands for variable arguments)
// the macro should be written on a single line,
//that's why we have the line continuation character at the end of each line
// Why the macro and not a function?
// the variables __FILE__ ecc are replaced at compiling time by the preprocessor.
//In the following line, I state what the compiler should do if the custom asserts 
//are forced to be ignored, due to compilation with option -DNDEBUG.
// This is done for balancing the slowdown introduced by throwing an exception 
// and the need for throwing it.
#ifndef NDEBUG
#define AP_assert(cond, ...)                                              \
  {                                                                       \
    if (!(cond))                                                          \
      ap::internal::pretty_error(__FILE__, __LINE__, __PRETTY_FUNCTION__, \
                                 __VA_ARGS__);                            \
  }
#else
#define AP_assert(cond, ...)
#endif

template <typename t1, typename t2, typename t3>
std::string NotInRange(const t1& a, const t2& b, const t3& c) {
  std::ostringstream os;
  os << c << " does not belong to [" << a << ", " << b << ")\n";
  return os.str();
}

namespace ap {
  namespace internal {
    template <typename T, typename... Tail>
    void pretty_error(const char* sfile,
                      const unsigned int& line,
                      const char* sfunc,
                      const T& f,
                      const Tail&... rest) {
      std::ostringstream os;
      os << "\n\n"
         << "------------------------------------------------------------------"
            "---"
            "\n"
         << "A runtime exception has been thrown\n\n"
         << "   function: " << sfunc << '\n'
         << "       file: " << sfile << '\n'
         << "       line: " << line << "\n\n"
         << "with the following output:\n\n"
         << f;
      error(os.str(), rest...);
    }
  }  // close namespace internal
}  // close namespace ap

#endif






/*
******************************************************************************************
NOTE ON void error(...): DEFINIZIONE DI UNA FUNZIONE CHE PRENDA IN INPUT UN NUM
												 ARBITRARIO DI VARIABILI

(1) string std::ostringstream.str() const;
(2) void std::ostringstream.str(const string& s);

Get/set content
The first form (1) returns a string object with a copy of the current contents of the stream.

The second form (2) sets s as the contents of the stream, discarding any previous contents. The object preserves its open mode: if this includes ios_base::ate, the writing position is moved to the end of the new sequence.

Internally, the function calls the str member of its internal string buffer object.
---------------------------------------------
Usage Minimal Example:
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::ostringstream

int main () {
  std::ostringstream oss;
  oss << "One hundred and one: " << 101; // giustappongo tutto nell'oggetto oss
  std::string s = oss.str(); // scrivo in una stringa gli oggetti in os
  std::cout << s << '\n';
  return 0;
}
---------------------------------------------


# PRE-DEFINED MACROS

## __FILE__ and __LINE__ : https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html

## __VA_ARGS__ : https://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html

## __PRETTY_FUNCION__ : https://gcc.gnu.org/onlinedocs/gcc/Function-Names.html
6.48 Function Names as Strings

GCC provides three magic constants that hold the name of the current function as a string. In C++11 and later modes, all three are treated as constant expressions and can be used in constexpr constexts. The first of these constants is __func__, which is part of the C99 standard:

The identifier __func__ is implicitly declared by the translator as if, immediately following the opening brace of each function definition, the declaration

static const char __func__[] = "function-name";

appeared, where function-name is the name of the lexically-enclosing function. This name is the unadorned name of the function. As an extension, at file (or, in C++, namespace scope), __func__ evaluates to the empty string.

__FUNCTION__ is another name for __func__, provided for backward compatibility with old versions of GCC.

In C, __PRETTY_FUNCTION__ is yet another name for __func__, except that at file (or, in C++, namespace scope), it evaluates to the string "top level". In addition, in C++, __PRETTY_FUNCTION__ contains the signature of the function as well as its bare name. For example, this program:

extern "C" int printf (const char *, ...);

class a {
 public:
  void sub (int i)
    {
      printf ("__FUNCTION__ = %s\n", __FUNCTION__);
      printf ("__PRETTY_FUNCTION__ = %s\n", __PRETTY_FUNCTION__);
    }
};

int
main (void)
{
  a ax;
  ax.sub (0);
  return 0;
}

gives this output:

__FUNCTION__ = sub
__PRETTY_FUNCTION__ = void a::sub(int)

These identifiers are variables, not preprocessor macros, and may not be used to initialize char arrays or be concatenated with string literals. 











******************************************************************************************
*/










