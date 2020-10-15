class CfgPatches
{
    class Master_Scripts
    {
        units[]={};
        weapons[]={};
        requiredVersion=0.1;
        requiredAddons[]=
        {
            "DZ_Data"
        };
    };
};

class CfgMods
{
	class Master
	{
		dir = "hlynge/Master";
		picture = "";
		action = "";
		hideName = 0;
		hidePicture = 1;
		name = "Master";
		credits = "hlynge";
		creditsJson = "hlynge/Master/Scripts/Data/Credits.json";
		author = "hlynge";
		authorID = "0"; 
		version = "0.1"; 
		extra = 0;
		type = "mod";
		
		dependencies[] = { "Game", "World", "Mission" };
		
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"hlynge/Master/Scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"hlynge/Master/Scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"hlynge/Master/Scripts/5_Mission"};
			};
		};
	};
};