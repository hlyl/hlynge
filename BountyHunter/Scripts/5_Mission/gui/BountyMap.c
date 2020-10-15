//################################################################################################################################################################
//####  Made by hlynge - August 2019
//################################################################################################################################################################


class BountyMap extends UIScriptedMenu 
{	
	ref ButtonWidget   m_btnexit;
	ref ButtonWidget   btn_info;

	ref MapWidget m_MapWidget;
	
	void BountyMap()
	{

	}
	
	override bool OnClick( Widget w, int x, int y, int button )
	{
			super.OnClick(w, x, y, button);

	if ( w == m_btnexit )
		{
			if(BountyLogger.m_debug) BountyLogger.LogMessage("BountyMap onClick() m_btnexit ");
			GetGame().GetUIManager().Back();			
			if(BountyLogger.m_debug) BountyLogger.LogMessage("BountyMap onClick() Close ");
			return true;
		}

		if(w == btn_info)
		{
			GetGame().GetUIManager().Back();			
			GetBhBase().ShowBountyMenu();
		}
		
		return false;
	
	}
	
	
	override Widget Init()
    {
		if(BountyLogger.m_debug) BountyLogger.LogMessage("BountyMap Init() ");

        layoutRoot = GetGame().GetWorkspace().CreateWidgets( "Bounty_fix/Scripts/5_Mission/gui/BountyMap.layout" );


		if(layoutRoot)
		{
			if(BountyLogger.m_debug) BountyLogger.LogMessage("BountyMap Init() layout found ");

			m_btnexit = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_exit" ) );
			btn_info = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "btn_info" ) );
 			m_MapWidget = MapWidget.Cast( layoutRoot.FindAnyWidget( "MapWidget" ) );
			
			for(int i = 0 ; i <  GetBhBase().m_bountyState.m_lastpos.Count(); i++)
			{
				
				
				vector vect = GetBhBase().m_bountyState.m_lastpos.Get(i);
				m_MapWidget.AddUserMark(vect , "-" + GetBhBase().m_bountyState.m_playername  , ARGB(255,204,0,0), "\\dz\\gear\\navigation\\data\\map_church_ca.paa");
			}

			
			if(BountyLogger.m_debug) BountyLogger.LogMessage("BountyMap Init() Exit ");
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