/*
 * Copyright (c) 2012, 2013, Joel Bodenmann aka Tectu <joel@unormal.org>
 * Copyright (c) 2012, 2013, Andrew Hannam aka inmarket
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *    * Neither the name of the <organization> nor the
 *      names of its contributors may be used to endorse or promote products
 *      derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * This demo demonstrates the use of the GAUDIN module to read audio channel 0.
 * The audio channel gets read to display a very simple oscilloscope.
 *
 * It also demonstrates how to write your own custom GWIN window type.
 */
#include "gfx.h"

/* Include our custom gwin audio oscilloscope */
#include "gwinosc.h"

/* Specify our timing parameters */
#define	MY_AUDIO_FREQUENCY	4000			/* 4khz */
#define MY_AUDIO_CHANNEL	0				/* Use channel 0 */

/* Data */
static GScopeObject			gScopeWindow;

/*
 * Application entry point.
 */
int main(void) {
	GHandle					ghScope;
	coord_t					swidth, sheight;

	gfxInit();

	/* Get the screen dimensions */
	swidth = gdispGetWidth();
	sheight = gdispGetHeight();

	/* Set up the scope window to fill the screen */
	{
		GWindowInit	wi;

		wi.show = TRUE;
		wi.x = wi.y = 0;
		wi.width = swidth; wi.height = sheight;
		ghScope = gwinScopeCreate(&gScopeWindow, &wi, MY_AUDIO_CHANNEL, MY_AUDIO_FREQUENCY);
	}
	gwinSetBgColor(ghScope, White);
	gwinSetColor(ghScope, Red);
	gwinClear(ghScope);

	/* Just keep displaying the scope traces */
	while (TRUE) {
		gwinScopeWaitForTrace(ghScope);
	}
}
