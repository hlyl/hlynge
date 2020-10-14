class CfgPatches
{
    class Editor_Scripts
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
	class DayZEditor
	{
		dir = "hlynge/DayZEditor";
		picture = "";
		action = "";
		hideName = 0;
		hidePicture = 1;
		name = "Example";
		credits = "Jacob_Mango, Arkensor";
		creditsJson = "hlynge/DayZEditor/Scripts/Data/Credits.json";
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
				files[] = {"hlynge/DayZEditor/Scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"hlynge/DayZEditor/Scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"hlynge/DayZEditor/Scripts/5_Mission"};
			};
		};
	};
};