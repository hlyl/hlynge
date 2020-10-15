//################################################################################################################################################################
//####  Made by hlynge - August 2019
//################################################################################################################################################################

class BountyLocation
{
    float m_x;
	float m_y;
    float m_z;

    string m_name;

    void BountyLocation(float x, float z, float y,  string name) 
	{
        m_x = x;
        m_y = y;

        if(z == -1)
            m_z =  GetGame().SurfaceY(m_x, m_y) ;
		else
			m_z = z;
        m_name = name;
    }

    vector GetPosition()
    {
      	vector pos;
		pos[0] = m_x;
		pos[1] = m_z;
		pos[2] =  m_y ;
        return pos;
    }
}
