/*

Thin C++ wrapper for libsndfile library.

The following functions are stored outside of the main file
due to different license.

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

// $Id: sndfile_ext.cpp 1040 2014-09-19 23:38:00Z serge $

#include "sndfile.hpp"      // self

#include	<math.h>        // log10

NAMESPACE_SNDFILE_CPP_START


double SndFile::get_duration()
{
    if( sfinfo_.samplerate < 1 )
        return -1;

    if( sfinfo_.frames / sfinfo_.samplerate > 0x7FFFFFFF )
        return -1;

    double seconds = ( 1.0 * sfinfo_.frames ) / sfinfo_.samplerate;

    return seconds;
}

double SndFile::calc_decibels( double max )
{
    double decibels = 0;

    int format = get_file_format();

    switch( format )
    {
    case SF_FORMAT_PCM_U8:
    case SF_FORMAT_PCM_S8:
        decibels = max / 0x80;
        break;

    case SF_FORMAT_PCM_16:
        decibels = max / 0x8000;
        break;

    case SF_FORMAT_PCM_24:
        decibels = max / 0x800000;
        break;

    case SF_FORMAT_PCM_32:
        decibels = max / 0x80000000;
        break;

    case SF_FORMAT_FLOAT:
    case SF_FORMAT_DOUBLE:
        decibels = max / 1.0;
        break;

    default:
        decibels = max / 0x8000;
        break;
    };

    return 20.0 * log10( decibels );
}

NAMESPACE_SNDFILE_CPP_END
