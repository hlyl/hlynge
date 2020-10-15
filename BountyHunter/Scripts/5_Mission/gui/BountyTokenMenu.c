class BountyTokenMenu extends UIScriptedMenu
{
	ref TextListboxWidget lst_PlayerList;
	ref ButtonWidget    btn_exit;
	ref ButtonWidget    btn_start;

	ItemBase m_token;
	static int color_good	=	0xFF2ECC71;
	static int color_bad	= 0xFFF22613;
	bool executeOnce = true;


	void BountyTokenMenu(ItemBase tokenItem)
	{
			m_token = tokenItem;
	}

	override bool OnClick( Widget w, int x, int y, int button )
	{
		super.OnClick(w, x, y, button);

		if ( w == btn_exit )
		{
			if(BountyLogger.m_debug) BountyLogger.LogMessage("BountyTokenMenu onClick() btn_exit ");
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(GetBhBase().CloseAllMenus, 500, false);
			if(BountyLogger.m_debug) BountyLogger.LogMessage("BountyTokenMenu onClick() Close ");
			return true;
		}
		if(w == btn_start)
		{
			int row = lst_PlayerList.GetSelectedRow();
			string selectedPlayer;
			lst_PlayerList.GetItemText(row, 0, selectedPlayer);
			GetRPCManager().SendRPC( "BountyRpcs", "RpcForceStartHuntSelected", new Param1<string> ( selectedPlayer ) );
			GetRPCManager().SendRPC( "BountyRpcs", "RpcDeleteToken", new Param1<Object> ( m_token ) );
			if(BountyLogger.m_debug) BountyLogger.LogMessage("BountyTokenMenu onClick() btn_start ");
			if(BountyLogger.m_debug) BountyLogger.LogMessage("BountyTokenMenu onClick() Close ");
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(GetBhBase().CloseAllMenus, 500, false);
		}
		return true;
	}


	override Widget Init()
  {
		if(BountyLogger.m_debug) BountyLogger.LogMessage("BountyTokenMenu Init() ");

    layoutRoot = GetGame().GetWorkspace().CreateWidgets( "Bounty_fix/Scripts/5_Mission/gui/BountyTokenMenu.layout" );
		if(layoutRoot)
		{
			if(BountyLogger.m_debug) BountyLogger.LogMessage("BountyTokenMenu Init() layout found ");
			lst_PlayerList = TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "lst_players" ) );
			btn_exit = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_exit" ) );
			btn_start = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_start" ) );
			if(BountyLogger.m_debug) BountyLogger.LogMessage("BountyTokenMenu Init() Exit ");
			PlayerBase pl = PlayerBase.Cast(GetGame().GetPlayer());
			PlayerIdentity Player_Id = pl.GetIdentity();
			GetRPCManager().SendRPC( "BountyRpcs", "RpcBountyGetPlayersActive", new Param1<bool> (true));
			return layoutRoot;
		}
		return null;
	}

   override void OnShow()
	{
		super.OnShow();
		GetGame().GetInput().ChangeGameFocus(1);
		GetGame().GetMission().GetHud().Show(false);
	}

	override void OnHide()
	{
		super.OnHide();
		GetGame().GetInput().ResetGameFocus();
		GetGame().GetMission().GetHud().Show(true);
		Close();
	}

	override bool UseMouse()
	{
		return true;
	}

	void AddPlayer(string pName, bool isSignedUp)
	{
		int line = lst_PlayerList.AddItem(pName, NULL, 0);

		// DO NOT INDICATE WHO IS SIGNED UP OR NOT FOR NORMAL PLAYER:
		/*if (isSignedUp)
		{
			lst_PlayerList.SetItemColor(line, 0, color_good );
		}
		else
		{
			lst_PlayerList.SetItemColor(line, 0, color_bad );
		}*/
		if (executeOnce)
		{
			lst_PlayerList.SelectRow(0);
			executeOnce = false;
		}
	}
}
