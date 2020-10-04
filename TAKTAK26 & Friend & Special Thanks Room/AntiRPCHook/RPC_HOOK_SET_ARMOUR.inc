ORPC:RPC_SET_ARMOUR(playerid, BitStream:bs)
{
	if(playerid == -1) return true;
	if(DAMAGE_INFO[playerid][DAMAGE_IMPACT] != 0xFFFF) return 0;
	new Float: SAMP_AC_ARMOUR;
    BS_ReadFloat(bs, SAMP_AC_ARMOUR);
    
    DAMAGE_INFO[playerid][DAMAGE_ARMOUR] = SAMP_AC_ARMOUR;
    return true;
}