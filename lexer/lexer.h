#include <cstddef>
#include <iostream>
#include <iterator>
#include <stdint.h>
#include <string_view>
class CapimlToken {
public:
  enum class TokenKind : uint8_t {
    Identifier,
    Colon,
    Minus,
    Number,
    Comment,
    Hash,
    STRING,
    LeftSquare,
    RightSquare,
    LeftCurly,
    RightCurly,
    End,
    Unexpected
  };

  CapimlToken(TokenKind kind) noexcept : kind_{kind} {}

  CapimlToken(TokenKind kind, const char *beg, std::size_t len) noexcept
      : kind_{kind}, lexeme_(beg, len) {}

  CapimlToken(TokenKind kind, const char *beg, const char *end) noexcept
      : kind_{kind}, lexeme_(beg, std::distance(beg, end)) {}

  TokenKind kind() const noexcept { return kind_; }

  void kind(TokenKind kind) noexcept { kind_ = kind; }

  bool is(TokenKind kind) const noexcept { return kind_ == kind; }

  bool is_not(TokenKind kind) const noexcept { return kind_ != kind; }

  bool is_one_of(TokenKind k1, TokenKind k2) const noexcept {
    return is(k1) || is(k2);
  }

  template <typename... Ts>
  bool is_one_of(TokenKind k1, TokenKind k2, Ts... ks) const noexcept {
    return is(k1) || is_one_of(k2, ks...);
  }
  std::string_view lexeme() const noexcept { return lexeme_; }

  void lexeme(std::string_view lexeme) noexcept { lexeme_ = std::move(lexeme); }

private:
  TokenKind kind_{};
  std::string_view lexeme_{};
};

class CapimlLexer {
public:
  CapimlLexer(const char *beg) noexcept : cursor_{beg} {}

  CapimlToken next() noexcept;

private:
  CapimlToken identifier() noexcept;
  CapimlToken number() noexcept;
  CapimlToken hash_comment() noexcept;
  CapimlToken string_literal() noexcept;
  CapimlToken atom(CapimlToken::TokenKind) noexcept;

  char peek() const noexcept { return *cursor_; }
  char get() noexcept { return *cursor_++; }

  const char *cursor_ = nullptr;
};

bool is_space(char c) noexcept {
  switch (c) {
  case ' ':
  case '\n':
  case '\t':
  case '\r':
    return true;
  default:
    return false;
  }
}

bool is_digit(char c) noexcept {
  switch (c) {
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    return true;
  default:
    return false;
  }
}
bool is_identifier_char(char c) noexcept {
  switch (c) {
  case 'a':
  case 'b':
  case 'c':
  case 'd':
  case 'e':
  case 'f':
  case 'g':
  case 'h':
  case 'i':
  case 'j':
  case 'k':
  case 'l':
  case 'm':
  case 'n':
  case 'o':
  case 'p':
  case 'q':
  case 'r':
  case 's':
  case 't':
  case 'u':
  case 'v':
  case 'w':
  case 'x':
  case 'y':
  case 'z':
  case 'A':
  case 'B':
  case 'C':
  case 'D':
  case 'E':
  case 'F':
  case 'G':
  case 'H':
  case 'I':
  case 'J':
  case 'K':
  case 'L':
  case 'M':
  case 'N':
  case 'O':
  case 'P':
  case 'Q':
  case 'R':
  case 'S':
  case 'T':
  case 'U':
  case 'V':
  case 'W':
  case 'X':
  case 'Y':
  case 'Z':
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
  case '_':
    return true;
  default:
    return false;
  }
}

CapimlToken CapimlLexer::atom(CapimlToken::TokenKind kind) noexcept {
  return CapimlToken(kind, cursor_++, 1);
}

CapimlToken CapimlLexer::next() noexcept {
  while (is_space(peek()))
    get();

  switch (peek()) {
  case '\0':
    return CapimlToken(CapimlToken::TokenKind::End, cursor_, 1);
  default:
    return atom(CapimlToken::TokenKind::Unexpected);
  case 'a':
  case 'b':
  case 'c':
  case 'd':
  case 'e':
  case 'f':
  case 'g':
  case 'h':
  case 'i':
  case 'j':
  case 'k':
  case 'l':
  case 'm':
  case 'n':
  case 'o':
  case 'p':
  case 'q':
  case 'r':
  case 's':
  case 't':
  case 'u':
  case 'v':
  case 'w':
  case 'x':
  case 'y':
  case 'z':
  case 'A':
  case 'B':
  case 'C':
  case 'D':
  case 'E':
  case 'F':
  case 'G':
  case 'H':
  case 'I':
  case 'J':
  case 'K':
  case 'L':
  case 'M':
  case 'N':
  case 'O':
  case 'P':
  case 'Q':
  case 'R':
  case 'S':
  case 'T':
  case 'U':
  case 'V':
  case 'W':
  case 'X':
  case 'Y':
  case 'Z':
    return identifier();
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    return number();
  case '"':
    return string_literal();
  case '\'':
    return string_literal();
  case '-':
    return atom(CapimlToken::TokenKind::Minus);
  case ':':
    return atom(CapimlToken::TokenKind::Colon);
  case '#':
    return hash_comment();
  case '[':
    return atom(CapimlToken::TokenKind::LeftSquare);
  case ']':
    return atom(CapimlToken::TokenKind::RightSquare);
  case '{':
    return atom(CapimlToken::TokenKind::LeftCurly);
  case '}':
    return atom(CapimlToken::TokenKind::RightCurly);
  }
}
int count_indent(std::string_view line) {
  int count = 0;
  for (char c : line) {
    if (c == ' ')
      count++;

    else if (c == '\t')
      count += 2;
    else
      break;
  }
  return count;
}

CapimlToken CapimlLexer::identifier() noexcept {
  const char *start = cursor_;

  get();
  while (is_identifier_char(peek()))
    get();

  return CapimlToken(CapimlToken::TokenKind::Identifier, start, cursor_);
}

CapimlToken CapimlLexer::string_literal() noexcept {
  const char *start = cursor_;
  char quote = get();

  start = cursor_;

  while (peek() != '\0' && peek() != quote && peek() != '\n') {
    get();
  }

  const char *end = cursor_;

  if (peek() == quote) {
    get();
  }

  return CapimlToken(CapimlToken::TokenKind::STRING, start, end);
}

CapimlToken CapimlLexer::number() noexcept {
  const char *start = cursor_;
  get();

  while (is_digit(peek()))
    get();
  return CapimlToken(CapimlToken::TokenKind::Number, start, cursor_);
}

CapimlToken CapimlLexer::hash_comment() noexcept {
  const char *start = cursor_;
  get();
  start = cursor_;
  while (peek() != '\0' && peek() != '\n') {
    get();
  }
  return CapimlToken(CapimlToken::TokenKind::Comment, start, cursor_);
}
