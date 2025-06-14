#!/bin/sh

thisdir=`cd -P -- "\`dirname -- "$0"\`" && printf '%s\n' "\`pwd -P\`"`

cd "${thisdir}/lib/x86"
i686-w64-mingw32-dlltool \
  --input-def "mspdb41.def" \
  --output-lib "mspdb41.lib" \
  --add-stdcall-underscore \
  --deterministic-libraries
