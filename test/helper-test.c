#include <assert.h>
#include <glib.h>
#include <stdio.h>
#include <helper.h>
#include <string.h>

static int test = 0;

#define TASSERT( a )    {                                \
        assert ( a );                                    \
        printf ( "Test %i passed (%s)\n", ++test, # a ); \
}

void error_dialog ( const char *msg, G_GNUC_UNUSED int markup )
{
    fputs ( msg, stderr );
}

int show_error_message ( const char *msg, int markup )
{
    error_dialog ( msg, markup );
    return 0;
}
#include <x11-helper.h>
int monitor_get_smallest_size ( G_GNUC_UNUSED Display *d )
{
    return 0;
}
int monitor_get_dimension ( G_GNUC_UNUSED Display *d, G_GNUC_UNUSED Screen *screen, G_GNUC_UNUSED int monitor, G_GNUC_UNUSED workarea *mon )
{
    return 0;
}

int main ( int argc, char ** argv )
{
    cmd_set_arguments ( argc, argv );
    char **list     = NULL;
    int  llength    = 0;
    char * test_str =
        "{host} {terminal} -e bash -c \"{ssh-client} {host}; echo '{terminal} {host}'\"";
    helper_parse_setup ( test_str, &list, &llength, "{host}", "chuck",
                         "{terminal}", "x-terminal-emulator", NULL );

    TASSERT ( llength == 6 );
    TASSERT ( strcmp ( list[0], "chuck" ) == 0 );
    TASSERT ( strcmp ( list[1], "x-terminal-emulator" ) == 0 );
    TASSERT ( strcmp ( list[2], "-e" ) == 0 );
    TASSERT ( strcmp ( list[3], "bash" ) == 0 );
    TASSERT ( strcmp ( list[4], "-c" ) == 0 );
    TASSERT ( strcmp ( list[5], "ssh chuck; echo 'x-terminal-emulator chuck'" ) == 0 );

    g_strfreev ( list );
}