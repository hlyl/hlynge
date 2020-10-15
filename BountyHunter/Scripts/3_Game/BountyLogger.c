//################################################################################################################################################################
//####  Made by hlynge - August 2019
//################################################################################################################################################################

class BountyLogger
{
    protected static const string bountyprefix =  " [Bounty] ";

    static bool m_debug = false;

    static void  LogMessage(string message)
    {
		if(m_debug)
        	Print( GetLogDate() +  bountyprefix + message );
    }

    static string GetLogDate() 
	{
		int year, month, day, hour, minute, second;
		GetYearMonthDay(year, month, day);
		GetHourMinuteSecond(hour, minute, second);
		return day.ToStringLen(2) + "." + month.ToStringLen(2) + "." + year.ToStringLen(4) + "." + hour.ToStringLen(2) + "." + minute.ToStringLen(2);
	}
}