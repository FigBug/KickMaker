/*
 *  cKeyedOptionMenu.h
 *  KickMaker
 *
 *  Created by Nik Reiman on 30.03.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __cKeyedOptionMenu_H
#define __cKeyedOptionMenu_H

#include "vstgui.h"

#include <vector>

#define MAX_KEY_LENGTH 24

class cKeyedOptionMenu : public COptionMenu {
public:
  cKeyedOptionMenu(const CRect &size, IControlListener *listener, long tag);
  ~cKeyedOptionMenu();

  int addKey(const char *name, long value = 0);
  long getCurrentKey() const;
  long getKey(long key) const;
  void setKeyValue(long key, long value);
protected:
    struct _tKey {
      char key[MAX_KEY_LENGTH];
      long value;
    };
  
  std::vector<struct _tKey> m_keys;
  int m_num_keys;
private:
};

#endif
