/*

Thin C++ wrapper for libsndfile library.

Copyright (C) 2014 Sergey Kolevatov

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

*/

// $Id: sndfile.cpp 1035 2014-09-19 23:25:54Z serge $

#include "sndfile.hpp"      // self

#include	<cstring>       // memset

NAMESPACE_SNDFILE_CPP_START

SndFile::SndFile():
    file_( nullptr )
{
    memset( &sfinfo_, 0, sizeof( sfinfo_ ) );
}

SndFile::~SndFile()
{
    if( file_ != nullptr )
        close();
}

int SndFile::command( int command, void *data, int datasize )
{
    return sf_command( file_, command, data, datasize );
}

bool SndFile::open( const char *name )
{
    if( file_ != nullptr )
        return false;

    file_ = sf_open( name, SFM_READ, &sfinfo_ );

    if( file_ == nullptr )
        return false;

    return true;
}

int SndFile::close()
{
    int res = sf_close( file_ );

    file_   = nullptr;

    return res;
}

std::string SndFile::strerror()
{
    return sf_strerror( file_ );
}

double SndFile::get_signal_max()
{
    double max;

    command( SFC_CALC_SIGNAL_MAX, &max, sizeof( max ) );

    return max;
}

int SndFile::get_file_format() const
{
    return sfinfo_.format & SF_FORMAT_SUBMASK;
}

std::string SndFile::get_log_info()
{
    static char res[BUFFER_LEN];

    command( SFC_GET_LOG_INFO, res, BUFFER_LEN );

    return res;
}

bool SndFile::is_num_frames_unknown() const
{
    return get_num_frames() == SF_COUNT_MAX;
}

long long SndFile::get_num_frames() const
{
    return sfinfo_.frames;
}
int SndFile::get_samplerate() const
{
    return sfinfo_.samplerate;
}
int SndFile::get_channels() const
{
    return sfinfo_.channels;
}
int SndFile::get_format() const
{
    return sfinfo_.format;
}
int SndFile::get_sections() const
{
    return sfinfo_.sections;
}
bool SndFile::is_seekable() const
{
    return sfinfo_.seekable ? true : false;
}


NAMESPACE_SNDFILE_CPP_END
