/*
 *  fxSelectWave.h
 *  KickMaker
 *
 *  Created by Nik Reiman on 05.07.07.
 *  Copyright 2007 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxSelectWave_H
#define __fxSelectWave_H

#include <string>

#ifndef __fxSinewave_H
#include "fxSinewave.h"
#endif

#ifndef __fxSquarewave_H
#include "fxSquarewave.h"
#endif

#ifndef __fxSawtooth_H
#include "fxSawtooth.h"
#endif

#ifndef __fxTriangle_H
#include "fxTriangle.h"
#endif

using namespace std;

enum {
  // Common parameters from subwaves (unused here)
  fxSelectWave_PRM_FREQ,
  fxSelectWave_PRM_PHASE,
  fxSelectWave_PRM_SAMPLE_RATE,
  fxSelectWave_NUM_PARAMS
};

enum {
  WAV_SINE = 0,
  WAV_SQUARE,
  WAV_SAWTOOTH,
  WAV_TRIANGLE,
  WAV_LAST_WAV
};

// Used by some display controls
static std::string gDictionaryWaveTables[WAV_LAST_WAV] =
{
  string("SINE"),
  string("SQUARE"),
  string("SAWTOOTH"),
  string("TRIANGLE")
};

class fxSelectWave : public fxSinewave,
public fxSquarewave,
public fxSawtooth,
public fxTriangle
{
public:
  fxSelectWave(pluginCore *p, int num_params = fxSelectWave_NUM_PARAMS);
  ~fxSelectWave();
  
  virtual float getParameter(int index) const;
  
  virtual void linkParameter(int plugin_index, int effect_index);
  virtual void linkParameter(float *target, int effect_index);

  // TODO: virtual void process(float *inputs, int frames);
  virtual void process(float &input);

  virtual void setParameter(int index, float value);

  virtual void setType(int wavetype);
protected:
  int m_wavetype;
};

#endif