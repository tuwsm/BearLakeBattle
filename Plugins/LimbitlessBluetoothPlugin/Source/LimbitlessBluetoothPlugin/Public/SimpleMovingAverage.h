#pragma once

template<typename T>
class TSimpleMovingAverage
{
public:
	explicit TSimpleMovingAverage(int32 InWindowSize)
	{
		Initialize(InWindowSize);
	}
	
	TSimpleMovingAverage() = default;

	void AddValue(const T& InValue)
	{
		if (WindowSize <= 0) { return; }
	
		T Front{};
		Window.Dequeue(Front);
		Window.Enqueue(InValue);
 
		Sum = Sum + InValue - Front;
	
		Average = Sum / WindowSize;
	}
	
	void Initialize(int32 InWindowSize)
	{
		Initialize(InWindowSize, {});
	}

	void Initialize(int32 InWindowSize, T DefaultValue)
	{
		Sum = InWindowSize * DefaultValue;
		Average = DefaultValue;
		WindowSize = InWindowSize;
		Window.Empty();
		for (int i = 0; i < InWindowSize; ++i)
		{
			Window.Enqueue(DefaultValue);
		}
	}
	
	const T& GetAverage() const { return Average; }
 
private:
	TQueue<T> Window{};
 
	int32 WindowSize{};
	T Sum{};
	T Average{};
};
