#include <iostream>
#include <string>

using namespace std;
using namespace std::string_literals;

/**
 * String literals can have no prefix, or u8, L, u, and U prefixes to
 * denote narrow character (single-byte or multi-byte), UTF-8,
 * wide character (UCS-2 or UTF-16), UTF-16 and UTF-32 encodings.
 * A raw string literal can have R, u8R, LR, uR and UR prefixes for
 * the raw version equivalents of these encodings.
 */


int main()
{
    // better Unicode support in C++11

    // Character literals
    auto c0 = 'A';  // char
    auto c1 = u8'A';  // char, same as above
    auto c2 = L'A';  // wchar_t
    auto c3 = u'A';  // char16_t
    auto c4 = U'A';  // char32_t

    // String literals
    auto s0 = "hello";  // const char*
    auto s1 = u8"hello";  // const char*, encoded as UTF-8
    auto s2 = L"hello";  // const wchar_t*
    auto s3 = u"hello";  // const char16_t*, encoded as UTF-16
    auto s4 = U"hello";  // const char32_t*, encoded as UTF-32

    // Raw string literals containing unescaped \ and "
    auto R0 = R"("Hello \ world")";  // const char*
    auto R1 = u8R"("Hello \ world")";  // const char*, encoded as UTF-8
    auto R2 = LR"("Hello \ world")";  // const wchar_t*
    auto R3 = uR"("Hello \ world")";  // const char16_t*, encoded as UTF-16
    auto R4 = UR"("Hello \ world")";  // const char32_t*, encoded as UTF-32

    // Combining string literals with standard s-suffix
    auto S0 = "hello"s;  // std::string
    auto S1 = u8"hello"s;  // std::string
    auto S2 = L"hello"s;  // std::wstring
    auto S3 = u"hello"s;  // std::u16string
    auto S4 = U"hello"s;  // std::u32string

    // Combining raw string literals with standard s-suffix
    // in a raw 
    auto S5 = R"("Hello \ world")"s;  // std::string from a raw const char*
    auto S6 = u8R"("Hello \ 
              world")"s;  // std::string from a raw const char*, encoded as UTF-8
    auto S7 = LR"("Hello \
                   world")"s;  // std::wstring from a raw const wchar_t*
    auto S8 = uR"("Hello \
                   world")"s;  // std::u16string from a raw const char16_t*, encoded as UTF-16
    auto S9 = UR"("Hello \ world")"s;  // std::u32string from a raw const char32_t*, encoded as UTF-32

    cout << S5 << endl;

    getchar();
    return 0;
}