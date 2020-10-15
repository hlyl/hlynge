modded class MissionGameplay
{
	void MissionGameplay()
    {
 		GetBhBase();
    }

	override void OnInit()
    {
        super.OnInit();
    }


	override void OnKeyPress( int key ) {
		super.OnKeyPress( key );
		GetBhBase().OnKeyPress(key);
	}

	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
		
		UAInput bountyKey = GetUApi().GetInputByName("UAToggleBounty");

		if(bountyKey.LocalClick())
		{
			GetBhBase().ShowBountyMenuKey();
		}
		
		UAInput bountyMapKey = GetUApi().GetInputByName("UAToggleBountyMap");

		if(bountyMapKey.LocalClick())
		{
			GetBhBase().ShowBountyMapKey();
		}

	
	}		
}


