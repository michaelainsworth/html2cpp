#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum Mode
{
    Code,
    Html
};

struct Token
{
    Token(Mode type_, const string& value_) :
        type(type_), value(value_)
    {}

    bool isWhitespace() const
    {
        for (size_t i = 0, s = value.size(); i < s; ++i)
        {
            char c = value[i];
            if (c != ' ' && c != '\n' && c != '\r' && c != '\t')
            {
                return false;
            }
        }
        return true;
    }

    Mode type;
    string value;
};

int main()
{
    string input;

    while (cin)
    {
        char c;
        cin.get(c);

        if (cin)
        {
            input += c;
        }
    }

    typedef std::vector<Token> TokenVector;
    TokenVector tokens;

    string prefix = "<!--", suffix = "-->";
    size_t prefixSize = prefix.size(), suffixSize = suffix.size();
    Mode mode = Html;
    string value;
    size_t i = 0, s = input.size();
    for (; i < s; ++i)
    {
        char c = input[i];
        size_t remaining = s - i;

        if (Html == mode)
        {
            if (input.substr(i, prefixSize) == prefix)
            {
                if (value.size())
                {
                    tokens.push_back(Token(Html, value));
                    value.clear();
                }

                i += prefixSize - 1;
                mode = Code;
            }
            else
            {
                value += c;
            }
        }
        else
        {
            if (input.substr(i, suffixSize) == suffix)
            {
                if (value.size())
                {
                    tokens.push_back(Token(Code, value));
                    value.clear();
                }

                i += suffixSize - 1;
                mode = Html;
            }
            else
            {
                value += c;
            }
        }
    }

    if (value.size())
    {
        tokens.push_back(Token(mode, value));
    }

    for (size_t i = 0, s = tokens.size(); i < s; ++i)
    {
        Token t = tokens[i];

        if (t.type == Html)
        {
            if (!t.isWhitespace())
            {
                cout << '"';
                for (size_t k = 0, z = t.value.size(); k < z; ++k)
                {
                    char c = t.value[k];
                    if (c == '\r')
                    {
                        cout << "\\r";
                    }
                    else if (c == '\n')
                    {
                        cout << "\\n";
                    }
                    else if (c == '\v')
                    {
                        cout << "\\v";
                    }
                    else if (c == '\t')
                    {
                        cout << "\\t";
                    }
                    else if (c == '\b')
                    {
                        cout << "\\b";
                    }
                    else if (c == '"')
                    {
                        cout << "\\\"";
                    }
                    else
                    {
                        cout << c;
                    }
                }
                cout << '"';
            }
        }
        else
        {
            cout.write(t.value.c_str(), t.value.size());
        }
    }

    return 0;
}
