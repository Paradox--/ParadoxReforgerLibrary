// This is a simple timer class that allows you to share functionality between game objects. 
// -- Paradox

// To use this class:
// add this to the script that requires a timer: 
// ParadoxTimer MyTimer = new ParadoxTimer(owningEntity, boolean doWeLoop, float amountOfTimeToWait); 
// 
// then when your script when you recieve a frame update for example the IEntity EOnFrame event:
// MyTimer.TimerTick(owner, timeSlice); 
//
// if you want to check if the timer needs to be ticked you can call:
// MyTimer.IsTimerActive()
// it will do this internally, but if you want more control you can add it to your scripts. 
//
// when you want to listen for this timer to go off: 
// MyTimer.GetOnTimerFired().Insert(yourClass.YourFunctionThatCatchesCallback)
// This timers delegate is void so you will need a method signature similar to: void YourFunctionThatCatchesCallback()
//
// if at any time you want to remove a single listener from the timers invokation list:
// MyTimer.GetOnTimerFired().Remove(yourClass.YourFunctionThatCatchesCallback)
//
// To Stop a timer at any time before it goes off, or if the timer is looping 
// MyTimer.ClearTimer()
// This will stop and remove all elements from its invokation list. 


class ParadoxTimer
{
	// -- Class Properties -- // 
	// is this timer active or not? 
	protected bool m_bIsActive = false; 
	
	// does this timer loop or not? 
	protected bool m_bDoesLoop = false; 
	
	// the starting time in seconds of this timer. 
	protected float m_fStartTime = 0.0;
	
	// the amount of time we want to wait before going off in seconds. 
	protected float m_fTimerDelay = 0.0; 
	
	// timer delegate when the timer goes off, either once if it doesnt loop, or till its told to stop if does loop
	ref ScriptInvoker m_OnTimerFired = new ScriptInvoker();
	
	// -- Class Constructor -- // 
	void ParadoxTimer(IEntity timerWorldContext, bool bDoesLoop, float amountOfTimeToWaitInSeconds)
	{
		// set our base properties
		m_bIsActive = true; 
		m_bDoesLoop = bDoesLoop; 
		m_fStartTime = ParadoxFunctionLibrary.GetTimeInSeconds(timerWorldContext);
		m_fTimerDelay = amountOfTimeToWait; 		
	}
	
	void ~ParadoxTimer()
	{
		// nuke any listenrs on our invokation list. 
		m_OnTimerFinished.Clear(); 
	}
	
	// -- Timer Methods -- // 
	// returns if the timer is active or not. 
	bool IsTimerActive()
	{
		return m_bIsActive; 
	}
	
	// returns if this timer is set to loop or not. 
	bool DoesTimerLoop()
	{
		return m_bDoesLoop; 
	}
	
	// returns the starting time of this timer, will be in seconds. 
	float GetTimerStartTime() 
	{
		return m_fStartTime; 
	}
	
	// returns the delay on this timer between each tick. 
	float GetTimerDelay()
	{
		return m_fTimerDelay; 
	}
		
	// returns the timers delegate
	ScriptInvoker GetOnTimerFired()
	{
		return m_OnTimerFired;
	}
	
	// ticks the timer. 
	void TimerTick(IEntity timerWorldContext, float currentTimeInMS)
	{
		// if the timer is not active. 
		if(!IsTimerActive())
		{
			// bail out early. 
			return; 
		}
		else
		{
			// has enough time based between the worlds context time, and the starting time and the required delay of this timer? 
			if(ParadoxFunctionLibrary.HasTimeElaspedInSeconds(timerWorldContext, GetTimerStartTime(), GetTimerDelay()))
			{
				// call the delegate such that any listeners hear this timer has gone off. 
			    m_OnTimerFired.Invoke(); 
				
				// does this timer loop? 
				if(DoesTimerLoop())
				{
					// if we do loop we need to push up the start time to now to reset the loop
					// this will allow us to be called again, and again till we are destroyed or cleared.  
					m_fStartTime = ParadoxFunctionLibrary.GetTimeInSeconds(timerWorldContext);				
				}
				else // else ... 
				{
					// if it does not set we are not active any longer
					m_bIsActive = false; 					
				}
			}
		}
	}
	
	void ClearTimer()
	{
		// reset all the data and the invoke list. 
		m_bIsActive = false; 
		m_bDoesLoop = false;
		m_fStartTime = 0.0; 
		m_fTimerDelay = 0.0; 
		m_OnTimerFired.Clear(); 
	}
};