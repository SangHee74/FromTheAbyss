#pragma once

class CheckBox
{
public:


	struct tagCheckBoxPopup
	{
		LPCWSTR script;
		RECT _checkBox;
		RECT _ok;
		RECT _no;
	

		tagCheckBoxPopup()
		{
			_checkBox = RectMakeCenter(RSCENTER_X, CENTER_Y,40,50 );

			_ok = RectMakeCenter(RSCENTER_X - 20, CENTER_Y, 20, 20);
			_no = RectMakeCenter(RSCENTER_X + 20, CENTER_Y, 20, 20);

		}

	};

	CheckBox()	{}
	~CheckBox() {}
};

