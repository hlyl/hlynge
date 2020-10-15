class BountyToken extends ItemBase
{
	void BountyToken()
	{
		//m_AdvancedText = NULL;
	}

	void ~BountyToken()
	{
	}

	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionBountyToken);
	}
}
