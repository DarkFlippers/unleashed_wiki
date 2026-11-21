#pragma once
/* Force-included in every translation unit when building for the host. */
#ifndef _ATTRIBUTE
#define _ATTRIBUTE(attrs) __attribute__(attrs)
#endif
