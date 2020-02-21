/*
 * Project:     Om Software
 * Version:     1.0.0
 * Website:     http://www.carlschissler.com/om
 * Author(s):   Carl Schissler
 * 
 * Copyright (c) 2016, Carl Schissler
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 	1. Redistributions of source code must retain the above copyright
 * 	   notice, this list of conditions and the following disclaimer.
 * 	2. Redistributions in binary form must reproduce the above copyright
 * 	   notice, this list of conditions and the following disclaimer in the
 * 	   documentation and/or other materials provided with the distribution.
 * 	3. Neither the name of the copyright holder nor the
 * 	   names of its contributors may be used to endorse or promote products
 * 	   derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef INCLUDE_OM_SOUND_STREAM_RECORDER_H
#define INCLUDE_OM_SOUND_STREAM_RECORDER_H


#include "omSoundFiltersConfig.h"


#include "omSoundFilter.h"


//##########################################################################################
//*************************  Start Om Sound Filters Namespace  *****************************
OM_SOUND_FILTERS_NAMESPACE_START
//******************************************************************************************
//##########################################################################################




//********************************************************************************
/// A class that handles recording audio data to a streaming sound destination.
/**
  * This class takes a pointer to a SoundOutputStream and then records sound
  * to that stream when the recorder is set to the 'record' mode.
  */
class StreamRecorder : public SoundFilter
{
	public:
		
		//********************************************************************************
		//******	Constructors
			
			
			/// Create a default sound stream recorder without any stream to record to.
			/**
			  * The constructed object will not do any recording until it has a valid
			  * stream object.
			  */
			StreamRecorder();
			
			
			/// Create a sound stream recorder which records to the specified sound output stream.
			/**
			  * If the supplied stream is NULL or invalid, the stream recorder records no sound.
			  * All recording occurs relative to the initial position within the stream.
			  */
			StreamRecorder( SoundOutputStream* newStream );
			
			
			/// Create a copy of the specified stream recorder and its state.
			StreamRecorder( const StreamRecorder& other );
			
			
		//********************************************************************************
		//******	Destructor
			
			
			/// Destroy a sound stream recorder and release all resources associated with it.
			~StreamRecorder();
			
			
		//********************************************************************************
		//******	Assignment Operator
			
			
			/// Assign the contents of another stream recorder to this one.
			StreamRecorder& operator = ( const StreamRecorder& other );
			
			
		//********************************************************************************
		//******	Stream Accessor Methods
			
			
			/// Return a const pointer to the SoundOutputStream that is being written to.
			/**
			  * If there is no sound output stream set or if the stream is not valid, a NULL
			  * pointer is returned, indicating the problem.
			  */
			const SoundOutputStream* getStream() const;
			
			
			/// Set the SoundOutputStream which this recorder should use as a sound destination.
			/**
			  * If the supplied pointer is NULL, the sound recorder is deactivated and doesn't
			  * record any more audio. Otherwise, the recorder resets its current recording
			  * position and starts recording to the current position in the stream.
			  * Thus, all recording occurs relative to the initial position
			  * within the stream.
			  */
			void setStream( SoundOutputStream* newStream );
			
			
		//********************************************************************************
		//******	Recording Accessor Methods
			
			
			/// Return whether or not this sound recorder is current recording audio.
			Bool isRecording() const;
			
			
			/// Set whether or not this sound recorder should be recording its input sound.
			/**
			  * The method returns whether or not recording will occurr, based on the type 
			  * of SoundOutputSream which this player has and the requested playback
			  * state.
			  */
			Bool setIsRecording( Bool newIsRecording );
			
			
			/// Tell the sound recorder to start recording sound from the current position.
			/**
			  * The method returns whether or not recording will occurr, based on the type 
			  * of SoundInputStream that this player has.
			  */
			Bool record();
			
			
			/// Stop recording sound and keep the record head at the last position.
			void stop();
			
			
			/// Reset the recording position to the first position within the stream.
			/**
			  * The method returns whether or not the rewind operation was successul.
			  * For SoundOutputStream objects that don't allow seeking, this method
			  * will always fail. This method does not affect the recording state of the
			  * recorder, thus rewinding will cause the recording to jump to the beginning
			  * of the stream if the recorder is currently recording.
			  */
			Bool rewind();
			
			
		//********************************************************************************
		//******	Filter Attribute Accessor Methods
			
			
			/// Return a human-readable name for this stream recorder.
			/**
			  * The method returns the string "Stream Recorder".
			  */
			virtual UTF8String getName() const;
			
			
			/// Return the manufacturer name of this stream recorder.
			/**
			  * The method returns the string "Om Sound".
			  */
			virtual UTF8String getManufacturer() const;
			
			
			/// Return an object representing the version of this stream recorder.
			virtual FilterVersion getVersion() const;
			
			
			/// Return an object that describes the category of effect that this filter implements.
			/**
			  * This method returns the value FilterCategory::RECORDING.
			  */
			virtual FilterCategory getCategory() const;
			
			
			/// Return whether or not this stream recorder can process audio data in-place.
			/**
			  * This method always returns TRUE, stream recorders can process audio data in-place.
			  */
			virtual Bool allowsInPlaceProcessing() const;
			
			
		//********************************************************************************
		//******	Public Static Property Objects
			
			
			/// A string indicating the human-readable name of this stream recorder.
			static const UTF8String NAME;
			
			
			/// A string indicating the manufacturer name of this stream recorder.
			static const UTF8String MANUFACTURER;
			
			
			/// An object indicating the version of this stream recorder.
			static const FilterVersion VERSION;
			
			
	private:
		
		//********************************************************************************
		//******	Private Filter Processing Methods
			
			
			/// Record the specified number of samples from the input frame to the sound output stream.
			virtual SoundResult processFrame( const SoundFrame& inputFrame,
													SoundFrame& outputFrame, Size numSamples );
			
			
		//********************************************************************************
		//******	Private Data Members
			
			
			/// A pointer to the sound output stream to which this recorder is recording.
			SoundOutputStream* stream;
			
			
			/// The current position within the stream, relative to the initial position within the stream.
			SampleIndex currentStreamPosition;
			
			
			/// The current maximum position that has been reached in the stream.
			/**
			  * This value allows the recorder to determine the total size of the stream
			  * indirectly by noting the positions within the sound stream where recording
			  * started and ended. The difference is the total length of the sound and it
			  * is used when rewinding in the stream.
			  */
			SoundSize currentStreamLength;
			
			
			/// A boolean value indicating whether or not the stream recorder should be recording input audio..
			Bool recordingEnabled;
			
			
			/// A boolean value indicating whether or not the sound stream supports seeking.
			Bool seekingAllowed;
			
			
			
};




//##########################################################################################
//*************************  End Om Sound Filters Namespace  *******************************
OM_SOUND_FILTERS_NAMESPACE_END
//******************************************************************************************
//##########################################################################################


#endif // INCLUDE_OM_SOUND_STREAM_RECORDER_H