#ifndef S_FUNC_H_INCLUDED
#define S_FUNC_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <cstring>
#include <string.h>

/** \brief
 *
 * \param
 * \param
 * \return
 */

enum for_compare_str
{
	 S_equal,
	 S_frst_more_scnd,
	 S_scnd_more_frst
};
#define PRINT_LINE printf("I am at line %d in func %s\n", __LINE__, __func__);
int min ( int frst, int scnd );

int delete_symbol (char* s[], char waste);

/** \brief  compare two string
 *
 * \param  frstSTR - adress first string
 * \param  scndSTR - adress second string
 * \return   result of comparation - const from enum for_compsre_str
 */
int compare_str (const char *frstSTR,const char *scndSTR );

/** \brief  compare two string from left to right
 *
 * \param  frstSTR - adress first string
 * \param  scndSTR - adress second string
 * \return   result of comparation - const from enum for_compsre_str
 */
int compare_str_reverse ( char *frstSTR, char *scndSTR);

/** \brief copy frst string in scnd
 *
 * \param  in [ ] - frst input string
 * \param  out [ ] - scnd output string
 * \return   1
 */
int copy_str( char *in, char *out);

/** \brief  find lentgh of string
 *
 * \param  s [ ] - string, whose size founded
 * \return  i - string size
 */
int strlength (char* s);

void s_print  (char *s);

int  del_xspace (char *s, size_t size);

void exch_symbols (char *s, size_t size, const char bad, const char good);

int  del_void_str (char *s, size_t size);

#endif // S_FUNC_H_INCLUDED
