#pragma once

enum EventID
{
	NoEvent,
	WindowCloseEvent,
	EncryptionEvent,
	DecryptionEvent,
	SwitchTextEvent
};

struct EventData
{
	bool hasEventStarted;
	EventID id;

	void resetData()
	{
		hasEventStarted = false;
		id = NoEvent;
	}
};

class EventDispatcher
{
public:
	inline EventData hasEventStarted() { return data; };
	void startEvent(EventData eventData) { data = eventData; }
	void handledEvent(EventID eventID)
	{
		if (eventID == data.id)
			data.resetData();
	};
private:
	EventData data;
};