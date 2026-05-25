#ifndef PARSER_H
#define PARSER_H

#include "../context/context.h"

// 
// Parser the raw HTTP request buffer and fills the RequestContext
//
void parse_buffer(char *buffer, RequestContext *context);
#endif
