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

// $Id: sndfile.hpp 1031 2014-09-19 23:07:51Z serge $

#include <string>           // std::string
#include <sndfile.h>        // SNDFILE

#include "namespace_lib.h"      // NAMESPACE_SNDFILE_CPP_START

NAMESPACE_SNDFILE_CPP_START

class SndFile
{
    static const int BUFFER_LEN      = (1 << 16);

public:

    SndFile();
    ~SndFile();

    // wrappers
    bool open( const char *name );
    int close();
    int command( int command, void *data, int datasize );
    std::string strerror();

    // auxiliary functions
    double get_signal_max();
    double get_duration();
    double calc_decibels( double max );

    int get_file_format() const;
    std::string get_log_info();

    bool is_num_frames_unknown() const;
    long long get_num_frames() const;
    int get_samplerate() const;
    int get_channels() const;
    int get_format() const;
    int get_sections() const;
    bool is_seekable() const;

private:

    SNDFILE     *file_;
    SF_INFO     sfinfo_;
};

NAMESPACE_SNDFILE_CPP_END
