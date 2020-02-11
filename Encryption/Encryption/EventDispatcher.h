#pragma once

struct EventData
{
	bool hasEventStarted;
	int EventID;

	void resetData()
	{
		hasEventStarted = false;
		EventID = -1 ;
	}
};

class EventDispatcher
{
public:
	inline EventData hasEventStarted() { return data; };
	void startEvent(EventData eventData) { data = eventData; }
	void handledEvent(int eventID)
	{
		if (eventID == data.EventID)
			data.resetData();
	};
private:
	EventData data;
};