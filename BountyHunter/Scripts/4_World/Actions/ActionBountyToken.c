class ActionBountyTokenCB : ActionContinuousBaseCB
{
	private const float TIME_SEC = 2.0;

	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(TIME_SEC);
	}
}

class ActionBountyToken: ActionContinuousBase
{
	void ActionBountyToken()
	{
		m_CallbackClass = ActionBountyTokenCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENITEM;
		m_CommandUIDProne = DayZPlayerConstants.CMD_ACTIONMOD_OPENITEM;
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_LOW;
	}

	override bool HasProneException()
	{
		return true;
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem		= new CCINone;
		m_ConditionTarget 	= new CCTNone;
	}

	override bool HasTarget()
	{
		return false;
	}

	override bool RemoveForceTargetAfterUse()
	{
		return false;
	}

	override string GetText()
	{
		return "Use";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return true;
	}

	override void OnFinishProgressServer( ActionData action_data )
	{
		PlayerIdentity PID = action_data.m_Player.GetIdentity();
		BountyToken token = BountyToken.Cast( action_data.m_MainItem );
		if ( token )
		{
			GetRPCManager().SendRPC( "BountyRpcs", "DisplayBountyToken", new Param2< Object, EntityAI >( token, action_data.m_Player), true, PID );
		}
	}
}
