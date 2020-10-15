//################################################################################################################################################################
//####  Made by hlynge - August 2019
//################################################################################################################################################################


class BountyAdminMenu extends UIScriptedMenu
{
	ref TextListboxWidget lst_PlayerList;
	ref ButtonWidget    btn_exit;
	ref ButtonWidget    btn_info;
	ref ButtonWidget    btn_permasave;
	ref ButtonWidget	btn_tempsave;
	ref ButtonWidget    btn_starthunt;
	ref ButtonWidget    btn_forcestart;
	ref ButtonWidget    btn_forceend;
	ref ButtonWidget	btn_endhunt;
	ref ButtonWidget 	btn_reloadSettings;
	ref ButtonWidget 	btn_forceselect;

    ref CheckBoxWidget cb_bountyactive;
	ref CheckBoxWidget cb_spandeadbountyaszombie;
	ref CheckBoxWidget cb_rewardbounty;


	ref EditBoxWidget  txt_bountyIntervall;
	ref EditBoxWidget  txt_hunttime;
	ref EditBoxWidget  txt_minplayers;
	ref EditBoxWidget  txt_rewardcontainer;
	ref EditBoxWidget  txt_showhuntpos;
	ref EditBoxWidget  txt_xhuntzone;
	ref EditBoxWidget  txt_huntzoney;
	ref EditBoxWidget  txt_huntposintervall;

	ref BountySetting m_settings;
	static int color_good	=	0xFF2ECC71;
	static int color_bad	= 0xFFF22613;
	bool executeOnce = true;


	void BountyAdminMenu(ref BountySetting settings)
	{
			m_settings = settings;
	}

	override bool OnClick( Widget w, int x, int y, int button )
	{
		super.OnClick(w, x, y, button);

		if ( w == btn_exit )
		{
			if(BountyLogger.m_debug) BountyLogger.LogMessage("BountyAdminMenu onClick() btn_exit ");
			GetGame().GetUIManager().Back();
			if(BountyLogger.m_debug) BountyLogger.LogMessage("BountyAdminMenu onClick() Close ");
			return true;
		}

		if(w == btn_info)
		{
			GetBhBase().CloseAllMenus();
			GetGame().GetUIManager().Back();
			return true;
		}

		if(w == btn_permasave || w == btn_tempsave)
		{
			ref BountySetting  m_settings = new ref BountySetting();
			m_settings.m_Interval = txt_bountyIntervall.GetText().ToFloat();
			m_settings.m_ShowBountyPosition = txt_huntposintervall.GetText().ToFloat();
			m_settings.m_MinPlayers = txt_minplayers.GetText().ToInt();
			m_settings.m_MaxBountyHuntTime = txt_hunttime.GetText().ToInt();
			m_settings.m_rewardContainer = txt_rewardcontainer.GetText();
			m_settings.m_SpawnBountyPlayerAsZombie = cb_spandeadbountyaszombie.IsChecked();
			m_settings.m_RewardBountyPlayerAlive = cb_rewardbounty.IsChecked();
			m_settings.m_HideBountyPossitionLessThan = txt_showhuntpos.GetText().ToInt();
			m_settings.m_huntzoneY = txt_huntzoney.GetText().ToFloat();
			m_settings.m_huntzoneX = txt_xhuntzone.GetText().ToFloat();
			m_settings.m_bountyactive = cb_bountyactive.IsChecked();

			if(w == btn_permasave)
				m_settings.m_premasave = true;

			GetRPCManager().SendRPC( "BountyRpcs", "RpcSaveSettings", new Param1<ref BountySetting> ( m_settings ) );
			GetGame().GetUIManager().Back();
			return true;
		}

		if(w == btn_forceend)
			GetRPCManager().SendRPC( "BountyRpcs", "RpcForceEndHunt", null);

		if(w == btn_forcestart)
			GetRPCManager().SendRPC( "BountyRpcs", "RpcForceStartHunt",null);

		if(w == btn_endhunt)
			GetRPCManager().SendRPC( "BountyRpcs", "RpcEndHunt",null);

		if(w == btn_starthunt)
			GetRPCManager().SendRPC( "BountyRpcs", "RpcStartHunt",null);

		if(w == btn_forceselect)
		{
			int row = lst_PlayerList.GetSelectedRow();
			string selectedPlayer;
			lst_PlayerList.GetItemText(row, 0, selectedPlayer);
			GetRPCManager().SendRPC( "BountyRpcs", "RpcForceStartHuntSelected", new Param1<string> ( selectedPlayer ) );
		}

		if(w == btn_reloadSettings)
		{
			GetRPCManager().SendRPC( "BountyRpcs", "RpcReloadSettings",null);
			GetGame().GetUIManager().Back();
		}
		return true;
	}


	override Widget Init()
  {
		if(BountyLogger.m_debug) BountyLogger.LogMessage("BountyAdminMenu Init() ");

        layoutRoot = GetGame().GetWorkspace().CreateWidgets( "Bounty_fix/Scripts/5_Mission/gui/BountyAdminMenu.layout" );


		if(layoutRoot)
		{
			if(BountyLogger.m_debug) BountyLogger.LogMessage("BountyAdminMenu Init() layout found ");

			lst_PlayerList = TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "lst_players" ) );

			btn_exit = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_exit" ) );
			btn_info =    ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_info") );
			btn_permasave =     ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_permasave") );
			btn_tempsave =	ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_tempsave") );

			btn_starthunt = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_starthunt" ) );
			btn_forceend =    ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_forceend") );
			btn_forcestart =     ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_forcestart") );
			btn_endhunt =	ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_endhunt") );
			btn_reloadSettings = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_reloadSettings") );
			btn_forceselect = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_forceselect") );

			cb_spandeadbountyaszombie = CheckBoxWidget.Cast( layoutRoot.FindAnyWidget( "cb_spandeadbountyaszombie") );
			cb_rewardbounty = CheckBoxWidget.Cast( layoutRoot.FindAnyWidget( "cb_rewardbounty") );
			cb_bountyactive = CheckBoxWidget.Cast( layoutRoot.FindAnyWidget( "cb_bountyactive") );

			txt_bountyIntervall = EditBoxWidget .Cast( layoutRoot.FindAnyWidget( "txt_bountyIntervall" ) );
			txt_hunttime = EditBoxWidget .Cast( layoutRoot.FindAnyWidget( "txt_hunttime" ) );
			txt_minplayers = EditBoxWidget .Cast( layoutRoot.FindAnyWidget( "txt_minplayers" ) );
			txt_rewardcontainer = EditBoxWidget .Cast( layoutRoot.FindAnyWidget( "txt_rewardcontainer" ) );
			txt_showhuntpos = EditBoxWidget .Cast( layoutRoot.FindAnyWidget( "txt_showhuntpos" ) );
			txt_xhuntzone = EditBoxWidget .Cast( layoutRoot.FindAnyWidget( "txt_xhuntzone" ) );
			txt_huntzoney = EditBoxWidget .Cast( layoutRoot.FindAnyWidget( "txt_huntzoney" ) );
			txt_huntposintervall = EditBoxWidget .Cast( layoutRoot.FindAnyWidget( "txt_huntposintervall" ) );


			cb_bountyactive.SetChecked( m_settings.m_bountyactive);
			txt_bountyIntervall.SetText(m_settings.m_Interval.ToString());
			txt_huntposintervall.SetText( m_settings.m_ShowBountyPosition.ToString());
			txt_minplayers.SetText( m_settings.m_MinPlayers.ToString());
			txt_hunttime.SetText( m_settings.m_MaxBountyHuntTime.ToString());
			txt_rewardcontainer.SetText( m_settings.m_rewardContainer);
			cb_spandeadbountyaszombie.SetChecked( m_settings.m_SpawnBountyPlayerAsZombie);
			cb_rewardbounty.SetChecked( m_settings.m_RewardBountyPlayerAlive);
			txt_showhuntpos.SetText( m_settings.m_HideBountyPossitionLessThan.ToString());
			txt_huntzoney.SetText( m_settings.m_huntzoneY.ToString());
			txt_xhuntzone.SetText( m_settings.m_huntzoneX.ToString());

			if(BountyLogger.m_debug) BountyLogger.LogMessage("BountyAdminMenu Init() Exit ");
			return layoutRoot;
		}

		return null;
	}


   override void OnShow()
	{
		super.OnShow();
		GetGame().GetInput().ChangeGameFocus(1);
		GetGame().GetMission().GetHud().Show(false);

		PlayerBase pl = PlayerBase.Cast(GetGame().GetPlayer());
		PlayerIdentity Player_Id = pl.GetIdentity();
		GetRPCManager().SendRPC( "BountyRpcs", "RpcBountyGetPlayersActive", new Param1<bool> (false));
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

		if (isSignedUp)
		{
			lst_PlayerList.SetItemColor(line, 0, color_good );
		}
		else
		{
			lst_PlayerList.SetItemColor(line, 0, color_bad );
		}
		if (executeOnce)
		{
			lst_PlayerList.SelectRow(0);
			executeOnce = false;
		}
	}
}
