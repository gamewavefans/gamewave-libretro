#include "zlua/eeprom.h"

namespace zlua::EEPROM
{

    static const luaL_reg zlua_eeprom_lib[] = {
        // {"SaveGameToNewSlot", zlua_eeprom_save_game_to_new_slot},
        // {"GetSaveNameByID", zlua_eeprom_get_save_name_by_id},
        // {"LoadSaveByID", zlua_eeprom_load_save_by_id},
        // {"UnloadData", zlua_eeprom_unload_data},
        // {"SaveGameToExistingSlot", zlua_eeprom_save_game_to_existing_slot},
        // {"EnumerateGameSavesByID", zlua_eeprom_enumerate_game_saves_by_id},
        {"EnumerateGameSavesByName", zlua_eeprom_enumerate_game_saves_by_name},
        // {"Format", zlua_eeprom_format},
        // {"CorruptFlash", zlua_eeprom_corrupt_flash},
        // {"CheckFlashIntegrity", zlua_eeprom_check_flash_integrity},
        {nullptr, nullptr}};

    int zlua_eeprom_loadlibrary(lua_State *L)
    {
        luaL_openlib(L, "eeprom", zlua_eeprom_lib, 0);
        return 1;
    }

    int zlua_eeprom_enumerate_game_saves_by_name(lua_State *L)
    {
        const char *name = luaL_checkstring(L, 1);
        int ret = 0;
        bool retBool = false;
        log_cb(RETRO_LOG_DEBUG, "\tcalled eeprom.EnumerateGameSavesByName(\"%s\") -> %d, %d - UNIMPLEMENTED\n", name, ret, retBool);
        lua_pushnumber(L, (lua_Number)ret);
        lua_pushboolean(L, retBool);
        return 2;
    }
}
