ORPC:RPC_SET_HEALTH(playerid, BitStream:bs)
{
	if(playerid == -1) return true;
	if(DAMAGE_INFO[playerid][DAMAGE_IMPACT] != 0xFFFF) return 0;
	new Float: SAMP_AC_HEALTH;
    BS_ReadFloat(bs, SAMP_AC_HEALTH);
    
	DAMAGE_INFO[playerid][DAMAGE_HEALTH] = SAMP_AC_HEALTH;
	DAMAGE_INFO[playerid][DAMAGE_FIX_HP] = 5;
    return true;
}