#include "class/capiml.h"
#include "lexer/lexer.h"
#include <iomanip>
#include <iostream>

std::ostream &operator<<(std::ostream &os, const CapimlToken::TokenKind &kind) {
  static const char *const names[]{
      "Identifier", "Colon",  "Minus",      "Number",      "Comment",
      "Hash",       "STRING", "LeftSquare", "RightSquare", "LeftCurly",
      "RightCurly", "End",    "Unexpected"};
  return os << names[static_cast<int>(kind)];
}

int main() {
  Capiml capiml;

  const auto cfg = capiml.Read("example/cfg.capiml");

  CapimlLexer lex(cfg.c_str());
  for (auto token = lex.next(); not token.is_one_of(
           CapimlToken::TokenKind::End, CapimlToken::TokenKind::Unexpected);
       token = lex.next()) {
    std::cout << std::setw(12) << token.kind() << " |" << token.lexeme()
              << "|\n";
  }
}
