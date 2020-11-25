#include "Font.h"

Font::Font()
{
	_Texture = TextureManager::getInstance()->getData()->Get(eType::FONT);
	_Sprite = new CSprite(eType::FONT, 0, 0, 125, 27, _Texture);
}

Font::~Font()
{
	SAFE_DELETE(_Sprite);
}

void Font::Draw(float x, float y, const string& s)
{
	for (UINT i = 0; i < s.size(); i++)
	{
		if (s[i] == ' ')
			continue;
		if (s[i] >= 'A' && s[i] <= 'Z')
		{
			_Sprite->SelectFrame(s[i] - 'A');
		}
		else
			if (s[i] >= '0' && s[i] <= '9')
			{
				_Sprite->SelectFrame(s[i] - '0' + 26);
			}
			else
				_Sprite->SelectFrame(36);
		_Sprite->DrawFrame(_Sprite->GetCurrentFrame(),x + i * 9, y, 13, 9.7, 9);
	}
}
