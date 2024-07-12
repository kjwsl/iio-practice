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

        void tokenize();
        void set_source(const string_view src);
        void set_separator(const string_view separator);

        string_view get_source() const noexcept;
        string_view get_separator() const noexcept;
        optional<token_t> get_next_token() noexcept;
        int get_token_size() const noexcept;
        bool has_more_tokens() const noexcept;
        void print_tokens() const noexcept;

    private:
        string_view m_src{};
        string_view m_separator{};
        tokenlist_t m_tokens{};
        int         m_token_cnt{0};
    };
}


#endif // __TOKENIZER_H__
