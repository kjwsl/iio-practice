#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

#include <string>
#include <vector>
#include <optional>

namespace gnss::impl {
    using namespace std;
    using token_t = string;
    using tokenlist_t = vector<token_t>;
    class Tokenizer {
    public:
        Tokenizer() = default;
        Tokenizer(const string_view src, const string_view separator);
        virtual ~Tokenizer() = default;

        void               tokenize();
        void               setSource(const string_view src);
        void               setSeparator(const string_view separator);

        string_view        getSource()       const noexcept;
        string_view        getSeparator()    const noexcept;
        optional<token_t>  getNextToken()         noexcept;
        int                getTokenSize()   const noexcept;
        bool               hasMoreTokens()  const noexcept;
        void               printTokens()     const noexcept;

    private:
        string_view mSrc{};
        string_view mSeparator{};
        tokenlist_t mTokens{};
        int         mTokenCnt{0};
    };
}


#endif // __TOKENIZER_H__
