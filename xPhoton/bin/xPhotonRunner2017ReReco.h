#ifndef __xPhotonRunner2017ReReco_h__
#define __xPhotonRunner2017ReReco_h__
#include <iostream>
#include <sstream>

const char* GetFileName(int argc, char* argv[]);
int         GetOption  (int argc, char* argv[]);
int         IntTranslater(char* val);
int main(int argc, char* argv[]);
#endif