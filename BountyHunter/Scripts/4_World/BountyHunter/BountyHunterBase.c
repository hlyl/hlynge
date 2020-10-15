//################################################################################################################################################################
//####  Made by hlynge - August 2019
//################################################################################################################################################################

class BountyBase extends PluginBase
{
	ref BountySetting m_Settings;
	bool m_BountyHuntActive = true;
	PlayerBase m_BountyPlayer;
	string m_BountyPlayerId;
	BountyLocation nearest;
	float m_nearestdistance = 999999;
	ref array<string> m_adminlist;
	ref BountyState m_BountyState;
	int m_nextruninseconds = 0;
	int m_timeleft = 0;
	int m_showbountypostime = -1;
	ref Timer m_timer;
	ref array<ref BountyStats> m_stats;

	bool m_bountydisconnect = false;
	int m_timetoreconnect;


	void BountyBase()
	{
		LogMessage("is Initializing");

		m_Settings = BountySetting.Load();

		BountyLogger.m_debug = m_Settings.m_debug;

		m_BountyState = new BountyState();

		m_stats = BountyStats.LoadStats();

		RegisterRPCS();

		m_timer = new Timer();
		m_timer.Run(10 ,this  ,  "Ticker", NULL , true );

		UpdateBountyState();
	}

	//does what it looks like
	void RegisterRPCS()
	{
		GetRPCManager().AddRPC( "BountyRpcs", "RpcForceEndHunt", this );
		GetRPCManager().AddRPC( "BountyRpcs", "RpcForceStartHunt", this );
		GetRPCManager().AddRPC( "BountyRpcs", "RpcEndHunt", this );
		GetRPCManager().AddRPC( "BountyRpcs", "RpcStartHunt", this );
		GetRPCManager().AddRPC( "BountyRpcs", "RpcGetBountyState", this );
		GetRPCManager().AddRPC( "BountyRpcs", "RpcGetBountyMap", this );
		GetRPCManager().AddRPC( "BountyRpcs", "RpcSaveSettings", this );
		GetRPCManager().AddRPC( "BountyRpcs", "RpcReloadSettings", this );
		GetRPCManager().AddRPC( "BountyRpcs", "RpcBountyPlayerActive", this );
		GetRPCManager().AddRPC( "BountyRpcs", "RpcBountyGetPlayersActive", this );
		GetRPCManager().AddRPC( "BountyRpcs", "RpcForceStartHuntSelected", this );
		GetRPCManager().AddRPC( "BountyRpcs", "RpcDeleteToken", this );
	}

	void  RpcSaveSettings(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		LogMessage("SaveSettings()  Admincommand");
		ref Param1<ref BountySetting> data;
        if ( !ctx.Read( data ) ) return;
		ref BountySetting settings  = data.param1;

		m_Settings.m_Interval = settings.m_Interval;
		m_Settings.m_ShowBountyPosition = settings.m_ShowBountyPosition;
		m_Settings.m_MinPlayers = settings.m_MinPlayers;
		m_Settings.m_MaxBountyHuntTime = settings.m_MaxBountyHuntTime;
		m_Settings.m_RewardBountyPlayerAlive = settings.m_RewardBountyPlayerAlive;
		m_Settings.m_SpawnBountyPlayerAsZombie = settings.m_SpawnBountyPlayerAsZombie;
		m_Settings.m_rewardContainer = settings.m_rewardContainer;
		m_Settings.m_HideBountyPossitionLessThan = settings.m_HideBountyPossitionLessThan;
		m_Settings.m_huntzoneY  = settings.m_huntzoneY;
		m_Settings.m_huntzoneX = settings.m_huntzoneX;
		m_Settings.m_bountyactive = settings.m_bountyactive;

		if(settings.m_premasave)
		  m_Settings.SaveSettings();
		SendIsAdmin(sender);
	}

	void  RpcReloadSettings(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		LogMessage("RpcReloadSettings()  Admincommand");
		m_Settings = BountySetting.Load();
		SendIsAdmin(sender);
	}


	void  RpcForceEndHunt(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		LogMessage("RpcForceEndHunt()  Admincommand");
		ForceEnd();

	}

	void  RpcForceStartHunt(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		LogMessage("RpcForceStartHunt()  Admincommand");
		ForceEnd();
		ref array<Man> players = new ref array<Man> ();
		GetGame().GetPlayers(players);
		StartBountyHunt(players);

	}

	void RpcForceStartHuntSelected(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		ref Param1<string> data;
    if ( !ctx.Read( data ) )
			return;

		LogMessage("RpcForceStartHuntSelected()  Admincommand or Token");
		string pName = data.param1;
		autoptr array<Man> players = new array<Man>;
		GetGame().GetPlayers( players );
		foreach(Man m_player : players)
		{
			PlayerBase plbase = PlayerBase.Cast(m_player);
			if(plbase.GetIdentity().GetName() == pName)
			{
				ForceEnd();
				ref array<Man> fakeArray = new ref array<Man> ();
				fakeArray.Insert(m_player);
				StartBountyHunt(fakeArray);
				return;
			}
		}
	}

	void  RpcEndHunt(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		LogMessage("RpcEndHunt()  Admincommand");
		BountyTimeEnd();
		ForceEnd();

	}

	void  RpcStartHunt(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		LogMessage("RpcStartHunt()  Admincommand");
		ForceEnd();
		InitBountyHunt();
	}

	void  RpcDeleteToken(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		ref Param1<Object> data;
    if ( !ctx.Read( data ) ) return;
		ItemBase tokenItem = ItemBase.Cast(data.param1);
		tokenItem.Delete();
		LogMessage("RpcDeleteToken()  ");
	}

	void SendIsAdmin(PlayerIdentity identity)
	{
		GetRPCManager().SendRPC( "BountyRpcs", "OnIsAdminCheck", new Param2<bool , BountySetting> ( true , m_Settings ), true ,identity  );
	}

	void  RpcBountyPlayerActive(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		LogMessage("RpcBountyPlayerActive()");
		ref Param1<bool> data;
        if ( !ctx.Read( data ) ) return;
		bool playerActive  = data.param1;
		PlayerBase player =  GetPlayer(sender.GetPlainId());
		player.m_bounty_player_active = playerActive;
		LogMessage("RpcBountyPlayerActive() Player changed state to " + playerActive + " " + player.GetPlayerUID());
	}

	void Ticker()
	{
		if(!m_Settings.m_bountyactive)
		{
		//ForceEnd();
		}
		else
		{
			if(m_bountydisconnect)
			{
				LogMessage("Ticker() Bounty player disconnected we wait for reconnect...");
				if(m_timetoreconnect <= 0)
				{
					LogMessage("Ticker() Bounty player disconnected Max ticks elapsed, force end :((");
					AddStat(m_BountyPlayerId,BountyStatsEvent.Leave, "");
					SendMessage(m_Settings.m_text_BountyLeftGame);
					ForceEnd();
					m_timetoreconnect = m_Settings.m_timetoreconnect;
					m_bountydisconnect = false;
				}
				else
				{
					LogMessage("Ticker() Bounty player disconnected Ticks Left : " + m_timetoreconnect);
					m_timetoreconnect = m_timetoreconnect - 10;

					//waiting until bounty has really left
					if(m_timetoreconnect >=  m_Settings.m_timetoreconnect - 60)
						return;

					autoptr array<Man> players = new array<Man>;
					GetGame().GetPlayers( players );
					foreach(Man m_player : players)
					{
						PlayerBase plbase = PlayerBase.Cast(m_player);
						if(plbase.GetPlayerUID() == m_BountyPlayerId)
						{
							LogMessage("Ticker() Bounty player is back, the hunt can go on - Player ID  " + plbase.GetPlayerUID()  + " BountyID " + m_BountyPlayerId );
							SendMessage(m_Settings.m_text_BountyPlayerIsBack);
							m_bountydisconnect = false;
							m_timetoreconnect = m_Settings.m_timetoreconnect;
							m_BountyPlayer  = PlayerBase.Cast(m_player);

							plbase.m_bounty_player_active_for_current = true;
							return;
						}
					}
				}
				return;
			}



			if(!BountyIsAlive())
			{

				if(m_nextruninseconds >= 0)
				{
					LogMessage("Ticker Bounty is inactive Timeleft " + m_nextruninseconds);
					m_nextruninseconds = m_nextruninseconds - 10;

				}
				else
				{
						LogMessage("Ticker Check for valid bounty hunt ");
						CheckBountyHuntIsActive();
				}
				UpdateBountyState();
			}
			else
			{
				LogMessage("Ticker Bounty is alive Timeleft " + m_timeleft);
				if(m_timeleft >= 0)
				{

					m_timeleft = m_timeleft - 10;

					if(m_showbountypostime <= 0)
					{
						ShowBountyPosition();
						m_showbountypostime = m_Settings.m_ShowBountyPosition * 60;
					}
					else
					 m_showbountypostime = m_showbountypostime - 10;
				}
				else
				{
					BountyTimeEnd();
				}
			}
		}
	}

	bool BountyIsAlive()
	{
		if(!m_BountyPlayer)
		{
			m_BountyHuntActive  = false;
			return false;
		}

		if(!m_BountyHuntActive)
			return false;

		if(!m_BountyPlayer.IsAlive())
		{
			m_BountyHuntActive = false;
			return false;
		}
		return true;
	}



	void LogMessage(string message)
	{
		if(BountyLogger.m_debug) BountyLogger.LogMessage(message);
		//SendMessage(message);

	}

void AddStat(string id , BountyStatsEvent bevent , string name)
{

    BountyStats stats;

    for( int i = 0 ; i < m_stats.Count() ; i++)
    {
        if(m_stats.Get(i).m_Identity == id)
        {
            stats = m_stats.Get(i);
			i = m_stats.Count();	
            break;
        }
    }

    if(!stats)
    {
        stats = new BountyStats();
        stats.m_Identity = id;
		stats.m_name = name;	
        m_stats.Insert(stats);
    }

		if(name != "")
			stats.m_name = name;

		switch (bevent)
		{
			case BountyStatsEvent.Death : 	stats.m_bountyDeaths++;
										 	stats.m_points = stats.m_points + m_Settings.m_points_deathpoints;
				break;
			case BountyStatsEvent.Kill : 	stats.m_bountyKills++;
										 	stats.m_points = stats.m_points + m_Settings.m_points_killpoints;
				break;
			case BountyStatsEvent.Leave :
											stats.m_points = stats.m_points + m_Settings.m_points_leavepoints;
				break;
			case BountyStatsEvent.Survive : stats.m_bountySurvived++;
											stats.m_points = stats.m_points + m_Settings.m_points_survivepoints;
				break;
		}

		m_stats = BountyStats.SortStats(m_stats);
		BountyStats.SaveStats(m_stats);
	}



	void SendMessage(string message )
	{
			//LogMessage("SendMessage " + message);
			Param1<string> m_MessageParam = new Param1<string>(message);
			autoptr array<Man> players = new array<Man>;
			GetGame().GetPlayers( players );
			foreach(Man player : players)
			{
				SendMessageToPlayer(message , player );
			}
	}


	void SendMessageToPlayer(string message,ref Man player )
	{
			PlayerBase plbase = PlayerBase.Cast(player);
			if(plbase.m_bounty_player_active_for_current)
			{

				//LogMessage("SendMessage to single player" + message);
				Param1<string> m_MessageParam = new Param1<string>(message);
				GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, m_MessageParam, true, player.GetIdentity());
			}
	}


	void SendDistanceBetweenPlayersAndBounty()
	{
			if(!BountyIsAlive())
				return;

			LogMessage("SendDistanceBetweenPlayers()");
			int m_sourplayers = 0;
			autoptr array<Man> players = new array<Man>;
			GetGame().GetPlayers( players );
			foreach(Man m_player : players)
			{
				if(m_player.GetIdentity() != m_BountyPlayer.GetIdentity() )
				{
					LogMessage("SendDistanceBetweenPlayers() Player is not the bounty player");
					float m_distance =  vector.Distance( m_player.GetPosition() , m_BountyPlayer.GetPosition());
					if(m_distance > m_Settings.m_HideBountyPossitionLessThan)
					{
						string msg = m_Settings.m_text_BountyDistanceToHunter;
						msg.Replace("##distance##" , Math.Round(m_distance).ToString());
						LogMessage("SendDistanceBetweenPlayers " + msg);
						SendMessageToPlayer(msg ,m_player);
					}
					else // count surrounding players
						m_sourplayers++;
				}
			}
		if(m_sourplayers > 0 )
		{
			string msg1 = m_Settings.m_text_NearEnemys;
			msg1.Replace("##players##" , m_sourplayers.ToString());
			SendMessageToBounty(msg1);
		}
	}

	void SendMessageToBounty(string message)
	{

		LogMessage("SendMessageToBounty " + message);
		if(m_BountyPlayer)
		{
				Param1<string> m_MessageParam = new Param1<string>(message);
				GetGame().RPCSingleParam(m_BountyPlayer, ERPCs.RPC_USER_ACTION_MESSAGE, m_MessageParam, true, m_BountyPlayer.GetIdentity());
		}
	}

	bool IsAdmin(ref PlayerBase player)
	{
		for(int i = 0; i < m_Settings.m_admins.Count(); i++)
		{
			if(player.GetPlayerUID() == m_Settings.m_admins.Get(i))
			
			{
				GetRPCManager().SendRPC( "BountyRpcs", "OnIsAdminCheck", new Param2<bool , BountySetting> ( true , m_Settings ),true,player.GetIdentity() );
				return true;
			}
		}
		return false;
	}


	void RpcGetBountyState( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
	//		LogMessage("GetBountyState() Sending to target " + sender.GetPlainId());
			PlayerBase plbase = GetPlayer(sender.GetPlainId());
			ref BountyState stat  = m_BountyState;
			if(!BountyIsAlive())
				plbase.m_bounty_player_active_for_current = true;
			GetRPCManager().SendRPC( "BountyRpcs", "OnBountyHuntUpdate", new ref Param2<bool, ref BountyState >( plbase.m_bounty_player_active_for_current , stat ),true ,sender);
	//		LogMessage("GetBountyState() Exit");
	}

	void RpcBountyGetPlayersActive( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
	{
		ref Param1<bool> data;
  	if ( !ctx.Read( data ) )
			return;

		bool isToken  = data.param1;
		autoptr array<Man> players = new array<Man>;
		GetGame().GetPlayers( players );
			for(int i = 0; i < players.Count() ; i++)
			{
				Man playerMan =  players.Get(i);
				if (playerMan)
				{
					PlayerBase plbas = PlayerBase.Cast(playerMan);
					if (plbas)
					{
						bool isActive = true;

						if(!plbas.m_bounty_player_active || !plbas.IsAlive())
							isActive = false;

						GetRPCManager().SendRPC( "BountyRpcs", "PassPlayerActive", new ref Param3<string, bool, bool>(plbas.GetIdentity().GetName(), isActive, isToken),true, sender);
					}
				}
			}
	}


	void CheckBountyHuntIsActive()
	{
//		LogMessage("CheckBountyHuntIsActive()");

		if(BountyIsAlive() || m_BountyHuntActive )
			return;
	    m_BountyHuntActive = true;
		InitBountyHunt();
	}



	void InitBountyHunt()
	{
//		LogMessage("InitBountyHunt()");

//		LogMessage("InitBountyHunt() Setting up hunt");

		autoptr array<Man> players = new array<Man>;
		GetGame().GetPlayers( players );

			autoptr array<Man> validPlayers = new array<Man>;

			for(int i = 0; i < players.Count() ; i++)
			{
				Man pl =  players.Get(i);

				PlayerBase plbase = PlayerBase.Cast(pl);

				if(!plbase.m_bounty_player_active)
					plbase.m_bounty_player_active_for_current = false;

				if(pl.IsAlive() && plbase.m_bounty_player_active)
				{
					if(!m_Settings.m_huntzoneX && m_Settings.m_huntzoneX == 0)
						 m_Settings.m_huntzoneX = 12000;

					if(!m_Settings.m_huntzoneY && m_Settings.m_huntzoneY == 0)
						 m_Settings.m_huntzoneY = 3100;

					plbase.m_bounty_player_active_for_current = true;

					vector plposition = pl.GetPosition();
					if(plposition[0] < m_Settings.m_huntzoneX && plposition[2] > m_Settings.m_huntzoneY )
					{
						validPlayers.Insert(pl);
						LogMessage("InitBountyHunt() Player "  +  pl.GetIdentity().GetName()  + " " + plposition + " is valid  X is  "  +  m_Settings.m_huntzoneX + " Y is " +  m_Settings.m_huntzoneY );
					}
					else
					{
						LogMessage("InitBountyHunt() Player "  +  pl.GetIdentity().GetName()  + " " + plposition + " is NOT valid  X is  "  +  m_Settings.m_huntzoneX + " Y is " +  m_Settings.m_huntzoneY );
					}

				}
			}

		if(players.Count() >= m_Settings.m_MinPlayers && validPlayers.Count() > 0)
		{
			LogMessage("InitBountyHunt() -- Enough valid players found");
			StartBountyHunt(validPlayers);
		}
    }


	void PlayerKilled(Object killer, PlayerBase victim)
	{
		LogMessage("PlayerKilled()");

		bool killnotlegit = false;

		if(victim != m_BountyPlayer)
		{
		LogMessage("PlayerKilled() -- victim is not hunted player return");
			return;
		}

		LogMessage("PlayerKilled() -- victim is hunted player lets check if everything is good");

		if(victim == killer)
		{
			 LogMessage("PlayerKilled() -- Kill was not done by other player");
			 ForceEndSuicide();
		}

		AddStat(victim.GetPlayerUID() ,BountyStatsEvent.Death, victim.GetIdentity().GetName());

		if (killer.IsInherited(DayZInfected))
		{
			LogMessage("PlayerKilled() -- Kill was done by infected");
			ForceEndByInfected();
		}

		if ((killer.IsInherited(SurvivorBase) && killer != victim) || killer.IsWeapon() || killer.IsMeleeWeapon())
		{
			LogMessage("PlayerKilled() -- Kill was done by other player");
			PlayerBase killerVictim = PlayerBase.Cast(killer);
			if(!killerVictim)
				killerVictim = PlayerBase.Cast(EntityAI.Cast(killer).GetHierarchyParent());
			CheckBountyKilled(killerVictim , victim.GetIdentity());
		}

		Transport vehicle = Transport.Cast(killer);
		if (vehicle && vehicle.IsTransport())
		{
			LogMessage("PlayerKilled() -- by a vehicle");
			CarScript car = CarScript.Cast(killer);
			Human driver = Human.Cast(car.CrewMember(0));
			CheckBountyKilled(PlayerBase.Cast(driver) , victim.GetIdentity());
		}
	}


	void StartBountyHunt(array<Man> players)
	{
		LogMessage("StartBountyHunt() Preparing the hunt");

		m_BountyPlayer = PlayerBase.Cast(players.GetRandomElement());
		string msg =  m_Settings.m_text_NewBountyBegin;
		msg.Replace("##player##" , m_BountyPlayer.GetIdentity().GetName());
		SendMessage(msg);

		m_BountyHuntActive = true;

		m_timeleft =  m_Settings.m_MaxBountyHuntTime * 60;
		m_showbountypostime = m_Settings.m_ShowBountyPosition * 60;
		ShowBountyPosition();
		UpdateBountyState();

	}


	void BountyTimeEnd()
	{
		LogMessage("BountyTimeEnd()");

		if(!BountyIsAlive())
				return;

		LogMessage("BountyTimeEnd() Target won the hunt");
		string msg = m_Settings.m_text_BountyEndElapsedTimeSendReward;
		msg.Replace("##player" , m_BountyPlayer.GetIdentity().GetName());
		SendMessage(msg);
		LogMessage("BountyTimeEnd() Rewarding player survived");
		AddStat(m_BountyPlayer.GetPlayerUID() ,BountyStatsEvent.Survive,m_BountyPlayer.GetIdentity().GetName());
Print("[BOUNTYHUNT] GetPlayerUID: " +m_BountyPlayer.GetPlayerUID());	
Print("[BOUNTYHUNT] GetID : " +m_BountyPlayer.GetIdentity().GetId());				
	//	AddStat(m_BountyPlayer.GetIdentity().GetId(),BountyStatsEvent.Survive,m_BountyPlayer.GetIdentity().GetName());
		if(m_Settings.m_RewardBountyPlayerAlive)
		{
			SendReward();
		}
		ForceEnd();
	}


	void ForceEnd()
	{
		LogMessage("ForceEnd Execute force end");
		m_showbountypostime = -1;
		m_BountyHuntActive = false;
		m_BountyPlayer = null;
		m_timeleft = 0;
		m_nextruninseconds = m_Settings.m_Interval * 60;
		m_BountyState.m_lastpos.Clear();
		UpdateBountyState();
	}


	void ForceEndSuicide()
	{
			AddStat(m_BountyPlayer.GetPlayerUID() ,BountyStatsEvent.Leave,m_BountyPlayer.GetIdentity().GetName());
	//		AddStat(m_BountyPlayer.GetIdentity().GetId(),BountyStatsEvent.Leave,m_BountyPlayer.GetIdentity().GetName());
		 	SpawnBountyPlayerAsZombie();
			SendMessage(m_Settings.m_text_BountySuicide);
			ForceEnd();
	}


	void ForceEndByInfected()
	{
		AddStat(m_BountyPlayer.GetPlayerUID() ,BountyStatsEvent.Death, m_BountyPlayer.GetIdentity().GetName());
	//	AddStat(m_BountyPlayer.GetIdentity().GetId(),BountyStatsEvent.Death, m_BountyPlayer.GetIdentity().GetName());
		SpawnBountyPlayerAsZombie();
		SendReward();
		SendMessage(m_Settings.m_text_BountyKilledByInfected);
		ForceEnd();
	}

	void SpawnBountyPlayerAsZombie()
	{
		LogMessage("SpawnBountyPlayerAsZombie()");
		GetGame().CreateObject( WorkingZombieClasses().GetRandomElement(), m_BountyPlayer.GetPosition() , false, true);
	}


	void ForceEndDisconnect(PlayerBase player)
	{
		if(m_BountyPlayer)
			if(player.GetPlayerUID() == m_BountyPlayer.GetIdentity().GetPlainId())
			{
				m_BountyPlayerId = player.GetPlayerUID();
				LogMessage("Bounty Disconnect ID = "+ m_BountyPlayerId + " Bounty ID  " +   m_BountyPlayer.GetIdentity().GetPlainId());
				LogMessage("Bounty Disconnect Name = "+ player.GetIdentity().GetName() + " Bounty ID  " +   m_BountyPlayer.GetIdentity().GetName());
				//6  ticks ==  1min
			 	m_timetoreconnect = m_Settings.m_timetoreconnect;
				m_bountydisconnect = true;
				SendMessage(m_Settings.m_text_BountyPlayerIsDisconnected);
			}
	}

	void SendReward()
	{
	    LogMessage("SendReward()");
		bool validchest = true;
		if(m_Settings.m_rewardContainer == "")
			validchest = false;

		EntityAI m_chest;
		m_chest = EntityAI.Cast(GetGame().CreateObject( m_Settings.m_rewardContainer, m_BountyPlayer.GetPosition()));

		if(!m_chest)
			validchest = false;

		BountyLoot reward = m_Settings.m_rewards.GetRandomElement();

		if (reward) LogMessage("SendReward() Random reward found, trying to spawn " + reward.m_weapon);
			if(validchest)
			{
				LogMessage("SendReward() chest is valid spawning items in chest");
				EntityAI weapon;
				weapon = m_chest.GetInventory().CreateInInventory(reward.m_weapon);

				for(int i = 0; i < reward.m_weapon_attachements.Count() ; i++)
				{
					LogMessage("SendReward() spawning weapon attachement  " + reward.m_weapon_attachements.Get(i) + " in the reward container");
					weapon.GetInventory().CreateAttachment(reward.m_weapon_attachements.Get(i));
				}

				for(int a = 0; a < reward.m_other_Loot.Count() ; a++)
				{
					LogMessage("SendReward() spawning other loot " + reward.m_other_Loot.Get(a) + " in the reward container");
					m_chest.GetInventory().CreateInInventory(reward.m_other_Loot.Get(a));
				}
			}
			else
			{
				LogMessage("SendReward() chest is NOT valid spawning items at players location");

				EntityAI weapon1;
				weapon1 = EntityAI.Cast(GetGame().CreateObject( reward.m_weapon, m_BountyPlayer.GetPosition()));

				for(int f = 0; f < reward.m_weapon_attachements.Count() ; f++)
				{
					LogMessage("SendReward() spawning weapon attachement  " + reward.m_weapon_attachements.Get(f) + " at players position");
					weapon1.GetInventory().CreateAttachment(reward.m_weapon_attachements.Get(f));
				}

				for(int g = 0; g < reward.m_other_Loot.Count() ; g++)
				{
					LogMessage("SendReward() spawning other loot " + reward.m_other_Loot.Get(g) + " at players position");
					GetGame().CreateObject(reward.m_other_Loot.Get(g),m_BountyPlayer.GetPosition());
				}
			}

		ForceEnd();
	}

	void ShowBountyPosition()
	{
		LogMessage("ShowBountyPosition()");
		if(!BountyIsAlive())
				return;

		if(m_Settings.m_showbountyonmap)
		{
			if(m_BountyState.m_lastpos.Count() >=  m_Settings.m_bountyposqueue)
				m_BountyState.m_lastpos.Remove(0);
			if(m_BountyState.m_lastpos.Count() > 0)
			{
				int size = m_BountyState.m_lastpos.Count() ;
				int lastindex = size - 1;
				vector lastpos = m_BountyState.m_lastpos.Get(lastindex);
				if(vector.Distance(lastpos ,m_BountyPlayer.GetPosition()) > 100 )
				{
					m_BountyState.m_lastpos.Insert(m_BountyPlayer.GetPosition());
				}
			}
			else
			  	m_BountyState.m_lastpos.Insert(m_BountyPlayer.GetPosition());
		}
		else
		{
		m_BountyState.m_lastpos.Remove(0);	
		}


		CheckIsInForbiddenArea();

		CalculateNearestPos();

		string msg = m_Settings.m_text_BountyInfo;
		msg.Replace("##player##", m_BountyPlayer.GetIdentity().GetName());
		msg.Replace("##distance##",Math.Round(m_nearestdistance).ToString());
		msg.Replace("##location##",nearest.m_name);
		SendMessage(msg);
		SendDistanceBetweenPlayersAndBounty();
		UpdateBountyState();
	}


	void UpdateBountyState()
	{
		if(BountyIsAlive())
		{
			m_BountyState.m_lastseen = nearest.m_name + " " +  Math.Round(m_nearestdistance) + "m away";
			m_BountyState.m_playername = m_BountyPlayer.GetIdentity().GetName();
			PlayerBase pbase = PlayerBase.Cast(m_BountyPlayer);
			ItemBase ibase = pbase.GetItemInHands();
			if(ibase)
			{
				if(ibase.IsWeapon())
					m_BountyState.m_weaponinhands = ibase.GetType(); // ?? GetDisplayName() ??
				else
					m_BountyState.m_weaponinhands = "-";
			}
			else
			{
					m_BountyState.m_weaponinhands = "-";
			}

			m_BountyState.m_currblood =  Math.Round( pbase.GetHealth("","Blood") / 5000 * 100) ;
			m_BountyState.m_currhealth = Math.Round(	pbase.GetHealth() );

			int totalsec =  m_Settings.m_MaxBountyHuntTime * 60;
			int tleft =  Math.Round(m_timeleft / 60);
			m_BountyState.m_timeleft = "" + tleft + "min";
			m_BountyState.m_progress = Math.Round(m_timeleft / totalsec * 100);
			LogMessage("UpdateBountyState Timeleft time:  " +  m_BountyState.m_timeleft );
			LogMessage("UpdateBountyState Timeleft PGR:  " +  m_BountyState.m_progress);

			if(tleft < 0)
				m_BountyState.m_timeleft = "--:--";
			if(m_BountyState.m_progress < 0)
				m_BountyState.m_progress = 0;

		}
		else
		{
			m_BountyState.m_playername = "-";
			m_BountyState.m_lastseen = "-";
			m_BountyState.m_currhealth = 100;
			m_BountyState.m_weaponinhands = "-";
			m_BountyState.m_currblood = 100;

			int totalsec1 =  m_Settings.m_Interval * 60;
			int nexthunt = Math.Round(m_nextruninseconds / 60);
			m_BountyState.m_timeleft ="" + nexthunt + "min";
			m_BountyState.m_progress = Math.Round(m_nextruninseconds / totalsec1 * 100);

			if(nexthunt <= 0)
				m_BountyState.m_timeleft = "Waiting for valid players...";
			if(m_BountyState.m_progress < 0)
				m_BountyState.m_progress = 0;

			LogMessage("UpdateBountyState Next Hunt time:  " +  m_BountyState.m_timeleft );
			LogMessage("UpdateBountyState Next Hunt PGR:  " +  m_BountyState.m_progress);
		}

		m_BountyState.m_stats = BountyStats.GetTop50(m_stats);
	}


	void CheckIsInForbiddenArea()
	{
		if(!m_BountyPlayer || !m_BountyHuntActive)
			return;

		m_nearestdistance = 999999;
		LogMessage("CheckIsInForbiddenArea()");
        for(int i = 0; i < m_Settings.m_forbiddenarea.Count() ; i++)
		{
			BountyLocation loc = m_Settings.m_forbiddenarea.Get(i);
		   // LogMessage("CheckIsInForbiddenArea() Checking location " + loc.m_name + " Position is " + loc.m_x + " " + loc.m_y);

			vector pos = loc.GetPosition();
			float m_distance =  vector.Distance(pos  , m_BountyPlayer.GetPosition());

		//	LogMessage("CheckIsInForbiddenArea() Checking location " + loc.m_name + " distance from hunted player is " + m_distance);

			if(m_distance <  500)
			{
				LogMessage("CheckIsInForbiddenArea()  Target is in a forbidden area, teleporting him 500m away ");
				pos[1] = GetGame().SurfaceY(loc.m_x + 500, loc.m_y + 500) ;
				pos[0] = loc.m_x + 500;
				pos[2] =  loc.m_y + 500;
				m_BountyPlayer.SetPosition(pos);
				SendMessageToBounty(m_Settings.m_text_BountyForbiddenArea);
			}
		}
	}


	void CheckBountyKilled(PlayerBase killer, PlayerIdentity victimIdentity)
	{
		LogMessage("CheckBountyKilled()");
		if(!m_BountyHuntActive)
			return;

		if(victimIdentity == m_BountyPlayer.GetIdentity())
		{
			LogMessage("CheckBountyKilled() victim is the hunted player");
			string msg = m_Settings.m_text_BountyIsKilled;
			msg.Replace("##player##" ,  killer.GetIdentity().GetName());
			SendMessage(msg);
			SpawnBountyPlayerAsZombie();
			SendReward();
			AddStat(killer.GetPlayerUID(),BountyStatsEvent.Kill , killer.GetIdentity().GetName());
		}
		else
			LogMessage("CheckBountyKilled() victim is NOT the hunted player");

	}


	void CalculateNearestPos()
	{
		m_nearestdistance = 999999;
		LogMessage("CalculateNearestPos()");
        for(int i = 0; i < m_Settings.m_locations.Count() ; i++)
		{
			BountyLocation loc = m_Settings.m_locations.Get(i);
		  //   LogMessage("CalculateNearestPos() Checking location " + loc.m_name + " Position is " + loc.m_x + " " + loc.m_y);

			float m_distance =  vector.Distance( loc.GetPosition() , m_BountyPlayer.GetPosition());

		  //	LogMessage("CalculateNearestPos() Checking location " + loc.m_name + " distance from hunted player is " + m_distance);

			if(m_distance <  m_nearestdistance)
			{
			//	LogMessage("CalculateNearestPos() Checking location " + loc.m_name + " is the nearest. Previous distance was " + m_nearestdistance);
				nearest = loc;
				m_nearestdistance = m_distance;
			}

			if(m_nearestdistance < 400)
			{
				LogMessage("CalculateNearestPos() Location is under 400m we dont need to search more");
				nearest = loc;
				m_nearestdistance = m_distance;
				return;
			}
		}
	}

	PlayerBase GetPlayer(string identity)
	{
			array<Man> players = new array<Man>;
			GetGame().GetPlayers( players );
			foreach(Man player : players)
			{
				PlayerBase ident = PlayerBase.Cast(player);
				LogMessage(" " + ident.GetPlayerUID() + " " + ident.GetName());
				if( ident.GetPlayerUID() == identity)
					return ident;
			}
			return null,
	}

	TStringArray WorkingZombieClasses()
	{
		return {
		"ZmbM_HermitSkinny_Base","ZmbM_HermitSkinny_Beige","ZmbM_HermitSkinny_Black","ZmbM_HermitSkinny_Green",
		"ZmbM_HermitSkinny_Red","ZmbM_FarmerFat_Base","ZmbM_FarmerFat_Beige","ZmbM_FarmerFat_Blue","ZmbM_FarmerFat_Brown",
		"ZmbM_FarmerFat_Green","ZmbF_CitizenANormal_Base","ZmbF_CitizenANormal_Beige","ZmbF_CitizenANormal_Brown",
		"ZmbF_CitizenANormal_Blue","ZmbM_CitizenASkinny_Base","ZmbM_CitizenASkinny_Blue","ZmbM_CitizenASkinny_Brown",
		"ZmbM_CitizenASkinny_Grey","ZmbM_CitizenASkinny_Red","ZmbM_CitizenBFat_Base","ZmbM_CitizenBFat_Blue","ZmbM_CitizenBFat_Red",
		"ZmbM_CitizenBFat_Green","ZmbF_CitizenBSkinny_Base","ZmbF_CitizenBSkinny","ZmbM_PrisonerSkinny_Base","ZmbM_PrisonerSkinny",
		"ZmbM_FirefighterNormal_Base","ZmbM_FirefighterNormal","ZmbM_FishermanOld_Base","ZmbM_FishermanOld_Blue","ZmbM_FishermanOld_Green",
		"ZmbM_FishermanOld_Grey","ZmbM_FishermanOld_Red","ZmbM_JournalistSkinny_Base","ZmbM_JournalistSkinny","ZmbF_JournalistNormal_Base",
		"ZmbF_JournalistNormal_Blue","ZmbF_JournalistNormal_Green","ZmbF_JournalistNormal_Red","ZmbF_JournalistNormal_White",
		"ZmbM_ParamedicNormal_Base","ZmbM_ParamedicNormal_Blue","ZmbM_ParamedicNormal_Green","ZmbM_ParamedicNormal_Red",
		"ZmbM_ParamedicNormal_Black","ZmbF_ParamedicNormal_Base","ZmbF_ParamedicNormal_Blue","ZmbF_ParamedicNormal_Green",
		"ZmbF_ParamedicNormal_Red","ZmbM_HikerSkinny_Base","ZmbM_HikerSkinny_Blue","ZmbM_HikerSkinny_Green","ZmbM_HikerSkinny_Yellow",
		"ZmbF_HikerSkinny_Base","ZmbF_HikerSkinny_Blue","ZmbF_HikerSkinny_Grey","ZmbF_HikerSkinny_Green","ZmbF_HikerSkinny_Red",
		"ZmbM_HunterOld_Base","ZmbM_HunterOld_Autumn","ZmbM_HunterOld_Spring","ZmbM_HunterOld_Summer","ZmbM_HunterOld_Winter",
		"ZmbF_SurvivorNormal_Base","ZmbF_SurvivorNormal_Blue","ZmbF_SurvivorNormal_Orange","ZmbF_SurvivorNormal_Red",
		"ZmbF_SurvivorNormal_White","ZmbM_SurvivorDean_Base","ZmbM_SurvivorDean_Black","ZmbM_SurvivorDean_Blue","ZmbM_SurvivorDean_Grey",
		"ZmbM_PolicemanFat_Base","ZmbM_PolicemanFat","ZmbF_PoliceWomanNormal_Base","ZmbF_PoliceWomanNormal","ZmbM_PolicemanSpecForce_Base",
		"ZmbM_PolicemanSpecForce","ZmbM_SoldierNormal_Base","ZmbM_SoldierNormal","ZmbM_usSoldier_normal_Base",
		"ZmbM_usSoldier_normal_Woodland","ZmbM_usSoldier_normal_Desert","ZmbM_CommercialPilotOld_Base","ZmbM_CommercialPilotOld_Blue",
		"ZmbM_CommercialPilotOld_Olive","ZmbM_CommercialPilotOld_Brown","ZmbM_CommercialPilotOld_Grey","ZmbM_PatrolNormal_Base",
		"ZmbM_PatrolNormal_PautRev","ZmbM_PatrolNormal_Autumn","ZmbM_PatrolNormal_Flat","ZmbM_PatrolNormal_Summer","ZmbM_JoggerSkinny_Base",
		"ZmbM_JoggerSkinny_Blue","ZmbM_JoggerSkinny_Green","ZmbM_JoggerSkinny_Red","ZmbF_JoggerSkinny_Base","ZmbF_JoggerSkinny_Blue",
		"ZmbF_JoggerSkinny_Brown","ZmbF_JoggerSkinny_Green","ZmbF_JoggerSkinny_Red","ZmbM_MotobikerFat_Base","ZmbM_MotobikerFat_Beige",
		"ZmbM_MotobikerFat_Black","ZmbM_MotobikerFat_Blue","ZmbM_VillagerOld_Base","ZmbM_VillagerOld_Blue","ZmbM_VillagerOld_Green",
		"ZmbM_VillagerOld_White","ZmbM_SkaterYoung_Base","ZmbM_SkaterYoung_Blue","ZmbM_SkaterYoung_Brown","ZmbM_SkaterYoung_Green",
		"ZmbM_SkaterYoung_Grey","ZmbF_SkaterYoung_Base","ZmbF_SkaterYoung_Brown","ZmbF_SkaterYoung_Striped","ZmbF_SkaterYoung_Violet",
		"ZmbF_DoctorSkinny_Base","ZmbF_DoctorSkinny","ZmbF_BlueCollarFat_Base","ZmbF_BlueCollarFat_Blue","ZmbF_BlueCollarFat_Green",
		"ZmbF_BlueCollarFat_Red","ZmbF_BlueCollarFat_White","ZmbF_MechanicNormal_Base","ZmbF_MechanicNormal_Beige","ZmbF_MechanicNormal_Green",
		"ZmbF_MechanicNormal_Grey","ZmbF_MechanicNormal_Orange","ZmbM_MechanicSkinny_Base","ZmbM_MechanicSkinny_Blue","ZmbM_MechanicSkinny_Grey",
		"ZmbM_MechanicSkinny_Green","ZmbM_MechanicSkinny_Red","ZmbM_ConstrWorkerNormal_Base","ZmbM_ConstrWorkerNormal_Beige",
		"ZmbM_ConstrWorkerNormal_Black","ZmbM_ConstrWorkerNormal_Green","ZmbM_ConstrWorkerNormal_Grey","ZmbM_HeavyIndustryWorker_Base",
		"ZmbM_HeavyIndustryWorker","ZmbM_OffshoreWorker_Base","ZmbM_OffshoreWorker_Green","ZmbM_OffshoreWorker_Orange","ZmbM_OffshoreWorker_Red",
		"ZmbM_OffshoreWorker_Yellow","ZmbF_NurseFat_Base","ZmbF_NurseFat","ZmbM_HandymanNormal_Base","ZmbM_HandymanNormal_Beige",
		"ZmbM_HandymanNormal_Blue","ZmbM_HandymanNormal_Green","ZmbM_HandymanNormal_Grey","ZmbM_HandymanNormal_White","ZmbM_DoctorFat_Base",
		"ZmbM_DoctorFat","ZmbM_Jacket_Base","ZmbM_Jacket_beige","ZmbM_Jacket_black","ZmbM_Jacket_blue","ZmbM_Jacket_bluechecks",
		"ZmbM_Jacket_brown","ZmbM_Jacket_greenchecks","ZmbM_Jacket_grey","ZmbM_Jacket_khaki","ZmbM_Jacket_magenta","ZmbM_Jacket_stripes",
		"ZmbF_PatientOld_Base","ZmbF_PatientOld","ZmbM_PatientSkinny_Base","ZmbM_PatientSkinny","ZmbF_ShortSkirt_Base","ZmbF_ShortSkirt_beige",
		"ZmbF_ShortSkirt_black","ZmbF_ShortSkirt_brown","ZmbF_ShortSkirt_green","ZmbF_ShortSkirt_grey","ZmbF_ShortSkirt_checks",
		"ZmbF_ShortSkirt_red","ZmbF_ShortSkirt_stripes","ZmbF_ShortSkirt_white","ZmbF_ShortSkirt_yellow","ZmbF_VillagerOld_Base",
		"ZmbF_VillagerOld_Blue","ZmbF_VillagerOld_Green","ZmbF_VillagerOld_Red","ZmbF_VillagerOld_White","ZmbM_Soldier","ZmbM_SoldierAlice",
		"ZmbM_SoldierHelmet","ZmbM_SoldierVest","ZmbM_SoldierAliceHelmet","ZmbM_SoldierVestHelmet","ZmbF_MilkMaidOld_Base",
		"ZmbF_MilkMaidOld_Beige","ZmbF_MilkMaidOld_Black","ZmbF_MilkMaidOld_Green","ZmbF_MilkMaidOld_Grey","ZmbM_priestPopSkinny_Base",
		"ZmbM_priestPopSkinny","ZmbM_ClerkFat_Base","ZmbM_ClerkFat_Brown","ZmbM_ClerkFat_Grey","ZmbM_ClerkFat_Khaki","ZmbM_ClerkFat_White",
		"ZmbF_Clerk_Normal_Base","ZmbF_Clerk_Normal_Blue","ZmbF_Clerk_Normal_White","ZmbF_Clerk_Normal_Green","ZmbF_Clerk_Normal_Red",
		};
	}
}

static ref BountyBase g_BountyBase;
static ref BountyBase GetBountyBase()
{
	if(!g_BountyBase)
		g_BountyBase = BountyBase.Cast(GetPlugin(BountyBase));
    return g_BountyBase;
}
