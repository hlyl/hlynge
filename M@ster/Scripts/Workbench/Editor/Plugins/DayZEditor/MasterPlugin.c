[WorkbenchPluginAttribute("-> Deploy Mod", "Deploys the active loaded mod", "alt+1", "", {"ResourceManager", "ScriptEditor"})]
class DeployModTool: DayZTool
{
	string BatchFile;

	void DeployModTool()
	{
		BatchFile = GetWorkDriveDirectory() + "Batchfiles\\Deploy.bat";
	}
	
	override void Run()
	{
		RunDayZBat(BatchFile, true);
	}
}

[WorkbenchPluginAttribute("-> Kill it", "Kill Dayz Tasks", "ctrl+3", "", {"ResourceManager", "ScriptEditor"})]
class KillModTool: DayZTool
{
	string BatchFile;

	void KillModTool()
	{
		BatchFile = GetWorkDriveDirectory() + "Batchfiles\\Exit.bat";
	}
	
	override void Run()
	{
		RunDayZBat(BatchFile, true);
	}
}


[WorkbenchPluginAttribute("-> Update Version", "Updates the mod version", "alt+5", "", {"ResourceManager", "ScriptEditor"})]
class UpdateVersionModTool: DayZTool
{
	string BatchFile;

	void UpdateVersionModTool()
	{
		BatchFile = GetWorkDriveDirectory() + "Batchfiles\\UpdateVersion.bat";
	}		
	override void Run()
	{
		RunDayZBat(BatchFile, true);
	}
}

[WorkbenchPluginAttribute("-> Launch Offline", "Launches the game in offline mode", "F5", "", {"ResourceManager", "ScriptEditor"})]
class LaunchOfflineModTool: DayZProjectManager
{
	string BatchFile;
	string BatchFile1;
	void LaunchOfflineModTool()
	{
		BatchFile = GetWorkDriveDirectory() + "Batchfiles\\Exit.bat";
		BatchFile = GetWorkDriveDirectory() + "Batchfiles\\LaunchOffline.bat";
	}		
	override void Run()
	{
		RunDayZBat(BatchFile, true);
		RunDayZBat(BatchFile1, true);
	}	
}

[WorkbenchPluginAttribute("-> Open Log Files", "Opens logfiles in NPP", "F4", "", {"ResourceManager", "ScriptEditor"})]
class OpenLogFiles: DayZProjectManager
{
	
	override void Run()
	{
		RunDayZBat("P:\\openlogs.bat", true);
	}
}

[WorkbenchPluginAttribute("-> Build Mod", "Builds current mod", "F8", "", {"ResourceManager", "ScriptEditor"})]
class BuildMod: DayZProjectManager
{
	string BatchFile;
	string BatchFile1;

	void BuildMod()
	{
		BatchFile = GetWorkDriveDirectory() + "Batchfiles\\Exit.bat";
		BatchFile = GetWorkDriveDirectory() + "Batchfiles\\ZBinarizeDeploy.bat";
	}
	
	override void Run()
	{
		RunDayZBat(BatchFile, true);
		RunDayZBat(BatchFile1, true);
	}	

}

[WorkbenchPluginAttribute("-> Build Mod + Offline", "Builds and launch current mod", "Ctrl+F8", "", {"ResourceManager", "ScriptEditor"})]
class BuildModAndLaunch: DayZProjectManager
{
	string BatchFile;
	string BatchFile1;
	string BatchFile2;
	
	void BuildModAndLaunch()
	{
		BatchFile = GetWorkDriveDirectory() + "Batchfiles\\Exit.bat";
		BatchFile1 = GetWorkDriveDirectory() + "Batchfiles\\ZBinarizeDeploy.bat";
		BatchFile2 = GetWorkDriveDirectory() + "Batchfiles\\LaunchOffline.bat";
	}
	
	override void Run()
	{
		RunDayZBat(BatchFile, true);
		RunDayZBat(BatchFile1, true);
		RunDayZBat(BatchFile2, true);
	}
}

[WorkbenchPluginAttribute("-> Launch Server+Client", "Launches Server+Client", "Ctrl+F6", "", {"ResourceManager", "ScriptEditor"})]
class LaunchServerClient: DayZProjectManager
{
	string BatchFile;
	string BatchFile1;
	string BatchFile2;
	string BatchFile3;

	void LaunchServerClient()
	{
		BatchFile = GetWorkDriveDirectory() + "Batchfiles\\Exit.bat";
		BatchFile1 = GetWorkDriveDirectory() + "Batchfiles\\ZBinarizeDeploy.bat";
		BatchFile2 = GetWorkDriveDirectory() + "Batchfiles\\LaunchServer.bat";
		BatchFile3 = GetWorkDriveDirectory() + "Batchfiles\\LaunchLocalMP.bat";
	}
	
	override void Run()
	{
		RunDayZBat(BatchFile, true);
		RunDayZBat(BatchFile1, true);
		RunDayZBat(BatchFile2, true);
		RunDayZBat(BatchFile3, true);		
	}
}


[WorkbenchPluginAttribute("-> Edit Project", "Edit Project", "", "", {"ResourceManager", "ScriptEditor"})]
class DayZProjectManager: DayZTool
{
	[Attribute("", "editbox")]
	string Directory;
	
		
	override void Run()
	{
		Workbench.ScriptDialog("Edit Project Settings", "", this);
	}
	
	override void RunDayZBat(string filepath, bool wait = false)
	{
		if (filepath.Length() < 2) return;
		
		filepath.Replace("\\", "/");
		
		if (filepath[1] != ":")
		{
			string cwd;
			Workbench.GetCwd(cwd);
			filepath = cwd + "/" + filepath;
		}
		
		int index = filepath.IndexOf("/");
		int last_index = index;
		
		while(index != -1)
		{
			last_index = index;
			index = filepath.IndexOfFrom(last_index + 1, "/");
		}
		
		if (last_index == -1) return;
		
		string path = filepath.Substring(0, last_index);
		string bat = filepath.Substring(last_index + 1, filepath.Length() - last_index - 1);
		
		Print("cmd /c \"chdir /D " + path + " & call " + bat + "\"");
		Workbench.RunCmd("cmd /c \"chdir /D " + path + " & call " + bat + "\"", wait);
	}
	
	
	void RunDayZBatList(array<string> filepaths)
	{
		foreach (string file: filepaths) {
			RunDayZBat(file, true);
		}
	}
}


