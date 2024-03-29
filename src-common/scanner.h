// scanner.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2009-2013 John Horigan - john@glyphic.com
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
// 
// John Horigan can be contacted at john@glyphic.com or at
// John Horigan, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
//


#ifndef CFDG_SCANNER_H
#define CFDG_SCANNER_H

#include <stack>
// Flex expects the signature of yylex to be defined in the macro YY_DECL, and
// the C++ parser expects it to be declared. We can factor both as follows.

#ifndef YY_DECL

#define YY_DECL                             \
    int                                     \
    yy::Scanner::lex(                       \
    yy::CfdgParser::semantic_type* yylval,  \
    yy::CfdgParser::location_type* yylloc,  \
    Builder&                       driver   \
    )
#endif

#ifndef __FLEX_LEXER_H
#define yyFlexLexer CfdgFlexLexer
#include "FlexLexer.h"
//#undef yyFlexLexer
#endif

#include "cfdg.tab.hpp"
#include "builder.h"
#include <cassert>
#include <map>

namespace yy {

/** Scanner is a derived class to add some extra function to the scanner
 * class. Flex itself creates a class named yyFlexLexer. However we change 
 * the context of the generated yylex() function to be contained within the
 * Scanner class. This is required because the yylex() defined in yyFlexLexer
 * has no parameters. */
class Scanner : public CfdgFlexLexer
{
public:
    enum LocAction_t { normalAction, pushLoc, popLoc };
    typedef std::map<CfdgParser::token_type, const char*> tokenMap;
    /** Create a new scanner object. The streams arg_yyin and arg_yyout default
     * to cin and cout, but that assignment is only made when initializing in
     * yylex(). */
    Scanner(std::istream* arg_yyin = nullptr, std::ostream* arg_yyout = nullptr);

    /** Required for virtual functions */
    virtual ~Scanner();

    /** This is the main lexing function. It is generated by flex according to
     * the macro declaration YY_DECL above. The generated bison parser then
     * calls this virtual function to fetch new tokens. */
    virtual int lex(
        CfdgParser::semantic_type* yylval,
        CfdgParser::location_type* yylloc,
        Builder&                   driver
    );

    Builder*    driver;
    LocAction_t nextLocAction;
    int         startToken;
    int         maybeVersion;
    tokenMap    utf8chars;
    
    /** Enable debug output (via arg_yyout) if compiled into the scanner. */
    void set_debug(bool b);
    virtual void LexerError(const char* msg);
private:
    void setupLoc(CfdgParser::location_type* yylloc);
    unsigned int utf8length(const char* txt, size_t len);
    std::stack<CfdgParser::location_type> mLocationStack;
    bool        atStartup;
    CfdgParser::token_type v2token(CfdgParser::semantic_type* yylval,
                                   AST::ASTmodTerm::modTypeEnum mod);
};

} // namespace yy

#endif // CFDG_SCANNER_H
