/*
 * This example is based on libsndfile-1.0.25/programs/sndfile-info.c
 */

/*
** Copyright (C) 1999-2011 Erik de Castro Lopo <erikd@mega-nerd.com>
**
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**
**     * Redistributions of source code must retain the above copyright
**       notice, this list of conditions and the following disclaimer.
**     * Redistributions in binary form must reproduce the above copyright
**       notice, this list of conditions and the following disclaimer in
**       the documentation and/or other materials provided with the
**       distribution.
**     * Neither the author nor the names of any contributors may be used
**       to endorse or promote products derived from this software without
**       specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
** TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
** PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
** CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
** EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
** OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
** OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
** ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// $Id: example.cpp 1054 2014-09-22 18:09:35Z serge $

#include "sndfile.hpp"

void get_info( const char *filename )
{
    sndfile::SndFile file;

    if( file.open( filename ) == false )
    {
        printf( "Error : Not able to open input file %s.\n", filename );
        fflush( stdout );
        puts( file.get_log_info().c_str() );
        puts( file.strerror().c_str() );
        return;
    };

    printf( "========================================\n" );
    puts( file.get_log_info().c_str() );
    printf( "----------------------------------------\n" );

    printf( "Sample Rate : %d\n", file.get_samplerate() );

    if( file.is_num_frames_unknown() )
        printf( "Frames      : unknown\n" );
    else
        printf( "Frames      : %llu\n", file.get_num_frames() );

    printf( "Channels    : %d\n", file.get_channels() );
    printf( "Format      : 0x%08X\n", file.get_format() );
    printf( "Sections    : %d\n", file.get_sections() );
    printf( "Seekable    : %s\n", file.is_seekable() ? "TRUE" : "FALSE" );
    printf( "Duration    : %4.2f\n", file.get_duration() );

    if( file.get_num_frames() < 100 * 1024 * 1024 )
    { /* Do not use sf_signal_max because it doesn't work for non-seekable files . */
        double signal_max = file.get_signal_max();
        double decibels = file.calc_decibels( signal_max );
        printf( "Signal Max  : %g (%4.2f dB)\n", signal_max, decibels );
    };
    putchar( '\n' );

    file.close();
}


int main( int argc, char *argv[] )
{
    for( int i = 1; i < argc; i++ )
        get_info( argv[i] );

    return 0;
}
