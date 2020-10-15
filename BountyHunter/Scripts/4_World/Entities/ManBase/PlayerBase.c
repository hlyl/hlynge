//################################################################################################################################################################
//####  Made by hlynge - August 2019
//################################################################################################################################################################


modded class PlayerBase
{
	protected string PlayerUID;
	
	bool m_bounty_player_active = true;
	
	bool m_bounty_player_active_for_current = false;
	
    void PlayerBase()
    {
    }
	override void OnPlayerLoaded()
	{
	    super.OnPlayerLoaded();
	    if (this.GetIdentity())
	        PlayerUID = this.GetIdentity().GetPlainId();
	}
	
    string GetPlayerUID()
    {
        return PlayerUID;
    }
	
    override void EEKilled( Object killer )
    {
			GetBountyBase().PlayerKilled(killer , this);
			
            super.EEKilled(killer);
    }
	
	override void OnConnect()
	{
		super.OnConnect();
		
		if(GetGame().IsServer())
		{
			PlayerUID = this.GetIdentity().GetPlainId();
			
			if(!GetBountyBase().BountyIsAlive())
				m_bounty_player_active_for_current = false;
			
			if(BountyLogger.m_debug) BountyLogger.LogMessage("OnConnect() Player connected check if he is admin Uid : " + PlayerUID);
			GetBountyBase().IsAdmin(this);
		}
		
		
	}
	
}