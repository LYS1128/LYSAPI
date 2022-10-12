#pragma once

template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

template<typename T>
bool		CompareY(T Dest, T Sour)
{
	return Dest->Get_Info().fY < Sour->Get_Info().fY;
}

class CFind_Tag
{


public:
	CFind_Tag(const TCHAR* pString)
		: m_pString(pString) {}

public:
	template<typename T>
	bool		operator()(T& Pair)
	{
		if (!lstrcmp(m_pString, Pair.first))
			return true;

		return false;
	}

private:
	const	TCHAR*		m_pString;
};

class CDeleteMap
{
public:
	template<typename T>
	void		operator()(T& Pair)
	{
		if (nullptr != Pair.second)
		{
			delete Pair.second;
			Pair.second = nullptr;
		}
	}
};