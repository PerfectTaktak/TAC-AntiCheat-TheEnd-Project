public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart)
{
	if(CENTER_CONTROLE[9][CONTROL_STATE] == 1)
	{
		if((damagedid != 0xFFFF && playerid != 0xFFFF) && !(3 <= bodypart <= 9))
		{
			SAMP_AC_SEND_WARNING_FOR_SCRIPT(playerid, "Damage Helper", 9, 0);
		}
	}
#if defined SAC_OnPlayerGiveDamage
    return SAC_OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart);
#else
	return 0;
#endif
}
#if defined _ALS_OnPlayerGiveDamage
    #undef    OnPlayerGiveDamage
#else
    #define    _ALS_OnPlayerGiveDamage
#endif
#define    OnPlayerGiveDamage    SAC_OnPlayerGiveDamage
#if defined SAC_OnPlayerGiveDamage
forward SAC_OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart);
#endif