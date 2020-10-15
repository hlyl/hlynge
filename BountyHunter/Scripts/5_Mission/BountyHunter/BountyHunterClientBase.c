//################################################################################################################################################################
//####  Made by hlynge - August 2019
//################################################################################################################################################################

class BountyClientBase extends PluginBase
{

	ref BountyState m_bountyState = new ref BountyState();
	ref BountyMenu m_bountyMenu;
	ref BountyAdminMenu m_adminMenu;
	ref BountyTokenMenu m_tokenMenu;
	ref BountyMap m_mapmenu;
	ref BountyRankingMenu m_rankingMenu;
	ref BountySetting m_settings;
	const int CONST_TOKEN_MENU = 3234513;


	bool m_isAdmin = false;

	void BountyClientBase()
	{
		if(BountyLogger.m_debug) BountyLogger.LogMessage("BountyClientBase Initializing ");
		GetRPCManager().AddRPC( "BountyRpcs", "OnBountyHuntUpdate", this);
		GetRPCManager().AddRPC( "BountyRpcs", "OnIsAdminCheck", this);
		GetRPCManager().AddRPC( "BountyRpcs", "PassPlayerActive", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "BountyRpcs", "DisplayBountyToken", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "BountyRpcs", "RpcGetBountyMap", this);
		if(BountyLogger.m_debug) BountyLogger.LogMessage("BountyClientBase Exit ");
	}

//################################################################################################################################################################
//#### Bounty RPCS
//################################################################################################################################################################
	void DisplayBountyToken ( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
	{
			if ( type == CallType.Client )
			{
				Param2< Object, EntityAI > data;
				if ( !ctx.Read( data ) )
					return;
				ShowTokenMenu(ItemBase.Cast(data.param1));
			}
	}
	
	void RpcGetBountyMap ( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
	{
			if ( type == CallType.Client )
			{
				Param2< Object, EntityAI > data;
				if ( !ctx.Read( data ) )
					return;
				ShowMapMenu();
			}
	}
	

	void PassPlayerActive( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
	{
		Param3< string, bool, bool > data;
		if ( !ctx.Read( data ) )
			return;

		string name = data.param1;
		bool isActive = data.param2;
		bool isToken = data.param3;
		if (m_adminMenu && !isToken)
		{
			m_adminMenu.AddPlayer(name, isActive);
		}
		if (m_tokenMenu && isToken)
		{
			m_tokenMenu.AddPlayer(name, isActive);
		}
	}

	void OnIsAdminCheck(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		if(BountyLogger.m_debug) BountyLogger.LogMessage("OnIsAdminCheck ");
		Param2<bool,BountySetting> data;
    if ( !ctx.Read( data ) ) return;
		m_isAdmin = data.param1;
		m_settings = data.param2;

		if(BountyLogger.m_debug) BountyLogger.LogMessage("OnIsAdminCheck Settings  : " + m_settings);
	}


	void OnBountyHuntUpdate(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		if(BountyLogger.m_debug) BountyLogger.LogMessage("OnBountyHuntUpdate ");
		ref Param2<bool, ref BountyState> data;
        if ( !ctx.Read( data ) ) return;
		m_bountyState  = data.param2;
		PlayerBase plbase = PlayerBase.Cast(GetGame().GetPlayer());
		plbase.m_bounty_player_active_for_current = data.param1;
 		ShowBountyMenu();
	}


//################################################################################################################################################################
//#### Bounty Dayz events
//################################################################################################################################################################


    void OnKeyPress( int key )
    {
		if(key == KeyCode.KC_ESCAPE)
			CloseAllMenus();
	}


	void ShowBountyMenuKey()
	{
		if (   GetGame().GetUIManager().GetMenu() == NULL )
		{
				if(BountyLogger.m_debug) BountyLogger.LogMessage("OnKeyPress Send RPC  GetBountyState");
				GetRPCManager().SendRPC( "BountyRpcs", "RpcGetBountyState", new Param1<bool> ( true ) );
		}
	}

	void ShowBountyMapKey()
	{
		if (   GetGame().GetUIManager().GetMenu() == NULL )
		{
				if(BountyLogger.m_debug) BountyLogger.LogMessage("OnKeyPress Send RPC  GetBountyMap");
				GetRPCManager().SendRPC( "BountyRpcs", "RpcGetBountyMap", new Param1<bool> ( true ) );
		}
	}
	
	

//################################################################################################################################################################
//#### Bounty Uis Functions
//################################################################################################################################################################
	void CloseAllMenus()
	{
		  GetGame().GetUIManager().HideDialog();
		  GetGame().GetUIManager().CloseAll();
	}

	void ShowBountyMenu()
	{
        m_bountyMenu = new ref BountyMenu;
        GetGame().GetUIManager().ShowScriptedMenu( m_bountyMenu , NULL );

    }

	void ShowAdminMenu()
	{
        m_adminMenu = new ref BountyAdminMenu(m_settings);
        GetGame().GetUIManager().ShowScriptedMenu( m_adminMenu , NULL );

    }

	void ShowRankingMenu()
	{

        m_rankingMenu = new ref BountyRankingMenu();
       	GetGame().GetUIManager().ShowScriptedMenu( m_rankingMenu , NULL );

    }

	void ShowMapMenu()
	{
        m_mapmenu = new ref BountyMap();
        GetGame().GetUIManager().ShowScriptedMenu( m_mapmenu , NULL );

  }
	void ShowTokenMenu(ItemBase tokenItem)
	{
				if ( CheckMenus( CONST_TOKEN_MENU) )
					return;

				if (m_tokenMenu == NULL)
				{
			    m_tokenMenu = new ref BountyTokenMenu(tokenItem);
					m_tokenMenu.SetID( CONST_TOKEN_MENU );
				}
	      GetGame().GetUIManager().ShowScriptedMenu( m_tokenMenu , NULL );
	}

	bool CheckMenus( int menuID )
	{
			if ( GetGame().GetUIManager().IsMenuOpen( menuID ) ) return true;

			for (int i = 5; i < 37; i++)
			{
					if ( GetGame().GetUIManager().IsMenuOpen( i ) ) return true;
			}

			return false;
	}

}

static ref BountyClientBase g_BountyClientBase;
static ref BountyClientBase GetBhBase()
{
	if(!g_BountyClientBase)
		g_BountyClientBase = BountyClientBase.Cast(GetPlugin(BountyClientBase));
	return g_BountyClientBase;
}
