//################################################################################################################################################################
//####  written by theothergun (c) 2019
//################################################################################################################################################################


class BountyMenu extends UIScriptedMenu 
{	
	ref ButtonWidget   m_btnexit;
	
	ref CheckBoxWidget cb_active;

    ref ProgressBarWidget prg_timeleft;
    ref ProgressBarWidget prg_currblood;
    ref ProgressBarWidget prg_currhealth;


	ref TextWidget txt_timeleft;
    ref TextWidget txt_playername;
    ref TextWidget txt_position;
    ref TextWidget txt_weapon;
	ref TextWidget txt_healtpercent;
	ref TextWidget txt_bloodpercent;
	
	ref TextWidget txt_info;

	ref ButtonWidget btn_admincmd;
	ref ButtonWidget   btn_ranking;
	ref ButtonWidget   btn_map;

	void BountyMenu()
	{

	}
	
	override bool OnClick( Widget w, int x, int y, int button )
	{
			super.OnClick(w, x, y, button);

		if ( w == m_btnexit )
		{
			if(BountyLogger.m_debug) BountyLogger.LogMessage("BountyMenu onClick() m_btnexit ");

			GetGame().GetUIManager().Back();			
			if(BountyLogger.m_debug) BountyLogger.LogMessage("BountyMenu onClick() Close ");
				return true;
		}
		
		if(w == cb_active)
		{
			PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
			player.m_bounty_player_active = cb_active.IsChecked();
			GetRPCManager().SendRPC( "BountyRpcs", "RpcBountyPlayerActive", new Param1<bool> (player.m_bounty_player_active   ) );
			return true;
		}

		if(w == btn_admincmd)
		{
			GetBhBase().CloseAllMenus();
			GetBhBase().ShowAdminMenu();
			return true;
		}
		
		if(w == btn_ranking)
		{
			GetBhBase().CloseAllMenus();
			GetBhBase().ShowRankingMenu();
			return true;
		}
		
		if(w == btn_map)
		{
			GetBhBase().CloseAllMenus();
			GetBhBase().ShowMapMenu();
			return true;
		}
		
		return false;
	
	}
	
	
	override Widget Init()
    {
		if(BountyLogger.m_debug) BountyLogger.LogMessage("BountyMenu Init() ");

        layoutRoot = GetGame().GetWorkspace().CreateWidgets( "Bounty_fix/Scripts/5_Mission/gui/BountyMenu.layout" );


		if(layoutRoot)
		{
			if(BountyLogger.m_debug) BountyLogger.LogMessage("BountyMenu Init() layout found ");

			cb_active = CheckBoxWidget.Cast( layoutRoot.FindAnyWidget( "cb_active" ) );
		
			
			m_btnexit = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_exit" ) );
			btn_ranking= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_ranking" ) );
			
			btn_map= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_map" ) );
			
			PlayerBase plbase = PlayerBase.Cast(GetGame().GetPlayer());
			
			if(!plbase)
				return layoutRoot;
			
			cb_active.SetChecked(plbase.m_bounty_player_active);
			
			btn_map.Show(plbase.m_bounty_player_active_for_current);
			
			txt_timeleft = TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_timeleft" ) );
			
        	txt_playername = TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_playername" ) );
			txt_playername.Show(plbase.m_bounty_player_active_for_current);
        	txt_position = TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_position" ) );
			txt_position.Show(plbase.m_bounty_player_active_for_current);
        	txt_weapon = TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_weapon" ) );
			txt_weapon.Show(plbase.m_bounty_player_active_for_current);
			
			txt_info= TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_info" ) );
			
	  		txt_healtpercent = TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_healtpercent" ) );
			txt_healtpercent.Show(plbase.m_bounty_player_active_for_current);
	  		txt_bloodpercent = TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_bloodpercent" ) );
			txt_bloodpercent.Show(plbase.m_bounty_player_active_for_current);


        	prg_timeleft = ProgressBarWidget.Cast( layoutRoot.FindAnyWidget( "prg_timeleft" ) );
        	prg_currblood  = ProgressBarWidget.Cast( layoutRoot.FindAnyWidget( "prg_currblood" ) );
			prg_currblood.Show(plbase.m_bounty_player_active_for_current);

        	prg_currhealth  = ProgressBarWidget.Cast( layoutRoot.FindAnyWidget( "prg_currhealth" ) );
			prg_currhealth.Show(plbase.m_bounty_player_active_for_current);

			if(plbase.m_bounty_player_active_for_current)
			{
				prg_currblood.SetCurrent(GetBhBase().m_bountyState.m_currblood);
				prg_currhealth.SetCurrent(GetBhBase().m_bountyState.m_currhealth);
				txt_playername.SetText(  GetBhBase().m_bountyState.m_playername);
				txt_position.SetText( GetBhBase().m_bountyState.m_lastseen);
				txt_weapon.SetText( GetBhBase().m_bountyState.m_weaponinhands);
				txt_healtpercent.SetText( "" + GetBhBase().m_bountyState.m_currhealth + "%");
				txt_bloodpercent.SetText( "" + GetBhBase().m_bountyState.m_currblood + "%");
				txt_timeleft.SetText("Bountyhunt Active : " + GetBhBase().m_bountyState.m_timeleft + " left.");
			}
			else
			{
				txt_playername.SetText(  "-");
				txt_position.SetText("-");
				txt_weapon.SetText( "-");
				txt_timeleft.SetText("You are not a valid Hunter. Please wait : " + GetBhBase().m_bountyState.m_timeleft);
			}
			
			if(GetBhBase().m_bountyState.m_lastpos.Count() == 0)
				txt_timeleft.SetText("Waiting for next Hunt. Please wait : " + GetBhBase().m_bountyState.m_timeleft);				
			

			prg_timeleft.SetCurrent(GetBhBase().m_bountyState.m_progress);
	
			
			

			if((!GetBhBase().m_settings.m_showbountyonmap || GetBhBase().m_bountyState.m_lastpos.Count() == 0) && plbase.m_bounty_player_active_for_current)
			{
				btn_map.Show(false);
			}
			else{
				btn_map.Show(true);
			}
			
			
			if( GetBhBase().m_isAdmin)
			{
	  			btn_admincmd = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_admincmd" ) );
				btn_admincmd.Show(true);
			}

 
			if(BountyLogger.m_debug) BountyLogger.LogMessage("BountyMenu Init() Exit ");
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
	
}