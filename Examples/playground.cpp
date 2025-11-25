/*
    playground.cpp
    Attempt to "import" (include) a broad set of C++ standard library headers
    and bring std into global namespace for quick experimentation.
    Note: using namespace std; and including lots of headers is convenient for
    playgrounds but not recommended for production code.
*/

#if defined(__has_include)
#  if __has_include(<bits/stdc++.h>)
#    include <bits/stdc++.h>
#  else
#    include <algorithm>
#    include <array>
#    include <bitset>
#    include <cassert>
#    include <cctype>
#    include <cerrno>
#    include <cfenv>
#    include <cfloat>
#    include <cinttypes>
#    include <ciso646>
#    include <climits>
#    include <clocale>
#    include <cmath>
#    include <complex>
#    include <condition_variable>
#    include <csetjmp>
#    include <csignal>
#    include <cstdarg>
#    include <cstddef>
#    include <cstdint>
#    include <cstdio>
#    include <cstdlib>
#    include <cstring>
#    include <ctime>
#    include <cwchar>
#    include <cwctype>
#    include <deque>
#    include <exception>
#    include <forward_list>
#    include <fstream>
#    include <functional>
#    include <future>
#    include <initializer_list>
#    include <iomanip>
#    include <ios>
#    include <iosfwd>
#    include <iostream>
#    include <istream>
#    include <iterator>
#    include <limits>
#    include <list>
#    include <locale>
#    include <map>
#    include <memory>
#    include <mutex>
#    include <new>
#    include <numeric>
#    include <ostream>
#    include <queue>
#    include <random>
#    include <ratio>
#    include <regex>
#    include <scoped_allocator>
#    include <set>
#    include <sstream>
#    include <stack>
#    include <stdexcept>
#    include <streambuf>
#    include <string>
#    include <system_error>
#    include <thread>
#    include <tuple>
#    include <type_traits>
#    include <typeindex>
#    include <typeinfo>
#    include <unordered_map>
#    include <unordered_set>
#    include <utility>
#    include <valarray>
#    include <vector>
#   include <ranges>
#  endif
#else
#  include <bits/stdc++.h>
#endif

using namespace std;

int main()
{
       vector<int> vec = {5, 2, 9, 1, 5, 6};
       vector<int> result(vec.size());
       partial_sum(vec.begin(), vec.end(), result.begin());
        for (int n : result) {
            cout << n << ' ';
        }
}