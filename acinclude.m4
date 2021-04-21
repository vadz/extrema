#
# Check for the MUon Data (MUD) library. (See http://musr.org/mud/)
# The output variables MUD_CXXFLAGSS and MUD_LIB will contain the
# compiler flags and libraries necessary to use the MUD library,
# e.g.,
#   with-MUD=/usr/local/mud
#
AC_DEFUN([AX_CHECK_MUD], [
  AC_ARG_WITH(MUD,AC_HELP_STRING([--with-MUD(=DIR)],[use the MUon Data package (in DIR)]),,with_MUD=no)
  if test "$with_MUD" != "no" && test "$with_MUD" != ""; then
    MUD_CXXFLAGS="-DHAVE_MUD -I$with_MUD/src"
    MUD_LIB="-L$with_MUD/lib -lmud"
  fi
  AC_SUBST(MUD_CXXFLAGS)
  AC_SUBST(MUD_LIB)
])
#
# Check for the Minuit library. (See http://seal.web.cern.ch/seal/snapshot/work-packages/mathlibs/minuit/)
# The output variables MINUIT_CXXFLAGSS and MINUIT_LIB will contain the
# compiler flags and libraries necessary to use the Minuit library,
# e.g.,
#   with-MINUIT=/usr/local
#
AC_DEFUN([AX_CHECK_MINUIT], [
  AC_ARG_WITH(MINUIT,AC_HELP_STRING([--with-MINUIT(=DIR)],[use the Minuit minimization package (in DIR)]),,with_MINUIT=no)
  if test "$with_MINUIT" != "no" && test "$with_MINUIT" != ""; then
    MINUIT_CXXFLAGS="-DHAVE_MINUIT -I$with_MINUIT/include/Minuit"
    MINUIT_LIB="-L$with_MINUIT/lib -llcg_Minuit"
  fi
  AC_SUBST(MINUIT_CXXFLAGS)
  AC_SUBST(MINUIT_LIB)
])

AC_DEFUN([AX_SETCXXFLAGS],[
  EX_CXXFLAGS='-I${top_srcdir}/src -I${top_srcdir}/src/Commands -I${top_srcdir}/src/Expression -I${top_srcdir}/src/Functions -I${top_srcdir}/src/Graphics -I${top_srcdir}/src/Operators -I${top_srcdir}/src/Parsing -I${top_srcdir}/src/Utilities -I${top_srcdir}/src/Variables -I${top_srcdir}/src/wxForms -DEX_DATADIR="\"$(datadir)\"" -DEX_BINDIR="\"$(bindir)\""'
  AC_SUBST(EX_CXXFLAGS)
])
