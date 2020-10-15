//################################################################################################################################################################
//####  Made by hlynge - August 2019
//################################################################################################################################################################


modded class MissionServer
{
	void MissionServer()
	{
		GetBountyBase();
	}

    override void PlayerDisconnected(PlayerBase player,PlayerIdentity identity, string uid)
	{
		GetBountyBase().ForceEndDisconnect(player);
        super.PlayerDisconnected(player, identity, uid);
    }
}
