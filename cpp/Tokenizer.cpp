#include "include/Tokenizer.h"
#include <stdexcept>
#include <cstring>
#include <iostream>

namespace gnss::impl {
    Tokenizer::Tokenizer(const string_view src, const string_view separator) {
        // Delegate to include checks
        set_source(src);
        set_separator(separator);
    }

    string_view Tokenizer::get_source() const noexcept {
        return m_src;
    }

    string_view Tokenizer::get_separator() const noexcept {
        return m_separator;
    }

    void Tokenizer::set_separator(const string_view separator) {
        if (separator.empty()) {
            throw invalid_argument {"Separator is empty"};
        }
        m_separator = separator;
    }

    void Tokenizer::set_source(const string_view src) {
        if (src.empty()) {
            throw invalid_argument {"Source is empty"};
        }
        m_src = src;
    }

    void Tokenizer::tokenize() {
        m_tokens.clear();
        size_t pos{};
        size_t new_pos;
        while((new_pos = m_src.find(m_separator, pos)) != string::npos){
            m_tokens.emplace_back(m_src.substr(pos, new_pos - pos));
            pos = new_pos + m_separator.size();
        }
        if (m_src.find(m_separator, --pos) != string::npos) {
            pos += m_separator.size();
        }
        m_tokens.emplace_back(m_src.substr(pos));
        m_token_cnt = m_tokens.size();
        print_tokens();
    }

    void Tokenizer::print_tokens() const noexcept {
        cout << "[";
        for (auto it = m_tokens.begin(); (it+1) != m_tokens.end(); it++) {
            cout << it->data() << ", ";
        }
        cout << m_tokens.back() << "]" << endl;
    }

    optional<token_t> Tokenizer::get_next_token() noexcept {
        if (!has_more_tokens()) {
            return nullopt;
        }
        m_token_cnt--;
        cout << "token size: " << m_token_cnt << endl;
        return m_tokens.front();
    }

    int Tokenizer::get_token_size() const noexcept {
        return m_token_cnt;
    }

    bool Tokenizer::has_more_tokens() const noexcept {
        return get_token_size();
    }
}

