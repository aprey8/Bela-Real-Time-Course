/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

The platform for ultra-low latency audio and sensor processing
http://bela.io

(c) 2020 Augmented Instruments Ltd

A project from the Augmented Instruments Laboratory within the
Centre for Digital Music at Queen Mary University of London.
http://instrumentslab.org

The Bela software is distributed under the GNU Lesser General Public License
(LGPL 3.0), available here: https://www.gnu.org/licenses/lgpl-3.0.txt
*/

#include <Bela.h>
#include <cmath>

float gFrequency = 440.0;			// Frequency of the sine wave in Hz
float gAmplitude = 0.6;				// Amplitude of the sine wave (1.0 is maximum)
unsigned int gNumSamples = 0; 		// Track total number of elapsed samples for sin wave
float gPhase = 0;					// Track phase of sin wave

// setup() runs once at the beginning of your program
bool setup(BelaContext *context, void *userData)
{
    return true;
}

// render() is called repeatedly by Bela for each audio block
void render(BelaContext *context, void *userData)
{
   	// This for() loop goes through all the samples in the block
	for (unsigned int n = 0; n < context->audioFrames; n++) {
		
		// Increment phase by one sample at frequency
		gPhase += 2.0 * M_PI * gFrequency / context->audioSampleRate);
		if (gPhase >= 2.0 * M_PI) {
			gphase -= 2.0 * M_PI;
		}
		
		// Calculate sin wave sample
		float out = gAmplitude * sin(gPhase);
		
		// This part is done for you: store the sample in the
		// audio output buffer
		for(unsigned int channel = 0; channel < context->audioOutChannels; channel++) {
		    audioWrite(context, n, channel, out);
		}
    }
}

// cleanup() runs once at the end of the program
void cleanup(BelaContext *context, void *userData)
{
	// Nothing to do here
}
