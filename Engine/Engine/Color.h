#ifndef COLOR_H
#define COLOR_H
#define DLLEXPORT __declspec(dllexport)

#define RBGTOFLOAT 0.004f

namespace Engine
{
	//extern int RBGTOFLOAT;

	class DLLEXPORT Color
	{
	private:
		float _red;
		float _green;
		float _blue;
		float _alpha;
	public:
		Color();
		Color(float red, float green, float blue, float alpha);
		void SetColor(float red, float green, float blue, float alpha);
		float GetRed();
		float GetGreen();
		float GetBlue();
		float GetAlpha();
		~Color();
	};
}

#endif //COLOR_H
