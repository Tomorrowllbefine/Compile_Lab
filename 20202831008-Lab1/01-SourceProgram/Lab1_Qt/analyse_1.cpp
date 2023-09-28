#include "analyse_1.h"
#include<iostream>
#include<string>
#include<math.h>
#include<map>
#include<unordered_set>
#include <QDebug>

using namespace std;

// ctor
Analyse_1::Analyse_1(){}


// 单词种类的枚举
enum TokenID {
    ASSIGN, EQ, LT, GT, LTE, GTE, NOTEQ, NUMBER, ARROW, POINT, COMMA, LSHIFT, RSHIFT, COLON, SCOPEOP, LCURLYBRACE, RCURLYBRACE,
    ID, ADD, SUB, MUL, DIV, MOD, ADDEQ, ADDADD, SUBEQ, SUBSUB, MULEQ, MULMUL, DIVEQ, QMARK,
    LBRACKET, RBRACKET, BRACKETS, LSQUAREBRACKET, RSQUAREBRACKET, SQUAREBRACKETS, SEMICOLON,
    BITAND, LOGICAND, BITOR, LOGICOR, LOGICNOT, BITNOT,
    COMMENT, ENDCOMMENT, BEGINCOMMENT, STRING, APOSTROPHE,
    ENDINPUT,
};
// 关键字的哈希表
unordered_set<std::string> KeyWords = {
    "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor", "bool",
    "break", "case", "catch", "char", "char8_t", "char16_t", "char32_t", "class", "compl",
    "const", "const_cast", "continue", "decltype", "default", "delete", "do", "double",
    "dynamic_cast", "else", "enum", "explicit", "export", "extern", "false", "float",
    "for", "friend", "goto", "if", "inline", "int", "long", "mutable", "namespace",
    "new", "noexcept", "not", "not_eq", "nullptr", "operator", "or", "or_eq", "private",
    "protected", "public", "register", "reinterpret_cast", "return", "short", "signed",
    "sizeof", "static", "static_assert", "static_cast", "struct", "switch", "template",
    "this", "throw", "true", "try", "typedef", "typeid", "typename", "union", "unsigned",
    "using", "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq",
    "cin","cout","cerr","clog"
};
// 运算符号
unordered_set<std::string> Operators = {
    "+", "-", "*", "/", "=", "==", "!=", "<", ">", "<=", ">=", "&&", "||", "!",
    "&", "|", "^", "~", "<<", ">>", "++", "--", "+=", "-=", "*=", "/=", "%=", "&=", "|=",
    "^=", "<<=", ">>=", "sizeof", "->", ".", ":", "[]", "()", "?", ","
};
// 特殊符号
unordered_set<std::string> special_symbols = {
    "{", "}", "[", "]", "(", ")", "<<", ">>", "::", ";", "..."
};
// 预处理指令
unordered_set<string> preprocess_directive = {
    "#include","#define","#ifdef","#ifndef","#if","#endif","#else","#elif","#undef","#pragma","#error","once"
};


// 单词结构
struct TokenStru
{
    TokenID  ID;
    double val;
    char E[20]; // 存储数字E后的内容
    char op[3];
    char word[20];
};


TokenStru token; // 全局变量
char buffer[255];
int pos = 0;  // 全局index

// 词法分析函数：算术表达式的词法分析，
// 数字是优于表示符判别的，不会出现标识符第一个是数字的情况
void Analyse_1::GetToken()
{
    int s;
    memset(token.op, 0, sizeof token.op);
    memset(token.word,0,sizeof token.word);
    memset(token.E, 0, sizeof token.E);

    while (buffer[pos] == 32 || buffer[pos] == 9)  // spacebar or tab
        pos++;
    // 数字
    if ( (buffer[pos] >= '0') && (buffer[pos] <= '9'))
    {
        s = 0;
        while (buffer[pos] >= '0' && buffer[pos] <= '9')
        {
            s = s * 10 + buffer[pos] - '0';   pos++;
        }
        token.ID = NUMBER; token.val = s;
        if (buffer[pos] == '.')
        {
            int len = 0;
            s = 0; pos++;
            while (buffer[pos] >= '0' && buffer[pos] <= '9')
            {
                s = s * 10 + buffer[pos] - '0'; len++;  pos++;
            }
            token.val = token.val + s / pow(10, len);
        }
        if (buffer[pos] == 'E' or buffer[pos] == 'e') {
            int len = 0;
            token.E[len++] = buffer[pos++];
            if (buffer[pos] == '+' || buffer[pos] == '-') {
                token.E[len++] = buffer[pos++];
            }
            while (buffer[pos] >= '0' && buffer[pos] <= '9') {
                token.E[len++] = buffer[pos++];
            }
            token.E[len] = '\0';
        }
    }
    // 标识符(关键字、预处理指令)
    else if (isalpha(buffer[pos]) || buffer[pos] == '#' || buffer[pos] == '_')
    {
        int len = 0;
        while (isalpha(buffer[pos]) || isdigit(buffer[pos]) || buffer[pos] == '_' || buffer[pos] == '#')
        {
            token.word[len] = buffer[pos];
            len++;
            pos++;
        }
        token.word[len] = '\0';
        token.ID = ID;
    }
    // 运算符、特殊符号、注释、字符串
    else if (buffer[pos] != '\0')
    {
        int len = 0;
        switch (buffer[pos])
        {
        case '+':  token.op[0] = buffer[pos]; // +
            if (buffer[pos + 1] == '=') { // +=
                pos++; token.ID = ADDEQ; token.op[1] = '='; token.op[2] = '\0'; break;
            }
            else if (buffer[pos + 1] == '+') { // ++
                pos++; token.ID = ADDADD; token.op[1] = '+'; token.op[2] = '\0'; break;
            }
            token.op[1] = '\0';  token.ID = ADD;
            break;
        case '-': token.op[0] = buffer[pos];  // -
            if (buffer[pos + 1] == '=') { // -=
                pos++; token.ID = SUBEQ; token.op[1] = '='; token.op[2] = '\0'; break;
            }
            else if (buffer[pos + 1] == '-') { // --
                pos++; token.ID = SUBSUB; token.op[1] = '-'; token.op[2] = '\0'; break;
            }
            else if (buffer[pos + 1] == '>') { // ->
                pos++; token.ID = ARROW; token.op[1] = '>'; token.op[2] = '\0'; break;
            }
            token.op[1] = '\0'; token.ID = SUB;  break; // -
        case '*':token.op[0] = buffer[pos];
            if (buffer[pos + 1] == '=') { // *=
                pos++; token.ID = MULEQ; token.op[1] = '='; token.op[2] = '\0'; break;
            }
            else if (buffer[pos + 1] == '*') { // --
                pos++; token.ID = MULMUL; token.op[1] = '*'; token.op[2] = '\0'; break;
            }
            else if (buffer[pos + 1] == '/') {
                pos++;  token.op[1] = '/'; token.ID = ENDCOMMENT; token.op[2] = '\0'; break;
            }
            token.op[1] = '\0'; token.ID = MUL;  break; // -
        case '/': token.op[0] = buffer[pos];
            if (buffer[pos + 1] == '=') {
                pos++; token.ID = DIVEQ; token.op[1] = '='; token.op[2] = '\0'; break;
            }
            else if (buffer[pos + 1] == '/') {
                len = 0;
                // 后续的所有内容都是注释
                while (buffer[pos] != '\0') {
                    token.word[len++] = buffer[pos];
                    pos++;
                }
                token.op[1] = '/'; token.ID = COMMENT; token.op[2] = '\0'; break;
            }
            else if (buffer[pos + 1] == '*') {
                len = 2;
                token.word[0] = buffer[pos++];
                token.word[1] = buffer[pos++];
                // 直到遇到 * /
                while (buffer[pos] != '\0') {
                    if (buffer[pos] == '*' && buffer[pos + 1] != '\0' && buffer[pos + 1] == '/')
                    {
                        token.word[len++] = buffer[pos++];
                        token.word[len++] = buffer[pos]; // 只取下一个pos
                        break;
                    }
                    token.word[len++] = buffer[pos];
                    pos++;
                }
                token.op[1] = '*'; token.ID = BEGINCOMMENT; token.op[2] = '\0';
                break;
            }
            token.op[1] = '\0'; token.ID = DIV;  break;   // /
        case '%': token.ID = MOD; token.op[0] = buffer[pos]; token.op[1] = '\0';  break;
        case '(':
            if (buffer[pos + 1] == ')') { // [] 不拆开
                token.op[0] = '(';
                pos++; token.ID = BRACKETS; token.op[1] = ')'; token.op[2] = '\0'; break;
            }
            else {
                token.op[0] = '('; token.op[1] = '\0'; token.ID = LBRACKET; break;
            }
        case ')': token.ID = RBRACKET; token.op[0] = buffer[pos]; token.op[1] = '\0';  break;
        case ';': token.ID = SEMICOLON; token.op[0] = buffer[pos]; token.op[1] = '\0';  break;
        case '&': token.op[0] = buffer[pos]; // &
            if (buffer[pos + 1] == '&') { // &&
                pos++; token.ID = LOGICAND;
                token.op[1] = '&'; token.op[2] = '\0'; break;
            }
            token.op[1] = '\0'; token.ID = BITAND;
            break;
        case '|':  token.op[0] = buffer[pos]; // |
            if (buffer[pos + 1] == '|') { // ||
                pos++; token.ID = LOGICOR;
                token.op[1] = '|'; token.op[2] = '\0'; break;
            }
            token.op[1] = '\0'; token.ID = BITOR;
            break;
        case '~': token.op[0] = '~'; token.op[1] = '\0'; token.ID = BITNOT; break; // ~位取反
        case '>': token.op[0] = '>';
            if (buffer[pos + 1] == '=') { // >=
                pos++; token.ID = GTE; token.op[1] = '='; token.op[2] = '\0'; break;
            }
            else if (buffer[pos + 1] == '>') { // >>
                pos++; token.op[1] = '>'; token.ID = RSHIFT; token.op[2] = '\0'; break;
            }
            token.op[1] = '\0'; token.ID = GT;
            break;
        case '<': token.op[0] = '<';
            if (buffer[pos + 1] == '=') { // <=
                pos++; token.ID = LTE; token.op[1] = '='; token.op[2] = '\0'; break;
            }
            else if (buffer[pos + 1] == '<') { // <<
                pos++; token.op[1] = '<'; token.ID = LSHIFT; token.op[2] = '\0'; break;
            }
            token.op[1] = '\0'; token.ID = LT;
            break;
        case '=': token.op[0] = '=';
            if (buffer[pos + 1] == '=') { // ==
                pos++; token.ID = EQ; token.op[1] = '='; token.op[2] = '\0'; break;
            }
            token.op[1] = '\0'; token.ID = ASSIGN;
            break;
        case '!': token.op[0] = '!';
            if (buffer[pos + 1] == '=') { // !=
                pos++; token.ID = NOTEQ; token.op[1] = '='; token.op[2] = '\0'; break;
            }
            token.op[1] = '\0'; token.ID = LOGICNOT;
            break;
        case '.': token.op[0] = '.'; token.op[1] = '\0'; token.ID = POINT; break; // .
        case ',': token.op[0] = ','; token.op[1] = '\0'; token.ID = COMMA; break; // .
        case '?': token.op[0] = '?'; token.op[1] = '\0'; token.ID = QMARK; break; // ?
        case '[':
            if (buffer[pos + 1] == ']') { // [] 不拆开
                token.op[0] = '[';
                pos++; token.ID = SQUAREBRACKETS; token.op[1] = ']'; token.op[2] = '\0'; break;
            }
            else {
                token.op[0] = '['; token.op[1] = '\0'; token.ID = LSQUAREBRACKET; break;
            }
        case ']': token.op[0] = ']'; token.op[1] = '\0'; token.ID = RSQUAREBRACKET; break;
        case ':': token.op[0] = ':';
            if (buffer[pos + 1] == ':') {
                pos++; token.op[1] = ':'; token.op[2] = '\0'; token.ID = SCOPEOP; break;
            }
            token.ID = COLON; token.op[1] = '\0'; break;
        case '{': token.op[0] = '{'; token.op[1] = '\0'; token.ID = LCURLYBRACE; break;
        case '}': token.op[0] = '}'; token.op[1] = '\0'; token.ID = RCURLYBRACE; break;
        case '\'': token.op[0] = '\'';
            token.word[0] = buffer[pos++];
            token.word[1] = buffer[pos++];
            token.word[2] = buffer[pos];
            token.ID = APOSTROPHE;
            token.op[1] = '\0';
            break;
        case '"': token.op[0] = 34; // 字符串
            len = 0;
            while (buffer[pos] != '\0') {
                if (buffer[pos + 1] != '\0' && buffer[pos + 1] == '"') {
                    token.word[len++] = buffer[pos++];
                    token.word[len] = buffer[pos]; // 只取下一个
                    break; // while
                }
                token.word[len++] = buffer[pos];
                pos++;
            }
            token.op[1] = '\0'; token.ID = STRING;
            //            qDebug() << "TestString: ";
            //            for (int i = 0; i < len; i++) qDebug().noquote() << token.word[i];
            //            for (int i = 0; i < 3; i++) qDebug().noquote() << token.op[i];
            //            qDebug();
            break;

        default:  token.op[0] = buffer[pos];
        }
        pos++;
    }
    else  token.ID = ENDINPUT;

}
// 判断当前op[]是否是 注释// /* */  串"
bool Analyse_1::strComparation(char op[3], string s) {
    for (int i = 0; i < 2; i++) {
        if (op[i] != '\0') {
            if (op[i] != s[i]) return false;
        }
    }
    return true;
}


string Analyse_1::analyse(string str) {
    pos = 0;

    string ans = ""; // 结果

    // 将str中的内容存入buffer数组
    strcpy(buffer, str.c_str());

    GetToken(); // 获取单词
    while (token.ID != ENDINPUT)
    {

        if (token.ID == NUMBER){

            ans += std::to_string(token.val);
            if (token.E[0] != '\0') {
                ans += token.E;
            }
            ans += "\t数字";
        }
        else if (token.ID == ID) {
            if (KeyWords.find(token.word) != KeyWords.end()) {

                ans = ans + token.word + "\t关键字";
            }
            else if (preprocess_directive.find(token.word) != preprocess_directive.end()) {
                ans = ans + token.word + "\t预处理指令";
            }
            else ans = ans + token.word + "\t标识符";
        }
        else {
            if (special_symbols.find(token.op) != special_symbols.end()) {
                ans = ans + token.op + "\t特殊符号";
            }
            else if (Operators.find(token.op) != Operators.end()) {
                ans = ans + token.op + "\t运算符";
            }
            else {

                qDebug() << "testOP: " << token.op;
                if (strComparation(token.op, "//")) {
                    ans = ans + token.word + "\t单行注释";
                }
                else if (strComparation(token.op, "/*")) {
                    ans = ans + token.word + "\t多行注释";
                }
                else if (strComparation(token.op, "*/")) {
                    ans = ans + token.op + "\t多行注释";
                }
                else if(strComparation(token.op, "\"")) {
                    ans = ans + token.word + "\t字符串";
                }
                else if (strComparation(token.op, "\'")) {
                    ans = ans + token.word + "\t字符";
                }
                else ans += "Unknown Text...";
            }
        }
        ans += "\n";
        GetToken(); // 获取下一个单词
    }
    cout << ans << endl;
    return ans;
}

