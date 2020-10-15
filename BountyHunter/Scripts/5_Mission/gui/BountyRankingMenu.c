class BountyRankingMenu extends UIScriptedMenu 
{	
	ref ButtonWidget   m_btnexit;

	ref ButtonWidget   btn_info;

	ref TextListboxWidget  m_rankbox;

	ref array<string> m_playernames; 

	void BountyRankMenu()
	{

	}
	
	override bool OnClick( Widget w, int x, int y, int button )
	{
			super.OnClick(w, x, y, button);

		if ( w == m_btnexit )
		{
			if(BountyLogger.m_debug) BountyLogger.LogMessage("BountyRankMenu onClick() m_btnexit ");
			GetGame().GetUIManager().Back();			
			if(BountyLogger.m_debug) BountyLogger.LogMessage("BountyRankMenu onClick() Close ");
			return true;
		}

		if(w == btn_info)
		{
			GetGame().GetUIManager().Back();			
			GetBhBase().ShowBountyMenu();
			return true;
		}
		
		return false;
	
	}
	
	
	override Widget Init()
    {
		if(BountyLogger.m_debug) BountyLogger.LogMessage("BountyRankMenu Init() ");

        layoutRoot = GetGame().GetWorkspace().CreateWidgets("Bounty_fix/Scripts/5_Mission/gui/BountyRankingMenu.layout" );


		if(layoutRoot)
		{
			if(BountyLogger.m_debug) BountyLogger.LogMessage("BountyRankMenu Init() layout found ");

			m_btnexit = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_exit" ) );
			btn_info = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_info" ) );

			if(BountyLogger.m_debug) BountyLogger.LogMessage("BountyRankMenu Init() m_btnexit found ");

			m_rankbox = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("lb_players") );

			if(BountyLogger.m_debug) BountyLogger.LogMessage("BountyRankMenu Init() rankbox found ");

			 if(GetBhBase().m_bountyState && GetBhBase().m_bountyState.m_stats)
			 {
				 m_rankbox.ClearItems();
				 ref array<ref BountyStats>  stats =  GetBhBase().m_bountyState.m_stats;
				 for(int i = 0; i < stats.Count() ; i++)
				 {
					ref BountyStats sta = stats.Get(i);
					if(sta)
					{
						string pname = "" +  i + "." + sta.m_name;
						m_rankbox.AddItem( sta.m_name  , 	NULL, 0 );	
						m_rankbox.SetItem( i, "" + sta.m_bountyKills , 		NULL, 1 );
						m_rankbox.SetItem( i, "" + sta.m_bountyDeaths, 		NULL, 2 );
						m_rankbox.SetItem( i, "" + sta.m_bountySurvived, 	NULL, 3 );
						m_rankbox.SetItem( i, "" + sta.m_points, 			NULL, 4 );

				
						if(sta.m_isonline)
						{
							m_rankbox.SetItemColor(i, 0, ARGBF(1, 0, 1, 0)  );
							m_rankbox.SetItemColor(i, 1, ARGBF(1, 0, 1, 0)  );
							m_rankbox.SetItemColor(i, 2, ARGBF(1, 0, 1, 0)  );
							m_rankbox.SetItemColor(i, 3, ARGBF(1, 0, 1, 0)  );
							m_rankbox.SetItemColor(i, 4, ARGBF(1, 0, 1, 0)  );
						}
					}
					
					
					
				 }
			 }


			if(BountyLogger.m_debug) BountyLogger.LogMessage("BountyRankMenu Init() Exit ");
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