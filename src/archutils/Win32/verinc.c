// Ehhh....
//
// I think I'll just put this one in the public domain
// (with no warranty as usual).
//
// --Avery

// Modified for OpenITG pre-build event... -- Vyhd

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>

typedef unsigned long ulong;

int main(void)
{
	FILE *f;
	ulong build=0, build_t;
	char strdate[10], strtime[25];
	time_t tm;

	// try to read the last version seen
	if ( f = fopen("version.bin","rb") )
	{
		if( fread(&build_t, sizeof(build_t), 1, f) == 4 )
			build = build_t;
		fclose( f );
	}

	// increment the build number
	++build;

	// get the current time
	time(&tm);

	// print the debug serial date/time
	strftime( strdate, 15, "%Y%m%d", localtime(&tm) );
	memcpy( strtime, asctime(localtime(&tm)), 24 );

	// zero out the newline character
	strtime[24] = 0;

	if ( f = fopen("verstub.cpp","w") )
	{
		fprintf(f,
			"unsigned long VersionNumber = %ld;\n"
			"extern const char *const VersionTime = \"%s\";\n"
			"extern const char *const VersionDate = \"%s\";\n"
			"extern const bool VersionSVN = false;\n",
			build, strtime, strdate );

		fclose( f );
	}

	if( f = fopen("version.bin","wb") )
	{
		fwrite( &build, sizeof(build), 1, f );
		fclose( f );
	}

	return 0;
}
