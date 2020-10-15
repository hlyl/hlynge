//################################################################################################################################################################
//####  Made by hlynge - August 2019
//################################################################################################################################################################

class BountyState
{
	bool m_player_valid_for_currentHunt;
	
    float m_progress;

    string m_timeleft;

    string m_playername;

    string m_lastseen;

    string m_weaponinhands;

    float m_currhealth;

    float m_currblood;


	
	ref array<vector> m_lastpos = new ref array<vector> ();
	
	ref array<ref BountyStats> m_stats;

}