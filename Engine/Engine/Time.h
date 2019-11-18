#ifndef Time_H
#define Time_H
#define DLLEXPORT __declspec(dllexport)


namespace Engine
{
	class DLLEXPORT Time
	{
	private:
		float deltaTime;
	public:
		Time(float time = 0.0f) : deltaTime(time)
		{
		}

		operator float() const { return deltaTime; }
		float GetSeconds() const { return deltaTime; }
	};
}

#endif // Time_H
