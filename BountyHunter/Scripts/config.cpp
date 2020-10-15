class CfgPatches
{
	class BountyHunter
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"JM_CF_Scripts"
		};
	};
};
class CfgMods
{
	class BountyHunter
	{
		
		inputs="hlynge/BountyHunter/Scripts/Data/Inputs.xml";		
		dir="Bounty_fix";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="BountyHunter";
		credits="hlynge";
		author="hlynge";
		authorID="0";
		version="1.0";
		extra=0;
		type="mod";
		dependencies[]=
		{
			"Game",
			"Mission",
			"World"
		};
		class defs
		{
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"hlynge/BountyHunter/Scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"hlynge/BountyHunter/Scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"hlynge/BountyHunter/Scripts/5_Mission"
				};
			};
		};
	};
};
class CfgVehicles
{
	class Inventory_Base;
	class BountyToken: Inventory_Base
	{
		scope=2;
		displayName="Bounty Token";
		descriptionShort="Start a bounty hunt.";
		model="\dz\gear\consumables\Paper.p3d";
		isMeleeWeapon=1;
		weight=2;
		absorbency=1;
		rotationFlags=16;
		itemSize[]={1,1};
		inventorySlot="Paper";
		lootTag[]=
		{
			"Civilian",
			"Office"
		};
		lootCategory="Materials";
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\gear\consumables\data\Loot_Paper.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\gear\consumables\data\Loot_Paper.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\gear\consumables\data\Loot_Paper_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\gear\consumables\data\Loot_Paper_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\gear\consumables\data\Loot_Paper_destruct.rvmat"
							}
						}
					};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem
				{
					soundSet="pickUpPaper_SoundSet";
					id=797;
				};
			};
		};
	};
};
