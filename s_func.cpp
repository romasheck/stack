#include "s_func.h"

int copy_str(char *in, char *out)
{
    if( sizeof (*in) > sizeof (*out) )
	{
        return 0;
    }
    for( int i=0; in [ i ] != '\0'; ++i)
	{
        out [ i ] = in [ i ];
	}
    return 1;
}

int strlength (char *s)
{
    int i = 0;

    while( *(s + i) != '\0')
	{
        ++i;
    }
    return i;
}


// smth wrohg with { }  !!!
// maxlen = 50, for Onegin
/*int getline_by_Kernighan ( char s [ ], int size_str)
{
    if ( size_str > maxlen )
    {
        return 0;
    }

    int i = 0;
    char c = 0;

    while ( i < size_str - 1 && c = getchar () != EOF && c != '\n' )
    {
        s [ i ] = c;
        ++i;
    }
    if (c == '\n') 
    {
        s [ i ] = c;
        ++i;
    }
    s [ i ] = '\0';

    return i;
}*/
  // smth wrohg with { }  !!!


int compare_str ( const char *frstSTR, const char *scndSTR )
{
	assert ( frstSTR != NULL );
	assert ( scndSTR != NULL );

	int i = 0;
	while (frstSTR [ i ] == scndSTR [ i ] && frstSTR [ i ] != '\0' && scndSTR [ i ] != '\0') 
	{                                
		++i;
	}
	if ( frstSTR [ i ] > scndSTR [ i ] ) return S_frst_more_scnd;
	if ( frstSTR [ i ] < scndSTR [ i ] ) return S_scnd_more_frst;

	return S_equal;	
}

int compare_str_reverse ( char *frstSTR, char *scndSTR)
{
	assert ( frstSTR != NULL );
	assert ( scndSTR != NULL );

	int frstLEN = strlength ( frstSTR );
	int scndLEN = strlength ( scndSTR );

	for ( int i = 0; i < min ( frstLEN, scndLEN); ++i )
	{
		if ( frstSTR [ frstLEN - i ] == scndSTR [ scndLEN - i ] ) continue;
		if ( frstSTR [ frstLEN - i ]  > scndSTR [ scndLEN - i ] )  return S_frst_more_scnd;
		if ( frstSTR [ frstLEN - i ]  < scndSTR [ scndLEN - i ] )  return S_scnd_more_frst;
	}
	if ( frstLEN  > scndLEN ) return S_frst_more_scnd;
	if ( frstLEN  < scndLEN ) return S_scnd_more_frst;
	
	return S_equal;
}

int delete_symbol (char* s, char waste)
{
	assert ( s != NULL );

	char cntr_waste = 0;
	int i = -1;
    char current_symbol = s [ 0 ];

	while ( current_symbol != '\0' || current_symbol != EOF || current_symbol != '\n' ) {
			++i;
            current_symbol = s [ i ];

			if ( s [ i ] == waste )
            {
				++ cntr_waste;
				continue;
			}
			s [ i - cntr_waste ] = s [ i ];
	}
	s [ i - cntr_waste +1 ] = '\0';

	return cntr_waste;
}

int min ( int frst, int scnd )
{
	if ( frst >= scnd ) return scnd;
	else return frst; 
}

void s_print (char *s)
{
	assert (NULL != s);

	int i = 0;
	while (s[i] != '\0')
	{
		printf("%c", s[i]);
		i++;
	}
	printf("\n");
}

