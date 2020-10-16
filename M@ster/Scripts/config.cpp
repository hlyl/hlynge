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
		dir = "M@ster";
		picture = "";
		action = "";
		hideName = 0;
		hidePicture = 1;
		name = "Example";
		credits = "Jacob_Mango, Arkensor";
		creditsJson = "M@ster/Scripts/Data/Credits.json";
		author = "Jacob_Mango, Arkensor";
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
				files[] = {"M@ster/Scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"M@ster/Scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"M@ster/Scripts/5_Mission"};
			};
		};
	};
};