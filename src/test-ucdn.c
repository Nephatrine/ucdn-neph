#include <stdio.h>
#include <stdlib.h>
#include <ucdn.h>

int main( int argc, char *argv[] )
{
	printf( "unicode version: %s\n", ucdn_get_unicode_version() );

	printf( "\ntesting combining classes\n" );

	if( ucdn_get_combining_class( 0x035A ) != UCDN_COMBINING_BELOW ) {
		printf( "  - 0x035A FAILED\n\n" );
		return EXIT_FAILURE;
	}
	printf( "  - 0x035A = Below\n" );

	if( ucdn_get_combining_class( 0x035B ) != UCDN_COMBINING_ABOVE ) {
		printf( "  - 0x035B FAILED\n\n" );
		return EXIT_FAILURE;
	}
	printf( "  - 0x035B = Above\n" );

	if( ucdn_get_combining_class( 0x035C ) != UCDN_COMBINING_DOUBLE_BELOW ) {
		printf( "  - 0x035C FAILED\n\n" );
		return EXIT_FAILURE;
	}
	printf( "  - 0x035C = Double Below\n" );

	if( ucdn_get_combining_class( 0x035D ) != UCDN_COMBINING_DOUBLE_ABOVE ) {
		printf( "  - 0x035D FAILED\n\n" );
		return EXIT_FAILURE;
	}
	printf( "  - 0x035D = Double Above\n" );

	printf( "\ntesting east asian width\n" );

	if( ucdn_get_east_asian_width( 0x00AA ) != UCDN_EAST_ASIAN_AMBIGUOUS ) {
		printf( "  - 0x00AA FAILED\n\n" );
		return EXIT_FAILURE;
	}
	printf( "  - 0x00AA = Ambiguous\n" );

	if( ucdn_get_east_asian_width( 0x00AB ) != UCDN_EAST_ASIAN_NEUTRAL ) {
		printf( "  - 0x00AB FAILED\n\n" );
		return EXIT_FAILURE;
	}
	printf( "  - 0x00AB = Neutral\n" );

	if( ucdn_get_east_asian_width( 0x00AC ) != UCDN_EAST_ASIAN_NARROW ) {
		printf( "  - 0x00AC FAILED\n\n" );
		return EXIT_FAILURE;
	}
	printf( "  - 0x00AC = Narrow\n" );

	printf( "\ntesting script\n" );

	if( ucdn_get_script( 0x037E ) != UCDN_SCRIPT_COMMON ) {
		printf( "  - 0x037E FAILED\n\n" );
		return EXIT_FAILURE;
	}
	printf( "  - 0x037E = Common\n" );

	if( ucdn_get_script( 0x037F ) != UCDN_SCRIPT_GREEK ) {
		printf( "  - 0x037F FAILED\n\n" );
		return EXIT_FAILURE;
	}
	printf( "  - 0x037F = Greek\n" );

	if( ucdn_get_script( 0x0380 ) != UCDN_SCRIPT_UNKNOWN ) {
		printf( "  - 0x037F FAILED\n\n" );
		return EXIT_FAILURE;
	}
	printf( "  - 0x0380 = Unknown\n" );

	return EXIT_SUCCESS;
}
