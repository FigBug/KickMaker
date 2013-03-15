/*
  ==============================================================================

    BufferProcessor.h
    Created: 15 Mar 2013 7:51:14pm
    Author:  nik

  ==============================================================================
*/

#ifndef __BUFFERPROCESSOR_H_8B7D07F4__
#define __BUFFERPROCESSOR_H_8B7D07F4__

class BufferProcessor {
public:
    BufferProcessor() {}
    virtual ~BufferProcessor() {}

    virtual void process(float *buffer, int numSamples) = 0;
};

#endif  // __BUFFERPROCESSOR_H_8B7D07F4__
