modded class MissionGameplay
{
    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);

        Input input = GetGame().GetInput();
        PlayerBase player = GetGame().GetPlayer();

        if (input.LocalPress("UAGetPosOri", true))
        {
            string position = VectorToString(player.GetPosition());
            string orientation = VectorToString(player.GetOrientation());;

            GetGame().CopyToClipboard("<ObjectPosition> " + position + "\n<ObjectOrientation> " + orientation);
            player.MessageStatus("Copied Position & Orientation to clipboard!");
        }
    }

    string VectorToString(vector vec)
    {
        string result = vec.ToString();
        result.Replace("<", string.Empty);
        result.Replace(">", string.Empty);
        return result;
    }
}