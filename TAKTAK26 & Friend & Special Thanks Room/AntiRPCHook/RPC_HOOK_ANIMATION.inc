ORPC:RPC_APPLY_ANIMATION(playerid, BitStream:bs)
{
	if(playerid == -1) return true;
	if(DAMAGE_INFO[playerid][DAMAGE_IMPACT] != 0xFFFF) return 0;
    return true;
}

