AC_INIT([stupiddns],[0.1])
AC_CONFIG_SRCDIR([notsrv.c])
AC_CONFIG_HEADERS([config.h])
AC_GNU_SOURCE

AC_DEFINE(STUPID_TTL,1023,the time to live for any answer)
AC_DEFINE(STUPID_HOSTNAME,["SHARING"],the hostname that is returned on reverse lookup)
AC_DEFINE(STUPID_IP4,[{10,0,0,1}],IPv4 reverse address of the system)
AC_DEFINE(STUPID_IP6,[{0xfe,0xc0,0,0,0,0,0,0,0,0,0,0,0,1}],IPv6 reverse addres of the system)

AC_DEFINE(STUPID_IP4_ARPA,["1.0.0.10.in-addr.arpa"],IPv4 reverse address of the system)
AC_DEFINE(STUPID_IP6_ARPA,["1.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.c.e.f.ip6.arpa"],IPv6 reverse addres of the system)
AC_DEFINE(STUPID_LISTEN_PORT,[5359],Port we listen for requests)


AM_INIT_AUTOMAKE
AC_PROG_CC
AM_PROG_CC_C_O
PKG_CHECK_MODULES([LIBEVENTSTUFF], [libevent > 2.0.0])

dnl AC_CHECK_PROGS(gengetopt, gengetopt, [false])
dnl GENGETOPT=$gengetopt
dnl AC_SUBST(GENGETOPT)
dnl AC_ARG_VAR(var-name, help-string)

dnl AC_ARG_ENABLE(debug_pc,
dnl 	      [  --enable-debug_pc    Thou shall use this to debug without an icnovalike platform],
dnl 	      AC_DEFINE([DEBUG_NOT_ICNOVA]), )

AC_OUTPUT([
Makefile
])

