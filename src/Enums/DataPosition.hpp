#pragma once

namespace ooh {

// Will determine where to write to or read from a file 
enum DataPosition
{
  DATPOS_BLOOD = 0,
  DATPOS_WAVE = 1,
  DATPOS_WEAPON_LVL = 2,
  DATPOS_ARMOR_LVL = 3,
  DATPOS_POTION_LVL = 4
};

}
