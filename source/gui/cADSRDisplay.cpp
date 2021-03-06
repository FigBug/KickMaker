/*
 *  cADSRDisplay.cpp
 *  KickMaker
 *
 *  Created by Nik Reiman on 16.02.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __cADSRDisplay_H
#include "cADSRDisplay.h"
#endif

cADSRDisplay::cADSRDisplay(const CRect &size, IControlListener *listener, long tag, CBitmap *pBackground) :
CControl(size, listener, tag, pBackground) {
  m_attack_x = m_attack_y = 0;
  m_decay_x = m_decay_y = 0;
  m_sustain_x = m_sustain_y = 0;
  m_release_x = m_release_y = 0;
  m_attack_amp = m_decay_amp = m_sustain_amp = 0.0;
  setValue(0);
}

cADSRDisplay::~cADSRDisplay() {
}

void cADSRDisplay::draw(CDrawContext *pContext) {
  CColor lcolor (200, 200, 200, 255);
  pContext->setFrameColor(lcolor);
  pContext->setLineWidth(1);
  pContext->setDrawMode(kAntiAliasing);
  
  
  pContext->drawLine(CPoint(size.left, size.bottom), CPoint(m_attack_x, m_attack_y));
  pContext->drawLine(CPoint(m_attack_x, m_attack_y), CPoint(m_decay_x, m_decay_y));
  pContext->drawLine(CPoint(m_decay_x, m_decay_y), CPoint(m_sustain_x, m_sustain_y));
  pContext->drawLine(CPoint(m_sustain_x, m_sustain_y), CPoint(m_release_x, m_release_y));
  
  CColor heightcol (255, (int)((m_attack_amp - 1.0) * -255), 0, 255);
  pContext->setFillColor(heightcol);
  CDrawContext::PointList pointarr;
  pointarr.push_back(CPoint(m_attack_x - 2, m_attack_y - 2));
  pointarr.push_back(CPoint(m_attack_x + 2, m_attack_y - 2));
  pointarr.push_back(CPoint(m_attack_x + 2, m_attack_y + 2));
  pointarr.push_back(CPoint(m_attack_x - 2, m_attack_y + 2));
  pContext->drawPolygon(pointarr, kDrawFilled);
  pointarr.clear();
  
  heightcol(255, (int)((m_decay_amp - 1.0) * -255), 0, 255);
  pContext->setFillColor(heightcol);
  pointarr.push_back(CPoint(m_decay_x - 2, m_decay_y - 2));
  pointarr.push_back(CPoint(m_decay_x + 2, m_decay_y - 2));
  pointarr.push_back(CPoint(m_decay_x + 2, m_decay_y + 2));
  pointarr.push_back(CPoint(m_decay_x - 2, m_decay_y + 2));
  pContext->drawPolygon(pointarr, kDrawFilled);
  pointarr.clear();
    
  heightcol(255, (unsigned char)((m_sustain_amp - 1.0) * -255), 0, 255);
  pContext->setFillColor(heightcol);
  pointarr.push_back(CPoint(m_sustain_x - 2, m_sustain_y - 2));
  pointarr.push_back(CPoint(m_sustain_x + 2, m_sustain_y - 2));
  pointarr.push_back(CPoint(m_sustain_x + 2, m_sustain_y + 2));
  pointarr.push_back(CPoint(m_sustain_x - 2, m_sustain_y + 2));
  pContext->drawPolygon(pointarr, kDrawFilled);
  pointarr.clear();
    
  setDirty(false);
}

int cADSRDisplay::distance(int x1, int y1, int x2, int y2) const {
  int a = (int)sqrt((float)(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)))); 
  return a;
}

void cADSRDisplay::mouse(CDrawContext *pContext, CPoint &where, long buttons) {
  mouse(pContext, where, buttons);

  if(distance(where.x, where.y, m_attack_x, m_attack_y) < DEF_MOUSE_TOLERANCE) {
    setValue(1);
  }
  else if(distance(where.x, where.y, m_decay_x, m_decay_y) < DEF_MOUSE_TOLERANCE) {
    setValue(2);
  }
  else if(distance(where.x, where.y, m_sustain_x, m_sustain_y) < DEF_MOUSE_TOLERANCE) {
    setValue(3);
  }
  else {
    setValue(0);
  }
  
  long button = 0;
  beginEdit();
	do {
        // todo: rmr
		//button = pContext->getMouseButtons();
		//getMouseLocation(pContext, where);
    // Force a redraw right away
		//doIdleStuff(); // todo: rmr
    listener->valueChanged(this);
	} while(button & kLButton);
  endEdit();
}

void cADSRDisplay::setAttackCoords(float amount, float amp) {
  m_attack_x = (int)((amount / (float)MAX_ATTACK) * ((float)(size.right - size.left) / 4.0))
    + size.left;
  m_attack_y = size.bottom - (int)(amp * (float)(size.bottom - size.top));
  m_attack_amp = amp;
  setDirty();
}

void cADSRDisplay::setDecayCoords(float amount, float amp) {
  m_decay_x = (int)((amount / (float)MAX_DECAY) * ((float)(size.right - size.left) / 4.0))
    + m_attack_x;
  m_decay_y = size.bottom - (int)(amp * (float)(size.bottom - size.top));
  m_decay_amp = amp;
  setDirty();
}

void cADSRDisplay::setSustainCoords(float amount, float amp) {
  m_sustain_x = (int)((amount / (float)MAX_SUSTAIN) * ((float)(size.right - size.left) / 4.0))
    + m_decay_x;
  m_sustain_y = size.bottom - (int)(amp * (float)(size.bottom - size.top));
  m_sustain_amp = amp;
  setDirty();
}

void cADSRDisplay::setReleaseCoords(float amount, float amp) {
  m_release_x = (int)((amount / (float)MAX_RELEASE) * ((float)(size.right - size.left) / 4.0))
    + m_sustain_x;
  m_release_y = size.bottom;
  setDirty();
}
