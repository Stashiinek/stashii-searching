#include <libfts/funct.hpp>
#include <csv.h>

#include <iostream>

fts::inData ret_inData();

#ifdef __cplusplus
extern "C" {
#endif

void indexator();
void search();

#ifdef __cplusplus
}
#endif