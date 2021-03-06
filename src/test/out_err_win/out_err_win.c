// SPDX-License-Identifier: BSD-3-Clause
/* Copyright 2014-2017, Intel Corporation */

/*
 * out_err_win.c -- unit test for error messages
 */

#define LOG_PREFIX "trace"
#define LOG_LEVEL_VAR "TRACE_LOG_LEVEL"
#define LOG_FILE_VAR "TRACE_LOG_FILE"
#define MAJOR_VERSION 1
#define MINOR_VERSION 0

#include <sys/types.h>
#include <stdarg.h>
#include "unittest.h"
#include "pmemcommon.h"

int
wmain(int argc, wchar_t *argv[])
{
	char buff[UT_MAX_ERR_MSG];

	STARTW(argc, argv, "out_err_win");

	/* Execute test */
	common_init(LOG_PREFIX, LOG_LEVEL_VAR, LOG_FILE_VAR,
			MAJOR_VERSION, MINOR_VERSION);

	errno = 0;
	ERR("ERR #%d", 1);
	UT_OUT("%S", out_get_errormsgW());

	errno = 0;
	ERR("!ERR #%d", 2);
	UT_OUT("%S", out_get_errormsgW());

	errno = EINVAL;
	ERR("!ERR #%d", 3);
	UT_OUT("%S", out_get_errormsgW());

	errno = EBADF;
	ut_strerror(errno, buff, UT_MAX_ERR_MSG);
	out_err(__FILE__, 100, __func__,
		"ERR1: %s:%d", buff, 1234);
	UT_OUT("%S", out_get_errormsgW());

	errno = EBADF;
	ut_strerror(errno, buff, UT_MAX_ERR_MSG);
	out_err(NULL, 0, NULL,
		"ERR2: %s:%d", buff, 1234);
	UT_OUT("%S", out_get_errormsgW());

	/* Cleanup */
	common_fini();

	DONEW(NULL);
}
