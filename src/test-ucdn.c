#include <stdio.h>
#include <stdlib.h>
#include <ucdn.h>

int report( uint32_t cp, uint32_t result, uint32_t expect )
{
	if( result != expect ) {
		printf( "  - U+%04X\t= %d\t= EXPECTED %d\n", cp, result, expect );
		return 1;
	}

	printf( "  - U+%04X\t= %d\t= SUCCESS\n", cp, result );
	return 0;
}

int main( int argc, char *argv[] )
{
	int failures = 0;

	printf( "unicode version: %s\n", ucdn_get_unicode_version() );

	printf( "\ntesting combining classes\n" );

	uint32_t cc_expect[] = {0x035A, UCDN_COMBINING_BELOW,
	                        0x035B, UCDN_COMBINING_ABOVE,
	                        0x035C, UCDN_COMBINING_DOUBLE_BELOW,
	                        0x035D, UCDN_COMBINING_DOUBLE_ABOVE};

	for( size_t i = 0; i < sizeof( cc_expect ) / sizeof( uint32_t ); i += 2 )
		failures +=
		        report( cc_expect[i], ucdn_get_combining_class( cc_expect[i] ),
		                cc_expect[i + 1] );

	printf( "\ntesting east asian width\n" );

	uint32_t ea_expect[] = {0x00AA, UCDN_EAST_ASIAN_AMBIGUOUS,
	                        0x00AB, UCDN_EAST_ASIAN_NEUTRAL,
	                        0x00AC, UCDN_EAST_ASIAN_NARROW};

	for( size_t i = 0; i < sizeof( ea_expect ) / sizeof( uint32_t ); i += 2 )
		failures +=
		        report( ea_expect[i], ucdn_get_east_asian_width( ea_expect[i] ),
		                ea_expect[i + 1] );

	printf( "\ntesting script\n" );

	uint32_t sc_expect[] = {0x037E, UCDN_SCRIPT_COMMON,
	                        0x037F, UCDN_SCRIPT_GREEK,
	                        0x0380, UCDN_SCRIPT_UNKNOWN};

	for( size_t i = 0; i < sizeof( sc_expect ) / sizeof( uint32_t ); i += 2 )
		failures += report( sc_expect[i], ucdn_get_script( sc_expect[i] ),
		                    sc_expect[i + 1] );

	printf( "\ntesting linebreak\n" );

	uint32_t lb_expect[] = {
	        0x000D, UCDN_LINEBREAK_CARRIAGE_RETURN,
	        0x000A, UCDN_LINEBREAK_LINE_FEED,
	        0x0085, UCDN_LINEBREAK_NEXT_LINE,
	        0x00A7, UCDN_LINEBREAK_AMBIGUOUS,
	        0x0E01, UCDN_LINEBREAK_COMPLEX_CONTEXT,
	        0x0E31, UCDN_LINEBREAK_COMPLEX_CONTEXT,
	        0x0E78, UCDN_LINEBREAK_UNKNOWN,
	        0x3043, UCDN_LINEBREAK_CONDITIONAL_JAPANESE_STARTER};

	for( size_t i = 0; i < sizeof( lb_expect ) / sizeof( uint32_t ); i += 2 )
		failures +=
		        report( lb_expect[i], ucdn_get_linebreak_class( lb_expect[i] ),
		                lb_expect[i + 1] );

	printf( "\ntesting simplified linebreak\n" );

	uint32_t lbr_expect[] = {0x000D, UCDN_LINEBREAK_MANDATORY_BREAK,
	                         0x000A, UCDN_LINEBREAK_MANDATORY_BREAK,
	                         0x0085, UCDN_LINEBREAK_MANDATORY_BREAK,
	                         0x00A7, UCDN_LINEBREAK_ALPHABETIC,
	                         0x0E01, UCDN_LINEBREAK_ALPHABETIC,
	                         0x0E31, UCDN_LINEBREAK_COMBINING_MARK,
	                         0x0E78, UCDN_LINEBREAK_ALPHABETIC,
	                         0x3043, UCDN_LINEBREAK_NONSTARTER};

	for( size_t i = 0; i < sizeof( lbr_expect ) / sizeof( uint32_t ); i += 2 )
		failures += report( lbr_expect[i],
		                    ucdn_get_resolved_linebreak_class( lbr_expect[i] ),
		                    lbr_expect[i + 1] );

	if( failures > 0 ) return EXIT_FAILURE;
	return EXIT_SUCCESS;
}
