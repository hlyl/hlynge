class CfgPatches
{
    class M@ster_Scripts
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
	class M@ster
	{
		dir = "hlynge/M@ster";
		picture = "";
		action = "";
		hideName = 0;
		hidePicture = 1;
		name = "M@ster";
		credits = "hlynge";
		creditsJson = "hlynge/M@ster/Scripts/Data/Credits.json";
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
				files[] = {"hlynge/M@ster/Scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"hlynge/M@ster/Scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"hlynge/M@ster/Scripts/5_Mission"};
			};
		};
	};
};