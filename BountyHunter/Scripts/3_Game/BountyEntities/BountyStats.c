//################################################################################################################################################################
//####  Made by hlynge - August 2019
//################################################################################################################################################################

class BountyStats
{
	string m_Identity;
	string m_name;
	bool m_isonline;
	int m_points;
	int m_bountyKills;
	int m_bountySurvived;
	int m_bountyDeaths;
	int m_placemeant;
	
	static  ref array<ref BountyStats> LoadStats()
	{
		ref array<ref BountyStats> stats = new ref array<ref BountyStats>();
		
		if ( !FileExist( BOUNTY_JSON_PATH_DIRECTORY_SETTINGS ) )
		{
			MakeDirectory( BOUNTY_JSON_PATH_DIRECTORY_SETTINGS );
		}
		
		if ( !FileExist( BOUNTY_JSON_PATH_BOUNTYSTATS ) )
		{
			JsonFileLoader<ref array<ref BountyStats>>.JsonSaveFile(BOUNTY_JSON_PATH_BOUNTYSTATS, stats );
		}
		
		JsonFileLoader<ref array<ref BountyStats>>.JsonLoadFile(BOUNTY_JSON_PATH_BOUNTYSTATS, stats );
		return stats;
	}
	
	static ref array<ref BountyStats> SortStats(ref array<ref BountyStats> m_stats)
	{
	
        int n = m_stats.Count(); 
        for (int i = 1; i < n; ++i) { 
				 ref BountyStats keystats =  m_stats.Get(i);
            int key = keystats.m_points; 
            int j = i - 1; 
  
           ref BountyStats compstats =  m_stats.Get(j);
			   int compkey = compstats.m_points;
			
            while (j >= 0 && compkey < key) { 
						m_stats.SwapItems(j + 1 ,j);
                j = j - 1; 
				
				 		compstats =  m_stats.Get(j);
						if(compstats)
			    			compkey = compstats.m_points;
            } 
            m_stats.Set(  j +1, keystats); 
        } 
    	
	
		return m_stats;
	}
	
	static ref  array<ref BountyStats> GetTop50(ref array<ref BountyStats> m_stats)
	{
		ref array<ref BountyStats> rstats = new ref array<ref BountyStats>();
		
		autoptr array<Man> players = new array<Man>;
		GetGame().GetPlayers( players );
		
		
		for(int i =0; i < 49 && i < m_stats.Count() ; i++)
		{
			BountyStats state = m_stats.Get(i);
			state.m_isonline = false;
			
			for(int p =0; p < players.Count() ; p++)
			{
				PlayerIdentity ident =  players.Get(p).GetIdentity();
				if(state.m_Identity ==  ident.GetPlainId())
					state.m_isonline = true;
			}
			
			rstats.Insert(state);
		}
		return rstats;
	}
	
	static void SaveStats(ref array<ref BountyStats> m_stats)
	{
			JsonFileLoader<ref array<ref BountyStats>>.JsonSaveFile(BOUNTY_JSON_PATH_BOUNTYSTATS + ".BAK", m_stats );
			JsonFileLoader<ref array<ref BountyStats>>.JsonSaveFile(BOUNTY_JSON_PATH_BOUNTYSTATS, m_stats );
	}
	
}

enum BountyStatsEvent
{
	Death,
	Kill,
	Leave,
	Survive
}

