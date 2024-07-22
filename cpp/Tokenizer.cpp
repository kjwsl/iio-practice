#include "include/Tokenizer.h"
#include <stdexcept>
#include <cstring>
#include <iostream>

namespace gnss::impl {
    Tokenizer::Tokenizer(const string_view src, const string_view separator) {
        // Delegate to include checks
        setSource(src);
        setSeparator(separator);
    }

    string_view Tokenizer::getSource() const noexcept {
        return mSrc;
    }

    string_view Tokenizer::getSeparator() const noexcept {
        return mSeparator;
    }

    void Tokenizer::setSeparator(const string_view separator) {
        if (separator.empty()) {
            throw invalid_argument {"Separator is empty"};
        }
        mSeparator = separator;
    }

    void Tokenizer::setSource(const string_view src) {
        if (src.empty()) {
            throw invalid_argument {"Source is empty"};
        }
        mSrc = src;
    }

    void Tokenizer::tokenize() {
        mTokens.clear();
        size_t pos{};
        size_t new_pos;
        while((new_pos = mSrc.find(mSeparator, pos)) != string::npos){
            mTokens.emplace_back(mSrc.substr(pos, new_pos - pos));
            pos = new_pos + mSeparator.size();
        }
        if (mSrc.find(mSeparator, --pos) != string::npos) {
            pos += mSeparator.size();
        }
        mTokens.emplace_back(mSrc.substr(pos));
        mTokenCnt = mTokens.size();
        printTokens();
    }

    void Tokenizer::printTokens() const noexcept {
        cout << "[";
        for (auto it = mTokens.begin(); (it+1) != mTokens.end(); it++) {
            cout << it->data() << ", ";
        }
        cout << mTokens.back() << "]" << endl;
    }

    optional<token_t> Tokenizer::getNextToken() noexcept {
        if (!hasMoreTokens()) {
            return nullopt;
        }
        mTokenCnt--;
        cout << "token size: " << mTokenCnt << endl;
        return mTokens.front();
    }

    int Tokenizer::getTokenSize() const noexcept {
        return mTokenCnt;
    }

    bool Tokenizer::hasMoreTokens() const noexcept {
        return getTokenSize();
    }
}

