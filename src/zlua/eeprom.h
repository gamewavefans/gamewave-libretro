#pragma once

#include "libretro-common/include/libretro.h"

extern "C"
{
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
}

#include "global.h"

#include "zlua/rm.h"

/*
eeprom
    bool SaveGameToNewSlot(int i, int j, str s, str s2, userData u)
    str, str, bool GetSaveNameByID(int i,)
    lightUserData, bool LoadSaveByID(int i)
    UnloadData(userData u)
    bool SaveGameToExistingSlot(int i, userData u)
    int, bool EnumerateGameSavesByID(int i)
        returns number_of_slots, 0
    int, bool EnumerateGameSavesByName(str s)
        returns number_of_slots, 0
    Format()
    CorruptFlash()
    int CheckFlashIntegrity()
*/
namespace zlua::EEPROM
{
    extern "C"
    {
        int zlua_eeprom_loadlibrary(lua_State *L);
        // int zlua_eeprom_save_game_to_new_slot(lua_State *L);
        // int zlua_eeprom_get_save_name_by_id(lua_State *L);
        // int zlua_eeprom_load_save_by_id(lua_State *L);
        // int zlua_eeprom_unload_data(lua_State *L);
        // int zlua_eeprom_save_game_to_existing_slot(lua_State *L);
        // int zlua_eeprom_enumerate_game_saves_by_id(lua_State *L);
        int zlua_eeprom_enumerate_game_saves_by_name(lua_State *L);
        // int zlua_eeprom_format(lua_State *L);
        // int zlua_eeprom_corrupt_flash(lua_State *L);
        // int zlua_eeprom_check_flash_integrity(lua_State *L);
    }
}
