#ifndef __checkJetIDRunner_h__
#define __checkJetIDRunner_h__
#include <iostream>
#include <sstream>

const char* GetFileName(int argc, char* argv[]);
int         GetOption  (int argc, char* argv[]);
int         IntTranslater(char* val);
int main(int argc, char* argv[]);
#endif
