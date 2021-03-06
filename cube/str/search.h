/*
*	mm - memory operation module
*/
#pragma once
#include "cube\ns.h"

BEGIN_CUBE_STR_NS
/*
*	get the max length of the same prefix and postfix of input data sequence block.
*for example:
*	input data block: <abadaba>,  prefix: <a,ab, aba, abad, abada, abadab>, postfix:<a, ba, aba, daba, adaba, badaba>
*same prefix and postfix is<a, aba>, and the max is <aba>, its length is 3 which will be returned.
*@param blk: data sequence block
*@param len: length of input data block in bytes
*@return:
*	max length of the same prefix and postfix
*/
int max_same_prefix_and_postfix(const char* blk, int len);

/*
*	search wrapper, search a target data block in the content data block, return the position of the first ocurrence in the content
*@param content: content data block to search
*@param content_length: size of the content data block in bytes
*@param target: target target data to search
*@param target_length: size of the target data block in bytes
*@return
*	pointer to the first occurence of @target in the @content block, or 0 if target not found.
*/
char* search(char* content, int content_length, const char* target, int target_length, bool fast = true);
const char* search(const char* content, int content_length, const char* target, int target_length, bool fast = true);

/*
*	fast search, search a target data block in the content data block, return the position of the first ocurrence in the content
*@param content: content data block to search
*@param content_length: size of the content data block in bytes
*@param target: target target data to search
*@param target_length: size of the target data block in bytes
*@return
*	pointer to the first occurence of @target in the @content block, or 0 if target not found.
*/
char* search_fast(char* content, int content_length, const char* target, int target_length);
const char* search_fast(const char* content, int content_length, const char* target, int target_length);

/*
*	slow search, search a target data block in the content data block, return the position of the first ocurrence in the content
*@param content: content data block to search
*@param content_length: size of the content data block in bytes
*@param target: target target data to search
*@param target_length: size of the target data block in bytes
*@return
*	pointer to the first occurence of @target in the @content block, or 0 if target not found.
*/
char* search_slow(char* content, int content_length, const char* target, int target_length);
const char* search_slow(const char* content, int content_length, const char* target, int target_length);

/*
*	overwrite source with destination in the given data, use default value if destinaiton length is less than source length
*@param data: in/out, given data
*@param datalen: in, sizeof data
*@param src: in, source data to be overwrite
*@param srclen: in, length of source data in bytes
*@param dest: in, destiniation data
*@param destlen: in, length of destinationdata in bytes
*@param default: default value use to overwrite source if destination length is less than source
*@return:
*	place number overwrited, otherwise <0
*/
int search_replace(char* data, int datalen, const char* src, int srclen, const char* dest, int destlen, char default = 0, bool onlyfirst = true);
END_CUBE_STR_NS
