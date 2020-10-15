//################################################################################################################################################################
//####  Made by hlynge - August 2019
//################################################################################################################################################################


class BountySetting
{
	string m_text_BountyDistanceToHunter =  "The Bounty is ##distance## m away from you come closer and get it.";
	string m_text_NearEnemys = "There are ##players## nearby be careful";
	string m_text_NewBountyBegin = "New Bounty Hunt begins. Find the Bounty! Bounty Player : ##player##";
	string m_text_BountyEndElapsedTimeSendReward = "The Hunt ends, Player ##player## is still alive and will get the reward";
	string m_text_BountySuicide = "The Hunt ends, Huntedplayer left us by suicide :-(";
	string m_text_BountyKilledByInfected = "The Hunt ends, Bounty Player was killed by infected";
	string m_text_BountyLeftGame = "The Hunt ends, Bounty Player left the game or maybe... his game crashed.";
	string m_text_BountyForbiddenArea = "You are in a forbidden area while hunted.. You get Teleported";
	string m_text_BountyIsKilled = "The Bounty Hunt is over, we got a winner -> ##player##";
	string m_text_BountyInfo = "Target ##player## he is ##distance## m away from ##location##. Get him!";
	string m_text_BountyPlayerIsBack = "Bounty player is back, the hunt can go on.";
	string m_text_BountyPlayerIsDisconnected = "Bounty player is disconnected, waiting for reconnect.";
	string m_version = "1.2";
	
	int m_bountyposqueue = 10;
	
	int m_timetoreconnect = 350;
	
	bool m_showbountyonmap = true;	
	
	bool m_debug = false;
	
	float m_Interval = 15.0; // Time in minutes from server start for first hunt

	float m_ShowBountyPosition = 5.0;
	
	int m_MinPlayers = 10;
	
	int m_MaxBountyHuntTime = 60; //max time a hunt exists in minutes

	bool m_RewardBountyPlayerAlive = true;
	
	bool m_SpawnBountyPlayerAsZombie = true;
	
	bool m_premasave = false;

	bool m_bountyactive = true;	

	string m_rewardContainer = "SeaChest";
	
	int m_HideBountyPossitionLessThan = 100;
	float m_huntzoneY = 3100;
	float m_huntzoneX = 12000; 
	
	int m_points_survivepoints = 10;
	int m_points_killpoints = 25;
	int m_points_deathpoints = -5;
	int m_points_leavepoints = -25;
	
	
	
	ref array<string> m_admins = new ref array<string>();

	ref array<ref BountyLocation> m_forbiddenarea = {
		new BountyLocation(3724,-1, 5997, "Green Mountain"),
		new BountyLocation(8434,-1, 6668, "Guglovo"),
	};

	ref array<ref BountyLocation> m_locations = {
		new BountyLocation(1656, -1 , 14000, "Tisy Military"),
		new BountyLocation(7883,-1 , 14670, "Troitskoe Military"),
		new BountyLocation(4524,-1 , 8273, "Vybor Military"),
		new BountyLocation(4022,-1 , 11769, "NW Airfield North"),
		new BountyLocation(4916,-1 , 9614, "NW Airfield North"),
		new BountyLocation(1152,-1 , 7209, "Myshkino Tents"),
		new BountyLocation(2165,-1 , 3350, "Pavlovo Military"),
		new BountyLocation(3724, -1 ,5997, "Green Mountain"),	
        new BountyLocation(4500,-1 , 2500, "Balota"),
		new BountyLocation(100,-1 , 800, "Belaya Polana"),
		new BountyLocation(12000,-1 , 9000, "Berezino"),
		new BountyLocation(2600,-1 , 5200, "Zelenogorsk"),
		new BountyLocation(15169,-1 , 13824, "Berezhki"),
		new BountyLocation(1570,-1 , 8936, "Bogatyrka"),
		new BountyLocation(3261,-1 , 3941, "Bor"),
		new BountyLocation(12120,-1 , 13715, "Chernaya Polana"),
		new BountyLocation(6454,-1 , 2560, "Chernogorsk"),
		new BountyLocation(12915,-1 , 15060, "Dobroe"),
		new BountyLocation(11350,-1 , 6593, "Dolina"),
		new BountyLocation(3394,-1 , 4928, "Drozhino"),
		new BountyLocation(6647,-1 , 3567, "Dubky"),
		new BountyLocation(10448,-1 , 9828, "Dubrovka"),
		new BountyLocation(10350,-1 , 2124, "Elektrozavodsk"),
		new BountyLocation(9600,-1 , 8800, "Gorka"),
		new BountyLocation(5976,-1 , 10312, "Grishino"),
		new BountyLocation(8434,-1 , 6668, "Guglovo"),
		new BountyLocation(8560,-1 , 11883, "Gvozdno"),
		new BountyLocation(5309,-1 , 8611, "Kabanino"),
		new BountyLocation(1866,-1 , 2245, "Kamenka"),
		new BountyLocation(6672,-1 , 14480, "Kamensk"),
		new BountyLocation(12067,-1 , 3509, "Kamyshovo"),
		new BountyLocation(12661,-1 , 14695, "Karmanovka"),
		new BountyLocation(12321,-1 , 10818, "Khelm"),
		new BountyLocation(3645,-1 , 2482, "Komarovo"),
		new BountyLocation(4434,-1 , 4629, "Kozlovka"),
		new BountyLocation(6441,-1 , 14985, "Krasnoe"),
		new BountyLocation(11177,-1 , 12250, "Krasnostav"),
		new BountyLocation(2756,-1 , 9980, "Lopatino"),
		new BountyLocation(7990,-1 , 13044, "Mamino"),
		new BountyLocation(7555,-1 , 5150, "Mogilevka"),
		new BountyLocation(11304,-1 , 5469, "Msta"),
		new BountyLocation(2017,-1 , 7316, "Myshkino"),
		new BountyLocation(5850,-1 , 4763, "Nadezhdino"),
		new BountyLocation(9338,-1 , 14557, "Nagornoe"),
		new BountyLocation(12857,-1 , 8050, "Nizhnoye"),
		new BountyLocation(3384,-1 , 13042, "Novaya Petrovka"),
		new BountyLocation(11601,-1 , 14427, "Novodmitrovsk"),
		new BountyLocation(6140,-1 , 3250, "Novoselky"),
		new BountyLocation(7104,-1 , 7690, "Novy Sobor"),
		new BountyLocation(13343,-1 , 12898, "Olsha"),
		new BountyLocation(12090,-1 , 7035, "Orlovets"),
		new BountyLocation(1685,-1 , 3822, "Pavlovo"),
		new BountyLocation(4463,-1 , 6423, "Pogorevka"),
		new BountyLocation(10705,-1 , 8050, "Polana"),
		new BountyLocation(5754,-1 , 13334, "Polesovo"),
		new BountyLocation(8016,-1 , 3400, "Prigorodki"),
		new BountyLocation(4961,-1 , 5638, "Pulkovo"),
		new BountyLocation(9155,-1 , 3911, "Pusta"),
		new BountyLocation(3071,-1 , 7917, "Pustoshka"),
		new BountyLocation(6209,-1 , 12675, "Ratnoe"),
		new BountyLocation(4772,-1 , 6791, "Rogovo"),
		new BountyLocation(7922,-1 , 12651, "Severograd"),
		new BountyLocation(9678,-1 , 6530, "Shakhovka"),
		new BountyLocation(1467,-1 , 11951, "Sinistok"),
		new BountyLocation(11420,-1 , 15098, "Smirnovo"),
		new BountyLocation(13384,-1 , 6246, "Solnichniy"),
		new BountyLocation(2525,-1 , 6377, "Sosnovka"),
		new BountyLocation(10133,-1 , 5494, "Staroye"),
		new BountyLocation(6090,-1 , 7771, "Stary Sobor"),
		new BountyLocation(4990,-1 , 15082, "Stary Yar"),
		new BountyLocation(9500,-1 , 13748, "Svergino"),
		new BountyLocation(13958,-1 , 13245, "Svetlojarsk"),
		new BountyLocation(3446,-1 , 14792, "Tisy"),
		new BountyLocation(2805,-1 , 12325, "Topolniki"),
		new BountyLocation(7559,-1 , 13309, "Troitskoe"),
		new BountyLocation(12800,-1 , 4407, "Tulga"),
		new BountyLocation(13518,-1 , 14145, "Turovo"),
		new BountyLocation(2300, -1 ,11005, "Vavilovo"),
		new BountyLocation(3835, -1 , 8912, "Vybor"),
		new BountyLocation(9946,-1 , 10373, "Vyshnaya Dubrovka"),
		new BountyLocation(6585,-1 , 6062, "Vyshnoye"),
		new BountyLocation(5706,-1 , 2540, "Vysotovo"),
		new BountyLocation(1200,-1 , 9964, "Zabolotye"),
		new BountyLocation(4560,-1 , 13180, "Zaprudnoe"),
		new BountyLocation(454,-1 , 5189, "Zvir"),
		new BountyLocation(2653,-1 , 1325, "Prison Island")
	};	
	
	
	ref array<ref BountyLoot> m_rewards = new  array<ref BountyLoot>();

	static ref BountySetting Load()
    {
		
		ref BountySetting settings = new BountySetting();

		
		settings.m_admins.Insert("76561198147649086");
	
		ref BountyLoot loot = new ref BountyLoot();
		loot.m_weapon = "M4A1";
		loot.m_weapon_attachements.Insert("ACOGOptic");
		loot.m_weapon_attachements.Insert( "M4_Suppressor");
		loot.m_weapon_attachements.Insert( "M4_RISHndgrd_Black");
		loot.m_weapon_attachements.Insert( "M4_OEBttstck_Black");
		loot.m_weapon_attachements.Insert( "Light_Universal");
	
		loot.m_other_Loot.Insert("Mag_STANAG_30Rnd");
		loot.m_other_Loot.Insert("Mag_STANAG_30Rnd");
		settings.m_rewards.Insert(loot);
		
		
		loot = new ref BountyLoot();
		loot.m_weapon = "SVD";
		loot.m_other_Loot.Insert("Mag_SVD_10Rnd");
		loot.m_other_Loot.Insert("Mag_SVD_10Rnd");
		loot.m_other_Loot.Insert("PSO1Optic");

		settings.m_rewards.Insert(loot);

		if ( !FileExist( BOUNTY_JSON_PATH_DIRECTORY_SETTINGS ) )
		{
			MakeDirectory( BOUNTY_JSON_PATH_DIRECTORY_SETTINGS );
		}
		
		if ( !FileExist( BOUNTY_JSON_PATH_BountySETTINGS ) )
		{
			settings.SaveSettings();
		}
		
		JsonFileLoader<BountySetting>.JsonLoadFile(BOUNTY_JSON_PATH_BountySETTINGS, settings );
		
		JsonFileLoader<BountySetting>.JsonSaveFile(BOUNTY_JSON_PATH_BountySETTINGS + ".BAK", settings );

		if(settings.m_version == "")
		{
			ref BountySetting default_settings = new ref BountySetting();
			settings.m_version = "1.1";
			settings.m_text_BountyDistanceToHunter = default_settings.m_text_BountyDistanceToHunter;
			settings.m_text_NearEnemys = default_settings.m_text_NearEnemys;
			settings.m_text_NewBountyBegin = default_settings.m_text_NewBountyBegin;
			settings.m_text_BountyEndElapsedTimeSendReward = default_settings.m_text_BountyEndElapsedTimeSendReward;
			settings.m_text_BountySuicide = default_settings.m_text_BountySuicide;
			settings.m_text_BountyKilledByInfected = default_settings.m_text_BountyKilledByInfected;
			settings.m_text_BountyLeftGame = default_settings.m_text_BountyLeftGame;
			settings.m_text_BountyForbiddenArea = default_settings.m_text_BountyForbiddenArea;
			settings.m_text_BountyIsKilled = default_settings.m_text_BountyIsKilled;
			settings.m_text_BountyInfo = default_settings.m_text_BountyInfo;
			settings.SaveSettings();
		}

		if(settings.m_version == "1.1")
		{
			settings.m_version = "1.2";
			settings.m_timetoreconnect = 350;
			settings.m_points_survivepoints = 10;
			settings.m_points_killpoints = 25;
			settings.m_points_deathpoints = -5;
			settings.m_points_leavepoints = -25;
			settings.m_showbountyonmap = true;
			settings.m_bountyposqueue = 10;
			settings.m_text_BountyPlayerIsBack = "Bounty player is back, the hunt can go on.";
	    	settings.m_text_BountyPlayerIsDisconnected = "Bounty player is disconnected, waiting for reconnect.";
			settings.SaveSettings();
		}
		
		return settings;
	}
	
	void SaveSettings()
	{
		m_premasave = false;
		JsonFileLoader<BountySetting>.JsonSaveFile(BOUNTY_JSON_PATH_BountySETTINGS, this );
	}
}