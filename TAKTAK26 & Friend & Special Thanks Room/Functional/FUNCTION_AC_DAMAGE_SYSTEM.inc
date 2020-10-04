stock SAMP_AC_START_UPDATE_DAMAGE(playerid, weaponid)
{
	new
		SAMP_AC_HEALTH, SAMP_AC_ARMOUR, SAMP_AC_DAMAGE;
		
	SAMP_AC_ARMOUR = floatround(DAMAGE_INFO[playerid][DAMAGE_ARMOUR], floatround_tozero);
	SAMP_AC_HEALTH = floatround(DAMAGE_INFO[playerid][DAMAGE_HEALTH], floatround_tozero);
	SAMP_AC_TOP_DAMAGE_WEAPON_SHOT(weaponid, SAMP_AC_DAMAGE);

	if(SAMP_AC_ARMOUR <= 0)
	{
		SAMP_AC_HEALTH = SAMP_AC_HEALTH - SAMP_AC_DAMAGE;
		if(SAMP_AC_HEALTH <= 2) 
		{
			SAMP_AC_HEALTH = 2;
			DAMAGE_INFO[playerid][DAMAGE_IMPACT] = 1;
		}
		DAMAGE_INFO[playerid][DAMAGE_HEALTH] = SAMP_AC_HEALTH;
		SetPlayerHealth(playerid, SAMP_AC_HEALTH);
	}
	if(SAMP_AC_ARMOUR > 0)
	{
		if(SAMP_AC_ARMOUR - SAMP_AC_DAMAGE > 0)
		{
			DAMAGE_INFO[playerid][DAMAGE_ARMOUR] -= float(SAMP_AC_DAMAGE);
			SetPlayerArmour(playerid, DAMAGE_INFO[playerid][DAMAGE_ARMOUR]);
		}
		else if(SAMP_AC_ARMOUR - SAMP_AC_DAMAGE <= 0)
		{
			SAMP_AC_DAMAGE = SAMP_AC_DAMAGE -= SAMP_AC_ARMOUR;
			SAMP_AC_HEALTH -= SAMP_AC_DAMAGE;
			if(SAMP_AC_HEALTH < 0) 
			{
				SAMP_AC_HEALTH = 2;
				DAMAGE_INFO[playerid][DAMAGE_IMPACT] = 1;
			}
			DAMAGE_INFO[playerid][DAMAGE_HEALTH] = SAMP_AC_HEALTH;
			DAMAGE_INFO[playerid][DAMAGE_ARMOUR] = 0;
			
			SetPlayerHealth(playerid, SAMP_AC_HEALTH);
			SetPlayerArmour(playerid, 0.0);
		}
	}
	if(DAMAGE_INFO[playerid][DAMAGE_IMPACT] == 1)
	{
		if(SERVER_INFO[playerid][SAMP_ID_VEHICLE] > 0)
		{
			switch(GetVehicleModel(SERVER_INFO[playerid][SAMP_ID_VEHICLE]))
			{
				case 509, 481, 510, 462, 448, 581, 522, 461, 521, 523, 463, 586, 468, 471:
				{
					new Float: speed_x, Float: speed_y, Float: speed_z;
					TogglePlayerControllable(playerid, false);
					GetVehicleVelocity(SERVER_INFO[playerid][SAMP_ID_VEHICLE], speed_x, speed_y, speed_z);

					if(speed_x * speed_x + speed_y * speed_y + speed_z * speed_z >= 0.4)
					{
						SAMP_AC_DEATH_ANIMATION(playerid, "PED", "BIKE_fallR", 0);
						SAMP_AC_DEATH_ANIMATION(playerid, "PED", "BIKE_fallR", 0);
					}
					else
					{
						SAMP_AC_DEATH_ANIMATION(playerid, "PED", "BIKE_fall_off", 0);
						SAMP_AC_DEATH_ANIMATION(playerid, "PED", "BIKE_fall_off", 0);
					}
				}
				default:
				{
					if(GetPlayerVehicleSeat(playerid) & 1)
					{
						SAMP_AC_DEATH_ANIMATION(playerid, "PED", "CAR_dead_LHS");
						SAMP_AC_DEATH_ANIMATION(playerid, "PED", "CAR_dead_LHS");
					}
					else
					{
						SAMP_AC_DEATH_ANIMATION(playerid, "PED", "CAR_dead_RHS");
						SAMP_AC_DEATH_ANIMATION(playerid, "PED", "CAR_dead_RHS");
					}
				}
			}
		}
		DAMAGE_INFO[playerid][DAMAGE_IMPACT] = 2;
	}
	return true;
}
stock SAMP_AC_CHECK_PLAYER_HEALTH(playerid, &SAMP_AC_SERVER_HEALTH)
{
	if(SAMP_AC_SERVER_HEALTH > floatround(DAMAGE_INFO[playerid][DAMAGE_HEALTH], floatround_tozero))
	{
		if(DAMAGE_INFO[playerid][DAMAGE_FIX_HP] <= 0) SetPlayerHealth(playerid, DAMAGE_INFO[playerid][DAMAGE_HEALTH]);
	}
	else
	{
		if(DAMAGE_INFO[playerid][DAMAGE_FIX_HP] <= 0) DAMAGE_INFO[playerid][DAMAGE_HEALTH] = float(SAMP_AC_SERVER_HEALTH);
	}


	SAMP_AC_SERVER_HEALTH = floatround(DAMAGE_INFO[playerid][DAMAGE_HEALTH], floatround_tozero);

	if(DAMAGE_INFO[playerid][DAMAGE_IMPACT] == 2 && DAMAGE_INFO[playerid][DAMAGE_TIMER] != 1)
	{
		ClearAnimations(playerid);
		DAMAGE_INFO[playerid][DAMAGE_TIMER] = 1;
		DAMAGE_INFO[playerid][DAMAGE_IMPACT] = 0xFFFF;
		TogglePlayerControllable(playerid, true);
		SetPlayerHealth(playerid, 1.0);
		ApplyAnimation(playerid,"CRACK", "crckdeth2", 4.0, 0, 0, 0, 0, 0, 1);
		SetTimerEx("SAMP_AC_END_ANIMATION_DEATH", 1500, false, "i", playerid);
	}
	return 1;
}
stock SAMP_AC_TOP_DAMAGE_WEAPON_SHOT(weaponid, &SAMP_AC_DAMAGE)
{
	if(!(0 <= weaponid >= 46))
	{
		switch(weaponid)
		{
			case 0..15:		SAMP_AC_DAMAGE = 3; 
			case 16..18:	SAMP_AC_DAMAGE = 0;
			case 19..22:	SAMP_AC_DAMAGE = 10;
			case 23:		SAMP_AC_DAMAGE = 14;
			case 24:		SAMP_AC_DAMAGE = 45;
			case 25:		SAMP_AC_DAMAGE = 12;
			case 26..27: 	SAMP_AC_DAMAGE = 20;
			case 28:		SAMP_AC_DAMAGE = 5;
			case 29:		SAMP_AC_DAMAGE = 8;
			case 30..31:	SAMP_AC_DAMAGE = 10;
			case 32:		SAMP_AC_DAMAGE = 8;
			case 33..34:	SAMP_AC_DAMAGE = 50;
			case 35:		SAMP_AC_DAMAGE = 0;
			case 36:		SAMP_AC_DAMAGE = 0;
			case 37:		SAMP_AC_DAMAGE = 10;
			case 38:		SAMP_AC_DAMAGE = 5;
			case 39..40:	SAMP_AC_DAMAGE = 0;
			case 41..42:	SAMP_AC_DAMAGE = 2;
			case 43..45:	SAMP_AC_DAMAGE = 0;
			case 46:		SAMP_AC_DAMAGE = 3;
			default:    	SAMP_AC_DAMAGE = -1;
		}
	
	}
	return 1;
}
stock SAMP_AC_TOP_TIME_WEAPON_SHOT(weaponid, &SAMP_AC_TICKCOUNT)
{
	if(!(0 <= weaponid >= 48))
	{
		switch(weaponid)
		{
			case 0..8, 10..15: 		SAMP_AC_TICKCOUNT = 250;
			case 9: 				SAMP_AC_TICKCOUNT = 30;
			case 16..18:			SAMP_AC_TICKCOUNT = 0;
			case 19..20:			SAMP_AC_TICKCOUNT = 20;
			case 21:				SAMP_AC_TICKCOUNT = 0;
			case 22:				SAMP_AC_TICKCOUNT = 100;
			case 23:				SAMP_AC_TICKCOUNT = 100;
			case 24:				SAMP_AC_TICKCOUNT = 400;
			case 25:				SAMP_AC_TICKCOUNT = 600;
			case 26..27:			SAMP_AC_TICKCOUNT = 70;
			case 28..32:			SAMP_AC_TICKCOUNT = 60;
			case 33..34:			SAMP_AC_TICKCOUNT = 500;
			case 35..37:			SAMP_AC_TICKCOUNT = 0;
			case 38:				SAMP_AC_TICKCOUNT = 20;
			case 39..40:			SAMP_AC_TICKCOUNT = 0;
			case 41..42:			SAMP_AC_TICKCOUNT = 10;
			case 43..47:			SAMP_AC_TICKCOUNT = 0;
			case 48:				SAMP_AC_TICKCOUNT = 400;
			default:				SAMP_AC_TICKCOUNT = -1;
		}
	}
	return 1;
}
stock SAMP_AC_TOP_DISTANCE_SHOT(weaponid, &SAMP_AC_DISTANCE)
{
	if(!(0 <= weaponid >= 46))
	{
		switch(weaponid)
		{
		    case 0..15: 		SAMP_AC_DISTANCE = 1;
		    case 19, 31:  		SAMP_AC_DISTANCE = 70;
			case 20, 38:        SAMP_AC_DISTANCE = 60;
			case 22..24:        SAMP_AC_DISTANCE = 30;
			case 25, 27:        SAMP_AC_DISTANCE = 40;
			case 26, 28:        SAMP_AC_DISTANCE = 30;
			case 29, 32:     	SAMP_AC_DISTANCE = 30;
			case 30:            SAMP_AC_DISTANCE = 70;
			case 33:            SAMP_AC_DISTANCE = 90;
			case 34:            SAMP_AC_DISTANCE = 300;
			default: 			SAMP_AC_DISTANCE = 0;
		}
	}
	return 1;
}
stock SAMP_AC_DEATH_ANIMATION(playerid, animlib[32], animname[32], anim_lock = 0, anim_freeze = 1)
{
	if(animlib[0] && animname[0])
	{
		ApplyAnimation(playerid, animlib, animname, 4.1, 0, anim_lock, anim_lock, anim_freeze, 0, 1);
	}
}
forward SAMP_AC_END_ANIMATION_DEATH(playerid);
public SAMP_AC_END_ANIMATION_DEATH(playerid)
{
	if(DAMAGE_INFO[playerid][DAMAGE_KILLER] == 0xFFFF && DAMAGE_INFO[playerid][DAMAGE_REASON] == 0xFFFF) return 1;
	CallRemoteFunction("SAMP_AC_PLAYER_DEATH","iid", playerid, DAMAGE_INFO[playerid][DAMAGE_KILLER], DAMAGE_INFO[playerid][DAMAGE_REASON]);
	return true;
}

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	if(CENTER_CONTROLE[0][CONTROL_DAMAGE] == 1)
	{
		new Float: VALUE_IGNORE, Float: STOP_X, Float: STOP_Y, Float: STOP_Z;
		GetPlayerLastShotVectors(playerid, VALUE_IGNORE, VALUE_IGNORE, VALUE_IGNORE, STOP_X, STOP_Y, STOP_Z);

		new SAMP_AC_TICK_SHOT;
		new Float: FIRST_DISTANCE;
		SAMP_AC_TOP_TIME_WEAPON_SHOT(weaponid, SAMP_AC_TICK_SHOT);
		
		new SAMP_AC_WEAPON_USE_SLOT = SAMP_AC_WEAPON_SLOT[weaponid];
		if(SERVER_INFO[playerid][SAMP_AMMOUT][SAMP_AC_WEAPON_USE_SLOT] > 0)
		{
			SERVER_INFO[playerid][SAMP_AMMOUT][SAMP_AC_WEAPON_USE_SLOT] --;

			SERVER_INFO[playerid][SAMP_TIC_WEAPON] = SERVER_INFO[playerid][SAMP_TICK];
		}
		if(hittype == BULLET_HIT_TYPE_PLAYER)
		{
			if(hitid != 65535)
			{
				#include																	SAMP_AC/MODULE/ANTICRASHER/BULLET
				#include																	SAMP_AC/MODULE/ANTICRASHER/ECLIPSE
				if(SERVER_INFO[playerid][SAMP_TICK] - SERVER_INFO[playerid][SAMP_USE_REPORT]  < SAMP_AC_TICK_SHOT) return 0;
				
				switch(weaponid)
				{
					case 0..15: 		FIRST_DISTANCE = 1.0;
					case 19, 31:  		FIRST_DISTANCE = 70.0;
					case 20, 38:        FIRST_DISTANCE = 60.0;
					case 22..24:        FIRST_DISTANCE = 30.0;
					case 25, 27:        FIRST_DISTANCE = 40.0;
					case 26, 28:        FIRST_DISTANCE = 30.0;
					case 29, 32:     	FIRST_DISTANCE = 30.0;
					case 30:            FIRST_DISTANCE = 70.0;
					case 33:            FIRST_DISTANCE = 90.0;
					case 34:            FIRST_DISTANCE = 300.0;
					default: 			FIRST_DISTANCE = 0.0;
				}
				
				if(IsPlayerInRangeOfPoint(playerid, FIRST_DISTANCE, STOP_X, STOP_Y, STOP_Z) == 0) return 0;
				if(DAMAGE_INFO[playerid][DAMAGE_IMPACT] != 0xFFFF) return 0;

				switch(weaponid)
				{
					case 22..34, 38:
					{
						SAMP_AC_START_UPDATE_DAMAGE(hitid, weaponid);
						DAMAGE_INFO[hitid][DAMAGE_KILLER] = playerid;
						DAMAGE_INFO[hitid][DAMAGE_REASON] = weaponid;
					}
					default: return true;
				}
				SERVER_INFO[playerid][SAMP_USE_REPORT] = SERVER_INFO[playerid][SAMP_TICK];
				if(SERVER_INFO[hitid][SAMP_ID_VEHICLE] > 0) return 0;
			}
		}
	}
#if defined SAMP_AC_OnPlayerWeaponShot
    return SAMP_AC_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);
#else
	return true;
#endif
}
#if defined _ALS_OnPlayerWeaponShot
    #undef    OnPlayerWeaponShot
#else
    #define    _ALS_OnPlayerWeaponShot
#endif
#define    OnPlayerWeaponShot    SAMP_AC_OnPlayerWeaponShot
#if defined SAMP_AC_OnPlayerWeaponShot
forward SAMP_AC_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);
#endif


public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart)
{
	if(CENTER_CONTROLE[0][CONTROL_DAMAGE] == 1)
	{
		switch(weaponid)
		{
			case 22..34, 38:
			{
				if(GetPlayerVehicleID(damagedid) > 0)
				{
					SetPlayerTeam(damagedid, NO_TEAM);
				}
				else
				{
					SetPlayerTeam(playerid, 100);
					SetPlayerTeam(damagedid, 100);
				}
			}
			default:
			{
				if(DAMAGE_INFO[playerid][DAMAGE_IMPACT] == 0xFFFF)
				{
					SetPlayerTeam(playerid, NO_TEAM);
					SetPlayerTeam(damagedid, NO_TEAM);
				}
				else
				{
					SetPlayerTeam(playerid, 100);
					SetPlayerTeam(damagedid, 100);
				}
			}
		}
	}
#if defined SAMP_AC_OnPlayerGiveDamage
    return SAMP_AC_OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart);
#else
	return 0;
#endif
}
#if defined _ALS_OnPlayerGiveDamage
    #undef    OnPlayerGiveDamage
#else
    #define    _ALS_OnPlayerGiveDamage
#endif
#define    OnPlayerGiveDamage    SAMP_AC_OnPlayerGiveDamage
#if defined SAMP_AC_OnPlayerGiveDamage
forward SAMP_AC_OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart);
#endif


public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(CENTER_CONTROLE[0][CONTROL_DAMAGE] == 1)
	{
		if(newstate == PLAYER_STATE_DRIVER)
		{
			#include                                                                SAMP_AC/MODULE/ANTICRASHER/HUNTER
			SetPlayerTeam(playerid, NO_TEAM);
		}
		if(newstate == PLAYER_STATE_PASSENGER)
		{
			#include                                                                SAMP_AC/MODULE/ANTICRASHER/PLANE
			SetPlayerTeam(playerid, NO_TEAM);
		}
		if(newstate == PLAYER_STATE_ONFOOT)
		{
			SetPlayerTeam(playerid, 100);
		}
	}
#if defined SAC_OnPlayerStateChange
    return SAC_OnPlayerStateChange(playerid, newstate, oldstate);
#else
	return true;
#endif
}
#if defined _ALS_OnPlayerStateChange
    #undef    OnPlayerStateChange
#else
    #define    _ALS_OnPlayerStateChange
#endif
#define    OnPlayerStateChange    SAC_OnPlayerStateChange
#if defined SAC_OnPlayerStateChange
forward SAC_OnPlayerStateChange(playerid, newstate, oldstate);
#endif